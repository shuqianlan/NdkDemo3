//
// Created by 吴正华 on 2019-06-24.
//

#include "com_ilifesmart_ndkdemo_Lame.h"
#include "com_ilifesmart_ndkdemo_DataProvider.h"
#include <android/log.h>
#include <malloc.h>
#include <string.h>

#define  LOG_TAG "System.out"
#define LOGD(format, ...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __FILE__":%d|" #format, __LINE__, ##__VA_ARGS__)
#define LOGI(format, ...) __android_log_print( ANDROID_LOG_INFO, LOG_TAG, __FILE__":%d|" #format, __LINE__, ##__VA_ARGS__)


JNIEXPORT jstring JNICALL Java_com_ilifesmart_ndkdemo_Lame_getLameVersion
        (JNIEnv *env, jobject) {

    const char* version = get_lame_version();
    return env->NewStringUTF(version);
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

JNIEXPORT void JNICALL Java_com_ilifesmart_ndkdemo_Lame_convertAudio
        (JNIEnv *env, jobject, jstring input, jstring output) {

    char * inputName = Jstring2CStr(env, input);
    char * outputName = Jstring2CStr(env, output);

    LOGD("inputFileName %s ", inputName);
    LOGD("outputFileName %s ", outputName);

    FILE *wav = fopen(inputName, "rb");
    FILE *mp3 = fopen(outputName, "wb");

    int read, write;
    short int wav_buffer[8192*2];
    unsigned char mp3_buffer[8192];

    lame_t lame = lame_init();
    lame_set_in_samplerate(lame, 44100);
    lame_set_num_channels(lame, 2);
    lame_set_VBR(lame, vbr_default);
    lame_init_params(lame);

    do {
        read = fread(wav_buffer, sizeof(short int)*2, 8192, wav);
        if (read == 0) {
            write = lame_encode_flush(lame, mp3_buffer, 8192);
            fwrite(mp3_buffer, sizeof(char), write, mp3);
        } else {
            write = lame_encode_buffer_interleaved(lame, wav_buffer, read, mp3_buffer, 8192);
            fwrite(mp3_buffer, sizeof(char), write, mp3);
        }
    } while (read != 0);

    lame_close(lame);
    fclose(wav);
    fclose(mp3);

    LOGD("%s", "Completed");
}