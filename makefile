C_COMPILER=clang

CHEATSHEET_DIR=src

LIB_DIR=lib

pointers: $(CHEATSHEET_DIR)/pointers.c
	$(C_COMPILER) -g $(CHEATSHEET_DIR)/pointers.c -o pointers

structs: $(CHEATSHEET_DIR)/structs.c
	$(C_COMPILER) -g $(CHEATSHEET_DIR)/structs.c -o structs

cheatsheet: pointers

clean:
	rm -f pointers
	rm -rf pointers.dSYM
	rm -f structs
	rm -rf structs.dSYM
