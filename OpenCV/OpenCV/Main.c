#include "ImageRecognize.h"

int main() {
	while (1) {
		printf("����״����ʾ��1,���Ƶ���ʾ��2.\n");
		int option = 0;
		scanf("%d",&option);
		if (option == 1)
		{
			RecognizeShape();
		}
		else if(option == 2){
			recognizeLicensePlate();
		}
		else
		{
			printf("����,Ī����!\n");
		}
	}
	return 0;
}