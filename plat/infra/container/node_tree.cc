#include "node_tree.h"

namespace container {

NodeTree::ElementPath::ElementPath(std::string ename) : name(ename)
{
    next = NULL;
    prev = NULL;
    parent = NULL;
    child = NULL;
}

NodeTree::ElementPath::ElementPath(const NodeTree::ElementPath& other)
{
    name = other.name;
    next = other.next;
    prev = other.prev;
    parent = other.parent;
    child = other.child;
}

std::string NodeTree::ElementPath::GetName()
{
    return name;
}

NodeTree::ElementPath* NodeTree::ElementPath::SearchPath(std::string path)
{
    std::vector<std::string> path_vec;
    util::String::Split(path, "/", path_vec);
    std::reverse(std::begin(path_vec), std::end(path_vec));

    NodeTree::ElementPath* ptr = this;
    for (auto it : path_vec) {
        ptr = ptr->SearchChild(it);
        if (!ptr) return NULL;
    }
    return ptr;
}

NodeTree::ElementPath* NodeTree::ElementPath::SearchChild(std::string name)
{
    if (!child) {
        return NULL;
    }
    return child->SearchBrother(name);
}

NodeTree::ElementPath* NodeTree::ElementPath::SearchBrother(std::string ename)
{
    if (name == ename) {
        return this;
    }
    NodeTree::ElementPath* ptr = prev;
    while(ptr) {
        if (ptr->name == ename) {
            return ptr;
        }
        ptr = ptr->prev;
    }
    ptr = next;
    while(ptr) {
        if (ptr->name == ename) {
            return ptr;
        }
        ptr = ptr->next;
    }
    return NULL;
}

ContainerRet NodeTree::ElementPath::SearchPathAll(std::string path, std::vector<NodeTree::ElementPath*>& vec)
{
    std::vector<std::string> path_vec;
    util::String::Split(path, "/", path_vec);
    std::reverse(std::begin(path_vec), std::end(path_vec));

    return SearchPathAll(path_vec, vec);
}

ContainerRet NodeTree::ElementPath::SearchPathAll(std::vector<std::string> path_vec, std::vector<NodeTree::ElementPath*>& vec)
{
    if (path_vec.size() == 0) {
        return ContainerRet::SUCCESS;
    } else if (path_vec.size() == 1) {
        std::string path = path_vec.back();
        path_vec.pop_back();
        return SearchChildAll(path, vec);
    } else {
        std::string path = path_vec.back();
        path_vec.pop_back();
        std::vector<NodeTree::ElementPath*> path_vec_tmp;
        SearchChildAll(path, path_vec_tmp);
        for (auto it : path_vec_tmp) {
            it->SearchPathAll(path_vec, vec);
        }
        return ContainerRet::SUCCESS;
    }
}

ContainerRet NodeTree::ElementPath::SearchChildAll(std::string name, std::vector<NodeTree::ElementPath*>& vec)
{
    if (!child) {
        return ContainerRet::NT_ENOTFOUND;
    }
    return child->SearchBrotherAll(name, vec);
}

ContainerRet NodeTree::ElementPath::SearchBrotherAll(std::string ename, std::vector<NodeTree::ElementPath*>& vec)
{
    if (name == ename) {
        vec.push_back(this);
    }
    NodeTree::ElementPath* ptr = prev;
    while(ptr) {
        if (ptr->name == ename) {
            vec.push_back(ptr);
        }
        ptr = ptr->prev;
    }
    ptr = next;
    while(ptr) {
        if (ptr->name == ename) {
            vec.push_back(ptr);
        }
        ptr = ptr->next;
    }
    return vec.size() ? ContainerRet::SUCCESS : ContainerRet::NT_ENOTFOUND;
}

NodeTree::ElementPath* NodeTree::ElementPath::InsertChild(NodeTree::ElementPath* element)
{
    if (!child) {
        child = element;
        child->parent = this;
        return child;
    }
    return child->InsertNext(element);
}

NodeTree::ElementPath* NodeTree::ElementPath::InsertNext(NodeTree::ElementPath* element)
{
    if (!next) {
        next = element;
        next->prev = this;
        next->parent = parent;
        return next;
    }
    NodeTree::ElementPath* ptr = next;
    while(ptr->next) {
        ptr = ptr->next;
    }
    ptr->next = element;
    ptr->next->prev = ptr;
    ptr->next->parent = parent;

    return ptr->next;
}

NodeTree::ElementPath* NodeTree::ElementPath::InsertPrev(NodeTree::ElementPath* element)
{
    if (!prev) {
        prev = element;
        prev->next = this;
        prev->parent = parent;
        return prev;
    }
    NodeTree::ElementPath* ptr = prev;
    while(!ptr->prev) {
        ptr = ptr->prev;
    }
    ptr->prev = element;
    ptr->prev->next = ptr;
    ptr->prev->parent = parent;

    return ptr->prev;
}

ContainerRet NodeTree::ElementPath::DeletePath(std::string name)
{}

ContainerRet NodeTree::ElementPath::DeleteChild(std::string name)
{}

ContainerRet NodeTree::ElementPath::DeleteBrother(std::string name)
{}

ContainerRet NodeTree::ElementPath::DeletePathAll(std::string name)
{}

ContainerRet NodeTree::ElementPath::DeleteChildAll(std::string name)
{}

ContainerRet NodeTree::ElementPath::DeleteBrotherAll(std::string name)
{}

void NodeTree::ElementPath::PrintBranch(int depth, std::string line)
{
#define SINGLE_CHILD_LINE "---"
#define FIRST_CHILD_LINE "-+-"
#define NEXT_CHILD_LINE " |-"
#define LAST_CHILD_LINE " `-"
#define INDENT_CHAR '|'
#define EXTEN_CHAR '+'
    std::string raw_line = line;
    for (auto& c : raw_line) {
        if (c != EXTEN_CHAR && c != INDENT_CHAR) {
            c = ' ';
        } else {
            c = INDENT_CHAR;
        }
    }

    if (depth == 0) {
        line += name;
    } else {
        if (!next && !prev) {
            line += SINGLE_CHILD_LINE;
        } else if (!prev) {
            line += FIRST_CHILD_LINE;
        } else if (!next) {
            line += LAST_CHILD_LINE;
        } else {
            line += NEXT_CHILD_LINE;
        }
        line += name;
    }

    if (!child) {
        std::cout << line << std::endl;
        if (next) {
            next->PrintBranch(depth, raw_line);
        }
    } else {
        child->PrintBranch(depth+1, line);
        if (next) {
            next->PrintBranch(depth, raw_line);
        }
    }
}

}
