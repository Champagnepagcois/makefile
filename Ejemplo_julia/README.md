# Julia Set – Automatización con Makefile

**Materia:** Sistemas Embebidos 
**Institución:** ESCOM – IPN  
**Herramientas:** C++23, GNUplot, Make

---

## ¿Qué hace este proyecto?

Este proyecto genera y visualiza el **conjunto de Julia**, una figura fractal producida por iteración de la función compleja:

```
z_(n+1) = z_n² + c
```

donde `c = -0.70176 + (-0.3842)i` es una constante compleja fija.

El programa evalúa cuántas iteraciones tarda cada punto del plano complejo en "escapar" (superar módulo 2). El resultado se guarda en un archivo de texto y se grafica automáticamente con GNUplot, produciendo una imagen PNG del fractal.

---

## Archivos del proyecto

| Archivo | Descripción |
|---|---|
| `main.cpp` | Código fuente en C++. Calcula el conjunto de Julia y escribe los datos en `julia_set.txt`. |
| `julia_set.gp` | Script de GNUplot. Lee `julia_set.txt` y genera la imagen `julia_set.png`. |
| `Makefile` | Automatiza compilación, ejecución y graficación. |
| `.gitignore` | Excluye archivos generados (`*.o`, `julia`, `*.txt`, `*.png`). |

---

## Requisitos

- `g++` con soporte para C++23
- `gnuplot` instalado
- Sistema Linux o WSL (Windows Subsystem for Linux)

---

## Instrucciones de uso

### 1. Clonar el repositorio

```bash
git clone <URL-del-repositorio>
cd julia
```

### 2. Ejecutar el flujo completo

```bash
make
```

Este único comando ejecuta en orden:
1. Compila `main.cpp` → `main.o`
2. Enlaza `main.o` → ejecutable `julia`
3. Ejecuta `julia` → genera `julia_set.txt`
4. Ejecuta GNUplot → genera `julia_set.png`
5. Abre la imagen en el visor del sistema

### 3. Comandos individuales disponibles

| Comando | Acción |
|---|---|
| `make` | Flujo completo: compilar, ejecutar, graficar y abrir |
| `make run` | Solo ejecuta el binario (recompila si es necesario) |
| `make plot` | Solo genera la gráfica desde `julia_set.txt` |
| `make vars` | Muestra el valor de las variables internas del Makefile |
| `make clean` | Elimina todos los archivos generados |

---

## Análisis del Makefile

```makefile
# ─── Variables ───────────────────────────────────────────
CXX      = g++
CXXFLAGS = -std=c++23 -O3

GP  = julia_set.gp
TXT = $(GP:.gp=.txt)      # → julia_set.txt  (sustitución de sufijo)
PNG = $(GP:.gp=.png)      # → julia_set.png

SRCS = main.cpp
OBJS = $(SRCS:.cpp=.o)    # → main.o

APP = julia
```

Las variables centralizan nombres y flags. Si el proyecto crece o se cambia de compilador, basta modificar una línea.

```makefile
# ─── Objetivo principal ──────────────────────────────────
all: run plot open
```

`all` es el primer objetivo, así que `make` lo ejecuta por defecto. Depende de `run`, `plot` y `open`, que se resuelven en ese orden.

```makefile
# ─── Regla de patrón: compilación ────────────────────────
%.o: %.cpp
	@echo "Compiling"
	$(CXX) $(CXXFLAGS) -c $< -o $@
```

Regla genérica: cualquier `.o` se construye desde su `.cpp` correspondiente.  
- `$<` → primera dependencia (`main.cpp`)  
- `$@` → nombre del objetivo (`main.o`)

```makefile
# ─── Enlace ──────────────────────────────────────────────
$(APP): $(OBJS)
	@echo "Linking"
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(APP)
```

Combina los archivos objeto para producir el ejecutable `julia`.

```makefile
# ─── Ejecución ───────────────────────────────────────────
run: $(APP)
	@echo "RUN"
	./$(APP)
```

Garantiza que el ejecutable exista antes de correrlo. Si `main.cpp` fue modificado, `make` recompila automáticamente.

```makefile
# ─── Graficación ─────────────────────────────────────────
plot: $(TXT)
	@echo "Plot"
	gnuplot $(GP)
```

Depende de `julia_set.txt`. Si el archivo no existe, `make` lo genera ejecutando `run` primero.

```makefile
# ─── Apertura de imagen ───────────────────────────────────
open:
	@echo "Open"
	xdg-open $(PNG) &
```

Abre la imagen PNG con el visor predeterminado del sistema en segundo plano (`&`).

```makefile
# ─── Limpieza ────────────────────────────────────────────
clean:
	rm *.o $(APP) *.txt *.png
```

Elimina todos los artefactos generados. Útil para comenzar desde cero o antes de hacer commit.

```makefile
# ─── Variables de diagnóstico ────────────────────────────
.PHONY: vars
vars:
	@echo "SRCS = $(SRCS)"
	@echo "OBJS = $(OBJS)"
	@echo "GP   = $(GP)"
	@echo "TXT  = $(TXT)"
```

Objetivo de utilidad para verificar que las variables tengan el valor esperado.

---

## Resultados de ejecución

Al ejecutar `make`, la secuencia de salida en terminal es:

```
Compiling
g++ -std=c++23 -O3 -c main.cpp -o main.o
Linking
g++ -std=c++23 -O3 main.o -o julia
RUN
./julia
Plot
gnuplot julia_set.gp
PNG Mode Selected
Open
xdg-open julia_set.png &
```

Y se genera la imagen `julia_set.png` con el fractal de Julia para `c = -0.70176 - 0.3842i`:

> La imagen muestra una región fractal simétrica con degradado de color que representa la velocidad de escape de cada punto del plano complejo.

---

## ¿Cómo contribuye el Makefile a la automatización?

Sin Makefile, el flujo requeriría ejecutar manualmente 4 comandos distintos cada vez que se modifica el código. El Makefile resuelve esto de tres formas:

1. **Dependencias declarativas:** `make` analiza qué archivos cambiaron y reconstruye solo lo necesario. Si únicamente se modifica `julia_set.gp`, no recompila el C++.

2. **Un solo punto de entrada:** `make` (sin argumentos) ejecuta todo el pipeline de principio a fin.

3. **Reproducibilidad:** cualquier persona que clone el repositorio obtiene exactamente el mismo resultado con el mismo comando.

---

## .gitignore

```gitignore
# Archivos objeto
*.o

# Ejecutable
julia

# Datos generados
*.txt

# Imágenes generadas
*.png
*.pdf
```

Solo se versiona el código fuente (`main.cpp`, `julia_set.gp`, `Makefile`, `README.md`). Los archivos generados se excluyen porque pueden reproducirse con `make`.
