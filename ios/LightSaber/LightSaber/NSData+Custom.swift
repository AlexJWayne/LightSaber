//
//  NSData+Custom.swift
//  LightSaber
//
//  Created by Alex Wayne on 8/3/14.
//  Copyright (c) 2014 Alex Wayne. All rights reserved.
//

import Foundation

extension NSData {
    var byteArray: [UInt8] {
        var bytes: [UInt8] = [UInt8](count: length, repeatedValue: 0)
        self.getBytes(&bytes)
        return bytes
    }
}