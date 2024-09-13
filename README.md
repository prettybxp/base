Why chrome-base? 
Chrome base is a good C++ base library, like boost, but it is smaller and simpler than boost and has many useful features. 
 
Objectives and characteristics 
1. Separate chrome-base from chome so it can be compiled separately. 
2, support windows, mac, linux and other platforms, and finally cross-compile period applied to embedded platforms 
3. Build with CMake, which is simpler and easier to port than gn+ninja 
 
version
Based on Chrome 65.0.3325.181, newer versions require C++17 and above, and Chrome 65 only requires C++14 to accommodate embedded platforms 
 
ChangeLog 
2024-9-10, initial submission, start building based on CMake 
2024-9-11, mac platform compiled by MAC OS X 14.6.1, xcode 15.4 
2024-9-12, linux platform compilation connect through, centos, gcc version 11.5.0

为什么是Chrome-base
Chrome的base是一个优秀的C++基础库，如同boost，但它比boost更小更简单，还有很多实用功能。

目标和特点
1、将chrome-base从chome中剥离，使能够单独编译，
2、支持windows，mac，linux等多平台，最终交叉编译时期应用于嵌入式平台
3、使用CMake构建，相较于gn+ninja更简单方便，更容易移植

版本
基于Chrome 65.0.3325.181, 更新的版本需要C++17即以上版本，为了适应嵌入式平台，Chrome 65只需要C++14即可

提交历史
2024-9-10，初时提交，基于CMake开始构建
2024-9-11，mac平台编译通过，macosx 14.6.1, xcode 15.4
2024-9-12，linux平台编译连接通过, centos, gcc version 11.5.0 





