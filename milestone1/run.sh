#!/bin/bash

INSTRUCTIONS="How to use: $0 [options]\nOptions:\n\t-i  Specify input (.py) file\n\t-o  Specify output (.pdf) file\n\t-v  Enable verbose mode\n\t-h  Show help"
HELP_MESSAGE=$INSTRUCTIONS

display_help() { echo -e $HELP_MESSAGE; exit 0; }
show_usage() { echo "Usage: $0 [-i input] [-o output] [-v] [-h]"; exit 1; }

file_py=""
file_pdf=""
file_dot="out.dot"
verbose_mode=0
OPTIONS=$(getopt -o i:o:vh -- "$@")
eval set -- "$OPTIONS"

while :; do
    case "$1" in
        -i)
            file_py="$2"
            shift 2 ;;
        -o)
            file_pdf="$2"
            shift 2 ;;
        -v)
            verbose_mode=1
            shift ;;
        -h)
            display_help ;;
        --)
            shift; break ;;
        *)
            show_usage ;;
    esac
done

if [ -z "$file_py" ]; then
    echo "Error: Input file is missing."
    exit 1
fi

if [ -z "$file_pdf" ]; then
    echo "Error: Output file is missing."
    exit 1
fi

EXEC_PARSER="src/parser_exec.out"
eval "$EXEC_PARSER $file_py $file_dot $verbose_mode"
eval "dot -Tpdf $file_dot -o $file_pdf"
