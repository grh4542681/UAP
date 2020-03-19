#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <string>

namespace base {

class Object {
public:
    Object() { }
    Object(Object& other) {
        object_name_ = other.object_name_;
        object_type_name_ = other.object_type_name_;
        object_describe_ = other.object_describe_;
    }
    virtual ~Object() { }

    const Object& operator=(const Object& other) {
        object_name_ = other.object_name_;
        object_type_name_ = other.object_type_name_;
        object_describe_ = other.object_describe_;
        return *this;
    }

    std::string ObjectName() {
        return object_name_;
    }
    std::string ObjectTypeName() {
        return object_type_name_;
    }
    std::string ObjectDesctibe() {
        return object_describe_;
    }

    std::string object_name_ = "Object";
    std::string object_type_name_ = "Object";
    std::string object_describe_ = "Base object";

};

}

#endif
