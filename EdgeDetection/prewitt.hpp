#include "../Helper.hpp"
using namespace cv;
class Prewitt
{

    Mat prewitt_1 = (Mat_<float>(3, 3) << -1, -1, -1,
                     0, 0, 0,
                     1, 1, 1);

    Mat prewitt_2 = (Mat_<float>(3, 3) << -1, 0, 1,
                     -1, 0, 1,
                     -1, 0, 1);

public:
    void Work(std::string src_image_path)
    {
        auto src_image = Helper::Read(src_image_path);
        Mat grey(src_image.size(), src_image.type());
        cvtColor(src_image, grey, COLOR_RGB2GRAY);

        Mat temp(grey.size(), grey.type());
        // Sobel(src_image,temp,CV_16S,0,1);
        auto rows = temp.rows;
        auto cols = temp.cols;
        for (int i = 0; i < rows - 3; i++)
            for (int j = 0; j < cols - 3; j++)
            {
                // break;
                auto s1 = conv(i, j, grey, prewitt_1);

                auto s2 = conv(i, j, grey, prewitt_2);
                auto res = max(s1, s2);

                temp.at<float>(i, j) = res;
            }
        auto dst_image_name = Helper::Set_extra_name(src_image_path, "prewitt");
        threshold(temp, temp, 0, 255, THRESH_BINARY);
        Helper::Save(temp, dst_image_name);
    }

    float conv(int x, int y, Mat src, Mat kernel)
    {
        short res = 0;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
            {
                auto wcw = src.at<float>(x + i, y + j);
                res = res + src.at<float>(x + i, y + j) * kernel.at<float>(i, j);
            }
        return res;
    }
};
