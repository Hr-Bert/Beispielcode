#include "Kunde.h"

// Kunde::Kunde() { }
Kunde::Kunde(std::string extName, Adresse* extAdr)
{
	name = extName;

	meineKonten.push_back(new Konto{});
	
	if (extAdr != nullptr) meineAdresse = extAdr;
	else std::cout << "\nEs muss eine Adresse angegeben werden!\n";

	meinOnlineZugang = nullptr;
}
Kunde::Kunde(std::string extName, Adresse* extAdr, Onlinebanking* extOnline)
{
	name = extName;

	meineKonten.push_back(new Konto{});

	if (extAdr != nullptr) meineAdresse = extAdr;
	else std::cout << "\nEs muss eine Adresse angegeben werden!\n";

	if (extOnline != nullptr) meinOnlineZugang = extOnline;
	else std::cout << "\nNullpointer sind unzulässig, es muss ein Onlinezugang angegeben werden!\n";
}

void Kunde::setName(std::string extName)
{
	name = extName;
}
void Kunde::setMeineAdresse(Adresse* extAdr)
{
	meineAdresse = extAdr;
}
void Kunde::setOnlinebanking(Onlinebanking* extOnline)
{
	meinOnlineZugang = extOnline;
}
void Kunde::hinzufuegenKonto()
{
	meineKonten.push_back(new Konto{});
}
void Kunde::einzahlenMeinKonto(std::string extKontonummer, double betrag)
{
	for (auto curs = meineKonten.begin(); curs != meineKonten.end(); curs++)
	{
		if ((*curs)->getKontonummer() == extKontonummer) (*curs)->einzahlen(betrag);
	}
}

std::list<Konto*> Kunde::getMeineKonten()
{
	return meineKonten;
}
Adresse* Kunde::getMeineAdresse()
{
	return meineAdresse;
}
Onlinebanking* Kunde::getMeinOnlineZugang()
{
	return meinOnlineZugang;
}
bool Kunde::auzahlenMeinKonto(std::string extKontonummer, double betrag)
{
	for (auto curs = meineKonten.begin(); curs != meineKonten.end(); curs++)
	{
		if (((*curs)->getKontonummer() == extKontonummer) && ((*curs)->getKontostand() >= betrag))
		{
			(*curs)->auszahlen(betrag, extKontonummer);
			return true;
		}
	}
	return false;
}

void Kunde::anzeige()
{
	system("cls");
	std::cout << "Name:    " << name << '\n';
	std::cout << "PLZ:     " << (this->getMeineAdresse())->getPlz() << '\n';
	std::cout << "Ort:     " << (this->getMeineAdresse())->getOrt() << '\n';
	std::cout << "Stra\xE1\e:  " << (this->getMeineAdresse())->getStrasse() << '\n';

	if (this->getMeinOnlineZugang() != nullptr)  // Wenn Onlinezugang vorhanden
	{
		std::cout << "\nBenutzername: " << (this->getMeinOnlineZugang())->getBenutzername()
				  << "\nPasswort:     " << (this->getMeinOnlineZugang())->getPasswort() << '\n';
	}
	else
	{
		std::cout << "\n(Noch) kein Onlinezugang vorhanden.\n";
	}

	int i = 0;
	for (auto curs = meineKonten.begin(); curs != meineKonten.end(); curs++)
	{
		std::cout << "\nKonto " << i + 1 << ':' << '\n'
				  << (*curs)->getKontostand() << " Euro" /*(unsigned char)128*/;
		i++;
		std::cout << "\n----------------------\n\n";
	}

	std::cout << "Dr\x81\cken Sie Enter.";
	std::cin.get();
}

Kunde::~Kunde()
{
	for (auto curs = meineKonten.begin(); curs != meineKonten.end(); curs++)
	{
		delete *curs;    // Löschen der Inhalte der Pointer aus der Kontenliste
	}
	meineKonten.clear(); // Löschen der Pointer, falls ein Kunde gelöscht wird
}