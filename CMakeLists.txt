cmake_minimum_required(VERSION 3.20.4 FATAL_ERROR)

set(TARGET_NAME Asteroids)

project(${TARGET_NAME})

set(BUILD_SHARED_LIBS FALSE)

file (GLOB_RECURSE SRC_FILES 
    ${PROJECT_SOURCE_DIR}/src/*.h
    ${PROJECT_SOURCE_DIR}/src/*.cpp
)

add_executable(${TARGET_NAME} ${SRC_FILES})

foreach(source IN LISTS SRC_FILES)
    get_filename_component(source_path "${source}" DIRECTORY)
    string(REPLACE ${PROJECT_SOURCE_DIR} "" source_path "${source_path}")
    source_group("${source_path}" FILES "${source}")
endforeach()

target_compile_features(${TARGET_NAME} PUBLIC cxx_std_20)

include_directories(src)

set_target_properties(${TARGET_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)
