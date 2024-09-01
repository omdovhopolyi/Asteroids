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

target_compile_definitions(${TARGET_NAME} PRIVATE SHEN_NO_MAIN)
set(SHEN_STATIC ON CACHE BOOL "" FORCE)

add_subdirectory(submodules/ShapesEngine2)

if(MSVC)
    target_link_libraries(${TARGET_NAME} ShapesEngine2)
    target_link_options(${TARGET_NAME} PRIVATE /WHOLEARCHIVE:ShapesEngine2)
else()
    target_link_libraries(${TARGET_NAME} PRIVATE -Wl,--whole-archive ShapesEngine2 -Wl,--no-whole-archive)
endif()

include_directories(submodules/ShapesEngine2/src)
include_directories(submodules/ShapesEngine2/submodules/entt/src)
include_directories(submodules/ShapesEngine2/submodules/spdlog/include)

add_compile_definitions(_SILENCE_STDEXT_ARR_ITERS_DEPRECATION_WARNING)

set_target_properties(${TARGET_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)
