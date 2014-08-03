//
//  Array+Custom.swift
//  LightSaber
//
//  Created by Alex Wayne on 8/3/14.
//  Copyright (c) 2014 Alex Wayne. All rights reserved.
//

import Foundation

extension Array {
    var last: T? {
        if self.count > 0 {
            return self[count - 1]
        } else {
            return nil
        }
    }
}