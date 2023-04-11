cmake_minimum_required(VERSION 3.5)

project(raytracer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set (HEADERS
     include/rtincludes.h
     include/image.h
     include/vec3.h)

set (SOURCES
    src/image.cpp)

set (TESTS
     tests/vec3_tests.cpp)

Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.0.1 # or a later release
)

FetchContent_MakeAvailable(Catch2)

add_executable(raytracer ${HEADERS} ${SOURCES} src/main.cpp)

add_executable(raytracertests ${HEADERS} ${SOURCES} ${TESTS})

target_link_libraries(raytracertests PRIVATE Catch2::Catch2WithMain)

target_include_directories(raytracertests
    PRIVATE
    ${PROJECT_SOURCE_DIR}/include)

target_include_directories(raytracer
    PRIVATE
    ${PROJECT_SOURCE_DIR}/include)
