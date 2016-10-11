#include "Companies.h"

int characterToIndex(char c)
{
	return (int)c - (int)'a';
}
int capitalToIndex(char c)
{
	return (int)c - (int)'A';
}

class TrieNode
{
public:
	vector<Company*> VectorInTree;
	TrieNode* children[26];

	TrieNode()
	{
		for (int i = 0; i < 26; i++)
			children[i] = 0;
	}
};

class Trie
{
public:
	TrieNode *root;
	Trie()
	{
		root = new TrieNode();
	}

	~Trie()
	{}

	void insert(Company* company, string key)
	{
		int length = key.size();
		int level;
		int index;
		TrieNode *Inserted = this->root;
		for (level = 0; level < length; level++)
		{
			if (level == 0)
				index = capitalToIndex(key[level]);
			else
				index = characterToIndex(key[level]);
			if (!Inserted->children[index])
			{
				TrieNode *temp = new TrieNode();
				Inserted->children[index] = temp;
			}
			Inserted = Inserted->children[index];
		}
		Inserted->VectorInTree.push_back(new Company());
		Inserted->VectorInTree[Inserted->VectorInTree.size() - 1] = company;
	}

	

	bool search(string key)
	{
		bool found = false;
		int level;
		int length = key.size();
		int index;
		TrieNode* SearchTerm = this->root;
		for (level = 0; level < length; level++)
		{
			if (level == 0)
				index = capitalToIndex(key[level]);
			else
				index = characterToIndex(key[level]);
			if (!SearchTerm->children[index])
				return false;
			SearchTerm = SearchTerm->children[index];
		}
		for (int i = 0; i < SearchTerm->VectorInTree.size(); i++) 
		{
			cout << key + " works for " + SearchTerm->VectorInTree[i]->title << endl;
			found = true;
		}
		return found;
	}
};



