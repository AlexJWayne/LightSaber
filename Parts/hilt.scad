tubeRadius = 20.9;
tubeLip = 5;

hiltHeight = 25;

wallWidth  = 2.25;

usbHoleWidth  = 8;
usbHoleHeight = 4;
usbHoleLength = 7;
usbOffset     = 4.25;

arduinoWidth  = 50;
arduinoHeight = 6.5;
arduinoLength = 18;

dialHoleRadius = 4;
dialHoleDistance = 8.5;

potAnchorFromCenter = 8;
potAnchorRaduis = 1.25;

switchLength = 11.5;
switchWidth  = 4.2;
switchHeight = 6;
switchLip    = 2;

difference() {
  body();


//  translate([arduinoLength/2, 7, 2])
//    rotate([0, -90, 0])
//      arduino();

  translate([dialHoleDistance, 0, 0])
    cylinder(h=hiltHeight, r=dialHoleRadius, center=true, $fn=90);

  translate([-dialHoleDistance, 0, 0]) {
    rotate(17.5)
      union() {
        cylinder(h=hiltHeight, r=dialHoleRadius, center=true, $fn=90);

        translate([potAnchorFromCenter,0,0])
          cylinder(h=3, r=potAnchorRaduis, center=false, $fn=20);
      }
  }

  // switch hole
  translate([0, 12, 0])
    cube(size=[switchLength, switchWidth, switchHeight], center=true);
}

module body() {
  intersection() {
    difference() {
      union() {
        cylinder(h=hiltHeight, r=tubeRadius, $fn=360);
        cylinder(h=tubeLip, r=tubeRadius+tubeLip, $fn=360);
      }
      
      translate([0, 0, 2])
        cylinder(h=hiltHeight, r=tubeRadius - wallWidth, center=false, $fn=360);
    }

    cylinder(h=hiltHeight, r1=tubeRadius*1.4, r2=tubeRadius-wallWidth*.75, center=false, $fn=360);
  }
}


module arduino() {
  union() {
    cube(size=[arduinoWidth, arduinoHeight, arduinoLength]);

    translate([-3, usbOffset, arduinoLength/2 - usbHoleLength/2])
      cube(size=[arduinoWidth, usbHoleHeight, usbHoleLength]);
  }
}