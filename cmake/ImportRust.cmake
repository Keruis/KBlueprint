function(import_rust_library crate_name crate_dir out_var)
    set(RUST_LIB ${crate_dir}/target/release/lib${crate_name}.a)
    file(GLOB_RECURSE RUST_SOURCES ${crate_dir}/src/*.rs)

    add_custom_command(
            OUTPUT ${RUST_LIB}
            COMMAND cargo build --release
            WORKING_DIRECTORY ${crate_dir}
            DEPENDS ${RUST_SOURCES}
            COMMENT "Building Rust static library (${crate_name})"
    )

    add_custom_target(${crate_name}_rustlib ALL DEPENDS ${RUST_LIB})

    add_library(${crate_name}_rust STATIC IMPORTED GLOBAL)
    set_target_properties(${crate_name}_rust PROPERTIES IMPORTED_LOCATION ${RUST_LIB})

    set(${out_var} ${crate_name}_rust PARENT_SCOPE)
endfunction()