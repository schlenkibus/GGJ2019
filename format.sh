#/bin/bash

find src/ -iname *.h -o -iname *.cpp | xargs clang-format-3.9 -i --style=file
