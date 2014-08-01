//
//  DetailViewController.swift
//  LightSaber
//
//  Created by Alex Wayne on 7/14/14.
//  Copyright (c) 2014 Alex Wayne. All rights reserved.
//

import UIKit

class DetailViewController: UIViewController, UISplitViewControllerDelegate {
    
    @IBOutlet var controlsView: UIView?
    @IBOutlet var lightsView: UIView?
    var lastViewFrame: CGRect = CGRectZero
    
    var lights = Array<UIView>()
    var bt: BTLE = BTLE()
    

    // Update the view when the detailItem changes
    var detailItem: AnyObject? {
        didSet {
            self.configureView()
        }
    }
    
    // Always returns a lightProgram instance
    var lightProgram: LightProgram {
    get {
        if !detailItem { detailItem = LightProgram() }
        return detailItem as LightProgram
    }
    }
    
    
    // Update the user interface for the detail item.
    func configureView() {
        navigationItem.title = lightProgram.name
    }
    
    // Create a view for every LED
    func createLightViews() {
        for i in 0..<lightProgram.lightCount {
            var light = UIView()
            
            light.backgroundColor = UIColor.whiteColor()
            
            lightsView!.addSubview(light)
            lights.append(light)
        }
    }
    
    func setFrames() {
        if lightsView!.frame != lastViewFrame {
            lastViewFrame = lightsView!.frame
            
            // lights
            let numLights: CGFloat  = CGFloat(lightProgram.lightCount)
            var width: CGFloat      = lightsView!.frame.size.width
            var height: CGFloat     = lightsView!.frame.size.height / numLights
            
            for i in 0..<lightProgram.lightCount {
                lights[i].frame = CGRect(
                    x: 0,
                    y: CGFloat(i) * height,
                    width:  width,
                    height: height - 0.5
                )
            }
            
            
            // controls
            for i in 0..<lightProgram.adjustables.count {
                let header: CGFloat = 30
                let height: CGFloat = 60

                var adj = lightProgram.adjustables[i]
                adj.control!.frame = CGRect(
                    x: 20,
                    y: header + height * CGFloat(i),
                    width: controlsView!.frame.size.width - 40,
                    height: 30
                )
            }
        }
    }
    
    func createControls() {
        let header: CGFloat = 10
        let height: CGFloat = 60
        var y: CGFloat = header
        
        for adj in lightProgram.adjustables {
            switch adj.type {
            case .Slider:
                
                // Name label
                var label = UILabel(frame: CGRect(
                    x: 20,
                    y: y,
                    width: controlsView!.frame.size.width - 40,
                    height: 30
                ))
                label.text = adj.name
                label.textColor = UIColor.whiteColor()
                controlsView!.addSubview(label)
                
                // Slider control
                var control = UISlider()
                controlsView!.addSubview(control)
                adj.control = control
                
                control.minimumValue = adj.range.0
                control.maximumValue = adj.range.1
                control.value = adj.getValue()
                
                y += height
            }
        }
    }
    

    override func viewDidLoad() {
        super.viewDidLoad()
        configureView()
        createLightViews()
        createControls()
        setFrames()
        
        updateLights()
        bt.scan()
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    func updateLights() {
        if self.parentViewController {
            let delay: Double = 1/10
            
            // Schedule next update
            NSTimer.scheduledTimerWithTimeInterval(
                delay,
                target: self,
                selector: Selector("updateLights"),
                userInfo: nil,
                repeats: false
            )
            
            // Ensure that dynamic views are still in the right place
            setFrames()
            
            // update adjustables
            lightProgram.updateAdjustables()
            
            // Set the lights!
            lightProgram.update(Float(delay))
            for i in 0..<lightProgram.colors.count {
                lights[i].backgroundColor = lightProgram.colors[i]
            }
            
            bt.send(lightProgram.dataBlob())
        }
    }
    
    //MARK: Split view
    var masterPopoverController: UIPopoverController? = nil
    
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

