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

headers: $(CHEATSHEET_DIR)/headers.h $(CHEATSHEET_DIR)/headers.c $(CHEATSHEET_DIR)/use-headers.c
# Compile source (c) files to object (o) files
	$(C_COMPILER) -g -H -c $(CHEATSHEET_DIR)/use-headers.c $(CHEATSHEET_DIR)/headers.c
# Link object files into executable
	$(C_COMPILER) -g use-headers.o headers.o -o use-headers

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
	rm -f headers.o
	rm -f use-headers
	rm -f use-headers.o
	rm -rf use-headers.dSYM
