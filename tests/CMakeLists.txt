set(TESTFILES test_main.cpp)

enable_testing()
add_executable(system-tests ${TESTFILES})
target_link_libraries(system-tests Coeus)
