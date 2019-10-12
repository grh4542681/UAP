#ifndef __NODE_TREE_H__
#define __NODE_TREE_H__

#include <unistd.h>

#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include <typeinfo>

#include "mempool.h"
#include "string/string_util.h"

#include "container_return.h"
#include "container_log.h"

namespace container {

class NodeTree {
public:
    enum class ElementType {
        Fundamental,
        Array,
        Compound,
        Path,
    };

    class ElementPath {
    public:
        ElementPath(std::string ename = "");
        ElementPath(const ElementPath& other);
        virtual ~ElementPath() { };
        virtual const std::type_info& GetTypeinfo() {
            return typeid(ElementPath);
        }

        std::string GetName();

        ElementPath* SearchPath(std::string path);
        ElementPath* SearchChild(std::string name);
        ElementPath* SearchBrother(std::string ename);
        ContainerRet SearchPathAll(std::string path, std::vector<ElementPath*>& vec);
        ContainerRet SearchChildAll(std::string name, std::vector<ElementPath*>& vec);
        ContainerRet SearchBrotherAll(std::string ename, std::vector<ElementPath*>& vec);

        ElementPath* InsertChild(ElementPath* element);
        ElementPath* InsertNext(ElementPath* element);
        ElementPath* InsertPrev(ElementPath* element);

        ContainerRet DeletePath(std::string name);
        ContainerRet DeleteChild(std::string name);
        ContainerRet DeleteBrother(std::string name);
        ContainerRet DeletePathAll(std::string name);
        ContainerRet DeleteChildAll(std::string name);
        ContainerRet DeleteBrotherAll(std::string name);

        void PrintBranch(int depth = 0, std::string line = "");

    protected:
        std::string name;
        ElementPath* next = nullptr;
        ElementPath* prev = nullptr;
        ElementPath* parent = nullptr;
        ElementPath* child = nullptr;

        ContainerRet SearchPathAll(std::vector<std::string> path_vec, std::vector<ElementPath*>& vec);
    };


    template < typename T > class Element : public ElementPath {
    public:
        Element(std::string name, ElementType type = ElementType::Fundamental) : ElementPath(name), element_type_(type) {
            mempool_ = mempool::MemPool::getInstance();
        }
        ~Element() { }

        const std::type_info& GetTypeinfo() {
            return typeid(T);
        }

        void Add(const T& data) {
            if (element_type_ == ElementType::Array) {
                element_data_.push_back(data);
            } else {
                element_data_.clear();
                element_data_.push_back(data);
            }
        }
        ContainerRet Get(T* data, unsigned int index = 0) {
            if (index > element_data_.size()) {
                return ContainerRet::NT_EINDEXCROSS;
            }
            *data = element_data_[index];
            return ContainerRet::SUCCESS;
        }

        template < typename D > Element<D>* operator[](std::string path) {
            return Search(path);
        }

        template < typename D > Element<D>* Search(std::string path) {
            ElementPath* ptr = SearchPath(path);
            if (!ptr) {
                return NULL;
            }
            Element<D>* eptr = dynamic_cast<Element<D>*>(ptr);
            if (!eptr) {
                CONTAINER_ERROR("Mismatched type \"%s\" need \"%s\"", typeid(D).name(), ptr->GetTypeinfo().name());
                return NULL;
            }
            return eptr;
        }
        template < typename D > ContainerRet Search(std::string path, std::vector<Element<D>*>& vec) {
            std::vector<NodeTree::ElementPath*> evec;
            SearchPathAll(path, evec);
            if (evec.size() == 0) {
                return ContainerRet::NT_ENOTFOUND;
            } else {
                for (auto it : evec) {
                    Element<D>* eptr = dynamic_cast<Element<D>*>(it);
                    if (!eptr) {
                        CONTAINER_ERROR("Mismatched type \"%s\" need \"%s\"", typeid(D).name(), it->GetTypeinfo().name());
                        return ContainerRet::NT_ENOTFOUND;
                    }
                    vec.push_back(eptr);
                }
            }
            return ContainerRet::SUCCESS;
        }

        template < typename D > ContainerRet Insert(std::string name, const D& data) {
            Element<D> element(name, ElementType::Fundamental);
            element.Add(data);
            return Insert(element);
        }
        template < typename D > ContainerRet Insert(std::string name, const std::vector<D> data) {
            Element<D> element(name, ElementType::Array);
            for (auto it : data) {
                element.Add(it);
            }
            return Insert(element);
        }
        template < typename D > ContainerRet Insert(std::string name, const std::vector<D*> data) {
            Element<D> element(name, ElementType::Array);
            for (auto it : data) {
                element.Add(*it);
            }
            return Insert(element);
        }

        template < typename D > ContainerRet Insert(const Element<D>& element) {
            Element<D>* p_element = mempool_->Malloc<Element<D>>(element);
            if (p_element == NULL) {
                return ContainerRet::EMALLOC;
            }
            InsertChild(p_element);
            return ContainerRet::SUCCESS;
        }
        ContainerRet Insert(ElementPath& element) {
            ElementPath* p_element = mempool_->Malloc<ElementPath>(element);
            if (p_element == NULL) {
                return ContainerRet::EMALLOC;
            }
            InsertChild(p_element);
            return ContainerRet::SUCCESS;
        }
    private:
        mempool::MemPool* mempool_ = nullptr;
        std::string element_name_;
        ElementType element_type_;
        std::vector<T> element_data_;
    };

public:
    NodeTree() {
    }
    ~NodeTree(){

    }

//    virtual Load(std::string str);
//    virtual Load(file::File& file);
//    virtual Store(std::string str);
//    virtual Store(file::File& file);

private:

//    ElementPath root_;
};

} //namespace end

#endif
