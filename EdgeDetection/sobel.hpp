#include "../Helper.hpp"
using namespace cv;
class M_Sobel

{

    Mat sobel_1 = (Mat_<float>(3, 3) << -1, -2, -1,
                   0, 0, 0,
                   1, 2, 1);

    Mat sobel_2 = (Mat_<float>(3, 3) << -1, 0, -1,
                   -2, 0, 2,
                   -1, 0, 1);

public:
    void Work(std::string src_image_path)
    {
        auto src_image = Helper::Read(src_image_path);
 
        Mat grey(src_image.size(), src_image.type());
        cvtColor(src_image, grey, COLOR_RGB2GRAY);

        Mat temp(grey.size(), grey.type());
        Sobel(grey,temp,CV_16S,1,0);
        auto rows = temp.rows;
        auto cols = temp.cols;
        for (int i = 0; i < rows - 3; i++)
            for (int j = 0; j < cols - 3; j++)
            {
                break;
                auto jj = src_image.at<float>(i, j);
                auto ww = grey.at<float>(i, j);
                auto s1 = conv(i, j, grey, sobel_1);

                auto s2 = conv(i, j, grey, sobel_2);

                auto res = sqrt(s1 * s1 + s2 * s2);

                temp.at<float>(i, j) = res;
            }
        auto dst_image_name = Helper::Set_extra_name(src_image_path, "hough");

        
        // threshold(temp, temp, 0, 255, THRESH_BINARY);

     
         
        // std::vector<Vec2f> lines;
        // HoughLines(temp, lines, 1, CV_PI / 180, 10, 0, 10);
        // for (size_t i = 0; i < lines.size(); i++)
        // {
        //     auto l = lines[i];
        //     // line(temp, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 3, LINE_AA);
        // } 
        // std::vector<Vec2f> lines;

        // HoughLines(temp, lines, 1, CV_PI / 180,100,100,10);
        // Scalar color = Scalar(0, 0, 255);
        // for (size_t i = 0; i < lines.size(); i++)
        // {
        //      auto hline = lines[i];
        //      line(temp, Point(hline[0], hline[1]), Point(hline[2], hline[3]), color, 3, LINE_AA); //绘制直线

        // }
     
        Helper::Save(temp, dst_image_name);
    }

    float conv(int x, int y, Mat src, Mat kernel)
    {
        short res = 0;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
            {
                auto wcw = src.at<float>(x + i, y + j);
                res = res + src.at<float>(x + i, y + j) * kernel.at<float>(i, j)  ;
            }
        return res;
    }
};