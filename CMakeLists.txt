

cmake_minimum_required( VERSION 3.14 )

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(main)

add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

set(APP_NAME main)

add_executable(${APP_NAME}
    main.cpp
)

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
target_link_libraries( ${APP_NAME} PRIVATE ${OpenCV_LIBS} )


# 添加 libyuv 子目录
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/dependencies/libyuv)

# 包含 libyuv 头文件目录
include_directories(${CMAKE_CURRENT_LIST_DIR}/dependencies/libyuv/include)
# 链接 libyuv 库
target_link_libraries(${APP_NAME} PRIVATE yuv)
