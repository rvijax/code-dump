//============================================================================
// Name        : TryTrie.cpp
// Author      : Vijay Rajakumar
// Version     :
// Copyright   : Oct 29,2009
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <set>
#include <vector>
#include "Trie.h"
#include "array.h"
#include "DictHash.h"
#include <string>
#include <cstring>
#include "output.h"

#include "Rank.h"

using namespace std;

int main() {

	map<string,long> wordDictionary;
	vector<string> invDictionary;
	vector<string> recordList;
	vector<list<long> > dataSet;
	Trie *T=new Trie();
	Rank *RankHandle=new Rank();

	getDictHash(wordDictionary,invDictionary,dataSet,recordList,*T,RankHandle->rankList);

	//serialize
//	string outFileName;
//	outFileName.append("/home/vijay/workplace/Resources/recordList.txt");
//	if(existFile(outFileName)){
//			writeString(recordList,outFileName);
//	}

	string inputQuery;
	vector<string> queryTokens;
	set<long> result;
	set<long>::const_iterator aIter;
	list<long> query;
	vector<string>::const_iterator qIter;
	vector<string> tempSet;
	vector<string>::iterator tempSetIter;

	bool whileIter=true;
	list<long> it;
	list<long>::iterator itIter;

	list<long> finalOutput;
	list<long>::iterator outIter;

	int counter;
	multimap<long,list<long>*, greater<long> > pq;
	multimap<long,list<long>*, greater<long> >::iterator pqIter;

	list<long> tmp;
	list<long>::iterator tmpIter;

	while(whileIter==true){
		int option=2;
		cout<<"options: 1.query Trie\t2.quit\t ENTER option:"<<endl;
		cin>>option;
		switch(option)
		{
		case 1:
			inputQuery.clear();
			query.clear();
			cout<<"enter query:";
			cin.ignore( 1000, '\n' );
			getline(std::cin,inputQuery);
			queryTokens.clear();
			Tokenize(inputQuery,queryTokens," ");

			for(qIter=queryTokens.begin();qIter!=queryTokens.end();qIter++){
				query.push_back(wordDictionary[(string)*qIter]);
			}
			result.clear();
			T->queryWord2Result(query,result);

			counter=0;
			//top k by merge_sort_list
			for(aIter=result.begin();aIter!=result.end();aIter++){
				it=dataSet[*aIter];
				if (it.empty())
					continue;
				tmpIter=it.begin();
				pq.insert(pair<long,list<long>* >(RankHandle->rankList[*tmpIter],&it));
				//cout<<RankHandle->rankList[*tmpIter]<<"ii->"<<*tmpIter<<endl;
			}

			while (!pq.empty() && counter<5) {
						counter++;
						pqIter=pq.begin();

						std::list<long> *p = pqIter->second;
						pq.erase(pq.begin());

						//finalOutput.push_back(p->front());
						//cout<<RankHandle->rankList[p->front()]/1000<<"->";
						cout<<recordList[p->front()]<<endl;

						p->pop_front();

						if (!p->empty())
								tmpIter=p->begin();
								pq.insert(pair<long,list<long>* >(RankHandle->rankList[*tmpIter],p));
			}

			break;
		case 2:
			whileIter=false;
			break;
		default:
			whileIter=false;
		}
	}

	delete T;
	wordDictionary.clear();
	invDictionary.clear();
	query.clear();
	result.clear();

	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	return 0;
}



