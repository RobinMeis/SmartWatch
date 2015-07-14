module button() {
    color("red") difference() {
        union() {
            cube([9,8,2], center=true);
            translate([0,0,-1]) cube([10,9,1], center=true);
        }
        translate([0,0,-0.6]) cube([8,7,3], center=true);
    }
}
button();