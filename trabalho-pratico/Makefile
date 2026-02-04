# Variáveis
CC = gcc
CFLAGS = -g -Wall -Wextra -std=c99 -Iinclude `pkg-config --cflags glib-2.0`
LDFLAGS = `pkg-config --libs glib-2.0`
OBJDIR = obj
SRCDIR = src
INCDIR = include
RESULTSDIR = resultados
EXEC_PRINCIPAL = programa-principal
EXEC_INTERATIVO = programa-interativo
EXEC_TESTES = programa-testes


# Arquivos fonte
SRC_FILES = $(SRCDIR)/Entidades/artists.c $(SRCDIR)/Entidades/albuns.c $(SRCDIR)/Entidades/history.c \
            $(SRCDIR)/HashParser/hash.c $(SRCDIR)/Entidades/musics.c $(SRCDIR)/HashParser/parser.c \
            $(SRCDIR)/Queries/Q1.c $(SRCDIR)/Queries/Q2.c $(SRCDIR)/Queries/Q3.c $(SRCDIR)/Entidades/users.c \
			$(SRCDIR)/Queries/Q4.c $(SRCDIR)/Queries/Q5.c $(SRCDIR)/Queries/Q6.c \
            $(SRCDIR)/Validacoes/validation.c $(SRCDIR)/Utilitarias/utilitarias.c \
            $(SRCDIR)/Programas/principal.c $(SRCDIR)/main.c $(SRCDIR)/Programas/interactive.c $(SRCDIR)/Programas/tests.c


# Arquivos objeto para todos os programas
OBJ_FILES = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRC_FILES))

# Regra principal
all: $(EXEC_PRINCIPAL) $(EXEC_INTERATIVO) $(EXEC_TESTES)

# Compilar o programa principal
$(EXEC_PRINCIPAL): $(OBJ_FILES)
	$(CC) $(OBJ_FILES) $(LDFLAGS) -o $(EXEC_PRINCIPAL)

# Compilar o programa interativo
$(EXEC_INTERATIVO): $(OBJ_FILES)
	$(CC) $(OBJ_FILES) $(LDFLAGS) -o $(EXEC_INTERATIVO)

# Compilar o programa de testes
$(EXEC_TESTES): $(OBJ_FILES)
	$(CC) $(OBJ_FILES) $(LDFLAGS) -o $(EXEC_TESTES)

# Regra para compilar arquivos .o
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)  # Cria os diretórios necessários no OBJDIR
	@mkdir -p $(RESULTSDIR)  # Cria o diretório de resultados
	$(CC) $(CFLAGS) -c $< -o $@

# Alvo para rodar o programa com Valgrind
valgrind: $(EXEC_PRINCIPAL)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(EXEC_PRINCIPAL)

# Limpeza
clean:
	rm -rf $(OBJDIR) $(EXEC_PRINCIPAL) $(EXEC_INTERATIVO) $(EXEC_TESTES)
	rm -rf $(RESULTSDIR)/*

.PHONY: all clean valgrind
