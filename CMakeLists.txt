cmake_minimum_required(VERSION 3.16)

project(IDEFY VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.8)

include_directories(yocto view util core)

set(PROJECT_SOURCES
        main.cpp        
        yocto/parser.hpp
        yocto/parser.cpp
        yocto/recipe.hpp
        yocto/layer.hpp
        yocto/configfile.hpp
        yocto/yoctoengine.hpp
        yocto/yoctoengine.cpp
        util/pathmatcher.hpp
        util/pathmatcher.cpp
        core/application.hpp
        core/application.cpp
)

qt_add_executable(IDEFY
    ${PROJECT_SOURCES}
)

qt_add_qml_module(IDEFY
    URI IDEFY
    VERSION 1.0
    QML_FILES
        qml/WindowDragHandler.qml
        qml/Editor.qml
        qml/FileSystemView.qml
)



# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(IDEFY PROPERTIES
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(IDEFY
    PRIVATE Qt6::Quick
)

include(GNUInstallDirs)
install(TARGETS IDEFY
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
