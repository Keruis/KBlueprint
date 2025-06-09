function(import_cs_library project_name project_dir out_var)
    set(CS_LIB_DIR ${project_dir}/bin/Release/net9.0/linux-x64/publish)
    set(CS_ORIGINAL_SO ${CS_LIB_DIR}/${project_name}.so)
    set(CS_LIB ${CS_LIB_DIR}/lib${project_name}.so)

    message(STATUS "${project_name} .so path = ${CS_LIB}")

    add_custom_command(
            OUTPUT ${CS_LIB}
            COMMAND dotnet publish -c Release -r linux-x64 --self-contained true
            WORKING_DIRECTORY ${project_dir}
            DEPENDS ${project_dir}/Program.cs
            COMMAND ${CMAKE_COMMAND} -E rename ${CS_ORIGINAL_SO} ${CS_LIB}
            COMMENT "Building and renaming C# shared library (${project_name})"
    )

    add_custom_target(${project_name}_buildcs ALL DEPENDS ${CS_LIB})

    add_library(${project_name}_cs SHARED IMPORTED GLOBAL)
    set_target_properties(${project_name}_cs PROPERTIES IMPORTED_LOCATION ${CS_LIB})

    set(${out_var} ${project_name}_cs PARENT_SCOPE)
endfunction()