
#pragma once

#include "base/logging.h"


void TestLog()
{
    logging::SetLogItems(false, true, true, false);
    logging::SetMinLogLevel(logging::LOG_WARNING);
    LOG(INFO) << "Log Test Info" ;
    LOG(WARNING) << "Log Test WARNING";
    LOG(ERROR) << "Log Test ERROR";
    //LOG(FATAL) << "Log Test FATAL";   这里会assert

    logging::SetMinLogLevel(logging::LOG_VERBOSE);
}