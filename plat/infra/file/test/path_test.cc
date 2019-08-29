#include "file_path.h"

int main() {
    std::string s = "  /opt/test//11.txt ";
    file::FilePath p;
    p.Split(s);
    printf("%s\n",p.GetRaw().c_str());
    return 0;
}
