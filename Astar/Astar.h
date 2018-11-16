#pragma once

#include <opencv2/core/core.hpp> 
#include <opencv2/highgui/highgui.hpp> 
#include <opencv2/imgproc/types_c.h> 
#include <opencv2/imgproc/imgproc.hpp> 

#include <iostream>
#include "Node.h"
#include "NodeList.h"
#include "Grid.h"
#include "ObjectDetection.h"
#include "NodeGrid.h"

//using namespace cv;
using namespace std; // shouldnt be done 

class Astar
{
public:
	Astar();
	Astar(cv::Mat* pImgOriginal, cv::Mat* pImgTreshold, cv::Point pStart, cv::Point pEnd, int pGridSize);
	~Astar();

	void Start(bool pAutomatic);

private:
	void ReconstructPath(Node* pEnd);

	Grid _grid;
	bool errorGridSize = false;

	ObjectDetection _detector;
	NodeGrid _gridNode;
	cv::Mat _img;
	cv::Mat _imgOriginal;
};

