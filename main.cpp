#include <iostream>
#include "Helper.hpp"
#include "./EdgeDetection/prewitt.hpp"

#include "./EdgeDetection/sobel.hpp"
#include "./EdgeDetection/thres.hpp"
// using namespace cv;
using namespace std;

using namespace Helper;

 

int main(int, char **)
{

    // M_Sobel sobel_worker;
    // //  sobel_worker.Work("/home/homework_2/images/delete.jpg");

    // sobel_worker.Work("/home/homework_2/images/noddles.jpg");
    // std::cout << "finish" << std::endl;
    // //    return 0;
    // sobel_worker.Work("/home/homework_2/images/berger.jpg");

    // sobel_worker.Work("/home/homework_2/images/sushi.jpg");

    // Prewitt prewitt_worker;
    // prewitt_worker.Work("/home/homework_2/images/noddles.jpg");

    // prewitt_worker.Work("/home/homework_2/images/berger.jpg");

    // prewitt_worker.Work("/home/homework_2/images/sushi.jpg");

    thres t;
    t.Work("/home/homework_2/images/berger.jpg");
    t.Work("/home/homework_2/images/noddles.jpg");
    // t.Work("/home/homework_2/images/sushi.jpg");
    return 0;
}
