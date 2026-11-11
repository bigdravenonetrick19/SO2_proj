cmake_minimum_required(VERSION 3.20)
project(ExplodingKittens C)

set(CMAKE_C_STANDARD 11)

# Adăugăm biblioteca ncurses
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

# Cream executabilul pentru Server
add_executable(server server.c
        server.c)
target_link_libraries(server ${CURSES_LIBRARIES} pthread)


