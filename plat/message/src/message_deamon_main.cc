#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>

#include <string>
#include <iostream>
#include <map>

#include "file.h"
#include "file_api.h"
#include "parser_json.h"
#include "parser_yaml.h"
#include "process_main.h"

#include "message_log.h"
#include "message_server.h"

static parser::ParserJson process_config;

int main(int argc, char** argv)
{
    //command line arguments
    std::string process_config_file = "";

    //command line process.
    char short_options[] = ":p:h";
    struct option long_options[] = {
        {"process_config", 1, 0, 'p'},
        {"help", 0, 0, 'h'},
        {0, 0, 0, 0}
    };

    int option_val;
    int option_index = 0;
    while (1) {
        option_index = 0;
        option_val = getopt_long(argc, argv, short_options, long_options, &option_index);
        if (option_val == -1) {
            break;
        }
        switch (option_val) {
            case 0:
                break;
            case 'p':
                process_config_file.assign(optarg);
                break;
            case 'h':
                std::cout << "Useage:" << std::endl;
                exit(0);
            case ':':
                std::cout << "Option [" << argv[optind-1] << "] need arguments" << std::endl;
                std::cout << "Please use [-h or --help] to see usage." << std::endl;
                exit(0);
            case '?':
                std::cout << "Unknow option [" << argv[optind] << "]" << std::endl;
                std::cout << "Please use [-h or --help] to see usage." << std::endl;
                exit(0);
            default:
                break;
        }
    }

    if (optind < argc) {
        std::cout << "Unknow option ";
        while (optind < argc)
            std::cout << "[" << argv[optind++] << "] ";
        std::cout << std::endl;
        std::cout << "Please use [-h or --help] to see usage." << std::endl;
        exit(0);
    }

    process::ProcessMain<decltype(&message::MessageServer::Main)> pmain(process_config_file, message::MessageServer::Main);
    int i = 10;
    std::string str = "test args";
    pmain.Run(argc, argv, i, str);

    return 0;
}
