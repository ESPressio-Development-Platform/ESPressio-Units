cmake_minimum_required(VERSION 3.13)
project(ESPressioUnitsTests LANGUAGES CXX)

option(ESPRESSIO_ENABLE_COVERAGE "Enable source coverage instrumentation" OFF)
option(ESPRESSIO_ENABLE_SANITIZERS "Enable address and undefined-behavior sanitizers" OFF)

set(ESPRESSIO_TEST_TARGETS
    espressio_units_tests
    espressio_conversion_tests
)

add_executable(espressio_units_tests test_units.cpp)
add_executable(espressio_conversion_tests test_conversions.cpp)

foreach(TEST_TARGET IN LISTS ESPRESSIO_TEST_TARGETS)
    target_include_directories(${TEST_TARGET} PRIVATE stubs ../src)
    target_compile_features(${TEST_TARGET} PRIVATE cxx_std_11)
endforeach()

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    foreach(TEST_TARGET IN LISTS ESPRESSIO_TEST_TARGETS)
        target_compile_options(${TEST_TARGET} PRIVATE
            -Wall -Wextra -Wpedantic -Werror
        )
    endforeach()
elseif(MSVC)
    foreach(TEST_TARGET IN LISTS ESPRESSIO_TEST_TARGETS)
        target_compile_options(${TEST_TARGET} PRIVATE /W4 /WX)
    endforeach()
endif()

if(ESPRESSIO_ENABLE_COVERAGE)
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        foreach(TEST_TARGET IN LISTS ESPRESSIO_TEST_TARGETS)
            target_compile_options(${TEST_TARGET} PRIVATE -O0 -g --coverage)
            target_link_options(${TEST_TARGET} PRIVATE --coverage)
        endforeach()
    else()
        message(FATAL_ERROR "Coverage is supported only with GCC or Clang")
    endif()
endif()

if(ESPRESSIO_ENABLE_SANITIZERS)
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        foreach(TEST_TARGET IN LISTS ESPRESSIO_TEST_TARGETS)
            target_compile_options(${TEST_TARGET} PRIVATE
                -fsanitize=address,undefined -fno-omit-frame-pointer
            )
            target_link_options(${TEST_TARGET} PRIVATE
                -fsanitize=address,undefined
            )
        endforeach()
    else()
        message(FATAL_ERROR "Sanitizers are supported only with GCC or Clang")
    endif()
endif()

enable_testing()
add_test(NAME espressio_units_tests COMMAND espressio_units_tests)
add_test(NAME espressio_conversion_tests COMMAND espressio_conversion_tests)
