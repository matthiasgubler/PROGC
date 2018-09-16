# Selbststudium 05: Verkette Liste
_Matthias Gubler (gublema6) & Daniele Colombo (colomdan)_

Nach dem Kompilieren kann das Modul via ./sst05-verketteteliste aufgerufen werden. Mit dem Modul können Personen in einer Liste verwaltet werden (Erfassen, Anschauen, Löschen und Filtern). Nach dem Start frägt das Modul die gewünsche Funktion ab:

|Funktion|Buchstabe|Beschreibung|
|--------|---------|------------|
|Insert  |I        |Einfügen einer neuen Person mit Name, Vorname, Alter|
|Remove  |R        |Löschen einer Person anhand von Name, Vorname, Alter|
|Show    |S        |Anzeigen aller Personen in einer sortierten Liste nach Name, Vorname, Alter|
|Filter  |F        |Anzeigen der Personen anhand eines Suchkriteriums für Name oder Vorname|
|Clear   |C        |Löschen aller erfassten Personen|
|End     |E        |Beenden des Programms|

*Achtung: Die Daten werden nur um Memory gespeichert und sind nicht persistent/verschwinden nach der Beendigung des Programms*


## Issues
Alle Sonderzeichen mussten für die Unittests angepasst werden (z.B. ä = ae), da die Tests sonst failen