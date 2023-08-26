cmake_minimum_required(VERSION 3.5)

#----------------------------------------#
set(PROJECT_NAME ScVideo)
project(${PROJECT_NAME} VERSION 3.3.0 LANGUAGES CXX)


set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON) # .ui .qrc


# windows下使用，可以避免linux代码拉取下来后出现如下警告
# warning C4819: 该文件包含不能在当前代码页(936)中表示的字符。请将该文件保存为 Unicode 格式以防止数据丢失
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /utf-8")


set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)  #存放可执行文件
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)  #存放动态库文件
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)  #存放静态库文件


# ---------- 添加第三方库文件查找路径 #------ link_directories命令用于添加目录使链接器能在其查找库
if(WIN32)
    if(MSVC)
        if(CMAKE_BUILD_TYPE STREQUAL "Release")
            link_directories(${TOP_DIR}/assets/prebuilt/windows/release)
            message(STATUS "build type: WIN32-MSVC-Release")
        elseif(CMAKE_BUILD_TYPE STREQUAL "Debug")
            link_directories(${TOP_DIR}/assets/prebuilt/windows/debug)
            message(STATUS "build type: WIN32-MSVC-Debug")
        else()
            message(STATUS "build type: WIN32-MSVC-unknown")
            message(SEND_ERROR "You are on an unsupported build type! (Not Release or Debug)")
        endif()
    else()
        message(STATUS "build type: WIN32-unknown")
        message(SEND_ERROR "You are using an unsupported Windows compiler! (Not MSVC)")
    endif(MSVC)
elseif(UNIX)
    link_directories(/usr/lib/x86_64-linux-gnu /usr/local/lib /usr/lib) #libev
    if(CMAKE_BUILD_TYPE STREQUAL "Release")
        link_directories(${TOP_DIR}/assets/prebuilt/linux/release)
        message(STATUS "build type: UNIX-Release")
    elseif(CMAKE_BUILD_TYPE STREQUAL "Debug")
        link_directories(${TOP_DIR}/assets/prebuilt/linux/debug)
        message(STATUS "build type: UNIX-Debug")
    else()
        message(STATUS "build type: UNIX-unknown")
        message(SEND_ERROR "You are on an unsupported build type! (Not Release or Debug)")
    endif()
else()
    message(STATUS "build type: unknown")
    message(SEND_ERROR "You are on an unsupported platform! (Not Win32 or Unix)")
endif(WIN32)


#----------------------------------------#
set(TOP_DIR ${CMAKE_CURRENT_SOURCE_DIR})
add_subdirectory(src)



