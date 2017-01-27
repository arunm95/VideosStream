// VideosStream.cpp : Defines the entry point for the console application.
//Adapted from code from BlackMagic's API examples, and also uses code from github user motiz88.
//Arun Raghavnn - 2016

#include "stdafx.h"
#include <iostream>
#include <utility>
#include <vector>
#include <limits>
#include <errno.h>
#include "opencv2/imgproc.hpp"
#include <boost/foreach.hpp>
#include <boost/format.hpp>

#include "DeckLinkAPI_h.h"
#include <stdio.h>
#include "ComPtr.h"
#include <sstream>
#include "DeckLinkCapture.h"
#include "DeckLinkCreateInstance.h"
#include "CoInitializer.h"

int main(int argc, char** argv)
	{
		CCoInitializer coinit;
		ComPtr<IDeckLinkIterator> deckLinkIterator = CreateDeckLinkIteratorInstance();
		if (!deckLinkIterator) {
			std::cerr << argv[0]
				<< "Unable to get iterator."
				<< std::endl;
			cv::waitKey(-1);
			return 1;
		}

		std::vector<std::string> windows;
		IDeckLink* deckLink;
		cv::VideoWriter recorder;
		std::string rec, file;
		std::cout << "Do you wish to record (y/n)?" << std::endl;
		std::cin >> rec;
		while (rec != "y" && rec != "n") {
			std::cout << "Invalid input. Please enter 'y' or 'n'." << std::endl;
			std::cin >> rec;
		}
		bool record = (rec == "y");
		try {
			if (deckLinkIterator->Next(&deckLink) == S_OK) { //changed from while to if
				DeckLinkCapture capture = DeckLinkCapture(ComPtr<IDeckLink>(deckLink));
				capture.Init();
				if (!capture.start(TRUE, -1)) {
					std::cerr << "Capture could not be started." << std::endl;
					return -1;
				}
				if (record) {
					std::cout << "Please enter the file location like so : F:\\exp\\test.avi (this is just an example)." << std::endl;
					std::cin >> file;
					std::stringstream ss;
					for (int i = 0; i < file.length(); ++i) {
						if (file[i] == 47) {
							ss << "\\";
						}
						else {
							ss << file[i];
						}
					}
					cv::Size size(1920, 1080);
					recorder.open(file, CV_FOURCC('D', 'I', 'V', 'X'), 30.00, size, true);
					if (!recorder.isOpened()) {
						std::cerr << "Videowriter could not be opened. The folder you wish to record in must exist before you write video there." << std::endl;
					}
				}
				cv::namedWindow("VideoStream");
				//NO ERROR HANDLING FOR CASE THAT DEVICE DOES NOT EXIST.
				while (true) {
					cv::Mat frame, show;
					if (!capture.grab()) {
						std::cerr << "Input callback does not exist." << std::endl;
					}
					if (capture.retrieve(frame)) {
						cv::resize(frame, show, cv::Size(1280, 720));
						cv::imshow("VideoStream", show);
					}
					if (record) {
						recorder.write(frame);
					}
					if (cv::waitKey(10) >= 0)
						break;
				}
				capture.stop();
			}
			else {
				std::cerr << "No DeckLink Device Found." << std::endl;
				cv::waitKey(-1); 
				return -1;
			}
		}
		catch (std::exception e) {
			std::cerr << "Unknown Exception, it is possible that the decklink device does not exist." << std::endl;
			cv::waitKey(-1);
			return 2;
		}

		cv::destroyAllWindows();

		return 0;
	}
