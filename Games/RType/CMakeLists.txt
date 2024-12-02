project(RType)

set(RTYPE_COMMON_SOURCES
    src/RType.cpp
)

function(create_rtype_target target_name definition)
    add_executable(${target_name} ${RTYPE_COMMON_SOURCES})

    target_compile_definitions(${target_name} PRIVATE ${definition})

    target_include_directories(${target_name} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    )

    target_link_libraries(${target_name} PRIVATE
        Engine
        Engine::Graphic
        Engine::Physics
        Engine::Inputs
        Engine::Audio
    )
endfunction()

if (SERVER)
    create_rtype_target(r-type_server SERVER)
endif()

if (CLIENT)
    create_rtype_target(r-type_client CLIENT)
endif()
