/*******************************************************
# Copyright (C) For free.
# All rights reserved.
# ******************************************************
# Author       : Ronghua Gao
# Last modified: 2019-01-21 03:37
# Email        : grh4542681@163.com
# Filename     : link_list.h
# Description  : Bidirectional linear list.
* ******************************************************/
#ifndef __LINK_LIST_H__
#define __LINK_LIST_H__

#include "mempool.h"

namespace ds {

/**
* @brief - Doubly linked list class.
*
* @tparam [T] - Data type.
*/
template <typename T>
class LinkList {
private:
    /**
    * @brief - List node.
    */
    class LinkNode {
    public:
        T* data_;
        LinkNode* prev;
        LinkNode* next;

    public:
        LinkNode(pub::MemPool* mp, T&& data) {
            data_ = mp->Malloc(sizeof(T));
            memset()
        }
        template<typename ... Args>
        LinkNode(pub::MemPool* mp, Args&& ... args) {
        }
        ~LinkNode() {}

        void erase() {
        }
        void swap(T&& newdata) {
        }
    private:
    };

public:
    /**
    * @brief - List iterator.
    */
    class iterator {
    public:
        iterator(LinkNode* node) : ptr(node) {}
        ~iterator() {}

        T& operator*() const { return *(ptr->data_); }
        bool operator!=(const iterator&& other) const { return (ptr != other.ptr); }
        const iterator& operator++() {
            ptr = ptr->next;
            return *this;
        }
    private:
        LinkNode* ptr;
    };

public:
    LinkNode* head;
    LinkNode* tail;

public:
    LinkList() { mempool_ = pub::MemPool::getInstance(); }
    ~LinkList() {}

    iterator begin () const { return iterator(head); }
    iterator end () const { return iterator(tail); }

    void pushback(T& data) {
        LinkNode newnode(std::move(data);
    }

    void pushback(T&& data) {
        LinkNode newnode(data);
    }

    template<typename ... Args>
    void pushback(Args&& ... args) {
        LinkNode newnode(std::forward<Args>(args)...);
    }

    void pushfront(T& data) {
        LinkNode newnode(std::move(data);
    }

    void pushfront(T&& data) {
        LinkNode newnode(data);
    }

    template<typename ... Args>
    void pushfront(Args&& ... args) {
        LinkNode newnode(std::forward<Args>(args)...);
    }

    void pushbefore(iterator& target, T& data) {
        LinkNode newnode(std::move(data);
    }

    void pushbefore(iterator& target, T&& data) {
        LinkNode newnode(data);
    }

    template<typename ... Args>
    void pushbefore(iterator& target, Args&& ... args) {
        LinkNode newnode(std::forward<Args>(args)...);
    }

    void pushafter(iterator& target, T& data) {
        LinkNode newnode(std::move(data);
    }

    void pushafter(iterator& target, T&& data) {
        LinkNode newnode(data);
    }

    template<typename ... Args>
    void pushafter(iterator& target, Args&& ... args) {
        LinkNode newnode(std::forward<Args>(args)...);
    }
private:
    pub::MemPool* mempool_;
};

} //namespace end

#endif
