TARGET = engg

#### Setup ####
STELLARISWARE = C:\StellarisWare
CMSIS = C:\cmsis
SRC           = $(wildcard src/*.c)
TOOLCHAIN     = arm-none-eabi
PART          = LM4F120H5QR
CPU           = cortex-m4
FPU           = fpv4-sp-d16
FABI          = softfp
SRC           += $(STELLARISWARE)/utils/uartstdio.c

LINKER_FILE = $(STELLARISWARE)/boards/ek-lm4f120xl/hello/hello.ld
SRC        += $(STELLARISWARE)/boards/ek-lm4f120xl/hello/startup_gcc.c

CC = $(TOOLCHAIN)-gcc
LD = $(TOOLCHAIN)-ld
CP = $(TOOLCHAIN)-objcopy
OD = $(TOOLCHAIN)-objdump

CFLAGS = -mthumb -mcpu=$(CPU) -mfpu=$(FPU) -mfloat-abi=$(FABI)
CFLAGS+= -Os -ffunction-sections -fdata-sections
CFLAGS+= -MD -std=c99 -Wall -pedantic
CFLAGS+= -DPART_$(PART) -c -DTARGET_IS_BLIZZARD_RA1
CFLAGS+= -g -D DEBUG

LIB_GCC_PATH=$(shell $(CC) $(CFLAGS) -print-libgcc-file-name)
LIBC_PATH=$(shell $(CC) $(CFLAGS) -print-file-name=libc.a)
LIBM_PATH=$(shell $(CC) $(CFLAGS) -print-file-name=libm.a)
DRIVER_LIB=$(STELLARISWARE)/driverlib/gcc-cm4f/libdriver-cm4f.a
USB_LIB=$(STELLARISWARE)/usblib/gcc-cm4f/libusb-cm4f.a
CMSIS_MATH=$(CMSIS)/CMSIS/Lib/GCC/libarm_cortexM4lf_math.a
CMSIS_LIB=$(CMSIS)/CMSIS/Lib/libdsplib_lm4f.a

CFLAGS+= -I$(STELLARISWARE) 
CFLAGS+= -I$(CMSIS)/CMSIS/Include
CFLAGS+= -I$(CMSIS)/Device/ARM/ARMCM4/Include

LFLAGS = --gc-sections --entry ResetISR
CPFLAGS = -Obinary

ODFLAGS = -S

FLASHER=LMFlash
FLASHER_FLAGS=-v -r

OBJS = $(SRC:.c=.o)

#### Rules ####
all: $(OBJS) $(TARGET).axf $(TARGET)

%.o: %.c
	@echo
	@echo Compiling $<...
	$(CC) -c $(CFLAGS) $< -o $@

$(TARGET).axf: $(OBJS)
	@echo
	@echo Linking...
	$(LD) -T $(LINKER_FILE) $(LFLAGS) -o bin/$(TARGET).axf $(OBJS) $(DRIVER_LIB) $(LIBM_PATH) $(LIBC_PATH) $(LIB_GCC_PATH) $(CMSIS_LIB)

$(TARGET): $(TARGET).axf
	@echo
	@echo Copying...
	$(CP) $(CPFLAGS) bin/$(TARGET).axf bin/$(TARGET).bin
	$(OD) $(ODFLAGS) bin/$(TARGET).axf > bin/$(TARGET).lst

install: $(TARGET)
	@echo
	@echo Flashing...
	$(FLASHER) bin/$(TARGET).bin $(FLASHER_FLAGS)

clean:
	@echo
	@echo Cleaning...
	rm src/*.o src/*.d bin/*