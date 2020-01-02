#include "parser_tvl.h"

namespace parser {

ParserTvl::ParserTvl() { }
ParserTvl::~ParserTvl()
{
    for (auto it : tvl_vec_) {
        mempool::MemPool::getInstance()->Free(it);
    }
}

ParserRet ParserTvl::LoadString(std::string str)
{

}
ParserRet ParserTvl::LoadFile(file::File& file)
{

}
ParserRet ParserTvl::LoadFile(std::string str)
{

}

ParserRet ParserTvl::StoreString(std::string& str)
{

}
ParserRet ParserTvl::StoreFile(file::File& file)
{

}
ParserRet ParserTvl::StoreFile(std::string str)
{

}

ParserTvl& ParserTvl::PushBack(ParserTvl& other)
{
    tvl_vec_.insert(tvl_vec_.end(), other.tvl_vec_.begin(), other.tvl_vec_.end());
    return *this;
}
ParserTvl& ParserTvl::PushBack(ParserTvlObject& other)
{
    ParserTvlObject* ptr = other.Clone();
    if (!ptr) {
        PARSER_ERROR("Create dynamic ParserTvlObject error.");
        return *this;
    }
    tvl_vec_.push_back(ptr);
    return *this;
}
ParserTvl& ParserTvlPopBack()
{

}

}
