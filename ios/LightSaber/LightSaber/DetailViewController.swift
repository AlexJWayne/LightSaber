//
//  DetailViewController.swift
//  LightSaber
//
//  Created by Alex Wayne on 8/1/14.
//  Copyright (c) 2014 Alex Wayne. All rights reserved.
//

import UIKit

struct ChannelAnimation {
    var channel: Int? = 0
    var lastMs: Double = 0
    var elapsedMs: Double = 0
    
    init() {
        lastMs = NSDate().timeIntervalSince1970
    }
    
    mutating func updateElapsed() {
        var now = NSDate().timeIntervalSince1970
        elapsedMs += now - lastMs
        lastMs = now
    }
}

class DetailViewController: UITableViewController {
    
    var program: Program! {
        didSet {
            program?.sendActivation()
            self.configureView()
        }
    }
    
    var animation: ChannelAnimation = ChannelAnimation()
    
    @IBAction func didUpdateSlider(sender: UIControl) {
        let slider = sender as UISlider
        program.updateChannel(UInt8(slider.tag), value: UInt8(Int(slider.value * 255.0)))
    }
    
    @IBAction func didToggleSwitch(sender: UIControl) {
        let toggle = sender as UISwitch
        
        for cell in tableView.visibleCells() {
            if (cell as ChannelCell).toggle != toggle {
                (cell as ChannelCell).toggle.setOn(false, animated: true)
            }
        }
        
        if toggle.on {
            animation.channel = toggle.tag
            animateChannel()
            NSLog("Channel %d on", animation.channel!)
        } else {
            NSLog("Stopping channel animation")
            animation.channel = nil
        }
    }
    
    func animateChannel() {
        if let channel = animation.channel {
            animation.updateElapsed()
            
            var val: Double = sin(animation.elapsedMs) / 2 + 0.5
            var val8: UInt8 = UInt8(UInt(val * 255))
            program.updateChannel(UInt8(channel), value: val8)
            
            let cell = tableView.cellForRowAtIndexPath(NSIndexPath(forRow: channel, inSection: 0)) as ChannelCell
            cell.slider.value = Float(val)
            
            NSTimer.scheduledTimerWithTimeInterval(1/40, target: self, selector: Selector("animateChannel"), userInfo: nil, repeats: false)
        }
    }
    
    
    
    
    
    // MARK: View Lifecycle

    func configureView() {
        // Update the user interface for the detail item.
        if let detail: Program = program {
            navigationItem!.title = program!.name
        }
    }
    
    override func viewDidDisappear(animated: Bool) {
        animation.channel = nil
    }

    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
        self.configureView()
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    // MARK: UITableViewDelegate
    
    override func tableView(tableView: UITableView!, shouldHighlightRowAtIndexPath indexPath: NSIndexPath!) -> Bool {
        return false
    }

    
    // MARK: UITableViewDataSource
    
    override func tableView(tableView: UITableView!, numberOfRowsInSection section: Int) -> Int {
        return program!.channels.count
    }
    
    override func numberOfSectionsInTableView(tableView: UITableView!) -> Int {
        return 1
    }
    
    override func tableView(tableView: UITableView!, cellForRowAtIndexPath indexPath: NSIndexPath!) -> UITableViewCell! {
        let channel: Channel = program.channels[indexPath.row]
        let cell = tableView.dequeueReusableCellWithIdentifier("RangeCell", forIndexPath: indexPath) as ChannelCell
        
        cell.channelID    = channel.id
        cell.slider.value = channel.value
        cell.label.text   = channel.name
        return cell
    }
}

