difference() {
    cube([43.6,37.6,19.6], center=true);
    translate([0,0,0.1]) cube([42,36,19.6], center=true);
}
//Außenhülle
difference() {
   cube([43.6,37.6,17.6], center=true);
    translate([0,0,1.6]) cube([42,36,16,8], center=true);
    translate([0,0,0.1])
    cube([40.8,34.8,17.6], center=true);
}
//Auflagefläche Displaycover


