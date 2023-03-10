###############################################################################################
# Make file template
# Author:	Ahmad Abdullah
#					University of Victoria
#					Computer Science Department
#					CSC 360 Introduction to Operating Systems
#					Spring 2023
#
# Last Updated: January 27, 2023
###############################################################################################
#
# When using make, please remeber:
#
# 1) When you type make or make [target], the Make will look through your current directory for
#    a Makefile. This file must be called makefile or Makefile.
# 2) Make will then look for the corresponding target in the makefile. If you don�t provide a
#    target, Make will just run the first target it finds.
# 3) If the target is found, the target�s dependencies will be run as needed, then the target 
#    commands will be run.
# 4) If any dependency need to be updated, the dependency will be updated first.

# First let's define some handy variables

COMPILER=gcc
OPTIONS=-g

# The following line commented (will not be used) and left to show other gcc options
#OPTIONS=-g -std=c++17 -pedantic -Wall -Wextra -Werror -Wshadow -Wconversion -Wunreachable-code

COMPILE=$(COMPILER) $(OPTIONS)
BUILD=build

# Update the following with your program name
PROGRAM=PMan

# Compile main by default
all: program

# $(BUILD)/*.o expands to all .o files in the $(BUILD) directory
# In this case, we'll get $(BUILD)/file1.o $(BUILD)/file2.o
#   $@ expands to the target name, i.e. target1
#   $< expands to the first dependency, i.e. dependency1
#   $^ expands to the complete list of dependencies, i.e. dependency1 dependency2


program: PMan.c $(BUILD)/Functions.o $(BUILD)/linkedlist.o
	$(COMPILE) $< $(BUILD)/*.o -o $(PROGRAM)


$(BUILD)/Functions.o: Functions.c Functions.h  build
	$(COMPILE) -c $< -o $@
$(BUILD)/linkedlist.o: linkedlist.c linkedlist.h  build
	$(COMPILE) -c $< -o $@
# Make the build directory if it doesn't exist
build:
	mkdir -p $(BUILD)


# These rules do not correspond to a specific file
.PHONY: build clean

# Delete the build directory and program
clean:
	rm -rf $(BUILD) program *.bak
