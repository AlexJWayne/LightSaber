//
//  Program.swift
//  LightSaber
//
//  Created by Alex Wayne on 8/2/14.
//  Copyright (c) 2014 Alex Wayne. All rights reserved.
//

import Foundation

enum ProgramProperties: UInt8 {
    case NewProgram      = 0x01
    case EndTransmission = 0xFF
    case ID              = 0x02
    case Name            = 0x03
}

enum ProgramCommand: UInt8 {
    case SwitchMode = 0x01
}


class Program : NSObject {
    
    var id: UInt8 = 0xFF
    var name: String = "Untitled"
    
    
    var bt: BTLE {
        return AppDelegate.instance().bt
    }
    
    class func buildPrograms(data: NSData) -> [Program] {
        NSLog("Received complete data: %@", data);
        
        var programs: [Program] = []
        var programDataArrays: [[UInt8]] = []
        let bytes: [UInt8] = data.byteArray
        
        var cursor: Int = 0
        
        var foo: [UInt8] = [1,2,3,4]
        var bar: Slice<UInt8> = foo[1...2]
        
        
        while cursor < bytes.count {
            if let prop = ProgramProperties.fromRaw(bytes[cursor]) {
                switch prop  {
                case .NewProgram:
                    let len = Int(bytes[cursor + 1])
                    let programBytes = [UInt8](
                        bytes[cursor..<cursor+len]
                    )

                    programDataArrays += programBytes
                    cursor += len
                    
                case .EndTransmission:
                    NSLog("Creating programs!")
                    for pBytes in programDataArrays {
                        programs += Program(bytes: pBytes)
                    }
                    return programs
                    
                default:
                    NSLog("This shouldn't happen!")
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
        var cursor: Int = 2
        
        while cursor < bytes.count {
            if let prop = ProgramProperties.fromRaw(bytes[cursor]) {
                switch prop {
                case .ID:
                    id = bytes[cursor+1]
                    cursor += 2
                    
                case .Name:
                    name = ""
                    
                    var len: Int = Int(bytes[cursor+1])
                    var nameBytes = [UInt8]( bytes[cursor+2..<cursor+2+len] )
                    self.name = NSString(bytes: nameBytes, length: len, encoding: NSASCIIStringEncoding)
                    cursor += 2 + len
                    
                default:
                    NSLog("Unknown property ID: %d", bytes[cursor])
                }
            } else {
                NSLog("This shouldn't happen!")
                break
            }
        }
        
        NSLog("Name: %@, id: %d", name, id)
    }
    
    func sendActivation() {
        var cmd: [UInt8] = [ProgramCommand.SwitchMode.toRaw(), id]
        AppDelegate.instance().bt.send(NSData(bytes: cmd, length: 2))
    }
}