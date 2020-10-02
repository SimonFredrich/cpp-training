#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <iostream>
#include <string>

using namespace cv;
using namespace std;

// define constants
#define VIDEO "./assets/autofahrt_02.mp4"

// define functions
Mat turnGray(Mat &frame);
vector<Vec2f> findLines(Mat &frame);
vector<Vec4i> findLinesProbabilistic(Mat &frame_input);
void drawLines(const vector<Vec2f> &lines, Mat &frame, const Scalar &color);
void drawLinesProbabilistic(const vector<Vec4i> &lines, Mat &frame, const Scalar &color);
Mat cropFrame(const Mat &frame, const Point *set_of_vertices[1],
			  int num_of_vertices[]);
Mat findEdges(Mat &frame);
vector<vector<Vec2f>> seperateLines(vector<Vec2f> &lines);

// define variables
Mat frame, frame_cropped, frame_gray, frame_edges;

int main(int argc, char **argv)
{
	VideoCapture cap(VIDEO);

	vector<Vec2f> lines;

	if (!cap.isOpened())
	{
		cerr << "Camera konnte nicht geöffnet werden\n";
		return -1;
	}

	cout << "Frames werden jetzt abgerufen" << endl
		 << "Um zu beenden q (quit) drücken.\n"
		 << endl;

	bool print_frame_stats = true;

	for (;;)
	{
		cap >> frame;
		if (frame.empty())
		{
			cerr << "Es wurde ein leerer Frame aufgenommen\n";
			break;
		}

		// get frame dimensions
		int height = frame.size().height;
		int width = frame.size().width;
		int channels = frame.channels();

		// get image stats
		if (print_frame_stats)
		{
			cout << "Image type: " << frame.type() << endl;
			cout << "Image dimensions: (" << height
				 << ", " << width << ", " << channels
				 << ")" << endl;
			print_frame_stats = false;
		}

		// define and init vertices for polygonal crop
		Point vertices[1][4];
		vertices[0][0].x = (0);
		vertices[0][0].y = (height);
		vertices[0][1].x = (width / 2);
		vertices[0][1].y = (height / 2);
		vertices[0][2].x = (width);
		vertices[0][2].y = (height - height / 8);
		vertices[0][3].x = (width);
		vertices[0][3].y = (height);
		const Point *set_of_vertices[1] = {vertices[0]};
		int num_of_vertices[] = {4};

		// convert cropped frame to grayscale
		frame_gray = turnGray(frame);
		// find edges in grayscale frame
		frame_edges = findEdges(frame_gray);
		// performe polygonal crop
		frame_cropped = cropFrame(frame_edges, set_of_vertices, num_of_vertices);

		// find and draw lines
		lines = findLines(frame_cropped);
		//cout << lines.size() << endl;
		vector<Vec2f> lines_left = seperateLines(lines)[0];
		vector<Vec2f> lines_right = seperateLines(lines)[1];
		// draw left lines
		drawLines(lines_left, frame, Scalar(255, 0, 0));
		drawLines(lines_right, frame, Scalar(0, 0, 255));

		// set up windows to show results in
		string name_original_window = "Frame";
		string name_processed_window = "Frame Processed";
		namedWindow(name_original_window, WINDOW_NORMAL);
		namedWindow(name_processed_window, WINDOW_NORMAL);
		resizeWindow(name_original_window, 900, 550);
		resizeWindow(name_processed_window, 900, 550);
		moveWindow(name_original_window, 100, 100);
		moveWindow(name_processed_window, 1000, 100);
		// show results
		imshow(name_original_window, frame);
		imshow(name_processed_window, frame_cropped);

		if (waitKey(25) >= 113)
			break;
	}

	cap.release();
	return 0;
}

/***
 * This function returns a grayscale version of the input frame.
 ***/
Mat turnGray(Mat &frame)
{
	Mat frame_gray;
	cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
	return frame_gray;
}

/***
 * This function returns lines calculated with cv::HoughLines(...).
 ***/
vector<Vec2f> findLines(Mat &frame_input)
{
	vector<Vec2f> lines;
	HoughLines(frame_input, lines, 6, CV_PI / 60, 220);
	return lines;
}

