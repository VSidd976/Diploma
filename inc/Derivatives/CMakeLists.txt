add_library("Derivatives" INTERFACE)

target_include_directories("Derivatives" INTERFACE ./)

if (MSVC)
    target_compile_options("Derivatives" INTERFACE /Zc:cmath)
endif()
