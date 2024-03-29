# 脚本文件，用于将C++编译为动态/静态库文件

# $(call my-dir): 获取Android.mk所在的目录
# $(CLEAR_VARS):  清除出LOCAL_PATH以外的所有LOCAL_XXX变量
# LOCAL_MODULE:   生成的库的名字
# $(BUILD_SHARED_LIBRARY): 将C++ 文件编译为动态库 *.so (体积小)
# $(BUILD_STATIC_LIBRARY): 将C++ 文件编译为静态库 *.a  (体积大)
# LOCAL_MODULE:生成的动态库名为"lib"+Name+".so"
# LOCAL_LDLIBS: 此处未链接liblog.so

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := DataProvider
LOCAL_SRC_FILES := com_ilifesmart_ndkdemo_DataProvider.cpp com_ilifesmart_ndkdemo_Lame.cpp bitstream.c encoder.c fft.c gain_analysis.c \
  id3tag.c lame.c mpglib_interface.c newmdct.c presets.c psymodel.c quantize_pvt.c quantize.c reservoir.c set_get.c tables.c takehiro.c util.c vbrquantize.c \
  VbrTag.c version.c $(LOCAL_PATH)/vector/xmm_quantize_sub.c

LOCAL_LDLIBS += -llog
include $(BUILD_SHARED_LIBRARY)