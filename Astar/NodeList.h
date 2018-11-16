#pragma once

#include <iostream>
#include <vector>
#include "Node.h"

using namespace std; // shouldnt be done 

class NodeList
{
public:
	NodeList();
	~NodeList();

	void Add(Node* pNode);
	void Remove(Node* pNode);
	void Replace(Node* pNode, int pIndex);

	bool IsEmpty();
	bool Contains(Node* pNode);

	Node* LowestScore();
	Node* Find(Node* pNode, int* pIndex);
private:
	vector<Node*> _NodeList;
};

