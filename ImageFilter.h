//
// Created by RONI EZEQUIEL CAMJALLI on 2019-09-22.
//

#ifndef IMAGEEDITOR_IMAGEFILTER_H
#define IMAGEEDITOR_IMAGEFILTER_H


#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

static string photo = "../photo.jpg";

enum OPERATIONS {EXIT = 0, RELOAD, BLUR, SOBEL, GRAYSCALE, COLORS8, POOLING, NONE, FAIL = -1};

Mat loadImage(string filename);
void saveImage(Mat &img, string filename);
int executeOperation(OPERATIONS o, Mat &img);


#endif //IMAGEEDITOR_IMAGEFILTER_H
