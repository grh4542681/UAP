#include <unistd.h>
#include <vector>

#include "string/string_util.h"

#include "file_api.h"
#include "file_log.h"

namespace file {

FileRet GetFileName(int fd, std::string& ofilename)
{
    char buf[1024];
    char filename[1024];
    memset(buf ,0x00, sizeof(buf));
    memset(filename, 0x00, sizeof(filename));

    sprintf(buf, "/proc/self/fd/%d", fd);
    if (readlink(buf, filename, sizeof(filename)-1) < 0) {
        int tmperrno = errno;
        FILE_ERROR("Get file name from file descriptor error");
        return tmperrno;
    }
    ofilename = std::string(filename);
    return FileRet::SUCCESS;
}

FileRet GetFileName(FILE* ffd, std::string& filename)
{
    return GetFileName(fileno(ffd), filename);
}

std::string GetFileExtension(std::string filename)
{
    std::vector<std::string> vec;
    util::String::Split(filename, ".", vec);
    return vec.back();
}

}
