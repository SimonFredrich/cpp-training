#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <iostream>
#include <string>

using namespace cv;
using namespace std;

#define VIDEO "./assets/autofahrt_02.mp4"
Mat turnGray(Mat &frame);
vector<Vec2f> getLines(Mat &frame);
void drawLines(const vector<Vec2f> lines, Mat &frame);

int main(int argc, char** argv)
{
    Mat frame;
	Mat frame_gray;
	vector<Vec2f> lines;

    VideoCapture cap(VIDEO);

    if (!cap.isOpened()){
		cerr << "Camera konnte nicht geöffnet werden\n";
		return -1;
	}

	cout << "Frames werden jetzt abgerufen" << endl
		<< "Um zu beenden q (quit) drücken." << endl;

	for (;;)
	{
		cap >> frame;
		if (frame.empty())
		{
			cerr << "Es wurde ein leerer Frame aufgenommen\n";
			break;
		}

		frame_gray = turnGray(frame);
		lines = getLines(frame_gray);
		drawLines(lines, frame);
		
		namedWindow("Frame", WINDOW_NORMAL);
		resizeWindow("Frame", 900, 550);
		imshow("Frame", frame);

		if (waitKey(25) >= 113)
			break;
	}

	cap.release();
	destroyAllWindows();
	
    return 0;
}

Mat turnGray(Mat &frame)
{
	Mat frame_gray;
	cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
	return frame_gray;
}

vector<Vec2f> getLines(Mat &frame_input)
{
	vector<Vec2f> lines;
	HoughLines(frame_input, lines, 1, CV_PI/180, 50, 0, 0);
	return lines;
}

void drawLines(const vector<Vec2f> lines, Mat &frame)
{
	for (size_t i = 0; i < lines.size(); i++)
	{
		float rho = lines[i][0], theta = lines[i][1];
		Point pt1, pt2;
		double a = cos(theta), b = sin(theta);
		double x0 = a*rho, y0 = b*rho;
		pt1.x = cvRound(x0 + 1000*(-b));
		pt1.y = cvRound(y0 + 1000*(a));
		pt2.x = cvRound(x0 - 1000*(-b));
		pt2.y = cvRound(y0 - 1000*(a));
		line(frame, pt1, pt2, Scalar(0,0,255), 3, LINE_AA);
	}
}


