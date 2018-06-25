#include "ImageRecognize.h"

char* IntegerUrl[10] = {"../image/IntegerCharacter/no0.bmp","../image/IntegerCharacter/no1.bmp","../image/IntegerCharacter/no2.bmp",
						"../image/IntegerCharacter/no3.bmp","../image/IntegerCharacter/no4.bmp","../image/IntegerCharacter/no5.bmp",
						"../image/IntegerCharacter/no6.bmp","../image/IntegerCharacter/no7.bmp","../image/IntegerCharacter/no8.bmp",
						"../image/IntegerCharacter/no9.bmp"};

//����û��I��O����������Ҳû����������ĸ��Ϊ�˷�ֹ��1��0����,�����ڴ����ʱ������ȱ��������ĸ��ƥ����±���ܻ������
//���ƥ����±�С��I����ԭ��ֱ�ӷ��أ��������IС��O������Ҫ��1���������O������Ҫ��2����
char* EnglishUrl[24]= {"../image/EnglishCharacter/A.bmp","../image/EnglishCharacter/B.bmp","../image/EnglishCharacter/C.bmp",
						"../image/EnglishCharacter/D.bmp","../image/EnglishCharacter/E.bmp","../image/EnglishCharacter/F.bmp",
						"../image/EnglishCharacter/G.bmp","../image/EnglishCharacter/H.bmp","../image/EnglishCharacter/J.bmp",
						"../image/EnglishCharacter/K.bmp","../image/EnglishCharacter/L.bmp","../image/EnglishCharacter/M.bmp",
						"../image/EnglishCharacter/N.bmp","../image/EnglishCharacter/P.bmp","../image/EnglishCharacter/Q.bmp",
						"../image/EnglishCharacter/R.bmp","../image/EnglishCharacter/S.bmp","../image/EnglishCharacter/T.bmp",
						"../image/EnglishCharacter/U.bmp","../image/EnglishCharacter/V.bmp","../image/EnglishCharacter/W.bmp",
						"../image/EnglishCharacter/X.bmp","../image/EnglishCharacter/Y.bmp","../image/EnglishCharacter/Z.bmp"};

