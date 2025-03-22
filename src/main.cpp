
#include "yolo-inference/yolo.h"

int main(int argc, char* argv[])
{
	if (argc != 7)
	{
		std::cerr << "argv input error" << std::endl;
		return -1;
	}
	std::cout << argv[1] << " " << argv[2] << " " << argv[3] << " " << argv[4] << " " << argv[5] << " " << argv[6] << std::endl;

	cv::Mat img = cv::imread("../bus.jpg");
	std::unique_ptr<YOLO> yolo = CreateFactory::instance().create(Backend_Type(atoi(argv[1])), Task_Type(atoi(argv[2])));
	yolo->init(Algo_Type(atoi(argv[3])), Device_Type(atoi(argv[4])), Model_Type(atoi(argv[5])), argv[6]);
	yolo->infer(img, true, true);
	yolo->release();
	return 0;
}

