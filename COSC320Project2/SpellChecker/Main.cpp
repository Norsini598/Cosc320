#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <ctime>



#include "Menus.h"
#include "Colors.h"
#include "Dictionary.h"
//this function will be implemented later in the project as the formatting of the dictionary txts
//have many conditions to be looked at and it is not part of the project- definitions would be cool to keep
//void ReadInDictionary(/*will need things such as a hash table as input*/);


using namespace Menus;
using namespace Menus::MainMenuPrompts;
using namespace Menus::SpellCheckPrompts;
using namespace Menus::DictionaryPrompt;
using namespace Menus::OptionsPrompt;
using namespace Menus::HashTableAnalysisPrompt;
using namespace Menus::DictionaryRelatedPrompts;

using namespace UtilityFunctions;

int main()
{
	srand(time(NULL));

	bool POS; //print on startup
	int HFtemp;
	std::ifstream StartIn;
	StartIn.open("Defaults.txt", std::ios::in); //read in a file that has global conditions
	//such as print summary on start up- more coming soon

	StartIn >> POS;
	StartIn >> HFtemp;
	
	StartIn.close();
	
	Dictionary EnglishDictionary(HFtemp);

	if (POS)
		EnglishDictionary.PrintDictionarySummary();
	else
		std::cout << "Print On Start Up is Off. To turn on see \"Options\"." << std::endl;


	//variable declarations
	int MMS = 0; //main menu selection
	int SCS = 0; //spell check selection
	int OMS = 0; //options menu selection
	int DMS = 0; //disctionary menu selection
	int HMS = 0; //Hash menu selection
	int CDS = 0; //Change defaults selection
	
	std::string input = "";
	std::string input2 = "";
	char response = ' ';
	//std::string copy = "";
	
	std::cout << GREEN << "Press any key to continueto main menu: " << DEFAULT;
	std::cin >> response;
	std::cout << std::endl;

	std::cout << FirstTimePrompt << std::endl;

	while (MMS != MMO) {
		//RESET variables
		input = "";
		response = ' ';
		//reset selections
		MMS = 0;
		SCS = 0;
		OMS = 0;
		DMS = 0;
		HMS = 0;
		CDS = 0;
		
		//main menu
		MMS = Menu(MainMenuMainPrompt, MMO, MainMenuPromptOpen);
		
		//open spell check
		if (MMS == 1) {
			while (SCS != SCO) {
				SCS = Menu(MainSpellCheckMainPrompt, SCO, MainSpellCheckOpenPrompt);
				//Main spell check
				if (SCS == 1) { 
					//get an input, parse each word- check them against the dictionary hash table
					int strlength = 0;
					int strwords = 0;
					int len = 0;
					do {
						int i = 0;
						if (i > 0)
							std::cout << "Input a valid string: ";
						else
							std::cout << "Input a string: ";
						std::cin.ignore();
						std::getline(std::cin, input);
					} while (input == "" || input == " ");

					strwords = CalculateSpaces(input); //numer of words in the input
					strlength = CalculateStringLength(input); //legnth of the input (all characters)
					
					//copy = RemovePunctuation(input); //remove punctations , . ? !.  ' may be part of a word dont remove.					
					//MakeLower(input); //no make the sentence lower case before parsing into an array

					RemoveSentencePunctuation(input); //remove puntution that is separating words

					std::string words[strwords]; //stores the input in parses

					//parse the input
					//get individual strings in an array of words
					for (int i = 0; i < strwords; i++) {
						words[i] = ParseString(strlength, input, len);
						len += CalculateStringLength(words[i]) + 1;
					}
					//now the words are in an array and ready to be checked for validity

					//find the wrong words
					int wrongcount = 0;
					std::string wrongwords = ""; //make a space delimited list

					for (int i = 0; i < strwords; i++) {
						//check the words in the array with the dictionary. Nifty == compaision. If returned false then word is not in dictionary
						if (EnglishDictionary == words[i])
							continue; //do nothing
						//not a word. build another array of wrong words
						else
							wrongwords += (words[i] + " "); //add to list
					}

					RemoveDuplicant(wrongwords); //in case the same incorrect spelling occurred twice or more.
					if (wrongwords == "")
						wrongcount = 0;
					else
						wrongcount = CalculateSpaces(wrongwords); //number of wrong words
					
					int fixedwrongcount = 0;

					//correction section--enter if there were errors.
					if (wrongcount != 0) {
						//build wrong words array by breaking apart the wrongwords list.
						std::string wrong[wrongcount];
						len = 0;
						//length of the combined list of wrongwords
						int len2 = CalculateStringLength(wrongwords); //get length of wrong words list.
						std::cout << "Misspelled Words: " << std::endl; 
						//build the array
						for (int i = 0; i < wrongcount; i++) {
							wrong[i] = ParseString(len2, wrongwords, len);
							len += CalculateStringLength(wrong[i]) + 1;//move starting character forward
							if (i == wrongcount - 1)
								std::cout << RED << wrong[i] << DEFAULT << ". " << std::endl;
							else
								std::cout << RED << wrong[i] << DEFAULT << ", ";
						}

						for (int i = 0; i < wrongcount; i++) {
							//print wrong words
							std::cout << " " << RED << wrong[i] << DEFAULT << " is misspelled." << std::endl;
							//are we adding it to the dictionary?
							switch (Menu(AddWordPrompt, DAO, AddWordOpenPrompt)) {
							case 1:
								//Add the word to the dictionary.
								EnglishDictionary + wrong[i]; //the non word is now a word so input does not need to be updated
								//check if it was added
								if(EnglishDictionary == wrong[i])
									wrong[i] = ""; //clear the word since it isn't wrong anymore.
								fixedwrongcount++;
								break;
							case 2:
								//Cancel: do nothing
								break;
							}
						}
						//if after dictionary adding options there remains misspelled words
						//move on to suggestions
						if (wrongcount - fixedwrongcount > 0) {
							std::cout << "|================================|" << std::endl;
							std::cout << "|Do you want to view suggestions |" << std::endl;
							do {
								std::cout << "|1. Yes                          |" << std::endl;
								std::cout << "|2. Cancel & Return to           |" << std::endl;
								std::cout << "|   Spell Check Menu             |" << std::endl;
								std::cout << "|Make Input: ";
								std::cin >> response;
							} while (response != '1' && response != '2');

							if (response == '1') {

								std::cout << "|================================|" << std::endl;
								std::cout << "|  Suggestions to Improve Input  |" << std::endl;
								std::cout << "| Below are suggestions for:     |" << std::endl;
								
								//go through it again but this time prompt corrections and potential to change your word
								for (int i = 0; i < wrongcount; i++) {
									//if still a wrong word.
									if (wrong[i] != "") {
										std::cout << "|" << RED << wrong[i] << DEFAULT << std::endl;
										std::cout << "| 1 Edit Words: \n" << GREEN << "Press any key to continue: " << DEFAULT;
										std::cin >> response;
										//calculate 1 edit words
										std::string Possible1editwords = EnglishDictionary.Get1EditWords(wrong[i]);
										int MFA = 0; //move forward anyway 1 if the user enter 0 to cancel 
										if (Possible1editwords == "") {
											std::cout << "No suggestions available." << std::endl;
											MFA = 1;
										}
										//there are word to search.
										else {
											//print for user
											std::cout << std::endl << Possible1editwords << std::endl << std::endl;
											//fix word now or move on to 2 letter edits
											std::cout << "|Enter 1 to correct the spelling of " << RED << wrong[i] << DEFAULT << std::endl;
											std::cout << "|or anything else to continue: ";
											std::cin >> response;
											std::cout << "|================================|" << std::endl;

											//and move forward. Otherwise they cant view 2 edit suggesstions
											//change input-- i.e fix the misspelling
											if (response == '1') {
												bool done = false;
												int p = 0;
												do {
													std::cout << "Input the word that will replace " << RED << wrong[i] << DEFAULT ": ";
													if (p > 0)
														std::cout << "\nOr enter a 0 to cancel and move forward: ";
													std::cin >> input2;
													//valid input
													//its either an option or some other word in the dicitonary
													if ((IsWithin(Possible1editwords, input2) || EnglishDictionary == input2) && input2 != "0") {
														//now replae the wrong[i] word in input with input2
														int index = WhereamI(input, wrong[i]); //index where wrong[i] begins in input
														Replace(input, input2, index); //input has been updated with input2's replacement at index
														done = true;
														wrong[i] = "";
													}
													else if (p > 0 && input2 == "0") {
														done = true;
														MFA = 1;
													}
													p++;
												} while (!done);
											}
										}
										//two letter edits. Can only enter if did do correction above
										if ((response == '1' && MFA == 1) || response != '1') {

											std::cout << "|================================|" << std::endl;
											std::cout << "|2 Edit Words: \n" << GREEN << "Press any key to continue: " << DEFAULT;
											std::cin >> response;
											//calculate 2 edit words
											std::string Possible2editwords = EnglishDictionary.Get2EditWords(wrong[i]);
											if(Possible2editwords == "")
												std::cout << "No suggestions available." << std::endl;
											else {
												//print for user
												std::cout << std::endl << Possible2editwords << std::endl << std::endl;

												//fix word now!
												std::cout << "|================================|" << std::endl;

												bool done = false;
												int p = 0;
												std::string oldinput2 = "l"; //initialize with something
												do {
													if(p == 0)
													std::cout << "Input the word that will replace " << RED << wrong[i] << DEFAULT << ": ";
													
													if (p > 0) {
														std::cout << YELLOW << input2 << DEFAULT << " is not in the dictionary." << std::endl;
														std::cout << "\nEnter a valid word\nEnter a 0 to add " << input2 << " to the dictionary and continue\nor enter a valid word. " << std::endl;
													}

													std::cin >> input2; //will be either a word or 0

													//entry is a word but not in dictionary can add it and get out- user defined
													if (p > 0 && input2 == "0") {
														//Add the word to the dictionary.
														EnglishDictionary + oldinput2; //the non word is now a word so input does not need to be updated
														int index = WhereamI(input, wrong[i]); //index where wrong[i] begins in input. still uses wrong[i] because that was the original.
														Replace(input, oldinput2, index);
														done = true; //get out of loop
														wrong[i] = ""; //clear the word since it isn't wrong anymore.
													}
													//its either an option or some other word in the dicitonary
													if (IsWithin(Possible2editwords, input2) || EnglishDictionary == input2) {
														//now replace the wrong[i] word in input with input2
														done = true;
														int index = WhereamI(input, wrong[i]); //index where wrong[i] begins in input
														Replace(input, input2, index); //input has been updated with input2's replacement at index
													}
													else
														p++;
													oldinput2 = input2;
												} while (!done);
											}
										}
									} //if still a wrong word block (not fixed in add to dictionary)
								} //wrong count for loop

								std::cout << "Sentence/Phrase after corrections: " << input << std::endl;
								std::cout << "-----------------------------------" << std::endl;
							} //fix word(s) menu
							else
								std::cout << std::endl;
						} //if wrong words after dictionary
					}//there were wrong words in the users input
					else
						std::cout << "No spelling errors. Good Job!" << std::endl;	
					//std::cout << "Input length: " << strlength << "\n# of words in input: " << strwords << std::endl;
				}
			}
		}
		//open dictionary study
		else if (MMS == 2) {
			while (DMS != DMO) {
				DMS = Menu(MainDictionaryMainPrompt, DMO, MainDictionaryOpenPrompt);
				if (DMS == 1) {
					bool loop = false;
					do {
						int grab = 0;
						int op = 0;
						loop = false;
						std::cout << "Study dictionary terms: " << std::endl;
						std::cout << "------------------------" << std::endl;
						std::cout << "How many terms do you want to study" << std::endl;
						do {
							std::cout << "Select an option: " << std::endl;
							std::cout << "1. 10\t2. 15\t3. 20\t 4. 25\t 5. Cancel" << std::endl;
							std::cin >> op;
						} while (op < 1 || op > 5);
						if (op != 5) {
							if (op == 1)
								grab = 10;
							else if (op == 2)
								grab = 15;
							else if (op == 3)
								grab = 20;
							else
								grab = 25;

							std::string* Terms;
							Terms = new std::string[grab];
							for (int i = 0; i < grab; i++)
								Terms[i] = ""; //initialize with empty string

							EnglishDictionary.GrabGREWords(grab, Terms);

							std::cout << "Study these words: " << std::endl;
							for (int i = 0; i < grab; i++) {
								std::cout << i + 1 << ". " << Terms[i] << std::endl;
							}
							std::cout << GREEN << "Press any key when ready to continue: " << DEFAULT;
							std::cin >> response;

							std::cout << "Enter a 1 to generate more terms. Or any other key to return to menu: ";
							std::cin >> response;
							if (response == '1')
								loop = true;
							response = ' ';

							delete[]Terms;
							Terms = NULL;
						}
					} while (loop);
					
				}
				//print list from dictionary table
				else if (DMS == 2) {
					bool loop = false;
					do {
						loop = false; //assume not again.
						std::string search;
						std::cout << "Enter any word. If it is a word that" << std::endl;
						std::cout << "list in the hash table will be printed." << std::endl;
						std::cout << "Input a word: ";
						std::cin >> search;
						if (EnglishDictionary == search) {
							std::cout << YELLOW << search << "'s List: " << DEFAULT << std::endl;
							EnglishDictionary.PrintList(search);
						}
						else {
							int opt = Menu(AddWordOpenPrompt, 2, AddWordPrompt);
							if (opt == 1)
								EnglishDictionary + search;
						}
						std::cout << GREEN << "Press any key when ready to continue: " << DEFAULT;
						std::cin >> response;

						std::cout << "Enter a 1 to search another list. Or any other key to return to menu: ";
						std::cin >> response;
						if (response == '1')
							loop = true;
						response = ' ';
					} while (loop);
				}
				//else quit and return to main menu
			}
		}
		
		//open options menu
		else if (MMS == 3) {
			while (OMS != OMO){
			OMS = Menu(MainOptionsMainPrompt, OMO, MainOptionsOpenPrompt);
			if (OMS == 1) {
				About();

				std::cout << GREEN << "Press any key to conintue: " << DEFAULT;
				std::cin >> response;
			}
			else if (OMS == 2) {
				std::cout << "Changing Hash Function" << std::endl;
				EnglishDictionary.ChangeHashFunction();
				
				EnglishDictionary.PrintDictionarySummary();

				std::cout << GREEN << "Press any key to conintue: " << DEFAULT;
				std::cin >> response;
				std::cout << std::endl;
				response = ' ';

			}
			else if (OMS == 3) {
				std::cout << "Changing Dictionary Directory" << std::endl;
				EnglishDictionary.ChangeDictionaryDirectory();
			}
			else if (OMS == 4) {
				while (CDS != CDO) {
					std::ofstream OutDefaults;
					OutDefaults.open("Defaults.txt"); //don't open in appen mode, replace mode.
					if (POS)
						//turn off
						CDS = Menu(ChangeDefaultsOpenPrompt, CDO, ChangeOptionsPrompt1);
					else
						//turn on
						CDS = Menu(ChangeDefaultsOpenPrompt, CDO, ChangeOptionsPrompt2);
					if (CDS == 1) {
						if (POS) {
							POS = false;
							OutDefaults << 0 << std::endl << EnglishDictionary.GetHashFunction();
						}
						else {
							POS = true;
							OutDefaults << 1 << std::endl << EnglishDictionary.GetHashFunction() << std::endl;
						}

						OutDefaults.close();
					}
				}
			}
			//else quit and return to menu
			}
		}

		//open hash table analysis
		else if (MMS == 4) {
			while (HMS != HMO) {
				HMS = Menu(MainHashAnalysisMainPrompt, HMO, MainHashAnalysisOpenPrompt);
				if (HMS == 1) {
					std::cout << "Number of implemented valid hashing functions: #" << stringhashes << std::endl;
					std::cout << "---------------------------------------------------------" << std::endl;
					std::cout << "|                    Hash Table Analysis                 |" << std::endl;
					std::cout << "| This method creates a hash table for each impelemented |" << std::endl;
					std::cout << "| hashing function. Fills all tables with strings from   |" << std::endl;
					std::cout << "| 0 to hashtableszie-1. Then stats will be displayed     |" << std::endl;
					std::cout << "| for each table one at a time.                          |" << std::endl;
					std::cout << "|--------------------------------------------------------|" << std::endl;

					std::cout << GREEN << "Press any key to continue: " << DEFAULT;
					std::cin >> response;
					std::cout << std::endl;
					response = ' ';

					//build and fill some tables
					HashTable<std::string> tables[stringhashes]; //create #HashFunctionsImplemented Hash Fucntions.
					for (int i = 0; i < HashTableSize; i++) {
						for (int j = 0; j < stringhashes; j++) {
							//set the hash functions
							if (i == 0)
								tables[j].SetHF(j + 1);
							tables[j].AddNode(std::to_string(i)); //add i to the hash table
						}
					}

					for (int i = 0; i < stringhashes; i++) {
						std::cout << "Table #" << i + 1 << " of " << stringhashes << std::endl;
						tables[i].PrintTableSummary();
						std::cout << GREEN << "Press any key to conintue: " << DEFAULT;
						std::cin >> response;
						std::cout << std::endl;
						response = ' ';
					}
				}
				else if (HMS == 2) {
					EnglishDictionary.PrintDictionarySummary();
					std::cout << GREEN << "Press any key to conintue: " << DEFAULT;
					std::cin >> response;
					std::cout << std::endl;
					response = ' ';
				}
				//else quit and return to menu
			}
		}

		//"Clear:
		if (MMS != 5)
			//move some spaces down to act though cleared
			std::cout << "\n\n\n\n\n\n\n\n|================================|\n";

		//if 5 was inputted then we quit
	}
	std::cout << "GoodBye!" << std::endl;
		
	return 0;
}
