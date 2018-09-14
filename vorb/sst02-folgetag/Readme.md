# Selbststudium 02: Berechnen des Folgetages
_Matthias Gubler (gublema6) & Daniele Colombo (colomdan)_

Nach dem Kompilieren kann das Modul via ./sst02-folgetag aufgerufen werden und frägt zur Laufzeit die Parameter ab, welche mit Enter bestätigt werden können.
Das Modul rechnet zu einem Datum jeweils einen Tag hinzu (default). Die Anzahl Tage welche hinzu oder abgezogen werden können jedoch übersteuert werden

Der Input wird wie folgt eingeben:
DD MM YYYY [Days To Add]
DD = Tage
MM = Monat
YYYY = Jahr

## Beispiel Input
| Input        | Resultat           | Bemerkung  |
| ------------- |-------------| -----|
| 12 01 1993      | 13.01.1993 | |
| 12 01 1993 5      | 17.01.1993      |   5 Tage werden aufgerechnet |
| 12 01 1993 -1 | 11.01.1993      |    Ein Tag wird abgezogen |
¡