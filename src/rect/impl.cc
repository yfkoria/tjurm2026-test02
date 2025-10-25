#include "impls.h"


std::pair<cv::Rect, cv::RotatedRect> get_rect_by_contours(const cv::Mat& input) {
    /**
     * 要求：
     * 使用findCountours函数找出输入图像（彩色图像）中的矩形轮廓，并且返回它的外接矩形，以及
     * 最小面积外接矩形。所需要的函数自行查找。
     * 
     * 通过条件：
     * 运行测试点，你找到的矩形跟答案一样就行。
    */
    std::pair<cv::Rect, cv::RotatedRect> res;
    cv::Mat gray, binary;
    cv::cvtColor(input, gray, cv::COLOR_BGR2GRAY);
    cv::threshold(gray, binary, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(binary, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    std::vector<std::vector<cv::Point>> rectangle_contours;

    for (size_t i = 0; i < contours.size(); i++) {
        // std::vector<cv::Point> approx;
        // double epsilon = 0.02 * cv::arcLength(contours[i], true);
        // cv::approxPolyDP(contours[i], approx, epsilon, true);
        rectangle_contours.push_back(contours[i]);
    }
    // if (rectangle_contours.empty()) return res;

    double max_area = 0;
    int max_index = -1;
    for (size_t i = 0; i < rectangle_contours.size(); i++) {
        double area = cv::contourArea(rectangle_contours[i]);
        if (area > max_area) {
            max_area = area;
            max_index = i;
        }
    }
    res.first = cv::boundingRect(rectangle_contours[max_index]);
    res.second = cv::minAreaRect(rectangle_contours[max_index]);
    return res;
}