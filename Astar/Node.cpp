#include "Node.h"

Node::Node()
{

}

Node::Node(cv::Point pPoint, Node * pParent)
{
	Pos = pPoint;
	Parent = pParent;
}

int Node::F()
{
	return G + H;
}

void Node::CalculateH(Node * pEnd)
{
	H = (abs(Pos.x - pEnd->Pos.x) + abs(Pos.y - pEnd->Pos.y)) * 10;
}

bool Node::Equals(Node * pNode)
{
	return (Pos.x == pNode->Pos.x && Pos.y == pNode->Pos.y);
}
