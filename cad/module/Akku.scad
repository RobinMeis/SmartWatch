translate([0,0,-10])
color("blue")cube([42,36,4], true);
//Akku

$fn=100;

minkowski() {
    color("Blue", 1) cube([23,23.4,1], center=true);
    cylinder(r=2,h=0.01, center=true);
}
color("Grey", 1) translate([0,0,0.9]) cube([27,19.5,0.8], center=true);
//Bildschirm
translate([0,0,-5]) color("red")
cube([40,35,10], true)

translate([10,10,10])rotate([0,180,0])difference() {
    cube([10,10,2.5], center=true);
    translate([0,0,0.1]) 
    cube([7,8,2.5], center=true);
}//Taster