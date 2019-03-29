#include "process_info.h"

namespace process {

ProcessInfo* ProcessInfo::pInstance = NULL;

ProcessInfo::ProcessInfo()
{

}

ProcessInfo::~ProcessInfo()
{

}

ProcessInfo* ProcessInfo::getInstance()
{
    if (!pInstance) {
        pInstance = new ProcessInfo();
    }
    return pInstance;
}

}
