cmake_minimum_required(VERSION 3.30)

project(monkey_typer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXE_LINKER_FLAGS "-mconsole")
set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH}:/opt/homebrew/opt/sfml@2:/opt/homebrew/opt/fmt")
set(SFML_DIR "/opt/homebrew/Cellar/sfml@2/2.6.2_1/lib/cmake/SFML")

find_package(SFML 2 REQUIRED COMPONENTS graphics window system)

find_package(fmt CONFIG REQUIRED)

add_executable(monkey_typer
        src/main.cpp
        src/Slowo.cpp
        src/Gra.cpp
        src/Gra.h
        src/Konfiguracje.cpp
        src/Konfiguracje.h
        src/Menu.cpp
        src/Menu.h
        src/Instrukcje.h
        src/Instrukcje.cpp
)

add_custom_command(TARGET monkey_typer POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/dane $<TARGET_FILE_DIR:monkey_typer>/dane)


target_link_libraries(monkey_typer PRIVATE
        sfml-graphics
        sfml-window
        sfml-system
        sfml-audio
        fmt::fmt)
