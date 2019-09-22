//
// Created by RONI EZEQUIEL CAMJALLI on 2019-09-22.
//

#include "ImageFilter.h"
#include <iostream>

Mat loadImage(string filename){
    Mat img = imread(filename, IMREAD_COLOR);
    Mat img2;
    img.convertTo(img2, CV_64FC3);
    return img2;
}

void saveImage(Mat &img, string filename){
    Mat img2;
    img.convertTo(img2, CV_8U);
    imwrite(filename, img2);
}

void generalEdition(Mat &img, const function<void(Vec3d &pixel)> functor){
    parallel_for_(Range(0,img.rows),[&](const Range& r) {
        for (int i = r.start; i < r.end; ++i) {
            parallel_for_(Range(0,img.cols),[&](const Range& s){
                for (int j = s.start; j < s.end; ++j) {
                    functor(img.at<Vec3d>(i, j));
                }
            });
        }
    });
}

void grayscaleImage(Mat &img){
    generalEdition(img,[&](Vec3d &pixel){
        double prom = (pixel[0] + pixel[1] + pixel[2])/3;
        pixel[0] = prom;
        pixel[1] = prom;
        pixel[2] = prom;
    });
}

void to8Colors(Mat &img){
    generalEdition(img,[&](Vec3d &pixel){
        for (int i = 0; i < 3; ++i) {
            pixel[i] = ((int)(pixel[i]/32))*32;
        }
    });
}

void convolute1D(Mat &img, const double kernel[3], bool isVertical){
    const int max_i = isVertical ? img.cols : img.rows;
    const int max_j = isVertical ? img.rows : img.cols;
    parallel_for_(Range(0,max_i),[&](const Range& r) {
        for (int i = r.start; i < r.end; ++i) {
            Mat aux = isVertical ? img.col(i) : img.row(i);
            Mat current;
            aux.copyTo(current);
            parallel_for_(Range(1,max_j-1),[&](const Range& s){
                for (int j = s.start; j < s.end; ++j) {
                    Vec3d *pixel = isVertical ? &img.at<Vec3d>(j, i) : &img.at<Vec3d>(i, j);
                    Vec3d a = current.at<Vec3d>(j-1);
                    a *= kernel[0];
                    Vec3d b = current.at<Vec3d>(j);
                    b *= kernel[1];
                    Vec3d c = current.at<Vec3d>(j+1);
                    c *= kernel[2];
                    *pixel = a+b+c;
                }
            });

        }
    });
}

void convolution(Mat &img, const double vKernel[3], const double hKernel[3]){
    convolute1D(img,vKernel,true);
    convolute1D(img,hKernel,false);
}


void blurImage(Mat &img){
    double kernel[3] = {0.25,0.5,0.25};
    convolution(img,kernel,kernel);
}

void sobelFilter(Mat &img){
    double vKernel[3] = {1,2,1};
    double hKernel[3] = {-1,0,1};
    convolution(img,vKernel,hKernel);
}

void pooling(Mat &img){
    Mat res = Mat(img.rows/2,img.cols/2,img.type());
    parallel_for_(Range(0,img.rows/2),[&](const Range& r) {
        for (int i = r.start; i < r.end; ++i) {
            parallel_for_(Range(0,img.cols/2),[&](const Range& s) {
                for (int j = s.start; j < s.end; ++j) {
                    Vec3d *currentPixels[4] = {&img.at<Vec3d>(i * 2, j * 2),
                                               &img.at<Vec3d>(i * 2, j * 2 + 1),
                                               &img.at<Vec3d>(i * 2 + 1, j * 2),
                                               &img.at<Vec3d>(i * 2 + 1, j * 2 + 1)};
                    Vec3d prom = Vec3d(0, 0, 0);
                    for (Vec3d *k : currentPixels) {
                        prom += *k;
                    }
                    res.at<Vec3d>(i, j) = prom / 4;
                }
            });
        }
    });
    res.copyTo(img);
}

int executeOperation(OPERATIONS o, Mat &img){
    double t = getTickCount();
    switch (o) {
        case RELOAD:
            img = loadImage(photo);
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
        case POOLING:
            pooling(img);
            break;
        default:
            break;
    }
    t = ((double)getTickCount() - t)/getTickFrequency();
    if(o!=NONE){
        cout << "Operation execution time:  " << t << "s." << endl;
    }
    if(!img.data){
        return FAIL;
    }
    return EXIT;
}
