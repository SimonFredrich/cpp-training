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
 * return vector with chunk indication (1, 2 or 3)
 * 1: fist chunk
 * 2: second chunk
 * 3: third chunk
 * */
void sortPixelValues(vector<Vec3b>& vals);

void test();