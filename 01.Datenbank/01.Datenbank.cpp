// Dieses Projekt stammt wie einige andere noch aus der E-Phase und wurde daher nicht objektorientiert programmiert

#include <iostream>     
#include <fstream>  // nötige Bibliothek um Dateien außerhalb des Arbeitsspeichers abzuspeichern
#include <conio.h>     // benötigt für die Eingabe eines chars ohne Enter
#include <Windows.h>  // benötigt unter anderem für Sleep()
#include <string>    // benötigt für einige String Funktionen 
using namespace std;


struct daten
{
	char anfangsbuchstabe = '\0';
	string name;         // komplexer Datentyp zum einspeichern eines Nahrungsmittels 
	int artikelnmr = 0;
	double preis = 0.0;
	char geschmack[20] = { 0 };
};


void Txt(int*, daten*);               // Abspeichern in eine .txt Datei
void Csv(int*, daten*);              // Abspeichern in eine .csv Datei  
void Bin(int*, daten*);             // Abspeichern in eine Binärdatei
void binSuche(daten*, string*);    // Ausgabe bestimmter Binärdatensätze
void binLoesch(daten*, string*);  // Löschen eines Datensatzes
void einlesen(daten*);           // Liest gewünschte Daten in die Struktur "Daten" ein & fragt nach gewünschtem Dateiformat zum abspeichern
void ausgabe(daten*);           // Liest Daten aus der Datei in die Struktur ein
int menu(daten*);              // Blendet das Standard-Menu ein
void ausgabeStruktur(daten*); // Ausgabe der Struktur nach dem Einlesen


int main(daten* db)
{
	daten essen[100] = { 0 };    // 100 Datensätze für Gerichte erstellen

	system("color 20");  // Farben der Konsole (2 = Hintergrund -> grün | 0 = Vordergrund (Schrift) -> schwarz
	system("mode 170, 40"); // Größe der Konsole einstellen

	menu(essen);  // Startmenu  --> alles Weitere wird von hier aus weitergeleitet
		
	return 0;
}

int menu(daten* db)

{
	system("cls");
	char ausw = '\0';

	for(int i = 0; i < 1; i++)
	{ 
		system("cls");

	cout << "\t------------------------------------\n";
	cout << "\t\tW\x84hle eine Option:\n\n";
	cout << "\t\tDateneingabe:     [1]\n";
	cout << "\t\tDatenausgabe:     [2]\n";
	cout << "\t\tProgramm beenden: [3]\n";
	/*cout << "\t\tDaten \x84ndern:     [4]\n";*/
	cout << "\t------------------------------------\n";

	ausw = _getch();

		if (ausw < '1' || ausw > '3')				// Wenn eine Zahl außerhalb der Möglichen Optionen gewählt wurde wird darauf hingewiesen
		{
		system("cls");
		cout << "Ung\x81ltige Eingabe! Bitte w\x84hle erneut eine der Optionen.\n\n";
		_getch();                                  // Warnung ignorieren, das _getch() dient nur als Pause und soll das Programm stoppen bis eine Eingabe erfolgt
		i--;
		}
	}

	switch (ausw)
	{
	case '1':
		einlesen(db); // Weiterleitung zur Eingabe
	break;
	case '2': 
		ausgabe(db); // Weiterleitung zur Ausgabe der gewünschten Daten
	break;
	case '3': 
		system("cls");
		exit(0);   // erzwingt Beenden des Programs 
	break;
	/*case 4:
		break;*/
	default: cout << "Das sollte nicht passieren...";
	}
}

void Txt(int* anzDS, daten* db)
{
    system("cls");

	string dateiname;
	cout << "Wie soll die Datei hei\xE1 \ben? (Ohne Format): ";
	getline(cin >> ws, dateiname);
	dateiname = dateiname + ".txt";
	
	ofstream datei;                          // Datei öffnen
    datei.open(dateiname, ios::out);

	datei << "Gericht," << "\t" << "Geschmack," << "\t" << "Preis," << "\t" << "Artikelnummer," << "\t" << "Anfangsbuchstabe" << "\n";  // Standard Kopf der Textdatei

	for (int i = 0; i < *anzDS; i++) // Schleife zum Einlesen der Variablen  in die Datei
	{
		datei  << db[i].name << '\t' << db[i].geschmack << '\t' << db[i].preis << '\t' << db[i].artikelnmr << '\t' << db[i].anfangsbuchstabe << '\n';
	}
    datei.close();

	system("cls");
	cout << "Datei gespeichert.";
	Sleep(3000);

	menu(db);
}

