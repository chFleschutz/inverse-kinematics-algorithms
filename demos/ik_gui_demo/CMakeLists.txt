project(ik-gui-demo)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
if (Qt6_FOUND)
    message(STATUS "Qt6 found version: ${Qt6_VERSION}")
    
    qt_standard_project_setup()

    qt_add_executable(ik-gui-demo
        IKMainWindow.cpp
        IKMainWindow.h
        IKMainWindow.ui
        main.cpp
    )

    target_link_libraries(ik-gui-demo PRIVATE 
        Qt6::Widgets
        ik-algorithms
    )

    set_target_properties(ik-gui-demo PROPERTIES
        WIN32_EXECUTABLE ON
        MACOSX_BUNDLE ON
    )
else()
    message(STATUS "Qt6 not found: Skipping Qt gui demo")
endif()
