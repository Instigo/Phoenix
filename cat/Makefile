CC		= g++
LD		= ld
CFLAGS		= -g -Wall
SOURCES 	= pcat.cc
OBJECTS		= $(SOURCES:.cc=.o)
TARGET		= pcat

all: $(SOURCES) $(TARGET)

$(TARGET): $(OBJECTS)
		$(CC) $(LDFLAGS) $(INCLUDES) $(OBJECTS) -o $@

.o: 
		$(CC) $(CFLAGS) $(INCLUDES)  $< -o $@

clean:
		rm -rf $(OBJECTS) $(TARGET)
