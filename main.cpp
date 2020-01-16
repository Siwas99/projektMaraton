#include <iostream>
#include <fstream>
#include <string>
#include <sys/types.h>
#include <vector>

#include "funkcje.h"
#include "struktury.h"




int main() {
	std::vector<std::string> tablicaNazw; // zdeklarowanie puestej tablicy o zmiennym rozmiarze, do przechowywania nazw plikow

	wynik uczestnik; //zdeklarowanie zmiennej do któej wprowadzanie beda dane uczestnikow

	Node* pKorzen = nullptr;

	listowanieKatalogu("zawody", tablicaNazw);

	for (int i = 0; i < tablicaNazw.size(); i++) { //petla dla wszystkich elementow w katalogu
		std::string nazwaPliku("zawody/" + tablicaNazw[i]); //dopisanie do popranych nazw -> zawody/

		int liczbaWierszy = zliczanieWierszy(nazwaPliku);  //zliczenie wierszy w celu ustalenia jak wiele jest zawodnikow, aby dla kazdego z osobna wykonac petle i osobno dodac do drzewa

		for (int idUczestnika = 0; idUczestnika <= liczbaWierszy; idUczestnika++) { //petla do wypisania po kolei kazdego uczestnika
			zapiszWynik(nazwaPliku, uczestnik, idUczestnika); //funckja do tego co wyzej 

			if (idUczestnika > 2) {  //wypisanie dopiero od drugiej iteracji, bo w pierwszej jest nazwa, a w drugiej data
				
			}
		}
	}

	////////////////
	wypiszZawodnika(pKorzen);
	//
	//wypisz(pKorzen, 5);

	//jezeli jest dobrze to WYSTARCZY dodac listy w wezlach, posortowac i wypisywac listy do plikow lecac przez cale drzewo

	//trzeba przeleciec prez cale drzewo i dla kazdego wezla wypisac liste a potem ja usunac

	return 0;
}