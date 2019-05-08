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
	//���̺߳���ָ��iosproc
	m_thread.reset(new std::thread(&YIosServer::IosProc, this));
}

void YIosServer::Run()
{
	while (!m_bStop)
	{
		std::deque<TaskPtr> tasks;	//���������б�		
		{
			//�������������б�
			std::unique_lock<std::mutex> mtx(m_mutex); //������
			if (m_TaskDeque.empty())
			{
				m_cv.wait(mtx);  //�ȴ����źţ�����,��һ�߳�֪ͨ
			}
			if (m_TaskDeque.empty())
			{
				continue;
			}
			tasks = std::move(m_TaskDeque); //�ƶ�����
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
