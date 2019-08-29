#include "file_path.h"

namespace file {

FilePath::FilePath()
{
    raw_.clear();
    file_.clear();
    path_vector_.clear();
}

FilePath::~FilePath() {

}

void FilePath::Split(std::string raw) {
    raw_.clear();
    file_.clear();
    path_vector_.clear();

    raw_ = raw;

    if (raw_.empty()) {
        return;
    }
    raw_.erase(0, raw_.find_first_not_of(" "));
    raw_.erase(raw_.find_last_not_of(" ") + 1);
}

std::string FilePath::GetRaw() {
    return raw_;
}

std::string FilePath::GetPath(int depth) {
    return path_;
}

}
