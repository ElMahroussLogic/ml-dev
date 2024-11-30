# !/bin/sh

# Build frameworks as PEF dylibs.
pbtb --fmt=pef64 --sign=YES dev/*/*.json

# Prompt that task is done.
echo "PBTB task is done. (PEF C++ target)"