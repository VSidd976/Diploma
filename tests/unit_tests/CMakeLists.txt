add_executable("unit_tests" main.cpp)
target_link_libraries("unit_tests" PUBLIC "Derivatives" Catch2::Catch2WithMain)

catch_discover_tests("unit_tests")
