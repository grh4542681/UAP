#ifndef __NODE_TREE_H__
#define __NODE_TREE_H__

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
    };

    class ElementAny {
    public:
        ElementAny(std::string ename = "") : name(ename) { }
        ElementAny(const ElementAny& other) {
            name = other.name;
            next = other.next;
            prev = other.prev;
            parent = other.parent;
            child = other.child;
        }
        virtual ~ElementAny() { };
        virtual const std::type_info& GetTypeinfo() = 0;

        ElementAny* SearchPath(std::string path) {
            std::vector<std::string> path_vec;
            util::String::Split(path, "/", path_vec);
            std::reverse(std::begin(path_vec), std::end(path_vec));

            ElementAny* ptr = this;
            for (auto it : path_vec) {
                ptr = ptr->SearchChild(it);
                if (!ptr) return NULL;
            }
            return ptr;
        }
        ElementAny* SearchChild(std::string name) {
            if (!child) {
                return NULL;
            }
            return child->SearchBrother(name);
        }

        ElementAny* SearchBrother(std::string ename) {
            if (name == ename) {
                return this;
            }
            ElementAny* ptr = prev;
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

        ElementAny* InsertChild(ElementAny* element) {
            if (!child) {
                child = element;
                child->parent = this;
                return child;
            }
            return child->InsertNext(element);
        }
        ElementAny* InsertNext(ElementAny* element) {
            if (!next) {
                next = element;
                next->prev = this;
                next->parent = parent;
                return next;
            }
            ElementAny* ptr = next;
            while(!ptr->next) {
                ptr = ptr->next;
            }
            ptr->next = element;
            ptr->next->prev = ptr;
            ptr->next->parent = parent;

            return ptr->next;
        }
        ElementAny* InsertPrev(ElementAny* element) {
            if (!prev) {
                prev = element;
                prev->next = this;
                prev->parent = parent;
                return prev;
            }
            ElementAny* ptr = prev;
            while(!ptr->prev) {
                ptr = ptr->prev;
            }
            ptr->prev = element;
            ptr->prev->next = ptr;
            ptr->prev->parent = parent;

            return ptr->prev;
        }

    public:
        std::string name;
        ElementAny* next = nullptr;
        ElementAny* prev = nullptr;
        ElementAny* parent = nullptr;
        ElementAny* child = nullptr;

    };

    template < typename T > class Element : public ElementAny {
    public:
        Element(std::string name, ElementType type = ElementType::Fundamental) : ElementAny(name), element_type_(type) {
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

        template < typename D > Element<D>* Search(std::string path) {
            ElementAny* ptr = SearchPath(path);
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


private:

//    ElementAny root_;
};

} //namespace end

#endif
