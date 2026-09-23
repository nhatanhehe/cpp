#!/usr/bin/env python3
import os
import subprocess
import sys
import random

def compile_prog(src, out):
    """Compile C++ source to executable."""
    cmd = ['g++', '-std=c++17', '-O2', '-pipe', '-o', out, src]
    print('Compiling {} -> {}'.format(src, out))
    result = subprocess.run(cmd, capture_output=True, text=True)
    if result.returncode != 0:
        print('Compilation failed:')
        print(result.stderr)
        sys.exit(1)
    else:
        print('Compilation successful.')

def generate_input_biased(seed, n_max, k_max, outfile):
    """Run generator to produce input file with bias towards high lexicographic order."""
    cmd = ['./gen_biased', str(seed), str(n_max), str(k_max)]
    with open(outfile, 'w') as f:
        result = subprocess.run(cmd, stdout=f, stderr=subprocess.PIPE, text=True)
    if result.returncode != 0:
        print('Generator failed for seed {}: {}'.format(seed, result.stderr))
        sys.exit(1)

def generate_input_standard(seed, n_max, k_max, outfile):
    """Run generator to produce input file (standard)."""
    cmd = ['./gen', str(seed), str(n_max), str(k_max)]
    with open(outfile, 'w') as f:
        result = subprocess.run(cmd, stdout=f, stderr=subprocess.PIPE, text=True)
    if result.returncode != 0:
        print('Generator failed for seed {}: {}'.format(seed, result.stderr))
        sys.exit(1)

def run_solution(infile, outfile):
    """Run compiled solution on input file."""
    cmd = ['./solution']
    with open(infile, 'r') as fin, open(outfile, 'w') as fout:
        result = subprocess.run(cmd, stdin=fin, stdout=fout, stderr=subprocess.PIPE, text=True)
    if result.returncode != 0:
        print('Solution failed on {}: {}'.format(infile, result.stderr))
        # don't exit, just note
    # else success

def main():
    # Compile generator and solution
    compile_prog('gen.cpp', 'gen')
    compile_prog('gen_biased.cpp', 'gen_biased')
    compile_prog('solution.cpp', 'solution')

    # Generate inputs for each test case
    print('Generating input files...')
    for tc in range(1, 51):
        if tc <= 5:
            n_max, k_max = 10, 10
            generate_input_standard(tc, n_max, k_max, f'ADBRACK.{tc}.in')
        elif tc <= 15:
            n_max, k_max = 20, 5
            generate_input_standard(tc, n_max, k_max, f'ADBRACK.{tc}.in')
        elif tc <= 30:
            n_max, k_max = 100, 5
            generate_input_standard(tc, n_max, k_max, f'ADBRACK.{tc}.in')
        else:
            # For final subtask (31-50): use larger n and k, and biased generation
            # Pick n from higher range (80-100, even)
            # Pick k from higher range but ensure 2*k <= n
            possible_n = list(range(80, 101, 2))  # 80, 82, ..., 100
            n = random.choice(possible_n)
            max_k = n // 2
            possible_k = list(range(max(1, max_k - 10), max_k + 1))  # k near max_k
            k = random.choice(possible_k)

            generate_input_biased(tc, n, k, f'ADBRACK.{tc}.in')
            print(f'Generated ADBRACK.{tc}.in (n={n}, k={k}) [biased]')
            continue

        # For non-final subtasks, print standard info
        if tc <= 5:
            print(f'Generated ADBRACK.{tc}.in (n_max=10, k_max=10)')
        elif tc <= 15:
            print(f'Generated ADBRACK.{tc}.in (n_max=20, k_max=5)')
        elif tc <= 30:
            print(f'Generated ADBRACK.{tc}.in (n_max=100, k_max=5)')

    print('\nAll input files generated.')
    print('Please now replace solution.cpp with your actual solution.')
    answer = input('After you have done that, type "y" to continue to generate output files: ').strip().lower()
    if answer != 'y':
        print('User did not confirm; stopping before generating outputs.')
        return

    # Ensure solution is compiled (maybe user changed it)
    print('Re-compiling solution...')
    compile_prog('solution.cpp', 'solution')

    print('Generating output files...')
    for tc in range(1, 51):
        infile = f'ADBRACK.{tc}.in'
        outfile = f'ADBRACK.{tc}.out'
        run_solution(infile, outfile)
        print(f'Generated {outfile}')

    print('Done.')

if __name__ == '__main__':
    main()