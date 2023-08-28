cmake_minimum_required(VERSION 3.4.1)

set (CMAKE_VERBOSE_MAKEFILE ON)
set (CMAKE_CXX_STANDARD 11)

add_library(cpp-code
            SHARED
            # ../cpp-code/src/src/v99core.cpp
            cpp-adapter.cpp
)

add_library(crypto STATIC IMPORTED)
add_library(openssl STATIC IMPORTED)
add_library(nghttp2 STATIC IMPORTED)
add_library(curl STATIC IMPORTED)
add_library(v99core STATIC IMPORTED)

set_target_properties(crypto PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/lib/${ANDROID_ABI}/libcrypto.a)
set_target_properties(openssl PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/lib/${ANDROID_ABI}/libssl.a)
set_target_properties(nghttp2 PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/lib/${ANDROID_ABI}/libnghttp2.a)
set_target_properties(curl PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/lib/${ANDROID_ABI}/libv99core.a)

# Specifies a path to native header files.
include_directories(
            ../cpp-code/src/include
)

find_library(z-lib z)

target_link_libraries( # Specifies the target library.
		cpp-code

		# Links the target library to the log library
		# included in the NDK.
		curl
		nghttp2
		openssl
		crypto
		${z-lib}
)