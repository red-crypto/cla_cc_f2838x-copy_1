################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccs2010/ccs/tools/compiler/ti-cgt-c2000_22.6.2.LTS

GEN_OPTS__FLAG := --cmd_file="syscfg/board.opt" --cmd_file="syscfg/c2000ware_libraries.opt" 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./syscfg/board.obj" \
"./syscfg/c2000ware_libraries.obj" \
"./lab_cla_tasks.obj" \
"./App/System_main.obj" \
"./App/lab_main.obj" \
"./Common/Ringbuffer.obj" \
"./Common/System_timer.obj" \
"./Drivers/Comm/spi_t.obj" \
"./Drivers/Motor/DRV8711.obj" \
"./Drivers/Motor/Step_motor.obj" \
"./device/device.obj" \
"./device/f2838x_codestartbranch.obj" \
"../2838x_RAM_CLA_lnk_cpu1.cmd" \
"C:/ti/c2000/C2000Ware_5_05_00_00/driverlib/f2838x/driverlib/ccs/Debug/driverlib.lib" \
$(GEN_CMDS__FLAG) \
-llibc.a \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include App/subdir_vars.mk
-include Common/subdir_vars.mk
-include Drivers/Comm/subdir_vars.mk
-include Drivers/Motor/subdir_vars.mk
-include device/subdir_vars.mk
-include subdir_rules.mk
-include App/subdir_rules.mk
-include Common/subdir_rules.mk
-include Drivers/Comm/subdir_rules.mk
-include Drivers/Motor/subdir_rules.mk
-include device/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
cla_cc_f2838x\ copy.out 

EXE_OUTPUTS__QUOTED += \
"cla_cc_f2838x copy.out" 


# All Target
all: $(OBJS) $(CMD_SRCS) $(LIB_SRCS) $(GEN_CMDS)
	@$(MAKE) --no-print-directory -Onone "cla_cc_f2838x copy.out"

# Tool invocations
cla_cc_f2838x\ copy.out: $(OBJS) $(CMD_SRCS) $(LIB_SRCS) $(GEN_CMDS)
	@echo 'Building target: "$@"'
	@echo 'Invoking: C2000 Linker'
	"C:/ti/ccs2010/ccs/tools/compiler/ti-cgt-c2000_22.6.2.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla2 --float_support=fpu32 --idiv_support=idiv0 --tmu_support=tmu0 --vcu_support=vcu0 -O0 --opt_for_speed=5 --fp_mode=relaxed --define=DEBUG --define=CPU1 --define=USE_ADC_REFERENCE_INTERNAL --c11 --c++03 --relaxed_ansi --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi -z -m"cla_cc_f2838x copy.map" --heap_size=0x100 --stack_size=0x200 --warn_sections -i"C:/ti/ccs2010/ccs/tools/compiler/ti-cgt-c2000_22.6.2.LTS/lib" -i"C:/ti/ccs2010/ccs/tools/compiler/ti-cgt-c2000_22.6.2.LTS/include" --reread_libs --diag_wrap=off --display_error_number --xml_link_info="cla_cc_f2838x copy_linkInfo.xml" --entry_point=code_start --rom_model -o "cla_cc_f2838x copy.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(GEN_MISC_FILES__QUOTED)$(GEN_FILES__QUOTED)$(EXE_OUTPUTS__QUOTED)
	-$(RM) "syscfg\board.obj" "syscfg\c2000ware_libraries.obj" "lab_cla_tasks.obj" "App\System_main.obj" "App\lab_main.obj" "Common\Ringbuffer.obj" "Common\System_timer.obj" "Drivers\Comm\spi_t.obj" "Drivers\Motor\DRV8711.obj" "Drivers\Motor\Step_motor.obj" "device\device.obj" "device\f2838x_codestartbranch.obj" 
	-$(RM) "syscfg\board.d" "syscfg\c2000ware_libraries.d" "App\System_main.d" "App\lab_main.d" "Common\Ringbuffer.d" "Common\System_timer.d" "Drivers\Comm\spi_t.d" "Drivers\Motor\DRV8711.d" "Drivers\Motor\Step_motor.d" "device\device.d" 
	-$(RM) "lab_cla_tasks.d" 
	-$(RM) "device\f2838x_codestartbranch.d" 
	-$(RMDIR) $(GEN_MISC_DIRS__QUOTED)
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

