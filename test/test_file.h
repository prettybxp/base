#pragma once
#include "base/files/file_path.h"
#include "base/path_service.h"
#include "base/files/file.h"


void TestFile()
{

    base::FilePath p;
	base::PathService::Get(base::FILE_EXE, &p);
    LOG(INFO)<<"test file path:"<<p.AsUTF8Unsafe();

    base::File f(p, base::File::FLAG_OPEN | base::File::FLAG_READ);
    base::File::Info info;
    if (f.GetInfo(&info))
    {
        LOG(INFO)<<"file size:"<<info.size<<" create_time:"<<info.creation_time;
    }


}