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

#include <type_traits>
#include <iterator>
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
        LinkNode(T* data) {
            data_ = NULL;
            prev = NULL;
            next = NULL;
            data_ = data;
        }

        ~LinkNode() {
        }

        void reset(T&& newdata) {
        }
    private:
    };

public:
    /**
    * @brief - List iterator.
    */
    class iterator : public std::iterator<std::input_iterator_tag, LinkNode> {
    public:
        friend class LinkList;
        iterator(LinkNode* node = NULL) : ptr(node) {}
        iterator(const iterator& other) : ptr(other.ptr) { }
        ~iterator() {}

        T& operator*() { return *(ptr->data_); }
        bool operator!=(const iterator& other) const { return (ptr != other.ptr); }
        bool operator==(const iterator& other) const { return (ptr == other.ptr); }
        const iterator& operator--() {
            ptr = ptr->prev;
            return *this;
        }
        const iterator operator--(int) {
            iterator tmp = *this;
            ptr = ptr->prev;
            return tmp;
        }
        const iterator& operator++() {
            ptr = ptr->next;
            return *this;
        }
        const iterator operator++(int) {
            iterator tmp = *this;
            ptr = ptr->next;
            return tmp;
        }

        void reset(T&& newdata) {
            ptr->reset(newdata);
        }
    private:
        LinkNode* ptr;
    };

public:
    LinkNode* head;
    LinkNode* tail;

    LinkList() {
        head = NULL;
        tail = NULL;
        count = 0;
        mp = pub::MemPool::getInstance();
    }
    ~LinkList() {
        clear();
    }

    iterator begin () const { return iterator(head); }
    iterator end () const { return iterator(NULL); }

    unsigned int size() { return count; }

    void pushback(T& data) {
        pushback(std::move(data));
    }

    void pushback(T&& data) {
        void* ptr = mp->Malloc(sizeof(LinkList) + sizeof(T));
        T* pdata = pub::MemPool::Construct<T>(ptr, data);
        LinkNode* pnode = pub::MemPool::Construct<LinkNode>(reinterpret_cast<char*>(ptr) + sizeof(T), pdata);
        _push_after(tail, pnode);
    }

    template<typename ... Args>
    void pushback(Args&& ... args) {
        void* ptr = mp->Malloc(sizeof(LinkList) + sizeof(T));
        T* pdata = pub::MemPool::Construct<T>(ptr, std::forward<Args>(args)...);
        LinkNode* pnode = pub::MemPool::Construct<LinkNode>(reinterpret_cast<char*>(ptr) + sizeof(T), pdata);
        _push_after(tail, pnode);
    }

    void pushfront(T& data) {
        pushfront(std::move(data));
    }

    void pushfront(T&& data) {
        void* ptr = mp->Malloc(sizeof(LinkList) + sizeof(T));
        T* pdata = pub::MemPool::Construct<T>(ptr, data);
        LinkNode* pnode = pub::MemPool::Construct<LinkNode>(reinterpret_cast<char*>(ptr) + sizeof(T), pdata);
        _push_before(head, pnode);
    }

    template<typename ... Args>
    void pushfront(Args&& ... args) {
        void* ptr = mp->Malloc(sizeof(LinkList) + sizeof(T));
        T* pdata = pub::MemPool::Construct<T>(ptr, std::forward<Args>(args)...);
        LinkNode* pnode = pub::MemPool::Construct<LinkNode>(reinterpret_cast<char*>(ptr) + sizeof(T), pdata);
        _push_before(head, pnode);
    }

    void pushbefore(iterator& target, T& data) {
        pushbefore(std::move(data));
    }

    void pushbefore(iterator& target, T&& data) {
        void* ptr = mp->Malloc(sizeof(LinkList) + sizeof(T));
        T* pdata = pub::MemPool::Construct<T>(ptr, data);
        LinkNode* pnode = pub::MemPool::Construct<LinkNode>(reinterpret_cast<char*>(ptr) + sizeof(T), pdata);
        _push_before(target.ptr, pnode);
    }

    template<typename ... Args>
    void pushbefore(iterator& target, Args&& ... args) {
        void* ptr = mp->Malloc(sizeof(LinkList) + sizeof(T));
        T* pdata = pub::MemPool::Construct<T>(ptr, std::forward<Args>(args)...);
        LinkNode* pnode = pub::MemPool::Construct<LinkNode>(reinterpret_cast<char*>(ptr) + sizeof(T), pdata);
        _push_before(target.ptr, pnode);
    }

    void pushafter(iterator& target, T& data) {
        pushafter(std::move(data));
    }

    void pushafter(iterator& target, T&& data) {
        void* ptr = mp->Malloc(sizeof(LinkList) + sizeof(T));
        T* pdata = pub::MemPool::Construct<T>(ptr, data);
        LinkNode* pnode = pub::MemPool::Construct<LinkNode>(reinterpret_cast<char*>(ptr) + sizeof(T), pdata);
        _push_after(target.ptr, pnode);
    }

    template<typename ... Args>
    void pushafter(iterator& target, Args&& ... args) {
        void* ptr = mp->Malloc(sizeof(LinkList) + sizeof(T));
        T* pdata = pub::MemPool::Construct<T>(ptr, std::forward<Args>(args)...);
        LinkNode* pnode = pub::MemPool::Construct<LinkNode>(reinterpret_cast<char*>(ptr) + sizeof(T), pdata);
        _push_after(target.ptr, pnode);
    }

    void pop(iterator& target) {
        LinkNode* pnode = _pop(target.ptr);
        if (pnode) {
            mp->Destruct<T>(pnode->data_);
            mp->Destruct<LinkNode>(pnode);
            mp->Free((void*)(pnode->data_));
        }
    }

    void popfront() {
        LinkNode* pnode = _pop(head);
        if (pnode) {
            mp->Destruct<T>(pnode->data_);
            mp->Destruct<LinkNode>(pnode);
            mp->Free((void*)(pnode->data_));
        }
    }

    void popback() {
        LinkNode* pnode = _pop(tail);
        if (pnode) {
            mp->Destruct<T>(pnode->data_);
            mp->Destruct<LinkNode>(pnode);
            mp->Free((void*)(pnode->data_));
        }
    }

    void clear() {
        while (head) {
            popfront();
        }
    }
