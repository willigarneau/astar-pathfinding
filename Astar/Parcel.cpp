#include "Parcel.h"

Parcel::Parcel(cv::Mat *inputFrame, int stepSize, int x, int y)
{
	AxisMergeImage cp;
	_inputFrame = inputFrame;
	_perfectFrame = cp.GetPerfectImage();
	width = inputFrame->size().width;
	height = inputFrame->size().height;
	_stepSize = stepSize;
	_halfStepSize = stepSize / 2;
	positionCenter.x = x + _halfStepSize;
	positionCenter.y = y + _halfStepSize;
	index = SquareIndex(x, y);
}

Parcel::~Parcel() {}

void Parcel::InitText(double textSize, cv::Scalar color) {
	int topLeftSquare = (_halfStepSize / 4 * 3);
	cv::Point position = cv::Point(positionCenter.x - topLeftSquare + 8, positionCenter.y - topLeftSquare);

	int thick = 1;
	cv::putText(*_inputFrame, "X:" + std::to_string(index.x) + " Y:" + std::to_string(index.y), position, CV_FONT_HERSHEY_PLAIN, textSize, color, thick);

	cv::putText(*_inputFrame, std::to_string((int)round(objectPercentage)) + "%", cv::Point(position.x + 15, position.y + 10), CV_FONT_HERSHEY_PLAIN, textSize, color, thick);
}

void Parcel::DrawInformations(Node node) {
	int topLeftSquare = (_halfStepSize / 4 * 3);
	cv::Point position = cv::Point(positionCenter.x - topLeftSquare, positionCenter.y - topLeftSquare);

	int thick = 1;
	
	cv::putText(*_inputFrame, "F:" + std::to_string(node.F()) + " G:" + std::to_string(node.G) + " H:" + std::to_string(node.H), cv::Point(position.x - 10, position.y + 60), CV_FONT_HERSHEY_PLAIN, 0.6, cv::Scalar(0,0,0), thick);
	cv::putText(*_inputFrame, "pX:" + std::to_string(node.Parent->Pos.x) + " pY:" + std::to_string(node.Parent->Pos.y), cv::Point(position.x - 10, position.y + 70), CV_FONT_HERSHEY_PLAIN, 0.75, cv::Scalar(0, 0, 0), thick);
}

void Parcel::ReplaceInformations(Node node)
{
 	int topLeftSquare = (_halfStepSize / 4 * 3);
	cv::Point position = cv::Point(positionCenter.x - topLeftSquare, positionCenter.y - topLeftSquare);

	int thick = 1;
	for (int i = position.x - 10; i < position.x + 70; i++) {
		for (int y = position.y - 10; y < position.y + 70; y++) {
			_inputFrame->at<cv::Vec3b>(y, i) = _perfectFrame.at<cv::Vec3b>(y, i);
		}
	}
	cv::circle(*_inputFrame, positionCenter, 10, cv::Scalar(255,0,0), -1);
	cv::putText(*_inputFrame, "X:" + std::to_string(index.x) + " Y:" + std::to_string(index.y), cv::Point(position.x + 8, position.y), CV_FONT_HERSHEY_PLAIN, 0.8, cv::Scalar(0,0,0), thick);
	cv::putText(*_inputFrame, std::to_string((int)round(objectPercentage)) + "%", cv::Point(position.x + 23, position.y + 10), CV_FONT_HERSHEY_PLAIN, 0.8, cv::Scalar(0, 0, 0), thick);
	cv::putText(*_inputFrame, "F:" + std::to_string(node.F()) + " G:" + std::to_string(node.G) + " H:" + std::to_string(node.H), cv::Point(position.x - 10, position.y + 60), CV_FONT_HERSHEY_PLAIN, 0.65, cv::Scalar(0, 0, 0), thick);
	cv::putText(*_inputFrame, "pX:" + std::to_string(node.Parent->Pos.x) + " pY:" + std::to_string(node.Parent->Pos.y), cv::Point(position.x - 10, position.y + 70), CV_FONT_HERSHEY_PLAIN, 0.75, cv::Scalar(0, 0, 0), thick);
}

void Parcel::InitCircle(int circleRadius, cv::Scalar color) {
	int thickness = -1;

	cv::circle(*_inputFrame, positionCenter, circleRadius, color, thickness);
}

cv::Point Parcel::SquareIndex(int x, int y) {
	indexX = (x) / _stepSize;
	indexY = (y) / _stepSize;
	return cv::Point(indexX, indexY);
}

int Parcel::getInitialX() {
	return positionCenter.x - _halfStepSize;
}

int Parcel::getInitialY() {
	return positionCenter.y - _halfStepSize;
}

int Parcel::getMaximumX() {
	return positionCenter.x + _halfStepSize;
}

int Parcel::getMaximumY() {
	return positionCenter.y + _halfStepSize;
}

void Parcel::setObjectPercentage(double percentage) {
	objectPercentage = percentage;
}

cv::Point Parcel::getIndex() {
	return cv::Point(indexX, indexY);
}
