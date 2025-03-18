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
include(FetchContent)

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

FetchContent_Declare(
    json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.3  
)
FetchContent_MakeAvailable(json)

# Ajouter des cibles exécutable
add_executable(MyTests ${DEFAULT_PROJECT_FILES} ${TEST_FILES})

add_executable(e_tron_cmd ${DEFAULT_PROJECT_FILES} ${CMAKE_SOURCE_DIR}/src/main.cpp)
add_executable(reader ${DEFAULT_PROJECT_FILES} ${CMAKE_SOURCE_DIR}/src/reader.cpp)

target_link_libraries(e_tron_cmd PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(reader PRIVATE nlohmann_json::nlohmann_json)

add_custom_command(
    OUTPUT ${CMAKE_BINARY_DIR}/config.ini
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/config.ini ${CMAKE_BINARY_DIR}/config.ini
    DEPENDS ${CMAKE_SOURCE_DIR}/config.ini
    COMMENT "Copying config to build root dir"
)
add_custom_target(config DEPENDS ${CMAKE_BINARY_DIR}/config.ini)
add_dependencies(e_tron_cmd config)

if (CMAKE_HOST_SYSTEM_NAME STREQUAL "Windows")
    add_executable(e_tron_directX ${DEFAULT_PROJECT_FILES} ${GRAPHICS_FILES})

    set_target_properties(e_tron_directX PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS")
    target_sources(e_tron_directX PRIVATE ${CMAKE_SOURCE_DIR}/src/graphics/core/resource/resource.rc)

    remove(${CMAKE_BINARY_DIR}/assets)

    add_custom_command(
        OUTPUT ${CMAKE_BINARY_DIR}/assets
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/assets ${CMAKE_BINARY_DIR}/assets
        DEPENDS ${CMAKE_SOURCE_DIR}/assets
        COMMENT "Copying assets folder to build directory"
    )
    add_custom_target(CopyAssets ALL DEPENDS ${CMAKE_BINARY_DIR}/assets)
    add_dependencies(e_tron_directX CopyAssets)

    target_link_libraries(e_tron_directX PRIVATE d3d11 d3dcompiler dxgi dxguid d2d1 dwrite)
    target_link_libraries(e_tron_directX PRIVATE nlohmann_json::nlohmann_json)
    
    # HLSL COMPILING
    find_program(FXC_COMPILER fxc.exe REQUIRED)
    message(STATUS "FXC Compiler found at: ${FXC_COMPILER}")

    # Define the shader source directory
    set(SHADER_SRC_DIR ${CMAKE_SOURCE_DIR}/src/graphics/core/render/shaders)

    # Define the directory to store the compiled shaders
    set(SHADER_OUTPUT_DIR ${CMAKE_BINARY_DIR}/shaders)

    # Ensure the output directory exists
    file(MAKE_DIRECTORY ${SHADER_OUTPUT_DIR})

    # Find all HLSL files in the shader source directory
    file(GLOB_RECURSE SHADER_FILES ${SHADER_SRC_DIR}/*.hlsl)

    # List to hold compiled shader files
    set(COMPILED_SHADERS)
    # Set the hlsl version
    set(HLSL_VERSION 5_0)
    # Compile each shader
    foreach(SHADER_FILE ${SHADER_FILES})
        message(STATUS "Shader file: ${SHADER_FILE}")
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
            ARGS /T ${HLSL_TYPE}_${HLSL_VERSION} /Fo ${COMPILED_SHADER} ${SHADER_FILE}
            DEPENDS ${SHADER_FILE}
            COMMENT "Compiling HLSL shader: ${SHADER_FILE}"
        )

        # Add a custom target to ensure the shaders are compiled
        list(APPEND COMPILED_SHADERS ${COMPILED_SHADER})
        message(STATUS "Adding shader: ${SHADER_FILE}")
    endforeach()
    add_custom_target(CompileShaders ALL DEPENDS ${COMPILED_SHADERS})
    add_dependencies(e_tron_directX CompileShaders)

endif()