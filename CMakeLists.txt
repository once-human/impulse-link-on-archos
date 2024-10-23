cmake_minimum_required(VERSION 3.10)
project(ImpulseLink)

set(CMAKE_CXX_STANDARD 17)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK4 REQUIRED gtk4)
pkg_check_modules(CURL REQUIRED libcurl)
pkg_check_modules(NOTIFY REQUIRED libnotify)

include_directories(${GTK4_INCLUDE_DIRS} ${CURL_INCLUDE_DIRS} ${NOTIFY_INCLUDE_DIRS} include)

add_executable(impulse_link
    src/main.cpp
    src/gui/main_window.cpp
    src/http_server/server.cpp
    src/http_server/request_handler.cpp
    src/models/file_model.cpp
    src/models/notification_model.cpp
)

target_link_libraries(impulse_link ${GTK4_LIBRARIES} ${CURL_LIBRARIES} ${NOTIFY_LIBRARIES})
