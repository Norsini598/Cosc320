#include "Dictionary.h"
#include <fstream>
#include <chrono>
#include <ctime>
#include <stdlib.h>

//Sie " "strukteruen
Dictionary::Dictionary(int H) {
	dictionarydirectory = defaultdirectory;
	if (H != 1)
		dictionary.SetHF(H); //Standard-Hash_Funktion ist Funktion 1.
	ReadInDictionary(); //setzt die Tabelle und das Zeit zum Lesen das Worterbuch
}
Dictionary::~Dictionary() {
	//kiene Zeiger!
	OutputDictionaryData();
}

//Lesen Sie das Worterbuch.
void Dictionary::ReadInDictionary() {
	std::ifstream In;
	In.open(dictionarydirectory, std::ios::in);

	std::string var = "";

	auto start = std::chrono::system_clock::now(); //set the timer for nreading in dictionary

	while (!In.eof()) {
		In >> var;
		dictionary + var; //fuge das Wort zum HashTable. Denken Sie daran, das ist wo dat Wort ist "hashed"
	}
	//stop the timer
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;
	std::time_t end_time = std::chrono::system_clock::to_time_t(end);

	ReadInDictionaryTime = elapsed_seconds.count();
	empty = false;

	dictionary.CalculateBiggestBucketSize();
	dictionary.CalculateSmallestBucketSize();
}

//Fuge ein wort zum Worterbuch
void Dictionary::operator+(std::string S) {
	int entry = 0;
	//Erste uberprufst wenn das Worst isnt keine zum Worterbuch
	if (!dictionary.InList(S)) { //wir wollst falsch, wenn true nicht hinzufugen zum Worterbuch, nur wen nicht im Worterbuch
	//Fuge das wort zu das Worterbuch.
		std::cout << "Confirm Dictionary Addition Prompt:" << std::endl;
		do {
			std::cout << "Enter a 1 to confirm or 0 to cancel: ";
			std::cin >> entry;
		} while (entry != 1 && entry != 0);
		if (entry == 1) {
			dictionary + S;
			std::cout << "Dictionary Updated!" << std::endl;
			
			//also update the directory
			std::ofstream Out;
			Out.open(dictionarydirectory, std::ios::app);
			Out << S << std::endl;
		}
		//else{dont add anything to the dictionary}
	}
}

//Klart das Worterbuch
void Dictionary::EmptyDictionary() {
	dictionary.EmptyTable();
	ReadInDictionaryTime = 0; //zurukstezen diesse Zietdaten.
	empty = true;
}

//andere das Funktion Hash
void Dictionary::ChangeHashFunction() {
	/*
	Diese Funktion erlaubt der Benutzer zu andern die Hashing-Funktion.
	Daten im alten Worterbuch werden geschrieben zu eine Datei und
	neue Daten werden einglessen.
	*/
	if (stringhashes > 1) {
		OutputDictionaryData(); //schcriebe das daten zum ein datei.
		dictionary.ChangeHashFunction();
		EmptyDictionary(); //empty it
		ReadInDictionary();//and reread it in
	}
	else
		std::cout << "Sorry only 1 valid string hashing\n function implemented right now." << std::endl;

}

//Wortbuchdaten drunken
void Dictionary::PrintDictionarySummary() {
	if (empty == false) {
		dictionary.PrintTableSummary(); //prints all stats on this hash table
		std::cout << "| Build Time " << ReadInDictionaryTime << " seconds" << std::endl; //plus the time to inser+ all elemnts
		std::cout << "-------------------------------------" << std::endl;
	}
	else
		std::cout << "Empty Dictionary!" << std::endl;
}

//underladungen:
/*
//Daten drucken
std::ostream& operator<<(std::ostream& os, const Dictionary& obj) {
	if (obj.empty == false) {
		os << obj.dictionary << std::endl; //prints all stats on this hash table
		os << "Insertion Time " << obj.ReadInDictionaryTime << " seconds" << std::endl; //plus the time to inser+ all elemnts
		os << "---------------------------------" << std::endl;
	}
	else
		os << "Empty Dictionary!" << std::endl;
	return os;
}*/
//Ist es im das Wortbuch? dictionary == help -> true
bool Dictionary::operator==(std::string Wort) {
	bool r = false;
	std::cout << Wort << std::endl; //drucke das Wort.
	if (dictionary.InList(Wort))
		r = true;
	return r;
//retouren treue wenn das Wort ist im das Worterbuch.
}

