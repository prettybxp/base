# mojom.cmake - Mojom IDL编译支持
cmake_minimum_required(VERSION 3.5)

# 设置Mojom生成器路径
set(MOJOM_GENERATOR_ROOT "${CMAKE_SOURCE_DIR}/mojo/public/tools/bindings")
set(MOJOM_GENERATOR_SCRIPT "${MOJOM_GENERATOR_ROOT}/mojom_bindings_generator.py")
set(GENERATE_EXPORT_HEADER_SCRIPT "${MOJOM_GENERATOR_ROOT}/generate_export_header.py")

# 查找Python解释器
find_package(PythonInterp REQUIRED)

# 定义全局Mojom设置
option(ENABLE_MOJOM_TYPEMAPPING "Enable typemapping support" ON)
option(ENABLE_SCRAMBLED_MESSAGE_IDS "Enable message ID scrambling" OFF)
set(MOJOM_MESSAGE_ID_SALT_PATH "${CMAKE_SOURCE_DIR}/chrome/VERSION" CACHE FILEPATH "Path to message ID salt file")
set(MOJOM_MESSAGE_ID_SALT_SUFFIX_PATH "" CACHE FILEPATH "Path to message ID salt suffix file")

# 添加Mojom目标函数
function(add_mojom_bindings TARGET)
    # 解析参数
    set(options  
        ALLOW_NATIVE_STRUCTS 
        SCRAMBLE_MESSAGE_IDS
    )
    set(oneValueArgs 
        COMPONENT_OUTPUT_PREFIX 
        COMPONENT_MACRO_PREFIX
        EXPORT_HEADER
    )
    set(multiValueArgs 
        SOURCES 
        DEPS 
        PUBLIC_DEPS 
        IMPORT_DIRS 
    )
    
    cmake_parse_arguments(MOJOM 
        "${options}" 
        "${oneValueArgs}" 
        "${multiValueArgs}" 
        ${ARGN}
    )
	
    
    # 处理所有依赖
    set(ALL_DEPS ${MOJOM_DEPS} ${MOJOM_PUBLIC_DEPS})
    
    # 创建目标组标记
    add_custom_target(${TARGET}__is_mojom)
    
    # 检查依赖是否都是Mojom目标
    foreach(DEP ${ALL_DEPS})
        add_dependencies(${TARGET}__is_mojom ${DEP}__is_mojom)
    endforeach()
    
    # 生成共享代码
    if(MOJOM_SOURCES)
        # 设置生成器参数
        set(COMMON_GENERATOR_ARGS
            "--use_bundled_pylibs"
            "generate"
            "${SOURCE}"
            "-d" "${CMAKE_SOURCE_DIR}"
            "-I" "${CMAKE_SOURCE_DIR}"
            "-o" "${CMAKE_CURRENT_BINARY_DIR}"
            "--bytecode_path" "${CMAKE_SOURCE_DIR}/mojo/public/tools/bindings"
        )
		
        
        # 处理消息ID加扰
        if(MOJOM_SCRAMBLE_MESSAGE_IDS) 
            list(APPEND COMMON_GENERATOR_ARGS
                "--scrambled_message_id_salt_path" "${MOJOM_MESSAGE_ID_SALT_PATH}"
            )
            if(MOJOM_MESSAGE_ID_SALT_SUFFIX_PATH)
                list(APPEND COMMON_GENERATOR_ARGS
                    "--scrambled_message_id_salt_path" "${MOJOM_MESSAGE_ID_SALT_SUFFIX_PATH}"
                )
            endif()
        endif()
        
        # 允许原生结构
        if(MOJOM_ALLOW_NATIVE_STRUCTS)
            list(APPEND COMMON_GENERATOR_ARGS "--allow_native_structs")
        endif()
        
        # 导入目录
        foreach(IMPORT_DIR ${MOJOM_IMPORT_DIRS})
            list(APPEND COMMON_GENERATOR_ARGS "-I" "${IMPORT_DIR}")
        endforeach()
        
        # 共享导出头处理
        if(MOJOM_COMPONENT_MACRO_PREFIX)
            set(SHARED_COMPONENT_EXPORT_MACRO "${MOJOM_COMPONENT_MACRO_PREFIX}_SHARED_EXPORT")
            set(SHARED_COMPONENT_IMPL_MACRO "${MOJOM_COMPONENT_MACRO_PREFIX}_SHARED_IMPL")
            set(SHARED_COMPONENT_OUTPUT_NAME "${MOJOM_COMPONENT_OUTPUT_PREFIX}_shared")
        endif()
        
        # 为每个源文件生成规则
        set(SHARED_CPP_OUTPUTS)
        foreach(SOURCE ${MOJOM_SOURCES})
            get_filename_component(SOURCE_NAME ${SOURCE} NAME_WE)
            set(SOURCE_GEN_DIR "${CMAKE_CURRENT_BINARY_DIR}/mojo")
            
            # 共享代码输出
            set(OUTPUTS
                "${SOURCE_GEN_DIR}/${SOURCE}-shared-internal.h"
                "${SOURCE_GEN_DIR}/${SOURCE}-shared.cc"
                "${SOURCE_GEN_DIR}/${SOURCE}-shared.h"
            )
            list(APPEND SHARED_CPP_OUTPUTS ${OUTPUTS})
            
            # 自定义命令
            add_custom_command(
                OUTPUT ${OUTPUTS}
                COMMAND ${PYTHON_EXECUTABLE} ${MOJOM_GENERATOR_SCRIPT}
                    ${COMMON_GENERATOR_ARGS}
					"--generate_non_variant_code"
                    "-g" "c++" ${SOURCE}
                DEPENDS ${SOURCE} ${MOJOM_GENERATOR_SCRIPT}
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                COMMENT "Generating shared bindings for ${SOURCE}"
            )
        endforeach()
		
		foreach(SOURCE ${MOJOM_SOURCES})
            get_filename_component(SOURCE_NAME ${SOURCE} NAME_WE)
            set(SOURCE_GEN_DIR "${CMAKE_CURRENT_BINARY_DIR}/mojo")
            
            # 共享代码输出
            set(OUTPUTS
                "${SOURCE_GEN_DIR}/${SOURCE}.cc"
                "${SOURCE_GEN_DIR}/${SOURCE}.h"
            )
            list(APPEND SHARED_CPP_OUTPUTS ${OUTPUTS})
            
            # 自定义命令
            add_custom_command(
                OUTPUT ${OUTPUTS}
                COMMAND ${PYTHON_EXECUTABLE} ${MOJOM_GENERATOR_SCRIPT}
                    ${COMMON_GENERATOR_ARGS}
                    "-g" "c++" ${SOURCE}
                DEPENDS ${SOURCE} ${MOJOM_GENERATOR_SCRIPT}
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                COMMENT "Generating shared bindings for ${SOURCE}"
            )
        endforeach()
        
        # 创建共享库目标
        #add_library(${TARGET}_shared STATIC ${SHARED_CPP_OUTPUTS})
		set(${TARGET}_SOURCES ${SHARED_CPP_OUTPUTS} PARENT_SCOPE)
        

        # 处理组件宏
        if(SHARED_COMPONENT_EXPORT_MACRO)
            # 生成共享导出头
            set(GENERATED_SHARED_EXPORT_HEADER "${CMAKE_CURRENT_BINARY_DIR}/${TARGET}_shared_export.h")
            add_custom_command(
                OUTPUT ${GENERATED_SHARED_EXPORT_HEADER}
                COMMAND ${PYTHON_EXECUTABLE} ${GENERATE_EXPORT_HEADER_SCRIPT}
                    "--export_macro" "${SHARED_COMPONENT_EXPORT_MACRO}"
                    "--impl_macro" "${SHARED_COMPONENT_IMPL_MACRO}"
                    "--output_file" "${GENERATED_SHARED_EXPORT_HEADER}"
                COMMENT "Generating shared export header for ${TARGET}"
            )
            
            # 添加到目标
            target_sources(${TARGET}_shared PRIVATE ${GENERATED_SHARED_EXPORT_HEADER})
            target_compile_definitions(${TARGET}_shared PRIVATE ${SHARED_COMPONENT_IMPL_MACRO})
        endif()
    endif()
    


endfunction()

