cmake_minimum_required(VERSION 3.20)
project(ExplodingKittens C)

set(CMAKE_C_STANDARD 11)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

# Server: fara ncurses
add_executable(server server.c)
target_link_libraries(server pthread)

# Client: cu ncurses
add_executable(client client.c gui.c)
target_link_libraries(client ${CURSES_LIBRARIES})

# Demo GUI (date false, fara server)
add_executable(gui_demo gui.c)
target_compile_definitions(gui_demo PRIVATE GUI_DEMO)
target_link_libraries(gui_demo ${CURSES_LIBRARIES})
