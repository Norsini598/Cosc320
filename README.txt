Lab 7: Hash Functions ReadMe:
Programmer: Nicholas Orsini
-----------------------------
For this lab the task was to make at least 3 hashing functions. 1 for numerics and 2 for string
variables. The numeric hash I followed as instructed, I think. 
The string hashes were more fun to code as there was freedom and flexibility. Both hashing 
functions I implemented took inspiration from the polynomial rolling hash function. The first
one goes through the array element by element (O(n)). It multiples the difference between that
character in the string from the ascii value of character 'a' as it is the first by a changing
multiple variable who is dependent on two internal prime variables and its past self. The other
string hash function attacks the string from the front and back at the same time so it only has
to loop through a total of half the string. The function take the sum of these characters of their
differences from 'a' and does a similar method but with different internal variables. This hash I
noticed was consistently larger than the former. At around ~35 characters it would overflow. So if
the input has a length greater than 30 characters the string is hashed using substrings of length 10.
So if the input is 42 characters long there will be 5 separate hashes that are combined into a single
hash by multiplying one with another taking their modulus on a large prime number shifted to the right
by 1 byte and summing that result to the overall hash value. Repeat this step with the 3 remaining
substring hashes. 

The user can elect to print the linked list values in hexadecimal if they so please by turning the 
option on in the options menu. For some reason when I would "std::hex << num << " it would convert
all outputs to hexadecimal form, even those not on the same line and separated by ";"'s. I didn't 
like this so the solution I made was to make hexadecimal print be an option. 

I did not want to do my finance homework so I created HashTables by implementing a singly-linked
list. Each Hash Table is an array of 10 linked lists. After a value is hashed it is added to its
respective hash table and the hash table stores its actual value (string, int, etc.) and its 
hash value.

Why does the integer hash function make sense:
	Characteristics of a good hash function:
		1. Fully determined by the data being hashed (deterministic)
		2. Function uses all the input data (not half of the string)
		3. Uniformly distributed
		4. Very different hashes for similar inputs
The hash function satisfies these 4 criteria by utilizing the "Division Method". a*x % W creates a
unique output due to the scale of W and a being prime make the output unique and uniform across all
W. This result is the shifted to the right by (w-p) bytes to ensure within bounds. 
Prime numbers minimize collisions because number theory apparently because they have a smaller
probability of sharing common factors which means less collisions. 


Improvements that can be made:
	The segement where I hash for every implemented StringHash I have a series of conditions
that determine which function to use to hash. Instead I should have create a function pointer array
so that I could have used the same i in the loop to just take the hash. If there were 10+ 
implemented hash functions its clear how what is implemented would get annoying.