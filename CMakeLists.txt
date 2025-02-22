
cmake_minimum_required(VERSION 3.5.0)

project(mini_base VERSION 1.0)


# Determine the platform.
if("${CMAKE_SYSTEM_NAME}" STREQUAL "Darwin")
  set(OS_MAC 1)
  set(OS_MACOSX 1)  # For backwards compatibility.
  set(OS_POSIX 1)
elseif("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
  set(OS_LINUX 1)
  set(OS_POSIX 1)
elseif("${CMAKE_SYSTEM_NAME}" STREQUAL "Windows")
  set(OS_WINDOWS 1)
endif()

# Append platform specific sources to a list of sources.
macro(APPEND_PLATFORM_SOURCES name_of_list)
  if(OS_LINUX AND ${name_of_list}_LINUX)
    list(APPEND ${name_of_list} ${${name_of_list}_LINUX})
  endif()
  if(OS_POSIX AND ${name_of_list}_POSIX)
    list(APPEND ${name_of_list} ${${name_of_list}_POSIX})
  endif()
  if(OS_WINDOWS AND ${name_of_list}_WINDOWS)
    list(APPEND ${name_of_list} ${${name_of_list}_WINDOWS})
  endif()
  if(OS_MAC AND ${name_of_list}_MAC)
    list(APPEND ${name_of_list} ${${name_of_list}_MAC})
  endif()
endmacro()

set(CMAKE_CXX_STANDARD 14)

add_compile_options(-Wno-deprecated-builtins -Wno-narrowing -Wno-deprecated-declarations -Wno-single-bit-bitfield-constant-conversion)

add_definitions(-D_FILE_OFFSET_BITS=64)

include(cmake/platform.cmake)

include_directories(${PROJECT_SOURCE_DIR}/)
include_directories(${PROJECT_SOURCE_DIR}/gen)


enable_language(ASM)

add_subdirectory(base)


add_executable(demo main.cc)

target_link_libraries(demo 
    base
    libevent
)

if(OS_LINUX)
  target_link_libraries(demo 
    -lpthread
	-static
  )
endif()
if(OS_MAC)
  target_link_libraries(demo 
    -lobjc
    "-framework Cocoa"
    "-framework Security"
  )
endif()
