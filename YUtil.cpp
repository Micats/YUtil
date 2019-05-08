#include "pch.h"
#include "YUtil.h"
#include <algorithm>
#include <functional>
#include <cctype>
#include <windows.h>
#include <io.h>
#include <direct.h>
#include <time.h>
#include <chrono>

std::string YSTR::StrReplace(const std::string & str, const std::string & sub_str, const std::string & new_str)
{
	if (!sub_str.size())
	{
		return str;
	}

	std::string str_copy = str;

	int nfirstfind = 0;
	while ((nfirstfind = str_copy.find(sub_str, nfirstfind)) != std::string::npos)
	{
		str_copy.replace(nfirstfind, sub_str.size(), new_str);
		nfirstfind += new_str.size();
	}
	return str_copy;
}

std::string YSTR::StrUpper(std::string & str)
{
	std::transform(str.begin(), str.end(), str.begin(), ::toupper);
	return str;
}

std::string YSTR::StrLower(std::string & str)
{
	std::transform(str.begin(), str.end(), str.begin(), ::tolower);
	return str;
}

void YSTR::StrSplit(std::vector<std::string>& _vecRet, std::string _resStr, std::string _strSplit, int _nSkip)
{
	std::vector<std::string>::size_type sPos = _nSkip;
	std::vector<std::string>::size_type ePos = _resStr.find(_strSplit, sPos);
	while (ePos != std::string::npos)
	{
		if (sPos != ePos) _vecRet.push_back(_resStr.substr(sPos, ePos - sPos));
		sPos = ePos + _strSplit.size();
		ePos = _resStr.find(_strSplit, sPos);
	}
	if (sPos < _resStr.size()) _vecRet.push_back(_resStr.substr(sPos, _resStr.size() - sPos));
}

std::string YSTR::IntToStr(int n)
{
	char szBuf[32] = { 0 };
	_snprintf(szBuf, sizeof(szBuf) - 1, "%d", n);
	return std::string(szBuf, 0, sizeof(szBuf) - 1);
	
}

std::string YSTR::UintToStr(unsigned int n)
{
	char szBuf[33] = { 0 };
	_snprintf(szBuf, sizeof(szBuf) - 1, "%u", n);
	return std::string(szBuf, 0, sizeof(szBuf) - 1);
}

char * YSTR::IntArrToStr(char * szBuf, int nBufLen, int arr[], int n)
{
	int nOffset = 0;
	for (int i = 0; i < n; i++)
	{
		nOffset += _snprintf(szBuf + nOffset, nBufLen - nOffset, "%d ", arr[i]);
	}
	return szBuf;
}

char * YSTR::UintArrToStr(char * szBuf, int nBufLen, unsigned int arr[], int n)
{
	int nOffset = 0;
	for (int i = 0; i < n; i++)
	{
		nOffset += _snprintf(szBuf + nOffset, nBufLen - nOffset, "%u ", arr[i]);
	}
	return szBuf;
}

char * YSTR::DoubleArrToStr(char * szBuf, int nBufLen, double arr[], int n)
{
	int nOffset = 0;
	for (int i = 0; i < n; i++)
	{
		nOffset += _snprintf(szBuf + nOffset, nBufLen - nOffset, "%f ", arr[i]);
	}
	return szBuf;
}

char * YSTR::U8ToUnicode(char * szU8)
{
	//预转换，得到所需空间的大小
	int wcsLen = ::MultiByteToWideChar(CP_UTF8, NULL, szU8, strlen(szU8), NULL, 0);
	//分配空间要给'\0'留个空间，MultiByteToWideChar不会给'\0'空间
	wchar_t* wszString = new wchar_t[wcsLen + 1];
	//转换
	::MultiByteToWideChar(CP_UTF8, NULL, szU8, strlen(szU8), wszString, wcsLen);
	//最后加上'\0'
	wszString[wcsLen] = '\0';

	char *m_char;
	int len = WideCharToMultiByte(CP_ACP, 0, wszString, wcslen(wszString), NULL, 0, NULL, NULL);
	m_char = new char[len + 1];
	WideCharToMultiByte(CP_ACP, 0, wszString, wcslen(wszString), m_char, len, NULL, NULL);
	m_char[len] = '\0';
	return m_char;
	return nullptr;
}

