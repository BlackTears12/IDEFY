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
        yocto/metadata.hpp
        yocto/yoctoengine.hpp
        yocto/yoctoengine.cpp
        util/pathmatcher.hpp
        util/pathmatcher.cpp
        core/application.hpp
        core/application.cpp
        core/metatypes.hpp
        core/qmlsingleton.hpp
)

qt_add_executable(IDEFY
    ${PROJECT_SOURCES}
)

set_source_files_properties(core/layermodel.hpp core/layermodel.cpp PROPERTIES QT_QML_SINGLETON_TYPE TRUE)

set_source_files_properties(qml/Colors.qml qml/Constants.qml PROPERTIES QT_QML_SINGLETON_TYPE TRUE)

qt_add_qml_module(IDEFY
    URI idefy
    VERSION 1.0
    QML_FILES
        qml/qmldir
        qml/qtquickcontrols2.conf
        qml/Colors.qml
        qml/Constants.qml
        qml/LayerExplorerView.qml
        qml/MainScreen.qml
        qml/Editor.qml
        qml/App.qml
    SOURCES
        core/layermodel.hpp core/layermodel.cpp
    RESOURCES
        qml/qmldir
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
