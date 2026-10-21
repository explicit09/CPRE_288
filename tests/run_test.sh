#!/bin/bash
set -e

#!/bin/bash
set -e

if [ -z "${TIVAWARE_ROOT:-}" ]; then
    case "$(uname -s)" in
        MINGW*|MSYS*)
            TIVAWARE_ROOT="C:/ti/TivaWare_C_Series-2.2.0.295"
            ;;
        *)
            echo "Set TIVAWARE_ROOT to your TivaWare folder."
            exit 1
            ;;
    esac
fi

mkdir -p .vscode/host-tests/build

gcc -std=gnu99 \
  -I "$TIVAWARE_ROOT" \
  tests/test_outlier_removal.c\
  Lab8/clean.c\
  -o .vscode/host-tests/build/test_find_smallest

  ./.vscode/host-tests/build/test_find_smallest