add_library(calcexp calcexp.cpp calcexp.h)
add_executable(calc main.cpp calcexp)
set_target_properties(calc PROPERTIES DEBUG_POSTFIX d)