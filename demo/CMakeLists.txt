set(DEMO_NAME demo)

# add executable
file(GLOB_RECURSE PROJECT_DEMO_INCLUDE_LIST ./*.hpp)
file(GLOB_RECURSE PROJECT_DEMO_SRC_LIST ./*.cpp)
add_executable(${DEMO_NAME} 
  ${PROJECT_DEMO_INCLUDE_LIST}
  ${PROJECT_DEMO_SRC_LIST}
)

# compile features
target_compile_features(${DEMO_NAME} 
  PUBLIC cxx_std_17
)

# link dependencies
target_link_libraries(${DEMO_NAME} PRIVATE ${PROJECT_NAME})
