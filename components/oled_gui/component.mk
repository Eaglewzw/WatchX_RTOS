#
# "main" pseudo-component makefile.
#
# (Uses default behaviour of compiling all source files in directory, adding 'include' to include path.)
#添加同级目录下需要编译的头文件 
COMPONENT_ADD_INCLUDEDIRS :=  inc
#添加同级目录下需要编译的C文件
COMPONENT_SRCDIRS := src