//Finden ein Wort
bool Dictionary::IsWord(std::string Wort) {
	return (dictionary.InList(Wort) ? true : false);
}

//Schribe das daten zum ein datei
void Dictionary::OutputDictionaryData() {
	std::ofstream out;
	if (empty) {
		std::cout << "Sorry, empty dictionary. " << std::endl;
	}
	else {
		out.open("DictionaryData.txt", std::ios::app);

		//erste scheibe muhelos daten. (Daten im diesse Klasse)
		out << ReadInDictionaryTime << ", ";

		//Im HashTable Klasse:
		//Jetzt schrieben daten aus dem HashTable klasse, diesse braucht eine Zieten. Das "schwierig" daten.
		out << dictionary.HF << ", "; //the hash functon being used. Crucial for comparing different hash functions
		out << HashTableSize << ", "; //the size of the hash table
		out << dictionary.Getload() << ", " << dictionary.Getuniqueload() << ", ";
		out << dictionary.CalcualteAverageBucketSize() << ", ";
		out << dictionary.GetBiggestBucket() << ", " << dictionary.GetBiggestCount() << ", " << dictionary.GetBiggestBucketTime() << ", ";
		out << dictionary.GetSmallestBucket() << ", " << dictionary.GetSmallestCount() << ", " << dictionary.GetSmallestBucketTime() << std::endl; //ende des ausschriebe

		out.close();
	}

}

//Andere das worterbuchverzeichnis.
void Dictionary::ChangeDictionaryDirectory() {
	std::string input;
	std::cout << "Input the name of a new dictionary directory without the ending \".txt\": ";
	std::cin >> input;
	input += ".txt";
	dictionarydirectory = input;
	
	//now check if it is a file (that can be opened)
	std::ifstream test;
	test.open(dictionarydirectory);
	//not good dictionary diretory
	if (!(test.is_open())) {
		std::cout << "Error opening file!" << std::endl;
		std::cout << "Dircectory Unchanged. " << std::endl;
		test.close();
		dictionarydirectory = defaultdirectory; //zurucksetzen
	}
	//wenn neue Worterbuchverzeichnis
	else {
		test.close();
		OutputDictionaryData(); //schcriebe das daten zum ein datei.
		EmptyDictionary(); //empty it
		ReadInDictionary();//and reread it in
	}
}

//Geben Sie ein Wort ein und retouren Sie alle Bearbeitungsworter zuruck.
std::string Dictionary::Get1EditWords(std::string Wort) {
	std::ofstream Out;
	Out.open("1EditWords.txt", std::ios::app);

	auto start = std::chrono::system_clock::now(); //set the timer for finding 1 change edits in dictionary

	//MakeLower(Wort); //ensure we are working in lower cases

	int strlen = CalculateStringLength(Wort); //Halten Sie die Lange der Zeichenfloge.

	std::string editword = ""; //das Wort wird gebaut.
	std::string Edit1Words = ""; //Liste alle Worter im ein bearbieten zuruck.
	std::string copy = Wort; //wird zum Zuruckstezen am Anfang der Schliefe verwendt.
	int wordcount = 0; //nummer auf worter zum ein beabieten.

	//Erste das Wort das du konst machen vorbei anhagen ein Zeichen zu die Front. \
	(append a character to the front of Wort and then check if that is a word)

	//Alles Situationen wo Buchstaben sind Anderungen oder hinzugefugt
	for (int j = -1; j < strlen + 1; j++) { //for every index in the inputted string plus append in front and append at rear
		copy = Wort; //copy wird bearbeitet 
		for (char i = 33; i < 127; i++) { //span the whole ascii table.
			editword = ""; //reset edit word
			if (j == -1)
				editword = i + Wort; //append wort to end
			else if (j == strlen)
				editword = Wort + i; //end character change to end
			else { //somewhere in between 
				 copy[j] = i; //replace that caracter at index j with the character that i is set as.
				 editword = copy;
			}
			if (dictionary.InList(editword)) {
				Edit1Words += editword + " "; //append the newly create word , if it is a word.
			}
		}

		//now go through again because we forgot words that could be made by adding a charactering in the middle of a string
		//ex: bech --> beach  added a
		if (j != -1 && j < strlen) {
			for (char i = 33; i < 127; i++) {
				editword = "";
				//build front half of the new word
				for (int k = 0; k <= j; k++)
					editword += Wort[k]; //if j == 0 then just add wort[0]
				editword += i; //append the additional character
				for (int k = j + 1; k < strlen; k++)
					editword += Wort[k];
				if (dictionary.InList(editword))
					Edit1Words += editword + " "; //append the newly create word , if it is a word.
			}
		}
	}
	//Alles Situationen wo ein Buchstaben ist entfernt
	for (int i = 0; i < strlen; i++) {
		copy = Wort;
		RemoveCharacter(i, copy);
		if (dictionary.InList(copy)) { //das Wort existiert! Fuge Sie die Wortliste hinzu.
			Edit1Words += copy + " "; //added to list
		}
	}


	RemoveDuplicant(Edit1Words); //Entferen das Duplikaten
	
	wordcount = CalculateSpaces(Edit1Words); //Wie viele beabietenworter?

	//stop the timer
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;
	std::time_t end_time = std::chrono::system_clock::to_time_t(end);

	Out << CalculateStringLength(Wort) << ", " << wordcount << ", "<< elapsed_seconds.count() << std::endl; //length of input, words valid, and time to find all

	Out.close();

	return Edit1Words; //Vor dem Druken diesse Wort veranderung Zeilenabstand fur Lesbarkeit.
}

