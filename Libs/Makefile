#******************************************************************************
#*
#* ----------------------------------------------------------------------------
#*
#* Module      : Makefile
#*
#* Function    : Allows to build the lib
#* Author      : hubert
#* Date        : 2015-12-26
#*
#* ----------------------------------------------------------------------------
#*
#******************************************************************************

##############################
# lib configuration
##############################

LIBNAME=libBlueLinServer.a

SOURCE_FILES= gpio/gpio.c \

LIB_BUILD_PATH=./build/

OBJECT_FILES= $(LIB_BUILD_PATH)/gpio.o \

CC=../Toolchain/bbb_toolchain/bin/arm-linux-gnueabihf-

OPTIONS=-Wall -Wno-psabi -O2 -c

##############
# main target
##############

usage:
	@echo ""
	@echo "Lib Build"
	@echo "-----------------------------------"
	@echo ""
	@echo "Please select one of the targets below"
	@echo ""
	@echo " build           - Build the lib"
	@echo " clean           - cleans all files created by the makefile"
	@echo ""

##############
# greeting
##############
hello:
	@echo ""
	@echo "-----------------------------------"
	@echo "          Lib Builder             "
	@echo "-----------------------------------"
	@echo ""

###############
# building
###############
build: hello
	mkdir -p $(LIB_BUILD_PATH)
	$(CC)gcc $(OPTIONS) $(SOURCE_FILES)
	mv *.o $(LIB_BUILD_PATH)
	$(CC)ar -rv $(LIBNAME) $(OBJECT_FILES)
	$(CC)ar -t $(LIBNAME)

############################################
# clean all files created by target above
############################################
clean:
	rm -rf $(LIB_BUILD_PATH)
	rm -f $(LIBNAME)
