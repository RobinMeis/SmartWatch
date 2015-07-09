module button() {
    difference() {
        cube([10,10,2.5], center=true);
        translate([0,0,0.1]) cube([7,8,2.5], center=true);
    }
}