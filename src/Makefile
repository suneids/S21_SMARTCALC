CFLAGS = -c -Wall -Werror -Wextra
LDFLAGS = -std=c11 -Wall -Werror -Wextra
SOURCE = $(wildcard s21_*.c)
OBJECTS = $(patsubst %.c,%.o, ${SOURCE})
UNAME_S := $(shell uname -s)
NEW_TEST_SRC=$(wildcard ./tests/*.c)

ifeq ($(UNAME_S),Linux)
  	OPEN_CMD = xdg-open
	ADD_LIB = -lcheck -lsubunit -lm -lrt -lpthread -D_GNU_SOURCE
	APP = build/s21_smartcalc
endif
ifeq ($(UNAME_S),Darwin)
	APP = build/s21_smartcalc
	OPEN_CMD = open
	ADD_LIB = -lcheck
endif

all: install

s21_calculator.a:
	@gcc $(CFLAGS) $(SOURCE)
	@ar rcs $@ $(OBJECTS)
	rm -rf *.o
	ranlib s21_calculator.a

test: s21_calculator.a
	@gcc $(LDFLAGS) ${NEW_TEST_SRC}  s21_calculator.a -o test $(ADD_LIB)
	./test
	
install: 
	@mkdir -p build
	cd build/ && qmake ../SmartCalc/s21_smartcalc.pro && make
	@mkdir -p $(HOME)/Desktop/SmartCalc/
	@cp -rf $(APP) $(HOME)/Desktop/SmartCalc/
	make clean

uninstall:
	@rm -rf $(HOME)/Desktop/SmartCalc/


leaks:
	CK_FORK=no valgrind --vgdb=no --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./test

clean:
	-rm -rf build*
	-rm -rf *.o && rm -rf *.gcno
	-rm -rf *.a && rm -rf *.gcda
	-rm -rf *.info && rm -rf *.gcov
	-rm -rf ./gcov_report
	-rm -fr report
	-rm -fr test
	-rm -rf *.txt
	
style:
	clang-format -style=Google -n *.c *.h */*.c */*.h
	cppcheck --enable=all --suppress=missingIncludeSystem ${SOURCE} ${NEW_TEST_SRC}
	
dvi: 
	open s21_specification/readme.md
	  
dist:
	@mkdir -p $(HOME)/Desktop/dist
	@cp -R $(HOME)/Desktop/SmartCalc/s21_smartcalc $(HOME)/Desktop/dist
	@cp -r s21_specification $(HOME)/Desktop/dist 
	@cd $(HOME)/Desktop/dist && tar cvzf  SmartCalc_v1.0.tgz *
	@cd $(HOME)/Desktop/dist && rm -rf  s21_smartcalc  s21_specification

gcov_report:${SOURCE}
	@gcc --coverage ${SOURCE} ${NEW_TEST_SRC} -o test $(ADD_LIB)
	./test
	@lcov -t "stest" -o s21_test.info -c -d .
	@genhtml -o report s21_test.info
	$(OPEN_CMD) ./report/index.html

.PHONY:	s21_calculator.a test prov valgrind