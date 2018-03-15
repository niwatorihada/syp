# Makefile for login.cpp
syp: ./src/syp.cpp
	@g++ -Wall -o ./syp ./src/syp.cpp
	@chmod 775 syp

# clean exe
clean:
	@rm -f syp

# make and run
run:
	@make
	@echo ==
	@./syp

# run and clean
rc:
	@run
	@make clean
