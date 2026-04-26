# Fibonacci – Generador y Visualizador de Secuencia

**Asignatura:** Sistemas Computacionales  
**Institución:** ESCOM – IPN  
**Herramientas:** C++23, GNUplot, Make

---

## Descripción del proyecto

Este proyecto calcula los primeros N términos de la **secuencia de Fibonacci**, definida por:

```
F(0) = 0
F(1) = 1
F(n) = F(n-1) + F(n-2)   para n ≥ 2
```

El programa escribe los resultados en `fibonacci.txt` y un script de GNUplot genera automáticamente una gráfica PNG de la secuencia.

El proceso completo está automatizado con un **Makefile**: desde la compilación hasta la imagen final, todo se ejecuta con un solo comando.

---

## Archivos del proyecto

| Archivo | Descripción |
|---|---|
| `main.cpp` | Código fuente. Calcula Fibonacci y escribe `fibonacci.txt`. |
| `fibonacci.gp` | Script GNUplot. Genera `fibonacci.png` desde los datos. |
| `Makefile` | Automatiza compilación, ejecución y graficación. |
| `.gitignore` | Excluye archivos generados del repositorio. |

---

## Requisitos

- `g++` compatible con C++23
- `gnuplot` instalado
- Linux, macOS o WSL

---

## Instrucciones de uso

### Clonar el repositorio

```bash
git clone https://github.com/Champagnepagcois/makefile.git
cd Mi_makeFile
```

### Ejecutar el flujo completo

```bash
make
```

Esto ejecuta en orden:
1. Compila `main.cpp` → `main.o` → `fibonacci`
2. Ejecuta `fibonacci` → genera `fibonacci.txt`
3. Lanza GNUplot → genera `fibonacci.png`

### Comandos disponibles

| Comando | Acción |
|---|---|
| `make` | Compilar, ejecutar y graficar |
| `make run` | Solo ejecuta el programa |
| `make plot` | Solo genera la gráfica |
| `make clean` | Elimina archivos generados |
| `make rebuild` | Limpia y reconstruye todo |
| `make vars` | Muestra variables internas |
| `make help` | Lista todos los comandos |

---

## Análisis del Makefile

### Variables

```makefile
CXX      = g++
CXXFLAGS = -std=c++23 -O2 -Wall
GP       = fibonacci.gp
TXT      = $(GP:.gp=.txt)   # → fibonacci.txt
PNG      = $(GP:.gp=.png)   # → fibonacci.png
SRCS     = main.cpp
OBJS     = $(SRCS:.cpp=.o)  # → main.o
APP      = fibonacci
```

Las variables permiten cambiar el compilador, flags o nombre del proyecto en un solo lugar. La sustitución de sufijo `$(VAR:.ext1=.ext2)` evita repetir nombres de archivo.

### Objetivo `all`

```makefile
all: run plot
```

Primer objetivo del archivo. Al ejecutar `make` sin argumentos, `make` construye `all`, que depende de `run` y `plot`.

### Regla de patrón

```makefile
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
```

Regla genérica para compilar cualquier `.cpp` a `.o`. Si se agregaran más archivos fuente, esta regla los manejaría sin cambios adicionales.

### Enlace

```makefile
$(APP): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(APP)
```

Produce el ejecutable final. `make` reconstruye este objetivo solo si algún `.o` cambió.

### `plot` depende de `$(TXT)`

```makefile
plot: $(TXT) $(GP)
	gnuplot $(GP)
```

Si `fibonacci.txt` no existe, `make` busca cómo generarlo. La cadena de dependencias lo lleva a compilar y ejecutar el programa primero automáticamente.

### `rebuild`

```makefile
rebuild: clean all
```

Objetivo compuesto: limpia y reconstruye desde cero. Útil al cambiar flags de compilación.

### `help`

```makefile
help:
	@echo "  make       → compila, ejecuta y grafica"
	...
```

El prefijo `@` suprime la impresión del comando mismo, mostrando solo su salida.

### `.PHONY`

```makefile
.PHONY: all run plot clean help rebuild vars
```

Declara que estos objetivos no corresponden a archivos reales. Sin esto, si existiera un archivo llamado `clean`, `make` lo ignoraría creyendo que ya está construido.

---

## Resultados de ejecución

```
[1/3] Compilando main.cpp...
g++ -std=c++23 -O2 -Wall -c main.cpp -o main.o
[2/3] Enlazando → fibonacci
g++ -std=c++23 -O2 -Wall main.o -o fibonacci
[3/3] Ejecutando fibonacci...
./fibonacci

Secuencia de Fibonacci (primeros 40 terminos):
    n               F(n)
-------------------------
    0                  0
    1                  1
    2                  1
    ...
   39        102334155
Datos guardados en fibonacci.txt

[+] Generando grafica con GNUplot...
[+] Imagen guardada: fibonacci.png
✓ Listo. Imagen generada: fibonacci.png
```

La gráfica muestra el crecimiento exponencial característico de la secuencia, confirmando la relación con la razón áurea φ ≈ 1.618.

---

## ¿Por qué usar un Makefile aquí?

Sin Makefile, cada vez que se modifica `main.cpp` habría que recordar y ejecutar manualmente:

```bash
g++ -std=c++23 -O2 -Wall -c main.cpp -o main.o
g++ -std=c++23 -O2 -Wall main.o -o fibonacci
./fibonacci
gnuplot fibonacci.gp
```

El Makefile resuelve esto porque:

- **Detecta cambios:** si solo se modifica `fibonacci.gp`, reconstruye solo la gráfica, no el binario.
- **Documenta el proceso:** el Makefile funciona como documentación ejecutable de cómo se construye el proyecto.
- **Elimina errores:** no hay riesgo de olvidar un paso o escribir un flag incorrecto.

---

## Estructura del repositorio

```
Mi_makeFile/
├── main.cpp        ← código fuente
├── fibonacci.gp    ← script GNUplot
├── Makefile        ← automatización
├── .gitignore      ← excluye archivos generados
└── README.md       ← documentación
```

Los archivos `*.o`, `fibonacci`, `fibonacci.txt` y `fibonacci.png` **no se suben al repositorio** porque se generan con `make`. Esto mantiene el repositorio limpio y cualquier persona puede reproducir el proyecto desde cero.
