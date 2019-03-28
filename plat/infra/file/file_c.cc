#include "file_c.h"

namespace file {

FileC::FileC(std::string filename)
{
    file_name_ = filename;
    fd_ = -1;
    ffd_ = NULL;
    state_ = FileState::NONE;
}

FileC::FileC(int fd)
{
    int flag = fcntl(fd, F_GETFL);
    if (flag < 0) {
        filename = "";
        fd_ = -1;
        ffd_ = NULL;
        state_ = FileState::INVALID;
        FILE_ERROR("File descriptor invalid.");
    } else {
        if (_GetFileName(fd, file_name_) != FileRet::SUCCESS) {
            filename = "";
            fd_ = -1;
            ffd_ = NULL;
            state_ = FileState::INVALID;
            FILE_ERROR("Get filename from file descriptor error.");
        } else {
            fd_ = fd;
            ffd_ = fdopen(fd, "w+");
            if (!ffd_) {
                state_ = FileState::INVALID;
                FILE_ERROR("Convert file descriptor to file stream pointer error.");
            } else {
                state_ = FileState::INTEROPENED;
            }
        }
    }
}

FileC::FileC(File* ffd)
{
    if (!ffd || fileno(ffd) < 0) {
        filename = "";
        fd_ = -1;
        ffd_ = NULL;
        state_ = FileState::INVALID;
        FILE_ERROR("File stream pointer invalid.");
    } else {
        fd_ = fileno(ffd);
        if (_GetFileName(fd, file_name_) != FileRet::SUCCESS) {
            filename = "";
            fd_ = -1;
            ffd_ = NULL;
            state_ = FileState::INVALID;
            FILE_ERROR("Get filename from file descriptor error.");
        } else {
            ffd_ = ffd;
            state_ = FileState::INTEROPENED;
        }
    }
}

FileRet _GetFileName(int fd, std::string& filename)
{
    char buf[1024];
    char filename[1024];
    memset(buf ,0x00, sizeof(buf));
    memset(filename, 0x00, sizeof(filename));

    sprintf(buf, "/proc/self/fd/%d", fd);
    if (readlink(buf, filename, sizeof(filename)-1) < 0) {
        int tmperrno = errno;
        return _error2ret(tmperrno);
    }
    filename = std::string(filename);
    return FileRet::SUCCESS;
}

FileRet _GetFileName(FILE* ffd, std::string& filename)
{
    return _GetFileNname(fileno(ffd), filename);
}

}
