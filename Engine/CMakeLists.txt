project(Engine)

add_subdirectory(Core)

if(BUILD_TOOLS)
    add_subdirectory(Tools)
endif()

if(BUILD_TESTS)
    add_subdirectory(Test)
endif()

if(GRAPHIC)
    add_subdirectory(Modules/Graphic)
endif()

if (PHYSICS)
    add_subdirectory(Modules/Physics)
endif()

if (INPUTS)
    add_subdirectory(Modules/Inputs)
endif()

if (NETWORK)
    add_subdirectory(Modules/Network)
endif()

if (AUDIO)
    add_subdirectory(Modules/Audio)
endif()
