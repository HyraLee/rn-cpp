//
// Created by Marius Reimer on 2019-08-10.
//

#include <iostream>
#include <jni.h>
#include <android/log.h>
#include "v99core.h"

using namespace std;

extern "C" JNIEXPORT jlong JNICALL
Java_com_mariusreimer_rncppcode_RNCPPCodeModule_nativeMultiply(JNIEnv *env, jclass type, jlong a, jlong b)
{
    return v99core::multiply(a, b);
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_mariusreimer_rncppcode_RNCPPCodeModule_nativeHttpGet(JNIEnv *env, jclass type, jstring url)
{
    const char *urlStr = env->GetStringUTFChars(url, nullptr);
    if (urlStr == nullptr)
    {
        // Handle the error, e.g., by returning an appropriate error string.
        return env->NewStringUTF("Error converting jstring to const char*");
    }

    // Create a C++ std::string from the C-style string
    std::string urlCpp(urlStr);

    // Release the memory allocated for the C-style string
    env->ReleaseStringUTFChars(url, urlStr);

    // Now you can use urlCpp as a C++ std::string in your code

    // Example usage:
    std::string result = v99core::httpGet(urlCpp);

    // Convert the C++ std::string back to a jstring for return
    return env->NewStringUTF(result.c_str());
}