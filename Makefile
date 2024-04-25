GCOV_FLAGS= --coverage
GCOV_LIBS= -lgcov

DEBUG_BUILD_TYPE=-DCMAKE_BUILD_TYPE=Debug
GCOV_REPORT_FLAGS=-DMAZE_COVERAGE_FLAGS:STRING="$(GCOV_FLAGS)"
GCOV_REPORT_LIBS=-DMAZE_COVERAGE_LIBS:STRING="$(GCOV_LIBS)"
RELEASE_BUILD_TYPE=-DCMAKE_BUILD_TYPE=Release
GCOV_NO_REPORT_FLAGS=-DMAZE_COVERAGE_FLAGS:STRING=""
GCOV_NO_REPORT_LIBS=-DMAZE_COVERAGE_LIBS:STRING=""

REPORT_BUILD= $(DEBUG_BUILD_TYPE) $(GCOV_REPORT_FLAGS) $(GCOV_REPORT_LIBS)
STANDART_BUILD= $(DEBUG_BUILD_TYPE) $(GCOV_NO_REPORT_FLAGS) $(GCOV_NO_REPORT_LIBS)

PATH_BUILD=build
PATH_REPORT=report
PATH_DOXY=doxy


.PHONY: all install uninstall clean rebuild test gcov_report valgrind leaks run dvi dist init_submodules build_test build_test_cov

all: install

install: init_submodules
	cmake -B $(PATH_BUILD) $(STANDART_BUILD) 
	cmake --build $(PATH_BUILD) --target maze

uninstall:
	rm -rf $(PATH_BUILD)

clean:
	rm -rf $(PATH_DOXY)/documentation
	rm -rf $(PATH_REPORT)
	cmake --build $(PATH_BUILD) --target clean

rebuild: clean all

test: build_test
	$(PATH_BUILD)/maze_test

gcov_report: build_test_cov
	rm -rf $(PATH_REPORT)
	./$(PATH_BUILD)/maze_test
	mkdir $(PATH_REPORT)	
	gcovr --html-details -o $(PATH_REPORT)/index.html
	open $(PATH_REPORT)/index.html

valgrind: build_test
	valgrind $(PATH_BUILD)/maze_test

leaks: build_test
	leaks -atExit -- $(PATH_BUILD)/maze_test

run:
	$(PATH_BUILD)/maze

dvi:
	doxygen $(PATH_DOXY)/doxyfile
	open $(PATH_DOXY)/documentation/html/index.html

dist:
	tar -cvf arhive.tar ..

init_submodules:
	git submodule init
	git submodule update

build_test: init_submodules
	cmake -B $(PATH_BUILD) $(STANDART_BUILD) 
	cmake --build $(PATH_BUILD) --target maze_test

build_test_cov: init_submodules
	cmake -B $(PATH_BUILD) $(REPORT_BUILD) 
	cmake --build $(PATH_BUILD) --target maze_test
