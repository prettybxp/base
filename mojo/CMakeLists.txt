



# 包含Mojom支持
include(mojom.cmake)


# 添加基本Mojom目标
add_mojom_bindings(internal
    SOURCES
		public/interfaces/bindings/native_struct.mojom
		public/interfaces/bindings/interface_control_messages.mojom
		public/interfaces/bindings/pipe_control_messages.mojom
		public/mojom/base/big_buffer.mojom
)
		
add_mojom_bindings(base_type
    SOURCES
		common/traits_test_service.mojom
		common/file_path.mojom
		common/version.mojom
		common/memory_allocator_dump_cross_process_uid.mojom
		common/process_id.mojom
		common/text_direction.mojom
		common/read_only_buffer.mojom
		common/thread_priority.mojom
		common/logfont_win.mojom
		common/file.mojom
		common/time.mojom
		common/file_info.mojom
		common/values.mojom
		common/string16.mojom
		common/unguessable_token.mojom
		common/test_common_custom_types.mojom
	ALLOW_NATIVE_STRUCTS
)

include_directories(${CMAKE_CURRENT_BINARY_DIR})



set(MOJO_SRCS_POSIX
)

set(MOJO_SRCS_LINUX
)

set(MOJO_SRCS_MAC
)

set(MOJO_SRCS_WINDOWS
  
)

set(MOJO_SRCS_IOS
    
)

set(MOJO_SRCS_ANDROID
)


set(MOJO_SRCS
	common/common_custom_types_struct_traits.cc
	common/values_struct_traits.cc
	common/data_pipe_drainer.h
	common/string16_struct_traits.h
	common/common_custom_types_struct_traits.h
	common/data_pipe_utils.h
	common/mojo_common_export.h
	common/data_pipe_utils.cc
	common/string16_struct_traits.cc
	common/values_struct_traits.h
	common/data_pipe_drainer.cc
	common/read_only_buffer_struct_traits.h
	common/time_struct_traits.h
)


if(OS_MAC)
    list(FILTER MOJO_SRCS EXCLUDE REGEX "_nacl\\.")
    list(FILTER MOJO_SRCS EXCLUDE REGEX "_glib\\.")
    list(FILTER MOJO_SRCS EXCLUDE REGEX "_chromeos\\.")
    list(FILTER MOJO_SRCS EXCLUDE REGEX "_ios\\.")
    list(FILTER MOJO_SRCS EXCLUDE REGEX "_android\\.")
    list(FILTER MOJO_SRCS EXCLUDE REGEX "_win\\.")
    list(FILTER MOJO_SRCS EXCLUDE REGEX "_linux\\.")
endif()

if(OS_LINUX)

	
	FOREACH(src IN ITEMS ${MOJO_SRCS})
		IF(src MATCHES "_nacl\\.")
			LIST(REMOVE_ITEM MOJO_SRCS ${src})
		ENDIF()
	ENDFOREACH()
	
	FOREACH(src IN ITEMS ${MOJO_SRCS})
		IF(src MATCHES "_glib\\.")
			LIST(REMOVE_ITEM MOJO_SRCS ${src})
		ENDIF()
	ENDFOREACH()
	
	FOREACH(src IN ITEMS ${MOJO_SRCS})
		IF(src MATCHES "_chromeos\\.")
			LIST(REMOVE_ITEM MOJO_SRCS ${src})
		ENDIF()
	ENDFOREACH()
	
	FOREACH(src IN ITEMS ${MOJO_SRCS})
		IF(src MATCHES "_ios\\.")
			LIST(REMOVE_ITEM MOJO_SRCS ${src})
		ENDIF()
	ENDFOREACH()
	
	FOREACH(src IN ITEMS ${MOJO_SRCS})
		IF(src MATCHES "_android\\.")
			LIST(REMOVE_ITEM MOJO_SRCS ${src})
		ENDIF()
	ENDFOREACH()
	
	FOREACH(src IN ITEMS ${MOJO_SRCS})
		IF(src MATCHES "_win\\.")
			LIST(REMOVE_ITEM MOJO_SRCS ${src})
		ENDIF()
	ENDFOREACH()
	
	FOREACH(src IN ITEMS ${MOJO_SRCS})
		IF(src MATCHES "_mac\\.")
			LIST(REMOVE_ITEM MOJO_SRCS ${src})
		ENDIF()
	ENDFOREACH()
endif()

if(OS_WINDOWS)
    list(FILTER MOJO_SRCS EXCLUDE REGEX "_nacl\\.")
    list(FILTER MOJO_SRCS EXCLUDE REGEX "_glib\\.")
    list(FILTER MOJO_SRCS EXCLUDE REGEX "_chromeos\\.")
    list(FILTER MOJO_SRCS EXCLUDE REGEX "_ios\\.")
    list(FILTER MOJO_SRCS EXCLUDE REGEX "_android\\.")
    list(FILTER MOJO_SRCS EXCLUDE REGEX "_linux\\.")
    list(FILTER MOJO_SRCS EXCLUDE REGEX "_mac\\.")
endif()

APPEND_PLATFORM_SOURCES(MOJO_SRCS)

add_library(mojo STATIC ${MOJO_SRCS} ${internal_SOURCES} ${base_type_SOURCES})

target_compile_definitions(mojo PRIVATE NO_TCMALLOC)








