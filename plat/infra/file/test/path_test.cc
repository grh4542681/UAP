#include "file_path.h"

int main() {
    std::string s = "  a/a/a/a/a/a/a/a/a/a/opt///////test//11 txt ";
    file::FilePath p(s);
    printf("%s\n",p.GetRaw().c_str());
    printf("%s\n",p.GetPath().c_str());
    return 0;
}
