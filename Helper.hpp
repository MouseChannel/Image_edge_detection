#pragma once
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>

namespace Helper
{
    using namespace cv;
    Mat Read(std::string path)
    {
        return imread(path);
    }
    void Save(Mat image, std::string path)
    {
        imwrite(path, image);
    }

    auto Get_File_name(std::string name)
    {
        auto index_name = name.find_last_of('/');

        auto index_postfix = name.find_last_of('.');
        auto postfix = name.substr(index_postfix);
        auto file_name = name.substr(index_name + 1, index_postfix - index_name - 1);

        return file_name;
    }
    auto Get_postfix(std::string name)
    {
        auto index_postfix = name.find_last_of('.');
        auto postfix = name.substr(index_postfix + 1);
        return postfix;
    }

    auto Get_dir_name(std::string name)
    {
        auto index_name = name.find_last_of('/');
        return name.substr(0, index_name + 1);
    }
    auto Set_extra_name(std::string src_image_path, std::string extra)
    {
        auto file_name = Get_File_name(src_image_path);
        auto postfix = Get_postfix(src_image_path);
        auto dir_name = Get_dir_name(src_image_path);
        return dir_name +""+ file_name + "_" + extra + "." + postfix;
    }
} // namespace homework_2
