cmake_minimum_required(VERSION 3.5)

project(maze VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(MAZE_TESTS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/tests)
set(MAZE_3D_PARTY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/3d_party)
set(MAZE_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(MAZE_EXE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(MAZE_MODEL_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/model)
set(MAZE_CONTROLLER_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/controller)
set(MAZE_VIEW_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/view)

set(MAZE_COVERAGE_LIBS "" CACHE STRING "")
set(MAZE_COVERAGE_FLAGS "" CACHE STRING "")
set(MAZE_WARNING_FLAGS "-Wall -Werror -Wextra" CACHE STRING "")
set(MAZE_STANDART_FLAGS "-std=c++17" CACHE STRING "")
set(MAZE_FLAGS "${MAZE_COVERAGE_FLAGS} ${MAZE_WARNING_FLAGS} ${MAZE_STANDART_FLAGS}")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${MAZE_FLAGS}")

include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}/view_autogen/include
  ${QT_INCLUDES}
  ${MAZE_SRC_DIR}
  ${MAZE_3D_PARTY_DIR}/mtlc/include/mtlc
  ${MAZE_3D_PARTY_DIR}/token_parser/include/token_parser
)

add_subdirectory(
  ${MAZE_3D_PARTY_DIR}/token_parser
  token_parser
)

set(MAZE_SOURCE_MODEL_LIB
  ${MAZE_MODEL_SOURCE_DIR}/model.h
  ${MAZE_MODEL_SOURCE_DIR}/model.cc
  ${MAZE_MODEL_SOURCE_DIR}/maze/maze.h
  ${MAZE_MODEL_SOURCE_DIR}/maze/maze.cc
  ${MAZE_MODEL_SOURCE_DIR}/maze/maze_importer.h
  ${MAZE_MODEL_SOURCE_DIR}/maze/maze_importer_txt.h
  ${MAZE_MODEL_SOURCE_DIR}/maze/maze_importer_txt.cc
  ${MAZE_MODEL_SOURCE_DIR}/maze/maze_exporter.h
  ${MAZE_MODEL_SOURCE_DIR}/maze/maze_exporter_txt.h
  ${MAZE_MODEL_SOURCE_DIR}/maze/maze_exporter_txt.cc
  ${MAZE_MODEL_SOURCE_DIR}/maze/factory_maze_importer.h
  ${MAZE_MODEL_SOURCE_DIR}/maze/factory_maze_importer.cc
  ${MAZE_MODEL_SOURCE_DIR}/maze/factory_maze_exporter.h
  ${MAZE_MODEL_SOURCE_DIR}/maze/factory_maze_exporter.cc
  ${MAZE_MODEL_SOURCE_DIR}/cave/cave.h
  ${MAZE_MODEL_SOURCE_DIR}/cave/cave.cc
  ${MAZE_MODEL_SOURCE_DIR}/cave/cave_exporter.h
  ${MAZE_MODEL_SOURCE_DIR}/cave/cave_exporter_txt.h
  ${MAZE_MODEL_SOURCE_DIR}/cave/cave_exporter_txt.cc
  ${MAZE_MODEL_SOURCE_DIR}/cave/cave_importer.h
  ${MAZE_MODEL_SOURCE_DIR}/cave/cave_importer_txt.h
  ${MAZE_MODEL_SOURCE_DIR}/cave/cave_importer_txt.cc
  ${MAZE_MODEL_SOURCE_DIR}/cave/factory_cave_exporter.h
  ${MAZE_MODEL_SOURCE_DIR}/cave/factory_cave_exporter.cc
  ${MAZE_MODEL_SOURCE_DIR}/cave/factory_cave_importer.h
  ${MAZE_MODEL_SOURCE_DIR}/cave/factory_cave_importer.cc
)

SET(MAZE_SOURCE_CONTROLLER_LIB
  ${MAZE_CONTROLLER_SOURCE_DIR}/controller.h
  ${MAZE_CONTROLLER_SOURCE_DIR}/controller_default.cc
  ${MAZE_CONTROLLER_SOURCE_DIR}/controller_default.h
)

SET(MAZE_SOURCE_VIEW_LIB
  ${MAZE_VIEW_SOURCE_DIR}/view.h
  ${MAZE_VIEW_SOURCE_DIR}/qt_view/qt_view.cc
  ${MAZE_VIEW_SOURCE_DIR}/qt_view/qt_view.h
  ${MAZE_VIEW_SOURCE_DIR}/qt_view/mainwindow.cc
  ${MAZE_VIEW_SOURCE_DIR}/qt_view/mainwindow.h
  ${MAZE_VIEW_SOURCE_DIR}/qt_view/mainwindow.ui
  ${MAZE_VIEW_SOURCE_DIR}/qt_view/widget_maze.h
  ${MAZE_VIEW_SOURCE_DIR}/qt_view/widget_maze.cc
  ${MAZE_VIEW_SOURCE_DIR}/qt_view/widget_cave.h
  ${MAZE_VIEW_SOURCE_DIR}/qt_view/widget_cave.cc
)

set(MAZE_SOURCE_EXE 
  ${MAZE_EXE_SOURCE_DIR}/main.cc
)

set(MAZE_SOURCE_TEST
  ${MAZE_TESTS_DIR}/tests.cc
  ${MAZE_TESTS_DIR}/model/cave/cave_test.h
  ${MAZE_TESTS_DIR}/model/cave/cave_test.cc
  ${MAZE_TESTS_DIR}/model/cave/constructors_test.cc
  ${MAZE_TESTS_DIR}/model/cave/export_test.cc
  ${MAZE_TESTS_DIR}/model/cave/import_test.cc
  ${MAZE_TESTS_DIR}/model/cave/next_iteration_test.cc
  ${MAZE_TESTS_DIR}/model/cave/set_random_test.cc
  ${MAZE_TESTS_DIR}/model/maze/perfect_maze.cc
  ${MAZE_TESTS_DIR}/model/maze/solution_maze.cc
  ${MAZE_TESTS_DIR}/model/maze/export_maze.cc
  ${MAZE_TESTS_DIR}/model/maze/import_maze.cc
  )

add_library(view STATIC ${MAZE_SOURCE_VIEW_LIB})
add_library(model STATIC ${MAZE_SOURCE_MODEL_LIB})
add_library(controller STATIC ${MAZE_SOURCE_CONTROLLER_LIB})
add_executable(maze ${MAZE_SOURCE_EXE})	
add_executable(maze_test ${MAZE_SOURCE_TEST})	

target_link_libraries(model
  token_parser
)

target_link_libraries(view
  Qt${QT_VERSION_MAJOR}::Widgets
)

target_link_libraries(maze
  model
  controller
  view
)

target_link_libraries(maze_test
  model
  gtest
  ${MAZE_COVERAGE_LIBS}
)
