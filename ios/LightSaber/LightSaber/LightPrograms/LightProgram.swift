//
//  LightProgram.swift
//  LightSaber
//
//  Created by Alex Wayne on 7/14/14.
//  Copyright (c) 2014 Alex Wayne. All rights reserved.
//

import UIKit

enum ControlType {
    case Slider
}

class Adjustable {
    var name: String = "Unnamed"
    var type: ControlType = .Slider
    var control: UIView? = nil
    var range: (Float, Float) = (0, 1)
    var onChange: (adj: Adjustable)->() = { (adj: Adjustable) in }
    var getValue: () -> Float = { return 0 }
    
    var slider: UISlider? {
    get {
        if self.control && control is UISlider { return self.control as? UISlider }
        return nil
    }}
    
    init(name: String) {
        self.name = name
    }
}

class LightProgram {
    
    // Name shows up on the screen when this program is selected
    var name: String = "Untitled"
    
    // An array of objects that map UI controls to program variables
    var adjustables = Array<Adjustable>()
    
    // How many leds there
    let lightCount: Int = 48
    
    // Array of colors, one for each LED
    var colors: [UIColor]
    
    // Overall brightness
    var brightness: Float = 1
    
    init() {
        colors = Array()
        for i in 0..<lightCount {
            colors.append(UIColor.whiteColor())
        }
        
//        adj("Brightness", { (adj) in
//            adj.onChange = { (adj) in self.brightness = adj.slider!.value }
//            adj.getValue = { return self.brightness }
//        })
    }
    
    // Creates an adjustable and stores it.
    // Optionally yields a block for configuration.
    func adj(name: String, block: ((adj: Adjustable)->())?) -> Adjustable {
        var adj = Adjustable(name: name)
        if block { block!(adj: adj) }
        adjustables.append(adj)
        return adj
    }
    
    // Blockless convenience method for creation of adjustables
    func adj(name: String) -> Adjustable {
        return adj(name, nil)
    }

    
    // Called every frame, with the time elapsed since the last frame
    // Override to update internal state
    func update(secondsElapsed: Float) {
        eachLight({ (index: Int) -> UIColor in
            return UIColor.whiteColor()
        })
    }
    
    // Iterates thorugh all colors and sets a new color.
    // Call from your update function to set the colors for that frame.
    func eachLight(block: (index: Int) -> UIColor) {
        for i in 0..<lightCount {
            setColor(i, color: block(index: i))
        }
    }
    
    // darken the color, then set it.
    func setColor(index: Int, color: UIColor) {
        var r: CGFloat = 0
        var g: CGFloat = 0
        var b: CGFloat = 0
        var a: CGFloat = 0
        
        var cgBrightness = CGFloat(brightness)
        
        color.getRed(&r, green: &g, blue: &b, alpha: &a)
        colors[index] = UIColor(
            red:   r * cgBrightness,
            green: g * cgBrightness,
            blue:  b * cgBrightness,
            alpha: a
        )
    }
    
    
    
    // Utility Functions
    
    // Wrap float values until they are 0-1 ranged
    func loopFloat(value: Float) -> Float {
        var result = value
        while result > 1 { result -= 1 }
        while result < 0 { result += 1 }
        return result
    }
    
    // Utility function to map a float value in a known input range to an output range
    func mapValue(actual: Float, inMin: Float, inMax: Float, outMin: Float, outMax: Float) -> Float {
        if actual <= inMin { return outMin }
        if actual >= inMax { return outMax }
        
        let completion = (actual - inMin) / (inMax - inMin)
        return completion * (outMax - outMin) + outMin
    }
    
    // Utility function to map a float value between 0 and 1 to an outpute range
    func mapValue(actual: Float, outMin: Float, outMax: Float) -> Float {
        return mapValue(actual, inMin: 0, inMax: 1, outMin: outMin, outMax: outMax)
    }
    
    // Return an NSData with all color data packaged as a sdtream of 24bit colors.
    func dataBlob() -> NSData {
        var data = NSMutableData(capacity: lightCount*3)
        
        for color: UIColor in colors {
            var rgb = color.rgba8
            data.appendBytes([rgb.r, rgb.g, rgb.a] as [UInt8], length: 3);
        }
        
        return data
    }
    
    // ---------------
    // --- PRIVATE ---
    // ---------------
    
    // Check each adjustable and updates things with the value of its control
    func updateAdjustables() {
        for adj in adjustables {
            adj.onChange(adj: adj)
        }
    }
}