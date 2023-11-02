set(TEST_NAME unit_test)

# add executable
file(GLOB_RECURSE PROJECT_TEST_SRC_LIST ./*.cpp)
add_executable(${TEST_NAME} ${PROJECT_TEST_SRC_LIST})

# compile features
target_compile_features(${TEST_NAME} 
  PUBLIC cxx_std_17
)
# compile options
if (MSVC)
  target_compile_options(${TEST_NAME} 
    PUBLIC /utf-8
  )
  target_compile_options(${TEST_NAME} 
    PUBLIC /EHsc
  )
endif()

# link dependencies
set(Boost_NO_WARN_NEW_VERSIONS ON)
find_package(Boost REQUIRED COMPONENTS unit_test_framework)
if (Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
  target_link_libraries(${TEST_NAME} PRIVATE Boost::boost Boost::unit_test_framework)
endif ()

target_link_libraries(${TEST_NAME} PRIVATE ${PROJECT_NAME})

# add test
add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
