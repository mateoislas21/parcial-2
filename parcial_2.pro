QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

DEFINES += QCUSTOMPLOT_USE_LIBRARY
DEFINES += MUPARSERLIB_EXPORTS

QMAKE_CXXFLAGS += -Wa,-mbig-obj

SOURCES += \
    main.cpp \
    de_info_aprobada.cpp

HEADERS += \
    de_info_aprobada.h

FORMS += \
    de_info_aprobada.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

LIBS += -LC:\Qt_archi_grafics
LIBS += -lqcustomplotd2
LIBS += -lmuParserDLL
INCLUDEPATH += C:\Qt_archi_grafics

