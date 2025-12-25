cmake_minimum_required(VERSION 3.16)
project(ContactSystem VERSION 1.0.0 LANGUAGES CXX)

# ============= vcpkg 集成配置 =============
# 1. 设置vcpkg工具链（必须放在project()之前）
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake"
    CACHE STRING "Vcpkg toolchain file")

# 2. 可选：设置vcpkg安装目录为项目本地
set(VCPKG_INSTALLED_DIR "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg_installed")

# ============= 编译器配置 =============
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# ============= Qt 配置 =============
# 注意：不再需要手动设置 CMAKE_PREFIX_PATH
# vcpkg 会自动处理 Qt 的查找

# 查找Qt库 - 根据你的代码，需要Core、Gui、Widgets
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

# ============= 可执行文件 =============
add_executable(${PROJECT_NAME}
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    contactbookwindow.h
    contactbookwindow.cpp
    contactbookwindow.ui
    fonts.qrc
    fontmanager.h
    fontmanager.cpp
    contact.h
    contact.cpp
    addcontactdialog.h addcontactdialog.cpp addcontactdialog.ui
    editcontactdialog.h editcontactdialog.cpp editcontactdialog.ui
    analysiswindow.h analysiswindow.cpp analysiswindow.ui
)

# ============= 链接库 =============
target_link_libraries(${PROJECT_NAME}
    Qt6::Core
    Qt6::Gui        # 添加这个，QLabel/QVBoxLayout等需要
    Qt6::Widgets    # QPushButton/QMessageBox等需要
)

# ============= 自动复制 Data 文件夹 =============
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/Data
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/Data
    COMMENT "复制 Data 文件夹到可执行文件目录"
    VERBATIM
)

# ============= 可选：Qt运行时依赖部署 =============
# 注意：使用vcpkg时，以下代码需要调整
# if(WIN32 AND MSVC AND NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
#     # vcpkg安装的Qt库路径不同
#     find_program(WINDEPLOYQT_EXE windeployqt HINTS "${VCPKG_INSTALLED_DIR}/tools/qt5/bin")
#     if(WINDEPLOYQT_EXE)
#         add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
#             COMMAND ${WINDEPLOYQT_EXE} $<TARGET_FILE:${PROJECT_NAME}>
#             COMMENT "部署Qt运行时库"
#         )
#     endif()
# endif()