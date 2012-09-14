cmake_minimum_required(VERSION 2.8.9)
project (Tutorial)

# The version number
set (Tutorial_VERSION_MAJOR 1)
set (Tutorial_VERSION_MINOR 0)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)

add_subdirectory(src)

message(ENV{CPPUTEST_HOME})

message("PROJECT_BINARY_DIR: ${PROJECT_BINARY_DIR}")
message("PROJECT_SOURCE_DIR: ${PROJECT_SOURCE_DIR}")
message("BUILD_SHARED_LIBS: ${BUILD_SHARED_LIBS}")
message("CMAKE_BINARY_DIR: ${CMAKE_BINARY_DIR}")
message("CMAKE_MODULE_PATH: ${CMAKE_MODULE_PATH}")
message("LIBRARY_OUTPUT_PATH: ${LIBRARY_OUTPUT_PATH}")
message("PROJECT_NAME: ${PROJECT_NAME}")
message("CMAKE_PROJECT_NAME: ${CMAKE_PROJECT_NAME}")
message("CMAKE_INCLUDE_PATH: ${CMAKE_INCLUDE_PATH}")
message("CMAKE_LIBRARY_PATH: ${CMAKE_LIBRARY_PATH}")
message("CMAKE_PREFIX_PATH: ${CMAKE_PREFIX_PATH}")
message("DESTDIR: ${DESTDIR}")
message("CMAKE_COMPILER_IS_GNUCC: ${CMAKE_COMPILER_IS_GNUCC}")
message("CMAKE_COMPILER_IS_GNUCXX: ${CMAKE_COMPILER_IS_GNUCXX}")

# variables
set(Foo a b c)
message(${Foo})

set(MultiLineString "this is 
a string with 
a newline in 
it")

message(${MultiLineString})

# loops
foreach(f ${Foo})
  message(${f})
endforeach(f)

# function have local scope
function(hello MESSAGE)
  message("Hello from function, ${MESSAGE}")
endfunction(hello)

hello("Davis")

# this macro definition will overwrite the function
# macros use global scope
macro(hello MESSAGE)
  message("Hello from macro, ${MESSAGE}")
endmacro(hello)

hello("Davis")

