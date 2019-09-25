//
// Created by RONI EZEQUIEL CAMJALLI on 2019-09-22.
//

#ifndef IMAGEEDITOR_IMAGEFILTER_H
#define IMAGEEDITOR_IMAGEFILTER_H


#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

enum OPERATION {RELOAD, BLUR, SOBEL, GRAYSCALE, COLORS8, INVERTCOLORS, POOLING};
enum OPERATION_RESULT {FAIL = -1, OK = 0};

class ImageFilter{
public:
    ImageFilter(string readFile, string writeFile);
    void loadNewImage(string filename);
    void saveImage();
    OPERATION_RESULT executeOperation(OPERATION operation);
    OPERATION_RESULT executeOperations(vector<OPERATION> operations);

private:
    Mat _loadImage(string filename);
    void _saveImage(Mat &img, string filename);
    OPERATION_RESULT _executeOperation(OPERATION o, Mat &img);


    string _readFile;
    string _writeFile;
    Mat _img;
};






#endif //IMAGEEDITOR_IMAGEFILTER_H
