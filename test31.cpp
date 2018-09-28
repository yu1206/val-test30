
#include <fstream>
#include <iostream>
#include <string>
#include <sstream> 
#include "opencv\cv.h"
#include "opencv\highgui.h"
#include <direct.h>
using namespace cv;
using namespace std;
int test31(int argc, char *argv[])
{
	
	string  labelpath = "I:/双个车牌放在一起/car0-hong-singlewhite-10-biaoji-train-分开/0_one.txt";
	string drawPath = "I:/双个车牌放在一起/car0-hong-singlewhite-10-biaoji-train-分开/result";
	mkdir(drawPath.c_str());
	fstream finRead;
	finRead.open(labelpath, ios::in);
	if (!finRead.is_open())
	{
		cout << "finRead 文件数据打开错误！" << endl;
		system("pause");
		return false;
	}

	

	string line;
	while (getline(finRead, line))
	{
		if (line.empty())
		{
			break;
		}
		
		 string ntxt; int label; Point pt1, pt2; Point pt[8];
			stringstream str_s(line);
			str_s >> ntxt >> label >> pt1.x >> pt1.y >> pt2.x >> pt2.y >> pt[0].x >> pt[0].y
				>> pt[1].x >> pt[1].y >> pt[2].x >> pt[2].y >> pt[3].x >> pt[3].y >> pt[4].x >> pt[4].y
				>> pt[5].x >> pt[5].y >> pt[6].x >> pt[6].y >> pt[7].x >> pt[7].y >> pt[8].x >> pt[8].y;
				

			int npos = ntxt.find_last_of('\\');
			int npos2 = ntxt.find_last_of('.');
			string nameImage = ntxt.substr(npos + 1, npos2 - npos - 1);
			Mat img = imread(ntxt.c_str());
			if (img.data == NULL)
			{
				printf("读入图像失败\n");
				system("pause");
				continue;
			}

			printf("%s:\n", ntxt.c_str());

			char file[128];
			rectangle(img,pt1,pt2,Scalar(0,255,0));
			for (int i = 0; i < 8;i++)
			{
				circle(img,pt[i],1,Scalar(0,0,255));
				
			}
			for (int i = 0; i < 4; i++)
			{
				sprintf(file, "%d", i);
				putText(img, file, Point(pt[i].x, pt[i].y-50), FONT_HERSHEY_COMPLEX, 2, Scalar(0, 0, 255));
			}
		
			for (int i = 4; i < 8; i++)
			{
				sprintf(file, "%d", i);
				putText(img, file, Point(pt[i].x, pt[i].y), FONT_HERSHEY_COMPLEX, 2, Scalar(0, 0, 255));
			}

			char filename[1024];
			sprintf(filename, "%s/%s-%d.jpg", drawPath.c_str(), nameImage.c_str(), label);
			imwrite(filename, img);

		
	}
	finRead.close();
	
	return 0;
}