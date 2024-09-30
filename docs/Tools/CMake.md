---
tags:
  - tools/Cmake
---

# CMake

!!! Info "INFO"
    - [官方教程](https://cmake.org/cmake/help/latest/guide/tutorial/)
![image-20240223212218052](http://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202402232122164.png)
> 1. CMake 中的对齐很重要！！！
>    ![image-20240223212218052](http://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202402232122164.png)
> 2. 

## Step 1 Starting Point

==文件架构==

 ```text
 step1/
     build/
     CMakeLists.txt
     tutorial.cpp
 ```

==演示==

```CMAKE
# TODO 1: Set the minimum required version of CMake to be 3.10
cmake_minimum_required(VERSION 3.10)

# TODO 2: Create a project named Tutorial
project(  
    Tutorial  
    VERSION 1.0
    DESCRIPTION "这是一个演示项目"  
    HOMEPAGE_URL "https://cmake.org/cmake/help/latest/guide/tutorial/A%20Basic%20Starting%20Point.html#"  
    LANGUAGES CXX C  
)  

# TODO 7: Set the project version number as 1.0 in the above project command
project(Tutorial VERSION 1.0)

# TODO 6: Set the variable CMAKE_CXX_STANDARD to 11
#         and the variable CMAKE_CXX_STANDARD_REQUIRED to True
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# TODO 8: Use configure_file to configure and copy TutorialConfig.h.in to
#         TutorialConfig.h
configure_file(TutorialConfig.h.in TutorialConfig.h)

# TODO 3: Add an executable called Tutorial to the project
# Hint: Be sure to specify the source file as tutorial.cxx
add_executable(Tutorial tutorial.cxx)

# TODO 9: Use target_include_directories to include ${PROJECT_BINARY_DIR}
target_include_directories(Tutorial PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           )
```

- `project`
  Sets the name of the project, and stores it in the variable [`PROJECT_NAME`](https://cmake.org/cmake/help/latest/variable/PROJECT_NAME.html#variable:PROJECT_NAME). When called from the top-level `CMakeLists.txt` also stores the project name in the variable [`CMAKE_PROJECT_NAME`](https://cmake.org/cmake/help/latest/variable/CMAKE_PROJECT_NAME.html#variable:CMAKE_PROJECT_NAME).
- `configure_file`
  ==TutorialConfig. H. In==

  ```c+
  // the configured options and settings for Tutorial
  #define Tutorial_VERSION_MAJOR @Tutorial_VERSION_MAJOR@
  #define Tutorial_VERSION_MINOR @Tutorial_VERSION_MINOR@
  ```

- `target_include_directories`

----

在 Run 之前，我们需要先构建 Build 目录

```
> mkdir build
> cd build
> cmake -G"MinGW Makefiles" ..

> cmake --build .
> ./Tutorial 4
```

- Windows 下，CMake 默认使用微软的 MSVC 作为编译器，我想使用 MinGW 编译器，可以通过 `-G` 参数来进行指定，只有第一次构建项目时需要指定。
- **``MinGW Makefiles``**是 CMake 所支持的一种生成器，它用于生成适用于 MinGW 工具链的 Makefiles。这些 Makefiles 包含了构建项目所需的指令，可以让你使用 MinGW 工具链来编译和构建你的项目。**当然，这一步也可以不这样指定**

> < INTERFACE  |  PUBLIC |  PRIVATE >
>
> **``PUBLIC``**: 当你使用**``target_link_libraries``**和**``target_include_directories``**命令将库链接到目标时，使用**``PUBLIC``**关键字表示，不仅会将库链接到目标本身，还会将库的依赖项传递给该目标的使用者。也就是说，如果一个目标链接到另一个目标，并且使用了**``PUBLIC``**关键字，那么链接到第一个目标的任何其他目标也会自动链接到第二个目标所链接的库。
>
> **``PRIVATE``**: 使用**``PRIVATE``**关键字表示，链接库的目标将会链接到该库，但不会将该库的依赖项传递给链接到该目标的其他目标。
>
> **``INTERFACE``**: 使用**``INTERFACE``**关键字表示，链接库的目标将不会链接到该库，但该库的依赖项会传递给链接到该目标的其他目标。

## Step 2 添加库

我们可以用一个或多个子目录来组织项目，而不是将所有源文件放在一个目录中。在这种情况下，我们将专门为我们的库创建一个子目录。在这里，我们可以添加一个新 `CMakeLists.txt` 文件和一个或多个源文件。在顶层 `CMakeLists.txt` 文件中，我们将使用 [`add_subdirectory()`](https://cmake.org/cmake/help/latest/command/add_subdirectory.html#command:add_subdirectory) 命令将子目录添加到构建中。

==文件架构==

 ```text
 step2/
     build/
     MathFunctions/
         CMakeLists.txt
         MathFunctions.cxx
         MathFunctions.h
         mysqrt.cxx
         mysqrt.h
     CMakeLists.txt
     tutorial.cxx
     TutorialConfig.h.in
 ```

==演示==

1. 底层的  MathFunctions

```CMAKE
# TODO 14: Remove mysqrt.cxx from the list of sources
# TODO 1: Add a library called MathFunctions with sources MathFunctions.cxx
# and mysqrt.cxx
add_library(MathFunctions MathFunctions.cxx)
# TODO 7: Create a variable USE_MYMATH using option and set default to ON
option(USE_MYMATH "Use tutorial provided math implementation" ON)
# TODO 8: If USE_MYMATH is ON, use target_compile_definitions to pass
# USE_MYMATH as a precompiled definition to our source files
if (USE_MYMATH)
    target_compile_definitions(MathFunctions PRIVATE "USE_MYMATH")
    # TODO 12: When USE_MYMATH is ON, add a library for SqrtLibrary with
    # source mysqrt.cxx
    add_library(SqrtLibrary STATIC
    mysqrt.cxx
    )
# TODO 13: When USE_MYMATH is ON, link SqrtLibrary to the MathFunctions Library
    target_link_libraries(MathFunctions PRIVATE SqrtLibrary)
endif()
```

2. 顶层的

```Cmake
cmake_minimum_required(VERSION 3.10)

# set the project name and version
project(Tutorial VERSION 1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file(TutorialConfig.h.in TutorialConfig.h)

# TODO 2: Use add_subdirectory() to add MathFunctions to this project
add_subdirectory(MathFunctions)
# add the executable
add_executable(Tutorial tutorial.cxx)

# TODO 3: 将库链接到可执行文件
target_link_libraries(Tutorial PUBLIC MathFunctions)
# TODO 4: Add MathFunctions to Tutorial's target_include_directories()
# Hint: ${PROJECT_SOURCE_DIR} is a path to the project source. AKA This folder!

# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
target_include_directories(Tutorial PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/MathFunctions"
                          )
```

- `add_library`
  用于定义一个库，可以结合其他命令对库的属性进行配置。
  1. 正常使用定义一个库
  2. 创建一个只包含接口而没有实际源文件的库，它通常用于传递编译器标志、包含目录等信息给依赖项。[实例见下](#add_library_usage_2)

- `target_link_libraries(<target> ... <item>... ...)`
  命令用于将一个或多个库或目标链接到特定的目标上。这个命令可以用于指定目标需要链接的库，包括其他目标、库文件或链接器标志。
- `add_subdirectory`
  将 ``MathFunctions`` 目录添加到项目中，这将调用 ``MathFunctions`` 目录中的 ``CMakeLists.txt`` 文件来构建库。

---

### 为库添加 Option

允许开发人员选择自定义实现或内置标准实现。

- `target_compile_definitions`
  命令用于向特定目标添加编译定义。这些定义在编译目标时会传递给编译器。
  `target_compile_definitions(MathFunctions PRIVATE "USE_MYMATH")` 就是在编译 `MathFunctions` 的过程中，加入了 `USE_MYMATH` 的预定义变量；同时，Private 表示这个变量只是用于 `MathFunction` 中
  
- `option`
  CMakeLists. Txt 文件中使用**``option``**命令定义的选项会被转化为 C/C++代码中的预处理器定义

> :question: How To Reset the option in the terminal ?
>
> :a: `cmake ../Step2 -DUSE_MYMATH=OFF` `-D` 选项用于在命令行中向 CMake 传递变量定义
>     这一点有利于动态的配置项目

## Step 3 添加库的 Usage Requirments

使用更加现代化的方式添加头文件依赖关系。

==文件架构==

 ```text
step3/
    build/
    MathFunctions/
        CMakeLists.txt
        MathFunctions.cxx
        MathFunctions.h
        mysqrt.cxx
        mysqrt.h
    CMakeLists.txt
    tutorial.cxx
    TutorialConfig.h.in
 ```

==演示==

1. 底层的  MathFunctions

```CMAKE
add_library(MathFunctions MathFunctions.cxx)

# TODO 1: State that anybody linking to MathFunctions needs to include the
# current source directory, while MathFunctions itself doesn't.
# Hint: Use target_include_directories with the INTERFACE keyword
target_include_directories(MathFunctions
                           INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
                           )
# should we use our own math functions
option(USE_MYMATH "Use tutorial provided math implementation" ON)

if (USE_MYMATH)
  target_compile_definitions(MathFunctions PRIVATE "USE_MYMATH")

  # library that just does sqrt
  add_library(SqrtLibrary STATIC
              mysqrt.cxx
              )

  # TODO 6: Link SqrtLibrary to tutorial_compiler_flags
  target_link_libraries(SqrtLibrary PUBLIC tutorial_compiler_flags)
  target_link_libraries(MathFunctions PRIVATE SqrtLibrary)
endif()

# TODO 7: Link MathFunctions to tutorial_compiler_flags
target_link_libraries(SqrtLibrary PUBLIC tutorial_compiler_flags)
```

2. 顶层的      <a id="add_library_usage_2">line 11 add_library_usage_2</a> 

```Cmake
cmake_minimum_required(VERSION 3.10)

# set the project name and version
project(Tutorial VERSION 1.0)

# TODO 4: Replace the following code by:
# * Creating an interface library called tutorial_compiler_flags
#   Hint: use add_library() with the INTERFACE signature
# * Add compiler feature cxx_std_11 to tutorial_compiler_flags
#   Hint: Use target_compile_features()
add_library(tutorial_compiler_flags INTERFACE)
target_compile_features(tutorial_compiler_flags INTERFACE cxx_std_11)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file(TutorialConfig.h.in TutorialConfig.h)

# TODO 2: Remove EXTRA_INCLUDES list
# add the MathFunctions library
add_subdirectory(MathFunctions)
# add the executable
add_executable(Tutorial tutorial.cxx)

# TODO 5: Link Tutorial to tutorial_compiler_flags
target_link_libraries(Tutorial PUBLIC MathFunctions tutorial_compiler_flags)

# TODO 3: Remove use of EXTRA_INCLUDES
# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
target_include_directories(Tutorial PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           )
```

## Step 4 添加生成器表达式





