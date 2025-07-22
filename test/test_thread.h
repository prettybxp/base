#pragma once

#include "base/threading/thread.h"


void MyTask()
{
    static int  count = 0;
    LOG(INFO) << "Task is running on the created thread."<< count++;
    if (count > 2)
    {
        return;
    }
    base::PlatformThread::Sleep(base::TimeDelta::FromSeconds(1));
    base::ThreadTaskRunnerHandle::Get()->PostTask(FROM_HERE, base::BindOnce(&MyTask));
}


void TestThread()
{
    base::Thread my_thread("MyThread");

	if (!my_thread.Start())
    {
		LOG(ERROR) << "Failed to start the thread.";
		return ;
	}
	my_thread.task_runner()->PostTask(FROM_HERE, base::BindOnce(&MyTask));
}