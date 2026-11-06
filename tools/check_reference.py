#!/usr/bin/env python3
"""Check printed fragment contracts/links; compile and run actual C++ snippets."""
import argparse
from collections import Counter
import os
from pathlib import Path
import re
import shlex
import subprocess
import tempfile

ROOT = Path(__file__).resolve().parents[1]


def documents():
    source = (ROOT / "reference.tex").read_text()
    descriptions = (ROOT / "descriptions.tex").read_text()
    files = re.findall(r"^\\cppfile(?:\[[^]]*\])?\{([^}]+)\}", source, re.M)
    cards = re.findall(r"^\\algodesc\{([^}]+)\}", descriptions, re.M)
    assert len(files) == len(set(files)), "duplicate printed fragment"
    assert all(count == 1 for count in Counter(cards).values()), "duplicate description"
    assert set(files) == set(cards), f"description mismatch: {set(files) ^ set(cards)}"
    for file in files:
        assert (ROOT / file).is_file(), f"missing code: {file}"
    texts = "\n".join(p.read_text() for p in ROOT.glob("*.tex"))
    for file in re.findall(r"\\algoref\{([^}]+)\}", texts):
        assert file in files, f"link to unprinted fragment: {file}"
    for file in re.findall(r"\\input\{([^}]+)\}", source):
        assert (ROOT / file).is_file(), f"missing TeX input: {file}"
    for macro in ["pb", "mp", "fst", "snd", "fore", "ALL", "SZ"]:
        assert re.search(r"^#define " + macro + r"\b", (ROOT / "other/template.cpp").read_text(), re.M)
    test = (ROOT / "tests/notebook_algorithms_test.cpp").read_text()
    included = re.findall(r'#include "\.\./([^\"]+)"', test)
    print(f"OK: {len(files)} fichas, archivos y enlaces; {len(included)} fragmentos incluidos en pruebas", flush=True)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--docs-only", action="store_true")
    parser.add_argument("--sanitize", action="store_true", help="address + undefined; ignores legacy allocation leaks")
    args = parser.parse_args()
    documents()
    if args.docs_only:
        return
    compiler = shlex.split(os.environ.get("CXX", "c++"))
    flags = ["-std=c++17", "-O2", "-Wno-dangling-else"]
    if args.sanitize:
        flags = ["-std=c++17", "-O1", "-g", "-Wno-dangling-else", "-fsanitize=address,undefined", "-fno-omit-frame-pointer"]
    with tempfile.TemporaryDirectory(prefix="icpc-notebook-") as tmp:
        exe = str(Path(tmp) / "checks")
        subprocess.run(compiler + flags + [str(ROOT / "tests/notebook_algorithms_test.cpp"), "-o", exe], check=True)
        env = os.environ.copy()
        if args.sanitize:
            env["ASAN_OPTIONS"] = "detect_leaks=0"
        subprocess.run([exe], check=True, env=env)


if __name__ == "__main__":
    main()
