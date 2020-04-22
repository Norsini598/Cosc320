#include "HashTable.h"
#include "Colors.h"
#include <chrono>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <math.h>

template<typename T>
HashTable<T>::HashTable() {
	BiggestBucket = 0;
	BiggestCount = 0;
	BiggestBucketTime = 0;

	SmallestBucket = 0;
	SmallestCount = 0;
	SmallestBucketTime = 0;

	EmptyTime = 0;

	load = 0;
	uniqueload = 0;

	HF = 1;
	HashingFunction = ComputeHashString1;

	StndevTime = 0;
}

template<typename T>
HashTable<T>::~HashTable() {

	//No pointers. 
}

//Adding Nodes:
template<typename T>
void HashTable<T>::AddNode(T d) {
	//build a node from some data
	Node<T> NewNode;
	NewNode.data = d;
	NewNode.hashvalue = HashingFunction(d);
	NewNode.next = NULL;
	//pass the node into the proper list where it is then added to the linked list.

	if (table[NewNode.hashvalue].IsEmpty())
		uniqueload++;
	load++; //regardless of above the load is incremented

	table[NewNode.hashvalue].AddNode(NewNode);
}
template<typename T>
void HashTable<T>::operator+(const T d) {
	//build a node from some data
	Node<T> NewNode;
	NewNode.data = d;
	NewNode.hashvalue = HashingFunction(d);
	NewNode.next = NULL;
	//pass the node into the proper list where it is then added to the linked list.

	if (table[NewNode.hashvalue].IsEmpty())
		uniqueload++;
	load++; //regardless of above the load is incremented

	table[NewNode.hashvalue].AddNode(NewNode);
	//dictionary + cat
}

//Printing:
/*
template<typename T>
std::ostream& operator<<(std::ostream& os, const HashTable<T>& obj)
{
	os << "    Hash Table Summary:    " << std::endl;
	os << "---------------------------" << std::endl;
	os << "| Elements in Hash Table:  " << obj.load << std::endl;
	os << "| Cells in Hash Table:     " << HashTableSize << std::endl;
	os << "| Number of Used Buckets:  " << obj.uniqueload << std::endl;
	os << "| Load Factor:             " << std::setprecision(3) << obj.CalcualteAverageBucketSize() << std::endl;
	os << "|--------------------------" << std::endl;
	os << "| Largest Bucket Size:     " << obj.BiggestBucket << std::endl;
	os << "| # Cells like this:       " << obj.BiggestCount << std::endl;
	os << "| Time to Calcualte:       " << std::setprecision(6) << obj.BiggestBucketTime << std::endl;
	os << "|--------------------------" << std::endl;
	os << "| Smallest Bucket Size:    " << obj.SmallestBucket << std::endl;
	os << "| # Cells like this:       " << obj.SmallestCount << std::endl;
	os << "| Time to Calculate:       " << std::setprecision(6) << obj.SmallestBucketTime << std::endl;
	os << "|--------------------------" << std::endl;
	return os;
}*/

template<typename T>
void HashTable<T>::PrintTableSummary() {
	if (BiggestBucket == 0) {
		CalculateBiggestBucketSize();
		CalculateSmallestBucketSize();
	}
	std::cout << GREEN << "          Hash Table Summary:        " << std::endl;
	std::cout << "-------------------------------------" << DEFAULT << std::endl;
	if (HF < 10)
		std::cout << "|            Hash Function #" << HF << "    " << std::endl;
	std::cout << "| Elements in Hash Table:  " << load << std::endl;
	std::cout << "| Cells in Hash Table:     " << HashTableSize << std::endl;
	std::cout << "| Number of Used Cells:    " << uniqueload << std::endl;
	std::cout << "| Load Factor:             " << std::setprecision(3) << CalcualteAverageBucketSize() << std::endl;
	std::cout << "-------------------------------------" << std::endl;
	std::cout << "| Standard Deviation:      " << std::setprecision(6) << StandardDeviationOfItemDisplacement() << std::endl;
	std::cout << "|   of cell spread.        " << std::endl;
	std::cout << "| Time to Calculate: " << std::setprecision(6) << StndevTime << std::endl;
	std::cout << "-------------------------------------" << std::endl;
	std::cout << "| Largest Bucket Size:     " << BiggestBucket << std::endl;
	std::cout << "| # Cells like this:       " << BiggestCount << std::endl;
	std::cout << "| Time to Calculate:       " << std::setprecision(6) << BiggestBucketTime << std::endl;
	std::cout << "-------------------------------------" << std::endl;
	std::cout << "| Smallest Bucket Size:    " << SmallestBucket << std::endl;
	std::cout << "| # Cells like this:       " << SmallestCount << std::endl;
	std::cout << "| Time to Calculate:       " << std::setprecision(6) << SmallestBucketTime << std::endl;
	std::cout << "-------------------------------------" << std::endl;
	std::cout << "| Hash Function Score:  " << std::fixed << std::setprecision(9) << CalcualteHashFunctionRank() << std::endl;
	std::cout << "-------------------------------------" << std::endl;
}

