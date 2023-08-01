# React Native C++ Code Native Module

Repo demo cho việc xây dựng một native module C++ cho React Native

## Tích hợp cho IOS

- Tích hợp C++ cho native module thông qua Objective C++ (.mm file)

- Sử dụng preprocessor directive __cplusplus để wrap code C++:

```bash
        #ifdef __cplusplus

        #import "example.h"

        #endif

        @class RNCPPCode;

        /**
        *...
        */
        @interface RNCPPCode : NSObject <RCTBridgeModule>

        @end

        #endif
```

- Khai báo native module và các file cpp trong file .podspec

```bash
        require 'json'

        package = JSON.parse(File.read(File.join(__dir__, 'package.json')))

        Pod::Spec.new do |s|
        s.name         = "RNCPPCode"
        s.version      = package['version']
        s.summary      = package['description']
        s.license      = package['license']

        s.authors      = package['author']
        s.homepage     = package['homepage']
        s.platforms    = { :ios => "9.0", :tvos => "9.2" }

        s.source       = { :git => "https://github.com/reime005/react-native-cpp-code.git", :tag => "s.version" }
        s.source_files  = "ios/**/*.{h,mm}", "cpp-code/**/*.{cpp,h}"

        s.dependency 'React'
        end
```

- Khai báo interface trong file .mm

- Lưu ý: sử dụng file .mm thay vì file .m cho phần tích hợp C++

## Tích hợp cho Android

- Đối với android cần phải sử dụng NDK để build ra một static libary

- Tương tác giữa C++ và android sẽ thông qua Java Native Interface (JNI)

### Step build native module cho android

- Mở rộng build.gradle để build libary.

- Tạo file CMakeLists.txt để khai báo file code C++

- Khai báo interface cho code C++

- Lưu ý: tên của function phải được khai báo chính xác theo cú pháp. Ví dụ:

```bash
#include <jni.h>
#include "example.h"

extern "C"
JNIEXPORT jlong JNICALL
Java_com_mariusreimer_rncppcode_RNCPPCodeModule_multiply(JNIEnv *env, jclass type, jlong a, jlong b) {
    return example::multiply(a, b);
}
```