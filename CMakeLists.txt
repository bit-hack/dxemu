cmake_minimum_required(VERSION 3.0)
project(dxemu)

add_definitions(-D_CRT_SECURE_NO_WARNINGS)

file(GLOB SOURCE ddraw/*.cpp ddraw/*.h)
add_library(ddraw SHARED ${SOURCE})

file(GLOB SOURCE dinput/*.cpp dinput/*.h)
add_library(dinput SHARED ${SOURCE})
