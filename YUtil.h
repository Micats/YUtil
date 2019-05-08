/*
	1.字符串处理工具
	2.路径处理工具
	3.时间日期处理工具
*/

#pragma once
#include <string>
#include <algorithm>
#include <functional>
#include <cctype>
#include <vector>

//字符串处理函数
class YSTR
{
public:
	//去除左边的空格
	static inline std::string& Ltrim(std::string& _str)
	{
		_str.erase(_str.begin(), std::find_if(_str.begin(), _str.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
		return _str;
	}
	//去除右边的空格
	static inline std::string& Rtrim(std::string& _str)
	{
		_str.erase(std::find_if(_str.rbegin(), _str.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), _str.end());
		return _str;
	}
	//去除两侧空格
	static inline std::string &Trim(std::string &_str) {
		return Ltrim(Rtrim(_str));
	}
	//全替换
	static std::string StrReplace(const std::string& str, const std::string& sub_str, const std::string& new_str);
	//大写
	static std::string StrUpper(std::string& str);
	//小写
	static std::string StrLower(std::string& str);
	
	//字符分割 参数：结果vec,源字符串,分隔符,开头跳过的字符个数，默认为0(汉字为2个字符)
	static void StrSplit(std::vector<std::string>& _vecRet, std::string _resStr, std::string _strSplit, int _nSkip = 0);

	//int 转 string
	static std::string IntToStr(int n);
	//uint 转 string
	static std::string UintToStr(unsigned int n);
	//int32数组 转 str
	static char* IntArrToStr(char* szBuf, int nBufLen, int arr[], int n);
	//uint32数组 转 str
	static char* UintArrToStr(char* szBuf, int nBufLen, unsigned int arr[], int n);
	//double数组 转 str
	static char* DoubleArrToStr(char* szBuf, int nBufLen, double arr[], int n);

	//utf-8 转 unicode (wchar转char) 需要delete
	static char* U8ToUnicode(char* szU8);

};

//路径处理工具
class YPATH
{
public:
	//获取一个文件的全路径，支持相对路径的文件,不检查对错，单纯的工作目录开始拼凑的
	static std::string GetFullPath(const std::string& strFile);
	//创建文件夹,上一级文件夹必须存在，一级一级的创建,不存在就创建，存在则返回
	static void CreateFolder(std::string _name);
	//判断文件是否存在
	static bool IsExistFile(std::string _name);
	//路径+文件名，获取文件名
	static std::string GetFileName(std::string _name);
	//正常化路径
	static void NormalizePath(std::string& strPath, bool isDir, char chSep = '\\');
	//判断前几个字符是否相同,忽略大小写
	static bool StartsWith(const std::string& str, const std::string& strPrefix);

};

//日期处理工具
class YTIME
{
public:
	//获取当天日期,yyMMdd
	static std::string GetCurDate();
	//获取前一天日期,yyMMdd
	static std::string GetPreDate();
	//获取当天秒级日期,yyMMddHHmmSS
	static std::string GetCurTime_s();
	//获取当天秒级日期,yyMMddHHmmSSms
	static std::string GetCurTime_ms();

};
