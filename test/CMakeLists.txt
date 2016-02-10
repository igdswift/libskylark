find_package(Check)
if (NOT CHECK_FOUND)
  message(STATUS "Skipping unit tests, Check library not found!")
else (NOT CHECK_FOUND)
  include_directories(${CHECK_INCLUDE_DIRS})
  set(TEST_LIBS ${TEST_LIBS} ${CHECK_LIBRARIES} pthread curl skylark)
  # Check needs to be linked against Librt on Linux
  if (${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    set(TEST_LIBS ${TEST_LIBS} rt)
  endif(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
  include_directories("${PROJECT_SOURCE_DIR}/include")
  file(GLOB libskylark_test_SRCS check_*.c)
  add_executable(test_skylark ${libskylark_test_SRCS})
  target_link_libraries(test_skylark ${TEST_LIBS})
  add_custom_command(
    TARGET test_skylark POST_BUILD
    COMMENT "Running unit tests"
    COMMAND test_skylark
   )
endif (NOT CHECK_FOUND)
