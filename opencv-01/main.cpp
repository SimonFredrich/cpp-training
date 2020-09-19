#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main( int argc, char** argv )
{
    Mat frame;

    VideoCapture cap;

    int device_id = 0;
    int api_id = 0;

    cap.open(device_id);

    if (!cap.isOpened()){
		cerr << "Camera konnte nicht geöffnet werden\n";
		return -1;
	}

	cout << "Frames werden jetzt abgerufen" << endl
		<< "Um zu beenden drücke einen beliebigen Knopf" << endl;

	for (;;)
	{
		cap >> frame;
		if (frame.empty())
		{
			cerr << "Es wurde ein leerer Frame aufgenommen\n";
			break;
		}
		
		namedWindow("Live", (200, 200));
		imshow("Live", frame);

		if (waitKey(5) >= 0)
			break;
	}

    return 0;
}
