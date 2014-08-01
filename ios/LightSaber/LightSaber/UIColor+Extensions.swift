//
//  UIColor+Extensions.swift
//  LightSaber
//
//  Created by Alex Wayne on 7/29/14.
//  Copyright (c) 2014 Alex Wayne. All rights reserved.
//

import UIKit

extension UIColor {
    var rgba: (r: CGFloat, g: CGFloat, b: CGFloat, a: CGFloat) {
    get {
        var res = (r: CGFloat(0), g: CGFloat(0), b: CGFloat(0), a: CGFloat(0))
        self.getRed(&res.r, green: &res.g, blue: &res.b, alpha: &res.a)
        return res
    }
    }
    
    var rgba8: (r: UInt8, g: UInt8, b: UInt8, a: UInt8) {
    get {
        var floats = self.rgba
        return (
            UInt8(Int(floats.r * 255)),
            UInt8(Int(floats.g * 255)),
            UInt8(Int(floats.b * 255)),
            UInt8(Int(floats.a * 255))
        )
    }
    }
}
