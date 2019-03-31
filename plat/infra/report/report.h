#ifndef __REPORT_H__
#define __REPORT_H__

#include <iostream>
#include <sstream>

#include "report_mode.h"
#include "file.h"

namespace report {

class VReport {
public:
    virtual void Report(file::File&& fd, ReportMode mode) { };
    virtual void Report(std::stringstream& ss, ReportMode mode) { };
};

void ReportRegister(std::string name, VReport& report);

};

#endif
