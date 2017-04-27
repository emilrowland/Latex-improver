cmake_minimum_required(VERSION 3.1)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMakeModules/")
project(LatexImprover)

#setup CPack
SET(CPACK_GENERATOR "DEB")
SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "Rowland Industries AB")
SET(CPACK_PACKAGE_CONTACT "Rowland Industries AB")
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Latex Improver")
SET(CPACK_PACKAGE_VENDOR "Rowland Industries AB")
INCLUDE(CPack)

include_directories(include)

#Select all c++ files
file(GLOB SOURCES "src/*.cpp")

add_executable(LatexImprover ${SOURCES})
target_compile_features(LatexImprover PRIVATE cxx_range_for)
install(TARGETS LatexImprover DESTINATION LatexImprover)
