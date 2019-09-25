#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "ImageFilter.h"

using namespace std;
using namespace cv;

int main(int argc, char *argv[]) {
    if(argc < 3){
        return FAIL;
    }

    string imgPath = argv[1];
    string wrPath = argv[2];

    if(imgPath.size()<=0 || wrPath.size() <= 0){
        return FAIL;
    }

    ImageFilter filter(imgPath, wrPath);

    vector<OPERATION> operations = {POOLING, POOLING, POOLING, COLORS8, GRAYSCALE, SOBEL, INVERTCOLORS};

    int key = filter.executeOperations(operations);

    if(key != FAIL){
        filter.saveImage();
    }

    return key;
}



