#ifndef KNGCAMERA_H
#define KNGCAMERA_H

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/aruco.hpp>
#include <glm/glm.hpp>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;
using namespace cv;

class KCvCamera {
	private:
		glm::mat4 mCamPose;
		int camNum=0;

		int dictionaryId = 10;//DICT_6X6_250=10
		Ptr<aruco::Dictionary> dictionary = aruco::getPredefinedDictionary(aruco::PREDEFINED_DICTIONARY_NAME(dictionaryId));
		Ptr<aruco::DetectorParameters> detectorParams = aruco::DetectorParameters::create();
	protected:
		
		bool getArucoRTVectors(cv::Mat img, vector< int > &ids, vector< vector< Point2f > > &corners);
	public:
		VideoCapture mCapture;
		KCvCamera();
		virtual ~KCvCamera();


		bool getCamImage(cv::Mat &img);

		bool init(int camNum_get, bool bThreadMode = false);
		void close();
		bool isOpened() { return mCapture.isOpened(); }
		bool getMarkerPose(int markId, glm::mat4 &camPose, cv::Mat &img, int cols = 320);
};

class KGlCamera {
	private:
	protected:
	public:
		KGlCamera();
		virtual ~KGlCamera();
};

#endif
