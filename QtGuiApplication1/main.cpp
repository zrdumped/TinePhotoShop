#include "QtGuiApplication1.h"
#include <opencv2/opencv.hpp>
#include <QtWidgets/QApplication>
#include <iostream>
using namespace std;
using namespace cv;

int main(int argc, char *argv[])
{
	//Mat image = imread("E:\\CV\\125.png");  //����Լ�ͼ���·�� 
	//imshow("��ʾͼ��", image);
	//waitKey(0);

	QApplication a(argc, argv);
	QtGuiApplication1 w;
	w.setWindowTitle("Tiny Photoshop");
	w.show();
	return a.exec();

}

void test() {
	cout << "aa";
}

