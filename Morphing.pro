#-------------------------------------------------
#
# Project created by QtCreator 2015-02-27T19:00:54
#
#-------------------------------------------------

QT       += core gui
QT       += widgets
TARGET = Morphing
TEMPLATE = app


SOURCES += main.cpp\
        morphing.cpp

HEADERS  += morphing.h

FORMS    += morphing.ui
INCLUDEPATH += /usr/local/include/opencv2
LIBS += -L/usr/local/lib
LIBS += -lopencv_core
LIBS += -lopencv_imgproc
LIBS += -lopencv_highgui
LIBS += -lopencv_ml
LIBS += -lopencv_video
LIBS += -lopencv_features2d
LIBS += -lopencv_calib3d
LIBS += -lopencv_objdetect
LIBS += -lopencv_contrib
LIBS += -lopencv_legacy
LIBS += -lopencv_flann
LIBS += -lopencv_nonfree
