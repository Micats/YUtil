/*
	任务调度器:在另一线程执行任务
	时间：2019-5-8
*/

/*
	使用实例：
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


//任务函数
typedef std::function<void(void)> Task;
//任务指针
typedef std::unique_ptr<Task> TaskPtr;

class YIosServer
{
public:
	YIosServer();
	~YIosServer();
	void Start();	
	void Stop();
	void Post(TaskPtr& task);  //投递任务
private:
	static void IosProc(void* arg);
	void Run();
private:
	std::unique_ptr<std::thread> m_thread;	//线程
	std::deque<TaskPtr> m_TaskDeque;		//任务列表
	std::mutex	m_mutex;					//锁
	std::condition_variable m_cv;			//条件变量
	bool m_bStop;							//运行标志
};

