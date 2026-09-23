import random
import sys

# Precompute sieve for primes up to 10^7 for subtask 6
def sieve_prime(limit):
    is_prime = [True] * (limit + 1)
    is_prime[0] = is_prime[1] = False
    for i in range(2, int(limit**0.5) + 1):
        if is_prime[i]:
            for j in range(i*i, limit+1, i):
                is_prime[j] = False
    primes = [i for i, prime in enumerate(is_prime) if prime]
    return is_prime, primes

# We'll generate primes up to 10^7
LIMIT = 10**7
is_prime, primes_list = sieve_prime(LIMIT)

def generate_subtask1(test_num):
    max_n = 50
    max_q = 50
    max_a = 100
    n = random.randint(1, max_n)
    q = random.randint(1, max_q)
    a = [random.randint(1, max_a) for _ in range(n)]
    queries = []
    for _ in range(q):
        l = random.randint(1, n)
        r = random.randint(l, n)
        queries.append((l, r))
    return n, q, a, queries

def generate_subtask2(test_num):
    max_n = 2000
    max_q = 2000
    max_a = 500
    n = random.randint(1, max_n)
    q = random.randint(1, max_q)
    a = [random.randint(1, max_a) for _ in range(n)]
    queries = []
    for _ in range(q):
        l = random.randint(1, n)
        r = random.randint(l, n)
        queries.append((l, r))
    return n, q, a, queries

def generate_subtask3(test_num):
    max_n = 200000
    max_q = 200000
    max_a = 3
    n = random.randint(1, max_n)
    q = random.randint(1, max_q)
    a = [random.randint(1, max_a) for _ in range(n)]
    queries = []
    for _ in range(q):
        l = random.randint(1, n)
        r = random.randint(l, n)
        queries.append((l, r))
    return n, q, a, queries

def generate_subtask4(test_num):
    max_n = 200000
    max_q = 200000
    max_a = 10**5
    n = random.randint(1, max_n)
    q = random.randint(1, max_q)
    a = [random.randint(1, max_a) for _ in range(n)]
    queries = []
    for _ in range(q):
        l = random.randint(1, n)
        r = l  # l = r
        queries.append((l, r))
    return n, q, a, queries

def generate_subtask5(test_num):
    max_n = 200000
    max_q = 200000
    max_a = 10**7
    n = random.randint(1, max_n)
    q = random.randint(1, max_q)
    a = [random.randint(1, max_a) for _ in range(n)]
    queries = []
    for _ in range(q):
        l = random.randint(1, n)
        r = l  # l = r
        queries.append((l, r))
    return n, q, a, queries

def generate_subtask6(test_num):
    max_n = 200000
    max_q = 200000
    max_a = 10**7
    n = random.randint(1, max_n)
    q = random.randint(1, max_q)
    # Generate array of primes: we'll sample from primes_list
    # But note: primes_list contains primes up to 10^7, which is exactly our max_a.
    a = [random.choice(primes_list) for _ in range(n)]
    queries = []
    for _ in range(q):
        l = random.randint(1, n)
        r = random.randint(l, n)
        queries.append((l, r))
    return n, q, a, queries

def generate_subtask7(test_num):
    max_n = 20000
    max_q = 20000
    max_a = 10**7
    n = random.randint(1, max_n)
    q = random.randint(1, max_q)
    a = [random.randint(1, max_a) for _ in range(n)]
    queries = []
    for _ in range(q):
        l = random.randint(1, n)
        r = random.randint(l, n)
        queries.append((l, r))
    return n, q, a, queries

def generate_subtask8(test_num):
    max_n = 10**5
    max_q = 20000
    max_a = 10**7
    n = random.randint(1, max_n)
    q = random.randint(1, max_q)
    a = [random.randint(1, max_a) for _ in range(n)]
    queries = []
    for _ in range(q):
        l = random.randint(1, n)
        r = random.randint(l, n)
        queries.append((l, r))
    return n, q, a, queries

def generate_subtask9(test_num):
    max_n = 80000
    max_q = 80000
    max_a = 10**7
    n = random.randint(1, max_n)
    q = random.randint(1, max_q)
    a = [random.randint(1, max_a) for _ in range(n)]
    queries = []
    for _ in range(q):
        l = random.randint(1, n)
        r = random.randint(l, n)
        queries.append((l, r))
    return n, q, a, queries

def generate_subtask10(test_num):
    max_n = 200000
    max_q = 200000
    max_a = 10**7
    n = random.randint(1, max_n)
    q = random.randint(1, max_q)
    a = [random.randint(1, max_a) for _ in range(n)]
    queries = []
    for _ in range(q):
        l = random.randint(1, n)
        r = random.randint(l, n)
        queries.append((l, r))
    return n, q, a, queries

# Mapping from subtask id to generator function
generators = {
    1: generate_subtask1,
    2: generate_subtask2,
    3: generate_subtask3,
    4: generate_subtask4,
    5: generate_subtask5,
    6: generate_subtask6,
    7: generate_subtask7,
    8: generate_subtask8,
    9: generate_subtask9,
    10: generate_subtask10
}

def main():
    random.seed(42)  # for reproducibility
    for subtask in range(1, 11):
        for test_num in range(1, 11):
            n, q, a, queries = generators[subtask](test_num)
            filename = f"subtask{subtask}.{test_num:02d}.in"
            with open(filename, 'w') as f:
                f.write(f"{n} {q}\n")
                f.write(" ".join(map(str, a)) + "\n")
                for l, r in queries:
                    f.write(f"{l} {r}\n")
            print(f"Generated {filename}")

if __name__ == "__main__":
    main()