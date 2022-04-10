# CMakeList.txt : CMake project for Alex, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("Alex") 
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    foreach(flag_var
        CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
        CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
    STRING (REGEX REPLACE "/W3" "/W4" ${flag_var} "${${flag_var}}")
    endforeach(flag_var) 
else()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic")
endif()

set(ALEX_COMMON_SRC      
vendors/imgui/imgui.cpp
vendors/imgui/imgui_demo.cpp
vendors/imgui/imgui_draw.cpp
vendors/imgui/imgui_tables.cpp
vendors/imgui/imgui_widgets.cpp
vendors/imgui/backends/imgui_impl_glfw.cpp
vendors/imgui/backends/imgui_impl_vulkan.cpp
"src/Alex.cpp" 
"src/Graphics/Vertex.cpp"
"src/Graphics/StaticMeshFactory.cpp" 
)

set(ALEX_COMMON_INC   
vendors/imgui
vendors/imgui/backends
)

add_definitions(-DSAIL_BUILD)
if(WIN32)
    set(ALEX_PLATFORM_SRC      

    )
    set(ALEX_PLATFORM_INC     
        
    )
	add_definitions(-DNOMINMAX)
elseif(APPLE)

    set(ALEX_PLATFORM_SRC
    )
    set(ALEX_PLATFORM_INC
    )
else()
  set(ALEX_PLATFORM_SRC 

    )
	set(ALEX_PLATFORM_INC
    )
endif()
	
find_package(Vulkan REQUIRED)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
option(GLFW_BUILD_DOCS OFF)
option(GLFW_VULKAN_STATIC ON)
add_subdirectory(vendors/glfw)
 
option(BUILD_SHARED_LIBS OFF)
option(ASSIMP_NO_EXPORT OFF)
option(ASSIMP_BUILD_SAMPLES OFF)
option(ASSIMP_BUILD_TESTS  OFF)
add_subdirectory(vendors/assimp)
  
 include_directories (${PROJECT_NAME} 
    ${ALEX_COMMON_INC}
    ${Vulkan_INCLUDE_DIR}
    ${glfw_INCLUDE_DIR}
    include
    vendors/
    vendors/glm
    vendors/stb
    assimp/include/
)

add_executable (${PROJECT_NAME} ${ALEX_COMMON_SRC})

target_link_libraries(${PROJECT_NAME} ${Vulkan_LIBRARIES} glfw assimp)  
