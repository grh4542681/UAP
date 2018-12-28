#include <iostream>
#include <unistd.h>
#include "parser_log.h"
#include "parser_ini.h"

#define PARSERINI_LINE_MAX_LEN (256)

namespace parser {

ParserIni::ParserIni(std::string filename)
{
    this->init_flag_ = false;
    this->filename_ = filename;
    this->mempool_ = pub::MemPool::getInstance();
	if (access(filename.c_str(),F_OK|R_OK)) {
		PARSER_ERROR("File[%s] test error [%s]",this->filename_.c_str() ,strerror(errno));
		return ;
	}
    this->init_flag_ = true;
}

ParserIni::~ParserIni()
{
    if (this->init_flag_) {
        _free();
        this->init_flag_ = false;
    }
}

ParserRet ParserIni::Load()
{
    if (!this->init_flag_) {
        return ParserRet::EINIT;
    } else {
        return _load();
    }
}

ParserRet ParserIni::Reload()
{
    if (!this->init_flag_) {
        return ParserRet::EINIT;
    } else {
        ParserRet ret;
        if ((ret = _free()) != ParserRet::SUCCESS) {
            return ret;
        } else {
            return _load();
        }
    }
}

ParserRet ParserIni::Storage(std::string filename)
{

}

ParserRet ParserIni::Print()
{
    std::map<std::string, Section*>::iterator section_it;
    Section::iterator item_it;
    section_it = this->conftree_.begin();
    while (section_it != this->conftree_.end()) {
        std::cout << "section:[" << section_it->first << "]" << std::endl;
        item_it = section_it->second->begin();
        while (item_it != section_it->second->end()) {
            std::cout << "\tkey[" << item_it->first << "]\tvalue[" << item_it->second << "]" << std::endl;
            item_it++;
        }
        section_it++;
    }
    return ParserRet::SUCCESS;
}

ParserRet ParserIni::Free()
{
    if (!this->init_flag_) {
        return ParserRet::EINIT;
    } else {
        ParserRet ret = _free();
        this->init_flag_ = false;
        return ret;
    }
}

std::string ParserIni::getConfig(std::string section, std::string item)
{
    std::map<std::string, Section*>::iterator section_it;
    Section::iterator item_it;
    section_it = this->conftree_.begin();
    while (section_it != this->conftree_.end()) {
        if (section_it->first.compare(section) == 0) {
            item_it = section_it->second->begin();
            while (item_it != section_it->second->end()) {
                if (item_it->first.compare(item) == 0) {
                    return item_it->second;
                }
                item_it++;
            }
        }
        section_it++;
    }
    std::string s;
    return s;
}

ParserRet ParserIni::setConfig(std::string section, std::string item, std::string value)
{

}

//private
ParserRet ParserIni::_load()
{
	FILE* pfile = fopen(this->filename_.c_str(), "r");
	if(!pfile)
	{
		PARSER_ERROR("File[%s] test error [%s]", this->filename_.c_str(), strerror(errno));
		return ParserRet::ERROR;
	}

    char* ptr_temp = NULL;
    char line[PARSERINI_LINE_MAX_LEN];
	char cursection[PARSERINI_LINE_MAX_LEN];
	char curitemkey[PARSERINI_LINE_MAX_LEN];
	char curitemvalue[PARSERINI_LINE_MAX_LEN];
	memset(line,0x00,sizeof(line));
	memset(cursection,0x00,sizeof(cursection));
	memset(curitemkey,0x00,sizeof(curitemkey));
	memset(curitemvalue,0x00,sizeof(curitemvalue));

    Section* pcursection;

    while (fgets(line, PARSERINI_LINE_MAX_LEN, pfile)) {
        if (strlen(line)==0 || line[0]=='\n' || line[0]=='#')
            continue;
        if (line[0] == '[') {
            //read a section line
            ptr_temp = strchr(line, ']');
            if (!ptr_temp) {
                _free();
                PARSER_ERROR("Not found ] in line[%s]", line);
                return ParserRet::ERROR;
            } else {
                memset(cursection, 0x00, sizeof(cursection));
                memcpy(cursection, line+1, ptr_temp-(line+1));
                pcursection = this->mempool_->Malloc<Section>();
                if (!pcursection) {
                    _free();
                    PARSER_ERROR("Create section map error[%s]", cursection);
                    return ParserRet::ERROR;
                }
                this->conftree_.insert(std::pair<std::string, Section*>(cursection, pcursection));
            }
        } else {
            //read an item line
            if (!pcursection) {
                continue;
            }
            ptr_temp = strchr(line,'=');
            if (!ptr_temp) {
                continue;
            }
            memset(curitemkey, 0x00, sizeof(curitemkey));
            memset(curitemvalue, 0x00, sizeof(curitemvalue));
            memcpy(curitemkey, line, ptr_temp - line);
            memcpy(curitemvalue,ptr_temp + 1, strlen(line) - (ptr_temp - line) - 2);
            pcursection->insert(std::pair<std::string, std::string>(curitemkey, curitemvalue));
        }
    }
    return ParserRet::SUCCESS;
}

ParserRet ParserIni::_free()
{
    std::map<std::string, Section*>::iterator section_it;
    Section::iterator item_it;
    section_it = this->conftree_.begin();
    while (section_it != this->conftree_.end()) {
        this->conftree_.erase(section_it);
        if (section_it->second) {
            this->mempool_->Free(section_it->second);
        }
        section_it++;
    }
    return ParserRet::SUCCESS;
}

}//namespace parser end





