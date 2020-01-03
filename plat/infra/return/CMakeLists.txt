SET(LIBGRET_SRC return.cc
)

add_library(GRHret_SO SHARED ${LIBGRET_SRC})
set_target_properties(GRHret_SO PROPERTIES OUTPUT_NAME "gret" CLEAN_DIRECT_OUTPUT 1)

if(BUILD_STATIC_LIBS)
    add_library(GRHret_A STATIC ${LIBGRET_SRC})
    set_target_properties(GRHret_A PROPERTIES OUTPUT_NAME "gret" CLEAN_DIRECT_OUTPUT 1)
endif()
