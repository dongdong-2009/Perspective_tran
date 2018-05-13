/*
imrang是否可以不针对hsv的挑选
如果有针对那就写转化*/
#include "stdafx.h" 
#include<opencv2/core.hpp>  
#include<opencv2/highgui.hpp>  
#include<opencv2/imgproc.hpp>  

#include<iostream>  
#include<string> 

using namespace cv;
using namespace std;


/*Point2f的列坐标在前，行坐标在后*/
int main()
{
	int i = 0;
	int j = 0;
	int count = 0;
	int flag1 = 0;
	int flag2 = 0;
	int bad = 0;
	int max[2] = { 0,0 };
	int min[2] = { 100000,100000 };

	vector<Point2f> corners(4);
	corners[0] = Point2f(0, 0);
	corners[2] = Point2f(0, 72);
	corners[1] = Point2f(97, 0);
	corners[3] = Point2f(97, 72);
	vector<Point2f> corners_trans(4);
	corners_trans[0] = Point2f(0, 0);
	corners_trans[2] = Point2f(140, 277);
	corners_trans[1] = Point2f(330, 0);
	corners_trans[3] = Point2f(190, 277);

	Mat transform = getPerspectiveTransform(corners_trans, corners);
	cout << transform << endl;
	vector<Point2f> points, points_trans;
	for (int i = 0; i<=277; i++) 
	{
		for (int j = 0; j<=330; j++) 
		{
			points_trans.push_back(Point2f(j, i));
		}
	}

	perspectiveTransform(points_trans, points, transform);
	count = 0;
	for (int i = 0; i <= 277; i++)
	{
		for (int j = 0; j <= 330; j++)
		{
			if (points[count].x < 0)
			{
				points[count].x = 0;
				flag1++;
			}
			if (points[count].x > 97)
			{
				points[count].x = 97;
				flag1++;
			}
			if (points[count].y < 0)
			{
				points[count].y = 0;
				flag2++;
			}
			if (points[count].y > 72)
			{
				points[count].x = 72;
				flag2++;
			}
			if (flag1 != 0 && flag2 != 0)
			{
				if (i < min[0]) min[0] = i;
				if (i > max[0]) max[0] = i;
				if (j < min[1]) min[1] = j;
				if (j > max[1]) max[1] = j;
				bad++;
			}
			flag1 = 0;
			flag2 = 0;
			count++;
		}
	}
	//FILE *fp=fopen("E:\\github\\transform\\transform\\data\\BP_rivise.txt","w");
	//if(!fp)
	//{
	//    printf("Can't open file\n");
	//    return 0;
	//}
	//count = 0;
	//for (int i = 0; i <= 277; i++)
	//{
	//	fprintf(fp, "{");
	//	for (int j = 0; j <= 330; j++)
	//	{
	//		fprintf(fp, "{%3d,%3d} ", (int)points[count].y, (int)points[count].x);
 //           if(j<330) fprintf(fp,",");
	//		count++;
	//		if(0==count%10) fprintf(fp,"\n");
	//	}
	//	fprintf(fp, "}");
	//	if(i<277) fprintf(fp,",");
	//}
	//fclose(fp);

	cout << count << endl;
	cout << bad << endl;
	cout << min[0] << endl;
	cout << max[0] << endl;
	cout << min[1] << endl;
	cout << max[1] << endl;
	getchar();
	return 0;
}

//     for(i=0;i<ROW;i++)
//         {
//             
//             for(j=0;j<COL;j++)
//             {
//                 
//             }
//             
//         }

//int main()
//{
//	vector<Point2f> corners(4);
//	corners[0] = Point2f(0, 0);								//左上
//	corners[1] = Point2f(img_width - 1, 0);					//右上
//	corners[2] = Point2f(0, img_height - 1);				//左下
//	corners[3] = Point2f(img_width - 1, img_height - 1);	//右下
//	vector<Point2f> corners_trans(4);
//	corners_trans[0] = Point2f(0, 0);
//	corners_trans[1] = Point2f(990, 0);
//	corners_trans[2] = Point2f(420, 831);
//	corners_trans[3] = Point2f(570, 831);
//
//	Mat transform = getPerspectiveTransform(corners_trans, corners);
//	cout << transform << endl;
//	vector<Point2f> ponits, points_trans;
//	for (int i = 0; i<img_height + 600; i++)
//	{
//		for (int j = 0; j<img_width + 500; j++)
//		{
//			ponits.push_back(Point2f(j, i));
//		}
//	}
//
//	perspectiveTransform(ponits, points_trans, transform);
//	Mat img_trans = Mat::zeros(img_height + 600, img_width + 500, CV_8UC3);
//	int count = 0;
//	for (int i = 0; i<img_height + 600; i++)
//	{
//		uchar* p = img_trans.ptr<uchar>(i);
//		for (int j = 0; j<img_width + 500; j++)
//		{
//			int y = points_trans[count].y;
//			int x = points_trans[count].x;
//			if (x > 550 || x < 0 || y>272 || y < 0)
//			{
//				count++;
//			}
//			else
//			{
//				uchar* t = img.ptr<uchar>(y);
//				p[j * 3] = t[x * 3];
//				p[j * 3 + 1] = t[x * 3 + 1];
//				p[j * 3 + 2] = t[x * 3 + 2];
//				count++;
//			}
//		}
//	}
//	imwrite("boy_trans.png", img_trans);
//	imshow("dst", img_trans);
//	cvWaitKey(0);
//
//	return 0;
//}