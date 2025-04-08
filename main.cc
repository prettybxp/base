
#include <iostream>
#include "base/at_exit.h"
#include "base/files/file_path.h"
#include "base/path_service.h"

#include "base/message_loop/message_loop.h"
#include "base/run_loop.h"
#include "base/bind.h"
#include "base/threading/thread_task_runner_handle.h"


#include "base/threading/thread.h"
//#include "base/task/single_thread_task_runner.h"
//#include "base/task/post_task.h"
#include "base/logging.h"
#include "base/memory/weak_ptr.h"


void testFilePath()
{
	base::FilePath p;
	base::PathService::Get(base::FILE_EXE, &p);
	std::cout << "FILE_EXE= " << p.AsUTF8Unsafe() << std::endl;
}


void testPostTask()
{
	scoped_refptr<base::SingleThreadTaskRunner> task_runner = base::ThreadTaskRunnerHandle::Get();
	task_runner->PostTask(FROM_HERE, base::BindOnce([](){
		std::cout << "hello world " << std::endl;
	}));
	
}

void MyTask() 
{
  LOG(INFO) << "Task is running on the created thread.";
  base::PlatformThread::Sleep(base::TimeDelta::FromSeconds(1));
  base::ThreadTaskRunnerHandle::Get()->PostTask(FROM_HERE, base::BindOnce(&MyTask));
}

void testThread()
{
	static base::Thread my_thread("MyThread");
	
	if (!my_thread.Start()) {
		LOG(ERROR) << "Failed to start the thread.";
		return ;
	}
	
	// 使用PostTask将任务发布到该线程上
	my_thread.task_runner()->PostTask(FROM_HERE, base::BindOnce(&MyTask));
}


class Demo : public base::RefCounted<Demo>
{
public:
	Demo(std::string const& name) : m_name(name), m_weakFactory(this)
	{
		std::cout << m_name<<" ctor" << std::endl;
	}
	
	~Demo()
	{
		std::cout << m_name<< " dtor" << std::endl;
	}
	
	void Callback(std::string const& param)
	{
		std::cout << " callback " <<param<<std::endl;
	}
	
	void FunStrong(std::string const& param)
	{
		base::ThreadTaskRunnerHandle::Get()->PostTask(FROM_HERE, base::Bind(&Demo::Callback, this, param));
	}
	
	void FunWeak(std::string const& param)
	{
		base::ThreadTaskRunnerHandle::Get()->PostTask(FROM_HERE, base::Bind(&Demo::Callback, m_weakFactory.GetWeakPtr(), param));
	}
	
	void FunRaw(std::string const& param)
	{
		base::ThreadTaskRunnerHandle::Get()->PostTask(FROM_HERE, base::Bind(&Demo::Callback, base::Unretained(this), param));
	}
	
	std::string m_name;
	base::WeakPtrFactory<Demo> m_weakFactory;
};

void testScopedPtr()
{
	scoped_refptr<Demo> ptr = new Demo("Scoped");
}


void testBindStrong()
{
	scoped_refptr<Demo> ptr = new Demo("Strong");
	ptr->FunStrong("111111");
}

void testBindWeak()
{
	scoped_refptr<Demo> ptr = new Demo("Weak");
	ptr->FunWeak("2222222");
}

void testBindRaw()
{
	scoped_refptr<Demo> ptr = new Demo("Raw");
	ptr->FunRaw("3333333");
}




int main(void)
{
	base::AtExitManager at;
	base::MessageLoopForUI message_loop;

	testFilePath();
	
	testPostTask();

	testThread();

	testScopedPtr();
	
	testBindStrong();
	
	testBindWeak();
	
	//testBindRaw();

	// 运行消息循环
	base::RunLoop run_loop;
	run_loop.Run();

	return 0;
}
