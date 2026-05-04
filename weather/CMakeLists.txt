cmake_minimum_required(VERSION 3.10)

project(weather VERSION 1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 99)

# 🔎 Trouver les libs
find_package(CURL REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(JSONC REQUIRED json-c)

include_directories(
    ${CURL_INCLUDE_DIRS}
    ${JSONC_INCLUDE_DIRS}
)

# 🏗️ Build
add_executable(weather src/main.c)

target_link_libraries(weather
    ${CURL_LIBRARIES}
    ${JSONC_LIBRARIES}
)

# 📦 Installation
install(TARGETS weather DESTINATION /usr/local/bin)

# ========================
# 📦 CPack configuration
# ========================

set(CPACK_PACKAGE_NAME "weather")
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_PACKAGE_CONTACT "oussama@email.com")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "CLI weather tool in C")

# Debian specifics
set(CPACK_GENERATOR "DEB")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Oussama")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libcurl4, libjson-c5")
set(CPACK_DEBIAN_PACKAGE_SECTION "utils")

include(CPack)