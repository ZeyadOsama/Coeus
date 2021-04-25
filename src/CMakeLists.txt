add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/data-units)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lex)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/utils)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/states)

add_library(Coeus STATIC ${SOURCES})