#include "message_heartbeat_element.h"

namespace message {

HeartbeatElement::HeartbeatElement(const MessageURI& orig_uri, const MessageURI dest_uri, const  timer::Time frequency, unsigned int fault_tolerance) :
                    orig_uri_(orig_uri), dest_uri_(dest_uri), frequency_(frequency), fault_tolerance_(fault_tolerance)
{
    interval_ = 0;
}

HeartbeatElement::~HeartbeatElement()
{

}

}
