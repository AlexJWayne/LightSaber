//
//  Program.swift
//  LightSaber
//
//  Created by Alex Wayne on 8/2/14.
//  Copyright (c) 2014 Alex Wayne. All rights reserved.
//

import Foundation

enum ProgramProperties: UInt8 {
    case Name = 0x01
}


class Program {
    var name: String = "Untitled"
    
    init(data: NSData) {
        var cursor: Int = 0
        var bytes = [UInt8](count:data.length, repeatedValue:0)
        data.getBytes(&bytes, length:data.length)
        
        while cursor < bytes.count {
            switch bytes[cursor] {
            case ProgramProperties.Name.toRaw():
                name = ""
                
                cursor++
                var len: Int = Int(bytes[cursor])
                
                cursor++
                var nameBytes = [UInt8](count:data.length, repeatedValue:0)
                data.getBytes(&nameBytes, range: NSRange(location: cursor, length: len))
                
                cursor += len
                for byte in nameBytes {
                    self.name += NSString(bytes: [byte] as [UInt8], length: 1, encoding: NSASCIIStringEncoding)
                    
                }
                
            default:
                NSLog("Unknown property ID: %d", bytes[cursor])
            }
        }
        
        NSLog("Name: %@", name)
    }
}