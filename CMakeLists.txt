cmake_minimum_required(VERSION 3.14)
project(GraphicsKernel LANGUAGES CXX)

include(FetchContent)

FetchContent_Declare(
    lab3_2ndsem
    GIT_REPOSITORY https://github.com/rodanuf/lab3_2ndsem
    GIT_TAG main
)

FetchContent_Declare(
    pointers
    GIT_REPOSITORY https://github.com/rodanuf/pointers
    GIT_TAG main
)

FetchContent_MakeAvailable(lab3_2ndsem pointers)

