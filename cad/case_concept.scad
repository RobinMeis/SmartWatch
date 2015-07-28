$fn=180;
$preview=false;

use<module/electronics.scad>
use<module/button.scad>
use<module/oled.scad>
use<module/charger.scad>

module armband() {
    minkowski() {
        difference() {
            cube([30,5.5,5], center=true);
            cube([28,4,6], center=true);
        }
        sphere(r=0.5);
    }
}

module main_body() {
    difference() {
        minkowski() {
            cube([44.4,40.4,10], center=true);
            sphere(r=2, center=true);
            rotate([0,90,0]) cylinder(r=2, center=true);
        }
        translate([0,0,1]) cube([44.4,38.4,15], center=true); //Inner space
        translate([0,0,10]) cube([43.2,37.2,10], center=true);
        translate([0,17,0]) cube([32,10,15], center=true);
    }
    
    difference() {
        cube([44.4,40.4,15], center=true);
        translate([0,0,0.1]) cube([40.8,34.8,15], center=true);
        translate([0,0,0.1])  cube([44.4,40.4,14], center=true);
    }
    
    if ($preview) {
        translate([0,7.3,5.8]) oled();
        
        translate([-11,-12,8.1]) button(); //Buttons
        translate([0,-12,8.1])     button();
        translate([11,-12,8.1])  button();
        
        translate([0,0,8])color("grey", 0.5) cube([43.2,37.2,2], center=true); //Glass
    }
}

module unibody() {
    difference() {
        union() {
            difference() {
                main_body();
                translate([0,0,-8]) cube([50,50,5], center=true);
                translate([20,21,-1]) cylinder(h=10,d=2.1, center=true);
                translate([-20,21,-1]) cylinder(h=10,d=2.1, center=true);
                translate([20,-21,-1]) cylinder(h=10,d=2.1, center=true);
                translate([-20,-21,-1]) cylinder(h=10,d=2.1, center=true);
            }
            
            translate([0,-25.5,-2.5]) armband();
            translate([0,25.5,-2.5]) armband();
        }
    translate([3.5,20,-2.5]) rotate([90,0,0]) cylinder(r=0.7,h=20, center=true); //Holes cables
    translate([-3.5,20,-2.5]) rotate([90,0,0]) cylinder(r=0.7,h=20, center=true);
    }
}

module backplate() {
    difference() {
        intersection() {
            main_body();
            translate([0,0,-8]) cube([50,50,5], center=true);
        }
        translate([20,21,-7]) cylinder(h=5,d=2.3, center=true);
        translate([-20,21,-7]) cylinder(h=5,d=2.3, center=true);
        translate([20,-21,-7]) cylinder(h=5,d=2.3, center=true);
        translate([-20,-21,-7]) cylinder(h=5,d=2.3, center=true);
        
        translate([20,21,-10]) cylinder(h=5,d=3.8, center=true);
        translate([-20,21,-10]) cylinder(h=5,d=3.8, center=true);
        translate([20,-21,-10]) cylinder(h=5,d=3.8, center=true);
        translate([-20,-21,-10]) cylinder(h=5,d=3.8, center=true);
    }
}

rotate([0,0,$t*360]) union() {
    if ($preview) {
        translate([0,0,38]) electronics();
        translate([0,0,25]) charger();
        translate([0,0,70]) unibody(); //Z=30
        translate([0,0,40]) translate([0,0,-10]) backplate();
    } else {
        rotate([180,0,0]) unibody();
        translate([0,0,-10]) backplate();
    }
}