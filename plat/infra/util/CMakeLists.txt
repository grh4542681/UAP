set(LIBGUTIL_SRC string/string_util.cc
)

add_library(GRHutil_SO SHARED ${LIBGUTIL_SRC})
set_target_properties(GRHutil_SO PROPERTIES OUTPUT_NAME "gutil" CLEAN_DIRECT_OUTPUT 1)

if(BUILD_STATIC_LIBS)
    add_library(GRHutil_A STATIC ${LIBGUTIL_SRC})
    set_target_properties(GRHutil_A PROPERTIES OUTPUT_NAME "gutil" CLEAN_DIRECT_OUTPUT 1)
endif()
