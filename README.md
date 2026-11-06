# The Strings — referencia ICPC

Guía en español del equipo “The algorithms are talking”, basada en
[El Vasito](https://github.com/mhunicken/icpc-team-notebook-el-vasito).
La copia original en el directorio hermano se conserva sin cambios.

La edición tiene fichas junto a cada fragmento: qué resuelve, entradas/salidas,
orden de llamadas, ejemplos, complejidad y casos donde no se debe usar.
El índice y las tablas por síntoma enlazan a las páginas de las implementaciones.

## Compilar

Desde este directorio:

```sh
./build.sh
```

Produce `reference.pdf`. Necesita Python 3 y un motor disponible: `latexmk`,
`pdflatex` (TeX Live/MacTeX) o `tectonic`. Para una instalación portátil:

```sh
TECTONIC=/ruta/a/tectonic ./build.sh
```

Tectonic descarga paquetes al primer uso. También se puede ejecutar
`pdflatex -interaction=nonstopmode -halt-on-error reference.tex` tres veces para
estabilizar índice, enlaces y total de páginas. A4 horizontal, dos columnas,
interlineado compacto; no se impone límite de páginas.

## Editar contenido

- `reference.tex`: orden de secciones y archivos impresos.
- `descriptions.tex`: fichas identificadas por ruta; `\cppfile` exige una ficha.
- `quickguide.tex`: selección por síntomas, convenciones y revisión de envíos.
- `recipes.tex`: llamadas completas, modelos de flujo y técnicas de DP/árboles.
- `identities.tex`: fórmulas con sus hipótesis y convenciones.
- `sources.tex`: evidencia de los sets LATAM 2024–2025 usados también en México,
  fuentes primarias y corte de consulta del 5 de noviembre de 2026. Las prioridades
  son una inferencia de preparación, sin porcentajes inventados de aparición.
- `preamble.tex`: diseño y macros de impresión; el texto no queda centrado por
  una declaración que se extienda accidentalmente a todo el documento.

## Verificar código y documentación

```sh
python3 tools/check_reference.py
python3 tools/check_reference.py --docs-only
python3 tools/check_reference.py --sanitize
```

El verificador comprueba fichas únicas, rutas, enlaces y abreviaturas. Compila
`tests/notebook_algorithms_test.cpp`, que **incluye los archivos reales** y
compara contra fuerza bruta, algoritmos simples u otras identidades con semilla
fija. Abarca todas las nuevas implementaciones y regresiones de estructuras,
cadenas, aritmética, transformadas, flujo y geometría. Se puede elegir compilador
con `CXX=g++` o `CXX=clang++`.

Los sanitizadores comprueban accesos y comportamiento indefinido; la detección
de fugas se desactiva porque algunas estructuras heredadas asignan nodos sin
destructor. No se afirma una revalidación de todos los algoritmos especializados
heredados contra jueces externos. Los antiguos `*_test.cpp` son en general
soluciones a problemas con entrada propia; no constituyen un runner automático.
Para usar los snippets GNU (`bits/stdc++.h`, PBDS, rope) hace falta libstdc++;
el runner local usa cabeceras estándar para poder ejecutarse también con Apple
Clang, sin reemplazar los algoritmos.

Correcciones incluyen límites de cadenas/LCP/eertree, casos vacíos de hull,
convoluciones y SA corto, orden estricto y tipos en geometría, liberación correcta
en Karatsuba, articulaciones aisladas, CRT sin alias ocultos, recurrencias con
índice `ll`, y min-cost flow con límite explícito, costos negativos iniciales y
potenciales sólo de alcanzables. Las fichas documentan las variantes que aún
requieren adaptación, por ejemplo 3D y agregados de Link-Cut.

El tester interactivo ahora es Python 3 y simula un protocolo de adivinar número;
no es un juez genérico. Uso: `python3 other/interactive_tester.py ./solucion --seed 42`.
