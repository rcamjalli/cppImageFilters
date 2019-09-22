//
// Created by RONI EZEQUIEL CAMJALLI on 2019-09-22.
//

#ifndef IMAGEEDITOR_OPERATIONS_H
#define IMAGEEDITOR_OPERATIONS_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

void grayscaleImage(Mat &img);
void to8Colors(Mat &img);
void blurImage(Mat &img);
void sobelFilter(Mat &img);
void pooling(Mat &img);

#endif //IMAGEEDITOR_OPERATIONS_H
