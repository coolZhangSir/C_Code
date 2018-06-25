#include "ImageRecognize.h"

void RecognizeShape() {

	shape simpleShapes[15];
	int shapeCount = 0;

	char* color[6] = {"��","��","��","��","��","��"};
	int circleCount = 0;
	int rectangleCount = 0;
	int triangleCount = 0;
	//ͼƬ��
	char *fileName = "./src1.jpg";
	//��ֵ
	int threshold = 250;

	IplImage* src = cvLoadImage(fileName,CV_LOAD_IMAGE_COLOR);
	IplImage* grayImage = cvLoadImage(fileName,CV_LOAD_IMAGE_GRAYSCALE);
	IplImage* binaryImage = cvCreateImage(cvGetSize(src),IPL_DEPTH_8U,1);
	IplImage* contourImage = cvCreateImage(cvGetSize(src),IPL_DEPTH_32F,3);

	//���ͼ��ֵ����160������������ȫ������
	cvThreshold(grayImage,binaryImage, threshold,255,CV_THRESH_BINARY);

	/*cvNamedWindow("test");
	cvShowImage("test", binaryImage);
	cvWaitKey(0);*/

	//Ѱ�Ҹ�ͼ������
	CvMemStorage* storage = cvCreateMemStorage(0);
	CvSeq* seq;
	int contours = cvFindContours(binaryImage,storage,&seq,sizeof(CvContour),CV_RETR_LIST,CV_CHAIN_APPROX_NONE,cvPoint(0,0)) - 1;

	//���ڶ���αƽ����ڴ������
	CvMemStorage* storage1 = cvCreateMemStorage(0);
	CvSeq* vertexSeq;

	for(;seq->h_next != 0;seq = seq->h_next){
		int minX = 10000,maxX = 0;
		int minY = 10000,maxY = 0;
		int centralPointY = 0;
		for(int i = 0; i < seq->total;i++){
			CvPoint* point = (CvPoint*)cvGetSeqElem(seq,i);
			cvSet2D(contourImage,point->y,point->x,CV_RGB(255,0,0));
			
			//�����ｫ�������������С������X��Y����ȫ��ͳ�Ƴ���,����ֻ��ҪԲ�����ĵ㣬����
			if(point->x < minX){
				minX = point->x;
				centralPointY = point->y;
			}
			if(point->x > maxX){
				maxX = point->x;
			}
			if(point->y < minY){
				minY = point->y;
			}
			if(point->y > maxY){
				maxY = point->y;
			}
		}
		//����������������Զ�ĵ�ľ��벢����2��Ϊ�ж��Ƿ�ΪԲ�İ뾶
		int radius = (maxX - minX) / 2;
		
		//���˰뾶֮��Ϳ���ȡ�������������ĵ�
		//(��ָ�����Բ�������,����Բ�϶����������ĵ㡣��Ȼ������ĵ��������ģ��������������ص㣬���ĵ��Y��������¸����������ص�)
		CvPoint centralPoint = cvPoint(minX + radius,centralPointY);
		cvSet2D(contourImage,centralPointY,centralPoint.x,CV_RGB(255,0,0));
		
		//�ж��Ƿ�ΪԲ
		int isCircleResult = isCircle(seq,centralPoint,radius);
		int shapeName = 0;
		int colorInfo[7] = {0};

		if(isCircleResult){
			
			circleCount++;
			shapeName = 1;

			//����״�ж���֮��ֱ�Ӷ��������ɫʶ��
			recognizeColor(src,minX,minY,maxX,maxY,colorInfo);
		}else{
			//��ΪԲ����ж���αƽ�,�õ�������Ŀ
			vertexSeq = cvApproxPoly(seq,sizeof(CvContour),storage,CV_POLY_APPROX_DP,cvContourPerimeter(seq) * 0.02,0);
			int vertexCount = getVertexCount(vertexSeq);
			
			if(3 == vertexCount){
				
				triangleCount++;
				shapeName = 2;

				//����״�ж���֮��ֱ�Ӷ��������ɫʶ��
				recognizeColor(src,minX,minY,maxX,maxY,colorInfo);
			}else if(4 == vertexCount){
				//����Ҫ�Ƚ�����ɫʶ�������һ����ɫ��Ϊ���Σ�������������ϵ���ɫ����Ҫ������һ������
				recognizeColor(src,minX,minY,maxX,maxY,colorInfo);
				
				if(1 == colorInfo[0]){
					rectangleCount++;
					shapeName = 3;
				}else if(2 == colorInfo[0]){
					triangleCount += 2;
					shapeName = 2;
				}
			}
		}
		
		//��ʶ�������ͼ����״����ɫ���б��棬���ں������
		if(1 == colorInfo[0]){
			simpleShapes[shapeCount].shapeName = shapeName;
			simpleShapes[shapeCount].colorName = colorInfo[1];
			shapeCount++;
		}else if(2 == colorInfo[0]){
			simpleShapes[shapeCount].shapeName = shapeName;
			simpleShapes[shapeCount].colorName = colorInfo[1];
			shapeCount++;
			simpleShapes[shapeCount].shapeName = shapeName;
			simpleShapes[shapeCount].colorName = colorInfo[2];
			shapeCount++;
		}
	}

	//���� ��������ɫ�����εĸ���
	int count = 0;
	for(int i = 0;i < shapeCount;i++){
		if(2 == simpleShapes[i].shapeName && 0 == simpleShapes[i].colorName){
			count++;
		}
	}
	printf("��%d����ɫ������\n",count);

	cvNamedWindow("contourImage",CV_WINDOW_AUTOSIZE);
	cvShowImage("contourImage",contourImage);

	cvWaitKey(0);
}
//�ú��������ж��Ƿ�ΪԲ��������򷵻�1�����򷵻�0
int isCircle(CvSeq* seq,CvPoint centralPoint,int radius){
	//���������Ĺ�ʽ�����ÿ���㵽���ĵ�ľ����Ƿ�������(��������(10-20)�ķ�Χ��
	for(int i = 0;i < seq->total;i++){
		CvPoint* point = (CvPoint*)cvGetSeqElem(seq,i);
		int x1 = centralPoint.x;
		int x2 = point->x;

		int y1 = centralPoint.y;
		int y2 = point->y;

		int distance = (int)sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
		
		if(abs(radius - distance) > 20){
			return 0;
		}
	}
		
	return 1;
}

