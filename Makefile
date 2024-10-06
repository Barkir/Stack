BIN=bin
SRC=src
INCLUDE=include

SOURCES=$(notdir $(foreach dir,$(SRC),$(wildcard $(dir)/*.cpp)))
TARGET=$(addprefix $(BIN)/,$(shell basename `pwd`))
OBJECTS=$(addprefix $(BIN)/,$(SOURCES:.cpp=.o))

CFLAGS=-Wall  \
    -pedantic -pedantic-errors -g3 $(addprefix -I,$(INCLUDE))
LDFLAGS=

vpath %.cpp $(SRC)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(LINK.o) $^ $(OUTPUT_OPTION)

$(BIN)/%.o: %.cpp
	$(COMPILE.c) $< $(OUTPUT_OPTION)

clean:
	$(RM) $(OBJECTS) $(TARGET)


.PHONY: all clean
