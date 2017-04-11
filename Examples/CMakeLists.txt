set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5Core)

#qt5_add_resources(RESOURCE_FILES main.qrc)

add_library(ViveTrackerMock SHARED mock.cpp mock.h)

add_executable(ViveTest main.cpp main.qml  main.qrc ${RESOURCE_FILES} scenemodifier.cpp scenemodifier.h)

target_link_libraries(ViveTest ViveTrackerMock ViveTracker
        Qt5::Core Qt5::Gui Qt5::Qml Qt5::Quick Qt5::3DQuick Qt5::3DExtras Qt5::3DQuickExtras Qt5::OpenGL)