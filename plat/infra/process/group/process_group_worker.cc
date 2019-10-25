#include "process_group_worker.h"

namespace process::group {

ProcessGroupWorker::ProcessGroupWorker(sock::SockAddress& worker_address)
{
    sock::SockClient client(&worker_address);
    if (client.Connect() == sock::SockRet::SUCCESS) {
        worker_fd_ = client.GetSockFD();
        select_item_ = SelectItem(this);
        state_ = State::Ready;
    } else {
        state_ = State::Error;
    }
}

ProcessGroupWorker::ProcessGroupWorker(ProcessID& pid, sock::SockFD& worker_fd)
{
    info_.pid_ = pid;
    worker_fd_ = worker_fd;
    state_ = State::Ready;
}

ProcessGroupWorker::~ProcessGroupWorker()
{

}

sock::SockFD& ProcessGroupWorker::GetWorkerFD()
{
    return worker_fd_;
}

ProcessGroupWorker::SelectItem& ProcessGroupWorker::GetSelectItem()
{
    return select_item_;
}

ProcessGroupWorker::State& ProcessGroupWorker::GetState()
{
    return state_;
}

bool ProcessGroupWorker::IsReady()
{
    return (state_ == State::Ready);
}

}