std::string YPATH::GetFullPath(const std::string & strFile)
{
	char szTemp[1024] = { 0 };
	int n = GetFullPathNameA(strFile.c_str(), sizeof(szTemp) / sizeof(szTemp[0]) - 1, szTemp, NULL);
	return std::string(szTemp, 0, sizeof(szTemp) / sizeof(szTemp[0]) - 1);
}

void YPATH::CreateFolder(std::string _name)
{
	if (_access(_name.c_str(),0)==-1)//文件夹不存在
	{
		_mkdir(_name.c_str());
	}
}

bool YPATH::IsExistFile(std::string _name)
{
	FILE* fp = fopen(_name.c_str(), "rb");
	bool nRet = (fp != NULL);
	if (fp)
	{
		fclose(fp);
	}
	return nRet;
}

std::string YPATH::GetFileName(std::string _name)
{	
	std::string sName = _name;
#ifdef WIN32
	int startP = sName.find_last_of("\\");
	if (startP == -1)
	{
		startP = 0;
	}
	std::string theLastName = sName.substr(startP + 1, sName.size() - startP);

#else
	int startP = sName.find_last_of("/");
	if (startP == -1)
	{
		startP = 0;
	}
	std::string theLastName = sName.substr(startP + 1, sName.size() - startP);

#endif
	return theLastName;
}

void YPATH::NormalizePath(std::string & strPath, bool isDir, char chSep)
{
	char chOrg = ((chSep == '\\') ? '/' : '\\');
	std::replace(strPath.begin(), strPath.end(), chOrg, chSep);

	std::string strTemp;
	strTemp.reserve(strPath.size() + 1);
	for (int i = 0; i < strPath.size(); )
	{
		int nBegin = strPath.find_first_of("\\/", i);
		if (nBegin != std::string::npos)
		{
			std::string strSub = strPath.substr(i, nBegin - i);
			strTemp += YSTR::Trim(strSub);
			strTemp.append(1, chSep);
		}
		else
		{
			std::string strSub = strPath.substr(i, strPath.size() - i);
			strTemp += YSTR::Trim(strSub);
		}
		//nBegin = strPath.find_first_not_of(chSep, nBegin);
		nBegin = strPath.find_first_not_of("\\/", nBegin);
		i = nBegin;
	}
	if (isDir && strTemp[strTemp.size() - 1] != chSep)
	{
		std::string strSlash = std::string(1, chSep);
		strTemp += strSlash;
	}

	strPath = strTemp;
}

bool YPATH::StartsWith(const std::string & str, const std::string & strPrefix)
{
	if (str.size() < strPrefix.size())
	{
		return false;
	}
	std::string str_cpy = str;
	std::transform(str_cpy.begin(), str_cpy.end(), str_cpy.begin(), ::toupper);
	std::string prefix_cpy = strPrefix;
	std::transform(prefix_cpy.begin(), prefix_cpy.end(), prefix_cpy.begin(), ::toupper);

	if (str_cpy.find(prefix_cpy) == 0)
	{
		return true;
	}
	return false;
}

std::string YTIME::GetCurDate()
{
	time_t t = time(0);
	char sTime[64];
	strftime(sTime, sizeof(sTime), "%Y%m%d", localtime(&t));
	return sTime;
}

std::string YTIME::GetPreDate()
{

	time_t t = time(0)-24*60*60;
	char sTime[64];
	strftime(sTime, sizeof(sTime), "%Y%m%d", localtime(&t));
	return sTime;
}

std::string YTIME::GetCurTime_s()
{
	time_t t = time(0);
	char sTime[64];
	strftime(sTime, sizeof(sTime), "%Y%m%d%H%M%S", localtime(&t));
	return sTime;
}

std::string YTIME::GetCurTime_ms()
{
	auto time_now = std::chrono::system_clock::now();
	auto tt = std::chrono::system_clock::to_time_t(time_now);
	auto duration_in_ms = std::chrono::duration_cast<std::chrono::milliseconds>(time_now.time_since_epoch());
	auto duration_in_s = std::chrono::duration_cast<std::chrono::seconds>(time_now.time_since_epoch());
	int theMs = duration_in_ms.count() - duration_in_s.count() * 1000;
	struct tm* ptm = localtime(&tt);


	char date[60] = { 0 };
	sprintf(date, "%d%02d%02%02d%02d%02d%03d%",
		(int)ptm->tm_year + 1900, (int)ptm->tm_mon + 1, (int)ptm->tm_mday,
		(int)ptm->tm_hour, (int)ptm->tm_min, (int)ptm->tm_sec, theMs);
	return std::string(date);
}
