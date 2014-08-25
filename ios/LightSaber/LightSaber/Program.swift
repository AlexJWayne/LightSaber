//
//  Program.swift
//  LightSaber
//
//  Created by Alex Wayne on 8/2/14.
//  Copyright (c) 2014 Alex Wayne. All rights reserved.
//

import Foundation

let PROTOCOL_VERSION: UInt8 = 1

enum ProgramProperties: UInt8 {
    case NewProgram      = 0x01
    case ID              = 0x02
    case Name            = 0x03
    
    // Program Channel types
    case VarRange        = 0x04
    
    case EndTransmission = 0xFF
}

enum ProgramCommand: UInt8 {
    case SwitchMode = 0x01
    case WriteVar   = 0x02
}

class Channel {
    let id: UInt8
    let name: String
    let type: ProgramProperties
    let value: Float
    var value8: UInt8 {
        return UInt8(self.value * 255)
    }
    
    init(id: UInt8, name: String, type: ProgramProperties, value: Float) {
        self.id = id
        self.type = type
        self.name = name
        self.value = value
    }
}

class Program : NSObject {
    
    var id: UInt8 = 0xFF
    var name: String = "Untitled"
    var channels: [Channel] = []
    
    
    var bt: BTLE {
        return AppDelegate.instance().bt
    }
    
    class func buildPrograms(data: NSData) -> [Program] {
        NSLog("Received complete data: %@", data);
        
        var programs: [Program] = []
        var programDataArrays: [[UInt8]] = []
        let bytes: [UInt8] = data.byteArray
        
        var cursor: Int = 0
        
        while cursor < bytes.count {
            if let prop = ProgramProperties.fromRaw(bytes[cursor]) {
                switch prop {
                case .NewProgram:
                    let len = Int(bytes[cursor + 2])
                    NSLog("Program len: %d", len)
                    let programBytes = [UInt8](
                        bytes[cursor..<cursor+len]
                    )

                    programDataArrays.append(programBytes)
                    cursor += len
                    
                case .EndTransmission:
                    NSLog("Creating programs!")
                    for pBytes in programDataArrays {
                        programs.append(Program(bytes: pBytes))
                    }
                    return programs
                    
                default:
                    NSLog("This shouldn't happen!!!")
                    break
                }
            } else {
                NSLog("This shouldn't happen: %x", bytes[cursor])
                break
            }
        }
        
        return programs
    }
    
    init(bytes: [UInt8]) {
        // Start at descriptor of first property
        var cursor: Int = 3
        
        while cursor < bytes.count {
            if let prop = ProgramProperties.fromRaw(bytes[cursor]) {
                switch prop {
                case .ID:
                    id = bytes[cursor+1]
                    cursor += 2
                    
                case .Name:
                    name = ""
                    
                    let len: Int = Int(bytes[cursor+1])
                    let nameBytes = [UInt8]( bytes[(cursor + 2)..<(cursor + 2 + len)] )
                    self.name = NSString(bytes: nameBytes, length: len, encoding: NSASCIIStringEncoding)
                    cursor += 2 + len
                
                case .VarRange:
                    let channelID: UInt8 = UInt8(channels.count)
                    let channelValue: Float = Float(Int(bytes[cursor+1])) / 255
                    
                    let len = Int(bytes[cursor+2])
                    let nameBytes = [UInt8]( bytes[(cursor + 3)..<(cursor + 3 + len)] )
                    let name = NSString(bytes: nameBytes, length: len, encoding: NSASCIIStringEncoding)
                    
                    channels.append(Channel(
                        id: channelID,
                        name: name,
                        type: .VarRange,
                        value: channelValue
                    ))
                    cursor += 3 + len
                    
                default:
                    NSLog("Unknown property ID: %d", bytes[cursor])
                }
            } else {
                NSLog("This shouldn't happen! %d", bytes[cursor])
                break
            }
        }
        
        NSLog("Name: %@, id: %d, channels: %d", name, id, channels.count)
    }
    
    func sendActivation() {
        var cmd: [UInt8] = [ProgramCommand.SwitchMode.toRaw(), id]
        bt.send(NSData(bytes: cmd, length: 2))
    }
    
    func updateChannel(channelID: UInt8, value: UInt8) {
        var cmd: [UInt8] = [ProgramCommand.WriteVar.toRaw(), channelID, value]
        bt.send(NSData(bytes: cmd, length: 3))
    }
}