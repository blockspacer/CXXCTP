cmake_minimum_required( VERSION 3.10.0 FATAL_ERROR )

#find_package(catch2 REQUIRED)
#find_package(FakeIt REQUIRED)

find_package(Catch2 REQUIRED)

add_library( test_main STATIC
  main.cpp
  testsCommon.h # include in IDE
)

get_target_property (catch2_IMPORTED_LOCATION Catch2::Catch2 INTERFACE_INCLUDE_DIRECTORIES)
message( STATUS "catch2_IMPORTED_LOCATION=${catch2_IMPORTED_LOCATION}" )

target_include_directories(test_main PUBLIC
    "${catch2_IMPORTED_LOCATION}/catch2/"
)

target_link_libraries(test_main PUBLIC
    CXXCTP_core
    #${CONAN_LIBS}
    #CONAN_PKG::catch2
    #catch2::catch2
    Catch2::Catch2
    #FakeIt::FakeIt
    CONAN_PKG::FakeIt
)

file(GLOB_RECURSE TEST_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_executable(cxxctp_test
    ${TEST_SOURCE})

target_link_libraries(cxxctp_test PUBLIC
    test_main
)

# We run our test from the source directory, so we can consistently
# load files with known paths.
# I also like color in my verbose output, so I put in a --force-colour flag.
add_test(NAME cxxctp_test
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
         COMMAND ${CMAKE_BINARY_DIR}/bin/cxxctp_test --force-colour)
