#pragma once

#include "stdafx.h"
#include <iostream>
#include "device_launch_parameters.h"
#include <Windows.h>
#include <iomanip>

#include <opencv2\core\core.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\core\core.hpp>
#include "AxisMergeImage.h"
#include "Node.h"

class Parcel
{
public:
	Parcel(cv::Mat *inputFrame, int stepSize, int x, int y);
	~Parcel();
	void InitText(double textSize, cv::Scalar color);
	void DrawInformations(Node node);
	void ReplaceInformations(Node node);
	void InitCircle(int circleRadius, cv::Scalar color);
	cv::Point SquareIndex(int x, int y);
	int getInitialX();
	int getInitialY();
	int getMaximumX();
	int getMaximumY();
	void setObjectPercentage(double percentage);
	cv::Point getIndex();
private:
	cv::Mat* _inputFrame;
	cv::Mat _perfectFrame;
	int _stepSize;
	int _halfStepSize;
	int width, height;
	int indexX, indexY;
	double objectPercentage;

	cv::Point index;
	cv::Point positionCenter;
};

