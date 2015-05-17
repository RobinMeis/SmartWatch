//Getestet und funktionsfähig
//TODO: Toleranz ermitteln
//TODO: Ecken abrunden

/* Über aufnahme_federsteg(breite_armband, breite_nasen=3, toleranz=0)

breite_armband : Gibt die Breite des gewünschten Armband an und bestimmt somit den Abstand zwischen den beiden Nasen
breite_nasen    : Gibt die Breite der Nasen an, die den Federsteg halten (Standard 3mm)
toleranz         : Gibt einen Wert an, der zu der Breite des Armbands zu addieren ist

Alle Werte sind in mm anzugeben!

Beispielaufruf: aufnahme_federsteg(18, 3, 1);
*/

module aufnahme_federsteg (breite_armband, breite_nasen=3, toleranz=0) {
    difference() {
        cube([breite_armband + toleranz + (breite_nasen * 2),10,5], center=true);
        translate([0,2.5,0]) cube([breite_armband + toleranz,5,5], center=true);
        translate([(breite_armband / 2) + 1,2.5,0]) rotate([0,90,0]) cylinder(r=0.5, h=2, center=true);
        translate([-((breite_armband / 2) + 1),2.5,0]) rotate([0,90,0]) cylinder(r=0.5, h=2, center=true);
    }
}