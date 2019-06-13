#include "ns_log.h"
#include "ns_return.h"
#include "ns_endpoint.h"

namespace ns{

thread_local NsEndPoint* NsEndPoint::pInstance = NULL;

NsEndPoint::NsEndPoint(std::string ep_name)
{
    if (ep_name.empty()) {
        NS_ERROR("Bad ep name");
        return;
    }
    this->ep_info_.ep_name_ = ep_name;
    if (!_init()) {
        NS_ERROR("NsEndPoint[%s] init error", ep_name.c_str());
        return;
    }
}

NsEndPoint::~NsEndPoint()
{

}

NsRet NsEndPoint::Register()
{

}

NsRet NsEndPoint::Update()
{

}

NsRet NsEndPoint::Unregister()
{

}

bool _init()
{

}

}
