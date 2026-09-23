import random
import sys

MOD = 1_000_000_007

def randint(l, r):
    return random.randint(l, r)

def gen_small():
    n = randint(1, 10)
    t = randint(1, 100)
    a = [randint(1, 20) for _ in range(n)]
    nodes = list(range(1, n+1))
    random.shuffle(nodes)
    used_b = set()
    used_c = set()
    edges = []
    for i in range(min(len(nodes)//2, n)):
        if len(nodes) < 2:
            break
        b = nodes.pop()
        c = nodes.pop()
        if b in used_b or c in used_c:
            # put back? just skip
            continue
        used_b.add(b)
        used_c.add(c)
        edges.append((b, c))
    q = len(edges)
    return n, q, t, a, edges

def gen_q0():
    n = randint(1, 50)
    t = randint(1, 1000)
    a = [randint(1, 100) for _ in range(n)]
    return n, 0, t, a, []

def gen_max_bounds():
    n = 300
    t = 100000
    a = [randint(1, 1000) for _ in range(n)]
    nodes = list(range(1, n+1))
    random.shuffle(nodes)
    used_b = set()
    used_c = set()
    edges = []
    i = 0
    while i + 1 < len(nodes):
        b = nodes[i]
        c = nodes[i+1]
        if b not in used_b and c not in used_c:
            edges.append((b, c))
            used_b.add(b)
            used_c.add(c)
            i += 2
        else:
            i += 1
    q = len(edges)
    return n, q, t, a, edges

def gen_edge():
    typ = randint(1, 5)
    if typ == 1:
        # cycle
        n = randint(2, 8)
        a = [randint(1, 20) for _ in range(n)]
        edges = []
        for i in range(n):
            b = i+1
            c = (i+1) % n + 1
            edges.append((b, c))
        q = n
        t = randint(1, 1000)
        return n, q, t, a, edges
    elif typ == 2:
        # chain where required minimum exceeds t
        n = randint(2, 10)
        a = [randint(5, 20) for _ in range(n)]
        edges = [(i+1, i+2) for i in range(n-1)]
        q = n-1
        min_sum = sum(a[b-1] for b, _ in edges)
        t = randint(1, min_sum-1) if min_sum > 1 else 1
        return n, q, t, a, edges
    elif typ == 3:
        n = randint(1, 20)
        t = randint(1, 100)
        a = [randint(1, 10) for _ in range(n)]
        return n, 0, t, a, []
    elif typ == 4:
        n = randint(200, 300)
        t = randint(1, 10)
        a = [randint(1, 5) for _ in range(n)]
        return n, 0, t, a, []
    else:
        n = randint(1, 15)
        a = [randint(1, 20) for _ in range(n)]
        nodes = list(range(1, n+1))
        random.shuffle(nodes)
        used_b = set()
        used_c = set()
        edges = []
        i = 0
        while i+1 < len(nodes):
            b = nodes[i]
            c = nodes[i+1]
            if b not in used_b and c not in used_c:
                edges.append((b, c))
                used_b.add(b)
                used_c.add(c)
                i += 2
            else:
                i += 1
        q = len(edges)
        t = randint(1, 200)
        return n, q, t, a, edges

def write_test(test_id, n, q, t, a, edges):
    filename = f'coin_troubles_tests/{test_id}.in'
    with open(filename, 'w') as f:
        f.write(f'{n} {q} {t}\n')
        f.write(' '.join(map(str, a)) + '\n')
        for b, c in edges:
            f.write(f'{b} {c}\n')

def main():
    random.seed(12345)
    test_id = 1
    for _ in range(10):
        n, q, t, a, edges = gen_small()
        write_test(test_id, n, q, t, a, edges)
        test_id += 1
    for _ in range(8):
        n, q, t, a, edges = gen_q0()
        write_test(test_id, n, q, t, a, edges)
        test_id += 1
    for _ in range(10):
        n, q, t, a, edges = gen_max_bounds()
        write_test(test_id, n, q, t, a, edges)
        test_id += 1
    for _ in range(8):
        n, q, t, a, edges = gen_edge()
        write_test(test_id, n, q, t, a, edges)
        test_id += 1
    print(f'Generated {test_id-1} test files')

if __name__ == '__main__':
    main()