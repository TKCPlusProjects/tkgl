string(TOUPPER ${PROJECT_NAME} PROJECT_NAME_TOUPPER)

# add library
file(GLOB_RECURSE PROJECT_BASE_INCLUDE_LIST include/**/*.hpp)
file(GLOB_RECURSE PROJECT_BASE_SRC_LIST src/**/*.cpp)
add_library(${PROJECT_NAME} STATIC
  ${PROJECT_BASE_INCLUDE_LIST}
  ${PROJECT_BASE_SRC_LIST}
)
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

# add include
target_include_directories(${PROJECT_NAME}
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

# compile definitions
if(BUILD_SHARED_LIBS AND WIN32)
  target_compile_definitions(${PROJECT_NAME}
    PRIVATE "${PROJECT_NAME_TOUPPER}_EXPORT=__declspec(dllexport)"
    INTERFACE "${PROJECT_NAME_TOUPPER}_EXPORT=__declspec(dllimport)")
endif()

# compile features
target_compile_features(${PROJECT_NAME} 
  PUBLIC cxx_std_17
)
# compile options
if (MSVC)
  target_compile_options(${PROJECT_NAME} 
    PUBLIC /utf-8
  )
  target_compile_options(${PROJECT_NAME} 
    PUBLIC /EHsc
  )
endif()

# link dependencies
find_package(glad CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC glad::glad)
find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC glfw)
find_package(glm CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC glm::glm)
find_package(tkcore CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC tkcore::tkcore)

# configure
configure_package_config_file(
  cmake/config.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake
  INSTALL_DESTINATION ${CMAKE_INSTALL_DATADIR}/${PROJECT_NAME}
  NO_SET_AND_CHECK_MACRO)
write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY SameMajorVersion)

# install
install(
  FILES
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake
  DESTINATION
    ${CMAKE_INSTALL_DATADIR}/${PROJECT_NAME}
)
install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}-targets)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(EXPORT ${PROJECT_NAME}-targets
  NAMESPACE ${PROJECT_NAME}::
  DESTINATION ${CMAKE_INSTALL_DATADIR}/${PROJECT_NAME}
)
