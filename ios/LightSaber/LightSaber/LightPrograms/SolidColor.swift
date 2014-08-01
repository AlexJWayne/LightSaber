//
//  SolidColor.swift
//  LightSaber
//
//  Created by Alex Wayne on 7/18/14.
//  Copyright (c) 2014 Alex Wayne. All rights reserved.
//

import UIKit

class SolidColor : LightProgram {
    var hue: Float = 0
    var saturation: Float = 1
    
    init() {
        super.init()
        
        name = "Solid Color"
        
        adj("Hue", { (adj) in
            adj.getValue = { return self.hue }
            adj.onChange = { (adj) in self.hue = adj.slider!.value }
        })
        
        adj("Saturation", { (adj) in
            adj.getValue = { return self.saturation }
            adj.onChange = { (adj) in self.saturation = adj.slider!.value }
        })
    }
    
    override func update(secondsElapsed: Float) {
        let color = UIColor(
            hue: CGFloat(hue),
            saturation: CGFloat(saturation),
            brightness: 1,
            alpha: 1
        )
        
        self.eachLight({ (index: Int) -> UIColor in
            return color
        })
    }
}