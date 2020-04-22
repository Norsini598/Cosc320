#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <iostream>
#include "HashTable.h" //from this access to HashFunctions and UtilityGeneric
//Ein Worterbuch ist ein Hash Tabelle auf Saiten
const std::string defaultdirectory = "englishwords.txt";

class Dictionary {

private:
	std::string dictionarydirectory; //die Textdatei das haben die Worter.
	HashTable<std::string> dictionary; //a dictionary is just a hash table of strings
	float ReadInDictionaryTime; //Lesen sie worterbuch lesenzeit.
	bool empty;

public:
	Dictionary(int = 1); //ein Konstruktor, Geben Sie einen indikator, das was Hash-Funktion benutzen sagen.
	~Dictionary(); //und ein Dekonstruktor

	void ReadInDictionary(); //Lesen sie worter aus dem Worterbuchdverzeichnis in eine HashTable
	void EmptyDictionary(); //klart das Worterbuch.
	void ChangeHashFunction(); //Andere das Funktion Hash
	void OutputDictionaryData(); //Shcriebe daten zum ein datei: ist information uber das Hash-Table und ziet lest das Worterbuch.
	void ChangeDictionaryDirectory(); //andere das Worterbuchverzeihnis
	void PrintDictionarySummary(); //Wortbuchdaten drunken

	//friend std::ostream& operator<<(std::ostream&, const Dictionary&); //will print stats on the hashtable
	void operator+(std::string); //Can add words easily by saying EnglishDictionary + someword
	bool operator==(std::string); //retouren treue wenn das Wort ist im Worterbuch. ist das brauche?\
	Was sonst? Wir brauchen? Wenn das Funktion retoren falsch Wortsuche auslosen. cat == dictionary (ist cat im das Worterbuch?)

	bool IsWord(std::string);

	std::string Get1EditWords(std::string); //Geben Sie ein Wort ein und retouren Sie alle Bearbeitungsworter zuruck.
	std::string Get2EditWords(std::string); //Geben Sie ein Wort zwie und retouren Sie alle Berabeitungsworten zuruck.
	std::string Get1EditWords_R(std::string); //Geben Sie ein Wort ein und reouren alles Saiten im eine Bearbeitungworter. (recursive friendly)
	//std::string Get3EditWords(std::string); //Geben Sie ein Wort drei und retouren Sie alle Berabeitungsworten zuruck. 

	//wenn ist sie ein Funktion das reouren die Worter im n Bearbeitungworten? Try to make one.

	//Was Sonst?

	void PrintList(std::string); //Sie druken ein Liste von das Hahsh Tabelle

	int GetHashFunction() { return dictionary.GetHashFunction(); }

	void GrabGREWords(int, std::string*);
};
#endif // !DICTIONARY_H

