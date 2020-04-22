
#include <iostream>
#include "Colors.h"

namespace Menus {
	
	const int MMO = 5; //main menu options
	const int SCO = 2; //spell check options
	const int DMO  = 3; //dictionary menu options
	const int OMO = 5; //optioms menu options
	const int HMO = 3; //hash menu options
	const int DAO = 2; //dictionary add options
	const int CDO = 2; //change defaults options

	//first time prompt
	const std::string FirstTimePrompt = "|    Project 2: Spell Checker    |\n| Programmer: Nicholas A.Orsini  |\n|================================|";
	//Menu prompts
	namespace MainMenuPrompts {
		const std::string MainMenuPromptOpen = "|           Main Menu            |\n|================================|";
		const std::string MainMenuMainPrompt = "| Select a corresponding option  |\n| 1. Open Spell Check            |\n| 2. Open Dictionary Options     |\n| 3. Open Options Menu           |\n| 4. Open Hash Table Analysis    |\n| 5. Quit                        |";
											   
	}										 
	//Spell check prompts
	namespace SpellCheckPrompts{
		const std::string MainSpellCheckOpenPrompt = "|================================|\n|        Spell Check Menu        |\n|================================|";
		const std::string MainSpellCheckMainPrompt = "| 1. Test Spelling               |\n| 2. Return to Main Menu         |";
	}
	//Dictionary stuffs prompt??
	namespace DictionaryPrompt {
		const std::string MainDictionaryOpenPrompt =  "|================================|\n|     Dictionary Options Menu    |\n|================================|";
		const std::string MainDictionaryMainPrompt =  "| 1. Study Dictionary Words      |\n| 2. Print a list from ditionary |\n| 3. Return to Main Menu         |";
	}
	//Options stuffs prompt
	namespace OptionsPrompt {
		const std::string MainOptionsOpenPrompt = "|================================|\n|          Options Menu          |\n|================================|";
		const std::string MainOptionsMainPrompt = "| 1. About                       |\n| 2. Modify Enabled Hash Function|\n| 3. Modify Dictionary Directory |\n| 4. Modify Other Defaults       |\n| 5. Return to Main Menu         |";
		
		const std::string ChangeDefaultsOpenPrompt =  "|================================|\n|      Change Defaults Menu      |\n|================================|";
		const std::string ChangeOptionsPrompt1 = "| 1. Turn off Print On Start Up  |\n| 2. Return to Options Menu      |";
		const std::string ChangeOptionsPrompt2 = "| 1. Turn on Print On Start Up   |\n| 2. Return to Options Menu      |";
	}											   
	//Hash table prompt->stats
	namespace HashTableAnalysisPrompt {
		const std::string MainHashAnalysisOpenPrompt = "|================================|\n|    Hash Table Analysis Menu    |\n|================================|";
		const std::string MainHashAnalysisMainPrompt = "| 1. View Hash Table Statistics  |\n| 2. Print Summary Table of Dict.|\n| 3. Return to Main Menu         |";
	}
	//Dictiionary Prompt Mernus
	namespace DictionaryRelatedPrompts {
		const std::string AddWordOpenPrompt = "|================================|\n|Do you want to add this word to |\n|        the dictionary?         |";
		const std::string AddWordPrompt =     "| 1. Add to Dictionary           |\n| 2. Don't Add To The Dictionary |";
	}


	//-------------------------------------------------------------------------------------------------------

	//declarations
	int Menu(std::string, int, std::string = "", std::string = "");

	//Implementation
	int Menu(std::string Promptmain, int maxoption, std::string OpeningPromptB, std::string PrompUnused){
		short option = 0;
		int loop = 0;
		//openingpromptA comes in as "" for all prompts asside main menu
		bool end = false;
		
		std::cout << OpeningPromptB << std::endl;
		
		do {
			if (loop > 0)
				std::cout << "----------------------------------\n|" << RED << "         Invalid input!         " << DEFAULT << "|\n| Appropriate values:   (1 - " << maxoption << ")  |\n|--------------------------------|" << std::endl;
			std::cout << Promptmain << std::endl;
			std::cout << "| Make Input: ";
			std::cin >> option;
			//error check
			while (!std::cin.good()) {
				//clear stream
				std::cin.clear();
				std::cin.ignore(INT8_MAX, '\n');
				//send back to the top
				option = MMO+1;
			}
			loop++;
		} while (option < 1 || option > maxoption);
		std::cout << std::endl;
		return option;
	}



}


void About() {
	std::cout << "------------------------------------ ABOUT -----------------------------------" << std::endl;
	std::cout << "|This project demonstates the functions of hash tables and hashing functions.|" << std::endl;
	std::cout << "|To do this the program reads in a directory of words- this can be changed if|" << std::endl;
	std::cout << "|the user would prefer to use their own directory. See Options Menu.         |" << std::endl;
	std::cout << "|After reading in the directory, the user will have the option to see the    |" << std::endl;
	std::cout << "|effectiveness of the hash-function being used, this too can be changed if   |" << std::endl;
	std::cout << "|the user would like to change the hash function. See Options Menu.          |" << std::endl;
	std::cout << "|The user can enter a sentence, word, or paragraph(s) in the Spell Check Menu|" << std::endl;
	std::cout << "|the input is then checked for spelling errors. An error is determined if the|" << std::endl;
	std::cout << "|word is not in the current directory. The user will then have the option to |" << std::endl;
	std::cout << "|add the misspelled word to the director. Additionally, the user can move    |" << std::endl;
	std::cout << "|forward to view suggessted words similar to the one they entered but in the |" << std::endl;
	std::cout << "|current directory. The user can seem 1-edit words and 2-edit words, after   |" << std::endl;
	std::cout << "|they must enter a correction, either a valid word or a word from the shown  |" << std::endl;
	std::cout << "|lists. The user can also check information about particular words such as   |" << std::endl;
	std::cout << "|their hash's, the list that a word is an element of, and more.              |" << std::endl;
	std::cout << "|Defaults in the program can be changed in the Options Menu.                 |" << std::endl;
	std::cout << "------------------------------------------------------------------------------" << std::endl;
}