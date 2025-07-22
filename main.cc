#include "base/at_exit.h"


#include "base/message_loop/message_loop.h"
#include "base/run_loop.h"

#include "test/test_refcount.h"
#include "test/test_weakptr.h"
#include "test/test_callback.h"
#include "test/test_log.h"
#include "test/test_file.h"
#include "test/test_thread.h"



int main(void)
{
	base::AtExitManager at;
	base::MessageLoopForUI message_loop;


	TestLog();

	TestFile();

	TestThread();

	TestCallback();

	TestRefCount();

	TestWeakPtr();

	// 运行消息循环
	base::RunLoop run_loop;
	run_loop.Run();

	return 0;
}
