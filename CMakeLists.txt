cmake_minimum_required(VERSION 3.22)

project("Dimploma" LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)

option(ENABLE_TESTING "Enable Unit tests build" ON)

include("cmake/CPM.cmake")

if(ENABLE_TESTING)
    CPMAddPackage("gh:catchorg/Catch2#v3.16.1")
    list(APPEND CMAKE_MODULE_PATH "${Catch2_SOURCE_DIR}/extras")
    include(CTest)
    include(Catch)
    enable_testing()
    add_subdirectory(tests)
endif()

add_subdirectory(inc)
add_subdirectory(app)
