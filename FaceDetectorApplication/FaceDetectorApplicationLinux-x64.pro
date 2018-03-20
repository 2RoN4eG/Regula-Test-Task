#-------------------------------------------------
#
# Project created by QtCreator XXXX-XX-XX XX:XX:XX
#
#-------------------------------------------------

QT -= core
QT -= gui

CONFIG += c++11

TARGET = FaceDetectorApplication

CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app
#TEMPLATE = lib

MAIN = $$PWD/../

DESTDIR = $$MAIN/binary/Linux/x64

HEADERS +=  $$MAIN/Tools/ThreadPool.h                               \
            src/Direcory.h                                          \
            src/JsonWriter.h

SOURCES +=  src/main.cpp                                            \
            src/Direcory.cpp                                        \
            src/JsonWriter.cpp

LIBS +=                                                             \
        -ldl                                                        \
        -lopencv_core                                               \
        -lopencv_imgproc                                            \
        -lopencv_highgui                                            \
        -lopencv_ml                                                 \
        -lopencv_video                                              \
        -lopencv_features2d                                         \
        -lopencv_calib3d                                            \
        -lopencv_objdetect                                          \
        -lopencv_legacy                                             \
        -lopencv_flann

INCLUDEPATH += $$MAIN