/*

INISEC* LoadINI(char* filepath)
{
	if(access(filepath,F_OK|R_OK))
	{
		SYSLOG(ERROR,"File[%s] test error [%s]",filepath,strerror(errno));
		return NULL;
	}

	FILE* pfile = fopen(filepath,"r");
	if(!pfile)
	{
		SYSLOG(ERROR,"File[%s] test error [%s]",filepath,strerror(errno));
		return NULL;
	}
	
	INISEC* INIhead = NULL;
	INISEC* INIcurr = NULL;
	char* ptmp1 = NULL;

	char line[INI_MAXLINE];
	char cursection[INI_MAXLINE];
	char curitemkey[INI_MAXLINE];
	char curitemvalue[INI_MAXLINE];
	memset(line,0x00,sizeof(line));
	memset(cursection,0x00,sizeof(cursection));
	memset(curitemkey,0x00,sizeof(curitemkey));
	memset(curitemvalue,0x00,sizeof(curitemvalue));

	while(fgets(line,INI_MAXLINE,pfile))
	{
		if(strlen(line)==0 || line[0]=='\n' || line[0]=='#')
			continue;
		if(line[0]=='[')
		{
			ptmp1 = strchr(line,']');
			if(!ptmp1)
			{
				SYSLOG(ERROR,"Match'[]' error on line:[%s]",line);
				SectionDestroy(&INIhead);
				return NULL;
			}
			else
			{
				// get section
				memset(cursection,0x00,sizeof(cursection));
				memcpy(cursection,line+1,ptmp1-line-1);
				INIcurr = SectionADD(&INIhead,cursection);
				if(!INIhead)
				{
					INIhead = INIcurr;
				}
			}
		}
		else
		{
			if(!INIcurr)
				continue;
			else
			{
				ptmp1 = strchr(line,'=');
				if(!ptmp1)
				{
					SYSLOG(ERROR,"Search '=' error on line:[%s]",line);
					SectionDestroy(&INIhead);
					return NULL;
				}
				else
				{
					// get item
					memset(curitemkey,0x00,sizeof(curitemkey));
					memset(curitemvalue,0x00,sizeof(curitemvalue));
					memcpy(curitemkey,line,ptmp1-line);
					memcpy(curitemvalue,ptmp1+1,strlen(line)-strlen(curitemkey)-1-1);
					SectionItemADD(INIcurr,curitemkey,curitemvalue);	
				}
			}
		}
		
	}
	return INIhead;
}


INISEC* GetSection(INISEC* Sectionhead,char* Section)
{
	return GetSectionByName(Sectionhead,Section);
}

INIITEM* GetSectionItem(INISEC* Sectionhead,char* Section,char* Item)
{
	INISEC* section = GetSectionByName(Sectionhead,Section);
	if(!section)
	{
		SYSLOG(ERROR,"Con't find section [%s]",Section);
		return NULL;
	}
	else
	{
		return GetItemByKey(section->child,Item);
	}
}

void FreeINI(INISEC* Sectionhead)
{
	SectionDestroy(&Sectionhead);
}
*/
