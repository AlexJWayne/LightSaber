//
//  LightProgram.swift
//  LightSaber
//
//  Created by Alex Wayne on 7/14/14.
//  Copyright (c) 2014 Alex Wayne. All rights reserved.
//

import UIKit

class LightProgram {
    let lightCount = 48
    
    let name = "Hue Crawl"
    
    var hue: Float = 0
    var hueSpread: Float = 0.5
    var hueSpeed: Float = 1
    
    func update(secondsElapsed: Float) {
        hue += hueSpeed * secondsElapsed * hueSpread
        hue = loopFloat(hue)
    }
    
    func lights() -> Array<UIColor> {
        var result = Array<UIColor>()
        
        for i in 0..<48 {
            let lightHue = loopFloat(hue + Float(i)/48*hueSpread)
            var color = UIColor(hue: CGFloat(lightHue), saturation: 1, brightness: 1, alpha: 1)
            result.append(color)
        }
        
        return result
    }
    
    func loopFloat(value: Float) -> Float {
        var result = value
        while result > 1 { result -= 1 }
        while result < 0 { result += 1 }
        return result
    }
    
}