cmake_minimum_required(VERSION 3.30)
project(froglike-game)

set(CMAKE_CXX_STANDARD 20)

# Include the command that downloads libraries
include(FetchContent)

# define a function for adding git dependencies
function(include_dependency libName gitURL gitTag)
    # setup the declare
    FetchContent_Declare(${libName}
            GIT_REPOSITORY ${gitURL}
            GIT_TAG ${gitTag}
            GIT_SHALLOW TRUE
            GIT_PROGRESS TRUE
    )

    FetchContent_MakeAvailable(${libName})
endfunction()

# add raylib support
set(LIB1 raylib)
find_package(${LIB1} QUIET)
if (NOT ${LIB1}_FOUND)
    message(STATUS "Getting ${LIB1} from Github")
    include_dependency(${LIB1} https://github.com/raysan5/raylib.git 5.5)
else ()
    message(STATUS "Using local ${LIB1}")
endif ()

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
)

# set the include directory
target_include_directories(froglike_game PRIVATE ${raylib_INCLUDE_DIRS})

# link all libraries to the project
target_link_libraries(froglike_game PRIVATE ${LIB1})