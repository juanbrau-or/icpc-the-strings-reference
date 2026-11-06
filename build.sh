#!/bin/sh
set -eu
cd "$(dirname "$0")"
python3 tools/check_reference.py --docs-only
if [ -n "${TECTONIC:-}" ]; then
    "$TECTONIC" --keep-logs reference.tex
elif command -v latexmk >/dev/null 2>&1; then
    latexmk -pdf -interaction=nonstopmode -halt-on-error reference.tex
elif command -v pdflatex >/dev/null 2>&1; then
    pdflatex -interaction=nonstopmode -halt-on-error reference.tex
    pdflatex -interaction=nonstopmode -halt-on-error reference.tex
    pdflatex -interaction=nonstopmode -halt-on-error reference.tex
elif command -v tectonic >/dev/null 2>&1; then
    tectonic --keep-logs reference.tex
else
    printf '%s\n' 'Falta un motor LaTeX: instala TeX Live/MacTeX o Tectonic.' >&2
    exit 1
fi
