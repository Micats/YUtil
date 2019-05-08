#include "pch.h"
#include "YIosServer.h"


YIosServer::YIosServer()
{
	m_bStop = false;
}


YIosServer::~YIosServer()
{
}

void YIosServer::Start()
{
	//将线程函数指向iosproc
	m_thread.reset(new std::thread(&YIosServer::IosProc, this));
}

void YIosServer::Run()
{
	while (!m_bStop)
	{
		std::deque<TaskPtr> tasks;	//复制任务列表		
		{
			//加锁访问任务列表
			std::unique_lock<std::mutex> mtx(m_mutex); //智能锁
			if (m_TaskDeque.empty())
			{
				m_cv.wait(mtx);  //等待锁信号，阻塞,另一线程通知
			}
			if (m_TaskDeque.empty())
			{
				continue;
			}
			tasks = std::move(m_TaskDeque); //移动复制
		}
		for (auto& it : tasks)
		{
			if (!m_bStop)
			{
				(*it)();
			}

		}

		
	}
}

void YIosServer::Stop()
{
	m_bStop = true;
	m_cv.notify_all();
	if (m_thread.get()==0)
	{
		return;
	}
	m_thread->join();
}

void YIosServer::Post(TaskPtr & task)
{
	bool bEmpty = true;
	{
		std::unique_lock<std::mutex> mtx(m_mutex);
		bEmpty = m_TaskDeque.empty();
		m_TaskDeque.push_back(std::move(task));
	}
	if (bEmpty)
	{
		m_cv.notify_all();
	}
}

void YIosServer::IosProc(void * arg)
{
	YIosServer* io = (YIosServer*)arg;
	io->Run();
}
