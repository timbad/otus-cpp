cmake_minimum_required(VERSION 3.12)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project(hw02 VERSION ${PROJECT_VESRION})

include_directories(../utils)

option(WITH_GTEST "Whether to build Google test" ON)

add_executable(ip_filter ip_filter.cpp ip_filter.h)

set_target_properties(ip_filter PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(ip_filter
    PRIVATE "${CMAKE_BINARY_DIR}"
)

if(WITH_GTEST)
    set(GOOGLETEST_DIR ../utils/googletest)
    add_subdirectory(${GOOGLETEST_DIR} build)

    add_executable(test_ip_filter test_ip_filter.cpp ip_filter.h)

    target_include_directories(test_ip_filter PRIVATE
        ${GOOGLETEST_DIR}/googletest/include
        ${GOOGLETEST_DIR}/googlemock/include
    )

    target_link_libraries(
        test_ip_filter
        gtest gtest_main gmock gmock_main
    )
endif()


if (MSVC)
    target_compile_options(ip_filter PRIVATE
        /W4
    )
    if(WITH_GTEST)
        target_compile_options(test_ip_filter PRIVATE
            /W4
        )
    endif()
else ()
    target_compile_options(ip_filter PRIVATE
        -Wall -Wextra -pedantic -Wunused-parameter
    )
    if(WITH_GTEST)
        target_compile_options(test_ip_filter PRIVATE
            -Wall -Wextra -pedantic -Werror
        )
    endif()
endif()

#install(TARGETS ip_filter RUNTIME DESTINATION bin)

if(WITH_GTEST)
    enable_testing()
    add_test(test_ip_filter test_ip_filter)
endif()