void Csv(int* anzDS, daten* db)
{
	system("cls");

	string dateiname;
	cout << "Wie soll die Datei hei\xE1 \ben? (Ohne Format): ";
	getline(cin >> ws, dateiname);
	dateiname = dateiname + ".csv";


	ofstream datei;
	datei.open(dateiname, ios::out);

	datei << "Gericht;Geschmack;Preis;Artikelnummer;Anfangsbuchstabe\n";  // Tabellenkopf ausfüllen
	
	for (int i = 0; i < *anzDS; i++)
	{
		datei << db[i].name << ';' << db[i].geschmack << ';' << db[i].preis << ';' << db[i].artikelnmr << ';' << db[i].anfangsbuchstabe << '\n';
	}
    datei.close();

	system("cls");
	cout << "Datei gespeichert.";
	Sleep(3000);

	menu(db);
}

void Bin(int* anzDS, daten* db)
{
    system("cls");
	
	string dateiname;
	cout << "Wie soll die Datei hei\xE1 \ben? (Ohne Format): ";
	getline(cin >> ws, dateiname);
	dateiname = dateiname + ".dat";

	
	ofstream datei;
	datei.open(dateiname, ios::binary | ios::out);  // Öffne die Datei für Binären output

	datei.write((char*)db, sizeof(daten) * *anzDS);  // schreibe in char-Schritten die Größe eines Datensatzes x Anzahl der Datensätze
	
	datei.close();

	
	system("cls");
	cout << "Datei gespeichert.";
	Sleep(3000);

	menu(db);
}

void binSuche(daten* db, string* filename)
{
	system("cls");

	cout << "Binaer Suchfunktion :D\n\n";
	system("pause");

	menu(db);
}

void binLoesch(daten* db, string* filename)  // Ist noch nicht 100% fertig daher vorübergehend auskommentiert
{
	system("cls");
    
	cout << "Binaer Loeschfunktion (Ist noch in Arbeit) :D\n\n";
	cin.get();

	cout << "Den wievielten Datensatz moechten sie loeschen? ";
	string dss;      // Datensatz-String
	cin >> dss;               

	if (dss == "alle") // Wenn alle Datensätze gelöscht werden sollen
	{
		ofstream loeschen;
		loeschen.open(*filename, ios::binary | ios::out | ios::trunc); // ios::trunc löscht den ganzen ihnalt der Datei
		loeschen.close();
	}
	else
	{
		int ds = stoi(dss) - 1; // Datensatz = Datensatzstring - 1 (Wegen des Index)

		ofstream loeschen;
		loeschen.open(*filename, ios::binary | ios::out);  // Binäre Datei mit angegebenem Namen für Output öffnen

		loeschen.seekp(ds * sizeof(daten), ios::beg);   // Lege den Dateizeiger auf n * die größe eines Datensatzes vom Beginn der Datei

		char leer[sizeof(db[ds])] = { 0 };            // Erstelle leeren char array von der Größe eines Datensatzes

		loeschen.write((char*)leer, sizeof(db[ds]));  // Lese den leeren char array (Binäre Nullen) an Stelle des Datensatzes ins Programm ein

		loeschen.close();
	}

	menu(db);
}

