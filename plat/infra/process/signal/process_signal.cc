#include "process_signal.h"

namespace process::signal {

ProcessSignal::ProcessSignal()
{

}

ProcessSignal::ProcessSignal(int sig) : sig_(sig)
{

}

ProcessSignal::ProcessSignal(const ProcessSignal& other)
{
    sig_ = other.sig_;
}

ProcessSignal::~ProcessSignal()
{

}

ProcessSignal& ProcessSignal::operator=(const ProcessSignal& other)
{
    sig_ = other.sig_;
    return *this;
}

bool ProcessSignal::operator<(const ProcessSignal& other) const
{
    return (sig_ < other.sig_);
}

}
