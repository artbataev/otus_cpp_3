cmake_minimum_required(VERSION 3.2)

if($ENV{TRAVIS_BUILD_NUMBER})
    project(allocator VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER} LANGUAGES CXX)
else()
    project(allocator VERSION 0.0.1 LANGUAGES CXX)
endif()

set(CMAKE_CXX_STANDARD 14)
include_directories("${PROJECT_SOURCE_DIR}/include")

add_library(factorial src/factorial.cpp)
add_executable(allocator src/allocator.cpp)
target_link_libraries(allocator factorial)

find_package(GTest REQUIRED)
add_executable(test_allocator test/test_allocator.cpp)
add_executable(test_customlist test/test_customlist.cpp)
target_link_libraries(test_allocator ${GTEST_LIBRARIES})
target_link_libraries(test_customlist ${GTEST_LIBRARIES})
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    target_link_libraries(test_allocator pthread)
    target_link_libraries(test_customlist pthread)
endif()


install(TARGETS allocator RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT artbataev@gmail.com)

include(CPack)

enable_testing()
add_test(test test_allocator)
add_test(test test_customlist)
