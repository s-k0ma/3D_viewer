.PHONY: all clean build format test gcov_report

CC = gcc
CPP = g++
GCOV=--coverage

CFLAGS = -Wall -Werror -Wextra -O0
STANDART=-std=c++17
ADD_LIB=-lm
GTEST=-lgtest -lgtest_main -pthread
LCOVFLAGS=
MODEL_FILES = model/obj_model.cc model/camera_model.cc
CONTROLLER_FILES = controller/*.cc
TEST_FILES = tests/test_main.cc
TEST_DIR = tests

GTEST_CFLAGS = $(shell pkg-config --cflags gtest)
GTEST_LIBS = $(shell pkg-config --libs gtest)


OS=$(shell uname -s)

ifeq ($(OS), Linux)
	LEAK_CHECK=valgrind --tool=memcheck --leak-check=yes
	OPEN_CMD=xdg-open
else ifeq ($(OS), Darwin)
	LEAK_CHECK=leaks -atExit --
	OPEN_CMD=open
endif

ifeq ($(strip $(OS)), Linux)
	UBUNTU := $(shell hostnamectl | grep -o 'Ubuntu')
	ifeq ($(strip $(UBUNTU)), Ubuntu)
	  LCOVFLAGS = --ignore-errors inconsistent --ignore-errors mismatch
	endif
endif

ifeq ($(strip $(OS)), Darwin)
  LCOVFLAGS = --ignore-errors inconsistent --ignore-errors mismatch
endif


all:
	$(MAKE) clean
	$(MAKE) uninstall
	$(MAKE) install

install:
	@$(MAKE) uninstall
	@mkdir 3DViewer
	@cd 3DViewer && cmake -B build "../view/" && make -C build viewer_front
	@cp -R 3DViewer/build/viewer_front ~/Desktop/3DViewer.app
	@echo " 3DViewer V2.0 was installed successfully! "

uninstall:
	@rm -rf 3DViewer
	@rm -rf ~/Desktop/3DViewer.app
	@echo " 3DViewer V2.0 was uninstalled successfully! "

dvi:
	cd documentation && doxygen
	open documentation/html/index.html

dist:
	 tar -cf 3DViewer.tar 3DViewer

test:
	$(MAKE) clean
	$(CPP) $(CFLAGS) $(STANDART) $(GTEST_CFLAGS) $(MODEL_FILES) $(CONTROLLER_FILES) $(TEST_DIR)/*.cc -o test $(ADD_LIB) $(GTEST_LIBS)
	./test

gcov_report:
	$(MAKE) clean
	$(CPP) $(CFLAGS) -fprofile-arcs -ftest-coverage $(STANDART) $(GTEST_CFLAGS) $(MODEL_FILES) $(CONTROLLER_FILES) $(TEST_DIR)/*.cc -o test $(ADD_LIB) $(GTEST_LIBS)
	./test
	@lcov -c -d . --no-external -o model_gcov.info $(LCOVFLAGS) --exclude '*/controller/*'
	@genhtml -o report model_gcov.info
	@chmod 777 report/*
	@rm *.gcda *.gcno *.info
	@$(OPEN_CMD) ./report/index.html


format:
	clang-format -style=Google -i model/*.cc model/*.h view/*.cc view/*.h tests/*.cc controller/*.cc controller/*.h

format_check:
	clang-format -style=Google -i model/*.cc model/*.h view/*.cc view/*.h tests/*.cc controller/*.cc controller/*.h

clean:
	@rm -rf *.o *.a report *.gcno *.gcda *.info *.tar 3DViewer test gcovreport html latex
	@cd documentation && rm -rf html


memory: clean test
	@echo "Checking for memory leaks..."
	@$(LEAK_CHECK) ./test
