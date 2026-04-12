cmake_minimum_required(VERSION 3.16)

project(lab5 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        # Класс брони (структура, только заголовок)
        Armor.h
        
        # Родительский класс NPC
        NPC.h
        NPC.cpp
        
        # Наследник 1 - Маг
        Magician.h
        Magician.cpp
        
        # Наследник 2 - Враг
        Enemy.h
        Enemy.cpp
        
        # Диалог информации
        InfoDialog.h
        InfoDialog.cpp
        InfoDialog.ui
        # ↑↑↑ InfoDialog.ui добавлен сюда ↑↑↑
        
        # Главное окно
        MainWindow.h
        MainWindow.cpp
        MainWindow.ui
        
        # Точка входа
        main.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(lab5
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(lab5 SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(lab5
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(lab5 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Настройка для iOS/macOS
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.lab5)
endif()

set_target_properties(lab5 PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS lab5
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Копирование файла с данными в директорию сборки
if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/data.txt)
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/data.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
endif()

# Копирование папки с изображениями в директорию сборки
if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/images)
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/images DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
endif()

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(lab5)
endif()