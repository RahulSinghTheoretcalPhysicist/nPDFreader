cmake_minimum_required(VERSION 3.24)

project(PDFReader
    VERSION 0.1.0
    DESCRIPTION "Lightweight native PDF reader for Windows 11"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Qt6 6.11 REQUIRED COMPONENTS Widgets)
qt_standard_project_setup()

qt_add_executable(PDFReader WIN32
    src/main.cpp
    src/ui/MainWindow.cpp
    src/ui/MainWindow.h
    src/ui/DocumentCanvas.cpp
    src/ui/DocumentCanvas.h
)

target_link_libraries(PDFReader PRIVATE Qt6::Widgets)

target_compile_definitions(PDFReader PRIVATE
    PDFREADER_VERSION="${PROJECT_VERSION}"
)

if(MSVC)
    target_compile_options(PDFReader PRIVATE /W4 /permissive- /EHsc)
else()
    target_compile_options(PDFReader PRIVATE -Wall -Wextra -Wpedantic)
endif()

install(TARGETS PDFReader
    RUNTIME DESTINATION .
    BUNDLE DESTINATION .
)
