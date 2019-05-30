#include "process_child.h"

namespace process {

ProcessChild::ProcessChild()
{
    Name.clear();
    ProcessPath.clear();
    ProcessName.clear();
    Role |= ProcessRole::Child;
    State = ProcessState::Normal;

    dead_callback_ = NULL;
    init_flag_ = false;
}

ProcessChild::ProcessChild(ProcessChild& other)
{
    Pid = other.Pid;
    Name = other.Name;
    ProcessPath = other.ProcessPath;
    ProcessName = other.ProcessName;
    Role = other.Role;
    State = other.State;

    dead_callback_ = other.dead_callback_;
    pair_ = other.pair_;
    init_flag_ = other.init_flag_;
}

ProcessChild::~ProcessChild()
{
    if (init_flag_) {
        pair_.Close();
    }
}

ProcessChild& ProcessChild::Enable()
{
    init_flag_ = true;
    return *this;
}

ProcessRet ProcessChild::setSendBlock(util::time::Time* overtime)
{
    if (pair_[ProcessChildSockFDIndex].setSendBlock(overtime) != sock::SockRet::SUCCESS) {
        PROCESS_ERROR("set Child sockfd in pair send block time failed");
        return ProcessRet::ERROR;
    }
    return ProcessRet::SUCCESS;
}

ProcessRet ProcessChild::setRecvBlock(util::time::Time* overtime)
{
    if (pair_[ProcessChildSockFDIndex].setRecvBlock(overtime) != sock::SockRet::SUCCESS) {
        PROCESS_ERROR("set Child sockfd in pair recv block time failed");
        return ProcessRet::ERROR;
    }
    return ProcessRet::SUCCESS;
}

ProcessRet ProcessChild::setNonBlock()
{
    if (pair_[ProcessChildSockFDIndex].setNonBlock() != sock::SockRet::SUCCESS) {
        PROCESS_ERROR("set Child sockfd in pair non block failed");
        return ProcessRet::ERROR;
    }
    return ProcessRet::SUCCESS;
}

}
