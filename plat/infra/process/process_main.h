#ifndef __PROCESS_MAIN_H__
#define __PROCESS_MAIN_H__

#include <utility>

#include "file.h"
#include "message_agent.h"

#include "process_log.h"
#include "process_return.h"
#include "process_info.h"
#include "pool/specific_pool.h"

namespace process {

template < typename F >
class ProcessMain {
public:
    ProcessMain(std::string filename, F main) {
        config_filename_ = filename;
        main_ = main;
    }
    ~ProcessMain() { }

    template <typename ... Args>
    ProcessRet Run(int argc, char** argv, Args&& ... args) {
        ProcessRet ret;
        ProcessInfo::getInstance()->SetCmdLine(argc, argv, environ);
        if ((ret = _load_config()) != ProcessRet::SUCCESS) {
            PROCESS_FATAL("Load process config file [%s] error", config_filename_.c_str());
            return ret;
        }
        pool::SpecificPool<F, Args&& ...> pool_(process::ProcessInfo::getInstance()->GetRealName(), main_, std::forward<Args>(args)...);
        pool_.Run();
        message::MessageAgent::getInstance()->Run();
        sleep(20);
//        main_(std::forward<Args>(args)...);
        return ProcessRet::SUCCESS;
    }

private:
    F main_;
    std::string config_filename_;

    ProcessRet _load_config() {
        process::ProcessInfo* process_info = process::ProcessInfo::getInstance();

        if (config_filename_.empty() || !file::IsExist(config_filename_)) {
            PROCESS_FATAL("Con't access process config file [%s].", config_filename_.c_str());
            return ProcessRet::PROCESS_ECONFIG;
        }

        file::File config_file(config_filename_);
        switch(config_file.GetFileFormat()) {
            case file::File::Format::Json:
                process_info->GetConfig().Load<parser::ParserJson>(config_file);
                break;
            case file::File::Format::Yaml:
                process_info->GetConfig().Load<parser::ParserYaml>(config_file);
                break;
            default:
                PROCESS_FATAL("Not support config file format [%s]", file::GetFileExtension(config_filename_).c_str());
                return ProcessRet::PROCESS_ECONFIG;
        }

        return ProcessRet::SUCCESS;
    }
};

}

#endif
