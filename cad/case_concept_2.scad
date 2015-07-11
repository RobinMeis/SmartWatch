$fn=50;

use<module/electronics.scad>

//TODO: Materialdicke Schraubenlöcher prüfen

module armband() {
    minkowski() {
        difference() {
            cube([30,5,5], center=true);
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
        }
    difference() {
    cube([44.4,40.4,15], center=true);
        translate([0,0,0.1])
    cube([40.8,34.8,15], center=true);
        translate([0,0,0.1])
    cube([44.4,40.4,14], center=true);
    }
    translate([0,0,8])color("grey")cube([43.2,37.2,2], center=true);
}

module unibody() {
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
    translate([0,0,30]) unibody(); //Z=10
    translate([0,0,-10]) backplate();
    translate([0,0,15]) electronics();
}