void recognizeLicensePlate(){
	
	IplImage* src = cvLoadImage("+../image/plate1.jpg",CV_LOAD_IMAGE_ANYCOLOR);
	IplImage* graySrc = cvLoadImage("../image/plate1.jpg",CV_LOAD_IMAGE_GRAYSCALE);
	IplImage* binarySrc = cvCreateImage(cvGetSize(src), IPL_DEPTH_8U, 1);
	
	cvThreshold(graySrc,binarySrc,140,255,CV_THRESH_BINARY);

	CvMemStorage* storage = cvCreateMemStorage(0);
	CvSeq* seq;
	//����������Ҫ�ַ�����ָ����������������Ҫʹ��CV_RETR_CCOMP��ȡ����������Ҫ��list����Ϊlist�������������������
	int contourCount = cvFindContours(binarySrc,storage,&seq,sizeof(CvContour),CV_RETR_CCOMP,CV_CHAIN_APPROX_NONE,cvPoint(0,0)) - 1;
	
	CvSeq* contours = seq;
	for(;contours->h_next != 0;contours = contours->h_next){
		CvRect rect = cvBoundingRect(contours,0);

		cvDrawRect(src,cvPoint(rect.x,rect.y),cvPoint(rect.x + rect.width , rect.y + rect.height),CV_RGB(255,0,0),1,8,0);
	}

	CvSeq* copyContours = seq;
	IplImage* splitCharacter[7];
	//���������Ϊ�˺�����ָ�������ַ������õ�
	int minXArr[7];
	for(int i = 0;copyContours->h_next != 0;copyContours = copyContours->h_next,i++){
		int minX = 10000,minY = 10000,maxX = 0,maxY = 0;
		for(int j = 0;j < copyContours->total;j++){
			CvPoint* point = (CvPoint*)cvGetSeqElem(copyContours,j);
			if(point->x < minX){
				minX = point->x;
			}
			if(point->x > maxX){
				maxX = point->x;
			}
			if(point->y > maxY){
				maxY = point->y;
			}
			if(point->y < minY){
				minY = point->y;
			}
		}
		if(i < 7){
			int width = maxX - minX;
			int height = maxY - minY;
			splitCharacter[i] = cvCreateImage(cvSize(width,height),graySrc->depth,graySrc->nChannels);
			minXArr[i] = minX;
			//���ַ��ָ����д���Ӧ��ͼƬ��������
			cvSetImageROI(graySrc,cvRect(minX,minY,width,height));
			cvCopy(graySrc, splitCharacter[i], NULL);
			cvResetImageROI(src);
		}
	}

	//�ȶԴ�����ַ������Ÿ��򣬰�minX�Ĵ�С��С������
	for(int i = 0;i < 6;i++){
		for(int j = i + 1;j < 7;j++){
			if(minXArr[i] > minXArr[j]){
				int tempX = minXArr[i];
				minXArr[i] = minXArr[j];
				minXArr[j] = tempX;

				IplImage* temp = splitCharacter[i];
				splitCharacter[i] = splitCharacter[j];
				splitCharacter[j] = temp;
			}
		}
	}

	//����ЩͼƬ��С��ģ��ߴ�
	IplImage* resizeCharacter[7];
	for(int i = 0;i < 7;i++){
		resizeCharacter[i] = cvCreateImage(cvSize(20,40),graySrc->depth,graySrc->nChannels);
		cvResize(splitCharacter[i],resizeCharacter[i],CV_INTER_AREA);
	}

	for(int i = 0;i < 7;i++){
		char name[2];
		//itoa�ǽ�����ת�����ַ����ĺ������������治Ҫ��char*�����ǳ��������ɱ䣬���ܱ�ת����ֵ����Ҫ��char[]����
		_itoa(i,name,10);
		cvNamedWindow(name, CV_WINDOW_AUTOSIZE);
		cvShowImage(name,resizeCharacter[i]);
		printf("%s\n",name);
	}

	
	//��ʼʶ��
	//һ������Ҫռ�����ֽڣ���Ĭ�Ϻ�����'\0'����������Ĵ�СΪ����+1���ѹ��ָ�ֵ��������ĸ����ֱ�Ӵ��±�2�������ַ�'\0'��ֱ�Ӹ���
	
	char results[9] = "��";
	for(int i = 1;i < 7;i++){
		results[i + 1] = recongnize(i,resizeCharacter[i]);
	}
	printf("���³��ƺ��е�����Ϊ:\n%s\n",results);

	//recongnize(2,resizeCharacter[2]);
	
	cvNamedWindow("src", CV_WINDOW_AUTOSIZE);
	cvShowImage("src",src);
	
	cvWaitKey(0);
}

char recongnize(int i,IplImage* image){
	//�Ƚ����ͼ���ж�ֵ��
	cvThreshold(image,image,150,255,CV_THRESH_BINARY);
	switch(i){
	/*case 0:		//ֱ�ӷ��ع̶�����Ĺ���
		return "��";
		break;*/
	case 1:		//ʶ��Ӣ���ַ�
		return recongnizeEnglishCharacter(image);
		break;	
	default:	//ʶ������
		return recongnizeIntegerCharacter(image);
		break;	
	}
}

//��ȡ������ƥ����ĸ
char recongnizeEnglishCharacter(IplImage* image){
	IplImage* templates[24];
	//�����е��ַ�ģ�嵼�����
	for(int i = 0;i < 24;i++){
		templates[i] = cvLoadImage(EnglishUrl[i],CV_LOAD_IMAGE_ANYCOLOR);
	}

	//������ȥ�Ա�������ͼ��֮��Ĳ��
	double result[24];
	for(int i = 0;i < 24;i++){
		int differenceCount = 0;
		for(int j = 0;j < image->height;j++){
			unsigned char* srcData = (unsigned char*)image->imageData + j * image->widthStep;
			unsigned char* tempData = (unsigned char*)templates[i]->imageData + j * templates[i]->widthStep;
			for(int k = 0;k < image->width;k++){
				if(*(srcData + k) != *(tempData + k)){
					differenceCount++;
				}
			}
		}
		result[i] = differenceCount / 800.0; //��Ϊresult��double���͵ģ����Է��ӷ�ĸ��һ��������С�����͵ģ���Ȼ��Ϊ0��
	}

	//������������ҳ���ֵ��С���±꼴Ϊƥ����ĸ��������Ҫ�������±���Ϊ����������ĸ���µ����
	double min = 100;
	int index = 0;
	for(int i = 0;i < 24;i++){
		if(result[i] < min){
			min = result[i];
			index = i;
		}
	}

	//�������
	if((index + 'A') > 'I' && (index + 'A') < 'O'){
		index++;
	}else if((index + 'A') > 'O'){
		index += 2;
	}

	//���껹��Ҫ�ͷ���Щģ��ͼƬ
	for(int i = 0;i < 24;i++){
		cvReleaseImage(&templates[i]);
	}
	return 'A' + index;
}

