#pragma once

#include <Windows.h>

#include "AxisCommunication.h"

#include <opencv2\core\core.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\core\core.hpp>

class AxisMergeImage
{
public:
	AxisMergeImage();
	~AxisMergeImage();

		void FlushCameraBuffer(Axis camera);
		void GetCameraImages();
		cv::Mat MergeImages(cv::Mat firstFrame, cv::Mat secondFrame);
		cv::Mat GetMergedImages();
		cv::Mat GetPerfectImage();
};

