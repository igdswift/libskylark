set(CMAKE_C_FLAGS "-Wmissing-prototypes ${CMAKE_C_FLAGS}")

include_directories("${PROJECT_SOURCE_DIR}/include")
file(GLOB libskylark_HEADERS "${PROJECT_SOURCE_DIR}/include/libskylark/*.h")
file(GLOB libskylark_SRCS "${PROJECT_SOURCE_DIR}/src/*.c")

add_library(skylark STATIC ${libskylark_SRCS})
install(FILES ${libskylark_HEADERS} DESTINATION include)
install(TARGETS skylark DESTINATION lib)

if(BUILD_SHARED_LIBS)
  add_library(skylark SHARED ${libskylark_SRCS})
  install(FILES ${libskylark_HEADERS} DESTINATION include)
  install(TARGETS skylark DESTINATION lib)
else(BUILD_SHARED_LIBS)
  message(STATUS "Not building shared libraries")
endif(BUILD_SHARED_LIBS)

link_directories("$ENV{HOME}/.local/lib")
include_directories("$ENV{HOME}/.local/include")

add_executable(sky-connect "${PROJECT_SOURCE_DIR}/src/sky-connect.c")
target_link_libraries(sky-connect skylark curl serialport)
install(TARGETS sky-connect DESTINATION bin)
