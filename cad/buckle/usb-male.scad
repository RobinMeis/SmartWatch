module armband() {
    minkowski() {
        difference() {
            cube([30,5,5], center=true);
            cube([28,4,6], center=true);
        }
        sphere(r=0.25);
    }
}
$fn=180;

module usb_plug() {
    cube([12,30,4.5], center=true); //Y=14.8
    translate([-5.44,-8.4,-0.6]) cube([1.2,2.5,5.7], center=true);
    translate([5.44,-8.4,-0.6]) cube([1.2,2.5,5.7], center=true);
    translate([3.5,-10,0]) rotate([90,0,0]) cylinder(r=0.7,h=15, center=true);
    translate([-3.5,-10,0]) rotate([90,0,0]) cylinder(r=0.7,h=15, center=true);
}

module usb_difference() {
    minkowski() {
        usb_plug();
        cube(0.15, center=true);
    }
}

//translate([0,9.5,0.5]) color("silver",0.5) usb_plug();
difference() {
    union() {
        color("red") minkowski() {
            cube([13.5,13.5,7], center=true);
            sphere(r=0.25);
        }
        translate([0,13,0]) cube([5,5,7.5], center=true);
        translate([0,-8.75,-1]) armband();
    }
    translate([0,9.5,0.5]) usb_difference();
    translate([0,13,5]) cube([6,6,7.5], center=true);
}