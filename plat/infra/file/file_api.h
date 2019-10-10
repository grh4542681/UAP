#ifndef __FILE_API_H__
#define __FILE_API_H__

#include "file_return.h"

namespace file {

FileRet GetFileName(int fd, std::string& filename);
FileRet GetFileName(FILE* ffd, std::string& filename);
std::string GetFileExtension(std::string filename);

}

#endif
