# Diretórios de origem e destino
SRCDIR = src
OBJDIR = obj
BINDIR = bin
INCDIR = include

# Nome dos arquivos fonte
SOURCES = $(SRCDIR)/main.cpp $(SRCDIR)/Huffman.cpp

# Objetos gerados
OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SOURCES))

# Flags do compilador
CXXFLAGS = -std=c++11 -Wall -I$(INCDIR)

# Nome do executável
TARGET = $(BINDIR)/huffman

# Comando para compilar e criar o executável
$(TARGET): $(OBJECTS)
	@mkdir -p $(BINDIR)
	@$(CXX) $(CXXFLAGS) $^ -o $@
	@echo "Compilação concluída. O executável foi criado em $(TARGET)"

# Comando para compilar os objetos
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	@$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo "Compilado $<"

# Comando para executar o programa
run: $(TARGET)
	@./$(TARGET) $(arg1) $(arg2) $(arg3)

# Comando para limpar arquivos objeto e o executável
clean:
	@rm -rf $(BINDIR) $(OBJDIR)

.PHONY: clean