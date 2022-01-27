cmake_minimum_required(VERSION 3.21)
project(provaCLion)

set(CMAKE_CXX_STANDARD 17)

add_executable(provaCLion olcPixelGameEngine.h ant.h map.h main.cpp olcPixelGameEngine.cpp army.h direction.h Tests/main.cpp)
target_link_libraries(provaCLion user32 gdi32 opengl32 gdiplus Shlwapi dwmapi stdc++fs)

