# Compiler
CC = g++

# Directories names
OBJECTS_DIR = build
OUTFILE 	= differentiator

# Source files
SOURCES = main.cpp differentiator_tree.cpp differentiator.cpp compose_tex.cpp differentiator_utils.cpp parse_formula.cpp

# Submodule object files
SUBMODULE_OBJECT_FILES = # lib/kalatushkin/build/text_data.o     \
       					 # lib/kalatushkin/build/color_scheme.o  \
       					 # lib/kalatushkin/build/flags.o          \
       					 # lib/kalatushkin/build/sort_text.o     \
       					 # lib/kalatushkin/build/utils.o         \
       					 # lib/kalatushkin/build/parsing_flags.o

SUBMODULE_NAME = # kalatushkin

# Escape sequences (colors for terminal output)
BOLD_RED 	  = \033[1;31m
BOLD_GREEN 	  = \033[1;32m
BOLD_YELLOW	  = \033[1;33m
BOLD_BLUE	  = \033[1;34m
BOLD_MAGENTA  = \033[1;35m
BOLD_CYAN	  = \033[1;36m
BOLD_WHITE	  = \033[1;37m
DEFAULT_STYLE = \033[0m

# Compilation flags
CFLAGS= -D _DEBUG -ggdb3 -std=c++17 -O0 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations 				\
		-Wc++14-compat -Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts 					\
		-Wconditionally-supported -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal 				\
		-Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlogical-op 			\
		-Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Winit-self -Wredundant-decls 		\
		-Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=2 					\
		-Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override 		\
		-Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast 		\
		-Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing 				\
		-Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation 				\
		-fstack-protector -fstrict-overflow -flto-odr-type-merging -fno-omit-frame-pointer 					\
		-Wlarger-than=8192 -Wstack-usage=8192 -pie -fPIE -Werror=vla -fsanitize=address,alignment,$			\
		bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,leak,$				\
		nonnull-attribute,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,$	\
		undefined,unreachable,vla-bound,vptr

# Includes
INCLUDE = -I include -I lib/kalatushkin/include

# Libs
LIBS = -L lib/kalatushkin/build -l kalatushkin

# Add .o in source files
OBJECT_FILES = $(addsuffix .o,$(basename $(SOURCES)))

.PHONY: clean all makedir

all: makedir $(OUTFILE)

$(OUTFILE): $(OBJECT_FILES)
	$(CC) $(addprefix $(OBJECTS_DIR)/,$^) $(INCLUDE) $(SUBMODULE_OBJECT_FILES) -o $(OBJECTS_DIR)/$(OUTFILE)

$(OBJECT_FILES): %.o: src/%.cpp
	$(CC) -c $^ $(INCLUDE) -o $(OBJECTS_DIR)/$@

makedir:
	@mkdir -p $(OBJECTS_DIR)

clean:
	@rm -f   $(OBJECTS_DIR)/*.o
	@rm -f   $(OBJECTS_DIR)/$(OUTFILE)
