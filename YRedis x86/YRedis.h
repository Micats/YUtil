//redis�����ļ򵥷�װ

#pragma once
#include "redis/hiredis.h"
#include <string>
class YRedis
{
private:
	YRedis();
	~YRedis();
	std::string m_ip;
	int m_port;
	std::string m_pwd;
	redisContext* Con; //redis���Ӿ��
public:
	static YRedis* getInstance();
	void SetInfo(std::string ip, int port, std::string pwd);
	void Initailize();
	void ConnectRedis();
	void DisconnectRedis();
	void setString(std::string key, const std::string value);
	void getString(std::string key, std::string& value);
	void setList(std::string key, const std::string value);
	void getListFirst(std::string key, std::string& value);
	
private:
	static YRedis* m_Instance;
	
};

