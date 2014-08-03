//
//  DetailViewController.swift
//  LightSaber
//
//  Created by Alex Wayne on 8/1/14.
//  Copyright (c) 2014 Alex Wayne. All rights reserved.
//

import UIKit

class DetailViewController: UIViewController {
                            
//    @IBOutlet weak var detailDescriptionLabel: UILabel!

    var program: Program? {
        didSet {
            program?.sendActivation()
            
            // Update the view.
            self.configureView()
        }
    }

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


}

