#!/usr/bin/env python3
import os
import subprocess
import sys

def compile_cpp(source_file, executable_file):
    """Compile a C++ source file."""
    try:
        subprocess.run(['g++', '-std=c++17', '-O2', source_file, '-o', executable_file],
                      check=True, capture_output=True, text=True)
        print(f"Compiled {source_file} successfully")
        return True
    except subprocess.CalledProcessError as e:
        print(f"Failed to compile {source_file}:")
        print(e.stderr)
        return False

def run_generator(executable, seed, subtask_type, n, q, maxW, output_file):
    """Run the generator to produce an input file."""
    try:
        with open(output_file, 'w') as f:
            subprocess.run([executable, str(seed), str(subtask_type), str(n), str(q), str(maxW)],
                          stdout=f, check=True, text=True)
        return True
    except subprocess.CalledProcessError as e:
        print(f"Generator failed for seed {seed}:")
        return False

def run_solution(executable, input_file, output_file):
    """Run the solution on an input file to produce output."""
    try:
        with open(input_file, 'r') as infile, open(output_file, 'w') as outfile:
            subprocess.run([executable], stdin=infile, stdout=outfile,
                          check=True, text=True)
        return True
    except subprocess.CalledProcessError as e:
        print(f"Solution failed for {input_file}:")
        return False

def main():
    # Compile generator and solution
    if not compile_cpp('gen.cpp', 'gen'):
        return
    if not compile_cpp('solution.cpp', 'solution'):
        return

    # Define subtask parameters: (test_start, test_end, description, n_limit, q_limit, special_notes)
    subtasks = [
        (1, 5, "Small N,Q <= 5000", 5000, 5000, ""),
        (6, 13, "Path graph (max degree <= 2)", 200000, 200000, ""),
        (14, 22, "k=0 for all type 1 queries", 200000, 200000, ""),
        (23, 35, "Static tree (no type 2 queries)", 200000, 200000, ""),
        (36, 50, "Full constraints", 200000, 200000, "")
    ]

    # For each subtask, generate test cases
    test_num = 1
    for (start, end, desc, n_limit, q_limit, notes) in subtasks:
        print(f"\nGenerating Subtask {start}-{end}: {desc}")
        for t in range(start, end+1):
            # Use test number as seed for variety
            seed = t

            # Choose parameters based on subtask
            if t <= 5:  # Subtask 1: smaller sizes
                n = min(100 + t*50, n_limit)  # 150, 200, 250, 300, 350
                q = min(100 + t*50, q_limit)
            elif t <= 13:  # Subtask 2: path graphs
                n = min(1000 + (t-6)*2000, n_limit)  # Scale up
                q = min(1000 + (t-6)*2000, q_limit)
            elif t <= 22:  # Subtask 3: k=0
                n = min(5000 + (t-14)*3000, n_limit)
                q = min(5000 + (t-14)*3000, q_limit)
            elif t <= 35:  # Subtask 4: static
                n = min(10000 + (t-23)*5000, n_limit)
                q = min(10000 + (t-23)*5000, q_limit)
            else:  # Subtask 5: full
                n = min(50000 + (t-36)*10000, n_limit)
                q = min(50000 + (t-36)*10000, q_limit)

            # Ensure at least 1 node
            n = max(1, n)
            q = max(1, q)

            maxW = 1000000000  # 1e9 as per constraints

            input_file = f"BulgarianNOI24.{t}.in"
            output_file = f"BulgarianNOI24.{t}.out"

            print(f"  Generating test {t} (seed={seed}, n={n}, q={q})...", end=" ")

            # Generate input
            if not run_generator('./gen', seed,
                                1 if t<=5 else 2 if t<=13 else 3 if t<=22 else 4 if t<=35 else 5,
                                n, q, maxW, input_file):
                print("FAILED (generator)")
                continue

            # Run solution
            if not run_solution('./solution', input_file, output_file):
                print("FAILED (solution)")
                continue

            print("DONE")

    print("\nAll tests generated!")

if __name__ == "__main__":
    main()