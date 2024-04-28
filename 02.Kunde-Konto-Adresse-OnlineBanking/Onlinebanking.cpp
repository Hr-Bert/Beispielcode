#include "Onlinebanking.h"

Onlinebanking::Onlinebanking()
{
	benutzername = "leer";
	passwort = "leer";
}
Onlinebanking::Onlinebanking(std::string extBenName, std::string extPasswort)
{
	if (extBenName.length() >= 3) benutzername = extBenName;
	else benutzername = "Max Mustermann"; 

	if (extPasswort.length() >= 5) passwort = extPasswort;
	else passwort = "abc123";
}

std::string Onlinebanking::getPasswort()
{
	std::string pwpx; // pwpx = Passwort pixel

	for (int i = passwort.size(); i > 0; i--) pwpx += '*';

	return pwpx;
}
std::string Onlinebanking::getBenutzername()
{
	return benutzername;
}

void Onlinebanking::setBenutzername(std::string extPasswort, std::string benutzernameAlt, std::string benutzernameNeu) 
{
	if ((extPasswort == passwort) && (benutzernameAlt == benutzername)) benutzername = benutzernameNeu;
}
void Onlinebanking::setPasswort(std::string passwortAlt, std::string passwortNeu) 
{ 
	if (passwortAlt == passwort) passwort = passwortNeu; 
}

Onlinebanking::~Onlinebanking() { }

