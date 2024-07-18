cmake_minimum_required(VERSION 3.20)

# Project Settings
project(Game VERSION 0.1.0)

# Set C++ standard and required flag
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set Rpath
set(CMAKE_SKIP_BUILD_RPATH  FALSE)
set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
set(CMAKE_INSTALL_RPATH "\${ORIGIN}")

# Set directories
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/ext/rubyraylib")
set(THIRD_PARTY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third_party)

# set(OPENGL_VERSION "4.3")
# set(PLATFORM RGFW CACHE STRING "" FORCE)
# set(PLATFORM SDL CACHE STRING "" FORCE)

# Set up third-party libraries
set(LIBRARIES
  raylib
  raygui
  reasings
)

foreach(LIB ${LIBRARIES})
  set(LIB_DIR ${THIRD_PARTY_DIR}/${LIB})
  set(LIB_BUILD_DIR ${CMAKE_BINARY_DIR}/third_party/${LIB})

  add_subdirectory(${LIB_DIR})

  if(${LIB} STREQUAL "raylib")
    include_directories(${LIB_BUILD_DIR}/raylib/include)
    target_compile_definitions(${LIB} PRIVATE PLATFORM_DESKTOP_RGFW)
  else()
    include_directories(${LIB_BUILD_DIR}/include)
  endif()

  if(${LIB} STREQUAL "raygui")
    target_compile_definitions(${LIB} PRIVATE RAYGUI_IMPLEMENTATION)
  endif()
endforeach()

# Executable definition
file(GLOB SRC_FILES ${SRC_DIR}/*.cpp)
add_executable(game ${SRC_FILES})
set_target_properties(game PROPERTIES OUTPUT_NAME "raylib-cruby-${CMAKE_SYSTEM_PROCESSOR}")

add_dependencies(game ${LIBRARIES})

# Find Ruby
find_package(Ruby 3.3 REQUIRED)

# Set up include directories
target_include_directories(game
  PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${RUBY_INCLUDE_PATH}
)

# Set up link libraries
target_link_libraries(game PRIVATE ${LIBRARIES} ${RUBY_LIBRARY})

# Copy Ruby library to output directory
add_custom_command(TARGET game POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_if_different
  ${RUBY_LIBRARY}
  $<TARGET_FILE_DIR:game>
)
