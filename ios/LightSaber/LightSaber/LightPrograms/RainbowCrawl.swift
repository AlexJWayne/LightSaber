//
//  RainbowCrawl.swift
//  LightSaber
//
//  Created by Alex Wayne on 7/14/14.
//  Copyright (c) 2014 Alex Wayne. All rights reserved.
//

import UIKit

class RainbowCrawl : LightProgram {
    var hue:        Float = 0
    var hueSpread:  Float = 1
    var hueSpeed:   Float = 1
    
    init() {
        super.init()
        name = "Rainbow Crawl"
        
        adj("Speed", { (adj) in
            adj.range = (-2, 2)
            adj.getValue = { return self.hueSpeed }
            adj.onChange = { (adj) in self.hueSpeed = adj.slider!.value }
        })
        
        adj("Wavelength", { (adj) in
            adj.range = (0.2, 4)
            adj.getValue = { return self.hueSpread }
            adj.onChange = { (adj) in self.hueSpread = adj.slider!.value }
        })
    }
    
    override func update(secondsElapsed: Float) {
        hue += hueSpeed * secondsElapsed * (0.5 + hueSpread * 0.5)
        hue = loopFloat(hue)
        
        eachLight({ (index: Int) -> UIColor in
            let distance = Float(index)/Float(self.lightCount)
            let delta = distance * self.hueSpread
            let lightHue = self.loopFloat(self.hue + delta)
            return UIColor(hue: CGFloat(lightHue), saturation: 1, brightness: 1, alpha: 1)
        })
    }
}