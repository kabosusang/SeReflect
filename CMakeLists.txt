cmake_minimum_required(VERSION 3.15)
project(SegoJson
  VERSION 1.0
  LANGUAGES CXX
)

# 并行编译
include(ProcessorCount)
ProcessorCount(N)
if(NOT N EQUAL 0)
    set(CMAKE_JOB_POOL_COMPILE compile_job_pool)
    set(CMAKE_JOB_POOLS compile_job_pool=${N})
endif()

#----------------------------------------------------------------
# 现代 CMake 核心配置
#----------------------------------------------------------------
set(CMAKE_CXX_STANDARD 20)                # 强制使用 C++20 标准
set(CMAKE_CXX_STANDARD_REQUIRED ON)       # 必须支持该标准
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)     # 生成 compile_commands.json


# 默认构建类型为 Debug（如果未指定）
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

#----------------------------------------------------------------
# 项目目录结构
#----------------------------------------------------------------
# 源文件目录
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
# 头文件目录
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

#----------------------------------------------------------------
# 自动收集头文件（递归搜索 include/ 及其子目录）
#----------------------------------------------------------------
file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS
    "${INCLUDE_DIR}/*.h"
    "${INCLUDE_DIR}/*.hpp"
    "${INCLUDE_DIR}/*.hxx"
)

#----------------------------------------------------------------
# 自动收集源文件（推荐显式列出，此处演示自动收集）
#----------------------------------------------------------------
set(SOURCES)
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
  "${SOURCE_DIR}/*.cpp"
)


# 过滤掉不需要的文件（如测试文件）
foreach(file IN LISTS SRC_FILES)
    if(NOT file MATCHES ".*/test/.*")  # 排除test目录
        list(APPEND SOURCES ${file})
    endif()
endforeach()


#----------------------------------------------------------------
# 第三方库
#----------------------------------------------------------------


#----------------------------------------------------------------
# 可执行目标
#----------------------------------------------------------------
# 设置可执行文件输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(${PROJECT_NAME})

# 添加源文件到目标
target_sources(${PROJECT_NAME} PRIVATE ${SOURCES})

# 添加头文件到目标（IDE支持）
target_sources(${PROJECT_NAME} PRIVATE ${HEADERS})


# 现代头文件包含方式
target_include_directories(${PROJECT_NAME} PUBLIC
  $<BUILD_INTERFACE:${INCLUDE_DIR}>  # 构建时包含
  # $<INSTALL_INTERFACE:include>       # 安装后包含（可选）
)


#----------------------------------------------------------------
# 依赖管理示例（假设需要第三方库）
#----------------------------------------------------------------
# find_package(OpenCV REQUIRED)
# target_link_libraries(${PROJECT_NAME} PRIVATE OpenCV::OpenCV)
# target_link_libraries(${PROJECT_NAME} PRIVATE Catch2::Catch2)



