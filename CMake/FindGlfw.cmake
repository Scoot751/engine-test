# Set the proper directory
if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(LIB_PATHS "${CMAKE_SOURCE_DIR}/lib/glfw/OSX")
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    set(LIB_PATHS "${CMAKE_SOURCE_DIR}/lib/glfw/Win64")
endif ()

# Find the headers
find_path(GLFW_INCLUDE_DIR glfw3.h
        PATHS "${CMAKE_SOURCE_DIR}/lib/glfw/include/GLFW")

find_path(GLFW_INCLUDE_DIR glfw3native.h
        PATHS "${CMAKE_SOURCE_DIR}/lib/glfw/include/GLFW")

# Find the library
if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    # Windows doesn't automatically include both .lib and .dll
    if (MSVC)
        set(CMAKE_FIND_LIBRARY_SUFFIXES ".lib")
    else ()
        set(CMAKE_FIND_LIBRARY_SUFFIXES ".dll")
    endif ()
    find_library(GLFW_LIBRARY NAME glfw PATHS ${LIB_PATHS})
else (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    find_library(GLFW_LIBRARY NAME glfw PATHS ${LIB_PATHS})
endif (${CMAKE_SYSTEM_NAME} MATCHES "Windows")

# No compiler switches necessary
set(GLFW_DEFINITIONS "")

# Handle _FOUND tags and print success/failure
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(GLFW DEFAULT_MSG GLFW_LIBRARY GLFW_INCLUDE_DIR)

# Don't display in GUI
mark_as_advanced(GLFW_LIBRARY GLFW_INCLUDE_DIR)

# No dependencies, so proceed.
set(GLFW_INCLUDE_DIRS ${GLFW_INCLUDE_DIR})
set(GLFW_LIBRARIES ${GLFW_LIBRARY})
set(GLFW_DLL "${LIB_PATHS}/glfw3.dll")