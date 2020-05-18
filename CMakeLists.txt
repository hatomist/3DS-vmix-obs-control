cmake_minimum_required(VERSION 3.7)
project(3DSBuildTemplate)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR armv6k)

set(CMAKE_CXX_STANDARD 11)

set(ARCH "-march=armv6k -mtune=mpcore -mfloat-abi=hard  -mtp=soft ")
set(CMAKE_C_FLAGS " -mword-relocations ${ARCH}" CACHE STRING "C flags")
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS}" CACHE STRING "C++ flags")
set(DKA_SUGGESTED_C_FLAGS "-fomit-frame-pointer")
set(DKA_SUGGESTED_CXX_FLAGS "${DKA_SUGGESTED_C_FLAGS} -fno-rtti -fno-exceptions -std=gnu++11")


set(DEVKITPRO /opt/devkitpro)
set(DEVKITARM /opt/devkitpro/devkitARM)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=armv6k -mtune=mpcore -mfloat-abi=hard")
set(LINKER_SCRIPT "${DEVKITPRO}/devkitarm-crtls/3dsx.ld")

add_compile_options(
        "-Wall" "-Wpedantic" "-Wextra" "-fexceptions"
        "$<$<CONFIG:DEBUG>:-O0;-g3;-ggdb>" "-mfpu=vfp" "-mfloat-abi=hard"
)

SET(CMAKE_C_COMPILER $ENV{DEVKITARM}/bin/arm-none-eabi-gcc)
SET(CMAKE_CXX_COMPILER_WORKS 1)
SET(CMAKE_CXX_COMPILER $ENV{DEVKITARM}/bin/arm-none-eabi-g++)
set(CMAKE_ASM_COMPILER $ENV{DEVKITARM}/bin/arm-none-eabi-gcc)
set(CMAKE_AR $ENV{DEVKITARM}/bin/arm-none-eabi-ar)
set(CMAKE_OBJCOPY $ENV{DEVKITARM}/bin/arm-none-eabi-objcopy)
set(CMAKE_OBJDUMP $ENV{DEVKITARM}/bin/arm-none-eabi-objdump)
set(SIZE $ENV{DEVKITARM}/bin/arm-none-eabi-size)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -specs=${DEVKITPRO}/devkitarm-crtls/3dsx.specs")

link_directories($ENV{DEVKITARM}/lib $ENV{DEVKITPRO}/libctru/lib source/lib)

set(SOURCE_FILES
        source/main.h
        source/main.cpp
        source/graphics/Output.h
        source/graphics/Output.cpp
        source/hbkb.h
        $ENV{DEVKITPRO}/devkitarm-crtls/3dsx_crt0.s
        source/logger/Logger.cpp
        source/logger/Logger.h
        lv_conf.h
        source/graphics/fnt.c
        source/lv_test_theme_2.c source/lv_test_theme_2.h source/graphics/initdisplays.cpp source/graphics/initdisplays.h source/graphics/setcontent.cpp source/graphics/setcontent.h)

include_directories(lvgl)


include_directories(/opt/devkitpro/devkitARM/include/)
include_directories(/opt/devkitpro/devkitARM/arm-none-eabi/include)
include_directories(/opt/devkitpro/libctru/include)
include_directories(/opt/devkitpro/devkitARM/arm-none-eabi/include/c++/7.1.0)

file(GLOB lvgl_SRC
        "lvgl/*.h"
        "lvgl/*.c"
        "lvgl/*/*.h"
        "lvgl/*/*.c"
        "lvgl/*/*/*.h"
        "lvgl/*/*/*.c")

add_library(lvgl ${lvgl_SRC})
set_target_properties(lvgl PROPERTIES LINKER_LANGUAGE C)

add_executable(3DSBuildTemplate ${SOURCE_FILES})
target_link_libraries(3DSBuildTemplate citro3d citro2d citro2dd citro3dd hbkb ctrud lvgl m)

