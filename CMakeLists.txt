#/****************************************************************************
# Copyright (c) 2013-2014 cocos2d-x.org
# Copyright (c) 2015-2017 Chukong Technologies Inc.
#
# http://www.cocos2d-x.org
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
# Try Lua
# ****************************************************************************/

cmake_minimum_required(VERSION 3.6)

set(APP_NAME hjctest)
project(${APP_NAME})

if (XCODE)
    if (NOT DEFINED CMAKE_XCODE_ATTRIBUTE_IPHONEOS_DEPLOYMENT_TARGET)
        SET(CMAKE_XCODE_ATTRIBUTE_IPHONEOS_DEPLOYMENT_TARGET 8.0)
    endif ()
endif ()

if (NOT DEFINED BUILD_ENGINE_DONE) # to test szj into root project
    set(COCOS2DX_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cocos2d)
    set(CMAKE_MODULE_PATH ${COCOS2DX_ROOT_PATH}/cmake/Modules/)

    include(CocosBuildSet)
#    set(BUILD_LUA_LIBS ON)
    add_subdirectory(${COCOS2DX_ROOT_PATH}/cocos ${ENGINE_BINARY_PATH}/cocos/core)
endif ()

# record sources, headers, resources...
set(GAME_SOURCE
        Classes/MainGame.cpp
)
set(GAME_HEADER
        Classes/MainGame.h
)
set(GAME_UI_SRC
        Classes/InputManager.cpp
        Classes/InputManager.h
        Classes/ResManager.cpp
        Classes/ResManager.h
        Classes/Common.cpp
        Classes/Common.h
        Classes/Player.cpp
        Classes/Player.h
        Classes/GameMap.cpp
        Classes/GameMap.h
        Classes/BaseView.cpp
        Classes/BaseView.h
        Classes/Test.cpp
        Classes/Test.h
        Classes/WsManager.cpp
        Classes/WsManager.h
        Classes/TestClass.cpp
        Classes/TestClass.h
)

if (WINDOWS)
    set(GAME_RES_FOLDER
            "${CMAKE_CURRENT_SOURCE_DIR}/ResourcesWin"
    )
elseif (ANDROID)
    set(GAME_RES_FOLDER
            "${CMAKE_CURRENT_SOURCE_DIR}/ResourcesAndroid"
    )
else ()
    set(GAME_RES_FOLDER
            "${CMAKE_CURRENT_SOURCE_DIR}/Resources"
    )
endif ()

if (APPLE OR WINDOWS)
    cocos_mark_multi_resources(common_res_files RES_TO "Resources" FOLDERS ${GAME_RES_FOLDER})
endif ()

set(compiler_c_flags "-Wno-error=format-security")

# add cross-platforms source files and header files
list(APPEND GAME_SOURCE
    Classes/AppDelegate.cpp
        Classes/MainScene.cpp


)
list(APPEND GAME_HEADER
    Classes/AppDelegate.h
        Classes/MainScene.h
)

list(APPEND GAME_UI_SRC
)

source_group("Sources"        FILES ${GAME_SOURCE})
source_group("Headers"        FILES ${GAME_HEADER})
source_group("UI"             FILES ${GAME_UI_SRC})

if (ANDROID)
    # change APP_NAME to the share library name for Android, it's value depend on AndroidManifest.xml
    set(APP_NAME MyGame)
    list(APPEND GAME_SOURCE
            proj.android/app/jni/hellocpp/main.cpp
#            Classes/szjLog/szjLog-android.cpp

    )
elseif (LINUX)
    list(APPEND GAME_SOURCE
            proj.linux/main.cpp
    )
elseif (WINDOWS)
    list(APPEND GAME_HEADER
            proj.win32/main.h
            proj.win32/resource.h
    )
    list(APPEND GAME_SOURCE
#            Classes/szjLog/szjLog.cpp
            proj.win32/main.cpp
            proj.win32/game.rc
            ${common_res_files}
    )
elseif (APPLE)
    if (IOS)
        list(APPEND GAME_HEADER
                proj.ios_mac/ios/AppController.h
                proj.ios_mac/ios/RootViewController.h
        )
        set(APP_UI_RES
                proj.ios_mac/ios/LaunchScreen.storyboard
                proj.ios_mac/ios/LaunchScreenBackground.png
                proj.ios_mac/ios/Images.xcassets
        )
        list(APPEND GAME_SOURCE
                proj.ios_mac/ios/main.m
                proj.ios_mac/ios/AppController.mm
                proj.ios_mac/ios/RootViewController.mm
                proj.ios_mac/ios/Prefix.pch
                ${APP_UI_RES}
        )
    elseif (MACOSX)
        set(APP_UI_RES
                proj.ios_mac/mac/Icon.icns
                proj.ios_mac/mac/Info.plist
        )
        list(APPEND GAME_SOURCE
                proj.ios_mac/mac/main.cpp
                proj.ios_mac/mac/Prefix.pch
                ${APP_UI_RES}
        )
    endif ()
    list(APPEND GAME_SOURCE ${common_res_files})
