LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_SRC_FILES := BurgerBuddies.c	# your source code
LOCAL_MODULE := BBC			# output file name
LOCAL_CFLAGS += -pie -fPIE		# These two line mustn’t be
LOCAL_LDFLAGS += -pie -fPIE		# change.
LOCAL_FORCE_STATIC_EXECUTABLE := true

include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES := 5140309178Process.c	# your source code
LOCAL_MODULE := 5140309178Parent	# output file name
LOCAL_CFLAGS += -pie -fPIE		# These two line mustn’t be
LOCAL_LDFLAGS += -pie -fPIE		# change.
LOCAL_FORCE_STATIC_EXECUTABLE := true

include $(BUILD_EXECUTABLE)


include $(CLEAR_VARS)
LOCAL_SRC_FILES := test_ptree.c		# your source code
LOCAL_MODULE := test_ptree		# output file name
LOCAL_CFLAGS += -pie -fPIE		# These two line mustn’t be
LOCAL_LDFLAGS += -pie -fPIE		# change.
LOCAL_FORCE_STATIC_EXECUTABLE := true

include $(BUILD_EXECUTABLE)
