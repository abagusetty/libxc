#!/usr/bin/env bash
#set -euo pipefail

LLVM_SPIRV=/opt/aurora/25.190.0/oneapi/compiler/2025.2/bin/compiler/llvm-spirv
OCLOC=ocloc
OUTDIR=spv_out
mkdir -p "$OUTDIR"

for bc in *.bc; do
  echo "=== $bc ==="
  # sanity-check it's LLVM bitcode
  file "$bc"

  spv="$OUTDIR/${bc%.bc}.spv"
  # asm="$OUTDIR/${bc%.bc}.spvasm"
  log="$OUTDIR/${bc%.bc}.ocloc.log"

  echo "Converting $bc -> $spv"
  "$LLVM_SPIRV" -o "$spv" "$bc" || { echo "llvm-spirv failed for $bc"; continue; }

  # echo "Disassembling for inspection -> $asm"
  # spirv-dis "$spv" -o "$asm" || true

  echo "Running ocloc..."
  $OCLOC -device pvc -spirv_input -file "$spv" -internal_options -cl-intel-compile-one-at-time > "$log" 

  # # show a short summary of ocloc output
  # echo "---- ocloc summary for $spv ----"
  # tail -n +1 "$log" | sed -n '1,200p'
  # echo "---------------------------------"
done
