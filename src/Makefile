OS = $(shell uname)
ifeq ("$(OS)", "Linux")
    BUILD_FILE_TMP = SmartCalc
    BUILD_FILE = SmartCalc
    OPEN = xdg-open
    TEST_FLAGS = -lcheck -pthread -lrt -lm -lsubunit
    LEAKS_RUN = valgrind ./test
else
    BUILD_FILE_TMP = SmartCalc.app
    BUILD_FILE = SmartCalc.app
    OPEN = open
    TEST_FLAGS = -lcheck
    LEAKS_RUN = CK_FORK=no leaks -atExit -- ./test
endif

FLAGS = -Wall -Wextra -Werror -std=c++17
GCOV_FLAGS = -fprofile-arcs -ftest-coverage

CC = g++

TMP_DIR = ./tmp
BUILD_DIR = ./build
DIST_DIR = ./"SmartCalc_v2_0"
REPORT_DIR = ./report
DVI_DIR = ./"doc_SmartCalc_v2_0"


BUILD = @mkdir -p $(BUILD_DIR)
TMP = @mkdir -p $(TMP_DIR)
DIST = @mkdir -p $(DIST_DIR)
REPORT = @mkdir -p $(REPORT_DIR)

DIST_NAME = $(DIST_DIR).tar.gz

all: install

install:
	$(BUILD)
	$(TMP)
	cd $(TMP_DIR) && cmake ../ -B . && cmake --build .
	cp -R ./tmp/$(BUILD_FILE_TMP) $(BUILD_DIR)/$(BUILD_FILE)
	rm -rf tmp

uninstall:
	rm -rf $(BUILD_DIR)

dvi:
	makeinfo -o $(DVI_DIR) --html --no-warn --force ./SmartCalc_v2_0_info.texi
	$(OPEN) $(DVI_DIR)/index.html

dist:
	$(DIST)
	cp -r Makefile CMakeLists.txt main.cc SmartCalc_v2_0_info.texi ./controller ./source ./model ./tests ./view $(DIST_DIR)
	tar -cvzf $(DIST_NAME) $(DIST_DIR)
	rm -rf $(DIST_DIR)

calculation.o:
	$(CC) -c ./source/calculation.h $(FLAGS)

tests: calculation.o
	$(CC) ./tests/tests.cc ./source/calculation.cc -o test -lgtest -pthread -lgmock $(GCOV_FLAGS)
	./test

gcov_report: tests
	$(REPORT)
	gcovr -r . --html --html-details -o $(REPORT_DIR)/report.html
	$(MAKE) clean_src
	$(OPEN) $(REPORT_DIR)/report.html

google_style:
	cp ../materials/linters/.clang-format .clang-format
	clang-format --verbose -i *.cc ./controller/*.h ./model/*.h ./view/*.h ./view/*.cc ./tests/*.cc ./source/calculation*
	rm .clang-format

clang:
	cp ../materials/linters/.clang-format .clang-format
	clang-format --verbose -n *.cc ./controller/*.h ./model/*.h ./view/*.h ./view/*.cc ./tests/*.cc ./source/calculation*
	rm .clang-format

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem ./controller/*.h ./model/*.h ./view/*.h ./view/*.cc ./source/calculation*

leaks: tests
	$(LEAKS_RUN)
	$(MAKE) clean_src

clean_src:
	rm -rf $(BUILD_DIR) $(DIST_DIR) $(TMP_DIR) $(DIST_NAME)

clean: clean_src
	rm -rf test *.gcda *.gcno **/*.gch $(REPORT_DIR) $(DVI_DIR)
