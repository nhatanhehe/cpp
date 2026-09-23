import os
import subprocess
import sys
import zipfile

def compile_cpp(source, executable):
    """Compile a C++ source file."""
    cmd = ["g++", "-O2", "-std=c++17", source, "-o", executable]
    result = subprocess.run(cmd, capture_output=True, text=True)
    if result.returncode != 0:
        print(f"Compilation failed for {source}:")
        print(result.stderr)
        sys.exit(1)
    return "./" + executable

def run_generator(executable, seed, n_max, l_max, mode, output_file):
    """Run the generator to produce input file."""
    cmd = [executable, str(seed), str(n_max), str(l_max), str(mode)]
    with open(output_file, 'w') as f:
        result = subprocess.run(cmd, stdout=f, stderr=subprocess.PIPE, text=True)
    if result.returncode != 0:
        print(f"Generator failed for seed {seed}:")
        print(result.stderr)
        sys.exit(1)

def run_solution(executable, input_file, output_file):
    """Run the solution on input to produce output."""
    with open(input_file, 'r') as infile:
        with open(output_file, 'w') as outfile:
            result = subprocess.run([executable], stdin=infile, stdout=outfile, stderr=subprocess.PIPE, text=True)
    if result.returncode != 0:
        print(f"Solution failed for {input_file}:")
        print(result.stderr)
        sys.exit(1)

def main():
    # Change to the script's directory (Bookshelf)
    os.chdir(os.path.dirname(os.path.abspath(__file__)))

    # Compile generator and solution
    print("Compiling gen.cpp...")
    gen_exe = compile_cpp("gen.cpp", "gen.exe")
    print("Compiling solution.cpp...")
    sol_exe = compile_cpp("solution.cpp", "solution.exe")

    # Generate 50 test cases
    for test_num in range(1, 51):
        print(f"Generating test {test_num}...")

        # Determine parameters based on subtask
        if test_num <= 10:
            # Subtask 1: N <= 10
            n_max = 10
            l_max = 100
            mode = 0  # random
        elif test_num <= 25:
            # Subtask 2: N <= 2000
            n_max = 2000
            l_max = 1000000000
            mode = (test_num - 11) % 5  # 0,1,2,3,4
        else:
            # Subtask 3: N <= 100000
            n_max = 100000
            l_max = 1000000000
            if 26 <= test_num <= 40:
                # Killer cases: modes 6,7,8 cycling
                mode = 6 + ((test_num - 26) % 3)
            else:
                # Standard cases: modes 0-5 cycling
                mode = (test_num - 41) % 6

        # Seed: use test_num to vary
        seed = test_num * 123456789

        # File names
        infile = f"Bookshelf.{test_num}.in"
        outfile = f"Bookshelf.{test_num}.out"

        # Generate input
        run_generator(gen_exe, seed, n_max, l_max, mode, infile)

        # Produce output
        run_solution(sol_exe, infile, outfile)

        print(f"  Generated {infile} and {outfile}")

    # Create ZIP file of all .in and .out files
    print("Creating TESTS.zip...")
    with zipfile.ZipFile("TESTS.zip", "w", zipfile.ZIP_DEFLATED) as zipf:
        for test_num in range(1, 51):
            zipf.write(f"Bookshelf.{test_num}.in")
            zipf.write(f"Bookshelf.{test_num}.out")
    print("Created TESTS.zip")

    print("All tests generated successfully.")

if __name__ == "__main__":
    main()