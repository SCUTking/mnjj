QT       += core gui
QT += charts
QT += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    airtwo.cpp \
    choose_city.cpp \
    dehumidifier.cpp \
    designair.cpp \
    designbed.cpp \
    designcase.cpp \
    designdesk.cpp \
    designdinuan.cpp \
    designnewwind.cpp \
    designroom.cpp \
    designscene.cpp \
    designtv.cpp \
    fridge.cpp \
    humidifier.cpp \
    humimage.cpp \
    main.cpp \
    allmain.cpp \
    mainscene.cpp \
    mypushbutton.cpp \
    mytoolbutton.cpp \
    object.cpp \
    qualityimage.cpp \
    season.cpp \
    temimage.cpp \
    unitqlinedit.cpp

HEADERS += \
    airtwo.h \
    allmain.h \
    choose_city.h \
    dehumidifier.h \
    designair.h \
    designbed.h \
    designcase.h \
    designdesk.h \
    designdinuan.h \
    designnewwind.h \
    designroom.h \
    designscene.h \
    designtv.h \
    fridge.h \
    humidifier.h \
    humimage.h \
    mainscene.h \
    mypushbutton.h \
    mytoolbutton.h \
    object.h \
    qualityimage.h \
    season.h \
    temimage.h \
    unitqlinedit.h

FORMS += \
    airtwo.ui \
    allmain.ui \
    choose_city.ui \
    dehumidifier.ui \
    designair.ui \
    designbed.ui \
    designcase.ui \
    designdesk.ui \
    designdinuan.ui \
    designnewwind.ui \
    designroom.ui \
    designscene.ui \
    designtv.ui \
    fridge.ui \
    humidifier.ui \
    humimage.ui \
    mainscene.ui \
    qualityimage.ui \
    season.ui \
    temimage.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
