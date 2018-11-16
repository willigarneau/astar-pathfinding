#include "Grid.h"

Grid::Grid()
{
}


Grid::Grid(cv::Mat * pImg, cv::Point pStart, cv::Point pEnd, int pGridSize, ObjectDetection pDetector, NodeGrid pGridNode)
{
	_GridSize = pGridSize;

	_detector = pDetector;
	_gridNode = pGridNode;

	Node* end = new Node(pEnd, nullptr);
	EndNode = end;

	Node* start = new Node(pStart, nullptr);	
	StartNode = start;
}

Grid::~Grid()
{
}

// TODO if there is an obstacle with an adjacent node dont add it into the adjacent list
vector<Node*> Grid::GetCurrentNeighborList(Node * pCurrent)
{
	vector<Node*> neighborList;

	cv::Point adjacent[8] = { cv::Point(-1, -1), cv::Point(0, -1), cv::Point(1, -1), cv::Point(-1, 0), cv::Point(1, 0), cv::Point(-1, 1), cv::Point(0, 1),  cv::Point(1, 1) };
	for (int i = 0; i < 8; i++) {
		//	if adjacent node is in the grid range
		if ((adjacent[i].x + pCurrent->Pos.x) >= 0 && (adjacent[i].x + pCurrent->Pos.x) < _GridSize && (adjacent[i].y + pCurrent->Pos.y) >= 0 && (adjacent[i].y + pCurrent->Pos.y) < _GridSize) {

			Node* nodeAdjacent = new Node(cv::Point(adjacent[i].x + pCurrent->Pos.x, adjacent[i].y + pCurrent->Pos.y), pCurrent); // memory leak? NO eheh gotcha

		    // get parcel information
			Parcel parcel = _gridNode.findParcel(nodeAdjacent->Pos);		
			if(_detector.isBusy(parcel))
			{
			   delete nodeAdjacent;
			   continue;
		    }

			//	the node is diagonal to the starting node
			if (abs(pCurrent->Pos.x - nodeAdjacent->Pos.x) == 1 && abs(pCurrent->Pos.y - nodeAdjacent->Pos.y) == 1) {
				
				// diagonal movement isnt permit if theres obstacle 
				cv::Point horizontal(nodeAdjacent->Pos.x, pCurrent->Pos.y);
				bool notEmptyHorizontal = _detector.isBusy(_gridNode.findParcel(horizontal));

				cv::Point vertical(pCurrent->Pos.x, nodeAdjacent->Pos.y);
				bool notEmptyVertical = _detector.isBusy(_gridNode.findParcel(vertical));

				if (!notEmptyHorizontal && !notEmptyVertical) {
					nodeAdjacent->G = pCurrent->G + 14;
				}				
				else
				{
				   delete nodeAdjacent;
				   continue;
				}
			}
			else //	the node is non-diagonal to the starting node
			{
				nodeAdjacent->G = pCurrent->G + 10;
			}

			//	estimate H with the Manhattan method
			nodeAdjacent->CalculateH(EndNode);

			neighborList.push_back(nodeAdjacent);
		}
	}

	return neighborList;
}
