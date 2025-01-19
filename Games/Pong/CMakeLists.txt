project(Pong)

set(PONG_COMMON_SOURCES
    src/Pong.cpp
)

function(create_pong_target target_name definition)
    add_executable(${target_name} ${PONG_COMMON_SOURCES})

    target_compile_definitions(${target_name} PRIVATE ${definition})

    target_include_directories(${target_name} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    )
    if (SERVER)
        target_link_libraries(${target_name} PRIVATE
            Engine
            Engine::Physics
            Engine::Inputs
            Engine::Network
        )
    endif()
    if (CLIENT)
        target_link_libraries(${target_name} PRIVATE
            Engine
            Engine::Graphic
            Engine::Physics
            Engine::Inputs
            Engine::Audio
            Engine::Network
        )
    endif()
endfunction()

if (SERVER)
    create_pong_target(pong_server SERVER)
endif()

if (CLIENT)
    create_pong_target(pong_client CLIENT)
endif()
