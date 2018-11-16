#include "ObjectDetection.h"

#include "opencv2\core\core.hpp"
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\core\core.hpp>

ObjectDetection::ObjectDetection(cv::Mat inputFrame) {
	frame = inputFrame;
}

ObjectDetection::ObjectDetection()
{
}

ObjectDetection::~ObjectDetection() {}

bool ObjectDetection::isBusy(Parcel parcel) {
	bool hasSomething = false;
	double totalPixel = ((parcel.getMaximumX() - parcel.getInitialX()) * (parcel.getMaximumY() - parcel.getInitialY()));
	double currentPixel = 0;
	for (int rows = parcel.getInitialX(); rows < parcel.getMaximumX(); rows++) {
		for (int cols = parcel.getInitialY(); cols < parcel.getMaximumY(); cols++) {
			float blue = frame.at<cv::Vec3b>(cols, rows)[0] / 255.0; // blue
			float green = frame.at<cv::Vec3b>(cols, rows)[1] / 255.0; // green
			float red = frame.at<cv::Vec3b>(cols, rows)[2] / 255.0; // red
			if (blue == 1.0f && green == 1.0f && red == 1.0f) {
				hasSomething = true;
				currentPixel += 1;
			}
		}
	}
	percentage = (currentPixel / totalPixel) * 100;
	if (percentage <= 6.0f) {
		hasSomething = false;
	}
	return hasSomething;
}

double ObjectDetection::getObjectPercentage() {
	return percentage;
}
