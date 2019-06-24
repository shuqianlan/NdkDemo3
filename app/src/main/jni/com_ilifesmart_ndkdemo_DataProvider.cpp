//
// Created by 吴正华 on 2019-06-24.
//

#include "com_ilifesmart_ndkdemo_DataProvider.h"
#include <android/log.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

#define  LOG_TAG "System.out"
#define LOGD(format, ...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __FILE__":%d|" #format, __LINE__, ##__VA_ARGS__)
#define LOGI(format, ...) __android_log_print( ANDROID_LOG_INFO, LOG_TAG, __FILE__":%d|" #format, __LINE__, ##__VA_ARGS__)

JNIEXPORT void JNICALL Java_com_ilifesmart_ndkdemo_DataProvider_callJavaAdd
  (JNIEnv *env, jobject obj) {
    const char * classname = "com/ilifesmart/ndkdemo/DataProvider";
    jclass clazz = env->FindClass(classname);

    if (clazz == 0) {
        LOGD("%s", "invalid class.");
    }

    jmethodID java_method = env->GetMethodID(clazz, "add", "(II)I");
    if (java_method == 0) {
        LOGD("%s", "invaliud method.");
    }

    jint result = env->CallIntMethod(obj, java_method, 3, 4);
    LOGD("Result=%d", result);
}

JNIEXPORT void JNICALL Java_com_ilifesmart_ndkdemo_DataProvider_callHelloFromJava
        (JNIEnv *env, jobject obj) {

    const char * classname = "com/ilifesmart/ndkdemo/DataProvider";
    jclass clazz = env->FindClass(classname);

    if (clazz == 0) {
        LOGD("%s", "invalid class.");
    }

    jmethodID java_method = env->GetMethodID(clazz, "helloFromJava", "()V");
    if (java_method == 0) {
        LOGD("%s", "invaliud method.");
    }

    env->CallVoidMethod(obj, java_method);
}

JNIEXPORT void JNICALL Java_com_ilifesmart_ndkdemo_DataProvider_callPrint
        (JNIEnv *env, jobject obj) {

    const char * classname = "com/ilifesmart/ndkdemo/DataProvider";
    jclass clazz = env->FindClass(classname);

    if (clazz == 0) {
        LOGD("%s", "invalid class.");
    }

    jmethodID java_method = env->GetMethodID(clazz, "print", "(Ljava/lang/String;)V");
    if (java_method == 0) {
        LOGD("%s", "invaliud method.");
    }

    env->CallVoidMethod(obj, java_method, env->NewStringUTF("This is from C++"));
}

extern "C"
JNIEXPORT void JNICALL
Java_com_ilifesmart_ndkdemo_DataProvider_callStaticPrint(JNIEnv *env, jclass type) {

    const char * classname = "com/ilifesmart/ndkdemo/DataProvider";
    jclass clazz = env->FindClass(classname);

    if (clazz == 0) {
        LOGD("%s", "invalid class.");
    }

    jmethodID java_method = env->GetStaticMethodID(clazz, "statticPrint", "()V");
    if (java_method == 0) {
        LOGD("%s", "invaliud method.");
    }

    env->CallStaticVoidMethod(type, java_method);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_ilifesmart_ndkdemo_DataProvider_sayHello(JNIEnv *env, jclass type) {

    LOGD("%s", "Hello,JNI");
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_ilifesmart_ndkdemo_DataProvider_add_1(JNIEnv *env, jclass type, jint x, jint y) {

    return x + y;
}

char * Jstring2CStr(JNIEnv *env, jstring jstr) {
    char* result = NULL;
    jclass clazz = env->FindClass("java/lang/String");
    if (clazz == 0) {
        LOGD("%s", "invalid class");
    }
    jstring strencode = env->NewStringUTF("GB2312");
    jmethodID java_method = env->GetMethodID(clazz, "getBytes", "(Ljava/lang/String;)[B");
    jbyteArray barr = (jbyteArray)env->CallObjectMethod(jstr, java_method, strencode);
    jsize alen = env->GetArrayLength(barr);
    jbyte *arrs = env->GetByteArrayElements(barr, JNI_FALSE);

    if (alen > 0) {
        result = (char*) malloc(alen+1);
        memcpy(result, arrs, alen);
        result[alen] = 0;
    }
    env->ReleaseByteArrayElements(barr, arrs, 0);
    return result;
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_ilifesmart_ndkdemo_DataProvider_append(JNIEnv *env, jclass type, jstring s_) {
    char *result = Jstring2CStr(env, s_);
    return env->NewStringUTF(strcat(result, "Append"));
}