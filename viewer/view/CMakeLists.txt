cmake_minimum_required(VERSION 3.16.3)
project(viewer_front)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 COMPONENTS Widgets PrintSupport OpenGLWidgets Gui REQUIRED)
qt6_add_resources(QT_RESOURCES qrc/qrc.qrc)

include_directories(
        ${CMAKE_SOURCE_DIR}/QtGifImage
        ${CMAKE_SOURCE_DIR}/QtGifImage/giflib
)

set(PROJECT_SOURCES
        #front
        main.cc
        gl_widget.cc
        gl_widget.h
        mainwindow.cc
        mainwindow.h
        mainwindow.ui
        file_operations.cc
        settings_operations.cc

        QtGifImage/giflib/dgif_lib.c
        QtGifImage/giflib/egif_lib.c
        QtGifImage/giflib/gif_err.c
        QtGifImage/giflib/gif_lib.h
        QtGifImage/giflib/gif_hash.c
        QtGifImage/giflib/gifalloc.c
        QtGifImage/giflib/quantize.c
        QtGifImage/qgifglobal.h
        QtGifImage/qgifimage.h
        QtGifImage/qgifimage_p.h
        QtGifImage/qgifimage.cpp

        #back
        "../model/obj_model.cc"
        "../model/obj_model.h"
        "../controller/obj_controller.cc"
        "../controller/obj_controller.h"
        "../controller/camera_controller.cc"
        "../controller/camera_controller.h"
        ../model/camera_model.cc
        ../model/camera_model.h
)

qt_add_executable(viewer_front
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        ${QT_RESOURCES}
)

target_link_libraries(viewer_front PRIVATE Qt6::PrintSupport)
target_link_libraries(viewer_front PRIVATE Qt6::Widgets)
target_link_libraries(viewer_front PRIVATE Qt6::OpenGLWidgets)
target_link_libraries(viewer_front PRIVATE Qt6::Gui)


qt_finalize_executable(viewer_front)

