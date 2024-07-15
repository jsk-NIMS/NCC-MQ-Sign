################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Core/Src/ncc/mont.s 

C_SRCS += \
../Core/Src/ncc/aes.c \
../Core/Src/ncc/fips202.c \
../Core/Src/ncc/packing.c \
../Core/Src/ncc/poly.c \
../Core/Src/ncc/randombytes.c \
../Core/Src/ncc/reduce.c \
../Core/Src/ncc/rounding.c \
../Core/Src/ncc/sign.c \
../Core/Src/ncc/symmetric-aes.c \
../Core/Src/ncc/symmetric-shake.c 

S_UPPER_SRCS += \
../Core/Src/ncc/intt.S \
../Core/Src/ncc/keccakf1600.S \
../Core/Src/ncc/ntt.S 

OBJS += \
./Core/Src/ncc/aes.o \
./Core/Src/ncc/fips202.o \
./Core/Src/ncc/intt.o \
./Core/Src/ncc/keccakf1600.o \
./Core/Src/ncc/mont.o \
./Core/Src/ncc/ntt.o \
./Core/Src/ncc/packing.o \
./Core/Src/ncc/poly.o \
./Core/Src/ncc/randombytes.o \
./Core/Src/ncc/reduce.o \
./Core/Src/ncc/rounding.o \
./Core/Src/ncc/sign.o \
./Core/Src/ncc/symmetric-aes.o \
./Core/Src/ncc/symmetric-shake.o 

S_DEPS += \
./Core/Src/ncc/mont.d 

S_UPPER_DEPS += \
./Core/Src/ncc/intt.d \
./Core/Src/ncc/keccakf1600.d \
./Core/Src/ncc/ntt.d 

C_DEPS += \
./Core/Src/ncc/aes.d \
./Core/Src/ncc/fips202.d \
./Core/Src/ncc/packing.d \
./Core/Src/ncc/poly.d \
./Core/Src/ncc/randombytes.d \
./Core/Src/ncc/reduce.d \
./Core/Src/ncc/rounding.d \
./Core/Src/ncc/sign.d \
./Core/Src/ncc/symmetric-aes.d \
./Core/Src/ncc/symmetric-shake.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/ncc/%.o Core/Src/ncc/%.su Core/Src/ncc/%.cyclo: ../Core/Src/ncc/%.c Core/Src/ncc/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L4R5xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O3 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/ncc/%.o: ../Core/Src/ncc/%.S Core/Src/ncc/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -DDEBUG -c -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"
Core/Src/ncc/%.o: ../Core/Src/ncc/%.s Core/Src/ncc/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -DDEBUG -c -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

clean: clean-Core-2f-Src-2f-ncc

clean-Core-2f-Src-2f-ncc:
	-$(RM) ./Core/Src/ncc/aes.cyclo ./Core/Src/ncc/aes.d ./Core/Src/ncc/aes.o ./Core/Src/ncc/aes.su ./Core/Src/ncc/fips202.cyclo ./Core/Src/ncc/fips202.d ./Core/Src/ncc/fips202.o ./Core/Src/ncc/fips202.su ./Core/Src/ncc/intt.d ./Core/Src/ncc/intt.o ./Core/Src/ncc/keccakf1600.d ./Core/Src/ncc/keccakf1600.o ./Core/Src/ncc/mont.d ./Core/Src/ncc/mont.o ./Core/Src/ncc/ntt.d ./Core/Src/ncc/ntt.o ./Core/Src/ncc/packing.cyclo ./Core/Src/ncc/packing.d ./Core/Src/ncc/packing.o ./Core/Src/ncc/packing.su ./Core/Src/ncc/poly.cyclo ./Core/Src/ncc/poly.d ./Core/Src/ncc/poly.o ./Core/Src/ncc/poly.su ./Core/Src/ncc/randombytes.cyclo ./Core/Src/ncc/randombytes.d ./Core/Src/ncc/randombytes.o ./Core/Src/ncc/randombytes.su ./Core/Src/ncc/reduce.cyclo ./Core/Src/ncc/reduce.d ./Core/Src/ncc/reduce.o ./Core/Src/ncc/reduce.su ./Core/Src/ncc/rounding.cyclo ./Core/Src/ncc/rounding.d ./Core/Src/ncc/rounding.o ./Core/Src/ncc/rounding.su ./Core/Src/ncc/sign.cyclo ./Core/Src/ncc/sign.d ./Core/Src/ncc/sign.o ./Core/Src/ncc/sign.su ./Core/Src/ncc/symmetric-aes.cyclo ./Core/Src/ncc/symmetric-aes.d ./Core/Src/ncc/symmetric-aes.o ./Core/Src/ncc/symmetric-aes.su ./Core/Src/ncc/symmetric-shake.cyclo ./Core/Src/ncc/symmetric-shake.d ./Core/Src/ncc/symmetric-shake.o ./Core/Src/ncc/symmetric-shake.su

.PHONY: clean-Core-2f-Src-2f-ncc

