# add the example executable, linked with the Coeus library
add_executable(LexicalAnalysis_Example end-to-end/main.cpp)
target_link_libraries(LexicalAnalysis_Example Coeus ${SYSTEM_LIBRARIES})