/*//Jetzt Worter im zwei anderungen von das Orignial Wort.
std::string Dictionary::Get2EditWords(std::string Wort) {
	//Wort ist das Wort das geandert wird.
	std::ofstream Out;

	int wordcount = 0;

	Out.open("2editwords.txt", std::ios::app);

	auto start = std::chrono::system_clock::now(); //set the timer for finding 2 change edits in dictionary

	MakeLower(Wort); //Stellen Sie Klienbuchstaben sicher
	//zwei Anderungen fur alles worter jeden.
	std::string editword = ""; //being built
	std::string Edit2Words = ""; //stores valid ediitword + " ". Space delimited list.

	//Anderungen ein
	//Anderungen zwei
	//diesse Sie brauchen zwei fur Schleifen

	//Wie oben das Stringlange bekommen 
	int strlen = CalculateStringLength(Wort);

	//als Biespiel oben Sie nehmen das wort "hime", es bearbeiten worter beinhalten:\
	"Chimes, Limes, Lamer, Crime, Wine, ..."
	//the first loop will range from 2 character before Wort to two after the end of Wort.
	for (int i = -2; i < strlen + 2; i++) {
		//-2 can only be applied if j = -1
		//now we need changeA's edit: this edit will/can be made across all i
		for (char a = 'a'; a <= 'z' + 1; a++) {  //from a to {. { denote removal of character at i
			//jetzt der zwei bearbeiten. diesse Sie konnen sein aus alles Buchstabe ausser bei Lage i.
			for (int j = -1; j < strlen + 1; j++) {
				editword = Wort; //reset editword

				//conditions that require skips
				if (i == j)
					continue; //skip this, as this is only 1 edit.
				else if (i == -2 && j != -1)
					continue; //can only make this word if the 1 edit distance loop is in append to front location
				else if (i == strlen + 1 && j != strlen)
					continue; //can only make this word if the 1 edit distance loop is in appen to end location

				//ein bearbeiten is haben.
				else {
					//Jetzt das zwei bearbeiten Schleife. 2nd edit char
					for (char b = 'a'; b <= 'z' + 1; b++) { //b = '{' denotes removal of character at j
						if (a != '{' || b != '{') {
							if (i == -2) { //implies j == -1
								//not removal of any characters
								editword = a + b;
								editword = editword + Wort;
							}
							else if (i == strlen + 1) { //implies j = strlen
								editword = Wort;
								editword = editword + b;
								editword = editword + a;
							}
							else if (i == -1 && j == strlen) { //one in front and one at the end
								editword = a + Wort;
								editword + b;
							}
							else if (i == strlen && j == -1) {
								editword = b;
								editword += Wort + a; //b in front, word in mid, and a at end.
							}
							//somewhere in between but neither are removal
							//both in the word
							else {
								editword = Wort;
								//i = {0, strlen-1} , j = {0, strlen-1}, and i != j
								editword[i] = a;
								editword[j] = b;
							}
						}
						//removal of characters
						else {
							//remove character at location i
							if (a == '{' && b != '{') {
								editword = Wort;
								RemoveCharacter(i, editword);
							}
							//remove of only character at j
							else if (a != '{' && b == '{') {
								editword = Wort;
								RemoveCharacter(j, editword);
							}
							//remove both
							else {
								editword = Wort;
								//erste entfernen char zu i
								RemoveCharacter(i, editword);
								//jetzt entfernen char zu j
								RemoveCharacter(j, editword);
							}
						}
					}
					//check if the new word is in the dictionary, if so append it to the 2 edit words\
					//What about duplicants for instance i = 4 and j = 3 is the same as i = 3 and j = 4.
					//thes is a funciton in UtlilityGeneric that removes duplicant words in a list ... so long separated by " ".
					if (dictionary.InList(editword))
						Edit2Words += editword + " ";
				}
			}
		}
	}
	RemoveDuplicant(Edit2Words); //remove duplicate words in the list

		//stop the timer
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;
	std::time_t end_time = std::chrono::system_clock::to_time_t(end);

	Out << CalculateStringLength(Wort) << ", " << wordcount << elapsed_seconds.count(); //length of input, words valid, and time to find all

	Out.close();
	return Edit2Words; //retouren alles Worter das sind innerhalb zwie anderungen
}
*/

