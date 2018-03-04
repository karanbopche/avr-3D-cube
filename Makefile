################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL := cmd.exe
RM := rm -rf

USER_OBJS :=

LIBS := 
PROJ := 

O_SRCS := 
C_SRCS := 
S_SRCS := 
S_UPPER_SRCS := 
OBJ_SRCS := 
ASM_SRCS := 
PREPROCESSING_SRCS := 
OBJS := 
OBJS_AS_ARGS := 
C_DEPS := 
C_DEPS_AS_ARGS := 
EXECUTABLES := 
OUTPUT_FILE_PATH :=
OUTPUT_FILE_PATH_AS_ARGS :=
AVR_APP_PATH :=$$$AVR_APP_PATH$$$
QUOTE := "
ADDITIONAL_DEPENDENCIES:=
OUTPUT_FILE_DEP:=

# Every subdirectory with source files must be described here
SUBDIRS := 


# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS +=  \
../main.c \
../Cube.c


PREPROCESSING_SRCS += 


ASM_SRCS += 


OBJS +=  \
main.o \
Cube.o


OBJS_AS_ARGS +=  \
main.o \
Cube.o


C_DEPS +=  \
main.d \
Cube.d


C_DEPS_AS_ARGS +=  \
main.d \
Cube.d


OUTPUT_FILE_PATH +=led_Cube_atmega8.elf

OUTPUT_FILE_PATH_AS_ARGS +=led_Cube_atmega8.elf

ADDITIONAL_DEPENDENCIES:=

OUTPUT_FILE_DEP:= ./makedep.mk

# AVR32/GNU C Compiler





./%.o: .././%.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler
	$(QUOTE)C:\WinAVR-20100110\bin\avr-gcc.exe$(QUOTE)  -DF_CPU=1000000UL  -O2 -Wall -c -gdwarf-2 -fsigned-char  -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)"  -mmcu=atmega8  -o"$@" "$<" 
	@echo Finished building: $<



# AVR32/GNU Preprocessing Assembler



# AVR32/GNU Assembler




ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: $(OUTPUT_FILE_PATH) $(ADDITIONAL_DEPENDENCIES)

$(OUTPUT_FILE_PATH): $(OBJS) $(USER_OBJS) $(OUTPUT_FILE_DEP)
	@echo Building target: $@
	@echo Invoking: AVR/GNU C Linker
	$(QUOTE)C:\WinAVR-20100110\bin\avr-gcc.exe$(QUOTE) -o$(OUTPUT_FILE_PATH_AS_ARGS) $(OBJS_AS_ARGS) $(USER_OBJS) $(LIBS) -Wl,-Map="led_Cube_atmega8.map"  -mmcu=atmega8  
	@echo Finished building target: $@
	"C:\WinAVR-20100110\bin\avr-objcopy.exe" -O ihex -R .eeprom -R .fuse -R .lock -R .signature  "led_Cube_atmega8.elf" "led_Cube_atmega8.hex"
	"C:\WinAVR-20100110\bin\avr-objcopy.exe" -j .eeprom  --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0  --no-change-warnings -O ihex "led_Cube_atmega8.elf" "led_Cube_atmega8.eep" || exit 0
	"C:\WinAVR-20100110\bin\avr-objdump.exe" -h -S "led_Cube_atmega8.elf" > "led_Cube_atmega8.lss"
	"C:\WinAVR-20100110\bin\avr-size.exe" -C --mcu=atmega8  "led_Cube_atmega8.elf"
	




# Other Targets
clean:
	-$(RM) $(OBJS_AS_ARGS)$(C_DEPS_AS_ARGS) $(EXECUTABLES) 
	rm -rf "led_Cube_atmega8.hex" "led_Cube_atmega8.lss" "led_Cube_atmega8.eep" "led_Cube_atmega8.map"
	