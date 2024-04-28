#pragma once

#include <string>

class Onlinebanking
{
private:
	std::string benutzername;
	std::string passwort;

public:
	Onlinebanking();
	Onlinebanking(std::string extBenName, std::string extPasswort);

	std::string getPasswort();
	std::string getBenutzername();

	void setBenutzername(std::string extPasswort, std::string benutzernameAlt, std::string benutzernameNeu);
	void setPasswort(std::string passwortAlt, std::string passwortNeu);

	~Onlinebanking();
};

