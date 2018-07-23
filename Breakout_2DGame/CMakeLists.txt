# 规定cmake程序的最低版本
cmake_minimum_required(VERSION 3.0)

# 项目信息
project(Breakout_2DGame_Opengl)

# 添加需要编译的源文件的子目录
add_subdirectory(lib/glfw)


# 向工程添加多个特定的头文件搜索路径
include_directories(include/
					lib/glad/include/
                    lib/glfw/include/
                    lib/glm)

file(GLOB LIB_SOURCES lib/glad/src/glad.c)
file(GLOB PROJECT_SOURCES src/*.h src/*.cpp src/common/*.h src/common/*.cpp)

# 添加要执行的编译命令
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${LIB_SOURCES})
	
target_link_libraries(${PROJECT_NAME} glfw)