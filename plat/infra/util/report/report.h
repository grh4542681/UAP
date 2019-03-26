#ifndef __REPORT_H__
#define __REPORT_H__

#include <sstream>

namespace util {

class Report {
public:
    virtual std::ostringstream format();
    void report();
    void notify();
};

};

#endif