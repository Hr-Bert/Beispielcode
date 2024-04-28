#pragma once

#include <string>

class Konto
{
private:
	double kontostand;
	std::string kontoNr;
	static int anzahlKonten;

public:
	Konto();
	
	// void setKontoNr(std::string kontoNrAlt, std::string kontoNrNeu);
	void einzahlen(double betrag);
	bool auszahlen(double betrag, std::string extKontoNr);
	double getKontostand();
	std::string getKontonummer();

	~Konto();
};

