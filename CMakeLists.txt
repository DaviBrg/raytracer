cmake_minimum_required(VERSION 3.5)

project(raytracer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set (HEADERS
    include/camera.h
    include/image.h
    include/sphere.h
    include/object.h
    include/objectconcept.h
    include/objectmodel.h
    include/ray.h
    include/renderer.h
    include/rtincludes.h
    include/vec3.h
)

set (SOURCES
    src/camera.cpp
    src/sphere.cpp
    src/image.cpp
    src/object.cpp
    src/renderer.cpp
)

set (TESTS
    tests/camera_tests.cpp
    tests/vec3_tests.cpp
)

Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.3.0 # or a later release
)

FetchContent_MakeAvailable(Catch2)

add_executable(raytracer ${HEADERS} ${SOURCES} src/main.cpp)

add_executable(raytracertests ${HEADERS} ${SOURCES} ${TESTS})

enable_testing()

add_test(NAME all COMMAND raytracertests)

target_link_libraries(raytracertests PRIVATE Catch2::Catch2WithMain)

target_include_directories(raytracertests
    PRIVATE
    ${PROJECT_SOURCE_DIR}/include)

target_include_directories(raytracer
    PRIVATE
    ${PROJECT_SOURCE_DIR}/include)
