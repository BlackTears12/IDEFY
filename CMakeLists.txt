cmake_minimum_required(VERSION 3.16)

project(IDEFY VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

include_directories(yocto view util)

set(PROJECT_SOURCES
        main.cpp
        view/mainwindow.cpp
        view/mainwindow.hpp
        view/mainwindow.ui
        yocto/parser.hpp
        yocto/parser.cpp
        yocto/recipe.hpp
        yocto/layer.hpp
        yocto/configfile.hpp
        yocto/yoctoengine.hpp
        yocto/yoctoengine.cpp
)

qt_add_executable(IDEFY
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
    util/filematcher.hpp util/filematcher.cpp
)

target_link_libraries(IDEFY PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

target_compile_options(IDEFY PRIVATE -Wno-trigraphs)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.IDEFY)
endif()
set_target_properties(IDEFY PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS IDEFY
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(IDEFY)
endif()
