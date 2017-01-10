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

memory: $(CHEATSHEET_DIR)/memory.c
	$(C_COMPILER) -g $(CHEATSHEET_DIR)/memory.c -o memory

functions: $(CHEATSHEET_DIR)/functions.c
	$(C_COMPILER) -g $(CHEATSHEET_DIR)/functions.c -o functions

static-headers: headers.o $(CHEATSHEET_DIR)/structs.c
# Create a static library/archive, which is just a collection of object files.
	$(C_COMPILER) -g -H -c $(CHEATSHEET_DIR)/structs.c
	ar -rcs $(LIB_DIR)/libtkheaders.a headers.o structs.o
# Link everything together. This is static linking.
	$(C_COMPILER) -g use-headers.o -L$(LIB_DIR) -ltkheaders -o use-headers-static

show-archive-symbols: $(LIB_DIR)/libtkheaders.a
	nm $(LIB_DIR)/libtkheaders.a

show-archive-objects: $(LIB_DIR)/libtkheaders.a
	ar -t $(LIB_DIR)/libtkheaders.a

extract-archive-object: $(LIB_DIR)/libtkheaders.a
	ar -x $(LIB_DIR)/libtkheaders.a headers.o

dynamiclib: $(CHEATSHEET_DIR)/headers.c
	$(C_COMPILER) -g -fPIC -c $(CHEATSHEET_DIR)/headers.c -o dynamic-headers.o
	$(C_COMPILER) -shared dynamic-headers.o -o $(LIB_DIR)/libheaders.dylib
	$(C_COMPILER) -g -c $(CHEATSHEET_DIR)/use-headers.c -o use-dynamic-headers.o
	$(C_COMPILER) -g use-dynamic-headers.o -L$(LIB_DIR) -lheaders -o use-dynamic-headers
# Static lib code is like a cake, once it's baked, it's pieces can not be changed.
# Dynamic lib code is like a puzzle. It's pieces can be substituted at runtime.

processes: $(CHEATSHEET_DIR)/processes.c
	$(C_COMPILER) -g $(CHEATSHEET_DIR)/processes.c -o processes

cheatsheet: pointers structs formatting input-and-output headers memory functions static-headers dynamiclib processes

clean:
	rm -f pointers
	rm -rf pointers.dSYM
	rm -f structs
	rm -f structs.o
	rm -rf structs.dSYM
	rm -f formatting
	rm -rf formatting.dSYM
	rm -f input-and-output
	rm -rf input-and-output.dSYM
	rm -f headers.o
	rm -f use-headers
	rm -f use-headers.o
	rm -rf use-headers.dSYM
	rm -f memory
	rm -rf memory.dSYM
	rm -f functions
	rm -rf functions.dSYM
	rm -f $(LIB_DIR)/libtkheaders.a
	rm -f use-headers-static
	rm -rf use-headers-static.dSYM
	rm -f dynamic-headers.o
	rm -f use-dynamic-headers.o
	rm -f $(LIB_DIR)/libheaders.dylib
	rm -f use-dynamic-headers
	rm -f processes
	rm -rf processes.dSYM
	rm -f process-output.txt
