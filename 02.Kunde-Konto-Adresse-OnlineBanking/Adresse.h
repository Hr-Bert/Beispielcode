#pragma once

#include <string>

class Adresse
{
private:
	std::string plz;
	std::string ort;
	std::string strasse;

public:
	Adresse();
	Adresse(std::string extPlz, std::string extOrt, std::string extStrasse);

	void setPlz(std::string plzAlt, std::string plzNeu);
	void setOrt(std::string ortAlt, std::string ortNeu);
	void setStrasse(std::string strasseAlt, std::string strasseNeu);
	std::string getPlz();
	std::string getOrt();
	std::string getStrasse();

	~Adresse();
};

