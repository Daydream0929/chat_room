cmake_minimum_required(VERSION 3.10)  # 指定CMake的最低版本要求

project(chat_room)  # 定义项目名称

# 设置C++标准
set(CMAKE_CXX_STANDARD 11)

# 添加可执行文件
add_executable(chat_room src/main.cpp)  # main.cpp 是你的项目的源文件

# 添加其他源文件（如果有的话）
# add_executable(MyChatApp main.cpp file1.cpp file2.cpp ...)

# 如果你需要使用外部库，可以使用 find_package 命令
# 例如，使用 Threads 库
#find_package(Threads REQUIRED)
#target_link_libraries(MyChatApp Threads::Threads)

# 如果你的项目需要其他库，也可以在这里添加