void einlesen(daten* db)
{
	string jon;   // String ja oder nein (Zur Abfrage)

	int anzDS = 0;  // Anzahl Datensätze (zählt beim Einleen mit)

	for (int i = 0; i < 100; i++) // Einlesen der Variablen in die Struktur
	{
		system("cls");

		cout << "\n\tEingabe:\n";
		cout << " __________________________\n\n";

		cout << "Gericht: ";
		getline(cin >> ws, db[i].name);   // getline + cin >> ws  um Fehler bei der Eingabe von Leerzeichen zu verhindern

		cout << "\nGeschmack: ";
		cin.getline(db[i].geschmack, sizeof(db[i].geschmack));        // cin.getline um den char array aufzunehmen

		cout << "\nPreis: ";
		cin >> db[i].preis;

		cout << "\nArtikelnummer: "; 
		cin >> db[i].artikelnmr;

		cout << "\nAnfangsbuchstabe: ";
		cin >> db[i].anfangsbuchstabe;

		anzDS++;
		system("cls");

		cout << "Wollen sie einen weiteren Datensatz einlesen? ";
		cin >> jon;

		if (jon[0] == 'N' || jon[0] == 'n')
		{
			i = 100;
		}
	} 
	

		char auswahl = 0;
		for (int i = 0; i < 1; i++)         // Schleife zur Auswahl der Formatoption
		{
			system("cls");

			cout << "   In welchem Format wollen sie speichern?\n\n";
			cout << "\t--------------------------\n";
			cout << "\t\t.txt  [1]\n";
			cout << "\t\t.csv  [2]\n";                                 // Ausgabe der möglichen Formatoptionen
			cout << "\t\tBin\x84r [3]\n";
			cout << "\t--------------------------\n";

			auswahl = _getch();                          // Eingabe der Option, ohne Notwendigkeit Enter zu drücken
                               
			if (auswahl < '1' || auswahl > '3')
			{
				system("cls");
				cout << "Ung\x81ltige Auswahl! Bitte versuche es erneut.";
				cin.get();
				i--;
			}
		}

		switch (auswahl)
		{
		case '1': Txt(&anzDS, db);
			break;
		case '2': Csv(&anzDS, db);
			break;
		case '3': Bin(&anzDS, db);
			break;
		default: cout << "Das Programm ist Scheisse!!!";
		}

}

