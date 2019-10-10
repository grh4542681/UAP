#ifndef __REPORT_H__
#define __REPORT_H__

#include <iostream>
#include <sstream>

#include "report_mode.h"

namespace file {
class File;
}

namespace report {

class VReport {
public:
    VReport() { }
    virtual ~VReport() { }
    virtual void Report(file::File&& fd, ReportMode mode) { };
    virtual void Report(std::stringstream& ss, ReportMode mode) { };
};

void ReportRegister(std::string name, VReport& report);

};

#endif
