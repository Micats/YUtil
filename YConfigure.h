/*
	通用解析配置类
*/

#pragma once
#include <string>
#include <vector>


class YConfigParser;
//获取的最终配置文件
class YConfigure
{
public:
	YConfigure();
	~YConfigure();
	void LoadConfig(std::string _name);
private:
	YConfigParser* m_parser;
public:
	//此处写数据
};


//配置文件解析类
class YConfigParser
{
public:
	YConfigParser();   //初始化注释字符
	~YConfigParser();

	bool Load(const std::string& strFile);//如果没有效行，或则文件打开失败，则返回false
	std::vector<std::string>& GetLines(); //获得加载的所有行
	int GetFileSize();					//获得原始文件大小
	//返回下一个搜索位置，如果为-1，表示本轮未找到  ;对于key会重复许多次的配置，nOffset千万别重复设置为0
	int GetConfigString(std::string& strValue, const std::string& key, int nOffset = 0) const;
private:
	std::vector<std::string> m_vecStrLines; //读入所有的非空、非注释行，并且将行内的注释移除后存入
	std::string m_strFile;					//文件名
	int m_nFileSize;						//文件大小
	int m_cComment;							//注释字符：#

};


//行解析
//按符号分割一行字符串
class YLineParser
{
public:
	YLineParser(const std::string& strLine, int nSplitter = ',');
	~YLineParser();
	const std::string& operator[](int i);
	int size();

private:
	std::vector<std::string>m_vecTokens;
};
