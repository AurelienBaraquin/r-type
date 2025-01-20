# Déclaration du projet
project(SuperMario)

# Liste des fichiers sources communs
set(SUPERMARIO_COMMON_SOURCES
    src/SuperMario.cpp
)

# Fonction pour créer une cible de Super Mario
function(create_supermario_target target_name definition)
    add_executable(${target_name} ${SUPERMARIO_COMMON_SOURCES})

    # Définitions de compilation spécifiques
    target_compile_definitions(${target_name} PRIVATE ${definition})

    # Répertoires d'inclusion
    target_include_directories(${target_name} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    )

    # Lien avec les bibliothèques nécessaires
    target_link_libraries(${target_name} PRIVATE
        Engine
        Engine::Graphic
        Engine::Physics
        Engine::Inputs
        Engine::Audio
    )
endfunction()

# Création des cibles conditionnellement
if (SERVER)
    create_supermario_target(supermario_server SERVER)
endif()

if (CLIENT)
    create_supermario_target(supermario_client CLIENT)
endif()
