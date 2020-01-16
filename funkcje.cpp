#include <iostream>
#include <fstream>
#include <string>
#include <sys/types.h>
#include <vector>
#include <deque>
#include <iomanip>

#include "funkcje.h"
#include "struktury.h"
#include "dirent.h"
#include "nvwa/debug_new.h"


//listowanie Katalogu i dodawanie jej elementow do dynamicznej tablicy
void listowanieKatalogu(const char* sciezka, std::vector<std::string>& tablica) {  //tego nie ogarniam na tyle, zeby to dokladnie opisac
	struct dirent* entry;
	DIR* dir = opendir(sciezka);

	if (dir == NULL) {
		return;
	}
	while ((entry = readdir(dir)) != NULL) {
		tablica.push_back(entry->d_name);  //dodawanie elementow katalogu do dynamicznej tablicy
	}
	tablica.erase(tablica.begin()); //usuniecie tych 2 kropek, co nie wiadomo skad sie biora
	tablica.erase(tablica.begin());

	closedir(dir);
}

int zliczanieWierszy(std::string nazwaPliku) { //zliczanie wierszy w celu sprawdzenia ilu jest zawidkó, ¿eby dla kazdego wykonac petle i dodac do drzewa

	int liczbaWierszy = 0;  //poczatkowa wartosc
	std::string wiersz;
	std::ifstream plik(nazwaPliku);


	while (std::getline(plik, wiersz))
		++liczbaWierszy;
	return liczbaWierszy;
}		//w skopiowanym kodzie, nie by³o otwarica pliku, sprawdzania ani zamykania, upenic sie, czy tak moze byc

void zapiszWynik(std::string nazwaPliku, wynik& uczestnik, const int& numerWiersza) { //funkcja sluzaca do zapisania wyniku w strukturze

	std::ifstream plik;
	plik.open(nazwaPliku); //otwarcie pliku

	if (!plik) { //jesli plik sie nie otowrzy
		std::cout << "Blad pliku" << std::endl; //wyswietla blad pliku
		return;
	}

	std::string wiersz, nazwisko;
	if (numerWiersza == 0) {  //pierwsza linijka  <-> NAZWA WYDARZENIA
		getline(plik, uczestnik.nazwa); //przypisanie nazwy do struktury
	}
	else if (numerWiersza == 1) { //druga linijka <->  DATA WYDARZENIA
		getline(plik, uczestnik.data); //ominiecie przerwszej lini, bo zapisalaby sie znowu nazwa
		getline(plik, uczestnik.data); //przypisanie daty do struktury
	}
	else {
		for (int i = 0; i < numerWiersza; i++) //w zalezniosci od numeru wiersza, skipuje tyle wersow, zeby sie dostac do konkretnego
			getline(plik, wiersz);

		int found = wiersz.find(',');  //szukanie przecinka w celu oddzielenia od reszty ciagu
		if (found != std::string::npos) {  //jesli wynik nie jest rowny temu co wyskakuje, gdy nie znajdzie przecinka 
			&wiersz.erase(0, found + 2);  //wymazuje niepotrzebne miejsce na mecie
			found = wiersz.find(','); //znajduje kolejny przecinek, ktory wskazuje na nazwisko
			nazwisko = wiersz.substr(0, found); // przerabianie wiersza, w celu zdobycia nazwiska
			uczestnik.nazwisko = nazwisko; //przypisanie nazwiska do struktury

			found = wiersz.find_last_of(','); //szukanie ostatniego przecinka
			wiersz.erase(0, found + 2); // kasowanie zawartosci wiersza, w celu pozostawienia jedynie czasu
			uczestnik.czas = wiersz; //przypisanie czasu


		}
	}
}

	Node* FindRunner(Node * pRoot, wynik*& biegacz)
	{
		if (pRoot)
		{
			if (pRoot->result->nazwisko == biegacz->nazwisko)
				return pRoot;

			if (biegacz->nazwisko < pRoot->result->nazwisko)
				return FindRunner(pRoot->pLeft, biegacz);
			else
				return FindRunner(pRoot->pRight, biegacz);
		}
		else
			return nullptr;
	}

	void AddNode(Node * &pRoot, Node * node)
	{
		if (!pRoot)
			pRoot = node;
		else
		{
			if (node->result->nazwisko < pRoot->result->nazwisko)
				AddNode(pRoot->pLeft, node);
			else
				AddNode(pRoot->pRight, node);
		}
	}

	void AddToConnected(ConnectedListElement * &pHead, wynik * wynik)
	{
		pHead = new ConnectedListElement{ wynik, pHead };
	}

	void AddRunner(Node*& pRoot, wynik*& uczestnik)
	{
		auto runner = FindRunner(pRoot, uczestnik);

		//Je¿eli wêze³ z biegaczem nie istnieje, utwórz go.

		if (!runner)
		{
			runner = new Node{ uczestnik, nullptr };
			AddNode(pRoot, runner);
		}
		//Je¿eli istnieje dodaje kolejny wynik do listy
		AddToConnected(runner->result->ConnectedHead, uczestnik);
	}


	/////////////////////////////////////////////
	void wypiszZawodnika(Node* pRoot) {
		if (pRoot) {
			wypiszZawodnika(pRoot->pRight);
			wypiszZawodnika(pRoot->pLeft);
			zapisywanieDoPliku(pRoot->result);
		}
	}

	void zapisywanieDoPliku(ConnectedListElement* wynik) {
		std::ofstream plik;
		plik.open(wynik->wynik->nazwisko, std::ios_base::app);

		if (plik) {
			plik << wynik->wynik->data << " " << wynik->wynik->nazwa << " " << wynik->wynik->czas << std::endl;
			plik.close();
		}

		zapisywanieDoPliku(wynik->pNext);
		usunZListy(wynik);
		
	}

	void usunZListy(ConnectedListElement* wynik) {
		delete wynik;
	}


	void usunDrzewo(Node*& pRoot)
	{
		if (pRoot)
		{
			usunDrzewo(pRoot->pLeft);
			usunDrzewo(pRoot->pRight);
			delete pRoot;
			pRoot = 0;
		}
	}
	// 

