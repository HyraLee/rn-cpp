//
// Created by Marius Reimer on 2019-08-10.
//

#include <iostream>
#include <jni.h>
#include <android/log.h>
#include "example.h"

using namespace std;

extern "C" JNIEXPORT jlong JNICALL
Java_com_mariusreimer_rncppcode_RNCPPCodeModule_multiply(JNIEnv *env, jclass type, jlong a, jlong b)
{
    return example::multiply(a, b);
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_mariusreimer_rncppcode_RNCPPCodeModule_httpGet(JNIEnv *env, jclass type, jstring url)
{
    return example::httpGet(url, "");
}