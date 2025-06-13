



# 包含Mojom支持
include(mojom.cmake)


# 添加基本Mojom目标
add_mojom_bindings(internal
    SOURCES
		public/interfaces/bindings/native_struct.mojom
		public/interfaces/bindings/interface_control_messages.mojom
		public/interfaces/bindings/pipe_control_messages.mojom
		public/mojom/base/big_buffer.mojom
		logger.mojom
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
add_definitions(-DOS_NACL)


set(MOJO_SRCS_POSIX
)

set(MOJO_SRCS_LINUX
)

set(MOJO_SRCS_MAC
	edk/system/mach_port_relay.h
	edk/system/mach_port_relay.cc
)

set(MOJO_SRCS_WINDOWS
  
)

set(MOJO_SRCS_IOS
    
)

set(MOJO_SRCS_ANDROID
)


set(MOJO_SRCS
	public/c/system/types.h
	public/c/system/data_pipe.h
	public/c/system/functions.h
	public/c/system/thunks.h
	public/c/system/system_export.h
	public/c/system/core.h
	public/c/system/buffer.h
	public/c/system/thunks.cc
	public/c/system/macros.h
	public/c/system/platform_handle.h
	public/c/system/message_pipe.h
	public/c/system/set_thunks_for_app.cc
	public/c/system/watcher.h

	public/cpp/system/data_pipe.h
	public/cpp/system/functions.h
	public/cpp/system/wait.cc
	public/cpp/system/handle.h
	public/cpp/system/wait_set.cc
	public/cpp/system/message_pipe.cc
	public/cpp/system/system_export.h
	public/cpp/system/file_data_pipe_producer.h
	public/cpp/system/simple_watcher.cc
	public/cpp/system/core.h
	public/cpp/system/wait_set.h
	public/cpp/system/message.h
	public/cpp/system/handle_signal_tracker.cc
	public/cpp/system/buffer.h
	public/cpp/system/platform_handle.cc
	public/cpp/system/platform_handle.h
	public/cpp/system/buffer.cc
	public/cpp/system/watcher.cc
	public/cpp/system/wait.h
	public/cpp/system/handle_signal_tracker.h
	public/cpp/system/handle_signals_state.h
	public/cpp/system/message_pipe.h
	public/cpp/system/simple_watcher.h
	public/cpp/system/watcher.h
	public/cpp/system/string_data_pipe_producer.cc
	public/cpp/system/file_data_pipe_producer.cc
	public/cpp/system/string_data_pipe_producer.h

	public/cpp/bindings/array_traits_span.h
	public/cpp/bindings/array_traits.h
	public/cpp/bindings/struct_traits.h
	public/cpp/bindings/raw_ptr_impl_ref_traits.h
	public/cpp/bindings/map.h
	public/cpp/bindings/associated_interface_request.h
	public/cpp/bindings/type_converter.h
	public/cpp/bindings/binding.h
	public/cpp/bindings/pipe_control_message_handler.h
	public/cpp/bindings/array_traits_wtf_vector.h
	public/cpp/bindings/callback_helpers.h
	public/cpp/bindings/sync_event_watcher.h
	public/cpp/bindings/string_traits_stl.h
	public/cpp/bindings/sync_handle_registry.h
	public/cpp/bindings/strong_binding.h
	public/cpp/bindings/interface_id.h
	public/cpp/bindings/native_enum.h
	public/cpp/bindings/struct_ptr.h
	public/cpp/bindings/map_traits.h
	public/cpp/bindings/array_data_view.h
	public/cpp/bindings/thread_safe_interface_ptr.h
	public/cpp/bindings/message_header_validator.h
	public/cpp/bindings/string_traits_string16.h
	public/cpp/bindings/message.h
	public/cpp/bindings/sync_call_restrictions.h
	public/cpp/bindings/associated_group.h
	public/cpp/bindings/strong_associated_binding_set.h
	public/cpp/bindings/binding_set.h
	public/cpp/bindings/associated_binding.h
	public/cpp/bindings/interface_ptr.h
	public/cpp/bindings/associated_interface_ptr.h
	public/cpp/bindings/sync_handle_watcher.h
	public/cpp/bindings/string_traits.h
	public/cpp/bindings/interface_endpoint_client.h
	public/cpp/bindings/enum_traits.h
	public/cpp/bindings/string_traits_wtf.h
	public/cpp/bindings/connection_error_callback.h
	public/cpp/bindings/bindings_export.h
	public/cpp/bindings/map_traits_stl.h
	public/cpp/bindings/disconnect_reason.h
	public/cpp/bindings/associated_group_controller.h
	public/cpp/bindings/unique_ptr_impl_ref_traits.h
	public/cpp/bindings/union_traits.h
	public/cpp/bindings/array_traits_stl.h
	public/cpp/bindings/connector.h
	public/cpp/bindings/string_data_view.h
	public/cpp/bindings/interface_endpoint_controller.h
	public/cpp/bindings/interface_request.h
	public/cpp/bindings/map_traits_wtf_hash_map.h
	public/cpp/bindings/associated_binding_set.h
	public/cpp/bindings/clone_traits.h
	public/cpp/bindings/map_data_view.h
	public/cpp/bindings/pipe_control_message_handler_delegate.h
	public/cpp/bindings/equals_traits.h
	public/cpp/bindings/filter_chain.h
	public/cpp/bindings/pipe_control_message_proxy.h
	public/cpp/bindings/strong_binding_set.h
	public/cpp/bindings/string_traits_string_piece.h
	public/cpp/bindings/strong_associated_binding.h
	public/cpp/bindings/interface_data_view.h
	public/cpp/bindings/interface_ptr_info.h
	public/cpp/bindings/scoped_interface_endpoint_handle.h
	public/cpp/bindings/interface_ptr_set.h
	public/cpp/bindings/associated_interface_ptr_info.h
	
	public/cpp/bindings/lib/multiplex_router.cc
	public/cpp/bindings/lib/fixed_buffer.cc
	public/cpp/bindings/lib/associated_interface_ptr.cc
	public/cpp/bindings/lib/validate_params.h
	public/cpp/bindings/lib/array_internal.cc
	public/cpp/bindings/lib/serialization_context.cc
	public/cpp/bindings/lib/associated_binding.cc
	public/cpp/bindings/lib/string_traits_string16.cc
	public/cpp/bindings/lib/fixed_buffer.h
	public/cpp/bindings/lib/interface_ptr_state.h
	public/cpp/bindings/lib/validation_util.h
	public/cpp/bindings/lib/validation_errors.h
	public/cpp/bindings/lib/handle_interface_serialization.h
	public/cpp/bindings/lib/binding_state.cc
	public/cpp/bindings/lib/template_util.h
	public/cpp/bindings/lib/sync_event_watcher.cc
	public/cpp/bindings/lib/task_runner_helper.cc
	public/cpp/bindings/lib/interface_ptr_state.cc
	public/cpp/bindings/lib/task_runner_helper.h
	public/cpp/bindings/lib/native_struct_serialization.h
	public/cpp/bindings/lib/control_message_handler.cc
	public/cpp/bindings/lib/unserialized_message_context.cc
	public/cpp/bindings/lib/binding_state.h
	public/cpp/bindings/lib/serialization_context.h
	public/cpp/bindings/lib/map_serialization.h
	public/cpp/bindings/lib/serialization_forward.h
	public/cpp/bindings/lib/associated_interface_ptr_state.h
	public/cpp/bindings/lib/wtf_hash_util.h
	public/cpp/bindings/lib/native_enum_serialization.h
	public/cpp/bindings/lib/associated_group_controller.cc
	public/cpp/bindings/lib/bindings_internal.h
	public/cpp/bindings/lib/hash_util.h
	public/cpp/bindings/lib/associated_interface_ptr_state.cc
	public/cpp/bindings/lib/wtf_clone_equals_util.h
	public/cpp/bindings/lib/filter_chain.cc
	public/cpp/bindings/lib/message_internal.cc
	public/cpp/bindings/lib/buffer.h
	public/cpp/bindings/lib/scoped_interface_endpoint_handle.cc
	public/cpp/bindings/lib/serialization_util.h
	public/cpp/bindings/lib/control_message_proxy.cc
	public/cpp/bindings/lib/string_serialization.h
	public/cpp/bindings/lib/buffer.cc
	public/cpp/bindings/lib/message_header_validator.cc
	public/cpp/bindings/lib/native_enum_data.h
	public/cpp/bindings/lib/validation_util.cc
	public/cpp/bindings/lib/wtf_serialization.h
	public/cpp/bindings/lib/sync_handle_watcher.cc
	public/cpp/bindings/lib/control_message_handler.h
	public/cpp/bindings/lib/may_auto_lock.h
	public/cpp/bindings/lib/validation_errors.cc
	public/cpp/bindings/lib/interface_endpoint_client.cc
	public/cpp/bindings/lib/pipe_control_message_proxy.cc
	public/cpp/bindings/lib/message_internal.h
	#public/cpp/bindings/lib/string_traits_wtf.cc
	public/cpp/bindings/lib/pipe_control_message_handler.cc
	public/cpp/bindings/lib/associated_group.cc
	public/cpp/bindings/lib/native_struct_serialization.cc
	public/cpp/bindings/lib/map_data_internal.h
	public/cpp/bindings/lib/array_internal.h
	public/cpp/bindings/lib/control_message_proxy.h
	public/cpp/bindings/lib/validation_context.h
	public/cpp/bindings/lib/unserialized_message_context.h
	public/cpp/bindings/lib/validation_context.cc
	public/cpp/bindings/lib/sync_call_restrictions.cc
	public/cpp/bindings/lib/sync_handle_registry.cc
	public/cpp/bindings/lib/multiplex_router.h
	public/cpp/bindings/lib/serialization.h
	public/cpp/bindings/lib/message.cc
	public/cpp/bindings/lib/array_serialization.h
	public/cpp/bindings/lib/connector.cc
	
	public/cpp/base/big_buffer_struct_traits.h
	public/cpp/base/big_buffer_struct_traits.cc
	public/cpp/base/mojo_base_export.h
	public/cpp/base/big_buffer.h
	public/cpp/base/mojo_base_traits_export.h
	public/cpp/base/big_buffer.cc
	
	#public/tools/fuzzers/mojo_parse_message_fuzzer.cc
	#public/tools/fuzzers/fuzz_impl.h
	#public/tools/fuzzers/mojo_fuzzer_message_dump.cc
	#public/tools/fuzzers/fuzz_impl.cc
	
	common/common_custom_types_struct_traits.cc
	common/values_struct_traits.cc
	common/data_pipe_drainer.h
	#common/string16_unittest.cc
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

	#edk/system/message_pipe_unittest.cc
	#edk/system/handle_table_unittest.cc
	edk/system/broker.h
	edk/system/core_test_base.h
	edk/system/data_pipe_producer_dispatcher.cc
	edk/system/user_message_impl.h
	edk/system/channel.h
	#edk/system/signals_unittest.cc
	edk/system/watcher_set.h
	edk/system/user_message_impl.cc
	edk/system/node_channel.cc
	edk/system/atomic_flag.h
	edk/system/mapping_table.h
	
	#edk/system/platform_wrapper_unittest.cc
	#edk/system/channel_unittest.cc
	edk/system/request_context.h
	edk/system/broker_win.cc
	#edk/system/message_unittest.cc
	edk/system/message_pipe_dispatcher.cc
	edk/system/data_pipe_control_message.h
	edk/system/request_context.cc
	edk/system/core.cc
	#edk/system/platform_handle_dispatcher_unittest.cc
	edk/system/data_pipe_producer_dispatcher.h
	#edk/system/shared_buffer_unittest.cc
	#edk/system/test_utils.h
	edk/system/handle_table.h
	edk/system/data_pipe_consumer_dispatcher.cc
	edk/system/core.h
	edk/system/data_pipe_control_message.cc
	#edk/system/options_validation_unittest.cc

	edk/system/shared_buffer_dispatcher.cc
	edk/system/platform_handle_dispatcher.cc
	edk/system/configuration.cc
	edk/system/dispatcher.cc
	edk/system/broker_messages.h
	edk/system/node_controller.cc
	edk/system/watcher_dispatcher.cc
	#edk/system/data_pipe_unittest.cc
	edk/system/watch.cc
	#edk/system/message_pipe_perftest.cc
	#edk/system/core_unittest.cc
	edk/system/broker_host.h
	edk/system/platform_handle_dispatcher.h
	edk/system/message_pipe_dispatcher.h
	edk/system/broker_host.cc
	#edk/system/shared_buffer_dispatcher_unittest.cc
	edk/system/system_impl_export.h
	edk/system/channel.cc
	edk/system/node_controller.h
	#edk/system/channel_fuchsia.cc
	edk/system/mapping_table.cc
	edk/system/watcher_set.cc
	edk/system/watcher_dispatcher.h
	edk/system/configuration.h
	#edk/system/core_test_base.cc
	#edk/system/watcher_unittest.cc
	edk/system/node_channel.h
	edk/system/handle_table.cc
	edk/system/dispatcher.h
	edk/system/data_pipe_consumer_dispatcher.h
	edk/system/handle_signals_state.h
	edk/system/channel_win.cc
	edk/system/options_validation.h
	edk/system/shared_buffer_dispatcher.h
	#edk/system/multiprocess_message_pipe_unittest.cc
	#edk/system/test_utils.cc
	edk/system/channel_posix.cc
	edk/system/broker_posix.cc
	edk/system/watch.h
	edk/system/ports/name.cc
	edk/system/ports/port_locker.cc
	edk/system/ports/user_data.h
	edk/system/ports/name.h
	edk/system/ports/node.h
	edk/system/ports/user_message.h
	#edk/system/ports/name_unittest.cc
	edk/system/ports/port.cc
	edk/system/ports/port_locker.h
	edk/system/ports/message_filter.h
	edk/system/ports/message_queue.h
	edk/system/ports/message_queue.cc
	edk/system/ports/event.h
	#edk/system/ports/ports_unittest.cc
	edk/system/ports/node.cc
	edk/system/ports/event.cc
	edk/system/ports/node_delegate.h
	edk/system/ports/port_ref.h
	edk/system/ports/port.h
	edk/system/ports/user_message.cc
	edk/system/ports/port_ref.cc
	
	edk/embedder/platform_handle_utils_posix.cc

	edk/embedder/platform_shared_buffer.h
	edk/embedder/platform_handle_utils.h
	edk/embedder/platform_channel_pair_posix.cc
	edk/embedder/platform_channel_pair.h
	edk/embedder/platform_channel_pair.cc
	edk/embedder/outgoing_broker_client_invitation.cc
	edk/embedder/platform_handle_utils_win.cc
	edk/embedder/scoped_ipc_support.cc

	edk/embedder/embedder_internal.h
	edk/embedder/entrypoints.cc
	edk/embedder/platform_channel_pair_win.cc
	edk/embedder/embedder.h
	edk/embedder/test_embedder.cc
	edk/embedder/scoped_platform_handle.h
	edk/embedder/peer_connection.h
	edk/embedder/named_platform_channel_pair.h
	edk/embedder/named_platform_handle_utils_win.cc
	#edk/embedder/named_platform_handle_utils_fuchsia.cc
	edk/embedder/incoming_broker_client_invitation.h
	edk/embedder/platform_handle.cc
	edk/embedder/entrypoints.h
	edk/embedder/platform_handle.h
	edk/embedder/named_platform_handle_utils_posix.cc
	edk/embedder/embedder.cc
	edk/embedder/peer_connection.cc
	edk/embedder/platform_handle_utils_fuchsia.cc
	edk/embedder/outgoing_broker_client_invitation.h
	edk/embedder/incoming_broker_client_invitation.cc
	#edk/embedder/platform_shared_buffer_unittest.cc
	edk/embedder/platform_shared_buffer.cc
	edk/embedder/platform_channel_pair_fuchsia.cc
	edk/embedder/test_embedder.h
	edk/embedder/configuration.h
	edk/embedder/platform_channel_utils_posix.cc
	edk/embedder/transport_protocol.h
	edk/embedder/connection_params.cc
	edk/embedder/named_platform_handle_utils.h
	edk/embedder/named_platform_handle.h
	edk/embedder/named_platform_channel_pair_win.cc
	edk/embedder/scoped_ipc_support.h
	edk/embedder/platform_channel_utils_posix.h
	edk/embedder/connection_params.h
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
	
	FOREACH(src IN ITEMS ${MOJO_SRCS})
		IF(src MATCHES "_fuchsia\\.")
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








