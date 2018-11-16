#include "AxisMergeImage.h"

AxisMergeImage::AxisMergeImage()
{
}

AxisMergeImage::~AxisMergeImage()
{
}

void AxisMergeImage::FlushCameraBuffer(Axis camera) {
	cv::Mat temp;
	for (int i = 0; i < 100; i++) {
		camera.GetImage(temp);
	}
}

void AxisMergeImage::GetCameraImages() {
	// Set initial matrix for gpu processing
	cv::Mat firstImage, secondImage;
	// Get first image and flush buffer
	Axis axis("10.128.3.4", "etudiant", "gty970");
	axis.AbsolutePan(-44.99);
	Sleep(1500);
	axis.AbsoluteTilt(-66.10);
	Sleep(2500);
	axis.GetImage(firstImage);
	Sleep(1500);
	FlushCameraBuffer(axis);
	Sleep(1500);
	// Get second image
	axis.AbsolutePan(136.67);
	Sleep(1500);
	axis.AbsoluteTilt(-70.70);
	Sleep(1500);
	axis.GetImage(secondImage);
	// Store the images in files
	cv::imwrite("first.jpg", firstImage);
	cv::imwrite("second.jpg", secondImage);
	axis.ReleaseCam();
}

cv::Mat AxisMergeImage::MergeImages(cv::Mat firstFrame, cv::Mat secondFrame) {
	// Flip the second image to fit the first one when merging
	cv::flip(secondFrame, secondFrame, -1);
	// Estimate the new values for the rows and cols
	int rows = firstFrame.rows + secondFrame.rows;
	int cols = cv::max(firstFrame.cols, secondFrame.cols);
	// Creating a new frame
	cv::Mat3b finalFrame(rows, cols, cv::Vec3b(0, 0, 0));
	// Copy images in correct positions
	firstFrame.copyTo(finalFrame(cv::Rect(0, 0, firstFrame.cols, firstFrame.rows)));
	secondFrame.copyTo(finalFrame(cv::Rect(0, firstFrame.rows, secondFrame.cols, secondFrame.rows)));
	cv::resize(finalFrame, finalFrame, cv::Size(600, 600));
	return finalFrame;
}

cv::Mat AxisMergeImage::GetMergedImages() {
	// Get the frames from the Axis camera and stores them in files
	GetCameraImages();
	// Read the files where the frames are stored
	cv::Mat firstFrame = cv::imread("first.jpg");
	cv::Mat secondFrame = cv::imread("second.jpg");
	// Merge the two images together
	cv::Mat mergedFrame = MergeImages(firstFrame, secondFrame);
	return mergedFrame;
}

cv::Mat AxisMergeImage::GetPerfectImage() {
	// Read the files where the frames are stored
	cv::Mat firstFrame = cv::imread("first.jpg");
	cv::Mat secondFrame = cv::imread("second.jpg");
	// Merge the two images together
	cv::Mat mergedFrame = MergeImages(firstFrame, secondFrame);
	return mergedFrame;
}