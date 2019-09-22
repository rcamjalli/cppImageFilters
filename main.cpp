#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "ImageFilter.h"

using namespace std;
using namespace cv;

int main() {

    string imgPath;
    cout << "Enter image path: ";
    cin >> imgPath;

    if(imgPath.size()<=0){
        return FAIL;
    }

    ImageFilter filter(imgPath);

    vector<OPERATION> operations = {POOLING, POOLING, POOLING, COLORS8, GRAYSCALE, SOBEL};

    int key = filter.executeOperations(operations);

    if(key != FAIL){
        filter.saveImage();
    }

    return key;
}



