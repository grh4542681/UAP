cmake_minimum_required(VERSION 2.8)

PROJECT(UAP)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules)

SET(FRAM_ROOT_PATH ${CMAKE_SOURCE_DIR})
SET(FRAM_LIB_PATH ${FRAM_ROOT_PATH}/lib)
SET(FRAM_BIN_PATH ${FRAM_ROOT_PATH}/bin)
SET(FRAM_3PP_PATH ${FRAM_ROOT_PATH}/plat/3pp)

SET(LIBRARY_OUTPUT_PATH ${FRAM_LIB_PATH})
SET(EXECUTABLE_OUTPUT_PATH ${FRAM_BIN_PATH})

SET(CMAKE_C_COMPILER "/home/ezgaoro/workspace/gcc-8.2/bin/gcc")
SET(CMAKE_CXX_COMPILER "/home/ezgaoro/workspace/gcc-8.2/bin/g++")

include(BuildYaml)

LINK_DIRECTORIES(${LIBRARY_OUTPUT_PATH})
SET(COMPILE_WARNINGS "-Wall")
SET(COMPILE_OPTIMIZATION "-Wl,--as-needed -O2")
SET(COMPILE_DEBUG "-g -ggdb")

SET(C_COMPILE_FLAGS "")
SET(CXX_COMPILE_FLAGS "-std=c++17 ${COMPILE_WARNINGS} ${COMPILE_OPTIMIZATION} ${COMPILE_DEBUG}")

SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${C_COMPILE_FLAGS}")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CXX_COMPILE_FLAGS}")

SET (PLAT_HRD "${FRAM_ROOT_PATH}/plat/message"
              )

SET (PLAT_INFRA_HRD "${FRAM_ROOT_PATH}/plat/infra/ds/cpp"
                    "${FRAM_ROOT_PATH}/plat/infra/return"
                    "${FRAM_ROOT_PATH}/plat/infra/timer"
                    "${FRAM_ROOT_PATH}/plat/infra/mempool"
                    "${FRAM_ROOT_PATH}/plat/infra/container"
                    "${FRAM_ROOT_PATH}/plat/infra/thread"
                    "${FRAM_ROOT_PATH}/plat/infra/process"
                    "${FRAM_ROOT_PATH}/plat/infra/file"
                    "${FRAM_ROOT_PATH}/plat/infra/socket"
                    "${FRAM_ROOT_PATH}/plat/infra/report"
                    "${FRAM_ROOT_PATH}/plat/infra/parser"
                    "${FRAM_ROOT_PATH}/plat/infra/ipc"
                    "${FRAM_ROOT_PATH}/plat/infra/util"
                    "${FRAM_ROOT_PATH}/plat/infra/io"
                    )

SET (PLAT_CONFIG_HRD "${FRAM_ROOT_PATH}/plat/config"
                     "${FRAM_ROOT_PATH}/plat/config/lib"
)

SET (PLAT_MESSAGE_HRD "${FRAM_ROOT_PATH}/plat/common"
                      "${FRAM_ROOT_PATH}/plat/message"
                      "${FRAM_ROOT_PATH}/plat/message/lib"
                      "${FRAM_ROOT_PATH}/plat/nameserver"
                      "${FRAM_ROOT_PATH}/plat/nameserver/lib"
                      )

SET (PLAT_NS_HRD "${FRAM_ROOT_PATH}/plat/nameserver"
                 "${FRAM_ROOT_PATH}/plat/nameserver/lib"
                 )

SET (COMMON_OS_LIB librt.so
                   libpthread.so
                   libm.so
                   )

SET (PLAT_LIB libgmsg.so
              )
SET (PLAT_INFRA_LIB libgret.so
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

INCLUDE_DIRECTORIES("${FRAM_3PP_PATH}/rapidjson/include")
INCLUDE_DIRECTORIES("${FRAM_3PP_PATH}/yaml-cpp/include")
INCLUDE_DIRECTORIES(${PLAT_INFRA_HRD})
INCLUDE_DIRECTORIES(${PLAT_MESSAGE_HRD})
INCLUDE_DIRECTORIES(${PLAT_CONFIG_HRD})

ADD_SUBDIRECTORY(plat)
