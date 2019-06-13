#include <iostream>

#include <opencv2/dnn_superres.hpp>

using namespace std;
using namespace cv;
using namespace dnn;
using namespace dnn_superres;

int main(int argc, char *argv[])
{   
    // Check for valid command line arguments, print usage
    // if insufficient arguments were given.
    if (argc < 3) {
        cout << "usage:   Arg 1: image     | Path to image" << endl;
        cout << "\t Arg 2: algorithm | edsr, espcn, fsrcnn or lapsrn" << endl;
        return -1;
    }
    string img_path = string(argv[1]);
    string algorithm = string(argv[2]);

    // Load the image
    Mat img = cv::imread(img_path);
    Mat original_img(img);
    if (img.empty())
    {
        std::cerr << "Couldn't load image: " << img << "\n";
        return -2;
    }

    //Make dnn super resolution instance
    DnnSuperResImpl sr;
    Mat img_new;

    if(algorithm == "bilinear"){
        img_new = sr.upsampleBilinear(img, 2);
    }
    else if(algorithm == "bicubic")
    {
        img_new = sr.upsampleBicubic(img, 2);
    }
    else{ //one of the neural networks
        sr.setModel(algorithm);
        img_new = sr.upsample(img, 2);
    }

    if (img_new.empty())
    {
        std::cerr << "Upsampling failed. \n";
        return -3;
    }
    cout << "Upsampling succeeded. \n";    

    // Display image
    cv::namedWindow("Initial Image", WINDOW_AUTOSIZE);
    cv::imshow("Initial Image", img_new);
    //cv::imwrite("./saved.jpg", img_new);
    cv::waitKey(0);

    return 0;
}