/***
 * This function returns lines calculated with cv::HoughLinesP(...).
 ***/
vector<Vec4i> findLinesProbabilistic(Mat &frame_input)
{
	vector<Vec4i> lines;
	HoughLinesP(frame_input, lines, 1, CV_PI, 100, 40, 25);
	return lines;
}

/***
 * This function draws the lines calculated with cv::HoughLines(...)
 * on the input frame.
 ***/
void drawLines(const vector<Vec2f> &lines, Mat &frame, const Scalar &color)
{
	for (size_t i = 0; i < lines.size(); i++)
	{
		float rho = lines[i][0], theta = lines[i][1];
		Point pt1, pt2;
		double a = cos(theta), b = sin(theta);
		double x0 = a * rho, y0 = b * rho;
		pt1.x = cvRound(x0 + 1000 * (-b));
		pt1.y = cvRound(y0 + 1000 * (a));
		pt2.x = cvRound(x0 - 1000 * (-b));
		pt2.y = cvRound(y0 - 1000 * (a));
		line(frame, pt1, pt2, color, 3, LINE_AA);
	}
}

/***
 * This function draws the lines calculated with cv::HoughLinesP(...)
 * on the input frame.
 ***/
void drawLinesProbabilistic(const vector<Vec4i> &lines, Mat &frame, const Scalar &color)
{
	for (size_t i = 0; i < lines.size(); i++)
	{
		float rho = lines[i][0], theta = lines[i][1];
		Point pt1, pt2;
		double a = cos(theta), b = sin(theta);
		double x0 = a * rho, y0 = b * rho;
		pt1.x = cvRound(x0 + 1000 * (-b));
		pt1.y = cvRound(y0 + 1000 * (a));
		pt2.x = cvRound(x0 - 1000 * (-b));
		pt2.y = cvRound(y0 - 1000 * (a));
		line(frame, pt1, pt2, color, 3, LINE_AA);
	}
}

/***
 * This function returns a polygon of the input frame.
 ***/
Mat cropFrame(const Mat &frame, const Point *set_of_vertices[1],
			  int num_of_vertices[])
{
	// create a blank frame
	Mat mask = Mat::zeros(Size(frame.cols, frame.rows), frame.type());

	// retrieve the number of color channels of the frame
	int channels = frame.channels();

	// fill polygon with the color white
	fillPoly(mask, set_of_vertices, num_of_vertices, 1, Scalar(255, 255, 255), 8);

	// fill only the poly-region with frame pixels
	Mat poly_mask;
	bitwise_and(frame, mask, poly_mask);

	// return only where mask pixels match
	return poly_mask;
}

/***
 * This function finds the edges in a given frame.
 ***/
Mat findEdges(Mat &frame)
{
	Mat edges;
	Canny(frame, edges, 100, 150);
	return edges;
}

/***
 * This function sorts the lines by slope (negative/positive);
 * It then returns a vector of left and right lines.
 ***/
vector<vector<Vec2f>> seperateLines(vector<Vec2f> &lines)
{
	vector<vector<Vec2f>> line_collector(2);
	for (size_t i = 0; i < lines.size(); i++)
	{
		float rho = lines[i][0], theta = lines[i][1];
		Point2d pt1, pt2;
		double a = cos(theta), b = sin(theta);
		double x0 = a * rho, y0 = b * rho;
		pt1.x = cvRound(x0 + 1000 * (-b));
		pt1.y = cvRound(y0 + 1000 * (a));
		pt2.x = cvRound(x0 - 1000 * (-b));
		pt2.y = cvRound(y0 - 1000 * (a));

		// calculate slope
		double slope = (pt2.y - pt1.y) / (pt2.x - pt1.x);

		// continue only for very vertical lines
		if (fabs(slope) < 0.5)
			continue;

		cout << slope << endl;
		if (slope <= 0)
		{
			line_collector[0].push_back(lines[i]);
		}
		else
		{
			line_collector[1].push_back(lines[i]);
		}
	}
	return line_collector;
}