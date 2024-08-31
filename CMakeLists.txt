cmake_minimum_required(VERSION 3.27)
project(oop-a10-Eduardismund)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_PREFIX_PATH "C:\\Qt\\6.5.5\\mingw_64\\lib\\cmake\\")

find_package(Qt6 COMPONENTS Widgets Core Gui
        REQUIRED)

add_executable(oop-a10-Eduardismund
        src/model/Dog.cpp
        src/model/Dog.h
        src/repository/RepoShelterDogs.cpp
        src/repository/RepoShelterDogs.h
        src/service/ServiceAdmin.h
        src/service/ServiceAdmin.cpp
        src/exception/Exception.h
        src/GUI/UserInterface.h
        src/GUI/UserInterface.cpp
        src/main/main.cpp
        src/tests/tests.h
        src/tests/tests.cpp
        src/repository/RepoAdoptedDogs.cpp
        src/repository/RepoAdoptedDogs.h
        src/service/ServiceUser.h
        src/service/ServiceUser.cpp
        libs/sqlite3.c
        libs/sqlite3.h
        libs/sqlite3.def
        libs/sqlite3.dll
        libs/sqlite3ext.h
        src/repository/DBRepository.cpp
        src/repository/DBRepository.cpp
        src/GUI/GUI.h
        src/GUI/GUI.cpp
        src/GUI/GUIUser.cpp
        src/action/Action.h
        src/GUI/TabelList.h
        src/GUI/TabelList.cpp
)

target_link_libraries(oop-a10-Eduardismund Qt::Widgets)

target_link_libraries(oop-a10-Eduardismund Qt::Widgets Qt::Core Qt::Gui)

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