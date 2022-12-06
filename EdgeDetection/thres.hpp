#include "../Helper.hpp"

class thres
{
public:
    int Get_bottom_index(std::vector<int> arr)
    {
        std::vector<std::tuple<int, int>> temp;

        for (int i = 0; i < arr.size(); i++)
        {
            temp.push_back(std::make_tuple(i, arr[i]));
        }
        int offset = 50;
        sort(temp.begin() + offset, temp.end() - 100, [](std::tuple<int, int> a, std::tuple<int, int> other)
             { return std::get<1>(a) < std::get<1>(other); });
        std::cout << std::get<0>(temp[31]) << std::endl;
        int res = 9999999;
        for(int i=50;i<200;i++){
            res = min(res,arr[i]);
        }
        std::cout<<res<<std::endl;
        return std::get<0>(temp[31]);
    }
    Mat getHistImage(const Mat &src, int &mid)
    {
        std::vector<int> histogram(256);
        int tmp;

        //统计灰度个数
        for (int i = 0; i < src.rows; i++)
        {
            for (int j = 0; j < src.cols; j++)
            {
                tmp = src.at<uchar>(i, j);
                histogram[tmp]++;
            }
        }
        // Mat ewf(1,256,CV_32F,)
        Mat hist(1, 256, CV_32F, histogram.data()); //用一个一维数组实例化Mat数组：hist并初始化

        double minVal = 0;
        double maxVal = 0;
        minMaxLoc(hist, &minVal, &maxVal, 0, 0); //寻找全局最小、最大像素数目

        //绘制直方图
        Mat histImage(255, 255, CV_8UC3, Scalar(255, 255, 255));
        int hpt = static_cast<uchar>(0.9 * hist.cols); //直方图最大高度
        for (int i = 0; i < 255; i++)
        {
            float binVal = hist.at<float>(i);
            int intensity = static_cast<int>(binVal * hpt / maxVal);
            line(histImage, Point(i, hist.cols), Point(i, hist.cols - intensity), Scalar(255, 0, 0));
        }

        mid = Get_bottom_index(histogram);
        return histImage;
    }

    cv::Mat getHistImage1(const cv::Mat &hist)
    {
        double maxValue = 0;
        double minValue = 0;
        // int a=0;
        // for(int i=0;i<hist.rows;i++){
        //     for(int j=0;j<hist.cols;j++){
        //         float b=hist.at<float>(i,j);
        //         a+=1;
        //         std::cout<< b <<std::endl;  //输出该二维数组
        //     }
        // }
        minMaxLoc(hist, &minValue, &maxValue, 0, 0); //寻找全局最小、最大像素数目

        int histSize = hist.rows;
        Mat histImage(histSize, histSize, CV_8UC3, Scalar(255, 255, 255));

        int hpt = static_cast<int>(0.9 * histSize); //设置最大高度
        for (int i = 0; i < hist.rows; i++)
        {
            float binVal = hist.at<float>(i);
            int intensity = static_cast<int>(binVal * hpt / maxValue);
            cv::line(histImage, cv::Point(i, histSize), cv::Point(i, histSize - intensity), Scalar(255, 0, 0));
        }

        return histImage;
    }

    void Work(std::string src_image_path)
    {

        Mat src = imread(src_image_path, 0);
        // Mat img2=imread("C:/Users/Administrator/Desktop/dog.jpg");
        Size dsize = Size(600, 400);                 // Size型 改变尺寸
        resize(src, src, dsize, 0, 0, INTER_LINEAR); //使用双线性插值缩放一下尺寸

        int image_count = 1;               //输出单个直方图
        int channels[1] = {0};             //单通道
        Mat out;                           //输出二维数组
        int dims = 1;                      //维度为1
        int histSize[1] = {256};           //灰度值Size：256个
        float hrange[2] = {0, 255};        //灰度范围[0-255]
        const float *ranges[1] = {hrange}; //单个灰度范围[0-255]
        int mid = 0;
        // 1、计数直接统计灰度个数
        Mat histImage = getHistImage(src, mid);

        // 2、使用calcHist输出二维灰度统计数组
        calcHist(&src, image_count, channels, Mat(), out, dims, histSize, ranges);
        // Mat histImage1 = getHistImage(out); //第二种方法
        auto dst_image_name = Helper::Set_extra_name(src_image_path, "grey");
        auto dst_image_graph = Helper::Set_extra_name(src_image_path, "graph");

        Helper::Save(src, dst_image_name);
        Helper::Save(histImage, dst_image_graph);
        threshold(src, src, 78, 255, THRESH_BINARY);

        dst_image_name = Helper::Set_extra_name(src_image_path, "after");
        Helper::Save(src, dst_image_name);
    }
};