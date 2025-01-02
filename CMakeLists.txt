cmake_minimum_required(VERSION 3.5)

# Project
project(MetalEngine)

# Sources
file(GLOB_RECURSE SOURCES src/*.cpp src/*.c)
file(GLOB_RECURSE HEADERS src/*.hpp src/*.h include/*.hpp include/*.h)

# Executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Flags
target_compile_options(${PROJECT_NAME} PRIVATE
	-std=c++17 -O3 -Wall -Wextra -Werror -Wfloat-equal -Wundef -Wcast-align -Wwrite-strings -Wconversion -Wunreachable-code -Wpedantic
)

# Include directories
target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC ${CMAKE_SOURCE_DIR}/src)
target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC ${CMAKE_SOURCE_DIR}/lib/metal-cpp)
target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC ${CMAKE_SOURCE_DIR}/lib/metal-cpp-extensions)
target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC ${CMAKE_SOURCE_DIR}/lib/stb_image)

# Libraries
find_library(APPLE_FWK_FOUNDATION Foundation REQUIRED)
find_library(APPLE_FWK_QUARTZ_CORE QuartzCore REQUIRED)
find_library(APPLE_FWK_METAL Metal REQUIRED)
find_library(APPLE_FWK_METALKIT MetalKit REQUIRED)
find_library(APPLE_FWK_APPKIT AppKit REQUIRED)

# Link libraries
target_link_libraries(${PROJECT_NAME}
    ${APPLE_FWK_FOUNDATION}
    ${APPLE_FWK_QUARTZ_CORE}
    ${APPLE_FWK_METAL}
    ${APPLE_FWK_METALKIT}
    ${APPLE_FWK_APPKIT}
)
