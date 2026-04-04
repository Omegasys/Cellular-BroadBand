# Minimum version of CMake required to build this project
cmake_minimum_required(VERSION 3.10)

# Project name and version
project(LTE_Modem VERSION 1.0)

# Set CMake policies (if necessary)
cmake_policy(SET CMP0074 NEW)

# Specify C++ standard (or C, if applicable)
set(CMAKE_C_STANDARD 99)

# Include directories for header files
include_directories(
    ${PROJECT_SOURCE_DIR}/include
)

# Optionally, specify installation directories (for future use)
# set(CMAKE_INSTALL_PREFIX /path/to/install)

# Define the source files of the project
set(SOURCE_FILES
    commands/modem_commands.c
    modem/ID/ID.conf
    modem/ID/ad_id_rotator.c
    modem/ID/imsi_rotator.c
    modem/ID/inzi_rotator.c
    modem/network/packet_handler.c
    modem/network/packet_handler.h
    modem/security/authentication.c
    modem/security/authentication.h
    modem/security/encryption.c
    modem/security/encryption.h
    modem/lte_modem.c
    modem/lte_modem.h
    utils/error_handling.c
    utils/error_handling.h
    utils/logging.c
    utils/logging.h
    event_logger.c
    main.c
    modem_access_restrictions.c
)

# If you have additional test files or documentation, include them here
set(TEST_FILES
    tests/test_lte_modem.c
    tests/test_encryption.c
    tests/test_authentication.c
    tests/test_packet_handler.c
)

# Executable target for the main application (LTE modem)
add_executable(lte_modem ${SOURCE_FILES})

# If you have unit tests, link test libraries
# find_package(GTest REQUIRED)  # If using Google Test
# add_executable(test_lte_modem ${TEST_FILES})
# target_link_libraries(test_lte_modem GTest::GTest GTest::Main)

# Enable compiler warnings for better debugging
if(MSVC)
    target_compile_options(lte_modem PRIVATE /W4 /WX)
else()
    target_compile_options(lte_modem PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

# Specify dependencies (if any)
# find_package(OpenSSL REQUIRED)  # For SSL/TLS encryption
# target_link_libraries(lte_modem OpenSSL::Crypto OpenSSL::SSL)

# Example: Linking pthread library (needed for multithreading in Linux)
if(UNIX)
    target_link_libraries(lte_modem pthread)
endif()

# Install the executable (optional)
# install(TARGETS lte_modem DESTINATION /usr/local/bin)

# Set up tests (if any)
# enable_testing()
# add_test(NAME test_lte_modem COMMAND test_lte_modem)
