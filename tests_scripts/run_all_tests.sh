#!/bin/bash

# ============================
#  Custom Shell Test Runner
# ============================
# Compares your custom shell (42sh) against tcsh for various commands.
# Supports:
#   - stdout output matching
#   - file output diffing (with ##file tag)
#   - crash detection
#   - automatic cleanup
#
# 📁 Test files go in: ./tests_scripts/tests/*.txt
# ➕ Add ##file at the end of a line if the output is stored in a file
#     and not displayed by the command itself (e.g., `echo hello > out.txt ##file`)
#     If the command already prints the file content (e.g., `echo hello > out.txt && cat out.txt`), you do NOT need ##file.
# ➕ Add comments with # (excluding ##file) — they will be ignored before execution.
# ============================

shell_ref="tcsh"
shell_test="./42sh"
input_dir="./tests_scripts/tests"
total=0
passed=0

# ❌ Check for valid test shell binary
if ! [ -x "$shell_test" ]; then
    echo "❌ Shell binary not found or not executable: $shell_test"
    exit 127
fi

echo "🧪 Running all test files in $input_dir..."

# 📄 Loop through each test file
for file in "$input_dir"/*.txt; do
    test_name=$(basename "$file" .txt)
    echo "🔍 Testing: $test_name"

    lineno=0
    while IFS= read -r cmd || [[ -n "$cmd" ]]; do
        lineno=$((lineno + 1))

        # 🚫 Ignore empty lines or full-line comments
        trimmed=$(echo "$cmd" | xargs)
        [[ -z "$trimmed" || "$trimmed" =~ ^# ]] && continue

        total=$((total + 1))

        # ✅ Detect and remove ##file, ignore normal comments
        is_file_test=$(echo "$cmd" | grep -q "##file" && echo true || echo false)
        if [ "$is_file_test" = true ]; then
            cmd_only=$(echo "$cmd" | sed 's/##file.*//' | sed 's/#.*//' | xargs)
        else
            cmd_only=$(echo "$cmd" | sed 's/#.*//' | xargs)
        fi

        # 📸 Snapshot file list before command
        before_files=$(find . -maxdepth 1 -type f | sort)

        if [ "$is_file_test" = true ]; then
            # === FILE OUTPUT TEST ===

            echo "$cmd_only" | $shell_ref > /dev/null 2>&1
            ref_after=$(find . -maxdepth 1 -type f | sort)
            ref_created=$(comm -13 <(echo "$before_files") <(echo "$ref_after"))

            echo "$cmd_only" | $shell_test > /dev/null 2>&1
            status=$?
            test_after=$(find . -maxdepth 1 -type f | sort)
            test_created=$(comm -13 <(echo "$before_files") <(echo "$test_after"))

            if [ -z "$ref_created" ]; then
                echo "  ⚠️ [$lineno] $cmd_only"
                echo "     Reference shell did not create any output file"
                continue
            fi

            if [ -z "$test_created" ]; then
                echo "  ❌ [$lineno] $cmd_only"
                echo "     Your shell did not create any output file"
                continue
            fi

            cat $ref_created 2>/dev/null > .out_tcsh
            cat $test_created 2>/dev/null > .out_42sh

            if [ $status -ge 128 ]; then
                echo "  ❌ [$lineno] $cmd_only"
                echo "     ❌ Your shell crashed or exited abnormally (exit code $status)"
            elif diff -q .out_tcsh .out_42sh &>/dev/null; then
                echo "  ✅ [$lineno] $cmd_only"
                passed=$((passed + 1))
            else
                echo "  ❌ [$lineno] $cmd_only"
                echo "     File output mismatch:"
                echo "     Expected:"; cat .out_tcsh
                echo "     Got:"; cat .out_42sh
            fi

            rm -f $ref_created $test_created .out_tcsh .out_42sh

        else
            # === STDOUT OUTPUT TEST ===
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
                echo "     Expected:"
                echo "$expected"
                echo "     Got:"
                echo "$actual"
            fi
        fi

        # 🧹 Cleanup new files (if any)
        after_files=$(find . -maxdepth 1 -type f | sort)
        new_files=$(comm -13 <(echo "$before_files") <(echo "$after_files"))

        for f in $new_files; do
            [[ "$f" == "./42sh" ]] && continue
            [[ "$f" == "./run_all_tests.sh" ]] && continue
            rm -f "$f"
        done

    done < "$file"
    echo ""
done

# 📊 Final summary
if [ "$total" -eq 0 ]; then
    percent=100
else
    percent=$((passed * 100 / total))
fi

echo "🎯 Test result: $passed/$total passed ✅ ($percent%)"

# ====================================
# Usage Guide:
# ====================================
# 1. Add test files in tests_scripts/tests/
# 2. Each file contains one command per line
# 3. Use `##file` at the end of a line if output is written to a file
#     and not explicitly shown by the command.
#     ✅ Example: echo test > out.txt ##file
#     ❌ Not needed: echo test > out.txt && cat out.txt
# 4. Add regular comments using `#` (they’ll be stripped before execution).
# 5. Run with: `make run_tests` or `bash run_all_tests.sh`
# ====================================
