#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <iostream>
#include "imagePixels.h"

using namespace cv;
using namespace std;

// definiere Bildpfad Konstante
#define IMAGE1 "./assets/vektor_mit_koordinatensystem.png"
#define IMAGE2 "./assets/simon.jpg"

int main()
{
	Mat img = imread(IMAGE2);
	cout << "Dimensionen: " << img.cols << "x" << img.rows << endl;

	// Fehler beim lesen der Bilddatei
	if (img.empty())
	{
		cout << "Die Datei konnte nicht gelesen werden." << endl;
		return 1;
	}

	Mat hsv_img;
	cvtColor(img, hsv_img, COLOR_BGR2HSV);

	vector<Vec3b> vals = getPixelValues(hsv_img);
	cout << (int)vals[0][0] << endl;

	//sortPixelValues(vals);
	test();

	int pixel_count = 0;
	for (size_t col = 0; col < img.cols; col++)
	{
		for (size_t row = 0; row < img.rows; row++)
		{
			img.at<Vec3b>(row, col) = vals[pixel_count];
			pixel_count++;
		}
	}
	
	// Zeige das Ergebnis
	imshow("img", img);
	if (waitKey(0))
	{
		return 0;
	}
}