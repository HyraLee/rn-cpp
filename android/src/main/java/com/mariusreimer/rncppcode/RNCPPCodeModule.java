/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

package com.mariusreimer.rncppcode;

import android.util.Log;

import com.facebook.react.bridge.Arguments;
import com.facebook.react.bridge.Promise;
import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.bridge.ReactContextBaseJavaModule;
import com.facebook.react.bridge.ReactMethod;
import com.facebook.react.bridge.WritableMap;
import com.facebook.react.module.annotations.ReactModule;

@ReactModule(name = RNCPPCodeModule.TAG)
public final class RNCPPCodeModule
    extends ReactContextBaseJavaModule {

  public static final String TAG = "RNCPPCode";

  static {
    try {
      System.loadLibrary("cpp-code");
      Log.d(TAG, "-------- libcpp-code: loaded");
    } catch (Exception e){
      Log.d(TAG, "-------- libcpp-code: loaded");
    }
  }

  RNCPPCodeModule(ReactApplicationContext reactContext) {
    super(reactContext);
  }

  @Override
  public String getName() {
    return TAG;
  }

  /**
   *
   */
  private static native double nativeMultiply(double a, double b);
  private static native String nativeHttpGet(String url);
  private static native String nativeHttpPost(String url, String pararm);
  private static native String nativeHttpDelete(String url);

  // Example method
  // See https://reactnative.dev/docs/native-modules-android
  @ReactMethod
  public void multiply(double a, double b, Promise promise) {
    promise.resolve(nativeMultiply(a, b));
  }

  @ReactMethod
  public void httpGet(String url, Promise promise) {
    promise.resolve(nativeHttpGet(url));
  }

  @ReactMethod
  public void httpPost(String url, String pararm, Promise promise) {
    promise.resolve(nativeHttpPost(url, pararm));
  }

  @ReactMethod
  public void httpDelete(String url, Promise promise) {
    promise.resolve(nativeHttpDelete(url));
  }
}
