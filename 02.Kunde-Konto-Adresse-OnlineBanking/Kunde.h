#pragma once

#include <string>
#include <iostream>
#include <list>
#include "Konto.h"
#include "Adresse.h"
#include "Onlinebanking.h"


class Kunde
{
private:
	std::string name;
	std::list<Konto*> meineKonten;
	Adresse* meineAdresse;
	Onlinebanking* meinOnlineZugang;

public:
	// Kunde();
	Kunde(std::string extName, Adresse* extAdr);                             // Konstruktoren
	Kunde(std::string extName, Adresse* extAdr, Onlinebanking* extOnline);

	void setName(std::string extName);
	void setMeineAdresse(Adresse* extAdr);          // setter
	void setOnlinebanking(Onlinebanking* extOnline);
	void hinzufuegenKonto();
	void einzahlenMeinKonto(std::string extKontonummer, double betrag);

	std::string getName();
	std::list<Konto*> getMeineKonten();
	Adresse* getMeineAdresse();             // getter
	Onlinebanking* getMeinOnlineZugang();
	bool auzahlenMeinKonto(std::string extKontonummer, double betrag);

	void anzeige();

	~Kunde();  // Destruktor
};

