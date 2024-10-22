# Makefile pro kompilaci tnine.c
CC = gcc                    # Překladač
CFLAGS = -std=c11 -Wall -Wextra -Werror  # Přepínače pro překladač
TARGET = tnine              # Název výstupního souboru
SOURCE = tnine.c            # Název zdrojového souboru

# Hlavní cíl (výchozí)
all: $(TARGET)

# Cíl pro kompilaci
$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCE)

# Cíl pro vyčištění
clean:
	del $(TARGET)            # Pro Windows
	# rm -f $(TARGET)        # Pro Unix/Linux/Mac

.PHONY: all clean           # Uvedení cílů, které nejsou soubory
