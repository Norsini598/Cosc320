Lab 8 README
For this lab I create a templated binary search tree by utilizing the class "BinaryTree" and the
struct "TreeNode". You will see the my TreeNode is not an innver private struct like the suggested.
My reason for this is that expand the use of TreeNode, i.e operator overloads: <, >, =, I tried << but
for some reason I was having linking issues with the template friend function. I had:
friend std::ofstream& operator<<(std::ofstream&, const TreeNode<T>&); and then the implemenations declared as:
template<typename T> _ std::ofstream& operator<<(std::ofstream& os, const TreeNode<T>& obj){. . . return os;}
Anyways, a binary tree is just a tree of TreeNode nodes. The user has the ability to add and remove as 
many elements as they'd like. For inserting I allowed the user the ability to insert as many elements as
they'd like in bulk, but they can also just add one node too if they so choose. As for deleting the
user has the choice to delete a single element or the whole tree (i implemented this for the sake of
data collection on deleting a binary search tree). At first there were no restrictions on what elements
can go into the tree. But when beginning my time analysis I noticed that around ~75000 elements the time
 to delete and insert began to go down due to duplicants not needing to be added to the tree, just
their count increments. Then after this I added in the options menu the ability to allow or disallow 
duplicant values. By default duplicants are not allowed- for this reason inserting in bulk takes a
very very long time (WARNING) since it randomizes a value until it is unique. The way I implemented 
this was very plain and due to the long time an improvement to the code would be to find a smarter way
garuntee uniqueness- maybe take the hashes of the values 1 to n, n ∈ Q. Then build the binary tree using
their hash values. If not unqiue after that just hash those hashes until all unique. 
-----
The way I timed my insert was as such: randomize a value, try to insert it, if it is the same as a value
in there previously break out before reaching a leaf position and discard that time and try again until
there are the requested number of unique values. On export of insertion, I export the number of nodes in
the tree before the most recent insertion and the time to insert the newest node. I was expecting to see
a clearer relationship but it looks too stable hovering around .005ish with exceptions. I am not sure if
insertion should be timed differently. The way I did it: start timer just after set up, loop through until
finding the NULL lead that the node will be inserted into. Insert and then stop the timer, export result. 
But it does not look accurate. 

For deletion I timed the two functions "EmptyTree" and "~BinaryTree()"- they both are the the same. The way
I wrote my deconstructor I expected something of the nature of O(n!) because for some reason I was thinking 
it had to visit every node each time where n is decreasing each time. n(n-1)(n-2)...(n-n-1). But haha thats
me being dumb at the time and thinking it was a list--- that's worst case scenario. So yes it is O(n!)
but I have not tested the worst case, I'll go back and do that hopefully. But θ would be based on a random 
function since order matters and the way the tree is filled is randomly. Best case would be an evenly
distributed tree in which it would have runtime O(log_2n).

I think the data doesn't match these because I tested the random case scenarios instead- but still their
probability would gravitate toward theory as randomized Quicksort did. So I am confused by my results.

Improvements (may be made in time):
InsertValueTypeMenu();
	Manual
	Random
	List  (Worst Case)
	Hashes
	Cancel

