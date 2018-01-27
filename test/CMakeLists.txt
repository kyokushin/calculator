enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIR} "${PROJECT_SOURCE_DIR}/src")

message(STATUS "${PROJECT_SOURCE_DIR}/src")

add_executable(calcTest main.cpp)
target_link_libraries(calcTest ${GTEST_BOTH_LIBRARIES} calcexp)