
#include <iostream>
#include "base/at_exit.h"
#include "base/files/file_path.h"
#include "base/path_service.h"

#include "base/message_loop/message_loop.h"
#include "base/run_loop.h"
#include "base/bind.h"
#include "base/threading/thread_task_runner_handle.h"

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


	scoped_refptr<base::SingleThreadTaskRunner> task_runner = base::ThreadTaskRunnerHandle::Get();
	//task_runner->PostTask(FROM_HERE, base::BindOnce(&test, p.AsUTF8Unsafe()));
	task_runner->PostTask(FROM_HERE, base::BindOnce([](){
		
		std::cout << "hello world " << std::endl;
	}));



	// 运行消息循环
	base::RunLoop run_loop;
	run_loop.Run();

	return 0;
}
