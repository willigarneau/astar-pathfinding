#pragma once
#include "stdafx.h"
#include <iostream>
#include "device_launch_parameters.h"
#include <Windows.h>

#include "Parcel.h"
#include "ObjectDetection.h"

#include <opencv2\core\core.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\core\core.hpp>

class NodeGrid
{
public:
	NodeGrid(cv::Mat inputFrame, int iter);
	NodeGrid();
	~NodeGrid();
	void DrawLines(cv::Scalar color);
	void InitSquare(cv::Scalar color, ObjectDetection obj);
	std::vector<Parcel*> getObjectList();
	Parcel findParcel(cv::Point coords);
private:
	cv::Mat frame;
	int stepSize;
	int centerSquare;
	int width, height;
	int iterations;

	std::vector<Parcel*> listParcel;
};

