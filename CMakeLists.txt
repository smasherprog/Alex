# CMakeList.txt : CMake project for Alex, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("Alex")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
else()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic")
endif()

set(ALEX_COMMON_SRC      
Alex.cpp
vendors/imgui/imgui.cpp
vendors/imgui/imgui_demo.cpp
vendors/imgui/imgui_draw.cpp
vendors/imgui/imgui_tables.cpp
vendors/imgui/imgui_widgets.cpp
vendors/imgui/backends/imgui_impl_glfw.cpp
vendors/imgui/backends/imgui_impl_vulkan.cpp
)

set(ALEX_COMMON_INC   
vendors/imgui
vendors/imgui/backends
)


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

 include_directories (${PROJECT_NAME} 
    ${ALEX_COMMON_INC}
    ${Vulkan_INCLUDE_DIR}
    vendors/glfw/include
)

add_executable (${PROJECT_NAME} ${ALEX_COMMON_SRC})

target_link_libraries(${PROJECT_NAME} ${Vulkan_LIBRARIES} glfw)  