endif ()

# mark app complie info and libs info
set(    all_code_files
        ${GAME_HEADER}
        ${GAME_SOURCE}
        ${GAME_UI_SRC}
)

if (NOT ANDROID)
    add_executable(${APP_NAME} ${all_code_files})
else ()
    set( LIB_FMOD ${FMOD_API_ROOT}/libs/android/${ANDROID_ABI}/libfmod${FMOD_LIB_SUFFIX}.so )

    add_library( fmod SHARED IMPORTED )

    set_target_properties(
            fmod PROPERTIES
            IMPORTED_LOCATION ${LIB_FMOD}
            INTERFACE_INCLUDE_DIRECTORIES ${FMOD_API_ROOT}/Classes/inc
    )

    add_library(${APP_NAME} SHARED ${all_code_files})
    add_subdirectory(${COCOS2DX_ROOT_PATH}/cocos/platform/android ${ENGINE_BINARY_PATH}/cocos/platform)
    target_link_libraries(${APP_NAME} -Wl,--whole-archive cpp_android_spec -Wl,--no-whole-archive fmod)
#    add_subdirectory(${COCOS2DX_ROOT_PATH}/cocos/scripting/lua-bindings/proj.android ${ENGINE_BINARY_PATH}/cocos/lua-android)
#    target_link_libraries(${APP_NAME} -Wl,--whole-archive lua_android_spec -Wl,--no-whole-archive)
endif ()

if (WINDOWS)
    add_library( fmodlib SHARED IMPORTED )
    if(CMAKE_SIZEOF_VOID_P EQUAL 8)
        set_target_properties(
                fmodlib PROPERTIES
                IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/libs/windows/x64/fmodL.dll
                IMPORTED_IMPLIB ${CMAKE_CURRENT_SOURCE_DIR}/libs/windows/x64/fmodL_vc.lib
        )
    elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
        set_target_properties(
                fmodlib PROPERTIES
                IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/libs/windows/x86/fmodL.dll
                IMPORTED_IMPLIB ${CMAKE_CURRENT_SOURCE_DIR}/libs/windows/x86/fmodL_vc.lib
        )
    endif()

    target_link_libraries(${APP_NAME} cocos2d fmodlib)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /NODEFAULTLIB:libcmt /NODEFAULTLIB:msvcrt")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /NODEFAULTLIB:libcmt /NODEFAULTLIB:msvcrt")
else ()
#    target_link_libraries(${APP_NAME} cocos2d luacocos2d)
endif ()

target_include_directories(${APP_NAME}
        PRIVATE Classes
        PRIVATE Classes/common/
        PRIVATE ${COCOS2DX_ROOT_PATH}/cocos/audio/include/
)
# ming make lua depend
target_include_directories(${APP_NAME}
        INTERFACE ${COCOS2DX_ROOT_PATH}/external/lua/tolua/.
        INTERFACE ${COCOS2DX_ROOT_PATH}/external/lua/luajit/include/
)

target_link_libraries(${APP_NAME} ${COCOS2DX_ROOT_PATH}/external/lua/luajit/prebuilt/win32/lua51.lib)
#target_link_libraries(${APP_NAME} luacocos2d)
# ming make lua depend end

# mark app resources
setup_cocos_app_config(${APP_NAME})
if (APPLE)
    set_target_properties(${APP_NAME} PROPERTIES RESOURCE "${APP_UI_RES}")

    if (MACOSX)
        set_xcode_property(${APP_NAME} INFOPLIST_FILE "${CMAKE_CURRENT_SOURCE_DIR}/proj.ios_mac/mac/Info.plist")
    elseif (IOS)
        set_xcode_property(${APP_NAME} INFOPLIST_FILE "${CMAKE_CURRENT_SOURCE_DIR}/proj.ios_mac/ios/Info.plist")
        set_xcode_property(${APP_NAME} ASSETCATALOG_COMPILER_APPICON_NAME "AppIcon")
    endif ()

    # For code-signing, set the DEVELOPMENT_TEAM:
    #set_xcode_property(${APP_NAME} DEVELOPMENT_TEAM "GRLXXXX2K9")
elseif (WINDOWS)
    cocos_copy_target_dll(${APP_NAME})
endif ()

if (LINUX OR WINDOWS)
    cocos_get_resource_path(APP_RES_DIR ${APP_NAME})
    cocos_copy_target_res(${APP_NAME} LINK_TO ${APP_RES_DIR} FOLDERS ${GAME_RES_FOLDER})
endif ()
