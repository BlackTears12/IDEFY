cmake_minimum_required(VERSION 3.16)

project(IDEFY VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Quick QuickControls2 Svg)

qt_standard_project_setup(REQUIRES 6.8)

include_directories(yocto view util core)

set(SINGLETON_SOURCES
    core/layermodel.hpp core/layermodel.cpp
    util/fileutil.hpp util/fileutil.cpp
    util/alertmanager.hpp util/alertmanager.cpp
    yocto/yoctoengine.hpp yocto/yoctoengine.cpp
)

set(PROJECT_SOURCES
        main.cpp        
        yocto/parser.hpp
        yocto/parser.cpp
        yocto/recipe.hpp
        yocto/layer.hpp
        yocto/metadata.hpp        
        util/pathmatcher.hpp
        util/pathmatcher.cpp
        core/application.hpp
        core/application.cpp
        core/metatypes.hpp
        core/qmlsingleton.hpp
        ${SINGLETON_SOURCES}
)

qt_add_executable(IDEFY
    ${PROJECT_SOURCES}
)

set_source_files_properties(qml/Colors.qml qml/Constants.qml ${SINGLETON_SOURCES} PROPERTIES QT_QML_SINGLETON_TYPE TRUE)

qt_add_qml_module(IDEFY
    URI idefy
    VERSION 1.0
    QML_FILES
        qml/Main.qml
        qml/Colors.qml
        qml/Constants.qml
        qml/LayerExplorerView.qml
        qml/MyMenuBar.qml
        qml/Editor.qml
        qml/Sidebar.qml
        qml/MyMenu.qml
        qml/WindowDragHandler.qml

    SOURCES
        ${SINGLETON_SOURCES}
        core/linenumbermodel.hpp core/linenumbermodel.cpp
        RESOURCES icons/folder_closed.svg
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
    PRIVATE
        Qt6::Core
        Qt6::Gui
        Qt6::Quick
        Qt6::QuickControls2
        Qt6::Svg
)

include(GNUInstallDirs)
install(TARGETS IDEFY
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

qt_generate_deploy_qml_app_script(
    TARGET IDEFY
    OUTPUT_SCRIPT deploy_script
    MACOS_BUNDLE_POST_BUILD
    NO_UNSUPPORTED_PLATFORM_ERROR
    DEPLOY_USER_QML_MODULES_ON_UNSUPPORTED_PLATFORM
)
install(SCRIPT ${deploy_script})
