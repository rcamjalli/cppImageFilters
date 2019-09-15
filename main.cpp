#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace std;
using namespace cv;

const string DISPLAY_NAME = "IMAGE EDITOR";

enum OPERATIONS {EXIT = 0, RELOAD, LOWRED, LOWGREEN, LOWBLUE, BLUR, SOBEL, NONE, FAIL = -1};

Mat loadImage();
int executeOperation(int o, Mat &img);

int main() {
    namedWindow(DISPLAY_NAME, WINDOW_NORMAL );
    int key = NONE;

    Mat img = loadImage();
    if (!img.data){
        key = FAIL;
    }

    while(key != EXIT && key != FAIL){
        if (executeOperation(key, img) != FAIL){
            key = waitKey(0);
            if (48 <= key && key <= 57){
                key -= 48;
            }else{
                key = NONE;
            }
        }else{
            key = FAIL;
        }
    }


    return key;
}


Mat loadImage(){
    Mat img = imread("../photo.jpeg", IMREAD_COLOR);
    return img;
}

void showImage(Mat &img){
    imshow(DISPLAY_NAME, img);
}

void generalEdition(Mat &img, std::function<void(Vec3b &pixel)> functor){
    parallel_for_(Range(0,img.rows),[&](const Range& r) {
        for (int i = r.start; i < r.end; ++i) {
            for (int j = 0; j < img.cols; ++j) {
                functor(img.at<Vec3b>(i, j));
            }
        }
    });
}

void editImage(Mat &img, int option){
    generalEdition(img,[&](Vec3b &pixel){
        uchar *blue = &pixel.val[0];
        uchar *green = &pixel.val[1];
        uchar *red = &pixel.val[2];

        if (*blue >= 5 && option == LOWBLUE) {
            *blue -= 5;
        }

        if (*green >= 5 && option == LOWGREEN) {
            *green -= 5;
        }

        if (*red >= 5 && option == LOWRED) {
            *red -= 5;
        }
    });
}

void convolute1D(Mat &img, const double kernel[3], bool isVertical){
    const int max_i = isVertical ? img.cols : img.rows;
    const int max_j = isVertical ? img.rows : img.cols;
    parallel_for_(Range(0,max_i),[&](const Range& r) {
        for (int i = r.start; i < r.end; ++i) {
            for (int j = 1; j < max_j-1; ++j) {
                Vec3i *pixel = isVertical ? &img.at<Vec3i>(j, i) : &img.at<Vec3i>(i, j);
                Vec3i a = isVertical ? img.at<Vec3i>(j-1,i): img.at<Vec3i>(i, j-1);
                a *= kernel[0];
                Vec3i b = isVertical ? img.at<Vec3i>(j,i): img.at<Vec3i>(i, j);
                b *= kernel[1];
                Vec3i c = isVertical ? img.at<Vec3i>(j+1,i): img.at<Vec3i>(i, j+1);
                c *= kernel[2];
                *pixel = a+b+c;
            }
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
    double vKernel[3] = {-0.5,0.75,-0.5};
    double hKernel[3] = {-1,0,1};
    convolution(img,vKernel,vKernel);
}

int executeOperation(int o, Mat &img){
    double t = getTickCount();
    switch (o) {
        case RELOAD:
            img = loadImage();
            break;
        case LOWRED:
        case LOWGREEN:
        case LOWBLUE:
            editImage(img, o);
            break;
        case BLUR:
            blurImage(img);
            break;
        case SOBEL:
            sobelFilter(img);
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
    showImage(img);
    return EXIT;
}

