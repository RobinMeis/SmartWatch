$fn=180;

module armband() {
    minkowski() {
        difference() {
            cube([29.5,4.5,4.5], center=true);
            cube([27.5,3.5,5], center=true);
        }
        sphere(r=0.5);
    }
}

module usb_connector() {
    cube([16,13.1,5.7], center=true);
    translate([6.6,0,0]) cube([1,14.4,7.05], center=true);
    translate([-9.1,0,0]) cube([4,16,5.7], center=true);
}

module usb_difference() {
    minkowski() {
        usb_connector();
        cube(0.15, center=true);
    }
}

//translate([2,0,0]) color ("silver") usb_connector();

difference() {
    union() {
        minkowski() {
            cube([19.5,17.5,7], center=true);
            sphere(r=0.5);
        }
        translate([-11.5,0,-1.25]) rotate([0,0,90]) armband();
    }
    translate([2.2,0,0]) usb_difference();
}