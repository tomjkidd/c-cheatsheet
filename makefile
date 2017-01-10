C_COMPILER=clang

CHEATSHEET_DIR=src

LIB_DIR=lib

pointers: $(CHEATSHEET_DIR)/pointers.c
	$(C_COMPILER) -g $(CHEATSHEET_DIR)/pointers.c -o pointers

structs: $(CHEATSHEET_DIR)/structs.c
	$(C_COMPILER) -g $(CHEATSHEET_DIR)/structs.c -o structs

formatting: $(CHEATSHEET_DIR)/formatting.c
	$(C_COMPILER) -g $(CHEATSHEET_DIR)/formatting.c -o formatting

input-and-output: $(CHEATSHEET_DIR)/input-and-output.c
	$(C_COMPILER) -g $(CHEATSHEET_DIR)/input-and-output.c -o input-and-output

cheatsheet: pointers structs formatting input-and-output

clean:
	rm -f pointers
	rm -rf pointers.dSYM
	rm -f structs
	rm -rf structs.dSYM
	rm -f formatting
	rm -rf formatting.dSYM
	rm -f input-and-output
	rm -rf input-and-output.dSYM
