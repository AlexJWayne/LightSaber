//
//  DetailViewController.swift
//  LightSaber
//
//  Created by Alex Wayne on 7/14/14.
//  Copyright (c) 2014 Alex Wayne. All rights reserved.
//

import UIKit

class DetailViewController: UIViewController, UISplitViewControllerDelegate {

    @IBOutlet var detailDescriptionLabel: UILabel
    var masterPopoverController: UIPopoverController? = nil
    var lights = Array<UIView>()

    var detailItem: AnyObject? {
        didSet {
            // Update the view.
            self.configureView()

            if self.masterPopoverController != nil {
                self.masterPopoverController!.dismissPopoverAnimated(true)
            }
        }
    }
    
    var lightProgram: LightProgram {
    get {
        return detailItem as LightProgram
    }
    }
    

    func configureView() {
        // Update the user interface for the detail item.
        if let label = self.detailDescriptionLabel {
            label.text = lightProgram.name
        }
    }
    
    func createLightViews() {
        for i in 0..<48 {
            
            var light = UIView(frame: CGRect(
                x: 1,
                y: 65 + i*10,
                width: 9,
                height: 9
            ))
            self.view.addSubview(light)
            self.lights.append(light)
            
            light.backgroundColor = UIColor.whiteColor()
        }
    }
    

    override func viewDidLoad() {
        super.viewDidLoad()
        self.configureView()
        self.createLightViews()
        self.updateLights()
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }

    
    
    func updateLights() {
//        var light = lights[10]
//        
//        NSLog(light.backgroundColor.description)
//        light.backgroundColor = UIColor.yellowColor()
//        light.frame.origin.x += 20
//        NSLog(light.backgroundColor.description)
        
//        return

        if self.parentViewController {
            let delay: Double = 1/60
            lightProgram.update(Float(delay))
            
            // Set the lights!
            let colors = lightProgram.lights()
            for i in 0..<colors.count  {
                lights[i].backgroundColor = colors[i]
            }
            
            // Schedule next update
            let nsDelay: Int64 = Int64(delay * Double(NSEC_PER_SEC))
            let popTime: dispatch_time_t = dispatch_time(DISPATCH_TIME_NOW, nsDelay)
            dispatch_after(popTime, dispatch_get_main_queue(), {
                self.updateLights()
            })
        }
    }
    
    
    
    // #pragma mark - Split view

    func splitViewController(splitController: UISplitViewController, willHideViewController viewController: UIViewController, withBarButtonItem barButtonItem: UIBarButtonItem, forPopoverController popoverController: UIPopoverController) {
        barButtonItem.title = "Master" // NSLocalizedString(@"Master", @"Master")
        self.navigationItem.setLeftBarButtonItem(barButtonItem, animated: true)
        self.masterPopoverController = popoverController
    }

    func splitViewController(splitController: UISplitViewController, willShowViewController viewController: UIViewController, invalidatingBarButtonItem barButtonItem: UIBarButtonItem) {
        // Called when the view is shown again in the split view, invalidating the button and popover controller.
        self.navigationItem.setLeftBarButtonItem(nil, animated: true)
        self.masterPopoverController = nil
    }
    func splitViewController(splitController: UISplitViewController, collapseSecondaryViewController secondaryViewController: UIViewController, ontoPrimaryViewController primaryViewController: UIViewController) -> Bool {
        // Return true to indicate that we have handled the collapse by doing nothing; the secondary controller will be discarded.
        return true
    }

}

