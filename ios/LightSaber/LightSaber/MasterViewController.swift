//
//  MasterViewController.swift
//  LightSaber
//
//  Created by Alex Wayne on 8/1/14.
//  Copyright (c) 2014 Alex Wayne. All rights reserved.
//

import UIKit

class MasterViewController: UITableViewController {
    
    var bt: BTLE = AppDelegate.instance().bt
    var objects = NSArray()


    override func awakeFromNib() {
        super.awakeFromNib()
    }

    override func viewDidLoad() {
        super.viewDidLoad()
        
        bt.onReceivedPrograms = { (programs) in
            self.objects = NSArray(array: programs)
            self.tableView!.reloadData()
        }
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }

    // MARK: - Segues

    override func prepareForSegue(segue: UIStoryboardSegue, sender: AnyObject?) {
        if segue.identifier == "showDetail" {
            let indexPath = self.tableView.indexPathForSelectedRow()
            let object = objects[indexPath.row] as Program
            (segue.destinationViewController as DetailViewController).program = object
        }
    }

    // MARK: - Table View

    override func numberOfSectionsInTableView(tableView: UITableView) -> Int {
        return 1
    }

    override func tableView(tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        if bt.connected {
            return objects.count
        } else {
            return 1
        }
    }

    override func tableView(tableView: UITableView, cellForRowAtIndexPath indexPath: NSIndexPath) -> UITableViewCell {
        if bt.connected {
            let cell = tableView.dequeueReusableCellWithIdentifier("ProgramCell", forIndexPath: indexPath) as UITableViewCell
            let object = objects[indexPath.row] as Program
            cell.textLabel.text = object.name
            return cell
            
        } else {
            let cell = tableView.dequeueReusableCellWithIdentifier("WaitingCell", forIndexPath: indexPath) as UITableViewCell
            var spinner = UIActivityIndicatorView(activityIndicatorStyle: .White)
            spinner.startAnimating()
            cell.accessoryView = spinner
            return cell
        }
    }
    
    override func tableView(tableView: UITableView!, didSelectRowAtIndexPath indexPath: NSIndexPath!) {
        performSegueWithIdentifier("showDetail", sender: self)
    }
}

