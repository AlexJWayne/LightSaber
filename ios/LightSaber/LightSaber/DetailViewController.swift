//
//  DetailViewController.swift
//  LightSaber
//
//  Created by Alex Wayne on 8/1/14.
//  Copyright (c) 2014 Alex Wayne. All rights reserved.
//

import UIKit

class DetailViewController: UITableViewController {
                            
//    @IBOutlet weak var detailDescriptionLabel: UILabel!

    var program: Program? {
        didSet {
            program?.sendActivation()
            
            // Update the view.
            self.configureView()
        }
    }
    
    @IBAction func didUpdateSlider(sender: UIControl) {
        let slider = sender as UISlider
        program!.updateChannel(UInt8(slider.tag), value: UInt8(Int(slider.value * 255.0)))
    }
    
    
    
    
    
    // MARK: View Lifecycle

    func configureView() {
        // Update the user interface for the detail item.
        if let detail: Program = program {
            navigationItem!.title = program!.name
        }
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
        let cell = tableView.dequeueReusableCellWithIdentifier("RangeCell", forIndexPath: indexPath) as UITableViewCell
        if let slider = cell.viewWithTag(-1) {
            slider.tag = indexPath!.row
        }
        
        if let label = cell.viewWithTag(10) as? UILabel {
            label.text = String(indexPath.row + 1)
        }
        
        return cell
    }
}

