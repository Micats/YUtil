/*
	���������:����һ�߳�ִ������
	ʱ�䣺2019-5-8
*/

/*
	ʹ��ʵ����
	m_ios->start();
	TaskPtr task(new Task(std::bind(&MyClass::deal, this, 6)));
	if (m_ios!=nullptr)
	{
		m_ios->Post(task);
	}
	m->iso->stop();
*/
#pragma once
#include <memory>
#include <functional>
#include <deque>
#include <thread>
#include <mutex>
#include <condition_variable>


//������
typedef std::function<void(void)> Task;
//����ָ��
typedef std::unique_ptr<Task> TaskPtr;

class YIosServer
{
public:
	YIosServer();
	~YIosServer();
	void Start();	
	void Stop();
	void Post(TaskPtr& task);  //Ͷ������
private:
	static void IosProc(void* arg);
	void Run();
private:
	std::unique_ptr<std::thread> m_thread;	//�߳�
	std::deque<TaskPtr> m_TaskDeque;		//�����б�
	std::mutex	m_mutex;					//��
	std::condition_variable m_cv;			//��������
	bool m_bStop;							//���б�־
};

