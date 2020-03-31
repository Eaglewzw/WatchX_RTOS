# Automatically generated build file. Do not edit.
COMPONENT_INCLUDES += $(PROJECT_PATH)/components/lwip/include/apps $(PROJECT_PATH)/components/lwip/include/apps/sntp $(PROJECT_PATH)/components/lwip/lwip/src/include $(PROJECT_PATH)/components/lwip/port/esp8266/include $(PROJECT_PATH)/components/lwip/port/esp8266/include/arch
COMPONENT_LDFLAGS += -L$(BUILD_DIR_BASE)/lwip -llwip
COMPONENT_LINKER_DEPS += 
COMPONENT_SUBMODULES += $(PROJECT_PATH)/components/lwip/lwip
COMPONENT_LIBRARIES += lwip
COMPONENT_LDFRAGMENTS += $(PROJECT_PATH)/components/lwip/linker.lf
component-lwip-build: 
