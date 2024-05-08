cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

project(c-note)

set(SOURCE_FILES src/cppnote.cpp
  src/ui/mainwindow.cpp
)

find_package(Qt6 COMPONENTS Widgets Core REQUIRED)
qt_standard_project_setup()

qt_add_executable(cppnote ${SOURCE_FILES})

target_link_libraries(cppnote PRIVATE Qt6::Widgets Qt6::Core)

# Non-linux compatibility options
set_target_properties(cppnote PROPERTIES
  WIN32_EXECUTABLE ON
  MACOSX_BUNDLE ON
)
