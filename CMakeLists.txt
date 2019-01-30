# CMakeList.txt: 顶层 CMake 项目文件，在此处执行全局配置
# 并包含子项目。
#
cmake_minimum_required (VERSION 3.8)

project ("HLang")
SET(OUTDIR "${PROJECT_SOURCE_DIR}/build")
SET(FILE_SUFFIX ".${CMAKE_SYSTEM_PROCESSOR}")
MESSAGE( STATUS "PROJECT_NAME: " ${PROJECT_NAME} )
MESSAGE( STATUS "Outdir: " ${OUTDIR} )
MESSAGE( STATUS "ARCHITECTURES: " ${CMAKE_SYSTEM_PROCESSOR})
# 包含子项目。
add_subdirectory ("HLangDLL")
