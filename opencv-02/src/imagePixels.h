#pragma once
#include <vector> 
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
using namespace std;
using namespace cv;

/**
 * returns vector with all color values of the image
 * */
vector<Vec3b> getPixelValues(const Mat& img);

/**
 * return sorted vector<Vec3b> (sorted after "value" Vec3b("value", x, x))
 * */
void sortPixelValues(vector<Vec3b>& vals);

void test();