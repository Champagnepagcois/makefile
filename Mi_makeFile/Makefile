# =====================================================
#  Makefile – Proyecto Fibonacci
#  Automatiza: compilacion, ejecucion y graficacion
# =====================================================

# ── Variables ────────────────────────────────────────
CXX      = g++
CXXFLAGS = -std=c++23 -O2 -Wall

GP  = fibonacci.gp
TXT = $(GP:.gp=.txt)
PNG = $(GP:.gp=.png)

SRCS = main.cpp
OBJS = $(SRCS:.cpp=.o)
APP  = fibonacci

# ── Objetivo principal ────────────────────────────────
.PHONY: all run plot clean help rebuild vars

all: run plot
	@echo "✓ Listo. Imagen generada: $(PNG)"

# ── Regla de patron: .cpp → .o ───────────────────────
%.o: %.cpp
	@echo "[1/3] Compilando $<..."
	$(CXX) $(CXXFLAGS) -c $< -o $@

# ── Enlace: .o → ejecutable ──────────────────────────
$(APP): $(OBJS)
	@echo "[2/3] Enlazando → $(APP)"
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(APP)

# ── Ejecucion ────────────────────────────────────────
run: $(APP)
	@echo "[3/3] Ejecutando $(APP)..."
	./$(APP)

# ── Graficacion ──────────────────────────────────────
plot: $(TXT) $(GP)
	@echo "[+] Generando grafica con GNUplot..."
	gnuplot $(GP)
	@echo "[+] Imagen guardada: $(PNG)"

# ── Limpieza ─────────────────────────────────────────
clean:
	@echo "Limpiando archivos generados..."
	rm -f *.o $(APP) $(TXT) $(PNG)

# ── Reconstruir todo desde cero ──────────────────────
rebuild: clean all

# ── Mostrar variables internas ───────────────────────
vars:
	@echo "CXX      = $(CXX)"
	@echo "CXXFLAGS = $(CXXFLAGS)"
	@echo "APP      = $(APP)"
	@echo "SRCS     = $(SRCS)"
	@echo "OBJS     = $(OBJS)"
	@echo "TXT      = $(TXT)"
	@echo "PNG      = $(PNG)"

# ── Ayuda ────────────────────────────────────────────
help:
	@echo ""
	@echo "  Proyecto Fibonacci – Comandos disponibles:"
	@echo ""
	@echo "  make          → compila, ejecuta y grafica"
	@echo "  make run      → solo ejecuta el programa"
	@echo "  make plot     → solo genera la grafica PNG"
	@echo "  make clean    → elimina archivos generados"
	@echo "  make rebuild  → limpia y vuelve a construir"
	@echo "  make vars     → muestra variables internas"
	@echo "  make help     → muestra esta ayuda"
	@echo ""
