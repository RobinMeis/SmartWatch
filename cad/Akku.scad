//TODO: Datei sinnvoll umbennen

$fn=100; //Decrease to increase rendering speed

use <module/oled.scad>;
use <module/button.scad>;
use <module/battery.scad>;
use <module/arduino.scad>;
use <module/bluetooth.scad>;
use <module/charger.scad>;

//translate([10,10,10]) rotate([0,180,0]) button();
oled();

//translate([0,0,-5]) color("red",0.5) cube([40,35,10], true); //Electronics

translate([-9,0,-4]) arduino();
translate([9,0,-4]) bluetooth();
//translate([-10,10,6]) charger();

translate([0,0,-10]) battery();