//
//  BTLE.swift
//  LightSaber
//
//  Created by Alex Wayne on 7/24/14.
//  Copyright (c) 2014 Alex Wayne. All rights reserved.
//

import Foundation
import CoreBluetooth

private let serviceUUID = "6E400001-B5A3-F393-E0A9-E50E24DCCA9E"
private let txUUID      = "6E400002-B5A3-F393-E0A9-E50E24DCCA9E"
private let rxUUID      = "6E400003-B5A3-F393-E0A9-E50E24DCCA9E"

class BTLE : NSObject, UARTPeripheralDelegate {
    
    var currentPeripheral: LGPeripheral?
    var currentService: LGService?
    var sendCharacteristic: LGCharacteristic?
    var receiveCharacteristic: LGCharacteristic?
    
    func scan() {
        NSLog("Scanning...")
        
        LGCentralManager.sharedInstance()
            .scanForPeripheralsByInterval(4,
                services: [UARTPeripheral.uartServiceUUID()],
                options: nil,
                completion: { (peripherals) in
                    NSLog("Found %d peripherals", peripherals.count)
                    if peripherals.count > 0 {
                        self.connect(peripherals[0] as LGPeripheral)
                    }
                })
    }
    
    func connect(peripheral: LGPeripheral) {
        
        // Open connection
        peripheral.connectWithCompletion({ (error) in
            if error { NSLog("Error: %@", error) }
            
            peripheral.discoverServicesWithCompletion({ (services, error) in
                if error { NSLog("Error: %@", error) }
                
                for service in services as [LGService] {
                    if service.UUIDString.uppercaseString == serviceUUID {
                        self.currentService = service
                        
                        service.discoverCharacteristicsWithCompletion({ (characteristics, error) in
                            for characteristic in characteristics as [LGCharacteristic] {
                                if error { NSLog("Error: %@", error) }
                                
                                switch characteristic.UUIDString.uppercaseString {
                                case rxUUID:
                                    self.receiveCharacteristic = characteristic
                                case txUUID:
                                    self.sendCharacteristic = characteristic
                                default:
                                    NSLog("Unknown characteristic: %@", characteristic.UUIDString)
                                }
                            }
                            
                            // Save peripheral, we are connected
                            self.currentPeripheral = peripheral
                        })
                    }
                }
            })
        })
    }
    
    func send(data: NSData) {
        let maxBytes: Int = 20
        
        if currentPeripheral && sendCharacteristic {
            var byteIndex: Int = 0
            NSLog("Sending %d bytes...", data.length)
            
            while byteIndex < data.length {
                var length: Int = maxBytes
                if byteIndex + maxBytes > data.length {
                    length = data.length - byteIndex
                }
                
                var packet = data.subdataWithRange(NSRange(location: byteIndex, length: length))
                sendCharacteristic!.writeValue(packet, completion: nil)
                byteIndex += maxBytes
            }
        }
    }
    
    
    // MARK: UARTPeripheralDelegate
    
    func didReceiveData(newData: NSData!) {
        NSLog("got data")
    }
    
    func didReadHardwareRevisionString(string: String!) {
        NSLog("HW Revision: %@", string)
    }
    
    func uartDidEncounterError(error: String!) {
        NSLog("UART ERROR: %@", error)
    }
}