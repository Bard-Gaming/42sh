#!/bin/bash

shell_ref="tcsh"
shell_test="./42sh"
input_dir="./tests_scripts/tests"

total=0
passed=0

# Snapshot files before running the command
before_files="$(ls)"

if ! [ -x "$shell_test" ]; then
    echo "❌ Shell binary not found or not executable: $shell_test"
    exit 127
fi

echo "🧪 Running all test files in $input_dir..."

for file in "$input_dir"/*.txt; do
    test_name=$(basename "$file" .txt)
    echo "🔍 Testing: $test_name"

    lineno=0
    while IFS= read -r cmd || [[ -n "$cmd" ]]; do
        lineno=$((lineno + 1))
        total=$((total + 1))

        cmd_only="$(echo "$cmd" | cut -d'#' -f1 | xargs)"
        is_file_test=$(echo "$cmd" | grep -q "#file" && echo true || echo false)

        before_files="$(ls)"

      if [ "$is_file_test" = true ]; then
          # Run with tcsh
          echo "$cmd_only" | $shell_ref 2>/dev/null
          if [ ! -f out.txt ]; then
              echo "  ⚠️ [$lineno] $cmd_only"
              echo "     Reference shell (tcsh) didn't create out.txt"
              continue
          fi
          cp out.txt .out_tcsh 2>/dev/null
          rm -f out.txt

          # Run with 42sh and capture crash signal
          echo "$cmd_only" | $shell_test 2>/dev/null
          status=$?

          if [ ! -f out.txt ]; then
              echo "  ❌ [$lineno] $cmd_only"
              echo "     Your shell did not create the expected file: out.txt"
          elif [ $status -ge 128 ]; then
              echo "  ❌ [$lineno] $cmd_only"
              echo "     Your shell crashed or exited abnormally (exit code $status)"
          else
              cp out.txt .out_42sh 2>/dev/null
              if diff -q .out_tcsh .out_42sh &>/dev/null; then
                  echo "  ✅ [$lineno] $cmd_only"
                  passed=$((passed + 1))
              else
                  echo "  ❌ [$lineno] $cmd_only"
                  echo "     File output mismatch:"
                  echo "     Expected:"
                  cat .out_tcsh
                  echo "     Got:"
                  cat .out_42sh
              fi
          fi

          rm -f .out_tcsh .out_42sh out.txt

          # Cleanup test-created files
          after_files="$(ls)"
          for f in $after_files; do
              if ! echo "$before_files" | grep -qx "$f"; then
                  rm -f "$f"
              fi
          done

        else
            # Fallback to stdout comparison
            expected=$(echo "$cmd_only" | $shell_ref 2>/dev/null)
            actual=$(echo "$cmd_only" | $shell_test 2>/dev/null)
            status=$?

            if [ $status -ge 128 ]; then
                echo "  ❌ [$lineno] $cmd_only"
                echo "     ❌ Your shell crashed or exited abnormally (exit code $status)"
            elif [ "$actual" = "$expected" ]; then
                echo "  ✅ [$lineno] $cmd_only"
                passed=$((passed + 1))
            else
                echo "  ❌ [$lineno] $cmd_only"
                echo "     Expected: '$expected'"
                echo "     Got:      '$actual'"
            fi
        fi
    done < "$file"
    echo ""
done

# ✅ Final summary AFTER all files
if [ "$total" -eq 0 ]; then
    percent=100
else
    percent=$((passed * 100 / total))
fi

echo "🎯 Test result: $passed/$total passed ✅ ($percent%)"
