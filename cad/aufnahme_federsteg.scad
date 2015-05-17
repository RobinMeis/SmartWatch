//Getestet und funktionsfähig
//TODO: Abstand der Nasen sollte vor Verwendung vergrößert werden

$fn = 180;

difference() {
    cube([24,10,5], center=true);
    translate([0,2.5,0]) cube([18,5,5], center=true);
    translate([10,2.5,0]) rotate([0,90,0]) cylinder(r=0.5, h=2, center=true);
    translate([-10,2.5,0]) rotate([0,90,0]) cylinder(r=0.5, h=2, center=true);
}