cmake_minimum_required(VERSION 3.26)
project(Tetris_sfml)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML COMPONENTS system window graphics audio CONFIG REQUIRED)

add_executable(Tetris_sfml main.cpp
        "Headers and cpp files/Headers/BasePiece.h"
        "Headers and cpp files/Headers/O.h"
        "Headers and cpp files/cpp/O.cpp"
        "Headers and cpp files/cpp/BasePiece.cpp"
        "Headers and cpp files/Headers/I.h"
        "Headers and cpp files/cpp/I.cpp"
        "Headers and cpp files/Headers/J.h"
        "Headers and cpp files/cpp/J.cpp"
        "Headers and cpp files/Headers/L.h"
        "Headers and cpp files/cpp/L.cpp"
        "Headers and cpp files/Headers/T.h"
        "Headers and cpp files/cpp/T.cpp"
        "Headers and cpp files/cpp/S.cpp"
        "Headers and cpp files/Headers/S.h"
        "Headers and cpp files/cpp/Z.cpp"
        "Headers and cpp files/Headers/Z.h"
        "Headers and cpp files/cpp/functions.cpp"
        "Headers and cpp files/Headers/functions.h")
target_link_libraries(Tetris_sfml PRIVATE sfml-system sfml-network sfml-graphics sfml-window sfml-audio)