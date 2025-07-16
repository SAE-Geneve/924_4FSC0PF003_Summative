message("1_Tests CMake Build")

option(ENABLE_TESTING "Enable gtest" OFF)

if (ENABLE_TESTING)
    list(APPEND VCPKG_MANIFEST_FEATURES "testing")
endif (ENABLE_TESTING)

# Packages : external libraries managed by
file(GLOB_RECURSE SRC_FILES src/*.cc)
file(GLOB_RECURSE HEADER_FILES include/*.h)

if (ENABLE_TESTING)
    file(GLOB_RECURSE TEST_FILES tests/*.cc)
    add_executable(1_Tests_Tests ${TEST_FILES})
    target_include_directories(1_Tests_Tests PRIVATE include/)
    target_link_libraries(1_Tests_Tests PRIVATE GTest::gtest GTest::gtest_main)
endif (ENABLE_TESTING)

