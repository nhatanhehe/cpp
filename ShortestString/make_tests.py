import os
import sys
import subprocess

def compile_programs():
    # Compile generator
    subprocess.run(["g++", "-std=c++11", "-O2", "gen.cpp", "-o", "gen.exe"], check=True)
    # Compile solution
    subprocess.run(["g++", "-std=c++11", "-O2", "solution.cpp", "-o", "solution.exe"], check=True)

def generate_test(seed, n, max_len, test_id):
    input_file = f"ShortestString.{test_id}.in"
    output_file = f"ShortestString.{test_id}.out"

    # Run generator with seed, n, max_len (no mode needed)
    with open(input_file, "w") as f:
        subprocess.run(["./gen.exe", str(seed), str(n), str(max_len)], stdout=f, check=True)

    # Run solution
    with open(input_file, "r") as infile, open(output_file, "w") as outfile:
        subprocess.run(["./solution.exe"], stdin=infile, stdout=outfile, check=True)

def main():
    # Number of test cases
    num_tests = 50

    compile_programs()

    for i in range(1, num_tests+1):
        # Use test index as seed
        seed = i
        # n cycles from 1 to 50
        n = (i % 50) + 1
        # max_len: for each block of 5 tests, increase max_len from 1 to 10
        max_len = ((i-1) // 5) % 10 + 1
        print(f"Generating test {i}: seed={seed}, n={n}, max_len={max_len}")
        generate_test(seed, n, max_len, i)

    print("Done generating tests.")

if __name__ == "__main__":
    main()