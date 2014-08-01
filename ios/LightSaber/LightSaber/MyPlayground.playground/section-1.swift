// Playground - noun: a place where people can play

import Cocoa

struct Vector {
    
    var x: Double = 0.0 {
    didSet {
        magnitudeActual = -1.0
    }
    }
    var y: Double = 0.0 {
    didSet {
        magnitudeActual = -1.0
    }
    }
    
    var magnitudeActual: Double = -1.0
    
    var magnitude: Double {
    mutating get {
        if magnitudeActual < 0.0 {
            NSLog("Recalc")
            magnitudeActual = sqrt(x * x + y * y)
        }
        return magnitudeActual
    }
    }
    
    init() {}
    
    init(_ x: Double, _ y: Double) {
        self.x = x
        self.y = y
    }
}

var v = Vector(3, 4)
v.magnitude
v.magnitude


v.x = 5
v.y = 12
v.magnitude