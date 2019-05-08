
//��ƽ̨��־�࣬�����ļ�
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>

#include <iostream>
#include <ratio>
#include <chrono>
#include <mutex>

namespace YLOG {
	static std::string curdate = "";	//��������

	std::string GetName(char * fileName);

	std::string getCurrentSystemTime();

	std::string getCurDate();

	long long getCurrentMs();



	// ��ʼ��·��"sdcard/log.txt" ���� "c:\\work\\log.txt"
	int LOGINIT();

	// ����ʱ�����
	int LOGEnd();

	// ���������־�ļ���Ĭ��5M, mSize��λ���ֽ�
	int LOGSetMaxSpace(int mSize);

	int logWrite(char * s);


}
#define  LOGE(...)  {\
						if (YLOG::curdate!=YLOG::getCurDate())\
						{\
							if (YLOG::curdate==""){\
							YLOG::LOGEnd();\
							} \
							YLOG::LOGINIT();\
						}\
                        char temp[8192] = {0};      \
						sprintf(temp, "%s", YLOG::getCurrentSystemTime().c_str());  \
						sprintf(temp+strlen(temp), "[ERROR][%s,%d]", YLOG::GetName(__FILE__).c_str(), __LINE__);  \
                        sprintf(temp+strlen(temp), __VA_ARGS__); \
						sprintf(temp + strlen(temp), "\n");    \
                        printf("%s", temp);   \
						YLOG::logWrite(temp); \
                    }

#define  LOGI(...)  {\
						if (YLOG::curdate!=YLOG::getCurDate())\
						{\
							if (YLOG::curdate==""){\
							YLOG::LOGEnd();\
							} \
							YLOG::LOGINIT();\
						}\
                        char temp[8192] = {0};      \
						sprintf(temp, "%s", YLOG::getCurrentSystemTime().c_str());  \
						sprintf(temp+strlen(temp), "[INFO][%s,%d]", YLOG::GetName(__FILE__).c_str(), __LINE__);  \
                        sprintf(temp+strlen(temp), __VA_ARGS__); \
						sprintf(temp + strlen(temp), "\n");    \
                        printf("%s", temp);   \
						YLOG::logWrite(temp); \
                    }