//��ȡ������ƥ������
char recongnizeIntegerCharacter(IplImage* image){
	//����Щģ��ͼƬ�����һ�����鷽��������ƥ��
	IplImage* templates[10];
	for(int i = 0;i < 10;i++){
		templates[i] = cvLoadImage(IntegerUrl[i],CV_LOAD_IMAGE_GRAYSCALE);
	}	

	//������ͼƬ����������ƥ��
	double result[10] = { 0.0 };
	for(int i = 0;i < 10;i++){
		int differenceCount = 0;
		for(int j = 0;j < templates[i]->height;j++){
			unsigned char* srcData = (unsigned char*)image->imageData + j * image->widthStep;
			unsigned char* templateData = (unsigned char*)templates[i]->imageData + j * templates[i]->widthStep;
			for(int k = 0;k < templates[i]->width;k++){
				if(*(srcData + k) != *(templateData + k)){
					differenceCount++;
				}
			}
		}
		result[i] = differenceCount / 800.0;
	}
	//����������ҳ������С����һ��ģ�弴Ϊƥ���ַ�
	double min = 100;
	int index = 0;
	for(int i = 0;i < 10;i++){
		if(result[i] < min){
			min = result[i];
			index = i;
		}
	}
	
	//���껹��Ҫ�ͷ�һ����ЩͼƬ
	for(int i = 0;i < 10;i++){
		cvReleaseImage(&templates[i]);
	}
	return index + '0';
}


/*HU����Щģ��ƥ�䶼���ѵģ�������
char recongnizeIntegerCharacter(IplImage* image){
	CvSeq* srcSeq;
	srcSeq = findContour(image);

	//����Щģ��ͼƬ�����һ�����鷽��������ƥ��
	IplImage* templates[10];
	for(int i = 0;i < 10;i++){
		templates[i] = cvLoadImage(IntegerUrl[i],CV_LOAD_IMAGE_GRAYSCALE);
	}

	//����Щģ��ͼƬ����������ȫ��Ū����
	CvSeq* seqs[10];
	for(int i = 0;i < 10;i++){
		seqs[i] = findContour(templates[i]);
	}
	//�������ģ������Ҫ����ƥ���ͼƬ��hu�صĲ�
	double results[10];
	for(int i = 0;i < 10;i++){
		results[i] = cvMatchShapes(srcSeq,seqs[i],2);
	}
	//�ҳ������С����һ������ƥ��ɹ��ģ��±꼴Ϊ��Ӧ��ƥ������
	double min = 10000;
	int index = 0;
	for(int i = 0;i < 10;i++){
		if(results[i] < min){
			min = results[i];
			index = i;
		}
		printf("min:%lf,i:%d\n",results[i],i);
	}
			printf("���������:%d\n",index);
	//������ת��Ϊ�ַ���Ҫ�����ַ�0��Ϊ��Ӧ�ַ�
	return index + '0';
}

//Ѱ������
CvSeq* findContour(IplImage* src){
	IplImage* image = cvCreateImage(cvGetSize(src),8,1);
	cvCopy(src,image);
	
	cvThreshold(image,image,140,255,CV_THRESH_BINARY);

	cvNamedWindow("test");
	cvShowImage("test",image);
	
	cvWaitKey(0);

	CvMemStorage* storage = cvCreateMemStorage(0);
	CvSeq* seq;
	cvFindContours(image,storage,&seq,sizeof(CvContour),CV_RETR_CCOMP,CV_CHAIN_APPROX_NONE,cvPoint(0,0));
	cvReleaseImage(&image);
	return seq;
}
*/