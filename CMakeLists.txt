cmake_minimum_required(VERSION 3.5)

project(PKUGAME VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(QRC_SOURCE_FILES src.qrc)

file(GLOB_RECURSE QRC_SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src.qrc)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

SOURCE_GROUP("Resource Files" FILES ${QRC_SOURCE_FILES})

set(PROJECT_SOURCES
        main.cpp
        main_menu.cpp
        main_menu.h
        main_menu.ui
        activity.h
        activity.cpp
        activity.ui
        welcome_page.h
        welcome_page.cpp
        welcome_page.ui
        warning_page.h
        warning_page.cpp
        warning_page.ui
        text_page.h
        text_page.cpp
        text_page.ui
        thing.h
        thing.cpp
        thing.ui
        gameserver.cpp
        gameserver.h
        confirm.h
        confirm.cpp
        confirm.ui
        src.qrc
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(PKUGAME
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET PKUGAME APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(PKUGAME SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(PKUGAME
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(PKUGAME PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(PKUGAME PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS PKUGAME
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(PKUGAME)
endif()
