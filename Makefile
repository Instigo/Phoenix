CC		= g++
LD		= ld
CFLAGS		= -g -Wall
SOURCES 	= pls.c
OBJECTS		= $(SOURCES:.c=.o)
TARGET		= pls

all: $(SOURCES) $(TARGET)

$(TARGET): $(OBJECTS)
		$(CC) $(LDFLAGS) $(INCLUDES) $(OBJECTS) -o $@

.o: 
		$(CC) $(CFLAGS) $(INCLUDES)  $< -o $@

clean:
		rm -rf $(OBJECTS) $(TARGET)