template<typename T>
void HashTable<T>::PrintSinlgeList(T d) {
	table[HashingFunction(d)].PrintList(); //prints the whole list.
}

//Resetting:
template<typename T> //remove all elements from the hash table doesnt resize the table! just empties it
void HashTable<T>::EmptyTable()
{
	auto start = std::chrono::system_clock::now(); //set the timer for clearing the hashtable

	for (int i = 0; i < HashTableSize; i++)
		//ifn not an empty list
		if (!table[i].IsEmpty())
			table[i].EmptyList();
	//finished clearing
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;
	std::time_t end_time = std::chrono::system_clock::to_time_t(end);
	EmptyTime = elapsed_seconds.count();

	//doesnt reset data outside the table-- needed for print out
}

template<typename T> //change the hashing function. data mush be dumped in such data will be written to a file
void HashTable<T>::ChangeHashFunction()
{
	//Change hash function menu.
	//yes, this is menu but not in menus.h, this one is different and isolated I suppose
	int violation = 0; //number that will not be allowed to enter
	int entry = 0;
	bool stop = false;
	int HFold = HF;
	do {
		//make sure the type is of type string- avoid this check by employing this isn dictionary maybe?
		//String Types
		if (std::is_same<T, std::string>::value) {
			//find current hash function
			std::cout << "Current Hash Function: ";
			if (HF == 1) {
				std::cout << "#1" << std::endl;
				violation = 1;
			}
			else if (HF == 2) {
				std::cout << "#2" << std::endl;
				violation = 2;
			}
			std::cout << "----------------------------------" << std::endl;
			std::cout << "|    Change Hash Function Menu   |" << std::endl;
			std::cout << "|  Select a corresponding Option |" << std::endl;
			for (int i = 0; i < stringhashes; i++)
			{
				if (violation == i + 1) //skip this option
					continue;

				std::cout << "| " << i + 1 << ". Hash Funcion #" << i + 1 << std::endl; //last one is stringhashes
			}
			std::cout << "| " << stringhashes + 1 << ". Return to Options Menu    " << std::endl; //last option in this menu.
			std::cout << "| Make Input: ";
			std::cin >> entry;
			//if valid entry 
			if (entry > 0 && entry < stringhashes + 2 && entry != violation) //while entry is in valid range and the entry is not the currently implemented\
			hash function and that entry is not the current hash function
				stop = true;
		}
		//Add other types of hash tables types.
	} while (!stop);

	//now set the new and proper hashfunction
	if (entry != stringhashes + 1) { //if not return to menu.
		if (entry == 1) {
			HashingFunction = ComputeHashString1;
			HF = 1;
		}
		else if (entry == 2) {
			HashingFunction = ComputeHashString3;
			HF = 2;
		}

		//now the current table needs to be emptied and then refilled but that last part will be taken care of else where.
		//erste ein datie geoffent werden.
		std::ofstream Out;
		Out.open("TableSummary.txt", std::ios::app);

		EmptyTable(); //empty the table. Then, output the table's data

		Out << HFold << ", " << load << ", " << HashTableSize << ", " <<  uniqueload << ", " << BiggestBucket << ", " << BiggestCount << ", " << BiggestBucketTime <<
			", " << SmallestBucket << ", " << ", " << SmallestCount << ", " << SmallestBucketTime << ", " << EmptyTime << ", " << StndevTime << std::endl;

		ResetVariables();

		Out.close(); //schliesse die datie.
	}
}

