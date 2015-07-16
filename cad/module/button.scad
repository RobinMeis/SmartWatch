module button() {
    color("red") difference() {
        union() {
            cube([9,8,2], center=true);
            translate([0,0,-1]) cube([10,9,1], center=true);
        }
        translate([0,0,-0.8]) cube([8,7,3], center=true);
    }
}
rotate([180,0,0]) button();