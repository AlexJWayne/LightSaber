hiltHeight      = 81;
wallWidth       = 2.25;
tubeRadius      = 18.75;
tubeThickness   = 3.5;
outerWallThick  = 8;
tubeLip         = tubeThickness + outerWallThick;
tubeLipHeight   = 30;

floorThickness  = 2;

boltHoleRadius  = 2.5;
boltHoleFromTop = 6;

switchWidth     = 14.5;
switchLength    = 9;
switchDepth     = 20;
switchOffset    = 11;

pcbWidth        = 35;
pcbHeight       = hiltHeight;
pcbDepth        = 5;
pcbOffset       = 2.5;

usbWidth        = 25;
usbHeight       = 5.5;

difference() {
  body();
  switchHole();
  pcb();
  boltHole();
}

module pcb() {
  union() {
    translate([0, 0, floorThickness])
      hcCube(pcbWidth, pcbDepth, pcbHeight);

    translate([-usbWidth/2, pcbDepth/2+pcbOffset, 0])
      cube([usbWidth, usbHeight, floorThickness+1]);
  }
}

module switchHole() {
  translate([0, -switchOffset, -1])
    hcCube(switchWidth, switchLength, switchDepth+2);

}

module boltHole() {
  translate([0, 0, hiltHeight - boltHoleFromTop])
    rotate([0, 90, 0])
      rotate([90, 0, 0]) {
        cylinder(r=boltHoleRadius, h=tubeRadius*4, center=true, $fn=32);

        translate([0, 0, tubeRadius + wallWidth + outerWallThick - 0.5])
          cylinder(r=boltHoleRadius*2, h=10, center=true, $fn=32);

        translate([0, 0, -(tubeRadius + wallWidth + outerWallThick - 0.5)])
          cylinder(r=boltHoleRadius*2, h=10, center=true, $fn=32);
      }
}

module body() {
  intersection() {
    difference() {
      union() {
        cylinder(h=hiltHeight, r=tubeRadius, $fn=360);
        cylinder(h=tubeLipHeight, r=tubeRadius+tubeLip, $fn=360);
        outerBody();
      }

      translate([0, 0, floorThickness])
        cylinder(h=hiltHeight, r=tubeRadius - wallWidth, center=false, $fn=360);
    }
    cylinder(h=hiltHeight, r=tubeRadius*1.4, $fn=360);
  }
}

module outerBody() {
  difference() {
    cylinder(r=tubeRadius + outerWallThick, h=100, $fn=360);
    cylinder(r=tubeRadius + wallWidth, h=100, $fn=360);
  }
}


module hcCube(w, l, h) {
  translate([-w/2, -l/2, 0])
    cube([w, l, h]);
}