//-------------------------------------------------
//Calulations:
template<typename T>
void HashTable<T>::CalculateBiggestBucketSize() {
	//reset key variables
	BiggestBucketTime = 0;
	BiggestBucket = 0;
	BiggestCount = 0;

	//start a timer
	auto start = std::chrono::system_clock::now(); //set the timer for clearing the hashtable

	BiggestBucket = table[0].GetNodesInList();
	BiggestCount++; //1

	//search the rest of the table
	for (int i = 1; i < HashTableSize; i++) {
		//reset biggest bucket
		if (BiggestBucket < table[i].GetNodesInList()) {
			BiggestBucket = table[i].GetNodesInList();
			BiggestCount = 1; //reset at 1
		}
		else if (BiggestBucket == table[i].GetNodesInList())
			BiggestCount++;
		//if biggestbucket is greater do nothing
		else
			continue;
	}
	//finished finding biggest bucket
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;
	std::time_t end_time = std::chrono::system_clock::to_time_t(end);
	BiggestBucketTime = elapsed_seconds.count();
}

template<typename T>
void HashTable<T>::CalculateSmallestBucketSize() {
	//reset key variables
	SmallestBucketTime = 0;
	SmallestBucket = 0;
	SmallestCount = 0;

	//start a timer
	auto start = std::chrono::system_clock::now(); //set the timer for clearing the hashtable

	SmallestBucket = table[0].GetNodesInList();
	SmallestCount++; //1

	//search the table
	for (int i = 1; i < HashTableSize; i++) {
		//reset biggest bucket
		if (SmallestBucket > table[i].GetNodesInList()) {
			SmallestBucket = table[i].GetNodesInList();
			SmallestCount = 1; //reset at 1
		}
		else if (SmallestBucket == table[i].GetNodesInList())
			SmallestCount++;
		//if smallestbucket is lesser do nothing
		else
			continue;
	}

	//end the time. finished searching for smallest bucket(s)
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;
	std::time_t end_time = std::chrono::system_clock::to_time_t(end);
	SmallestBucketTime = elapsed_seconds.count();
}

template<typename T>
float HashTable<T>::CalcualteAverageBucketSize() {
	return ((1.0 * load) / (1.0 * HashTableSize)); //i.e the load factor
}

template<typename T>
bool HashTable<T>::InList(T d) {
	size_t hash = HashingFunction(d);
	bool r = true;
	if (table[hash].IsEmpty())
		r = false;
	else
		//the hash is in that list, but now check if that specify d is in the list
		r = table[hash].InList(d);
	return r;
}

template<typename T>
float HashTable<T>::CalcualteHashFunctionRank() {
	float score = 0;
	for (int i = 0; i < HashTableSize; i++) {
		if (table[i].IsEmpty())
			score -= 100; //empty cells affect score by -100 points
		else if (table[i].GetNodesInList() > 1)
			score += (pow(basevaluescore, (1 - ((table[i].GetNodesInList()) / 100)))); //90^(1-.02) if 2 nodes so 82 points
		else
			score += 100;
	}
	score = (score / (1.0 * HashTableSize)); //average score goal is to be as close to 1
	return score;
}

template<typename T>
float HashTable<T>::StandardDeviationOfItemDisplacement() {
	//(sqrt((sum of loadat_i - loadfacot)^2)) / hahstablesize)

	//start a timer
	auto start = std::chrono::system_clock::now(); //set the timer for clearing the hashtable

	float Mean = CalcualteAverageBucketSize();
	float SumLoadSpread = 0;
	float standarddeviation = 0;
	for (int i = 0; i < HashTableSize; i++)
		SumLoadSpread += pow((table[i].GetNodesInList() - Mean), 2);
	
	SumLoadSpread /= HashTableSize;
	standarddeviation = pow(SumLoadSpread, .5);
	
	//end the time. finished searching for smallest bucket(s)
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;
	std::time_t end_time = std::chrono::system_clock::to_time_t(end);
	StndevTime = elapsed_seconds.count();

	return standarddeviation;
}

//Private Functions:
template<typename T>
void HashTable<T>::ResetVariables()
{
	//clear the stats
	EmptyTime = 0;
	load = 0;
	uniqueload = 0;
	BiggestBucket = 0;
	BiggestBucketTime = 0;
	BiggestCount = 0;
	SmallestBucket = 0;
	SmallestBucketTime = 0;
	SmallestCount = 0;
	StndevTime = 0;
}


template<typename T>
void HashTable<T>::SetHF(int H) {
	/*
	Assume called before table added- so don't output but call empty table in case
	*/
	if(H >= 1 && (H < (stringhashes+1))) {
		if (H == 1)
			HashingFunction = ComputeHashString1;
		else if (H == 2)
			HashingFunction = ComputeHashString3;
		
		EmptyTable(); //empty the table. Then, output the table's data
		
		HF = H;

		ResetVariables();
	}
}
