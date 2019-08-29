#ifndef __FILE_PATH_H__
#define __FILE_PATH_H__

#include <string>
#include <vector>

namespace file {

class FilePath {
public:
    FilePath();
    ~FilePath();

    void Split(std::string raw);
    std::string GetRaw();
    int GetDepth();
    std::string GetPath(int depth);

public:
    static std::string GetFileName(std::string raw);
    static std::string GetPathName(std::string raw);
private:
    std::string raw_;
    int depth_;
    std::vector<std::string> path_vector_;
};

}

#endif
