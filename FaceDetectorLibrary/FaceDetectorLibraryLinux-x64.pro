#-------------------------------------------------
#
# Project created by QtCreator XXXX-XX-XX XX:XX:XX
#
#-------------------------------------------------

QT -= core
QT -= gui

CONFIG += c++11

TARGET = FaceDetectorLibrary

CONFIG += console
CONFIG -= app_bundle

#TEMPLATE = app
TEMPLATE = lib

MAIN = $$PWD/../

DESTDIR = $$MAIN/binary/Linux/x64

SOURCES +=                                                          \
        src/FaceDetector.cpp

DEFINES += FACEDETECTOR_LIBRARY

HEADERS += \
        include/FaceDetector.h

LIBS +=                                                             \
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
