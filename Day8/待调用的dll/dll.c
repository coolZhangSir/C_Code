#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
_declspec(dllexport) void go() {
	MessageBoxA(0, "���óɹ�", "����", 0);
}

_declspec(dllexport) void run(char* content) {
	MessageBoxA(0, content, "����", 0);
}