import os
import re

# Configuración de los reemplazos
# El orden importa: primero las funciones con argumentos, luego palabras simples.
replacements = [
    # fore(i, a, b) -> for(int i = a, _n = b; i < _n; ++i)
    # Usamos _n para evitar evaluar el límite b múltiples veces si fuera una función.
    (r'\bfore\s*\(\s*([^,]+)\s*,\s*([^,]+)\s*,\s*([^,)]+)\s*\)', 
     r'for (int \1 = \2, _n = \3; \1 < _n; ++\1)'),
    
    # SZ(x) -> ((int)(x).size())
    (r'\bSZ\s*\((.*?)\)', r'((int)(\1).size())'),
    
    # Reemplazos simples con word boundaries (\b) para no romper otras palabras
    (r'\bpb\b', 'push_back'),
    (r'\bmp\b', 'make_pair'),
    (r'\bfst\b', 'first'),
    (r'\bsnd\b', 'second'),
]

def clean_file(filepath):
    with open(filepath, 'r', encoding='utf-8') as f:
        content = f.read()

    # Aplicar los reemplazos de macros
    new_content = content
    for pattern, substitute in replacements:
        new_content = re.sub(pattern, substitute, new_content)

    # Opcional: Eliminar los bloques de macros viejas si están en los archivos individuales
    # Esto busca el bloque de #ifdef DEMETRIO hasta el final de las definiciones de macros
    new_content = re.sub(r'#ifdef DEMETRIO.*?typedef long long ll;(\n)?', '', new_content, flags=re.DOTALL)

    # Escribir solo si hubo cambios
    if new_content != content:
        with open(filepath, 'w', encoding='utf-8') as f:
            f.write(new_content)
        print(f"Modificado: {filepath}")

def main():
    # Carpetas a procesar (basado en tu estructura)
    folders = ['data_structures', 'flow', 'geometry', 'graphs', 'math', 'other', 'strings']
    
    for folder in folders:
        if not os.path.exists(folder):
            continue
            
        for root, dirs, files in os.walk(folder):
            for file in files:
                if file.endswith('.cpp') or file.endswith('.h'):
                    clean_file(os.path.join(root, file))

if __name__ == "__main__":
    print("Iniciando limpieza de macros...")
    main()
    print("¡Proceso completado!")