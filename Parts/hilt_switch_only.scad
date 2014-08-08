hiltHeight     = 40;
wallWidth      = 2.25;
tubeRadius     = 20.9;
tubeLip        = 4;
taper          = 25;
floorThickness = 2;

switchWidth    = 14.5;
switchLength   = 9;
switchDepth    = 13.5;
switchOffset   = 10.5;

pcbWidth       = 39;
pcbHeight      = 44.25;
pcbDepth       = 10;
pcbHoleHeight  = 39;
pcbHoleOffset  = 14;

usbWidth       = 25;
usbHeight      = 5.5;

difference() {
  body();
  switchHole();
  pcb();
}

module pcb() {
  union() {
    translate([0, 0, floorThickness])
      hcCube(pcbWidth, pcbDepth, pcbHeight);

    translate([-usbWidth/2, pcbDepth/2, 0])
      cube([usbWidth, usbHeight, floorThickness+1]);
  }
}

module switchHole() {
  translate([0, -switchOffset, -1])
    hcCube(switchWidth, switchLength, switchDepth+2);

}

module bodyBounds() {
  cylinder(h=hiltHeight, r=tubeRadius, $fn=360);
}

module body() {
  intersection() {
    difference() {
      union() {
        bodyBounds();
        cylinder(h=tubeLip, r=tubeRadius+tubeLip, $fn=360);
      }

      translate([0, 0, floorThickness])
        cylinder(h=hiltHeight, r=tubeRadius - wallWidth, center=false, $fn=360);
    }
    union() {
      translate([0, 0, hiltHeight - taper])
        cylinder(h=taper, r1=tubeRadius*1.4, r2=tubeRadius-wallWidth*.75, center=false, $fn=360);

        cylinder(h=hiltHeight-taper, r=tubeRadius*1.4, $fn=360);
    }
  }
}


module hcCube(w, l, h) {
  translate([-w/2, -l/2, 0])
    cube([w, l, h]);
}
