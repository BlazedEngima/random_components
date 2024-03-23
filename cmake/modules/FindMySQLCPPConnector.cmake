# FindMySQLCPPConnector.cmake
# Locate MySQL CPP Connector library

set(MySQLCPPConnector_ROOT_DIR "${CMAKE_SOURCE_DIR}/lib/mysql-cpp-connector")
set(MySQLCPPConnector_INCLUDE_DIR "${MySQLCPPConnector_ROOT_DIR}/include")

if($ENV{HOST_ARCH} MATCHES "arm64")
    set(MySQLCPPConnector_LIB_DIR "${MySQLCPPConnector_ROOT_DIR}/lib64")
else()
    set(MySQLCPPConnector_LIB_DIR "${MySQLCPPConnector_ROOT_DIR}/lib64-x86_64")
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