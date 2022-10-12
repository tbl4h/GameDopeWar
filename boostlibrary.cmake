set(Boost_USE_STATIC_LIBS        ON)  # only find static libs
set(Boost_USE_DEBUG_LIBS         ON)  # ignore debug libs and
set(Boost_USE_RELEASE_LIBS       ON)  # only find release libs
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)
find_package(Boost 1.66.0  COMPONENTS system filesystem serialization REQUIRED)
if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
  # message(STATUS "BOOST INCLUDE DIR2: ${Boost_INCLUDE_DIRS}")
  #add_executable(foo foo.cc)
  #target_link_libraries(DrugGame ${Boost_LIBRARIES})
endif()