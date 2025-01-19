project(Games)

if(BUILD_RTYPE)
    add_subdirectory(RType)
endif()

if(BUILD_PONG)
    add_subdirectory(Pong)
endif()

if (BUILD_ENGINE_EDITOR)
    add_subdirectory(EngineEditor)
endif()
