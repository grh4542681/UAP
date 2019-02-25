/*******************************************************
# Copyright (C) For free.
# All rights reserved.
# ******************************************************
# Author       : Ronghua Gao
# Last modified: 2019-02-04 07:14
# Email        : grh4542681@163.com
# Filename     : trie_tree.h
# Description  : Tire tree data struct.
* ******************************************************/
#ifndef __TRIE_TREE_H__
#define __TRIE_TREE_H__

#include "mempool.h"

namespace ds{

#define TT_DICT_BASE_NUM (26) 
/*  'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z' */
#define TT_DICT_CAPITAL_NUM (26)
/*  'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z' */
#define TT_DICT_NUMBER_NUM (10)
/*  '0','1','2','3','4','5','6','7','8','9' */
#define TT_DICT_PUNCTUATESYMBOLS_NUM (13)
/*  ()[]{};:'",.? */
#define TT_DICT_MATHSYMBOLS_NUM (13)
/*  !~|&^+-*%/=<> */
#define TT_DICT_SPECIALSYMBOLS_NUM (6)
/*  @#$`\_ */

enum class TrieTreeDict : unsigned int {
    All = 0xFFFFFFFF,
    Capital = 1 << 1,
    Number = 1 << 2,
    PubctuateSymbols = 1 << 3,
    MathSymbols = 1 << 4,
    SpecialSymbols = 1 << 5,
};
unsigned int operator&(TrieTreeDict t1, TrieTreeDict t2) {
    return static_cast<unsigned int>(t1) & static_cast<unsigned int>(t2);
}
unsigned int operator&(TrieTreeDict t1, unsigned int t2) {
    return static_cast<unsigned int>(t1) & t2;
}
unsigned int operator&(unsigned int t1, TrieTreeDict t2) {
    return t1 & static_cast<unsigned int>(t2);
}
unsigned int operator|(TrieTreeDict t1, TrieTreeDict t2) {
    return static_cast<unsigned int>(t1) | static_cast<unsigned int>(t2);
}
unsigned int operator|(TrieTreeDict t1, unsigned int t2) {
    return static_cast<unsigned int>(t1) | t2;
}
unsigned int operator|(unsigned int t1, TrieTreeDict t2) {
    return t1 | static_cast<unsigned int>(t2);
}

template < typename T >
class TrieTree {
public:
    class TTNode {
    public:
        TTNode() {

        }
        ~TTNode() {

        }
    private:
        unsigned int level_;
        unsigned int offset_;
        T* data_;
        TTNode* parent_;
        TTNode* slots_[TT_DICT_NUM];
    };

public:
    TrieTree(unsigned int dictflag) {
        
    }
    ~TrieTree() {

    }

    static bool isSupportCapital(unsigned int dictflag) {
        return dictflag & (unsigned int)TrieTreeDict::Capital;
    }
    static bool isSupportNumber(unsigned int dictflag) {
        return dictflag & TrieTreeDict::Number;
    }
    static bool isSupportPunctuateSymbols(unsigned int dictflag) {
        return dictflag & TrieTreeDict::PubctuateSymbols;
    }
    static bool isSupportMathSymbols(unsigned int dictflag) {
        return dictflag & TrieTreeDict::MathSymbols;
    }
    static bool isSupportSpecialSymbols(unsigned int dictflag) {
        return dictflag & TrieTreeDict::SpecialSymbols;
    }

private:
    pub::MemPool* mp;
    unsigned int slots_size;


    unsigned int count;
    TTNode* slots_[TT_DICT_NUM];

};

}// namespace end

#endif
