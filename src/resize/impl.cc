#include "impls.h"


cv::Mat my_resize(const cv::Mat& input, float scale) {
    /**
     * 要求：
     *      实现resize算法，只能使用基础的语法，比如说for循环，Mat的基本操作。不能
     * 用cv::resize。resize算法的内容自行查找学习，不是很难。
     * 
     * 提示：
     * 无。
     * 
     * 通过条件：
     * 运行测试点，你的结果跟答案长的差不多就行。
     */
    int new_rows = input.rows * scale, new_cols = input.cols * scale;
    cv::Mat output(new_rows, new_cols, input.type());
    float row_ratio = static_cast<float>(input.rows) / new_rows;
    float col_ratio = static_cast<float>(input.cols) / new_cols;
    for (int i = 0; i < new_rows; i++) {
        for (int j = 0; j < new_cols; j++) {
            float src_i = i * row_ratio;
            float src_j = j * col_ratio;
            int i1 = static_cast<int>(src_i);
            int j1 = static_cast<int>(src_j);
            int i2 = i1 + 1;
            int j2 = j1 + 1;
            if(i2 >= input.rows) i2 = input.rows - 1;
            if(j2 >= input.cols) j2 = input.cols - 1;
            float di = src_i - i1;
            float dj = src_j - j1;
            float w1 = (1 - di) * (1 - dj);
            float w2 = (1 - di) * dj;
            float w3 = di * (1 - dj);
            float w4 = di * dj;
            if (input.channels() == 1) {
                float value = w1 * input.at<uchar>(i1, j1) + w2 * input.at<uchar>(i1, j2) + w3 * input.at<uchar>(i2, j1) + w4 * input.at<uchar>(i2, j2);
                output.at<uchar>(i, j) = static_cast<uchar>(value + 0.5f);
            }
            else if (input.channels() == 3) {
                cv::Vec3b p1 = input.at<cv::Vec3b>(i1, j1),p2 = input.at<cv::Vec3b>(i1, j2),p3 = input.at<cv::Vec3b>(i2, j1),p4 = input.at<cv::Vec3b>(i2, j2);
                cv::Vec3b value;
                for (int c = 0; c < 3; c++) {
                    float channel_value = w1 * p1[c] + w2 * p2[c] + w3 * p3[c] + w4 * p4[c];
                    value[c] = static_cast<uchar>(channel_value + 0.5f);
                }
                output.at<cv::Vec3b>(i, j) = value;
            }
        }
    }
    return output;
}