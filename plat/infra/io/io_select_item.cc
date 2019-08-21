#include "mempool.h"
#include "io_log.h"
#include "io_select_item.h"

namespace io {

SelectItem::SelectItem(FD& fd)
{
    fd_ = fd.Clone();
}

SelectItem::~SelectItem()
{
    if (fd_) {
        mempool::MemPool::getInstance()->Free<FD>(fd_);
    }
}

IoRet SelectItem::AddEvent(int event, Callback func)
{
    if (!fd_) {
        return IoRet::EINIT;
    }
    auto it = func_map_.find(event);
    if (it == func_map_.end()) {
        return IoRet::IO_EUNKNOWEVENT;
    } else {
        it->second = func;
        return IoRet::SUCCESS;
    }
}

IoRet SelectItem::DelEvent(int event)
{
    return IoRet::SUCCESS;
}

SelectItem::Callback SelectItem::GetFunc(int event)
{

}

}
