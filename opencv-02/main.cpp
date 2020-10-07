#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <iostream>

using namespace cv;
using namespace std;

// definiere Bildpfad Konstante
#define IMAGE "./assets/vektor_mit_koordinatensystem.png"

int main()
{
	Mat img = imread(IMAGE);
	cout << "Dimensionen: " << img.cols << "x" << img.rows << endl;

	// Fehler beim lesen der Bilddatei
	if (img.empty())
	{
		cout << "Die Datei konnte nicht gelesen werden." << endl;
		return 1;
	}

	// Überschreibe Pixel mit Schwarz
	for (size_t col = 0; col < img.cols; col+=2)
	{
		for (size_t row = 0; row < img.rows; row+=2)
		{
			img.at<Vec3b>(row, col) = (0, 0, 0);
		}
	}

	// Zeige das Ergebnis
	imshow("img", img);
	if (waitKey(0))
	{
		return 0;
	}
}