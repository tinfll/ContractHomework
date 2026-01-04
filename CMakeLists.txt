cmake_minimum_required(VERSION 3.10)
project(ContactSystem)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- 1. 查找系统级依赖 (Vulkan SDK) ---
find_package(Vulkan REQUIRED)

# --- 2. 设置项目内部路径 ---
set(VENDOR_DIR "${CMAKE_CURRENT_SOURCE_DIR}/vendor")
set(GLFW_DIR "${VENDOR_DIR}/glfw")
set(IMGUI_DIR "${VENDOR_DIR}/imgui")

# --- 3. 包含头文件路径 (Include Directories) ---
include_directories(
    # 1. 你的头文件目录
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    
    # 2. ImGui 核心头文件 (imgui.h)
    "${IMGUI_DIR}"
    
    # 3. ImGui 实现层头文件 (imgui_impl_vulkan.h 就在这里)
    "${IMGUI_DIR}/backends"
    
    # 4. GLFW 头文件
    "${GLFW_DIR}/include"
    
    # 5. Vulkan SDK 头文件 (自动找到的)
    ${Vulkan_INCLUDE_DIRS}
)

# --- 4. 收集源文件 ---

file(GLOB_RECURSE MY_SOURCES 
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp" 
    "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp"
)

file(GLOB_RECURSE MY_HEADERS 
    "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h"
)
    

# B. ImGui 的代码 (必须手动指定这几个核心文件)
set(IMGUI_SOURCES
    "${IMGUI_DIR}/imgui.cpp"
    "${IMGUI_DIR}/imgui_demo.cpp"
    "${IMGUI_DIR}/imgui_draw.cpp"
    "${IMGUI_DIR}/imgui_tables.cpp"
    "${IMGUI_DIR}/imgui_widgets.cpp"
    # 重点：把后端实现的 .cpp 也加进来编译
    "${IMGUI_DIR}/backends/imgui_impl_glfw.cpp"
    "${IMGUI_DIR}/backends/imgui_impl_vulkan.cpp"
)

# --- 5. 生成可执行文件 ---
add_executable(${PROJECT_NAME} ${MY_SOURCES} ${MY_HEADERS} ${IMGUI_SOURCES})

# --- 6. 链接库文件 ---
target_link_libraries(${PROJECT_NAME} PRIVATE
    Vulkan::Vulkan                       # 链接 Vulkan
    "${GLFW_DIR}/lib-vc2022/glfw3.lib"   # 链接项目内的 GLFW (确认你的文件夹名叫 lib-vc2022)
)

# --- 7. 资源拷贝 (自动把 shader 和 assets 拷到 build 目录) ---
# 如果你根目录下有 assets 和 shaders 文件夹，这部分代码会让它们自动跟随 exe
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/assets")
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets
    )
endif()

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/shaders")
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/shaders
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/shaders
    )
endif()

message(STATUS "Build setup complete. Include dir: ${CMAKE_CURRENT_SOURCE_DIR}/include")