SET(LIBGRHRM_SRC resource_manager.cc)
add_library(GRHrm_SO SHARED ${LIBGRHRM_SRC})
add_library(GRHrm_A STATIC ${LIBGRHRM_SRC})
target_link_libraries(GRHrm_SO pthread)
target_link_libraries(GRHrm_A pthread)
set_target_properties(GRHrm_SO PROPERTIES OUTPUT_NAME "grm" CLEAN_DIRECT_OUTPUT 1)
set_target_properties(GRHrm_A PROPERTIES OUTPUT_NAME "grm" CLEAN_DIRECT_OUTPUT 1)
