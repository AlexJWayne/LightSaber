//
//  BTLE.swift
//  LightSaber
//
//  Created by Alex Wayne on 8/1/14.
//  Copyright (c) 2014 Alex Wayne. All rights reserved.
//

import Foundation
import CoreBluetooth

let serviceUUID  = CBUUID.UUIDWithString("6E400001-B5A3-F393-E0A9-E50E24DCCA9E")
let writeUUID    = CBUUID.UUIDWithString("6E400002-B5A3-F393-E0A9-E50E24DCCA9E")
let readUUID     = CBUUID.UUIDWithString("6E400003-B5A3-F393-E0A9-E50E24DCCA9E")
let infoUUID     = CBUUID.UUIDWithString("180A")
let revisionUUID = CBUUID.UUIDWithString("2A27")

class BTLE : NSObject, CBCentralManagerDelegate, CBPeripheralDelegate {
    lazy var cm: CBCentralManager = CBCentralManager(delegate: self, queue: nil)
    
    var connected = false
    var peripheral: CBPeripheral?
    var service: CBService?
    var readCharacteristic: CBCharacteristic?
    var writeCharacteristic: CBCharacteristic?
    
    var programs: [Program] = []
    var buffer: NSMutableData? = nil
    
    var onReceivedPrograms: ((programs: [Program])->())?
    var onDisconnect: (()->())?
    
    func scan() {
        if !connected {
            NSLog("Scanning...")
            cm.stopScan()
            cm.scanForPeripheralsWithServices([serviceUUID], options: nil)
            
            NSTimer.scheduledTimerWithTimeInterval(2, target: self, selector: Selector("scan"), userInfo: nil, repeats: false)
        }
    }
    
    func send(data: NSData) {
        NSLog("Sending %d bytes", data.length)
        peripheral!.writeValue(data,
            forCharacteristic: writeCharacteristic,
            type: .WithoutResponse
        )
    }
    
    
    // MARK: CBCentralManagerDelegate
    
    func centralManager(central: CBCentralManager!, didDiscoverPeripheral peripheral: CBPeripheral!, advertisementData: [NSObject : AnyObject]!, RSSI: NSNumber!) {
        NSLog("Dicovered peripheral")
        self.peripheral = peripheral
        cm.cancelPeripheralConnection(peripheral)
        cm.connectPeripheral(peripheral, options: nil)
    }
    
    func centralManagerDidUpdateState(central: CBCentralManager!) {
        switch cm.state {
        case .Unknown:
            NSLog("Unknown")
        case .Resetting:
            NSLog("Resetting")
        case .Unsupported:
            NSLog("Unsupported")
        case .Unauthorized:
            NSLog("Unauthorized")
        case .PoweredOn:
            NSLog("PoweredOn")
        case .PoweredOff:
            NSLog("PoweredOff")
        }
    }
    
    func centralManager(central: CBCentralManager!, didConnectPeripheral peripheral: CBPeripheral!) {
        NSLog("Connected!")
        connected = true
        
        peripheral.delegate = self
        peripheral.discoverServices([serviceUUID])
    }
    
    func centralManager(central: CBCentralManager!, didDisconnectPeripheral peripheral: CBPeripheral!, error: NSError!) {
        NSLog("Disconnected")
        connected = false
        self.peripheral = nil
        onDisconnect?()
        scan()
    }
    
    func centralManager(central: CBCentralManager!, didFailToConnectPeripheral peripheral: CBPeripheral!, error: NSError!) {
        NSLog("boo...")
    }
    
    // MARK: CBPeripheralDelegate
    
    func peripheral(peripheral: CBPeripheral!, didDiscoverServices error: NSError!) {
        service = peripheral.services[0] as? CBService
        NSLog("Discovered service: %@", service!)
        
        peripheral.discoverCharacteristics([writeUUID, readUUID], forService: service)
    }
    
    func peripheral(peripheral: CBPeripheral!, didDiscoverCharacteristicsForService service: CBService!, error: NSError!) {
        NSLog("Discovered characteristics: %@", service!)
        for characteristic: CBCharacteristic in service.characteristics as [CBCharacteristic] {
            let uuid: String! = characteristic.UUID.UUIDString
            
            if uuid == readUUID.UUIDString {
                NSLog("found read")
                readCharacteristic = characteristic
                peripheral.setNotifyValue(true, forCharacteristic: readCharacteristic)
                
            } else if uuid == writeUUID.UUIDString {
                NSLog("found write")
                writeCharacteristic = characteristic
                
            } else {
                NSLog("Unknown characteristic: %@", uuid)
                
            }
        }
    }
    
    func peripheral(peripheral: CBPeripheral!, didUpdateValueForCharacteristic characteristic: CBCharacteristic!, error: NSError!) {
        let data: NSData = readCharacteristic!.value

        NSLog("Received data: %@", data)
        if buffer == nil { buffer = NSMutableData() }
        buffer!.appendData(data)
        
        let dataBytes = data.byteArray
        if dataBytes.count == 1 && ProgramProperties.fromRaw(dataBytes[0]) == ProgramProperties.EndTransmission {
            programs = Program.buildPrograms(buffer!)
            onReceivedPrograms?(programs: programs)
            buffer = nil
        }
    }
}