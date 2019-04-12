#include "stddef.h"
#include "process_signal_ctrl.h"

namespace process::signal {

ProcessSignalCtrl* ProcessSignalCtrl::pInstance = NULL;

ProcessSignalCtrl::ProcessSignalCtrl()
{
    mempool_ = mempool::MemPool::getInstance();
}

ProcessSignalCtrl::~ProcessSignalCtrl()
{

}

ProcessSignalCtrl* ProcessSignalCtrl::getInstance()
{
    if (!pInstance) {
        pInstance = new ProcessSignalCtrl();
    }
    return pInstance;
}

ProcessRet ProcessSignalCtrl::Register(ProcessSignal& sig, ProcessSignalAction& action)
{
    ProcessSignalAction old_action;
    return Register(sig, action, old_action);
}

ProcessRet ProcessSignalCtrl::Register(ProcessSignal& sig, ProcessSignalAction& new_action, ProcessSignalAction& old_action)
{
    ProcessRet ret = ProcessRet::SUCCESS;
    if ((ret = _register_signal(sig, new_action, old_action)) != ProcessRet::SUCCESS) {
        return ret;
    }
    //std::pair<std::map<ProcessSignal, ProcessSignalAction>::iterator, bool> ret;
    register_map_.insert_or_assign(sig, new_action);
    last_register_map_.insert_or_assign(sig, old_action);
    return ProcessRet::SUCCESS;
}

ProcessRet ProcessSignalCtrl::UnRegister()
{
    ProcessRet ret;
    ProcessSignal sig;
    std::map<ProcessSignal, ProcessSignalAction> register_map = register_map_;
    for (const auto& it : register_map) {
        sig = it.first;
        ret = UnRegister(sig);
        if ( ret != ProcessRet::SUCCESS) {
            return ret;
        }
    }
    return ProcessRet::SUCCESS;
}

ProcessRet ProcessSignalCtrl::UnRegister(ProcessSignal& sig)
{
    ProcessSignalAction old_action;
    return UnRegister(sig, old_action);
}

ProcessRet ProcessSignalCtrl::UnRegister(ProcessSignal& sig, ProcessSignalAction& old_action)
{
    ProcessSignalAction default_action;
    return Register(sig, default_action, old_action);
}

ProcessRet ProcessSignalCtrl::Revert()
{
    ProcessRet ret;
    ProcessSignal sig;
    ProcessSignalAction action;
    std::map<ProcessSignal, ProcessSignalAction> register_map = last_register_map_;
    for (const auto& it : register_map) {
        sig = it.first;
        action = it.second;
        ret = Register(sig, action);
        if ( ret != ProcessRet::SUCCESS) {
            return ret;
        }
    }
    return ProcessRet::SUCCESS;
}

ProcessRet ProcessSignalCtrl::Revert(ProcessSignal& sig)
{
    auto it = last_register_map_.find(sig);
    if (it == last_register_map_.end()) {
        return ProcessRet::PROCESS_ESIGNALNOTFOUND;
    }
    ProcessSignalAction action = it->second;
    return Register(sig, action);
}

ProcessRet ProcessSignalCtrl::Mask()
{
    ProcessSignalSet new_set;
    ProcessSignalSet old_set;
    new_set.AddAll();
    return Mask(new_set, old_set);
}

ProcessRet ProcessSignalCtrl::Mask(ProcessSignalSet& set)
{
    ProcessSignalSet old_set;
    return Mask(set, old_set);
}

ProcessRet ProcessSignalCtrl::Mask(ProcessSignalSet& new_set, ProcessSignalSet& old_set)
{
    ProcessRet ret = _mask_signal(SignalMaskType::APPEND, new_set, old_set);
    if (ret != ProcessRet::SUCCESS) {
        return ret;
    }
    last_mask_set_ = old_set;
    ret = _mask_signal(SignalMaskType::GETMASK, mask_set_, mask_set_);
    if (ret != ProcessRet::SUCCESS) {
        return ret;
    }
    return ProcessRet::SUCCESS;
}

ProcessRet ProcessSignalCtrl::MaskReplace(ProcessSignalSet& set)
{
    ProcessSignalSet old_set;
    return MaskReplace(set, old_set);
}

ProcessRet ProcessSignalCtrl::MaskReplace(ProcessSignalSet& new_set, ProcessSignalSet& old_set)
{
    ProcessRet ret = _mask_signal(SignalMaskType::REPLACE, new_set, old_set);
    if (ret != ProcessRet::SUCCESS) {
        return ret;
    }
    mask_set_ = new_set;
    last_mask_set_ = old_set;
    return ProcessRet::SUCCESS;
}

ProcessRet ProcessSignalCtrl::UnMask()
{
    ProcessSignalSet new_set;
    ProcessSignalSet old_set;
    new_set.AddAll();
    return UnMask(new_set, old_set);
}

ProcessRet ProcessSignalCtrl::UnMask(ProcessSignalSet& set)
{
    ProcessSignalSet old_set;
    return UnMask(set, old_set);
}

ProcessRet ProcessSignalCtrl::UnMask(ProcessSignalSet& new_set, ProcessSignalSet& old_set)
{
    ProcessRet ret = _mask_signal(SignalMaskType::SUBTRACT, new_set, old_set);
    if (ret != ProcessRet::SUCCESS) {
        return ret;
    }
    last_mask_set_ = old_set;
    ret = _mask_signal(SignalMaskType::GETMASK, mask_set_, mask_set_);
    if (ret != ProcessRet::SUCCESS) {
        return ret;
    }
    return ProcessRet::SUCCESS;
}

ProcessRet ProcessSignalCtrl::MaskRevert()
{
    ProcessSignalSet set = last_mask_set_;
    return Mask(set);
}

ProcessRet ProcessSignalCtrl::_register_signal(ProcessSignal& sig, ProcessSignalAction& new_action, ProcessSignalAction& old_action)
{

}

ProcessRet ProcessSignalCtrl::_mask_signal(SignalMaskType how, ProcessSignalSet& new_set, ProcessSignalSet& old_set)
{

}

}
