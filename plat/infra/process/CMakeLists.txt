SET(LIBGPROCESS_SRC process_return.cc
                    process_info.cc
                    process.cc
                    process_role.cc
                    process_id.cc
                    process_parent.cc
                    process_child.cc
                    process_config.cc
                    signal/process_signal.cc
                    signal/process_signal_ctrl.cc
                    signal/process_signal_set.cc
                    signal/process_signal_action.cc
                    pool/process_pool_worker.cc
                    )
ADD_LIBRARY(GRHprocess_SO SHARED ${LIBGPROCESS_SRC})
ADD_LIBRARY(GRHprocess_A STATIC ${LIBGPROCESS_SRC})
SET_TARGET_PROPERTIES(GRHprocess_SO PROPERTIES OUTPUT_NAME "gprocess" CLEAN_DIRECT_OUTPUT 1)
SET_TARGET_PROPERTIES(GRHprocess_A PROPERTIES OUTPUT_NAME "gprocess" CLEAN_DIRECT_OUTPUT 1)
