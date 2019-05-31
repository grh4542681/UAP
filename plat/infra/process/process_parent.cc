#include "process_parent.h"

namespace process {

ProcessParent::ProcessParent()
{
    name_.clear();
    dead_callback_ = NULL;
    init_flag_ = false;
}

ProcessParent::ProcessParent(std::string name, ProcessID&& pid)
{
    name_ = name;
    pid_ = pid;
    dead_callback_ = NULL;
    init_flag_ = true;
}

ProcessParent::ProcessParent(ProcessParent& other)
{
    pid_ = other.pid_;
    name_ = other.name_;

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

ProcessParent& ProcessParent::setSockPair(ipc::sock::SockPair&& pair)
{
    pair_ = pair;
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
