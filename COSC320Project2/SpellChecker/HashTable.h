#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "LinkedList.h"
#include "HashFunctions.h"

using namespace HashFunctions;

const int emptyscore = -100;
const int basevaluescore = 90;

template<typename T>
class HashTable {
	/*
	A hashtable is just an array of linked lists, but specalize in a certain type
	*/
private:
	LinkedList<T> table[HashTableSize];

	int BiggestBucket; //how many items are in the biggest bucket
	int SmallestBucket; //how many items are in the smallest bucket

	int BiggestCount; //how many cells have as many as the biggest bucket
	int SmallestCount; //how many cells have as many as the smallest bucket

	float BiggestBucketTime; //how long did it take to calculate the biggest bucket
	float SmallestBucketTime; //how long did it take to alcualte the smallest bucket

	float StndevTime;

	float EmptyTime;

	int load; //total number of units in the HashTable
	int uniqueload; //number of nodes without any elements- here just to make sure not 0.

	size_t(*HashingFunction)(T); //a function pointer that points to the currently being used string hashing function\
	is it possible to create a static function pointer? if so this should be that all HashTables would use same function.

	void ResetVariables(); //doesnt resize just make all size, count, times, loads, etc. 0; doesnt effet HF

	float CalcualteHashFunctionRank(); //scores the effectiveness of this hash function

public:
	//Public Variables:
	int HF; //indicates which hashing function is being used

	//Functions:
	HashTable();
	~HashTable();

	//Adding nodes to a list
	//void AddNode(Node<T>);
	void AddNode(T);
	void operator+(const T); //cooler way to add stuff to HashTables: Table + "cat"

	//Printing Functions
	//friend std::ostream& operator<<(std::ostream&, const HashTable<T>&); //displays the stats of the HashTable
	void PrintSinlgeList(T);//pass in a data, it gets hashed and the corresponding list in the table will be printed.
	void PrintTableSummary();

	//Stats-Related
	void CalculateBiggestBucketSize(); //calculate the size of the biggest bucket and how many buckets have this size.
	void CalculateSmallestBucketSize(); //calcualte the size of the smallest buck and how many buckets have this size.
	float CalcualteAverageBucketSize(); //nodes in table/ max number of cells

	//Resetting 
	void EmptyTable(); //empty the table, i.e delete and set all lists in the table to NULL. Called when changing a hashfunction\
	followed by rereading in dictionary in dictionary class.
	void ChangeHashFunction(); //change the hashing function being used in this hash table.

	//Search
	bool InList(const T);  //is a specific piece of data in the list. Because here is my question: if there is a colision or the likelihood\
	of a collision occuring exists then if you check the hash and its there how can you be sure its actually that value. For instance\
	say "how" and "cmdsdfs" mapped to the same value; "how" is in the table but if the user entered cmdsdfs instead well that will\
	return a word and that is no good so add both checks just in case.

	int GetBiggestBucket() { return BiggestBucket; } //how many items are in the biggest bucket
	int GetSmallestBucket() { return SmallestBucket; } //how many items are in the smallest bucket

	int GetBiggestCount() { return BiggestCount; } //how many cells have as many as the biggest bucket
	int GetSmallestCount() { return SmallestCount; } //how many cells have as many as the smallest bucket

	float GetBiggestBucketTime() { return BiggestBucketTime; } //how long did it take to calculate the biggest bucket
	float GetSmallestBucketTime() { return SmallestBucketTime; } //how long did it take to alcualte the smallest bucket

	int Getload() { return load; } //total number of units in the HashTable
	int Getuniqueload() { return uniqueload; } //number of nodes without any elements- here just to make sure not 0.

	int GetHashFunction() { return HF; }
	void SetHF(int H);

	float StandardDeviationOfItemDisplacement();

};

#endif // !HASHTABLE_H