//Jetzt berechnen  wir neue dat zwei anderungen auf das Original Wort aber mit ein besser Funktion
std::string Dictionary::Get2EditWords(std::string Wort) {
	//Wort ist das Wort das geandert wird.
	std::ofstream Out; //ein Ausgabestrom datei.
	auto start = std::chrono::system_clock::now(); //set the timer for finding 2 change edits in dictionary

	Out.open("2editwords.txt", std::ios::app); //das datei.
	int wordcount = 0;
	int strlen = CalculateStringLength(Wort); //Halten Sie die Lange der Zeichenfloge.

	//zwei Anderungen fur alles worter jeden.
	std::string editword = ""; //being built das Wort wird gebaut
	std::string Edit2Words = ""; //stores valid ediitword + " ". Space delimited list. Die Liste
	std::string copy = Wort; //wird zum Zuruckstezen am Anfang der Schliefe verwendt.
	int count = 0; //nummer auf worter zum ein beabieten.

	//anderungen auf eines Zeichen
	for (int j = -1; j < strlen+1; j++){
		copy = Wort; //copy wird bearbeitet
		//Anderungen bearbeiten
		for (char i = 33; i < 127; i++) { //span the whole ascii table.
			editword = ""; //reset edit word
			//haben ein Anderung.
			if (j == -1)
				editword = i + Wort; //append wort to end
			else if (j == strlen)
				editword = Wort + i; //end character change to end
			else { //somewhere in between 
				copy[j] = i; //replace that caracter at index j with the character that i is set as.
				editword = copy;
			}
			//make another change
			editword = Get1EditWords_R(editword); //jetzt editword ist ein liste auf worter. 
			//Calls same function as GetEdit1Words but doesn't filter out non words
			//Now we have a list of words so same procdure, make array of words by parsing string at spaces
			//then all each into the dictionary to see if they are a word, if it is then add it to Edit2Words
			
			//now we have a list of 2 edits from one of many possible edits
			//identify which of these two edits are a word, add to list
			int len = 0;
			int wrds = CalculateSpaces(editword);
			int strln = CalculateStringLength(editword);
			std::string edit2words[wrds];
			//parse the input
			//get individual strings in an array of words
			for (int i = 0; i < wrds; i++) {
				edit2words[i] = ParseString(strln, editword, len);
				len += CalculateStringLength(edit2words[i]) + 1;
			}

			for(int i=0; i < wrds; i++)
			if (dictionary.InList(edit2words[i])) {
				Edit2Words += edit2words[i] + " "; //append the newly create word , if it is a word.
			}
		}
	}

	//Alles Situationen wo ein Buchstaben ist entfernt
	for (int i = 0; i < strlen; i++) {
		editword = Wort;
		RemoveCharacter(i, editword); //remove a character from the word
		
					//make another change
		
		editword = Get1EditWords_R(editword); //jetzt editword ist ein liste auf worter. 
		//Calls same function as GetEdit1Words but doesn't filter out non words
		//Now we have a list of words so same procdure, make array of words by parsing string at spaces
		//then all each into the dictionary to see if they are a word, if it is then add it to Edit2Words

		//now we have a list of 2 edits from one of many possible edits
		//identify which of these two edits are a word, add to list
		int len = 0;
		int wrds = CalculateSpaces(editword);
		int strln = CalculateStringLength(editword);
		std::string edit2words[wrds];
		//parse the input
		//get individual strings in an array of words
		for (int i = 0; i < wrds; i++) {
			edit2words[i] = ParseString(strln, editword, len);
			len += CalculateStringLength(edit2words[i]) + 1;
		}

		for (int i = 0; i < wrds; i++) {
			if (dictionary.InList(edit2words[i])) //das Wort existiert! Fuge Sie die Wortliste hinzu.
				Edit2Words += edit2words[i] + " "; //append the newly create word , if it is a word.
		}
	}

	RemoveDuplicant(Edit2Words);
	count = CalculateSpaces(Edit2Words);

	//stop the timer
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;
	std::time_t end_time = std::chrono::system_clock::to_time_t(end);

	Out << CalculateStringLength(Wort) << ", " << count << ", " << elapsed_seconds.count() << std::endl; //length of input, words valid, and time to find all

	Out.close();

	return Edit2Words;
}


