
#ifndef AXIS_COMMUNICATION_H
#define AXIS_COMMUNICATION_H

#ifdef AXIS_EXPORTS
#define AXIS_API __declspec(dllexport)
#else
#define AXIS_API __declspec(dllimport)
#endif


#include <iostream>
#include <opencv2/opencv.hpp> 
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

//using namespace cv;
class Bimbo
{
	int tst1;
};
class AXIS_API AxisCommunication
{
public:
	//AxisCommunication(const char* userName, const char* password);
	AxisCommunication();
	~AxisCommunication();

	void setUserNameAndPassWord(const char* userName, const char* password);
	bool EnableUnsafeHeaderParsing();
	const char* sendRequest(const char* message);

private:
	const char* userName_;
	const char* password_;
};


class AXIS_API CamData
{
public:
	float Pan;
	float Tilt;
	int Zoom;
	int Focus;
	int Iris;
	int Brightness;
	bool AutoFocusState;
	bool AutoIrisStat;
	int Speed;
};

class AXIS_API Axis : public AxisCommunication
{
public:
	//AxisCommunication(const char* userName, const char* password);
	Axis(char* IpAdress, char* userName, char* password);
	Axis();
	~Axis();
	bool ValidateResult();
	std::string CamInfo();
	bool CenterCam(int x, int y);
	bool PrintErrorMsgOnConsole = true;

	bool RelativeZoom(int ZoomStep);
	bool RelativePan(float PanStep);
	bool RelativeTilt(float PanTilt);
	bool RelativeBrightness(int Brightness);
	bool RelativeFocus(int FocusStep);

	bool AbsoluteFocus(int Focus);
	bool AbsoluteZoom(int ZoomS);
	bool AbsolutePan(float Pan);
	bool AbsoluteTilt(float Tilt);

	bool SetContinousZoom(int Speed);
	bool StopContinousZoom();

	bool SetAutoFocus(bool AutoFocusState);
	bool SetAutoIris(bool AutoIrisState);

	bool GetImage(cv::Mat &Image);
	bool SetCamResolution(int Width, int Height);
	bool Axis::GetCamResolution(int &Height, int &Width);
	bool ReleaseCam();

	bool GetCamPos(CamData &Data);
	bool GetCamSpeed(CamData &Data);

private:
	char Command[500];
	std::string results;
	std::string ErrorMsg;
	bool ErorrOccur = false;
	std::string CamIpAdress;
	CamData ActualPosition;

	cv::VideoCapture video_capture;
	std::string UserName;
	std::string Password;
	bool CamIsOpen;
	int Width, Height;

	int CamPosGetNextFieldInResults(int Pos);
	int CamPosReadNextField(std::string &sField, int Position);
};


#endif //AXIS_COMMUNICATION_H
