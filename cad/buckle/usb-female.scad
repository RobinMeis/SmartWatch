$fn=45;

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
    minkowski() {
        cube([20.5,18.5,8], center=true);
    }
    translate([2.2,0,0]) usb_difference();
}