#pragma once

typedef struct ConnectedListElement;

struct wynik {
	std::string nazwa;
	std::string data;
	std::string nazwisko;
	std::string czas;
	ConnectedListElement* ConnectedHead;
};

struct ConnectedListElement
{
	wynik* wynik;
	ConnectedListElement* pNext;
};

struct Node
{
	wynik* result;
	Node* pLeft;
	Node* pRight;
};
//