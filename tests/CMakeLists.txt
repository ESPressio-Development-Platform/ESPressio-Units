cmake_minimum_required(VERSION 3.13)
project(ESPressioUnitsTests LANGUAGES CXX)

option(ESPRESSIO_ENABLE_COVERAGE "Enable source coverage instrumentation" OFF)
option(ESPRESSIO_ENABLE_SANITIZERS "Enable address and undefined-behavior sanitizers" OFF)

add_executable(espressio_units_tests test_units.cpp)
target_include_directories(espressio_units_tests PRIVATE
    stubs
    ../src
)
target_compile_features(espressio_units_tests PRIVATE cxx_std_11)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(espressio_units_tests PRIVATE
        -Wall -Wextra -Wpedantic -Werror
    )
elseif(MSVC)
    target_compile_options(espressio_units_tests PRIVATE /W4 /WX)
endif()

if(ESPRESSIO_ENABLE_COVERAGE)
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        target_compile_options(espressio_units_tests PRIVATE -O0 -g --coverage)
        target_link_options(espressio_units_tests PRIVATE --coverage)
    else()
        message(FATAL_ERROR "Coverage is supported only with GCC or Clang")
    endif()
endif()

if(ESPRESSIO_ENABLE_SANITIZERS)
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        target_compile_options(espressio_units_tests PRIVATE
            -fsanitize=address,undefined -fno-omit-frame-pointer
        )
        target_link_options(espressio_units_tests PRIVATE
            -fsanitize=address,undefined
        )
    else()
        message(FATAL_ERROR "Sanitizers are supported only with GCC or Clang")
    endif()
endif()

enable_testing()
add_test(NAME espressio_units_tests COMMAND espressio_units_tests)
