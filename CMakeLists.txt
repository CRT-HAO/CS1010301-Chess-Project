project(Chess C CXX)

cmake_minimum_required(VERSION 3.18)

set(SRC_DIR "src")
set(CMAKE_DIR "cmake")
set(INCLUDE_DIR "include")
set(APP_NAME ${CMAKE_PROJECT_NAME})

if(MSVC)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

add_compile_definitions("DEBUG=$<CONFIG:Debug>")

include(${CMAKE_DIR}/Ultralight.cmake)

include_directories(BEFORE ${INCLUDE_DIR})

set(CHESS_SOURCES
    ${SRC_DIR}/core/Board.cpp
    ${SRC_DIR}/core/MoveHandler.cpp
    ${SRC_DIR}/core/Game.cpp
    ${SRC_DIR}/gui/Inspector.cpp
    ${SRC_DIR}/gui/GUI.cpp)

add_library(ChessCore SHARED ${CHESS_SOURCES})

set(MAIN_SOURCES ${SRC_DIR}/main.cpp)

if(PORT MATCHES "UltralightLinux")
    SET(CMAKE_SKIP_BUILD_RPATH FALSE)
    SET(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
    SET(CMAKE_INSTALL_RPATH "$\{ORIGIN\}")
endif()

if(PORT MATCHES "UltralightMac")
    SET(CMAKE_SKIP_BUILD_RPATH FALSE)
    SET(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
    SET(CMAKE_INSTALL_RPATH "@executable_path/")
endif()

# add_executable(${APP_NAME} MACOSX_BUNDLE ${MAIN_SOURCES})
add_executable(${APP_NAME} WIN32 MACOSX_BUNDLE ${MAIN_SOURCES})
target_link_libraries(${APP_NAME} PRIVATE ChessCore)

if(APPLE)
    # Copy ChessCore library to build bundle
    add_custom_command(TARGET ${APP_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy "*ChessCore.*" $<TARGET_FILE_DIR:${APP_NAME}>)
endif()

if(APPLE)
    # Enable High-DPI on macOS through our custom Info.plist template
    set_target_properties(${APP_NAME} PROPERTIES MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/cmake/Info.plist.in)
endif()

if(MSVC)
    # Tell MSVC to use main instead of WinMain for Windows subsystem executables
    set_target_properties(${APP_NAME} PROPERTIES LINK_FLAGS "/ENTRY:mainCRTStartup")
endif()

# Copy all binaries to target directory
add_custom_command(TARGET ${APP_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${ULTRALIGHT_BINARY_DIR}" $<TARGET_FILE_DIR:${APP_NAME}>)

# Set the assets path to "/assets" or "/../Resources/assets" on macOS
if(APPLE)
    set(ASSETS_PATH "$<TARGET_FILE_DIR:${APP_NAME}>/../Resources/assets")
else()
    set(ASSETS_PATH "$<TARGET_FILE_DIR:${APP_NAME}>/assets")
endif()

# Copy assets to assets path
add_custom_command(TARGET ${APP_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/assets/" "${ASSETS_PATH}")

if(${ENABLE_INSPECTOR})
    # Copy inspector to assets directory
    add_custom_command(TARGET ${APP_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory "${ULTRALIGHT_INSPECTOR_DIR}" "${ASSETS_PATH}/inspector")
endif()

# Copy resources to assets directory
add_custom_command(TARGET ${APP_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${ULTRALIGHT_RESOURCES_DIR}" "${ASSETS_PATH}/resources")

add_dependencies(${APP_NAME} UltralightSDK)