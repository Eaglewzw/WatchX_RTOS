# Automatically generated build file. Do not edit.
COMPONENT_INCLUDES += $(PROJECT_PATH)/components/freertos/include $(PROJECT_PATH)/components/freertos/include $(PROJECT_PATH)/components/freertos/include/freertos $(PROJECT_PATH)/components/freertos/include/freertos/private $(PROJECT_PATH)/components/freertos/port/esp8266/include $(PROJECT_PATH)/components/freertos/port/esp8266/include/freertos
COMPONENT_LDFLAGS += -L$(BUILD_DIR_BASE)/freertos -lfreertos
COMPONENT_LINKER_DEPS += 
COMPONENT_SUBMODULES += 
COMPONENT_LIBRARIES += freertos
COMPONENT_LDFRAGMENTS += $(PROJECT_PATH)/components/freertos/linker.lf
component-freertos-build: 
