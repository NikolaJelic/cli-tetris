cmake_minimum_required(VERSION 3.19)
project(cli-tetris)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++17 -lncurses")
# Add the required ncurses library.
add_executable(${PROJECT_NAME}  src/main.cpp 
src/tetromino.cpp
src/field.cpp
src/render.cpp)

set(CURSES_NEED_NCURSES TRUE)
find_package(Curses REQUIRED)
link_libraries(${CURSES_LIBRARIES})

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Werror=return-type)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

