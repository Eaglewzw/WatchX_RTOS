# Automatically generated build file. Do not edit.
COMPONENT_INCLUDES += $(PROJECT_PATH)/components/newlib/include $(PROJECT_PATH)/components/newlib/newlib/port/include $(PROJECT_PATH)/components/newlib/newlib/include
COMPONENT_LDFLAGS += -L$(BUILD_DIR_BASE)/newlib $(PROJECT_PATH)/components/newlib/newlib/lib/libc_fnano.a $(PROJECT_PATH)/components/newlib/newlib/lib/libm.a -lnewlib -u _printf_float -u _scanf_float
COMPONENT_LINKER_DEPS += $(PROJECT_PATH)/components/newlib/newlib/lib/libc_fnano.a $(PROJECT_PATH)/components/newlib/newlib/lib/libm.a
COMPONENT_SUBMODULES += 
COMPONENT_LIBRARIES += newlib
COMPONENT_LDFRAGMENTS += 
component-newlib-build: 
