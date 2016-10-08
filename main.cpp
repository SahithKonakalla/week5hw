#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;

int main(int argc, char* argv[]) {
  std::string fileLocation = argv[1];
  Mat img_rgb = imread(fileLocation);

  Mat img_hsv;
  cvtColor(img_rgb, img_hsv, CV_BGR2HSV);
  std::vector<cv::Mat> channels;
  split(img_hsv, channels);

  Mat hueOrig = channels.at(0).clone();
  Mat threshLower, threshUpper;
  Mat result;

  threshold(hueOrig, threshLower, 130, 255, CV_THRESH_BINARY);
  threshold(hueOrig, threshUpper, 200, 255, CV_THRESH_BINARY_INV);

  result = threshLower & threshUpper;
  imshow("Flag-Hue", result);

  Mat edges;
  std::vector<std::vector<Point> > contours;

  Canny(result, edges, 0, 25, 3, false);

  imshow("Cannied", edges);

  cv::findContours(edges, contours, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

  Mat drawing = Mat::zeros(edges.size(), CV_8UC3);

  for(int i = 0; i< contours.size(); i++) {
    cv::drawContours(drawing, contours, i, 65, 1, 8, 0, 0, Point());
  }

  imshow("Contours", drawing);

  waitKey(0);

}
