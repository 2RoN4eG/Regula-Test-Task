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

TEMPLATE = lib

MAIN = $$PWD/../

DESTDIR = $$MAIN/binary/Windows/x86

SOURCES +=                                                          \
        src/FaceDetector.cpp

DEFINES += FACEDETECTOR_LIBRARY

HEADERS += \
        include/FaceDetector.h

INCLUDEPATH +=                                                      \
        $$MAIN/                                                     \
        $$MAIN/OpenCV/build/include/

LIBS +=                                                             \
        -L$$MAIN/OpenCV/build/lib/                                  \
        -lopencv_core2413                                           \
        -lopencv_imgproc2413                                        \
        -lopencv_highgui2413                                        \
        -lopencv_ml2413                                             \
        -lopencv_video2413                                          \
        -lopencv_features2d2413                                     \
        -lopencv_calib3d2413                                        \
        -lopencv_objdetect2413                                      \
        -lopencv_legacy2413                                         \
        -lopencv_flann2413

DEFINES -= UNICODE

QMAKESPEC += -static-libgcc -Wl,-Bstatic -lstdc++
