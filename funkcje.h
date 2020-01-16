#include <iostream>
#include <string>
#include <cstring>

#include "struktury.h"


#ifndef FUNKCJE_H
#define FUNKCJE_H


void listowanieKatalogu(const char* sciezka, std::vector<std::string>& tablica);

int zliczanieWierszy(std::string nazwaPliku);

void zapiszWynik(std::string nazwaPliku, wynik& uczestnik, const int& numerWiersza);

Node* FindRunner(Node* pRoot, wynik *& biegacz);

void AddNode(Node*& pRoot, Node* node);

void AddToConnected(ConnectedListElement*& pHead, wynik* wynik);

void AddRunner(Node*& pRoot, wynik*& uczestnik);

void wypiszZawodnika(Node* pRoot);

void zapisywanieDoPliku(ConnectedListElement* wynik);
//

#endif