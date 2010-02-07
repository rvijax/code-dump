/*
 * Trie.h
 *
 *  Created on: Nov 3, 2009
 *      Author: vijay
 */

#ifndef TRIE_H_
#define TRIE_H_

#include "array.h"
#include "TrieNode.h"
#include "assert.h"
#include <vector>
#include "stdlib.h"
#include <set>
#include<list>
using namespace std;

class Trie{
public:
	TrieNode* root;
	Trie();
	virtual ~Trie();
	void AddToTrie(const list<long> &in,const long &docID);

	void queryWord2Result(list<long> &queryword,set<long> &result);
	void checkEndFlag(TrieNode *root,set<long> &result);
	void oneNode2Result(TrieNode *node, set<long> &result);

};


#endif /* TRIE_H_ */
