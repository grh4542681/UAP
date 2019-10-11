#include "node_tree.h"

int main() {
    container::NodeTree tr;

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

    estr.Insert(eint);
    auto p = estr.Search<container::NodeTree>("int");
    if (!p) {
        printf("not found\n");
        return 0;
    }
//    p->Get(&int_t);
    printf("name -- %s  %d \n", p->name.c_str(), int_t);

    return 0;
}
