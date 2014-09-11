CC		= g++
LD		= ld
CFLAGS		= -g -Wall
SOURCES 	= ptail.cc
OBJECTS		= $(SOURCES:.cc=.o)
TARGET		= ptail

all: $(SOURCES) $(TARGET)

$(TARGET): $(OBJECTS)
		$(CC) $(LDFLAGS) $(INCLUDES) $(OBJECTS) -o $@

.o: 
		$(CC) $(CFLAGS) $(INCLUDES)  $< -o $@

clean:
		rm -rf $(OBJECTS) $(TARGET)
