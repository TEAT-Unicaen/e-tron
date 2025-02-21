# Minimum version de CMake
cmake_minimum_required(VERSION 3.20)

# Nom du projet
project(e_tron)

# Définir le standard C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Flags
set(CXX_FLAGS_DEFAULT "/MP /Ot /fp:fast")
set(CMAKE_CXX_FLAGS_RELEASE "${CXX_FLAGS_DEFAULT} /MD /DNDEBUG /DIS_DEBUG_MODE=false")
set(CMAKE_CXX_FLAGS_DEBUG "${CXX_FLAGS_DEFAULT} /MDd /DIS_DEBUG_MODE=true")

# Inclure les répertoires contenant les headers
include_directories(${CMAKE_SOURCE_DIR}/src)

# Ajouter les fichiers sources principaux
file(GLOB_RECURSE DEFAULT_PROJECT_FILES ${CMAKE_SOURCE_DIR}/src/*.cpp ${CMAKE_SOURCE_DIR}/src/*.h)

# Ajouter les fichiers pour les tests (dans src/test/)
file(GLOB_RECURSE TEST_FILES ${CMAKE_SOURCE_DIR}/src/testMain.cpp ${CMAKE_SOURCE_DIR}/src/test/*.cpp ${CMAKE_SOURCE_DIR}/src/test/*.h)

# Ajouter les fichiers pour le graphics
file(GLOB_RECURSE GRAPHICS_FILES ${CMAKE_SOURCE_DIR}/src/winMain.cpp ${CMAKE_SOURCE_DIR}/src/graphics/*.cpp ${CMAKE_SOURCE_DIR}/src/graphics/*.h)

# Build de la liste des fichiers sources
list(REMOVE_ITEM DEFAULT_PROJECT_FILES ${CMAKE_SOURCE_DIR}/src/main.cpp)
list(REMOVE_ITEM DEFAULT_PROJECT_FILES ${CMAKE_SOURCE_DIR}/src/reader.cpp)
list(REMOVE_ITEM DEFAULT_PROJECT_FILES ${GRAPHICS_FILES})
list(REMOVE_ITEM DEFAULT_PROJECT_FILES ${TEST_FILES})

# Ajouter des cibles exécutable
add_executable(MyTests ${DEFAULT_PROJECT_FILES} ${TEST_FILES})

add_executable(e_tron_cmd ${DEFAULT_PROJECT_FILES} ${CMAKE_SOURCE_DIR}/src/main.cpp)
add_executable(reader ${DEFAULT_PROJECT_FILES} ${CMAKE_SOURCE_DIR}/src/reader.cpp)

if (CMAKE_HOST_SYSTEM_NAME STREQUAL "Windows")
    add_executable(e_tron_directX ${DEFAULT_PROJECT_FILES} ${GRAPHICS_FILES})

    set_target_properties(e_tron_directX PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS")
    target_sources(e_tron_directX PRIVATE ${CMAKE_SOURCE_DIR}/src/graphics/resource/resource.rc)

    #Copy the assets folder to the build directory
    file(REMOVE_RECURSE ${CMAKE_BINARY_DIR}/assets)
    file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})

    target_link_libraries(e_tron_directX PRIVATE d3d11 d3dcompiler dxgi dxguid)
    
    # HLSL COMPILING
    
    # Find the HLSL compiler
    find_program(FXC_COMPILER fxc.exe REQUIRED)
    message(STATUS "FXC Compiler found at: ${FXC_COMPILER}")

    # Define the shader source directory
    set(SHADER_SRC_DIR ${CMAKE_SOURCE_DIR}/src/graphics/shaders)

    # Define the directory to store the compiled shaders
    set(SHADER_OUTPUT_DIR ${CMAKE_BINARY_DIR}/shaders)

    # Ensure the output directory exists
    file(MAKE_DIRECTORY ${SHADER_OUTPUT_DIR})

    # Find all HLSL files in the shader source directory
    file(GLOB_RECURSE SHADER_FILES ${SHADER_SRC_DIR}/*.hlsl)

    # List to hold compiled shader files
    set(COMPILED_SHADERS)

    # Compile each shader
    foreach(SHADER_FILE ${SHADER_FILES})
        # Get the filename without extension
        get_filename_component(SHADER_NAME ${SHADER_FILE} NAME_WE)
    
        # Define the compiled shader output path
        set(COMPILED_SHADER ${SHADER_OUTPUT_DIR}/${SHADER_NAME}.cso)


        # Determine the shader type
        set(HLSL_TYPE)
        if (SHADER_NAME MATCHES "PS")
            set(HLSL_TYPE ps)
        elseif (SHADER_NAME MATCHES "VS")
            set(HLSL_TYPE vs)
        elseif (SHADER_NAME MATCHES "GS")
            set(HLSL_TYPE gs)
        elseif (SHADER_NAME MATCHES "HS")
            set(HLSL_TYPE hs)
        elseif (SHADER_NAME MATCHES "DS")
            set(HLSL_TYPE ds)
        elseif (SHADER_NAME MATCHES "CS")
            set(HLSL_TYPE cs)
        else()
            message(WARNING "Unknown shader type: ${SHADER_NAME}. Skipping...")
            continue()
        endif()

        #compile the hlsl
        add_custom_command(
            OUTPUT ${COMPILED_SHADER}
            COMMAND ${FXC_COMPILER}
            ARGS /T ${HLSL_TYPE}_5_0 /Fo ${COMPILED_SHADER} ${SHADER_FILE}
            DEPENDS ${SHADER_FILE}
            COMMENT "Compiling HLSL shader: ${SHADER_FILE}"
        )

        # Add a custom target to ensure the shaders are compiled
        list(APPEND COMPILED_SHADERS ${COMPILED_SHADER})
    endforeach()
    add_custom_target(CompileShaders ALL DEPENDS ${COMPILED_SHADERS})

    add_dependencies(e_tron_directX CompileShaders)
endif()