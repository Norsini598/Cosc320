#include <iostream>
#include <string>

namespace UtilityFunctions {

	//calculate how long a given string is
	int CalculateStringLength(std::string);
	//return the string up to the first space (take off first word
	std::string ParseString(int, std::string, int = 0);
	//how many words are in the string
	int CalculateSpaces(std::string);
	//remove punctuation ? , . ! ;
	std::string RemovePunctuation(std::string);
	//remove punctuation followed by spaes
	void RemoveSentencePunctuation(std::string&);
	//make a string all lowercase
	void MakeLower(std::string&);
	//remove all duplicant words in a list
	void RemoveDuplicant(std::string&);
	//given an index return the inex of the next space
	int ReturnNextSpaceIndex(int, std::string);
	//if a string is in a list of string return true
	bool IsWithin(std::string, std::string);
	//return the index of one word begins from in a list of words or return -1 if not there
	int WhereamI(std::string, std::string);
	//the word beginning at i is replaced by a word brought in
	void Replace(std::string&, std::string, int); 
	//remove the character at a given index and overwrite the string wihout it
	void RemoveCharacter(int, std::string&);

	//**************************************************************\\

	int CalculateStringLength(std::string s) {
		int length = 0;
		while (s[length] != '\0')
			length++;
		return length;
	}

	//take first word off of a string
	std::string ParseString(int end, std::string input, int start) {
		std::string word = "";
		int i = start;
		while (input[i] != ' ' && input[i] != '\0') {
			word += input[i];
			i++;
		}
		//either reahed a space or the end
		//if reached end remove puncuation at the end of the word.
		//check if there is puncuation. can assume non letter at end it puncuation
		if (input[i] == '\0') {
			if (!((input[i - 1] > 64 && input[i - 1] < 91) || ((input[i - 1]) > 96 && input[i - 1] < 123)))
				RemoveCharacter(CalculateStringLength(word)-1, word);
		}
		return word;
	}

	//how many words in a string
	int CalculateSpaces(std::string input) {
		int i = 0;
		int words = 0;
		//if not empty string there is at least 1 word
		if (input != "" || input != " ")
			words++;
		while (input[i+1] != '\0') {
			if (input[i] == ' ' && input[i+1] != ' ')
				words++;
			i++;
		}
		return words;
	}

	//modify a string so that it does not contain any , . ? ! and others upon realizations
	std::string RemovePunctuation(std::string input) {
		int i = 0;
		std::string copy = "";
		while (input[i] != '\0') {
			if (input[i] == '!' || input[i] == '.' || input[i] == ',' || input[i] == '?')
				i++; //skip all punctuations
			else
				copy += input[i++];
		}
		return copy;
	}

	//modify a string so that all sentene sparating punctuations are removed. For instance,\
	The cat is, at home? --> The cat is at home
	void RemoveSentencePunctuation(std::string& input) {
		int i = 0;
		std::string copy = "";
		while (input[i+1] != '\0') {
			if(input[i+1] == ' ' && (input[i] == '!' || input[i] == '.' || input[i] == ',' || input[i] == '?'))
				i++; //skip that punctuations
			else
				copy += input[i++];
		}
		//now at last character- there is a chance the user didnt finish their sentence with puncutation
		if (!(input[i] == '!' || input[i] == '.' || input[i] == ',' || input[i] == '?'))
			copy += input[i];
		input = copy;
	}

	//take a string return the same string but all it values are lowercased
	void MakeLower(std::string& input) {
		int i = 0;
		while (input[i] != '\0') {
			//if an uppercased letter exists make it lower cased
			if (input[i] > 64 && input[i] < 91)
				input[i] += 32;
			i++;
		}
	}

	void RemoveDuplicant(std::string& input) {
		//pass in a list, there may be many of the same word on the list, remove all those duplicates.
		//MakeLower(input);

		int strlen = CalculateStringLength(input);
		int spaces = CalculateSpaces(input); //number of spaces = number of words-2
		int words = CalculateSpaces(input); //number of words in the list
		std::string compareword = "";
		std::string edit = "";

		int start = 0;
		int spaceindex = 0;
		
		std::string SWords[words];
		//put all the words in input into an array
		for (int i = 0; i < words; i++) {
			SWords[i] = ParseString(strlen, input, start);
			start += CalculateStringLength(SWords[i]) + 1;
		}
		for (int i = 0; i < words; i++)
		{
			for (int j = i + 1; j < words; j++)
				if (SWords[i] == SWords[j]) //DUPLICANT!!!!!!
					//replace the jth word with "" (empty string)
					SWords[j] = "";
		}
		//now rebuild the string
		input = "";
		for (int i = 0; i < words; i++) {
			if (SWords[i] != "")
				input += SWords[i] + " ";
		}

		//Give:\
		"apple captain cap apple square ball captain"\
		"apple captain cap square ball captian"\
		becomes:\
		apple captain cap square ball
	}

	int ReturnNextSpaceIndex(int start, std::string input) {
		//start is the index we are at: gnats_suck_. 2 passed in 5 returned
		int i = 0;
		//move to next space or end
		while (input[start + i] != ' ' && input[start + i] != '\0')
			i++;
		return (start + i);//if = strlen then we know its to the end
	}

	void RemoveCharacter(int i, std::string& input) {
		std::string copy = "";
		for (int j = 0; j < CalculateStringLength(input); j++) {
			if (i == j)
				continue; //skip this character
			else
				copy += input[j];
		}
		input = copy;
	}

	bool IsWithin(std::string List, std::string input) {
		bool r = false;
		int len = CalculateStringLength(List);
		int len2 = 0;

		int words = CalculateSpaces(List); //number of words in list
		for (int i = 0; i < words; i++) {
			std::string com = ParseString(len, List, len2); //take off a word in the list
			len2 += CalculateStringLength(com) + 1;
			if (com == input) {
				r = true;
				break; //no point to keep looking
			}
		}
		return r;
	}

	int WhereamI(std::string List, std::string input) {
		//if the word is in the list return the index of where it begins
		//Ex. Cat Hat Bat What Gnat.   Input: Gnat
		//returns: 17
		int r = -1;
		int len = CalculateStringLength(List);
		int len2 = 0;

		int words = CalculateSpaces(List); //number of words in list
		for (int i = 0; i < words; i++) {
			std::string com = ParseString(len, List, len2); //take off a word in the list
			//check bfore moving iteration forward
			if (com == input) {
				r = len2;
				break; //no point to keep looking
			}
			len2 += CalculateStringLength(com) + 1; //move to the next word
		}
		return r;
	}

	void Replace(std::string&host, std::string parasite, int i) {
		/*Get the word in host beginning at i
		parasite attack the string at i, kills the community there, and reporulates it with itself.		
		*/
		//1 Get word at host[i]
		int nextspace = ReturnNextSpaceIndex(i, host);
		int hostlen = CalculateStringLength(host);

		//std::string oldword = ParseString(0, host, i);

		std::string BeforeIhalf = "";
		for (int j = 0; j < i; j++) {
			BeforeIhalf += host[j];
		}
		std::string AferIHalf = "";
		for (int j = nextspace; j < hostlen; j++) {
			AferIHalf += host[j];
		}
		//rebuild host.
		host = BeforeIhalf;
		host += parasite;
		host += AferIHalf;
	}

}
