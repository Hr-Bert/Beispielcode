// HINWEIS: Um eine bestimmte Anforderung an das Programm zu erfüllen, wird das Programm gewollt mit einem Fehlercode beendet !!
#include "Kunde.h" 

using namespace std;

int main()  // main wurde zu Vorstellungszwecken mit Beispielwerten gefüllt um die Funktion zu demonstrieren
{
	Adresse ad1{ "34111", "Kassel", "Willi-Wills-Wissen-Strasse" }; // Adresse erstellen
	
	Kunde ku1{ "Dieter B.", &ad1 };  // Einer der Parameterkonstruktoren von Kunde wird aufgerufen

	ku1.anzeige();  // Methode die das meiste eines Kunden ausgibt (zu Debug und Kontrollierzwecken einzusetzen)

	ku1.einzahlenMeinKonto("100001", 299.99);   // 100001 ist die Kontonummer des ersten Kontos (fängt bei 100001 an und steigt um 1 bei jedem  zusätzlich generierten Konto)

	ku1.auzahlenMeinKonto("100001", 19.99);  

	ku1.setName("Peter B.");
															// Adresse und Namen verändern
	Adresse ad2{ "12345", "Fulda", "Rosarot-Strasse" };

	ku1.setMeineAdresse(&ad2);

	ku1.hinzufuegenKonto();

	ku1.einzahlenMeinKonto("100002", 17.97);   // einzahlen in das 2. Konto von Kunde 1

	ku1.einzahlenMeinKonto("100003", 9000.0);  // Fehler -> einzahlen in das 3. Konto von Kunde 1 (wurde noch nicht erstellt)

	ku1.anzeige();

	// ----------------------------------------------------------

	system("cls");
	cout << "Part 2 !!";
	cin.get();
	system("cls");

	// ----------------------------------------------------------

	Kunde* kun2 = new Kunde{ "Hans Peter", &ad2 };

	if (kun2->auzahlenMeinKonto("100003", 18.75))  // 18.75 Euro können nicht ausgezahlt werden, da das Konto beim Erstellen noch auf 0 Euro ist.
	{
		cout << "Das Geld wurde ausgezahlt!";	   // Das Auszahlen lässt sich mit einer if Bedingung überprüfen, da auszahlen eine bool-Funktion ist
	}
	else
		cout << "Fehler. Es ist nicht gen\x81gend Geld auf dem Konto!";

	cin.get();
	system("cls");

	kun2->einzahlenMeinKonto("100003", 50.01);

	Onlinebanking online;                // leerer Onlinezugang / Standardkonstruktor

	kun2->setOnlinebanking(&online);

	kun2->anzeige();

	online.setBenutzername("leer", "leer", "Hansi");  // (Passwort, alterBenutzername, neuerBenutzername)

	online.setPasswort("leer", "dasIstEinSehrLangesPasswort,WirdManGleichSehen");

	kun2->anzeige();

	// ---------------------------------------------------------------- 

	system("cls");
	std::cout << "Part 3 !! (Kunde 2 l\x94schen)";
	cin.get();
	system("cls");

	// -------------------------------------------------------------- 

	delete kun2;    //  Jetzt löschen wir den mit new erstellten Kunde

					// Adresse noch vorhanden, da diese in der main erstellt wurde 

	kun2->anzeige();  // Warnung gewollt. Wir greifen auf ein gelöschtes Objekt zu und wollen nur sehen ob die Konten noch bekannt sind, etc.

	return 0;
}