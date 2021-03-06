/*
 * Trie.cpp
 *
 *  Created on: Nov 3, 2009
 *      Author: vijay
 */

#include "Trie.h"

Trie::Trie(){
	this->root=new TrieNode;
}

Trie::~Trie(){
	delete this->root;
}



void Trie::AddToTrie(const list<long> &in,const long &docID)
{
	list<long>::const_iterator iter;
    TrieNode *t = root;
    unsigned long index;
    for(iter=in.begin();iter!=in.end();iter++){
    	if(t->keys.has(*iter)){
    		t=t->child[t->keys.binarySearch(*iter)];
    	}
    	else{
    		TrieNode *tmp=new TrieNode;
    		tmp->setParent(t);
    		tmp->name=*iter;
    		index=t->keys.insert(*iter);
    		t->child.insert(index,tmp);
			t->count++;
			t=t->child[index];
    	}
    }
    t->setEndFlag(true,docID);
}

void Trie::queryWord2Result(list<long> &queryword,set<long> &result){
	list<long>::const_iterator iter;
	TrieNode *t = root;
	for(iter=queryword.begin();iter!=queryword.end();iter++){
		//cout<<*iter<<endl;
	   	if(t->keys.has(*iter)){
	   		//cout<<*iter<<endl;
	   		t=t->child[t->keys.binarySearch(*iter)];
	   	}
	   	else{
	   		return;
	   	}
	}
	oneNode2Result(t,result);
}

void Trie::checkEndFlag(TrieNode *node,set<long> &result){
	if(node->getEndFlag()){
		//cout<<"added"<<endl;
//		result.push_back(node->forwardList);
		//cout<<node->forwardList<<endl;
		Array<long>::iterator fIter;
		for(fIter=node->forwardList.begin();fIter!=node->forwardList.end();fIter++){
			result.insert(*fIter);
		}
	}
}

void Trie::oneNode2Result(TrieNode *node, set<long> &result){
	unsigned i;
	//cout<<"was here1";
	checkEndFlag(node,result);
	if(node->count==0){
		return;
	}
	else{
		//int counter = 0;
		for(i=0; i < node->child.size(); i++){
			//append(result, node->name);
			if(node->child[i] != NULL)
			{
				oneNode2Result(node->child[i], result);
			//	counter++;
			}
		}
	}
	return;
}

