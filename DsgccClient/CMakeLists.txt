set(PLUGIN_NAME DsgccClient)
set(MODULE_NAME ${NAMESPACE}${PLUGIN_NAME})

find_package(${NAMESPACE}Interfaces REQUIRED)
find_package(${NAMESPACE}Plugins REQUIRED)

add_library(${MODULE_NAME} SHARED
        Module.cpp
        DsgccClient.cpp
        DsgccClientImplementation.cpp)

target_compile_definitions(${MODULE_NAME}
        PRIVATE
           DSG_RPC_INCLUDED=1 
           BCM_DSGCC_CLIENTS_USE_SHARED_MEMORY_IPC=1 
           TARGETOS_Linux)

set_target_properties(${MODULE_NAME} PROPERTIES
        CXX_STANDARD 11
        CXX_STANDARD_REQUIRED YES)

target_link_libraries(${MODULE_NAME} 
    PRIVATE
        ${NAMESPACE}Interfaces::${NAMESPACE}Interfaces
        ${NAMESPACE}Plugins::${NAMESPACE}Plugins
        # TODO: write a proper find module for dsgclient to supply all link and compile options. 
        #       check: FindNXSERVER.cmake, FindEGL.cmake
        dsgclient)

install(TARGETS ${MODULE_NAME} 
    DESTINATION lib/${STORAGE_DIRECTORY}/plugins)

write_config(${PLUGIN_NAME})
