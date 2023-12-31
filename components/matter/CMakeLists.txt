armino_build_get_property(target ARMINO_SOC)

armino_component_register()

if (CONFIG_SUPPORT_MATTER)

set(chip_dir ${COMPONENT_DIR})
set(base_dir ${COMPONENT_DIR}/../..)
set(config_dir ${CMAKE_BINARY_DIR}/config)
set(output_dir ${CMAKE_BINARY_DIR}/armino/matter_build)
set(lib_dir ${output_dir}/out/${target}/lib)
set(toolchain ${CONFIG_TOOLCHAIN_PATH})
set(toolchain_prefix ${CONFIG_TOOLCHAIN_PREFIX})

if(EXISTS ${chip_dir}/connectedhomeip)
message(STATUS "exist connectedhomeip")
else()
message(STATUS "not exist connectedhomeip")
message(STATUS "clone connectedhomeip...")
execute_process(COMMAND git clone -b main http://gitlab.bekencorp.com/wifi_pub/matter/connectedhomeip.git ${chip_dir}/connectedhomeip)
endif()

include(ExternalProject)
ExternalProject_Add(matter_project
	SOURCE_DIR ${chip_dir}
	CONFIGURE_COMMAND ""
	BUILD_IN_SOURCE 1
	BUILD_COMMAND
		make TARGET=${target}
		TOOLCHAIN_PATH=${toolchain}
		TOOLCHAIN_PREFIX=${toolchain_prefix}
		CONFIG_DIR=${config_dir}
		BASEDIR=${base_dir}
		OUTPUT_DIR=${output_dir}
		-f ${chip_dir}/libCHIP.mk
	BUILD_BYPRODUCTS ${lib_dir}/libMatterApp.a
	BUILD_ALWAYS 1
	INSTALL_COMMAND ""
	)
if(0)
add_library(lib_app STATIC IMPORTED GLOBAL)
add_dependencies(lib_app matter_project)
set_target_properties(lib_app PROPERTIES IMPORTED_LOCATION ${lib_dir}/libAPPLICATION.a)

add_library(lib_chip STATIC IMPORTED GLOBAL)
add_dependencies(lib_chip matter_project)
set_target_properties(lib_chip PROPERTIES IMPORTED_LOCATION ${lib_dir}/libCHIP.a)
endif()

add_library(lib_matter STATIC IMPORTED GLOBAL)
add_dependencies(lib_matter matter_project)
set_target_properties(lib_matter PROPERTIES IMPORTED_LOCATION ${lib_dir}/libMatterApp.a)

target_link_libraries(${COMPONENT_LIB} INTERFACE lib_matter)

endif()