void ausgabe(daten* db)
{
	system("cls");
    string dateiname;
	string tempstr;
	ifstream vorhdt;

	for (int i = 0; i < 1; i++)
	{
		system("cls");
		cout << "\n\tWelche Datei m\x94 \bchten sie ausgeben lassen? [Dateiname]:\n";
		cout << " ______________________________________________________________________\n\n";
		getline(cin >> ws, dateiname);

		vorhdt.open(dateiname, ios::in);

		if (!vorhdt)  // Fehlermeldung, falls die Datei nicht gefunden wird
		{
			bool leerzeichen = false;
			for (int j = 0; dateiname[j] != '\0'; j++) { if (dateiname[j] == ' ') { leerzeichen = true; } } // Auf eingegebene Leerzeiche prüfen
			
			if (leerzeichen) { cout << "\nSie d\x81rfen keine Leerzeichen eingeben!\n\n\n\n"; }

			else { cout << "\nDatei nicht gefunden, bitte \x81 \bberpr\x81 \bfe den Namen!\n\n\n\n"; }
			
			system("pause");
			i--;
		}
	}

	if(dateiname[dateiname.length() - 2] == 'x')   // Wenn Anzahl der Buchstaben - 2 (2. letzer Index) ein x ist (.txt) dann --> Ausgabe txt
		{
			system("cls");
			int count = 0;
			
			while (true)   // Einlesen der txt-Datei in die Struktur und anschließende Ausgabe
			{
			if (count == 0) { getline(vorhdt, tempstr, '\n'); }   // In der ersten Runde wird der Tabellenkopf "überlesen" damit es keine Probleme beim casten der Datentypen gibt

			getline(vorhdt, db[count].name, '\t');   // Vorhandene Datei wird bis zum nächsten Tabulator in den temporären String gespeichert und anschließend ausgegeben
			if (vorhdt.eof()) { break; }

			getline(vorhdt, tempstr, '\t');
			strcpy_s(db[count].geschmack, tempstr.c_str());

			getline(vorhdt, tempstr, '\t');
			db[count].preis = stod(tempstr);
			
			getline(vorhdt, tempstr, '\t');
			db[count].artikelnmr = stoi(tempstr);
			
			getline(vorhdt, tempstr, '\n');
			db[count].anfangsbuchstabe = tempstr[0];

			count++;
			}
			vorhdt.close();
			ausgabeStruktur(db);
		}

	else if (dateiname.back() == 'v')   // Ausgabe einer csv-Datei / Tabelle
		{
			system("cls");
			int ct = 0;
			
			while (true)   // Einlesen der CSV-Datei in die Struktur und anschließende Ausgabe
			{
				if (ct == 0) { getline(vorhdt, tempstr, '\n'); } // Kopfzeile missachten um keine Probleme beim Caasten zu bekommen
				
				getline(vorhdt, tempstr, ';'); 
				if (vorhdt.eof()) { break; }   
				db[ct].name = tempstr;              
				
				getline(vorhdt, tempstr, ';');
				strcpy_s(db[ct].geschmack, tempstr.c_str());    // Funktion um die temporäre string in einen char-Array zu übertragen
				
				getline(vorhdt, tempstr, ';');
				db[ct].preis = stod(tempstr);

				getline(vorhdt, tempstr, ';');
				db[ct].artikelnmr = stoi(tempstr);

				getline(vorhdt, tempstr, '\n');
				db[ct].anfangsbuchstabe = tempstr[0];
	
				ct++;
			}
			
			vorhdt.close();
			ausgabeStruktur(db);
		}

	else                               // Ausgabe einer Binär-Datei
	{
		system("cls");
		vorhdt.close();          // Datei wurde oben nicht als Binäre Datei geöffnet, daher schließe ich sie im Fall einer Binären Datei um sie neu zu öffnen

		char auswahl = '\0';

		for (int i = 0; i < 1; i++)         // Weitere Optionen zu Binärdateien
		{
			system("cls");

			cout << "\n -------------------------------\n";
			cout << "  Nach einem Wort suchen:   [1] \n";
			cout << "  Einen Datensatz l\x94schen:  [2] \n";
			cout << "  Einen Datensatz ausgeben: [3] \n";
			cout << "  Alle Datens\x84tze ausgeben: [4] \n";
			cout << " -------------------------------\n";

			auswahl = _getch();

			if (auswahl > '4' || auswahl < '1')    // Falsche Auswahlen aussortieren + Fehlermeldung
			{
				system("cls");
				cout << "Ung\x81ltige Eingabe! Versuche es erneut.";
				cin.get();
				i--;
			}
		}


		if (auswahl == '1') { binSuche(db, &dateiname); }

		else if (auswahl == '2') { binLoesch(db, &dateiname); }

		else
		{
			system("cls");


			vorhdt.open(dateiname, ios::binary | ios::in); // öffne die Datei für Binären input

			vorhdt.read((char*)db, sizeof(daten) * 100);  // lese 100 x die Größe eines Datensatzes byteweise in die Variable db

			vorhdt.close();  // Datei nach dem Einlesen wieder schließen


			if (auswahl == '4') { ausgabeStruktur(db);  } // Wenn alles Ausgeben ausgewählt wurde
			
			else
			{
				int datensatz = 0;

				for (int i = 0; i < 1; i++)
				{
					system("cls");
					cout << "Welchen Datensatz wollen Sie ausgeben lassen? ";
					cin >> datensatz;

					if (db[datensatz - 1].name[0] == '\0' || datensatz > 99)  // Wenn der Name des Gerichts in der ausgewählten Datei nicht beschrieben ist
					{
						cout << "\n\n Dieser Datensatz ist leer, w\x84hle einen anderen aus.\n\n";  // Fehlermeldung
						cin.get();
						i--;
					}
					else
					{
						system("cls");
						cout << datensatz << ". Datensatz\n";
						cout << "__________________________\n";
						cout << "Gericht:          " << db[datensatz - 1].name;
						cout << "\nGeschmack:        " << db[datensatz - 1].geschmack;
						cout << "\nPreis:            " << db[datensatz - 1].preis;
						cout << "\nArtikelnummer:    " << db[datensatz - 1].artikelnmr;
						cout << "\nAnfangsbuchstabe: " << db[datensatz - 1].anfangsbuchstabe << "\n\n";
						cout << "Wollen Sie einen weiteren Datensatz auslesen? [j/n]\n";
						char weiter = _getch();

						if (weiter == 'j' || weiter == 'J') { i--; }
						else
						{
							system("pause");
							// menu(db);
						}
					}
				}
			}
		}
	}  
}

void ausgabeStruktur(daten* db)
{
	system("cls");

	for (int i = 0; i < 100; i++)  // Ausgabe der Struktur bis alle Datensätze ausgegeben wurden
	{
		if (db[i].name[0] == '\0') // Abbruch der Ausgabe, wenn der Name nicht gefüllt ist (Der Datensatz leer ist)
		{
			break;
		}
		cout << i + 1 << ". Datensatz: \n";
		cout << "__________________________\n";
		cout << "Gericht:          " << db[i].name;
		cout << "\nGeschmack:        " << db[i].geschmack;
		cout << "\nPreis:            " << db[i].preis;
		cout << "\nArtikelnummer:    " << db[i].artikelnmr;
		cout << "\nAnfangsbuchstabe: " << db[i].anfangsbuchstabe << "\n\n\n";
	}

	system("pause");
	menu(db);
}
