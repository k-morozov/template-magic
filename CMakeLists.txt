cmake_minimum_required(VERSION 3.16)

set(APP_NAME print)
if (DEFINED $ENV{TRAVIS_BUILD_NUMBER})
    project(${APP_NAME} VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else()
    project(${APP_NAME} VERSION 0.0.1)
endif()

configure_file(version.h.in version.h)

add_executable(${APP_NAME} main.cpp)

set_target_properties(${APP_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(${APP_NAME} PRIVATE ${CMAKE_BINARY_DIR})
target_compile_options(${APP_NAME} PRIVATE -Wall -Wpedantic -Wextra -Werror)