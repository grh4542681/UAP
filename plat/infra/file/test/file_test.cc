#include "file_c.h"
#include "file_mode.h"

int main()
{
    file::FileC cf("test.txt");
    file::FileC cf1(stdout);

    cf1.Open(file::FileMode::APPEND|file::FileMode::READ_ONLY|file::FileMode::WRITE_ONLY);
    cf1.Open(file::FileMode::APPEND);
    cf1.Write("hello\n", 6);

    std::string name;
    file::FileC::GetFileName(stdout, name);
    printf("name %s\n",name.c_str());

    return 0;
}
