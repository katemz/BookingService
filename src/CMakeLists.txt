set(BINARY ${CMAKE_PROJECT_NAME})

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.hpp *.cpp)

set(SOURCES ${SOURCES})

add_executable(${BINARY}_run ${SOURCES})

add_library(${BINARY}_lib STATIC ${SOURCES})

target_link_libraries(${BINARY}_run PUBLIC ${CMAKE_PROJECT_NAME}_lib -lcpprest -lpthread -lboost_system -lssl -lcrypto)
