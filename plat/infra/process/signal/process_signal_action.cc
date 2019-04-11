#include "stddef.h"

#include "process_signal_action.h"

namespace process::signal {

ProcessSignalAction::ProcessSignalAction()
{

}

ProcessSignalAction::ProcessSignalAction(struct sigaction* action)
{
    action_.sa_handler = action->sa_handler;
    action_.sa_sigaction = action->sa_sigaction;
    action_.sa_mask = action->sa_mask;
    action_.sa_flags = action->sa_flags;
}

ProcessSignalAction::ProcessSignalAction(const ProcessSignalAction& other)
{
    action_.sa_handler = other.action_.sa_handler;
    action_.sa_sigaction = other.action_.sa_sigaction;
    action_.sa_mask = other.action_.sa_mask;
    action_.sa_flags = other.action_.sa_flags;
}

ProcessSignalAction::~ProcessSignalAction()
{

}

ProcessSignalAction& ProcessSignalAction::operator=(const ProcessSignalAction& other)
{
    action_.sa_handler = other.action_.sa_handler;
    action_.sa_sigaction = other.action_.sa_sigaction;
    action_.sa_mask = other.action_.sa_mask;
    action_.sa_flags = other.action_.sa_flags;
    return *this;
}

void ProcessSignalAction::SetCallback(SignalCallback callback)
{
    action_.sa_handler = callback;
    action_.sa_sigaction = NULL;
    action_.sa_flags &= ~SA_SIGINFO;
}

void ProcessSignalAction::SetCallback(SignalCallback2 callback)
{
    action_.sa_handler = NULL;
    action_.sa_sigaction = callback;
    action_.sa_flags |= SA_SIGINFO;
}

void ProcessSignalAction::SetMaskset(ProcessSignalSet& set)
{
    action_.sa_mask = set.set_;
}

}