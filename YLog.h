
//跨平台日志类，单个文件
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
	static std::string curdate = "";	//当日日期

	std::string GetName(char * fileName);

	std::string getCurrentSystemTime();

	std::string getCurDate();

	long long getCurrentMs();



	// 初始化路径"sdcard/log.txt" 或者 "c:\\work\\log.txt"
	int LOGINIT();

	// 结束时候调用
	int LOGEnd();

	// 设置最大日志文件，默认5M, mSize单位是字节
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
