# Set the proper directory
if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(LIB_PATHS "${CMAKE_SOURCE_DIR}/lib/glew/OSX")
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    set(LIB_PATHS "${CMAKE_SOURCE_DIR}/lib/glew/Win64")
endif ()

# Find the headers
find_path(GLEW_INCLUDE_DIR glew.h
        PATHS "${CMAKE_SOURCE_DIR}/lib/glew/include/GL")

find_path(GLEW_INCLUDE_DIR glxew.h
        PATHS "${CMAKE_SOURCE_DIR}/lib/glew/include/GL")

find_path(GLEW_INCLUDE_DIR wglew.h
        PATHS "${CMAKE_SOURCE_DIR}/lib/glew/include")

# Find the library
if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    # Windows doesn't automatically include both .lib and .dll
    if (MSVC)
        set(CMAKE_FIND_LIBRARY_SUFFIXES ".lib")
    else ()
        set(CMAKE_FIND_LIBRARY_SUFFIXES ".dll")
    endif ()
    find_library(GLEW_LIBRARY NAME glew PATHS ${LIB_PATHS})
else (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    find_library(GLEW_LIBRARY NAME glew PATHS ${LIB_PATHS})
endif (${CMAKE_SYSTEM_NAME} MATCHES "Windows")

# No compiler switches necessary
set(GLEW_DEFINITIONS "")

# Handle _FOUND tags and print success/failure
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(GLEW DEFAULT_MSG GLEW_LIBRARY GLEW_INCLUDE_DIR)

# Don't display in GUI
mark_as_advanced(GLEW_LIBRARY GLEW_INCLUDE_DIR)

# No dependencies, so proceed.
set(GLEW_INCLUDE_DIRS ${GLEW_INCLUDE_DIR})
set(GLEW_LIBRARIES ${GLEW_LIBRARY})
set(GLEW_DLL "${LIB_PATHS}/glew32.dll")