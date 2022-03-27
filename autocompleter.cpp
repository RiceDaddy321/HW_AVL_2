#include "autocompleter.h"

// Creates a new Autocompleter with an empty dictionary.
//
// Must run in O(1) time.
Autocompleter::Autocompleter()
{
	root = new Node();
	count = 0;
}

// Adds a string x to the dictionary.
// If x is already in the dictionary, does nothing.
//
// Must run in O(1) time.
void Autocompleter::insert(string x, int freq)
{
	//pointer to root for traversing through the trie
	Node* iptr = root;

	//for empty string
	//setup babyEntry
	Entry babyEntry;
	babyEntry.s = x;
	babyEntry.freq = freq;
	bool inserted = false;

	//add to the vector
	for (auto it = iptr->top.begin(); it < iptr->top.end(); it++)
	{
		if (babyEntry.freq > it->freq)
		{
			iptr->top.insert(it, babyEntry);
			inserted = true;
			break;
		}
	}

	if (!inserted)
		iptr->top.push_back(babyEntry);


	//check if the size is greater than 3; it should not be greater than 4
	if (iptr->top.size() > 3)
	{
		iptr->top.pop_back();
	}

	//let's first traverse to the location to where the string could be inserted
	for (int i = 0; i < x.size(); i++)
	{
		if (iptr->children[x[i]] == nullptr)
			iptr->children[x[i]] = new Node;

		iptr = iptr->children[x[i]];

		//start of adding to top three vector -----------
		//setup babyEntry
		Entry babyEntry;
		babyEntry.s = x;
		babyEntry.freq = freq;
		inserted = false;

		//add to the vector
		for (auto it = iptr->top.begin(); it < iptr->top.end(); it++)
		{
			if (babyEntry.freq > it->freq)
			{
				iptr->top.insert(it, babyEntry);
				inserted = true;
				break;
			}
		}

		if(!inserted)
			iptr->top.push_back(babyEntry);

		//check if the size is greater than 3; it should not be greater than 4
		if (iptr->top.size() > 3)
		{
			iptr->top.pop_back();
		}

	}

	//check if already in the trie for safekeeping
	if (iptr->marked)
		return;

	//mark final position of word
	iptr->marked = true;

	//finally, increment number of strings
	count++;
}

// Returns the number of strings in the dictionary.
// 
// Must run in O(1) time.
int Autocompleter::size()
{
	return count;
}

// Fills the vector T with the three most-frequent completions of x.
// If x has less than three completions, then 
// T is filled with all completions of x.
// The completions appear in T from most to least frequent.
// 
// Must run in O(1) time.
void Autocompleter::completions(string x, vector<string>& T)
{
	T.clear();
	//pointer to root for traversing through the trie
	Node* iptr = root;

	//let's first traverse to the location to where the string could be
	for (int i = 0; i < x.size(); i++)
	{
		if (iptr->children[x[i]] == nullptr)
			return;

		iptr = iptr->children[x[i]];
	}

	for (Entry e : iptr->top)
		T.push_back(e.s);


}