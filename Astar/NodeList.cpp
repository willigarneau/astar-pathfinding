#include "NodeList.h"

NodeList::NodeList()
{
}


NodeList::~NodeList()
{
}

void NodeList::Add(Node * pNode)
{	
	std::vector<Node*>::iterator it;
	for (it = _NodeList.begin(); it < _NodeList.end() && (*it)->F() < pNode->F() ; it++) {

	}
			
	_NodeList.insert(it, pNode);
}

void NodeList::Remove(Node * pNode)
{
	std::vector<Node*>::iterator node2remove = std::find_if(_NodeList.begin(), _NodeList.end(), [pNode](const Node* m) -> bool { return m->Pos.x == pNode->Pos.x && m->Pos.y == pNode->Pos.y;  });
	if (node2remove != _NodeList.end())
		_NodeList.erase(node2remove);
}

void NodeList::Replace(Node * pNode, int pIndex)
{
	/*std::vector<Node*>::iterator node2remove = std::find_if(_NodeList.begin(), _NodeList.end(), [pNode](const Node* m) -> bool { return m->Pos.x == pNode->Pos.x && m->Pos.y == pNode->Pos.y;  });
	if (node2remove != _NodeList.end()) {
		_NodeList.erase(node2remove);
		delete *node2remove;
	}*/
		
	std::vector<Node*>::iterator node2remove = _NodeList.begin() + pIndex;
	_NodeList.erase(node2remove);

	this->Add(pNode);
}

bool NodeList::IsEmpty()
{
	return _NodeList.empty();
}

bool NodeList::Contains(Node * pNode)
{
	bool found = false;

	for (auto &node : _NodeList) // access by reference to avoid copying
	{
		if (node->Pos.x == pNode->Pos.x && node->Pos.y == pNode->Pos.y) {
			found = true;
			break;
		}
			
	}

	return found;
}

Node * NodeList::LowestScore()
{
	/*
	//	choose the lowest F score from all nodes on the open list
	Node* lowest = nullptr;

	for (std::vector<Node*>::iterator it = _NodeList.begin(); it != _NodeList.end(); it++) {
		if (it == _NodeList.begin()) //	first element
			lowest = *it;

		int fScore = (*it)->F();
		//	if there is nodes with the same score, we choose the last one added to the open list
		//  it doesn’t really matter. (Differing treatment of ties is why two versions of A* may find different paths of equal length.)
		if (fScore <= lowest->F())
		{
			lowest = *it;
		}
	}
	return lowest;
	*/

	Node* lowest = _NodeList.front();
	_NodeList.erase(_NodeList.begin());

	return lowest;
}

Node * NodeList::Find(Node* pNode, int* pIndex)
{
	std::vector<Node*>::iterator node2remove = std::find_if(_NodeList.begin(), _NodeList.end(), [pNode](const Node* m) -> bool { return m->Pos.x == pNode->Pos.x && m->Pos.y == pNode->Pos.y;  });
	
	*pIndex = node2remove - _NodeList.begin();
	return *node2remove;
}
