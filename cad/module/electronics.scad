use <oled.scad>;
use <button.scad>;
use <battery.scad>;
use <arduino.scad>;
use <bluetooth.scad>;
use <charger.scad>;

module electronics() {
    oled();
    translate([0,8,-4]) rotate([0,0,90]) arduino();
    translate([0,-10,-4]) rotate([0,0,90]) bluetooth();
    //translate([-10,10,6]) charger();
    translate([0,0,-10]) battery();
}

electronics();