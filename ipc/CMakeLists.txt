
#include_directories(${CMAKE_CURRENT_BINARY_DIR})
#add_definitions(-DOS_NACL)


set(IPC_SRCS_POSIX
)

set(IPC_SRCS_LINUX
)

set(IPC_SRCS_MAC

)

set(IPC_SRCS_WINDOWS
  
)

set(IPC_SRCS_IOS
    
)

set(IPC_SRCS_ANDROID
)


set(IPC_SRCS

	ipc_message_utils.cc
    ipc_message_utils.h
	ipc_mojo_param_traits.cc
    ipc_mojo_param_traits.h
	
	native_handle_type_converters.cc
    native_handle_type_converters.h
	
	handle_attachment_win.cc
    handle_attachment_win.h
    handle_win.cc
    handle_win.h

    ipc_message.cc
    ipc_message.h
    ipc_message_attachment.cc
    ipc_message_attachment.h
    ipc_message_attachment_set.cc
    ipc_message_attachment_set.h
    ipc_message_support_export.h
    ipc_mojo_handle_attachment.cc
    ipc_mojo_handle_attachment.h
    ipc_mojo_message_helper.cc
    ipc_mojo_message_helper.h
    ipc_platform_file.cc
    ipc_platform_file.h
    ipc_platform_file_attachment_posix.cc
    ipc_platform_file_attachment_posix.h
    ipc_sync_message.cc
    ipc_sync_message.h
    mach_port_attachment_mac.cc
    mach_port_attachment_mac.h
    mach_port_mac.cc
    mach_port_mac.h
)


if(OS_MAC)
    list(FILTER IPC_SRCS EXCLUDE REGEX "_nacl\\.")
    list(FILTER IPC_SRCS EXCLUDE REGEX "_glib\\.")
    list(FILTER IPC_SRCS EXCLUDE REGEX "_chromeos\\.")
    list(FILTER IPC_SRCS EXCLUDE REGEX "_ios\\.")
    list(FILTER IPC_SRCS EXCLUDE REGEX "_android\\.")
    list(FILTER IPC_SRCS EXCLUDE REGEX "_win\\.")
    list(FILTER IPC_SRCS EXCLUDE REGEX "_linux\\.")
endif()

if(OS_LINUX)

	
	FOREACH(src IN ITEMS ${IPC_SRCS})
		IF(src MATCHES "_nacl\\.")
			LIST(REMOVE_ITEM IPC_SRCS ${src})
		ENDIF()
	ENDFOREACH()
	
	FOREACH(src IN ITEMS ${IPC_SRCS})
		IF(src MATCHES "_glib\\.")
			LIST(REMOVE_ITEM IPC_SRCS ${src})
		ENDIF()
	ENDFOREACH()
	
	FOREACH(src IN ITEMS ${IPC_SRCS})
		IF(src MATCHES "_chromeos\\.")
			LIST(REMOVE_ITEM IPC_SRCS ${src})
		ENDIF()
	ENDFOREACH()
	
	FOREACH(src IN ITEMS ${IPC_SRCS})
		IF(src MATCHES "_ios\\.")
			LIST(REMOVE_ITEM IPC_SRCS ${src})
		ENDIF()
	ENDFOREACH()
	
	FOREACH(src IN ITEMS ${IPC_SRCS})
		IF(src MATCHES "_android\\.")
			LIST(REMOVE_ITEM IPC_SRCS ${src})
		ENDIF()
	ENDFOREACH()
	
	FOREACH(src IN ITEMS ${IPC_SRCS})
		IF(src MATCHES "_win\\.")
			LIST(REMOVE_ITEM IPC_SRCS ${src})
		ENDIF()
	ENDFOREACH()
	
	FOREACH(src IN ITEMS ${IPC_SRCS})
		IF(src MATCHES "_mac\\.")
			LIST(REMOVE_ITEM IPC_SRCS ${src})
		ENDIF()
	ENDFOREACH()
	
	FOREACH(src IN ITEMS ${IPC_SRCS})
		IF(src MATCHES "_fuchsia\\.")
			LIST(REMOVE_ITEM IPC_SRCS ${src})
		ENDIF()
	ENDFOREACH()

endif()



if(OS_WINDOWS)
    list(FILTER IPC_SRCS EXCLUDE REGEX "_nacl\\.")
    list(FILTER IPC_SRCS EXCLUDE REGEX "_glib\\.")
    list(FILTER IPC_SRCS EXCLUDE REGEX "_chromeos\\.")
    list(FILTER IPC_SRCS EXCLUDE REGEX "_ios\\.")
    list(FILTER IPC_SRCS EXCLUDE REGEX "_android\\.")
    list(FILTER IPC_SRCS EXCLUDE REGEX "_linux\\.")
    list(FILTER IPC_SRCS EXCLUDE REGEX "_mac\\.")
endif()

APPEND_PLATFORM_SOURCES(IPC_SRCS)

add_library(ipc STATIC ${IPC_SRCS})

target_compile_definitions(ipc PRIVATE NO_TCMALLOC)








