#include <string.h>
#include <unistd.h>

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
        file_name_.erase();
        fd_ = -1;
        ffd_ = NULL;
        state_ = FileState::INVALID;
        FILE_ERROR("File descriptor invalid.");
    } else {
        if (GetFileName(fd, file_name_) != FileRet::SUCCESS) {
            file_name_.erase();
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

FileC::FileC(FILE* ffd)
{
    if (!ffd || fileno(ffd) < 0) {
        file_name_.erase();
        fd_ = -1;
        ffd_ = NULL;
        state_ = FileState::INVALID;
        FILE_ERROR("File stream pointer invalid.");
    } else {
        fd_ = fileno(ffd);
        if (GetFileName(fd_, file_name_) != FileRet::SUCCESS) {
            file_name_.erase();
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

FileC::~FileC()
{
    if (state_ == FileState::INTEROPENED) {
        Close();
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
        std::string smode;
        FileModeOp::FileModeConvert(mode, smode);
        ffd_ = fopen(file_name_.c_str(), smode.c_str());
        if (!ffd_) {
            return FileRet::ERROR;
        }
        fd_ = fileno(ffd_);
        state_ = FileState::INTEROPENED;
        return FileRet::SUCCESS;        
    } else {
        return FileRet::FILE_ESTATE;
    }
}

FileRet FileC::Open(FileMode mode)
{
    return Open((int)mode);
}

FileRet FileC::Close()
{
    if (state_ == FileState::INTEROPENED) {

    }
    return FileRet::SUCCESS;
}

int FileC::Read(void* data, unsigned int datalen)
{
    if (state_ == FileState::EXTEROPENED || state_ == FileState::INTEROPENED) {
        return fread(data, datalen, 1, ffd_);
    } else {
        return 0;
    }
}

int FileC::Write(const void* data, unsigned int datalen)
{
    if (state_ == FileState::EXTEROPENED || state_ == FileState::INTEROPENED) {
        return fwrite(data, datalen, 1, ffd_);
    } else {
        return 0;
    }
}

FileRet FileC::GetFileName(int fd, std::string& ofilename)
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

FileRet FileC::GetFileName(FILE* ffd, std::string& filename)
{
    return GetFileName(fileno(ffd), filename);
}

}
