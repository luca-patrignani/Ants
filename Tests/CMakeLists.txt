cmake_minimum_required(VERSION 3.21)
project(provaCLion)

set(CMAKE_CXX_STANDARD 17)

add_executable(Tests main.cpp ../direction.h)
target_link_libraries(Tests user32 gdi32 opengl32 gdiplus Shlwapi dwmapi stdc++fs)
