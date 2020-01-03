cmake_minimum_required(VERSION 3.16)

project(UAP)

option(BUILD_STATIC_LIBS "Build static Libraries" OFF)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules)

set(FRAM_ROOT_PATH ${CMAKE_SOURCE_DIR})
set(FRAM_LIB_PATH "${FRAM_ROOT_PATH}/lib")
set(FRAM_BIN_PATH "${FRAM_ROOT_PATH}/bin")
set(FRAM_3PP_PATH "${FRAM_ROOT_PATH}/plat/3pp")
set(FRAM_PLAT_PATH "${FRAM_ROOT_PATH}/plat")
set(PLAT_INFRA_PATH "${FRAM_PLAT_PATH}/infra")

set(CMAKE ${FRAM_ROOT_PATH}/tools/cmake/cmake-3.16.0-Linux-x86_64/bin/cmake)

set(LIBRARY_OUTPUT_PATH ${FRAM_LIB_PATH})
set(EXECUTABLE_OUTPUT_PATH ${FRAM_BIN_PATH})

set(CMAKE_C_COMPILER "/home/ezgaoro/workspace/gcc-8.2/bin/gcc")
set(CMAKE_CXX_COMPILER "/home/ezgaoro/workspace/gcc-8.2/bin/g++")

include(BuildRapidjson)
include(BuildProtobuf)
include(BuildYaml)

link_directories(${LIBRARY_OUTPUT_PATH})
set(COMPILE_WARNINGS "-Wall")
set(COMPILE_OPTIMIZATION "-Wl,--as-needed -O2")
set(COMPILE_DEBUG "-g -ggdb")

set(C_COMPILE_FLAGS "")
set(CXX_COMPILE_FLAGS "-std=c++17 ${COMPILE_WARNINGS} ${COMPILE_OPTIMIZATION} ${COMPILE_DEBUG}")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${C_COMPILE_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CXX_COMPILE_FLAGS}")

set (PLAT_HRD "${FRAM_ROOT_PATH}/plat/message"
              )
set (PLAT_INFRA_HRD "${FRAM_PLAT_PATH}/ds/cpp"
                    "${FRAM_PLAT_PATH}/return"
                    "${FRAM_PLAT_PATH}/timer"
                    "${FRAM_PLAT_PATH}/mempool"
                    "${FRAM_PLAT_PATH}/container"
                    "${FRAM_PLAT_PATH}/thread"
                    "${FRAM_PLAT_PATH}/process"
                    "${FRAM_PLAT_PATH}/file"
                    "${FRAM_PLAT_PATH}/socket"
                    "${FRAM_PLAT_PATH}/report"
                    "${FRAM_PLAT_PATH}/parser"
                    "${FRAM_PLAT_PATH}/ipc"
                    "${FRAM_PLAT_PATH}/util"
                    "${FRAM_PLAT_PATH}/io"
                    )

set (PLAT_CONFIG_HRD "${FRAM_ROOT_PATH}/plat/config"
                     "${FRAM_ROOT_PATH}/plat/config/lib"
)

set (PLAT_MESSAGE_HRD "${FRAM_ROOT_PATH}/plat/common"
                      "${FRAM_ROOT_PATH}/plat/message"
                      "${FRAM_ROOT_PATH}/plat/message/lib"
                      "${FRAM_ROOT_PATH}/plat/nameserver"
                      "${FRAM_ROOT_PATH}/plat/nameserver/lib"
                      )

set (PLAT_NS_HRD "${FRAM_ROOT_PATH}/plat/nameserver"
                 "${FRAM_ROOT_PATH}/plat/nameserver/lib"
                 )

set (COMMON_OS_LIB librt.so
                   libpthread.so
                   libm.so
                   )

set (PLAT_LIB libgmsg.so
              )
set (PLAT_INFRA_LIB libgret.so
                    libgtime.so
                    libgipc.so
                    libgret.so
                    libgmp.so
                    libgcontainer.so
                    libgparser.so
                    libgthread.so
                    libgprocess.so
                    libgfile.so
                    libgsocket.so
                    libgutil.so
                    )

#INCLUDE_DIRECTORIES("${FRAM_3PP_PATH}/rapidjson/include")
#INCLUDE_DIRECTORIES("${FRAM_3PP_PATH}/yaml-cpp/include")
#INCLUDE_DIRECTORIES(${PLAT_INFRA_HRD})
#INCLUDE_DIRECTORIES(${PLAT_MESSAGE_HRD})
#INCLUDE_DIRECTORIES(${PLAT_CONFIG_HRD})

ADD_SUBDIRECTORY(plat)
