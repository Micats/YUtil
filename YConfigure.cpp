#include "pch.h"
#include "YConfigure.h"
#include "YUtil.h"
#include <fstream>


YConfigure::YConfigure()
{
}


YConfigure::~YConfigure()
{
}

void YConfigure::LoadConfig(std::string _name)
{
	m_parser = new YConfigParser;
	if (!m_parser->Load(_name))
	{
		delete m_parser;
		m_parser = nullptr;
		printf("配置文件加载失败！\n");
		return;
	}
	//行数 和 值，用来获取信息
	int nLineOffset = 0;
	std::string strValue;

	//获取数据,修改此处用来获得数据
	nLineOffset = m_parser->GetConfigString(strValue, "Date", 0);
	if (nLineOffset == -1 || !strValue.size())
	{
		strValue;
	}
	else
	{
		strValue = atoi(strValue.c_str());
	}
	strValue.clear();

}

YLineParser::YLineParser(const std::string & strLine, int nSplitter)
{
	std::string strLineTmp = strLine;

	char* pTemp = (char*)strLineTmp.c_str();
	char* pContext = NULL;

	char* pToken = strtok_s(pTemp, ",", &pContext);

	if (pToken)
	{
		m_vecTokens.push_back(pToken);
		while (pToken = strtok_s(NULL, ",", &pContext))
		{
			std::string temp(pToken);
			m_vecTokens.push_back(YSTR::Trim(temp));
		}
	}


	std::string strToken;
	bool bMeetQuote = false;
	for (int i = 0; i < strLine.size(); i++)
	{
		char ch = strLine.at(i);

		if (ch == '"')
		{
			if (!bMeetQuote)
			{
				bMeetQuote = true;
			}
			else
			{
				//m_vecTokens.push_back(PathHelper::trim(strToken));
				//strToken.clear();
				bMeetQuote = false;
			}
		}
		else if (ch == nSplitter)
		{
			if (bMeetQuote)
			{
				strToken.push_back(ch);
			}
			else
			{
				m_vecTokens.push_back(YSTR::Trim(strToken));
				strToken.clear();
			}
		}
		else
		{
			strToken.push_back(ch);
		}

		if (i == strLine.size() - 1)
		{
			YSTR::Trim(strToken);
			if (strToken.size())
			{
				m_vecTokens.push_back(strToken);
			}
			strToken.clear();
		}
	}
}

YLineParser::~YLineParser()
{
}

const std::string & YLineParser::operator[](int i)
{
	return m_vecTokens[i];
}

int YLineParser::size()
{
	return m_vecTokens.size();
}

YConfigParser::YConfigParser()
{
	m_cComment = '#';
}

YConfigParser::~YConfigParser()
{
}

bool YConfigParser::Load(const std::string & strFile)
{
	if (m_vecStrLines.size())
	{
		m_vecStrLines.clear();
	}
	if (m_strFile.size())
	{
		m_strFile.clear();
	}
	m_nFileSize = 0;


	m_strFile = strFile;
	YSTR::Trim(m_strFile);
	if (!m_strFile.size())
	{
		return false;
	}

	YPATH::NormalizePath(m_strFile, false);

	FILE* fp = fopen(m_strFile.c_str(), "rb");
	if (!fp)
	{
		return false;
	}

	fseek(fp, 0, SEEK_END);
	m_nFileSize = ftell(fp);
	fclose(fp);

	std::string strLine;
	std::ifstream file(m_strFile, std::ios_base::in);

	if (!file.is_open())
	{
		return false;
	}

	while (std::getline(file, strLine))
	{
		YSTR::Ltrim(strLine);
		if (!strLine.size())
		{
			continue;
		}

		int nCommentPos = strLine.find_first_of(m_cComment);
		if (nCommentPos != std::string::npos)
		{
			strLine.erase(nCommentPos);
		}

		YSTR::Trim(strLine);

		if (strLine.size())
		{
			m_vecStrLines.push_back(strLine);
		}
	}

	if (m_vecStrLines.size())
	{
		return true;
	}
	else
	{
		return false;
	}
}

std::vector<std::string>& YConfigParser::GetLines()
{
	return m_vecStrLines;
}

int YConfigParser::GetFileSize()
{
	return m_nFileSize;
}

int YConfigParser::GetConfigString(std::string & strValue, const std::string & key, int nSeachStart) const
{
	if (strValue.size())
	{
		strValue.clear();
	}
	if (nSeachStart < 0 && nSeachStart >= m_vecStrLines.size())
	{
		return -1;
	}

	/////////
	int nFoundNext = -1;

	for (int i = nSeachStart; i < m_vecStrLines.size(); i++)
	{
		const std::string& strLine = m_vecStrLines[i];
		if (YPATH::StartsWith(strLine, key + "="))
		{
			nFoundNext = i + 1;
			strValue = m_vecStrLines[i].substr(key.size() + 1);
			break;
		}
	}

	return nFoundNext;
}
