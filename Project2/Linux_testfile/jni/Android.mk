LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_SRC_FILES := test_file_NORMAL.c	# your source code
LOCAL_MODULE := test_file_NORMAL	# output file name
LOCAL_CFLAGS += -pie -fPIE	# These two line mustn’t be
LOCAL_LDFLAGS += -pie -fPIE	# change.
LOCAL_FORCE_STATIC_EXECUTABLE := true

include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES := test_file_FIFO.c	# your source code
LOCAL_MODULE := test_file_FIFO	# output file name
LOCAL_CFLAGS += -pie -fPIE	# These two line mustn’t be
LOCAL_LDFLAGS += -pie -fPIE	# change.
LOCAL_FORCE_STATIC_EXECUTABLE := true

include $(BUILD_EXECUTABLE)


include $(CLEAR_VARS)
LOCAL_SRC_FILES := test_file_RR.c	# your source code
LOCAL_MODULE := test_file_RR	# output file name
LOCAL_CFLAGS += -pie -fPIE	# These two line mustn’t be
LOCAL_LDFLAGS += -pie -fPIE	# change.
LOCAL_FORCE_STATIC_EXECUTABLE := true

include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES := test_file.c	# your source code
LOCAL_MODULE := test_file	# output file name
LOCAL_CFLAGS += -pie -fPIE	# These two line mustn’t be
LOCAL_LDFLAGS += -pie -fPIE	# change.
LOCAL_FORCE_STATIC_EXECUTABLE := true

include $(BUILD_EXECUTABLE)