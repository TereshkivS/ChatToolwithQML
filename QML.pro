TEMPLATE = subdirs

SUBDIRS += \
    Client \
    Common/socketreadwrite/socketreadwrite \
    Server

contains(QMAKE_TARGET.arch, x86_64) {
    PLATFORM = x64
} else {
    PLATFORM = win32
}

CONFIG(release, debug|release) {
    BUILD_TYPE = Release
} else {
    BUILD_TYPE = Debug
}

DELIVERY_PATH = $$PWD/delivery/$${PLATFORM}/$${BUILD_TYPE}/
EXTERNS_PATH = $$PWD/externs
