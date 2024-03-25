# FindMySQLCPPConnector.cmake
# Locate MySQL CPP Connector library

set(MySQLCPPConnector_ROOT_DIR "${CMAKE_SOURCE_DIR}/lib/mysql-cpp-connector")
set(MySQLCPPConnector_INCLUDE_DIR "${MySQLCPPConnector_ROOT_DIR}/include")

# lowercase the processor name
string(TOLOWER ${CMAKE_SYSTEM_PROCESSOR} CMAKE_SYSTEM_PROCESSOR_LOWER)

# supported architectures
set(ARCH_LIB_DIR_MAP
  "arm64" "${MySQLCPPConnector_ROOT_DIR}/lib64"
  "aarch64" "${MySQLCPPConnector_ROOT_DIR}/lib64"
  "x86_64" "${MySQLCPPConnector_ROOT_DIR}/lib64-x86_64"
  "amd64" "${MySQLCPPConnector_ROOT_DIR}/lib64-x86_64"
)

list(FIND ARCH_LIB_DIR_MAP ${CMAKE_SYSTEM_PROCESSOR_LOWER} ARCH_INDEX)

# unsupported architecture
if(ARCH_INDEX EQUAL -1)
  message(FATAL_ERROR "Unsupported architecture: ${CMAKE_SYSTEM_PROCESSOR}")
else()
  # get the library directory
  math(EXPR LIB_DIR_INDEX "${ARCH_INDEX} + 1")
  list(GET ARCH_LIB_DIR_MAP ${LIB_DIR_INDEX} MySQLCPPConnector_LIB_DIR)
endif()

find_library(MySQLCPPConnector_LIB mysqlcppconn8
    HINTS
    ${MySQLCPPConnector_LIB_DIR}
)

include(FindPackageHandleStandardArgs)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(
    MySQLCPPConnector 
    DEFAULT_MSG 
    MySQLCPPConnector_LIB 
    MySQLCPPConnector_INCLUDE_DIR
)