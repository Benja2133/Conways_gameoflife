CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -std=c99 
SOURCES = grafico.c
OBJECTS = $(SOURCES:.c=.o)
TARGET = ejecutable
#LIBS = $(pkg-config allegro-5 allegro_font-5 --libs --cflags)
.PHONY: clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS) $$(pkg-config allegro-5 allegro_primitives-5 allegro_font-5 allegro_dialog-5 --libs --cflags)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@ $$(pkg-config allegro-5 allegro_primitives-5 allegro_font-5 allegro_dialog-5 --libs --cflags)

clean:
	$(RM) $(OBJECTS) $(TARGET)
