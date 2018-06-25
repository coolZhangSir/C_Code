#define _CRT_SECURE_NO_WARNINGS
#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include<cv.h>
#include<highgui.h>

typedef struct shapeStruct {
	int shapeName;
	int colorName;
}shape;

int isCircle(CvSeq* seq, CvPoint point, int radius);
int getVertexCount(CvSeq* seq);
void recognizeColor(IplImage* src, int minX, int minY, int maxX, int maxY, int colorInfo[7]);
void getColorCount(IplImage* src, int color[6]);
void getColorName(int colors[6], int colorInfo[7]);
void RecognizeShape();
void recognizeLicensePlate();

#define CIRCLE 1		//Բ
#define TRIANGLE 2		//������
#define RECTANGLE 3		//����

#define RED 1			//��
#define GREEN 2			//��
#define BLUE 3			//��
#define CYAN 4			//��
#define YELLOW 5		//��
#define PURPLE 6		//��

char recongnize(int i, IplImage* image);
char recongnizeEnglishCharacter(IplImage* image);
char recongnizeIntegerCharacter(IplImage* image);
CvSeq* findContour(IplImage* src);
void RecognizeShape();

char recongnize(int i, IplImage* image);
char recongnizeEnglishCharacter(IplImage* image);
char recongnizeIntegerCharacter(IplImage* image);
CvSeq* findContour(IplImage* src);
void recognizeLicensePlate();