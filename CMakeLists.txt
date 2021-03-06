cmake_minimum_required(VERSION 3.15)
project(Wanderer)

#set(CMAKE_CXX_FLAGS "-std=c++17")

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
set(BINARIES_DIR ${PROJECT_SOURCE_DIR}/bin)
set(RESOURCES_DIR ${PROJECT_SOURCE_DIR}/resources)

# Names of targets
set(WANDERER_LIB ${PROJECT_NAME}_lib)
set(WANDERER_EXECUTABLE ${PROJECT_NAME}_exe)
set(WANDERER_TEST ${PROJECT_NAME}_test)

# Checks if an environment variable is defined.
#   envVar: the name of the actual environment variable.
#   name: the name of the library associated with the environment variable.
function(find_env_var [envVar [name]])
    if (DEFINED ENV{${ARGV0}})
        message("Found ${ARGV1} environment variable! Path: " $ENV{${ARGV0}})
    else ()
        message("Couldn't find environment variable ${ARGV0}!")
    endif ()
endfunction()

find_env_var(SDL2DIR SDL2)
find_env_var(SDL2IMAGEDIR SDL2_image)
find_env_var(SDL2MIXERDIR SDL2_mixer)
find_env_var(SDL2TTFDIR SDL2_ttf)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_ttf REQUIRED)

add_subdirectory(src)
add_subdirectory(test)