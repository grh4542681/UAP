/*******************************************************
 * Copyright (C) For free.
 * All rights reserved.
 *******************************************************
 * @author   : Ronghua Gao
 * @date     : 2019-04-18 04:14
 * @file     : process_signal_set.cc
 * @brief    : ProcessSignal set.
 * @note     : Email - grh4542681@163.com
 * ******************************************************/
#include "process_signal_set.h"

namespace process::signal {

ProcessSignalSet::ProcessSignalSet()
{
    sigemptyset(&set_);
}

ProcessSignalSet::ProcessSignalSet(const ProcessSignalSet& other)
{
    set_ = other.set_;
}

ProcessSignalSet::~ProcessSignalSet()
{
    sigemptyset(&set_);
}

ProcessSignalSet& ProcessSignalSet::operator=(const ProcessSignalSet& other)
{
    set_ = other.set_;
    return *this;
}

ProcessRet ProcessSignalSet::AddSig(ProcessSignal& sig)
{
    return AddSig(std::move(sig));
}
ProcessRet ProcessSignalSet::AddSig(ProcessSignal&& sig)
{
    if (!sigaddset(&set_, sig.sig_)) {
        return ProcessRet::PROCESS_ESIGINVAL;
    }
    return ProcessRet::SUCCESS;
}

ProcessRet ProcessSignalSet::AddAll()
{
    if (!sigfillset(&set_)) {
        return ProcessRet::PROCESS_ESIGINVAL;
    }
    return ProcessRet::SUCCESS;
}

ProcessRet ProcessSignalSet::DelSig(ProcessSignal& sig)
{
    return DelSig(std::move(sig));
}
ProcessRet ProcessSignalSet::DelSig(ProcessSignal&& sig)
{
    if (!sigdelset(&set_, sig.sig_)) {
        return ProcessRet::PROCESS_ESIGINVAL;
    }
    return ProcessRet::SUCCESS;
}


ProcessRet ProcessSignalSet::DelAll()
{
    if (!sigemptyset(&set_)) {
        return ProcessRet::PROCESS_ESIGINVAL;
    }
    return ProcessRet::SUCCESS;
}

bool ProcessSignalSet::HasSig(ProcessSignal& sig)
{
    if (sigismember(&set_, sig.sig_) == 1) {
        return true;
    }
    return false;
}

sigset_t* ProcessSignalSet::GetSigset()
{
    return &set_;
}

}