private:
    unsigned int count;
    pub::MemPool* mp;

    void _push_before(LinkNode* currnode, LinkNode* newnode) {
        if (!newnode) {
            return;
        }
        if (!currnode) {
            head = tail = newnode;
            newnode->prev = NULL;
            newnode->next = NULL;
        } else {
            if (!(currnode->prev)) {
                newnode->prev = currnode->prev;
                newnode->next = currnode;
                currnode->prev = newnode;
                head = newnode;
            } else {
                currnode->prev->next = newnode;
                newnode->prev = currnode->prev;
                currnode->prev = newnode;
                newnode->next = currnode;
            }
        }
        ++count;
    }

    void _push_after(LinkNode* currnode, LinkNode* newnode) {
        if (!newnode) {
            return;
        }
        if (!currnode) {
            head = tail = newnode;
            newnode->prev = NULL;
            newnode->next = NULL;
        } else {
            if (!(currnode->next)) {
                newnode->next = currnode->next;
                newnode->prev = currnode;
                currnode->next = newnode;
                tail = newnode;
            } else {
                currnode->next->prev = newnode;
                newnode->next = currnode->next;
                currnode->next = newnode;
                newnode->prev = currnode;
            }
        }
        ++count;
    }

    LinkNode* _pop(LinkNode* node) {
        if (!node) {
            return NULL;
        }
        if (node->next && node->prev) {
            node->prev->next = node->next;
            node->next->prev = node->prev;
        } else if (node->next) {
            node->next->prev = node->prev;
            head = node->next;
        } else if (node->prev) {
            node->prev->next = node->next;
            tail = node->prev;
        } else {
            head = NULL;
            tail = NULL;
        }
        --count;
        return node;
    }
};

} //namespace end

#endif
