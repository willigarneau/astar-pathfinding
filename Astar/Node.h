#pragma once

#include <opencv2/core/core.hpp> 
#include <opencv2/highgui/highgui.hpp> 
#include <opencv2/imgproc/types_c.h> 
#include <opencv2/imgproc/imgproc.hpp>

class Node {

public:
	Node();
	Node(cv::Point pPoint, Node* pParent);

	int F();
	void CalculateH(Node* pEnd);
	bool Equals(Node* pNode);

	Node* Parent;
	int G;
	int H;
	bool IsEmpty;
	cv::Point Pos;
};