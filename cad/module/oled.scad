$fn=100;

minkowski() {
    color("Blue", 1) cube([23,23.4,1], center=true);
    cylinder(r=2,h=0.01, center=true);
}
color("Grey", 1) translate([0,0,0.9]) cube([27,19.5,0.8], center=true);