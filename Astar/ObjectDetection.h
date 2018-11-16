#pragma once
#include "stdafx.h"
#include <iostream>
#include "device_launch_parameters.h"
#include <Windows.h>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include "AxisCommunication.h"
#include "Parcel.h"

#include <opencv2\core\core.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\core\core.hpp>
class ObjectDetection
{
public:
	ObjectDetection(cv::Mat inputFrame);
	ObjectDetection();
	~ObjectDetection();
	bool isBusy(Parcel parcel);
	double getObjectPercentage();

private:
	cv::Mat frame;
	double percentage;
};

