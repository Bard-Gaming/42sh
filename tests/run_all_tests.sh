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
# ➕ Add comments with # (excluding ##file) — full-line comments and empty lines will be ignored.
# ============================

# ====================================
# Usage Guide:
# ====================================
# 1. Add test files in tests/tests/
# 2. Each file contains one command per line
# 3. Use `##file` at the end of a line if output is written to a file
#     and not explicitly shown by the command.
#     ✅ Example: echo test > out.txt ##file
#     ❌ Not needed: echo test > out.txt && cat out.txt
# 4. Use # to add comments on lines or alone (they’ll be stripped before execution).
# 5. Run with: `make run_tests` or `bash run_all_tests.sh`
# ====================================

# Reference shell and your custom shell binary
shell_ref="tcsh"
shell_test="./42sh"
input_dir="./tests/tests"

# Stats tracking
total=0
passed=0

# ✅ Check if your shell exists and is executable
if ! [ -x "$shell_test" ]; then
    echo "❌ Shell binary not found or not executable: $shell_test"
    exit 127
fi

echo "🧪 Running all test files in $input_dir..."

# 🔁 Loop over each test file (e.g., basics.txt, redirections.txt...)
for file in "$input_dir"/*.txt; do
    test_name=$(basename "$file" .txt)
    echo "🔍 Testing: $test_name"

    lineno=0
    # 📄 Read file line by line
    while IFS= read -r line || [[ -n "$line" ]]; do
        lineno=$((lineno + 1))

        # ⛔ Skip empty lines and full-line comments
        trimmed=$(echo "$line" | sed 's/^[[:space:]]*//')
        [[ -z "$trimmed" || "$trimmed" =~ ^# ]] && continue

        total=$((total + 1))

        # 🔍 Detect file-based test via ##file marker
        is_file_test=$(echo "$line" | grep -q "##file" && echo true || echo false)

        # 🧹 Strip comments and isolate command (still keep the original for display)
        if [ "$is_file_test" = true ]; then
            cmd_only=$(echo "$line" | sed 's/##file.*//' | sed 's/#.*//')
        else
            cmd_only=$(echo "$line" | sed 's/#.*//')
        fi

        # 🧼 Clean up any leading or trailing spaces
        cmd_only="${cmd_only#"${cmd_only%%[![:space:]]*}"}"
        cmd_only="${cmd_only%"${cmd_only##*[![:space:]]}"}"

        # 📸 Take snapshot of files before running command
        before_files=$(find . -maxdepth 1 -type f | sort)

        # ========================
        # 📂 FILE OUTPUT COMPARISON
        # ========================
        if [ "$is_file_test" = true ]; then
            # Run command in reference shell
            printf "%s\n" "$cmd_only" | $shell_ref > /dev/null 2>&1
            ref_after=$(find . -maxdepth 1 -type f | sort)
            ref_created=$(comm -13 <(echo "$before_files") <(echo "$ref_after"))

            # Run command in custom shell
            printf "%s\n" "$cmd_only" | $shell_test > /dev/null 2>&1
            status=$?
            test_after=$(find . -maxdepth 1 -type f | sort)
            test_created=$(comm -13 <(echo "$before_files") <(echo "$test_after"))

            # Check if reference shell created a file
            if [ -z "$ref_created" ]; then
                echo "  ⚠️ [$lineno] $cmd_only"
                echo "     Reference shell did not create any output file"
                continue
            fi

            # Check if your shell created a file
            if [ -z "$test_created" ]; then
                echo "  ❌ [$lineno] $cmd_only"
                echo "     Your shell did not create any output file"
                continue
            fi

            # 🧪 Combine content of all created files
            > .out_tcsh
            for f in $ref_created; do
                [ -f "$f" ] && cat "$f" >> .out_tcsh
            done

            > .out_42sh
            for f in $test_created; do
                [ -f "$f" ] && cat "$f" >> .out_42sh
            done

            # ✅ Compare file outputs
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

            # 🧽 Cleanup all temporary and output files
            rm -f $ref_created $test_created .out_tcsh .out_42sh

        # ========================
        # 🖨️ STDOUT OUTPUT COMPARISON
        # ========================
        else
            # Run command and capture both stdout and stderr
            expected=$(printf "%s\n" "$cmd_only" | $shell_ref 2>&1)
            actual=$(printf "%s\n" "$cmd_only" | $shell_test 2>&1)
            status=$?

            # ❌ Crash detection
            if [ $status -ge 128 ]; then
                echo "  ❌ [$lineno] $cmd_only"
                echo "     ❌ Your shell crashed or exited abnormally (exit code $status)"
            elif [ "$actual" = "$expected" ]; then
                echo "  ✅ [$lineno] $cmd_only"
                passed=$((passed + 1))
            else
                echo "  ❌ [$lineno] $cmd_only"
                echo "     Expected:"; echo "$expected"
                echo "     Got:"; echo "$actual"
            fi
        fi

        # 🧹 Cleanup any remaining new files
        after_files=$(find . -maxdepth 1 -type f | sort)
        new_files=$(comm -13 <(echo "$before_files") <(echo "$after_files"))
        for f in $new_files; do
            [[ "$f" == "./42sh" || "$f" == "./run_all_tests.sh" ]] && continue
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
