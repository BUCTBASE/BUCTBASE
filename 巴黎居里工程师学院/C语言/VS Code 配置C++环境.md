注意：Cpp兼容C，配置文件以后可以复制粘贴在本机上直接用

# 准备

#### 1.Visual Studio Code

- 下载 Visual Studio Code：[Visual Studio Code - Code Editing. Redefined](https%3A//code.visualstudio.com/%23alt-downloads)
- 安装中文扩展，C/C++扩展，Code Runner扩展
Code Runner的配置（最重要就是 Run In Terminal，调用 VS Code 的内置终端运行程序，可以满足输入要求）
![图片.png](https://upload-images.jianshu.io/upload_images/16807503-a27a5cf3b84fecd0.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

### 2.编译器MinGW-w64
- 下载 MinGW-w64-：[MinGW-w64 - for 32 and 64 bit Windows](https%3A//sourceforge.net/projects/mingw-w64/files/mingw-w64/mingw-w64-release/)，直接向下滚动，在较新版本中选择 [x86_64-posix-seh] 进行下载
- 解压添加系统变量：不用安装，解压到合适的位置（你一般程序的位置）并把mingw64的 bin目录路径（例 C:\Program Files\mingw64\bin）添加到系统环境变量PATH内
- 验证：Win + R --> cmd ，输入 gcc -v 确认环境变量是否成功配置

# 配置
新建工程文件夹，打开vscode并进入这个新建工程文件夹

### 1.C/C++: 编辑配置 (UI)
- 按下 Ctrl+Shift+P，输入 C/C++，点击 C/C++: 编辑配置 (UI)
- 在配置选项中， Complier path 选择 g++.exe  ；Intellisense mode 选 gcc-x64
- 用文件管理器打开「新建工程文件夹」，按住 Shift 并在空白处点击右键，「在此处右键打开 PowerShell 窗口」，输入 g++ main.cpp -v，在输出里找出类似下面的文字，并复制下来回到VScode粘贴到 「Include path /包含路径」 内，记得删除每行开头的空格

```
C:/Program Files/mingw64/bin/../lib/gcc/x86_64-w64-mingw32/8.1.0/include/c++
 C:/Program Files/mingw64/bin/../lib/gcc/x86_64-w64-mingw32/8.1.0/include/c++/x86_64-w64-mingw32
 C:/Program Files/mingw64/bin/../lib/gcc/x86_64-w64-mingw32/8.1.0/include/c++/backward
 C:/Program Files/mingw64/bin/../lib/gcc/x86_64-w64-mingw32/8.1.0/include
 C:/Program Files/mingw64/bin/../lib/gcc/x86_64-w64-mingw32/8.1.0/include-fixed
 C:/Program Files/mingw64/bin/../lib/gcc/x86_64-w64-mingw32/8.1.0/../../../../x86_64-w64-mingw32/include
```

下面的 C standard 和 C++ standard 可以根据自己的需要来选择，完成这部分的编辑

### 配置 task.json
按下 Ctrl+Shift+P，输入 task，点击「任务: 配置默认生成任务」，接着点击「使用模板创建 tasks.json 文件」，最后点击「Other 运行任意外部命令的示例」
在打开的 tasks.json 里，复制粘贴如下代码（具体的含义可参考知乎谭九鼎的回答）

```
{
    // See https://go.microsoft.com/fwlink/?LinkId=733558
    // for the documentation about the tasks.json format
    "version": "2.0.0",
    "tasks": [
        {
            "type": "process",
            "label": "g++.exe build active file",
            "command": "g++",
            "args": [
                "-g",
                "${file}",
                "-Wall",
                "-Wextra",
                "-save-temps",
                "-static-libgcc",
                "-o",
                "${fileDirname}\\${fileBasenameNoExtension}.exe"
            ],
            "problemMatcher": [
                "$gcc"
            ],
            "group": {
                "kind": "build",
                "isDefault": true
            }
        }
    ]
}
```

### 配置 launch.json
- 按下 Ctrl+Shift+P，输入 launch，点击「调试: 打开 launch.json」-->「C++ (GDB/LLDB)」-->默认配置。

- 在 launch.json 里，复制粘贴如下所示的代码（具体的含义可参考谭九鼎的回答）。
- 注意， "miDebuggerPath"要修改一下，路径为指向MinGW的gdb.exe （例 C:/Program Files/mingw64/bin/gdb.exe ）
```
{
    // 使用 IntelliSense 了解相关属性。 
    // 悬停以查看现有属性的描述。
    // 欲了解更多信息，请访问: https://go.microsoft.com/fwlink/?linkid=830387
    "version": "0.2.0",
    "configurations": [
        {
            "name": "(gdb) Launch",
            "type": "cppdbg",
            "request": "launch",
            "program": "${fileDirname}\\${fileBasenameNoExtension}.exe",
            "args": [],
            "stopAtEntry": false,
            "cwd": "${fileDirname}",
            "environment": [],
            "externalConsole": false,
            "internalConsoleOptions": "neverOpen",
            "MIMode": "gdb",
            "miDebuggerPath": "Z:/VisualStudioCode/x86_64-8.1.0-release-posix-seh-rt_v6-rev0/mingw64/bin/gdb.exe",
            //需要修改
            "setupCommands": [
                {
                    "description": "Enable pretty-printing for gdb",
                    "text": "-enable-pretty-printing",
                    "ignoreFailures": false
                }
            ],
            "preLaunchTask": "g++.exe build active file"
        }
    ]
}
```


# 编译、调试和运行
在 VSC 打开 main.cpp，写一段代码，然后保存

按Ctrl+Shift+B单纯编译，按F5为编译加调试
 >不要把f5当作编译来使用（有的bug只会产生警告，不会阻止编译）

插件Run Code的话 点击右上角图标 ，右击然后点击Run Code 或 Ctrl+Alt+N 都可以运行