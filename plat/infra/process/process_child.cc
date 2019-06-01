#include "process_child.h"

namespace process {

ProcessChild::ProcessChild()
{
    name_.clear();
    role_ |= ProcessRole::Child;
    state_ = ProcessState::Normal;

    dead_callback_ = NULL;
    init_flag_ = false;
}

ProcessChild::ProcessChild(std::string name, ProcessID&& pid)
{
    name_ = name;
    pid_ = pid;
    role_ |= ProcessRole::Child;
    state_ = ProcessState::Normal;

    dead_callback_ = NULL;
    init_flag_ = true;
}

ProcessChild::ProcessChild(ProcessChild& other)
{
    pid_ = other.pid_;
    name_ = other.name_;
    role_ = other.role_;
    state_ = other.state_;

    dead_callback_ = other.dead_callback_;
    pair_ = other.pair_;
    init_flag_ = other.init_flag_;
}

ProcessChild::~ProcessChild()
{

}

ProcessID& ProcessChild::GetPid()
{
    return pid_;
}

std::string ProcessChild::GetName()
{
    return name_;
}

ProcessRole& ProcessChild::GetRole()
{
    return role_;
}

ProcessState& ProcessChild::GetState()
{
    return state_;
}

void (*ProcessChild::GetDeadCallback())(int*)
{
    return dead_callback_;
}

ipc::sock::SockPair& ProcessChild::GetSockPair()
{
    return pair_;
}

ProcessChild& ProcessChild::SetState(ProcessState state)
{
    state_ = state;
    return *this;
}

ProcessChild& ProcessChild::SetDeadCallback(void (*dead_callback)(int*))
{
    dead_callback_ = dead_callback;
    return *this;
}

ProcessChild& ProcessChild::SetSockPair(ipc::sock::SockPair& pair)
{
    return SetSockPair(std::move(pair));
}
ProcessChild& ProcessChild::SetSockPair(ipc::sock::SockPair&& pair)
{
    pair_ = pair;
    return *this;
}

ProcessRet ProcessChild::SetSendBlock(util::time::Time* overtime)
{
    if (pair_[ProcessChildSockFDIndex].SetSendBlock(overtime) != sock::SockRet::SUCCESS) {
        PROCESS_ERROR("Set Child sockfd in pair send block time failed");
        return ProcessRet::ERROR;
    }
    return ProcessRet::SUCCESS;
}

ProcessRet ProcessChild::SetRecvBlock(util::time::Time* overtime)
{
    if (pair_[ProcessChildSockFDIndex].SetRecvBlock(overtime) != sock::SockRet::SUCCESS) {
        PROCESS_ERROR("Set Child sockfd in pair recv block time failed");
        return ProcessRet::ERROR;
    }
    return ProcessRet::SUCCESS;
}

ProcessRet ProcessChild::SetNonBlock()
{
    if (pair_[ProcessChildSockFDIndex].SetNonBlock() != sock::SockRet::SUCCESS) {
        PROCESS_ERROR("Set Child sockfd in pair non block failed");
        return ProcessRet::ERROR;
    }
    return ProcessRet::SUCCESS;
}

}
