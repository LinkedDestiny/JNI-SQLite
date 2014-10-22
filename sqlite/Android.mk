LOCAL_PATH:= $(call my-dir)  
include $(CLEAR_VARS)  

LOCAL_MODULE:= libsqlite3  

LOCAL_SRC_FILES:= sqlite3secure.c

include $(BUILD_STATIC_LIBRARY)  