//Druken ein Liste von Hash Tabelle
void Dictionary::PrintList(std::string d) {
	dictionary.PrintSinlgeList(d);
}

//Recursive friendly edit1words. doesn't check if in dictionary.
//Forinstane input = b. bu is 1 edit distance but not a word, it wouldn't get added to the list
//but but is a word 2 edit distances from b. 

std::string Dictionary::Get1EditWords_R(std::string Wort) {
//doeesnt filter out nonwords only duplicants
	int strlen = CalculateStringLength(Wort); //Halten Sie die Lange der Zeichenfloge.

	std::string editword = ""; //das Wort wird gebaut.
	std::string Edit1Words = ""; //Liste alle Worter im ein bearbieten zuruck.
	std::string copy = Wort; //wird zum Zuruckstezen am Anfang der Schliefe verwendt.
	int wordcount = 0; //nummer auf worter zum ein beabieten.

	//Erste das Wort das du konst machen vorbei anhagen ein Zeichen zu die Front. \
	(append a character to the front of Wort and then check if that is a word)

	//Alles Situationen wo Buchstaben sind Anderungen oder hinzugefugt
	for (int j = -1; j < strlen + 1; j++) { //for every index in the inputted string plus append in front and append at rear
		copy = Wort; //copy wird bearbeitet 
		for (char i = 33; i < 127; i++) { //span the whole ascii table.
			editword = ""; //reset edit word
			if (j == -1)
				editword = i + Wort; //append wort to end
			else if (j == strlen)
				editword = Wort + i; //end character change to end
			else { //somewhere in between 
				copy[j] = i; //replace that caracter at index j with the character that i is set as.
				editword = copy;
			}
			Edit1Words += editword + " "; //append the newly created mesh of words
		}
		//now go through again because we forgot words that could be made by adding a charactering in the middle of a string
		//ex: bech --> beach  added a
		if (j != -1 && j < strlen) {
			for (char i = 33; i < 127; i++) {
				editword = "";
				//build front half of the new word
				for (int k = 0; k <= j; k++)
					editword += Wort[k]; //if j == 0 then just add wort[0]
				editword += i; //append the additional character
				for (int k = j + 1; k < strlen; k++)
					editword += Wort[k];
				Edit1Words += editword + " "; //append the newly create mesh- likely many nonwords
			}
		}
	}
	//Alles Situationen wo ein Buchstaben ist entfernt
	for (int i = 0; i < strlen; i++) {
		copy = Wort;
		RemoveCharacter(i, copy);
		if (dictionary.InList(copy)) { //das Wort existiert! Fuge Sie die Wortliste hinzu.
			Edit1Words += copy + " "; //added to list
		}
	}

	RemoveDuplicant(Edit1Words); //Entferen das Duplikaten

	return Edit1Words; //Vor dem Druken diesse Wort veranderung Zeilenabstand fur Lesbarkeit.
}

//Geben GRE Worter
void Dictionary::GrabGREWords(int grab, std::string* Terms) {
	std::ifstream In;
	std::string var = "";
	int cnt = 0;
	//first get count and make sure all the words are in the dictionary
	In.open("GREWords.txt", std::ios::in);
	//get word count
	while (!In.eof())
	{
		In >> var;
		//if not in dictionary add it.
		if (!(dictionary.InList(var))) {
			dictionary.AddNode(var);
			//also update the directory
			std::ofstream Out2;
			Out2.open(dictionarydirectory, std::ios::app);
			Out2 << var << std::endl;
		}
		cnt++;
	}
	In.close(); //close the file

	//build array of "random" GRE words
	int find = rand() % (cnt-25) + 1; //use this word and the grab many after it, but cant be 25 from top to avoid potenital overflow
	In.open("GREWordsWithDef.txt", std::ios::in);
	for (int i = 0; i < grab; i++) {
		while (find > 0) {
			//move down the file until reaching the randomized value
			std::getline(In, var);
			find--;
		}
		std::getline(In, var);
		Terms[i] = var;
	}
	In.close();
}