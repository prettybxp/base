# 包含Mojom支持
include(mojom.cmake)

# 添加基本Mojom目标
add_mojom_bindings(baofish
    SOURCES
        common/time.mojom
    IMPORT_DIRS
        ${CMAKE_SOURCE_DIR}/mojo/public/interfaces
    ALLOW_NATIVE_STRUCTS
)