//����������н��б������õ�������������
int getVertexCount(CvSeq* seq){
	int count = 0;
	for(int i = 0;i < seq->total;i++){
		
		count++;
	}
	return count;
}

//��ȡ�������ڵ���ɫ
void recognizeColor(IplImage* src,int minX,int minY,int maxX,int maxY,int colorInfo[7]){
	int width = maxX - minX;
	int	height = maxY - minY;

	cvSetImageROI(src,cvRect(minX,minY,width,height));
	IplImage* copySrc = cvCreateImage(cvSize(width,height),IPL_DEPTH_8U,3);
	cvCopy(src,copySrc,NULL);	
	cvResetImageROI(src);
	
	/*
	cvNamedWindow("test");
	cvShowImage("test",copySrc);
	cvWaitKey(0);
	*/
	
	int colors[6] = {0};		//�������ÿ����ɫ���ֵĴ���,�±��Ӧ��ɫ˳����ֵĴ���
	getColorCount(copySrc,colors);
	getColorName(colors,colorInfo);
}

//ʶ�����Ӧͼ�����м�����ɫ����ʶ���������ɫ������һ�����飬���水˳�������ɫ��
void getColorCount(IplImage* src,int colors[6]){
	int nChannels = src->nChannels;
	int widthStep = src->widthStep;
	char* imageData = src->imageData;

	for(int i = 0;i < src->height;i++){
		unsigned char* row = (unsigned char*)(imageData + i * widthStep);
		for(int j = 0;j < src->width;j++){
			int b = *(row + (j * nChannels + 0));
			int g = *(row + (j * nChannels + 1));
			int r = *(row + (j * nChannels + 2));

			// �������,ֻҪ������Ҫ�жϵ�������ɫֵ����150,������ɫС��50,����������������ɫ.���ֵ��˼·���ǽ�����Ǳ��ṩ��Դ����.
			if (150 <= r && g <= 90 && b <= 90) { // �б��ɫ
				colors[0]++;
			}
			else if (r <= 90 && 150 <= g && b <= 90) { // �б���ɫ
				colors[1]++;
			}
			else if (r <= 90 && g <= 90 && 150 <= b) { // �б���ɫ
				colors[2]++;
			}
			else if (r <= 90 && 150 <= g && 150 <= b) { // �б���ɫ
				colors[3]++;
			}
			else if (150 <= r && 150 <= g && b <= 90) { // �б��ɫ
				colors[4]++;
			}
			else if (150 <= r && g <= 90 && 150 <= b) { // �б���ɫ
				colors[5]++;
			}
		}
	}
}

//��ǰһ������ȡͳ�Ƶ���ɫ���ֵĴ���������ͳ�ƴ����һ���±�,����İ�
void getColorName(int colors[6],int colorInfo[7]){
	int colorCount = 0;

	int j = 1;
	for(int i = 0;i < 6;i++){
		if(0 != colors[i]){
			//printf("j:%d,i:%d\n",j,i);
			colorCount++;
			colorInfo[j++] = i;
		}
	}
	colorInfo[0] = colorCount;
}
