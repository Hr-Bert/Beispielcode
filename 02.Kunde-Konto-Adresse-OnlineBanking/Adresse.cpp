#include "Adresse.h"
//#include "Kunde.h"

Adresse::Adresse()
{
	plz = "12345";
	ort = "Musterstadt";
	strasse = "Musterstrasse";
}
Adresse::Adresse(std::string extPlz, std::string extOrt, std::string extStrasse)
{
	if (extPlz.length() < 6) plz = extPlz;
	else plz = "00000";
	ort = extOrt;
	strasse = extStrasse;
}

void Adresse::setPlz(std::string plzAlt, std::string plzNeu) { if (plzAlt == plz) plz = plzNeu; }
void Adresse::setOrt(std::string ortAlt, std::string ortNeu) { if (ortAlt == ort) ort = ortNeu; }
void Adresse::setStrasse(std::string strasseAlt, std::string strasseNeu) { if (strasseAlt == strasse) strasse = strasseNeu; }

std::string Adresse::getPlz() {	return plz; }
std::string Adresse::getOrt() { return ort; }
std::string Adresse::getStrasse() { return strasse; }

Adresse::~Adresse() { }
