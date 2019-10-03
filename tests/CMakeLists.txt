cmake_minimum_required(VERSION 3.10.0 FATAL_ERROR)

#find_package(catch2 REQUIRED)
#find_package(FakeIt REQUIRED)

find_package(Catch2 REQUIRED)
find_package(GTest REQUIRED)

include(GoogleTest)
include(CTest)
include(Catch)

include_directories(${GTEST_INCLUDE_DIRS})

set(CMAKE_EXE_LINKER_FLAGS "-pthread")

set(test_main_sources
    main.cpp
    testsCommon.h # include in IDE
    )

add_library(catch2_test_main STATIC ${test_main_sources})

get_target_property(catch2_IMPORTED_LOCATION Catch2::Catch2 INTERFACE_INCLUDE_DIRECTORIES)
message(STATUS "catch2_IMPORTED_LOCATION=${catch2_IMPORTED_LOCATION}")

target_include_directories(catch2_test_main PUBLIC "${catch2_IMPORTED_LOCATION}/catch2/")

target_link_libraries(catch2_test_main
                      PUBLIC CXXCTP_core
                             #${CONAN_LIBS}
                             #CONAN_PKG::catch2
                             #catch2::catch2
                             Catch2::Catch2
                             #FakeIt::FakeIt
                             CONAN_PKG::FakeIt)

#file(GLOB_RECURSE TEST_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

#add_executable(cxxctp_test
#    ${TEST_SOURCE})

add_library(gtest_test_main STATIC ${test_main_sources})

target_link_libraries(gtest_test_main
                      PUBLIC CXXCTP_core
                             #${CONAN_LIBS}
                             #CONAN_PKG::catch2
                             #catch2::catch2
                             #Catch2::Catch2
                             #FakeIt::FakeIt
                             #CONAN_PKG::FakeIt
                             GTest::GTest)

function(add_catch2_unit_test NAME SRC_FILES)
  add_executable(${NAME} "${SRC_FILES}")
  target_link_libraries(${NAME} catch2_test_main)
  catch_discover_tests(${NAME})
endfunction()

function(add_gtest_unit_test NAME SRC_FILES)
  add_executable(${NAME} "${SRC_FILES}")
  target_link_libraries(${NAME} gtest_test_main)
  gtest_add_tests(TARGET ${NAME} TEST_PREFIX "${NAME}.")
endfunction()

add_catch2_unit_test("catch2_cxxctp_test" "catch2_cxxctp_test.cpp")

add_gtest_unit_test("gtest_cxxctp_test" "gtest_cxxctp_test.cpp")

# We run our test from the source directory, so we can consistently
# load files with known paths.
# I also like color in my verbose output, so I put in a --force-colour flag.
#add_test(NAME cxxctp_test
#         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
#         COMMAND ${CMAKE_BINARY_DIR}/bin/cxxctp_test --force-colour)
