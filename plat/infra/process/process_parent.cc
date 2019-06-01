#include "process_parent.h"

namespace process {

ProcessParent::ProcessParent()
{
    name_.clear();
    init_flag_ = false;
}

ProcessParent::ProcessParent(std::string name, ProcessID& pid)
{
    name_ = name;
    pid_ = pid;
    init_flag_ = true;
}

ProcessParent::ProcessParent(std::string name, ProcessID&& pid)
{
    name_ = name;
    pid_ = pid;
    init_flag_ = true;
}

ProcessParent::ProcessParent(ProcessParent& other)
{
    pid_ = other.pid_;
    name_ = other.name_;

    pair_ = other.pair_;
    init_flag_ = other.init_flag_;
}

ProcessParent::~ProcessParent()
{
    if (init_flag_) {
        pair_.Close();
    }
}

ipc::sock::SockPair& ProcessParent::GetSockPair()
{
    return pair_;
}

ProcessParent& ProcessParent::SetSockPair(ipc::sock::SockPair& pair)
{
    return SetSockPair(std::move(pair));
}
ProcessParent& ProcessParent::SetSockPair(ipc::sock::SockPair&& pair)
{
    pair_ = pair;
    return *this;
}

ProcessRet ProcessParent::SetSendBlock(util::time::Time* overtime)
{
    if (pair_[ProcessParentSockFDIndex].SetSendBlock(overtime) != sock::SockRet::SUCCESS) {
        PROCESS_ERROR("set Child sockfd in pair send block time failed");
        return ProcessRet::ERROR;
    }
    return ProcessRet::SUCCESS;
}

ProcessRet ProcessParent::SetRecvBlock(util::time::Time* overtime)
{
    if (pair_[ProcessParentSockFDIndex].SetRecvBlock(overtime) != sock::SockRet::SUCCESS) {
        PROCESS_ERROR("set Child sockfd in pair recv block time failed");
        return ProcessRet::ERROR;
    }
    return ProcessRet::SUCCESS;
}

ProcessRet ProcessParent::SetNonBlock()
{
    if (pair_[ProcessParentSockFDIndex].SetNonBlock() != sock::SockRet::SUCCESS) {
        PROCESS_ERROR("set Child sockfd in pair non block failed");
        return ProcessRet::ERROR;
    }
    return ProcessRet::SUCCESS;
}

}
