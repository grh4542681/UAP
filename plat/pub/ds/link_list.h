#ifndef __LINK_LIST_H__
#define __LINK_LIST_H__

namespace ds {

template <typename T>
class LinkList {
private:
    class LinkNode {
    public:
        T* data_;
        LinkNode* prev;
        LinkNode* next;

    public:
        LinkNode(T&& data) {
        }
        template<typename ... Args>
        LinkNode(Args&& ... args) {
        }
        ~LinkNode() {}

        void erase() {
        }
        void swap(T&& newdata) {
        }
    private:
        //pub::MemPool* mempool_;
    };

public:
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
    LinkList() {}
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
};

} //namespace end

#endif