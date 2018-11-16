#include "NodeGrid.h"

#include "opencv2\core\core.hpp"
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\core\core.hpp>

NodeGrid::NodeGrid(cv::Mat inputFrame, int iter) {
	frame = inputFrame;
	width = inputFrame.rows;
	height = inputFrame.cols;
	iterations = iter;
	stepSize = width / iterations;
	centerSquare = stepSize / 2;
}

NodeGrid::NodeGrid()
{
}

NodeGrid::~NodeGrid() {}

void NodeGrid::DrawLines(cv::Scalar color) {
	for (int i = 0; i < height; i += stepSize) {
		cv::line(frame, cv::Point(0, i), cv::Point(width, i), color);
	}
	for (int i = 0; i < width; i += stepSize) {
		cv::line(frame, cv::Point(i, 0), cv::Point(i, height), color);
	}
}

void NodeGrid::InitSquare(cv::Scalar color, ObjectDetection obj) {
	for (int cols = 0; cols < height - centerSquare; cols += stepSize) {
		for (int rows = 0; rows < width - centerSquare; rows += stepSize) {
				Parcel *parcel = new Parcel(&frame, stepSize, rows, cols);
				bool isBusy = obj.isBusy(*parcel);
				if (isBusy) {
					parcel->InitCircle(10, cv::Scalar(0, 0, 0));
				}
				double percentage = obj.getObjectPercentage();
				parcel->setObjectPercentage(percentage);
				parcel->InitText(0.8, cv::Scalar(0, 0, 0));
				listParcel.push_back(parcel);
		}
	}
	Parcel x = findParcel(cv::Point(1, 0));
}

std::vector<Parcel*> NodeGrid::getObjectList() {
	return listParcel;
}

Parcel NodeGrid::findParcel(cv::Point coords) {
	for (int i = 0; i < listParcel.size(); i++) {
		if (listParcel[i]->getIndex() == coords) {
			return *listParcel[i];
		}
	}
}

