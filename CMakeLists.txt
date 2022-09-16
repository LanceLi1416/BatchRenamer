cmake_minimum_required(VERSION 3.23)
project(BatchRenamer VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if (WIN32)
    set(CMAKE_PREFIX_PATH "D:/Qt/6.2.4/msvc2019_64/lib/cmake")
elseif (APPLE)
    set(CMAKE_PREFIX_PATH "/Applications/Qt/6.2.4/macos")
endif ()

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(BatchRenamer
        main.cpp
        enums.h
        Core.h
        Core/find_and_replace.cpp
        Core/find_and_replace.h
        Core/number.cpp
        Core/number.h
        Core/set_extension.cpp
        Core/set_extension.h
        Widgets/BatchRenamer.cpp
        Widgets/BatchRenamer.h
        Widgets/brFindAndReplace.cpp
        Widgets/brFindAndReplace.h
        Widgets/brNumber.cpp
        Widgets/brNumber.h
        Widgets/brRemoveText.cpp
        Widgets/brRemoveText.h
        Widgets/brSetExtension.cpp
        Widgets/brSetExtension.h
        Widgets/Pallet.hpp
        Widgets/Spacer.cpp
        Widgets/Spacer.h)

target_link_libraries(BatchRenamer PRIVATE
        Qt::Core
        Qt::Gui
        Qt::Widgets
        )

if (WIN32)
    set(DEBUG_SUFFIX)
    if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif ()
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif ()
    endif ()
    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif ()
    foreach (QT_LIB Core Gui Widgets)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt6${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)
endif ()
