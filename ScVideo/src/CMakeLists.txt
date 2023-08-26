message(STATUS "================================================")

file(GLOB_RECURSE CUR_PRJ_SRC
    ${TOP_DIR}/src/*.h
    ${TOP_DIR}/src/*.cpp
    ${TOP_DIR}/src/*.ui)
set(CUR_ALL_SRC
    main.cpp ${CUR_PRJ_SRC}
    ${TOP_DIR}/assets/appico/others.rc)


message(STATUS "--add_executable")
add_executable(${PROJECT_NAME} ${CUR_ALL_SRC})

#target_link_libraries(${PROJECT_NAME} PRIVATE sk_base) //引入外部库

target_include_directories(${PROJECT_NAME} PRIVATE ${TOP_DIR}/src)



#----------- Remove the console of gui program
if(WIN32)
    if(MSVC)
        set_target_properties(${PROJECT_NAME} PROPERTIES
            WIN32_EXECUTABLE YES
            LINK_FLAGS "/ENTRY:mainCRTStartup"
        )
    elseif(CMAKE_COMPILER_IS_GNUCXX)
        # SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mwindows") # Not tested
    else()
        message(SEND_ERROR "You are using an unsupported Windows compiler! (Not MSVC or GCC)")
    endif(MSVC)
elseif(APPLE)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        MACOSX_BUNDLE YES
    )
elseif(UNIX)
    # Nothing special required
else()
    message(SEND_ERROR "You are on an unsupported platform! (Not Win32, Mac OS X or Unix)")
endif(WIN32)

#------------------------------------------------ Qt 依赖库/框架
find_package(Qt5 COMPONENTS
        Core
        Gui
        WebSockets
        Network
        Widgets
        WebEngineWidgets
        Sql
        Xml
        AxContainer
        #LinguistTools   #QT-Linguist工具主要用在项目的多语言翻译处理过程中
        REQUIRED
    )
target_link_libraries(${PROJECT_NAME}
   PRIVATE
   Qt5::Core
   Qt5::Gui
   Qt5::WebSockets
   Qt5::Network
   Qt5::Widgets
   Qt5::WebEngineWidgets
   Qt5::Sql
   Qt5::Xml
   Qt5::AxContainer  #Qt5::GuiPrivate
)

message(STATUS "================================================")

