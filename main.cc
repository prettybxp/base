
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


#include "mojo/logger.mojom.h"




void MyTask() {
  LOG(INFO) << "Task is running on the created thread.";
  base::PlatformThread::Sleep(base::TimeDelta::FromSeconds(1));
  base::ThreadTaskRunnerHandle::Get()->PostTask(FROM_HERE, base::BindOnce(&MyTask));
}


void test(std::string const& param)
{
	std::cout << "hello baofish " << param << std::endl;
}

int main(void)
{
	base::AtExitManager at;
	base::MessageLoopForUI message_loop;


	base::FilePath p;
	base::PathService::Get(base::FILE_EXE, &p);


	base::Thread my_thread("MyThread");


	if (!my_thread.Start()) {
		LOG(ERROR) << "Failed to start the thread.";
		return -1;
	}
  
	scoped_refptr<base::SingleThreadTaskRunner> task_runner = base::ThreadTaskRunnerHandle::Get();
	//task_runner->PostTask(FROM_HERE, base::BindOnce(&test, p.AsUTF8Unsafe()));
	task_runner->PostTask(FROM_HERE, base::BindOnce([](){
		
		std::cout << "hello world " << std::endl;
	}));
	
	
	mojo::MessagePipe pipe;
	sample::mojom::LoggerPtr logger(
		sample::mojom::LoggerPtrInfo(std::move(pipe.handle0), 0));
	sample::mojom::LoggerRequest request(std::move(pipe.handle1));
	
	
	// 使用PostTask将任务发布到该线程上
	my_thread.task_runner()->PostTask(FROM_HERE, base::BindOnce(&MyTask));



	// 运行消息循环
	base::RunLoop run_loop;
	run_loop.Run();

	return 0;
}
