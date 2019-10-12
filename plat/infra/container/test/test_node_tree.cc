#include "node_tree.h"

int main() {
    container::NodeTree tr;

    container::NodeTree::Element<int> eint1("int1");
    eint1.Add(5);
    container::NodeTree::Element<int> eint2("int2");
    eint2.Add(5);
    container::NodeTree::Element<int> eint3("int3");
    eint3.Add(5);
    container::NodeTree::Element<int> eint4("int4");
    eint4.Add(5);
    container::NodeTree::Element<int> eint5("int5");
    eint5.Add(5);
    container::NodeTree::Element<int> eint6("int6");
    eint6.Add(5);
    container::NodeTree::Element<int> eint7("int7");
    eint7.Add(5);

    container::NodeTree::Element<int> eint("int");
    eint.Add(5);
    int int_t;
    eint.Get(&int_t);
    printf("%d\n",int_t);

    container::NodeTree::Element<std::string> estr("string");
    estr.Add("test");
    std::string str_t;
    estr.Get(&str_t);
    printf("%s\n",str_t.c_str());

    eint5.Insert(eint6);
    eint5.Insert(eint6);
    eint5.Insert(eint6);
    eint1.Insert(eint5);
    eint1.Insert(eint6);
    eint4.Insert(eint5);
    eint4.Insert(eint5);
    eint4.Insert(eint5);

    estr.Insert(eint);
    printf("---0---\n");
    estr.Insert(eint1);
    printf("---1---\n");
    estr.Insert(eint2);
    printf("---2---\n");
    estr.Insert(eint3);
    printf("---3---\n");
    estr.Insert(eint4);
    printf("---4---\n");
    auto p = estr.Search<int>("int");
    if (!p) {
        printf("not found\n");
        return 0;
    }
    p->Get(&int_t);
    printf("name -- %s  %d \n", p->GetName().c_str(), int_t);

    estr.PrintBranch();
    printf("-------------------------------------------\n");
    std::vector<container::NodeTree::Element<int>*> vec;
    estr.Search<int>("int4/int5/int6", vec);
    printf("vec num %d\n", vec.size());

    return 0;
}
