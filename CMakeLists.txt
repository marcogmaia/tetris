cmake_minimum_required(VERSION 3.25)

project(
  tetris
  VERSION 0.0.1
  LANGUAGES C CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_COMPILE_WARNING_AS_ERROR ON)

set(CMAKE_MODULE_PATH CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

# cmake-format: off
find_package(EnTT CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(GTest CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(tl-expected CONFIG REQUIRED)
find_package(tl-optional CONFIG REQUIRED)
# cmake-format: on

enable_testing()
include(CTest)
include(GoogleTest)

# Uncomment the line bellow to debug with LLVM.
#
# set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -gdwarf-4")

include_directories("${CMAKE_SOURCE_DIR}/src")

# Add 3rd_party libraries first
add_subdirectory(external)

# add_subdirectory(includes)
add_subdirectory(src)
