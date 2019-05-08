/*
	ͨ�ý���������
*/

#pragma once
#include <string>
#include <vector>


class YConfigParser;
//��ȡ�����������ļ�
class YConfigure
{
public:
	YConfigure();
	~YConfigure();
	void LoadConfig(std::string _name);
private:
	YConfigParser* m_parser;
public:
	//�˴�д����
};


//�����ļ�������
class YConfigParser
{
public:
	YConfigParser();   //��ʼ��ע���ַ�
	~YConfigParser();

	bool Load(const std::string& strFile);//���û��Ч�У������ļ���ʧ�ܣ��򷵻�false
	std::vector<std::string>& GetLines(); //��ü��ص�������
	int GetFileSize();					//���ԭʼ�ļ���С
	//������һ������λ�ã����Ϊ-1����ʾ����δ�ҵ�  ;����key���ظ����ε����ã�nOffsetǧ����ظ�����Ϊ0
	int GetConfigString(std::string& strValue, const std::string& key, int nOffset = 0) const;
private:
	std::vector<std::string> m_vecStrLines; //�������еķǿա���ע���У����ҽ����ڵ�ע���Ƴ������
	std::string m_strFile;					//�ļ���
	int m_nFileSize;						//�ļ���С
	int m_cComment;							//ע���ַ���#

};


//�н���
//�����ŷָ�һ���ַ���
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
