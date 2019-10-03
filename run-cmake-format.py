#!/usr/bin/env python3

import os
import hashlib
import pathlib
import subprocess
import sys
import codecs
from chardet import detect

patterns = [
    'CMakeLists.txt',
    # Keep an explicit list of files to format as we don't want to reformat
    # files we imported from other location.
    'src/**/*.cmake',
    'tools/**/*.cmake',
    'examples/**/*.cmake',
    'tests/**/*.cmake',
    'benchmarks/**/*.cmake',
    'cmake/**/*.cmake',
    # CMakeLists
    'src/**/CMakeLists.txt',
    'tools/**/CMakeLists.txt',
    'examples/**/CMakeLists.txt',
    'tests/**/CMakeLists.txt',
    'benchmarks/**/CMakeLists.txt',
    'cmake/**/CMakeLists.txt'
]

ignore_patterns = [
    '**/*submodule*/**/*.cmake',
    '**/*submodule*/**/*[cC][mM]ake*'
]

here = pathlib.Path(__file__).parent


def find_cmake_files():
    for pat in patterns:
        patset = set(here.glob(pat))
        for ig in ignore_patterns:
          patset -= set(here.glob(ig))
        yield from ( patset )

# get file encoding type
def get_encoding_type(file):
    with open(file, 'rb') as f:
        rawdata = f.read()
    return detect(rawdata)['encoding']

def run_cmake_format(paths):
    # cmake-format is fast enough that running in parallel doesn't seem
    # necessary
    # autosort is off because it breaks in cmake_format 5.1
    #   See: https://github.com/cheshirekow/cmake_format/issues/111
    cmd = ['python3', '-m cmake_format', '-c cmake-format.py', '-i'] + paths

    #out = subprocess.check_output(cmd) # example
    #print(out)
    try:
        print(subprocess.run(' '.join([str(v) for v in cmd]), shell=True, check=True, universal_newlines=True, stdout=subprocess.PIPE).stdout)
    except FileNotFoundError:
        try:
            import cmake_format
        except ImportError:
            raise ImportError(
                "Please install cmake-format: `pip install cmake_format`")
        else:
            # Other error, re-raise
            raise


def check_cmake_format(paths):
    hashes = {}
    for p in paths:
        contents = p.read_bytes()
        hashes[p] = hashlib.sha256(contents).digest()

    run_cmake_format(paths)

    # Check contents didn't change
    changed = []
    for p in paths:
        contents = p.read_bytes()
        if hashes[p] != hashlib.sha256(contents).digest():
            changed.append(p)

    if changed:
        items = "\n".join("- %s" % p for p in sorted(changed))
        print("The following cmake files need re-formatting:\n%s" % (items,))
        print()
        print("Consider running `run-cmake-format.py`")
        sys.exit(1)


if __name__ == "__main__":
    paths = list(find_cmake_files())
    print("running `run-cmake-format.py` on \n%s" % ("\n".join("- %s" % p for p in sorted(paths))))

    # convert to utf8
    for p in paths:
      try:
        with open(p, 'r', encoding=get_encoding_type(p)) as srcfile:
            text = srcfile.read() # for small files, for big use chunks
            os.remove(p) # remove old encoding file
            with open(p, 'w', encoding='utf-8') as outfile:
              outfile.write(text)
      except UnicodeDecodeError:
          print('Decode Error in' + p)
      except UnicodeEncodeError:
          print('Encode Error in' + p)

    if "--check" in sys.argv:
        check_cmake_format(paths)
    else:
        run_cmake_format(paths)
