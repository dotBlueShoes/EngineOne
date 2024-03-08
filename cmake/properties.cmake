set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "CMake")

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
set(CMAKE_DISABLE_SOURCE_CHANGES ON)

# --- BUILD TYPES
set(BUILD_TYPE_AGN 0)
set(BUILD_TYPE_WIN 1)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    if (BUILD_TYPE EQUAL ${BUILD_TYPE_WIN})
        message("-- Build Type WINDOWS DEBUG")
    else()
        message("-- Build Type AGNOSTIC DEBUG")
    endif()
else() # Release
    if (BUILD_TYPE EQUAL ${BUILD_TYPE_WIN})
        message("-- Build Type WINDOWS RELEASE")
    else()
        message("-- Build Type AGNOSTIC RELEASE")
    endif()
endif()