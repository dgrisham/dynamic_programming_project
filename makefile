# Set compiler commands
FC90 = mpif90
CPP = g++
# gfortran
#FLAGS = -O3 -fno-range-check 
# g++
#FLAGS = -03

# Set modules and objects
# MODS = constant_mod.mod function_mod.mod
#HEDS = TSP.h
#OBJS = constant_mod.o function_mod.o 
#OBJS = TSP.o

# Set rules for .o files
#%.o: %.f90
#	$(FC90) -c $(FLAGS) -o $@ $<
%.o: %.cpp 
	$(CPP) -c $(FLAGS) -o $@ $<

# Modules
#constant_mod.mod: constant_mod.f90
#	$(FC90) -c constant_mod.f90

#function_mod.mod: function_mod.f90
#	$(FC90) -c function_mod.f90

# Primary #all: constant_mod.mod function_mod.mod  num1.o $(OBJS)
#	$(FC90) -o num1_exe num1.o $(OBJS)
all: palindrome.o 
	$(CPP) -o exe_palindrome palindrome.o $(OBJS)

#num1_exe: num1.o $(OBJS)
#	  $(FC90) -o num1_exe num1.o $(OBJS) 

clean:
	rm exe_palindrome *.o

# Other rules
#function_mod.o: function_mod.f90 $(MODS)
#constant_mod.o: constant_mod.f90 $(MODS)
