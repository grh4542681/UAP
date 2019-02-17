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

#ifndef CASE_SENSITIVE
    #define TT_DICT_NUM (26*2+10)
/*
 *     'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
 *     'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
 *     '0','1','2','3','4','5','6','7','8','9'
 */
#else
    #define TT_DICT_NUM (26+10)
/*
 *     'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
 *     '0','1','2','3','4','5','6','7','8','9'
 */
#endif

namespace ds{

template < typename T >
class TrieTree {
public:
    enum class DictConfig : unsigned int {
        All = 0xFFFFFFFF,
        Capital = 1 << 1,
        Number = 1 << 2,
        Punctuation = 1 << 3,
        SpecialSymbol = 1 << 4,
    };

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
        return dictflag & DictConfig::Capital;
    }
    static bool isSupportNumber(unsigned int dictflag) {
        return dictflag & DictConfig::Number;
    }
    static bool isSupportPunctuation(unsigned int dictflag) {
        return dictflag & DictConfig::Punctuation;
    }
    static bool isSupportSpecialSymbol(unsigned int dictflag) {
        return dictflag & DictConfig::SpecialSymbold;
    }

private:
    unsigned int count;
    pub::MemPool* mp;
    TTNode* slots_[TT_DICT_NUM];
};

}// namespace end

#endif
