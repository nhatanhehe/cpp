import os
import sys
import subprocess
import zipfile
import shutil

def compile_cpp(source, executable):
    """Compile a C++ source file."""
    cmd = ["g++", "-std=c++17", "-O2", "-o", executable, source]
    try:
        subprocess.run(cmd, check=True, capture_output=True, text=True)
        print(f"Compiled {source} -> {executable}")
    except subprocess.CalledProcessError as e:
        print(f"Compilation failed for {source}:")
        print(e.stderr)
        sys.exit(1)

def run_executable(executable, input_file, output_file):
    """Run the executable with input from input_file and write to output_file."""
    with open(input_file, 'r') as fin, open(output_file, 'w') as fout:
        try:
            result = subprocess.run([executable], stdin=fin, stdout=fout, stderr=subprocess.PIPE, text=True, check=False)
            if result.returncode != 0:
                print(f"Execution failed for {executable} with input {input_file}:")
                print(result.stderr)
                sys.exit(1)
        except Exception as e:
            print(f"Unexpected error running {executable}: {e}")
            sys.exit(1)

def main():
    # We are in the Bookshelf_MultiTest directory
    print("Starting test generation...")

    # Compile generator and solution
    compile_cpp("gen.cpp", "gen")
    compile_cpp("solution.cpp", "solution")

    # Generate 50 test files
    for i in range(1, 51):
        # Determine subtask based on file number
        if 1 <= i <= 10:
            subtask = 1
        elif 11 <= i <= 25:
            subtask = 2
        else: # 26 <= i <= 50
            subtask = 3

        # Generate .in file
        in_file = f"{i}.in"
        # We'll use the file number as seed for variability, but also add a constant to avoid same patterns
        seed = i * 123456789
        cmd = ["./gen", str(subtask), str(i), str(seed)]
        print(f"Generating {in_file} (subtask {subtask})...")
        try:
            subprocess.run(cmd, check=True, capture_output=True, text=True)
        except subprocess.CalledProcessError as e:
            print(f"Generation failed for {in_file}:")
            print(e.stderr)
            sys.exit(1)

        # Run solution to generate .out
        out_file = f"{i}.out"
        print(f"Running solution on {in_file} -> {out_file}")
        run_executable("./solution", in_file, out_file)

    # Create ZIP archive
    zip_name = "TESTS.zip"
    print(f"Creating {zip_name}...")
    with zipfile.ZipFile(zip_name, 'w', zipfile.ZIP_DEFLATED) as zf:
        for i in range(1, 51):
            in_file = f"{i}.in"
            out_file = f"{i}.out"
            if os.path.exists(in_file):
                zf.write(in_file)
            if os.path.exists(out_file):
                zf.write(out_file)

    print("Done!")

if __name__ == "__main__":
    main()