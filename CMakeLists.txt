cmake_minimum_required(VERSION 3.30.5)
project(froglike-game)

set(CMAKE_CXX_STANDARD 20)

# Include the command that downloads libraries
include(FetchContent)

function(fetch_dependency libName gitURL gitTag)
    FetchContent_Declare(${libName}
            GIT_REPOSITORY ${gitURL}
            GIT_TAG ${gitTag}
            GIT_SHALLOW TRUE
            GIT_PROGRESS TRUE
    )

    FetchContent_GetProperties(${libName})
    if (NOT ${libName}_POPULATED)
        foreach (arg IN LISTS ARGN)
            if (arg MATCHES "([^=]+)=(.*)")
                set(${CMAKE_MATCH_1} ${CMAKE_MATCH_2})
            endif ()
        endforeach ()
    endif ()

    FetchContent_MakeAvailable(${libName})
endfunction()

function(add_dependency libName gitURL gitTag)
    find_package(${libName} QUIET)
    if (NOT ${libName}_FOUND)
        message(STATUS "Getting ${libName} from Github")
        fetch_dependency(${libName} ${gitURL} ${gitTag} ${ARGN})
    else ()
        message(STATUS "Using local ${libName}")
    endif ()
endfunction()

# add raylib support
add_dependency(raylib https://github.com/raysan5/raylib.git 5.5)
# add tileson support
add_dependency(tmxlite https://github.com/fallahn/tmxlite v1.4.4 TMXLITE_STATIC_LIB=TRUE)

add_executable(froglike_game src/main.cpp
        src/force/force.h
        src/force/force.cpp
        src/object/hero.h
        src/object/hero.cpp
        src/object/enemy.cpp
        src/object/enemy.h
        src/object/object.cpp
        src/object/object.h
        src/animation/animation.cpp
        src/animation/animation.h
        src/object/status.h
        src/object/type.h
        src/object/side.h
        src/animation/sprite.h
        src/environment/tilemap.cpp
        src/environment/tilemap.h
        src/environment/layerType.h
)

# link all libraries to the project
add_subdirectory(${CMAKE_BINARY_DIR}/_deps/tmxlite-src/tmxlite)
target_link_libraries(froglike_game PRIVATE raylib tmxlite)