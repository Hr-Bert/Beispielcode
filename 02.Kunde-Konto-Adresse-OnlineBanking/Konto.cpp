#include "Konto.h"

int Konto::anzahlKonten = 0;

Konto::Konto()
{
	anzahlKonten++;
	kontostand = 0.0;
	kontoNr = std::to_string(100000 + anzahlKonten);
}

// void Konto::setKontoNr(std::string kontoNrAlt, std::string kontoNrNeu) {	if (kontoNrAlt == kontoNr) kontoNr = kontoNrNeu;	}

void Konto::einzahlen(double betrag) {	 if (betrag) kontostand += betrag;	 }

bool Konto::auszahlen(double betrag, std::string extKontoNr) 
{
	if (extKontoNr == kontoNr)
	{
		if(betrag > 0) kontostand -= betrag;
		if(betrag < 0) kontostand += betrag;
		return true;
	}
	return false;
}

double Konto::getKontostand() { return kontostand;	}

std::string Konto::getKontonummer() { return kontoNr; }

Konto::~Konto() { anzahlKonten--; }