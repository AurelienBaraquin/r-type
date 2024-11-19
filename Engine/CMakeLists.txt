project(Engine)

add_subdirectory(Core)

if(BUILD_TESTS)
    add_subdirectory(Test)
endif()

if(GRAPHIC)
    add_subdirectory(Modules/Graphic)

endif ()

if (PHYSICS)
    add_subdirectory(Modules/Physics)
endif()
