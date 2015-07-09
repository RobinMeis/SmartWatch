//TODO: Datei sinnvoll umbennen

$fn=100; //Decrease to increase rendering speed

use <module/oled.scad>;
use <module/button.scad>;
use <module/battery.scad>;

translate([10,10,10]) rotate([0,180,0]) button();
oled();
translate([0,0,-10]) battery();
translate([0,0,-5]) color("red") cube([40,35,10], true); //Electronics