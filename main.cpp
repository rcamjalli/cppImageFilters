#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "ImageFilter.h"

using namespace std;
using namespace cv;

static string DISPLAY_NAME = "IMAGE EDITOR";

int main() {
    namedWindow(DISPLAY_NAME, WINDOW_AUTOSIZE);
    int key = EXIT;

    Mat img = loadImage(photo);
    if (!img.data){
        key = FAIL;
    }

    cout << "Img Size: " << img.rows << "x" << img.cols << endl;
    vector<OPERATIONS> operations = {POOLING, POOLING, POOLING, COLORS8, GRAYSCALE, SOBEL};
    for (OPERATIONS o : operations){
        key = executeOperation(o,img);
        if(key == FAIL){
            break;
        }
    }
    cout << "Img Size: " << img.rows << "x" << img.cols << endl;
    saveImage(img,photo);
    return key;
}



