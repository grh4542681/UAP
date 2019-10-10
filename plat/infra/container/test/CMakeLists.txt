SET(EXECUTABLE_OUTPUT_PATH ${FRAM_BIN_PATH}/test)

SET(BITMAP_TEST_SRC bitmap_test.cc)
SET(TEST_LINK_LIST_SRC test_link_list.cc)
SET(TEST_HASH_TABLE_SRC test_hash_table.cc)
SET(TEST_TRIE_TREE_SRC test_trie_tree.cc)

ADD_EXECUTABLE(bitmap_test ${BITMAP_TEST_SRC})
ADD_EXECUTABLE(test_link_list ${TEST_LINK_LIST_SRC})
ADD_EXECUTABLE(test_hash_table ${TEST_HASH_TABLE_SRC})
ADD_EXECUTABLE(test_trie_tree ${TEST_TRIE_TREE_SRC})

TARGET_LINK_LIBRARIES(bitmap_test libgcontainer.so librt.so libgmp.so libgret.so libgfile.so libgutil.so)
TARGET_LINK_LIBRARIES(test_link_list libgmp.so pthread libgthread.so libgprocess.so libgipc.so libgsocket.so libgfile.so libgutil.so libgret.so libgmsg.so libgio.so libgtime.so)
TARGET_LINK_LIBRARIES(test_hash_table libgmp.so pthread libgthread.so libgprocess.so libgipc.so libgsocket.so libgfile.so libgutil.so libgret.so libgmsg.so libgio.so libgtime.so)
TARGET_LINK_LIBRARIES(test_trie_tree libgmp.so pthread libgthread.so libgprocess.so libgipc.so libgsocket.so libgfile.so libgutil.so libgret.so libgmsg.so libgio.so libgtime.so)
