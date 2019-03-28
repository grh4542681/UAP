#include "file_c.h"

namespace file {

FileC::FileC(std::string filename)
{
    file_name_ = filename;
    fd_ = -1;
    ffd_ = NULL;
    state_ = FileState::INTERCLOSEED;
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
                state_ = FileState::EXTEROPENED;
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
            state_ = FileState::EXTEROPENED;
        }
    }
}

int FileC::GetFd()
{
    return fd_;
}

FILE* FileC::GetFFd()
{
    return ffd_;
}

FileRet FileC::Open(unsigned int mode)
{
    if (state_ == FileState::INVALID) {
        return FileRet::EINIT;
    } else if (state_ == FileState::EXTEROPENED) {
        return FileRet::SUCCESS;
    } else if (state_ == FileState::INTERCLOSEED) {
        
    } else {
        return FileRet::ESTATE;
    }
}

FileRet FileC::Close()
{

}

int FileC::Read(void* data, unsigned int datalen)
{

}

int FileC::Write(void* data, unsigned int datalen)
{

}

FileRet FileC::_GetFileName(int fd, std::string& filename)
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

FileRet FileC::_GetFileName(FILE* ffd, std::string& filename)
{
    return _GetFileNname(fileno(ffd), filename);
}

}
