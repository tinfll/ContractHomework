cmake_minimum_required(VERSION 3.16)
project(ContactSystem VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# 查找Qt库
find_package(Qt6 COMPONENTS Core Widgets REQUIRED)

# 创建可执行文件
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
