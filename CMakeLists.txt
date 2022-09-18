# ----------------------------------------------------------
# |                       WidgetTest                       |
# ----------------------------------------------------------
project(WidgetTest LANGUAGES C CXX)

cmake_minimum_required(VERSION 3.16)

find_package(wxWidgets REQUIRED)

FILE(GLOB_RECURSE CORE_SRC src/*.cpp)

add_executable(main ${CORE_SRC})

target_link_libraries(main PUBLIC ${wxWidgets_LIBRARIES})
target_include_directories(main PUBLIC ${wxWidgets_INCLUDE_DIRS})

target_compile_options(main PUBLIC ${wxWidgets_CXX_FLAGS})
target_compile_definitions(main PUBLIC ${wxWidgets_DEFINITIONS})

add_library(file_utils STATIC lib/act_reader.cpp lib/coord.cpp)
target_compile_options(file_utils PUBLIC "-lm")
target_compile_options(file_utils PUBLIC 
    $<$<OR:$<COMPILE_LANGUAGE:CXX>,$<COMPILE_LANGUAGE:CUDA>>: # Set flags if C++ or CUDA
    -Wall
    -Wextra
    -Wpedantic>)

add_executable(test lib/test.cpp)
target_link_libraries(test PUBLIC file_utils)
target_compile_options(test PUBLIC "-lm")
