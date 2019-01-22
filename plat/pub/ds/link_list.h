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
        LinkList* list;
        T* data_;
        LinkNode* prev;
        LinkNode* next;

    public:
        LinkNode(LinkList* mlist, T&& data) : list(mlist) {
            data_ = NULL;
            prev = NULL;
            next = NULL;
            data_ = list->mp->Malloc<T>(data);
        }

        template<typename ... Args>
        LinkNode(LinkList* mlist, Args&& ... args) : list(mlist) {
            data_ = NULL;
            prev = NULL;
            next = NULL;
            data_ = list->mp->Malloc<T>(std::forward<Args>(args)...);
        }

        ~LinkNode() {
            if (data_) {
                erase();
            }
        }

        void erase() {
            if (prev && next) {
                prev->next = next;
                next->prev = prev;
            } else if (prev) {
                prev->next = next;
                list->tail = prev;
            } else if (next) {
                next->prev = prev
                list->head = next;
            } else {
                list->tail = prev;
                list->head = next;
            }
            prev = NULL;
            next = NULL;
            list->mp->Free<T>(data_);
            --(list->count);
        }

        void reset(T&& newdata) {
            list->mp->Reset<T>(newdata);
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

        void erase() {
            ptr->erase();
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

public:
    LinkList() {
        count = 0;
        mp = pub::MemPool::getInstance();
    }
    ~LinkList() {}

    iterator begin () const { return iterator(head); }
    iterator end () const { return iterator(tail); }

    unsigned int size() { return count; }

    void pushback(T& data) {
        LinkNode* ptr = mp->Malloc<LinkNode>(this, std::move(data));
        _push_after(tail, ptr);
    }

    void pushback(T&& data) {
        LinkNode* ptr = mp->Malloc<LinkNode>(this, data);
        _push_after(tail, ptr);
    }

    template<typename ... Args>
    void pushback(Args&& ... args) {
        LinkNode* ptr = mp->Malloc<LinkNode>(this, std::forward<Args>(args)...);
        _push_after(tail, ptr);
    }

    void pushfront(T& data) {
        LinkNode* ptr = mp->Malloc<LinkNode>(this, std::move(data));
        _push_before(head, ptr);
    }

    void pushfront(T&& data) {
        LinkNode* ptr = mp->Malloc<LinkNode>(this, data);
        _push_before(head, ptr);
    }

    template<typename ... Args>
    void pushfront(Args&& ... args) {
        LinkNode* ptr = mp->Malloc<LinkNode>(this, std::forward<Args>(args)...);
        _push_before(head, ptr);
    }

    void pushbefore(iterator& target, T& data) {
        LinkNode* ptr = mp->Malloc<LinkNode>(this, std::move(data));
        _push_before(target.ptr, ptr);
    }

    void pushbefore(iterator& target, T&& data) {
        LinkNode* ptr = mp->Malloc<LinkNode>(this, data);
        _push_before(target.ptr, ptr);
    }

    template<typename ... Args>
    void pushbefore(iterator& target, Args&& ... args) {
        LinkNode* ptr = mp->Malloc<LinkNode>(this, std::forward<Args>(args)...);
        _push_before(target.ptr, ptr);
    }

    void pushafter(iterator& target, T& data) {
        LinkNode* ptr = mp->Malloc<LinkNode>(this, std::move(data));
        _push_after(target.ptr, ptr);
    }

    void pushafter(iterator& target, T&& data) {
        LinkNode* ptr = mp->Malloc<LinkNode>(this, data);
        _push_after(target.ptr, ptr);
    }

    template<typename ... Args>
    void pushafter(iterator& target, Args&& ... args) {
        LinkNode* ptr = mp->Malloc<LinkNode>(this, std::forward<Args>(args)...);
        _push_after(target.ptr, ptr);
    }
private:
    unsigned int count;
    pub::MemPool* mp;

    void _push_before(ListNode* currnode, ListNode* newnode) {
        if (!currnode) {
            head = tail = newnode;
            newnode->prev = NULL;
            newnode->next = NULL;
        } else {
            currnode->prev->next = newnode;
            newnode->prev = currnode->prev;
            currnode->prev = newnode;
            newnode->next = currnode;
            if (!(newnode->prev))
                head = newnode;
        }
        ++count;
    }

    void _push_after(ListNode* currnode, ListNode* newnode) {
        if (!currnode) {
            head = tail = newnode;
            newnode->prev = NULL;
            newnode->next = NULL;
        } else {
            currnode->next->prev = newnode;
            newnode->next = currnode->next;
            currnode->next = newnode;
            newnode->prev = currnode;
            if (!(newnode->next))
                tail = newnode;
        }
        ++count;
    }
};

} //namespace end

#endif
