project(api_route_unit_tests)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(api_route_unit_tests
    main.cpp
    radix_test.cpp
 "str_test.cpp")

target_link_libraries(api_route_unit_tests
    GTest::gtest_main
)

include(GoogleTest)

gtest_discover_tests(api_route_unit_tests)