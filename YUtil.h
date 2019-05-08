/*
	1.�ַ���������
	2.·��������
	3.ʱ�����ڴ�����
*/

#pragma once
#include <string>
#include <algorithm>
#include <functional>
#include <cctype>
#include <vector>

//�ַ���������
class YSTR
{
public:
	//ȥ����ߵĿո�
	static inline std::string& Ltrim(std::string& _str)
	{
		_str.erase(_str.begin(), std::find_if(_str.begin(), _str.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
		return _str;
	}
	//ȥ���ұߵĿո�
	static inline std::string& Rtrim(std::string& _str)
	{
		_str.erase(std::find_if(_str.rbegin(), _str.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), _str.end());
		return _str;
	}
	//ȥ������ո�
	static inline std::string &Trim(std::string &_str) {
		return Ltrim(Rtrim(_str));
	}
	//ȫ�滻
	static std::string StrReplace(const std::string& str, const std::string& sub_str, const std::string& new_str);
	//��д
	static std::string StrUpper(std::string& str);
	//Сд
	static std::string StrLower(std::string& str);
	
	//�ַ��ָ� ���������vec,Դ�ַ���,�ָ���,��ͷ�������ַ�������Ĭ��Ϊ0(����Ϊ2���ַ�)
	static void StrSplit(std::vector<std::string>& _vecRet, std::string _resStr, std::string _strSplit, int _nSkip = 0);

	//int ת string
	static std::string IntToStr(int n);
	//uint ת string
	static std::string UintToStr(unsigned int n);
	//int32���� ת str
	static char* IntArrToStr(char* szBuf, int nBufLen, int arr[], int n);
	//uint32���� ת str
	static char* UintArrToStr(char* szBuf, int nBufLen, unsigned int arr[], int n);
	//double���� ת str
	static char* DoubleArrToStr(char* szBuf, int nBufLen, double arr[], int n);

	//utf-8 ת unicode (wcharתchar) ��Ҫdelete
	static char* U8ToUnicode(char* szU8);

};

//·��������
class YPATH
{
public:
	//��ȡһ���ļ���ȫ·����֧�����·�����ļ�,�����Դ������Ĺ���Ŀ¼��ʼƴ�յ�
	static std::string GetFullPath(const std::string& strFile);
	//�����ļ���,��һ���ļ��б�����ڣ�һ��һ���Ĵ���,�����ھʹ����������򷵻�
	static void CreateFolder(std::string _name);
	//�ж��ļ��Ƿ����
	static bool IsExistFile(std::string _name);
	//·��+�ļ�������ȡ�ļ���
	static std::string GetFileName(std::string _name);
	//������·��
	static void NormalizePath(std::string& strPath, bool isDir, char chSep = '\\');
	//�ж�ǰ�����ַ��Ƿ���ͬ,���Դ�Сд
	static bool StartsWith(const std::string& str, const std::string& strPrefix);

};

//���ڴ�����
class YTIME
{
public:
	//��ȡ��������,yyMMdd
	static std::string GetCurDate();
	//��ȡǰһ������,yyMMdd
	static std::string GetPreDate();
	//��ȡ�����뼶����,yyMMddHHmmSS
	static std::string GetCurTime_s();
	//��ȡ�����뼶����,yyMMddHHmmSSms
	static std::string GetCurTime_ms();

};
