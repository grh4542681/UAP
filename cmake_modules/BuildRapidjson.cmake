message("Build rapidjson 3pp")

include(ExternalProject)

set(RAPIDJSON_DIR ${FRAM_3PP_PATH}/rapidjson)
set(3PP_RAPIDJSON_HRD "${RAPIDJSON_DIR}/include") 

message("Build ymal-cpp 3pp done.")
