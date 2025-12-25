cmake_minimum_required(VERSION 3.16)
project(ContactSystem VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# 设置Qt路径（根据你的实际路径修改）
# set(CMAKE_PREFIX_PATH "C:/Qt/6.5.3/msvc2019_64")

# 查找Qt库
find_package(Qt6 COMPONENTS Core Widgets REQUIRED)

# 创建可执行文件并添加源文件
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

# 链接Qt库
target_link_libraries(${PROJECT_NAME}
    Qt6::Core
    Qt6::Widgets
)

# ============= 新增的 Data 文件夹复制配置 =============
# 构建后自动复制 Data 文件夹到可执行文件目录
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/Data
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/Data
    COMMENT "复制 Data 文件夹到可执行文件目录"
    VERBATIM
)

# 可选：复制Qt运行时依赖（用于发布）
# if(WIN32 AND MSVC AND NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
#     add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
#         COMMAND ${CMAKE_COMMAND} -E copy_directory
#             "$ENV{QTDIR}/bin"
#             $<TARGET_FILE_DIR:${PROJECT_NAME}>
#     )
# endif()