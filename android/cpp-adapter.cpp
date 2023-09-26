//
// Created by Marius Reimer on 2019-08-10.
//

#include <iostream>
#include <jni.h>
#include <android/log.h>
#include "v99core.h"

using namespace std;

//  Fix issues with clang compiler

#undef stderr
FILE *stderr = &__sF[2];

#undef stdin
FILE *stdin = &__sF[0];

extern "C"
{
    void __stack_chk_fail(void)
    {
        abort();
    }
    /* On some architectures, this helps needless PIC pointer setup
       that would be needed just for the __stack_chk_fail call.  */

    void __stack_chk_fail_local(void)
    {
        __stack_chk_fail();
    }
}

extern "C" JNIEXPORT jdouble JNICALL
Java_com_mariusreimer_rncppcode_RNCPPCodeModule_nativeMultiply(JNIEnv *env, jclass type, jdouble a, jdouble b)
{
    return v99core::multiply(a, b);
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_mariusreimer_rncppcode_RNCPPCodeModule_nativeHttpGet(JNIEnv *env, jclass type, jstring url)
{
    const char *urlStr = env->GetStringUTFChars(url, nullptr);
    if (urlStr == nullptr)
    {
        return env->NewStringUTF("Error converting jstring to const char*");
    }

    std::string urlCpp(urlStr);
    env->ReleaseStringUTFChars(url, urlStr);
    std::string result = v99core::httpGet(urlCpp);
    return env->NewStringUTF(result.c_str());
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_mariusreimer_rncppcode_RNCPPCodeModule_nativeHttpPost(JNIEnv *env, jclass type, jstring url, jstring param)
{
    const char *urlStr = env->GetStringUTFChars(url, nullptr);
    const char *paramStr = env->GetStringUTFChars(param, nullptr);
    if (urlStr == nullptr || paramStr == nullptr)
    {
        return env->NewStringUTF("Error converting jstring to const char*");
    }

    std::string urlCpp(urlStr);
    std::string parCpp(paramStr);
    env->ReleaseStringUTFChars(url, urlStr);
    env->ReleaseStringUTFChars(param, paramStr);
    std::string result = v99core::httpPost(urlCpp, parCpp);
    return env->NewStringUTF(result.c_str());
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_mariusreimer_rncppcode_RNCPPCodeModule_nativeHttpDelete(JNIEnv *env, jclass type, jstring url)
{
    const char *urlStr = env->GetStringUTFChars(url, nullptr);
    if (urlStr == nullptr)
    {
        return env->NewStringUTF("Error converting jstring to const char*");
    }

    std::string urlCpp(urlStr);
    env->ReleaseStringUTFChars(url, urlStr);
    std::string result = v99core::httpDelete(urlCpp);
    return env->NewStringUTF(result.c_str());
}

////////////////////////////////////////////////////
////////////     V99 CORE APP           ////////////
////////////////////////////////////////////////////

extern "C" JNIEXPORT jstring JNICALL
Java_com_mariusreimer_rncppcode_RNCPPCodeModule_nativeGetPlatform(JNIEnv *env, jclass type)
{
    std::string result = v99core::getPlatform();
    return env->NewStringUTF(result.c_str());
}
