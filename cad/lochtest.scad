$fn=100;

difference() {
    cube([22,5,2], center=true);
    translate([-9,0,0]) cylinder(h=3,d=1.7, center=true);
    translate([-6,0,0]) cylinder(h=3,d=1.8, center=true);
    translate([-3,0,0]) cylinder(h=3,d=1.9, center=true);
    translate([0,0,0]) cylinder(h=3,d=2, center=true);
    
    translate([3,0,0]) cylinder(h=3,d=2.1, center=true);
    translate([6,0,0]) cylinder(h=3,d=2.2, center=true);
    translate([9,0,0]) cylinder(h=3,d=2.3, center=true);
}

