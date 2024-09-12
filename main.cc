
#include <iostream>
#include "base/at_exit.h"
#include "base/files/file_path.h"
#include "base/path_service.h"

int main(void)
{
	base::AtExitManager at;

	base::FilePath p;
	base::PathService::Get(base::FILE_EXE, &p);



	std::cout<<"hello baofish "<<p.AsUTF8Unsafe()<<std::endl;
	return 0;
}
