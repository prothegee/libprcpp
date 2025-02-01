#! /bin/bash	

cd .. && sphinx-multiversion docs/source docs/_build/dirhtml \
    --pre-build 'doxygen Doxyfile.in' \
    --pre-build "find . -mindepth 2 -name README.md -execdir mv '{}' index.md ';'"
