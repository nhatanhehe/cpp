import random
import subprocess
import os
import sys

def gen_matrix(subtask):
    """Generate 3x3 matrix (1-indexed indices 1..3)"""
    if subtask == 2:
        return [[1]*4 for _ in range(4)]  # we'll ignore index 0
    else:
        # random 0/1
        m = [[0]*4 for _ in range(4)]
        for i in range(1,4):
            for j in range(1,4):
                m[i][j] = random.randint(0,1)
        return m

def gen_sequence(n):
    return [random.randint(0,3) for _ in range(n)]

def gen_query(n, subtask):
    l = random.randint(1, n)
    r = random.randint(l, n)
    x = random.randint(0,3)
    y = random.randint(x,3)  # ensure x <= y
    if subtask == 3:
        # l=r
        l = r = random.randint(1, n)
    if subtask == 4:
        y = 0
        # ensure x <= y => x must be 0 as well because y=0 and x<=y => x=0
        x = 0
    return l, r, x, y

def write_test(fn, n, q, mat, seq, queries):
    with open(fn, 'w') as f:
        f.write(f"{n} {q}\n")
        for i in range(1,4):
            f.write(f"{mat[i][1]} {mat[i][2]} {mat[i][3]}\n")
        f.write(' '.join(map(str, seq)) + '\n')
        for l,r,x,y in queries:
            f.write(f"{l} {r} {x} {y}\n")

def run_solution(input_path):
    result = subprocess.run([r'./solution'], stdin=open(input_path, 'r'), capture_output=True, text=True)
    if result.returncode != 0:
        print(f"Error running solution on {input_path}: {result.stderr}")
        return None
    return result.stdout.strip()

def main():
    random.seed(12345)  # for reproducibility
    # We are already in friendly directory
    tests = []
    for subtask in range(1,6):
        for t in range(10):
            test_num = (subtask-1)*10 + t + 1
            # determine n,q bounds
            if subtask == 1:
                n = random.randint(1, 3000)
                q = random.randint(1, 3000)
            elif subtask == 5:
                n = random.randint(1, 100000)
                q = random.randint(1, 100000)
                # but to avoid huge generation, we cap at 2000 for speed
                if n > 2000:
                    n = 2000
                if q > 2000:
                    q = 2000
            else:
                # subtask 2,3,4: we can set n,q up to 2000 as well
                n = random.randint(1, 2000)
                q = random.randint(1, 2000)
            mat = gen_matrix(subtask)
            seq = gen_sequence(n)
            queries = [gen_query(n, subtask) for _ in range(q)]
            in_fn = f'test{test_num}.in'
            out_fn = f'test{test_num}.out'
            write_test(in_fn, n, q, mat, seq, queries)
            out = run_solution(in_fn)
            if out is None:
                print(f"Failed to generate output for {in_fn}")
                return
            with open(out_fn, 'w') as f:
                f.write(out)
            tests.append((in_fn, out_fn))
            print(f'Generated {in_fn} and {out_fn}')
    # Create init.yml
    init_content = "archive: test.zip\ntest_cases:\n"
    for subtask in range(1,6):
        init_content += "  - batched:\n"
        for t in range(10):
            test_num = (subtask-1)*10 + t + 1
            init_content += f"    - {{in: test{test_num}.in, out: test{test_num}.out}}\n"
        init_content += "    points: 20\n"
    with open('init.yml', 'w') as f:
        f.write(init_content)
    # Package
    subprocess.run(['powershell', '-command', f'Compress-Archive -Path test*.in, test*.out, init.yml -DestinationPath test.zip'])
    # Cleanup
    for subtask in range(1,6):
        for t in range(10):
            test_num = (subtask-1)*10 + t + 1
            if os.path.exists(f'test{test_num}.in'):
                os.remove(f'test{test_num}.in')
            if os.path.exists(f'test{test_num}.out'):
                os.remove(f'test{test_num}.out')
    if os.path.exists('init.yml'):
        os.remove('init.yml')
    print('Test generation complete. test.zip created.')

if __name__ == '__main__':
    main()