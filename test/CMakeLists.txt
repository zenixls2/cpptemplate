find_package(Boost COMPONENTS system thread REQUIRED)
find_package(Threads REQUIRED)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include(ExternalProject)
set(gtest googletest_template)
ExternalProject_Add(${gtest}
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.8.0
    INSTALL_COMMAND "")
set(GTEST_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/${gtest}-prefox/src/${gtest}/googletest/include)
set(GTEST_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/${gtest}-prefox/src/${gtest}-build/googlemock)
set(TARGET
    ${GTEST_LIB_DIR}/gtest/libgtest_main.a}
    ${GTEST_LIB_DIR}/gtest/ligbtest.a
    Boost::system)
include_directories(BEFORE ${GTEST_INCLUDE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/../generated)

add_definitions(-O3 -mmmx -msse2 -msse3 -msse4.1 -msse4.2 -mavx -mavx2 -lm -ffast-math)
add_executable(test_example test.cpp)
target_link_libraries(test_example ${TARGE})
add_dependencies(test_example googletest_template)
