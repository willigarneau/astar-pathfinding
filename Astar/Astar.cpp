#include "Astar.h"

Astar::Astar()
{
}

Astar::Astar(cv::Mat* pImgOriginal, cv::Mat* pImgTreshold, cv::Point pStart, cv::Point pEnd, int pGridSize)
{
	if (pStart.x >= 0 && pGridSize > pStart.x && pEnd.x >= 0 && pGridSize > pEnd.x && pStart.y >= 0 && pGridSize > pStart.y && pEnd.y >= 0 && pGridSize > pEnd.y) {
		_detector = ObjectDetection(*pImgTreshold);
		_gridNode = NodeGrid(*pImgOriginal, 7);
		_gridNode.DrawLines(cv::Scalar(0, 0, 0));
		_gridNode.InitSquare(cv::Scalar(0, 0, 0), _detector);

		_grid = Grid(pImgTreshold, pStart, pEnd, pGridSize, _detector, _gridNode);

		_img = *pImgTreshold;
		_imgOriginal = *pImgOriginal;


		Parcel end = _gridNode.findParcel(pEnd);
		end.InitCircle(10, cv::Scalar(255, 0, 255));
	}
	else {
		errorGridSize = true;
		cout << "point arent in the grid range" << endl;
	}
}

Astar::~Astar()
{
}

void Astar::Start(bool pAutomatic)
{	
	if (errorGridSize) {
		cout << "cant start astar because target points arent in the grid range" << endl;
		return;
	}

 	NodeList closedList;
	NodeList openList;
	openList.Add(_grid.StartNode);

	while (!openList.IsEmpty()) {
		Node* current = openList.LowestScore();
		if (current->Equals(_grid.EndNode)) { 
			ReconstructPath(current);
			return;
		}
		
	    // current node goes into the closed list so draw it red
		_gridNode.findParcel(current->Pos).InitCircle(10, cv::Scalar(0, 0, 255));

		openList.Remove(current); 
		closedList.Add(current);

		vector<Node*> neighborList = _grid.GetCurrentNeighborList(current);
		for (auto &neighbor : neighborList) // access by reference to avoid copying
		{		
			Parcel tempParcel = _gridNode.findParcel(neighbor->Pos);
			if (closedList.Contains(neighbor)) {
				delete neighbor;
				continue;
			}
			else if (!openList.Contains(neighbor)) {
				openList.Add(neighbor);
			    
				// new point into the open list so draw it blue
				tempParcel.InitCircle(10, cv::Scalar(255, 0, 0));	
				tempParcel.DrawInformations(*neighbor);			

				continue;
			}				

			int i = 0;
			if (neighbor->G >= openList.Find(neighbor, &i)->G) {
				delete neighbor;			
				continue;
			}
			else {
				// this new path is better than the current path so change its G & parent value
				openList.Replace(neighbor, i);
				tempParcel.ReplaceInformations(*neighbor);
			}	
		}

		cv::imshow("Astar", _imgOriginal);

		if (pAutomatic)
			cv::waitKey(150);
		else
			cv::waitKey(0);
	}

	// TODO test by blocking all path to the object
	// path doesnt exist
	cout << "theres no path" << endl;
}

void Astar::ReconstructPath(Node* pEnd)
{
 	cout << "***** Backward Path *****" << endl;
	Node* node = pEnd;
	while (node != nullptr)
	{
		//
		_gridNode.findParcel(node->Pos).InitCircle(10, cv::Scalar(0, 255, 0));
		//

		cout << node->Pos.x << ";" << node->Pos.y << "   f:" << node->F() << " g:" << node->G << " h:" << node->H << endl;
		node = node->Parent;

		cv::imshow("Astar", _imgOriginal);
		cv::waitKey(150);
	}

}

