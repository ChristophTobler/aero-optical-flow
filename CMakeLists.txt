cmake_minimum_required(VERSION 3.1)

project(aero-optical-flow)

find_package(OpenCV REQUIRED)
find_package(PythonLibs 2.7 REQUIRED)
find_package(PythonInterp 2.7 REQUIRED)
find_package(Threads REQUIRED)

set(MAVLINK_DIALECT common)

add_custom_command(
    OUTPUT mavlink-c-stamp
    COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_SOURCE_DIR}/modules/mavlink/pymavlink/tools/mavgen.py --lang=C --wire-protocol 2.0
            -o include/mavlink ${CMAKE_SOURCE_DIR}/modules/mavlink/message_definitions/v1.0/${MAVLINK_DIALECT}.xml
    COMMAND touch mavlink-c-stamp
)
add_custom_target(mavlink-c ALL DEPENDS mavlink-c-stamp)

add_subdirectory(modules/OpticalFlow)

add_executable(aero-optical-flow src/mainloop.cpp src/camera.cpp src/mavlink_udp.cpp src/spi.cpp src/bmi160.cpp src/main.cpp mavlink-c-stamp)
set_property(TARGET aero-optical-flow PROPERTY CXX_STANDARD 11)
set_property(TARGET aero-optical-flow PROPERTY COMPILE_FLAGS "-Wall -Wextra -Wshadow -Wundef -Wformat=2 -Wlogical-op -Wsign-compare -Wformat-security -Wformat-nonliteral -Wpointer-arith -Winit-self -Wmissing-noreturn -Wstrict-aliasing=2 -Wno-overlength-strings -Wno-missing-field-initializers -Wuninitialized")
target_include_directories(aero-optical-flow PUBLIC ${CMAKE_BINARY_DIR}/include/mavlink/${MAVLINK_DIALECT})
target_link_libraries(aero-optical-flow ${OpenCV_LIBS})
target_link_libraries(aero-optical-flow OpticalFlow)
target_link_libraries(aero-optical-flow pthread)
install(TARGETS aero-optical-flow DESTINATION bin)