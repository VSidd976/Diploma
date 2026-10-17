add_executable("Executable" main.cpp)

target_link_libraries("Executable" PUBLIC "Derivatives")

add_executable("Test" jacobian_demo.cpp)
