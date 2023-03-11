cmake_minimum_required(VERSION 3.0)

project(jusy-bus-cli)

# Define the source files for the application
set(SOURCES
    jusy_bus_cli.cpp
)

# Create the executable
add_executable(jusy-bus-cli ${SOURCES})

# Set C++ version
set_target_properties(jusy-bus-cli PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

# Add any necessary libraries
target_link_libraries(jusy-bus-cli
    jucy-bus
)