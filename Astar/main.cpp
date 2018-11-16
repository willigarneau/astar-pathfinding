// Astar.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"

#include "cuda_runtime.h" 
#include "device_launch_parameters.h"

#include <opencv2/core/core.hpp> 
#include <opencv2/highgui/highgui.hpp> 
#include <opencv2/imgproc/types_c.h> 
#include <opencv2/imgproc/imgproc.hpp> 

#include "AxisMergeImage.h"
#include "Astar.h"

using namespace cv;

int defaultFgColor[3] = { 255, 255, 255 };
extern "C" bool GPGPU_BackGroundSubstractionHSV(cv::Mat* imgHSV, cv::Mat* GPGPUimg, int minHue, int maxHue,
	int* backGroundColor, bool replaceForeground = false, int* ForegroundColor = defaultFgColor);

int main()
{
	std::cout << "Press s/S to start astar" << std::endl;
	std::cout << "Press a/A to put astar in automatic mode" << std::endl;
	std::cout << "Press b/B to show treshold" << std::endl;

	AxisMergeImage axis;
	Mat frame = axis.GetMergedImages();
	//imwrite("frame.jpg", frame);
	//Mat frame = imread("frame.jpg");
	Mat treshold = frame.clone();

	int lowHue = 75;
	int highHue = 150;
	int bgColor[3] = { 0, 0, 0 };
	GPGPU_BackGroundSubstractionHSV(&frame, &treshold, lowHue, highHue, bgColor, true);

	int gridSize = 7;
	Point start(3, 6);
	Point end(5, 6);

	Astar astar(&frame, &treshold, start, end, gridSize);

	bool waiting = true;
	bool automatic = false;

	while (waiting)
	{
		imshow("Astar", frame);
		char key = (char)waitKey(0);

		if (key == 's' || key == 'S') {
			astar.Start(automatic);
			waiting = false;
		}
		else if (key == 'a' || key == 'A')
			automatic = true;
		else if (key == 'b' || key == 'B')
			cv::imshow("treshold", treshold);
	}
	waitKey(0);
    return 0;
}

