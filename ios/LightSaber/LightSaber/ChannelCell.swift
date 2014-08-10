//
//  ChannelCell.swift
//  LightSaber
//
//  Created by Alex Wayne on 8/10/14.
//  Copyright (c) 2014 Alex Wayne. All rights reserved.
//

import UIKit

class ChannelCell : UITableViewCell {
    @IBOutlet var label: UILabel!
    @IBOutlet var slider: UISlider!
    @IBOutlet var toggle: UISwitch!
    
    var channelID: UInt8 = 0xFF {
    didSet {
        slider.tag = Int(channelID)
        toggle.tag = Int(channelID)
        label.text = String(channelID)
    }
    }
}