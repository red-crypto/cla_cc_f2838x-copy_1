################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
build-1314615825: ../lab_cla_controlcard_250717.syscfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: SysConfig'
	"C:/ti/ccs2010/ccs/utils/sysconfig_1.24.0/sysconfig_cli.bat" --script "C:/Users/combi/workspace_ccstheia/cla_cc_f2838x copy/lab_cla_controlcard_250717.syscfg" -o "syscfg" -s "C:/ti/c2000/C2000Ware_5_05_00_00/.metadata/sdk.json" -b "/boards/TMDSCNCD28388D" --compiler ccs
	@echo 'Finished building: "$<"'
	@echo ' '

syscfg/board.c: build-1314615825 ../lab_cla_controlcard_250717.syscfg
syscfg/board.h: build-1314615825
syscfg/board.cmd.genlibs: build-1314615825
syscfg/board.opt: build-1314615825
syscfg/board.json: build-1314615825
syscfg/pinmux.csv: build-1314615825
syscfg/adc.dot: build-1314615825
syscfg/c2000ware_libraries.cmd.genlibs: build-1314615825
syscfg/c2000ware_libraries.opt: build-1314615825
syscfg/c2000ware_libraries.c: build-1314615825
syscfg/c2000ware_libraries.h: build-1314615825
syscfg/clocktree.h: build-1314615825
syscfg: build-1314615825

syscfg/%.obj: ./syscfg/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs2010/ccs/tools/compiler/ti-cgt-c2000_22.6.2.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla2 --float_support=fpu32 --idiv_support=idiv0 --tmu_support=tmu0 --vcu_support=vcu0 -O0 --opt_for_speed=5 --fp_mode=relaxed --include_path="C:/Users/combi/workspace_ccstheia/cla_cc_f2838x copy/inc" --include_path="C:/Users/combi/workspace_ccstheia/cla_cc_f2838x copy/Sensor" --include_path="C:/Users/combi/workspace_ccstheia/cla_cc_f2838x copy/Drivers/Motor" --include_path="C:/Users/combi/workspace_ccstheia/cla_cc_f2838x copy/Drivers/Comm" --include_path="C:/Users/combi/workspace_ccstheia/cla_cc_f2838x copy/Common" --include_path="C:/Users/combi/workspace_ccstheia/cla_cc_f2838x copy/App" --include_path="C:/Users/combi/workspace_ccstheia/cla_cc_f2838x copy" --include_path="C:/Users/combi/workspace_ccstheia/cla_cc_f2838x copy/device" --include_path="C:/ti/c2000/C2000Ware_5_05_00_00/driverlib/f2838x/driverlib" --include_path="C:/Users/combi/workspace_ccstheia/cla_cc_f2838x copy/device/include" --include_path="C:/ti/ccs2010/ccs/tools/compiler/ti-cgt-c2000_22.6.2.LTS/include" --include_path="C:/ti/c2000/C2000Ware_5_05_00_00" --define=DEBUG --define=CPU1 --define=USE_ADC_REFERENCE_INTERNAL --c11 --c++03 --relaxed_ansi --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --preproc_with_compile --preproc_dependency="syscfg/$(basename $(<F)).d_raw" --include_path="C:/Users/combi/workspace_ccstheia/cla_cc_f2838x copy/CPU1_RAM/syscfg" --obj_directory="syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

%.obj: ../%.cla $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs2010/ccs/tools/compiler/ti-cgt-c2000_22.6.2.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla2 --float_support=fpu32 --idiv_support=idiv0 --tmu_support=tmu0 --vcu_support=vcu0 -O0 --opt_for_speed=5 --fp_mode=relaxed --include_path="C:/Users/combi/workspace_ccstheia/cla_cc_f2838x copy/inc" --include_path="C:/Users/combi/workspace_ccstheia/cla_cc_f2838x copy/Sensor" --include_path="C:/Users/combi/workspace_ccstheia/cla_cc_f2838x copy/Drivers/Motor" --include_path="C:/Users/combi/workspace_ccstheia/cla_cc_f2838x copy/Drivers/Comm" --include_path="C:/Users/combi/workspace_ccstheia/cla_cc_f2838x copy/Common" --include_path="C:/Users/combi/workspace_ccstheia/cla_cc_f2838x copy/App" --include_path="C:/Users/combi/workspace_ccstheia/cla_cc_f2838x copy" --include_path="C:/Users/combi/workspace_ccstheia/cla_cc_f2838x copy/device" --include_path="C:/ti/c2000/C2000Ware_5_05_00_00/driverlib/f2838x/driverlib" --include_path="C:/Users/combi/workspace_ccstheia/cla_cc_f2838x copy/device/include" --include_path="C:/ti/ccs2010/ccs/tools/compiler/ti-cgt-c2000_22.6.2.LTS/include" --include_path="C:/ti/c2000/C2000Ware_5_05_00_00" --define=DEBUG --define=CPU1 --define=USE_ADC_REFERENCE_INTERNAL --c11 --c++03 --relaxed_ansi --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" --include_path="C:/Users/combi/workspace_ccstheia/cla_cc_f2838x copy/CPU1_RAM/syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


