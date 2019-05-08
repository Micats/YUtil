#include "pch.h"
#include "YRedis.h"
#include "win32fixes.h"

YRedis::YRedis()
{
	Initailize();
}


YRedis::~YRedis()
{
}

void YRedis::SetInfo(std::string ip, int port, std::string pwd)
{
	m_ip = ip;
	m_port = port;
	m_pwd = pwd;
}

void YRedis::Initailize()
{
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 1), &wsaData);
}

void YRedis::ConnectRedis()
{
	Con = redisConnect(m_ip.c_str(), m_port);
	if (Con && Con->err)
	{
		printf("redisConnect failed \n");
		return;
	}
	redisReply* reply = (redisReply*)redisCommand(Con, "AUTH %s", m_pwd.c_str());
	if (reply->type == REDIS_REPLY_ERROR)
	{
		printf("Redis Authentication failed !!!! \n");
		return;
	}
	freeReplyObject(reply);
	printf("Redis access !!!! \n");
}

void YRedis::DisconnectRedis()
{
	redisFree(Con);
}

void YRedis::setString(std::string  _key, const std::string  _value)
{
	redisReply* ret = (redisReply*)redisCommand(Con, "SET %s %s", _key.c_str(), _value.c_str());
	if (!(ret->type == REDIS_REPLY_STATUS && strcasecmp(ret->str, "OK") == 0))
	{
		printf("Failed to execute SET(string)\n");
		freeReplyObject(ret);
		return;
	}
	freeReplyObject(ret);
	//printf("execute SET(string) success \n");
}

void YRedis::setList(std::string _key, const std::string _value)
{
	redisReply* ret = (redisReply*)redisCommand(Con, "LPUSH %s %s", _key.c_str(), _value.c_str());
	if (ret->type != REDIS_REPLY_INTEGER )
	{
		printf("Failed to execute LPUSH(string)\n");
		freeReplyObject(ret);
		return;
	}
	freeReplyObject(ret);
}

void YRedis::getListFirst(std::string _key, std::string & _value)
{
	redisReply* ret = (redisReply*)redisCommand(Con, "LPOP %s", _key.c_str()); //³¬Ê±Ê±¼ä10s
	if (ret->type == REDIS_REPLY_STRING)
	{
		_value = ret->str;
		freeReplyObject(ret);
		return;
	}
	if (ret->type == REDIS_REPLY_NIL)
	{
		_value = "";
		freeReplyObject(ret);
		return;
	}
	
}

void YRedis::getString(std::string _key, std::string& _value)
{
	redisReply* ret = (redisReply*)redisCommand(Con, "GET %s", _key.c_str());
	if (ret->type == REDIS_REPLY_STRING)
	{
		_value =ret->str;
		freeReplyObject(ret);
		return;
	}
	//printf("execute GET(string) failed \n");
}

YRedis* YRedis::m_Instance;

YRedis * YRedis::getInstance()
{
	if (m_Instance==nullptr)
	{
		m_Instance = new YRedis();
	}
	return m_Instance;
}
