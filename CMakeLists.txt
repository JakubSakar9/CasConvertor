cmake_minimum_required(VERSION 3.26)
project(CasConvertor)

set(CMAKE_CXX_STANDARD 23)

add_executable(CasConvertor application.cpp
        formats/wav.cpp
        formats/wav.h
        formats/cas.cpp
        formats/cas.h
        atari/standard/atari_standard_wave.cpp
        atari/standard/atari_standard_wave.h
        defines.h
        auxiliary/log.h
)
