#include "process_parent.h"

namespace process {

ProcessParent::ProcessParent()
{
    Name.clear();
    ProcessPath.clear();
    ProcessName.clear();
    Role |= ProcessRole::Child;
    State = ProcessState::Normal;

    dead_callback_ = NULL;
    init_flag_ = false;
}

ProcessParent::ProcessParent(ProcessParent& other)
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

ProcessParent::~ProcessParent()
{
    if (init_flag_) {
        pair_.Close();
    }
}

ProcessParent& ProcessParent::Enable()
{
    init_flag_ = true;
    return *this;
}

ProcessRet ProcessParent::setSendBlock(util::time::Time* overtime)
{
    if (pair_[ProcessParentSockFDIndex].setSendBlock(overtime) != sock::SockRet::SUCCESS) {
        PROCESS_ERROR("set Child sockfd in pair send block time failed");
        return ProcessRet::ERROR;
    }
    return ProcessRet::SUCCESS;
}

ProcessRet ProcessParent::setRecvBlock(util::time::Time* overtime)
{
    if (pair_[ProcessParentSockFDIndex].setRecvBlock(overtime) != sock::SockRet::SUCCESS) {
        PROCESS_ERROR("set Child sockfd in pair recv block time failed");
        return ProcessRet::ERROR;
    }
    return ProcessRet::SUCCESS;
}

ProcessRet ProcessParent::setNonBlock()
{
    if (pair_[ProcessParentSockFDIndex].setNonBlock() != sock::SockRet::SUCCESS) {
        PROCESS_ERROR("set Child sockfd in pair non block failed");
        return ProcessRet::ERROR;
    }
    return ProcessRet::SUCCESS;
}

}
