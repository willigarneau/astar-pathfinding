#pragma once

#include <opencv2/core/core.hpp> 
#include <opencv2/highgui/highgui.hpp> 
#include <opencv2/imgproc/types_c.h> 
#include <opencv2/imgproc/imgproc.hpp> 

#include "NodeGrid.h"
#include "ObjectDetection.h"

#include <iostream>
#include <math.h>
#include "Node.h"

using namespace std; // shouldnt be done 

class Grid
{
public:
	Grid();
	Grid(cv::Mat* pImg, cv::Point pStart, cv::Point pEnd, int pGridSize, ObjectDetection pDetector, NodeGrid pGridNode);
	~Grid();

	vector<Node*> GetCurrentNeighborList(Node* pCurrent);

	Node* StartNode;
	Node* EndNode;

private:
	int _GridSize;

	NodeGrid _gridNode;
	ObjectDetection _detector;

};

