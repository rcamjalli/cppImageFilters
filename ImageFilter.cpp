//
// Created by RONI EZEQUIEL CAMJALLI on 2019-09-22.
//

#include "ImageFilter.h"
#import "Operations.h"
#include <iostream>

ImageFilter::ImageFilter(const string readFile, const string writeFile): _readFile(readFile), _writeFile(writeFile) {
    _executeOperation(RELOAD,_img);
}

void ImageFilter::loadNewImage(const string filename) {
    _readFile = filename;
    _executeOperation(RELOAD,_img);
}

void ImageFilter::saveImage() {
    _saveImage(_img, _writeFile);
}

OPERATION_RESULT ImageFilter::executeOperations(const vector<OPERATION> operations){
    OPERATION_RESULT res = OK;
    for(OPERATION o : operations){
        if(executeOperation(o) == FAIL){
            break;
        }
    }
    return res;
}

OPERATION_RESULT ImageFilter::executeOperation(const OPERATION operation){
    return _executeOperation(operation, _img);
}

Mat ImageFilter::_loadImage(const string filename){
    Mat img = imread(filename, IMREAD_COLOR);
    Mat img2;
    img.convertTo(img2, CV_64FC3);
    return img2;
}

void ImageFilter::_saveImage(Mat &img, const string filename){
    Mat img2;
    img.convertTo(img2, CV_8U);
    imwrite(filename, img2);
}

OPERATION_RESULT ImageFilter::_executeOperation(const OPERATION o, Mat &img){
    double t = getTickCount();
    switch (o) {
        case RELOAD:
            img = _loadImage(_readFile);
            break;
        case BLUR:
            blurImage(img);
            break;
        case SOBEL:
            sobelFilter(img);
            break;
        case GRAYSCALE:
            grayscaleImage(img);
            break;
        case COLORS8:
            to8Colors(img);
            break;
        case INVERTCOLORS:
            invertColors(img);
            break;
        case POOLING:
            pooling(img);
            break;
        default:
            break;
    }
    t = ((double)getTickCount() - t)/getTickFrequency();
    cout << "Operation execution time:  " << t << "s." << endl;
    return img.data ? OK : FAIL;
}
