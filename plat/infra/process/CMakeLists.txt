SET(LIBGPROCESS_SRC process_info.cc
                    process.cc
                    process_role.cc
                    signal/process_signal.cc
                    signal/process_signal_ctrl.cc
                    signal/process_signal_set.cc
                    signal/process_signal_action.cc
                    )
ADD_LIBRARY(GRHprocess_SO SHARED ${LIBGPROCESS_SRC})
ADD_LIBRARY(GRHprocess_A STATIC ${LIBGPROCESS_SRC})
TARGET_LINK_LIBRARIES(GRHprocess_SO pthread libgthread.so)
TARGET_LINK_LIBRARIES(GRHprocess_A pthread libgthread.so)
SET_TARGET_PROPERTIES(GRHprocess_SO PROPERTIES OUTPUT_NAME "gprocess" CLEAN_DIRECT_OUTPUT 1)
SET_TARGET_PROPERTIES(GRHprocess_A PROPERTIES OUTPUT_NAME "gprocess" CLEAN_DIRECT_OUTPUT 1)
