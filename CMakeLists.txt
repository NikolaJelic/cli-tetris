cmake_minimum_required(VERSION 3.19)


project(cli-tetris)
add_executable(${PROJECT_NAME}  src/main.cpp 
                                src/tetromino.cpp
                                src/field.cpp)

target_link_libraries(${PROJECT_NAME}
  PRIVATE ftxui::screen
  PRIVATE ftxui::dom
  PRIVATE ftxui::component 
)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Werror=return-type)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

