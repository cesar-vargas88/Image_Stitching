#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/stitching.hpp>
#include <iostream>

using namespace std;
using namespace cv;

vector<Mat> imgs;

vector<string> images_source{	"C:/Users/cesar.vargas/Downloads/lanscape 2.jpg", 
								"C:/Users/cesar.vargas/Downloads/lanscape 3.jpg",
								"C:/Users/cesar.vargas/Downloads/lanscape 4.jpg", 
								"C:/Users/cesar.vargas/Downloads/lanscape 5.jpg", 
								"C:/Users/cesar.vargas/Downloads/lanscape 1.jpg" };

string image_result = "image_result.jpg";

int parseCmdArgs(vector<string> images_source);

int main()
{
	int retval = parseCmdArgs(images_source);
	if (retval) return EXIT_FAILURE;

	Mat pano;
	Ptr<Stitcher> stitcher = Stitcher::create(Stitcher::PANORAMA);
	Stitcher::Status status = stitcher->stitch(imgs, pano);

	if (status != Stitcher::OK)
	{
		cout << "Can't stitch images, error code = " << int(status) << endl;
		return EXIT_FAILURE;
	}

	imwrite(image_result, pano);
	cout << "stitching completed successfully\n" << image_result << " saved!";
	return EXIT_SUCCESS;

	return 0;
}

int parseCmdArgs(vector<string> images_source)
{
	if (images_source.size() < 2)
		return EXIT_FAILURE;

	for (int index = 0; index < images_source.size(); index++)
	{
		Mat img = imread(samples::findFile(images_source[index]));

		if (img.empty())
		{
			cout << "Can't read image '" << images_source[index] << "'\n";
			return EXIT_FAILURE;
		}

		imgs.push_back(img);
	}

	return EXIT_SUCCESS;
}