import sys

def verify_file(filename):
    with open(filename, 'r') as f:
        lines = f.readlines()
    i = 0
    case_num = 0
    while i < len(lines):
        if not lines[i].strip():
            i += 1
            continue
        parts = lines[i].split()
        if len(parts) != 2:
            print(f"Unexpected line: {lines[i]}")
            return False
        n = int(parts[0])
        L = int(parts[1])
        i += 1
        for j in range(n):
            if i >= len(lines):
                print(f"Unexpected EOF in case {case_num}")
                return False
            parts = lines[i].split()
            if len(parts) != 2:
                print(f"Unexpected book line: {lines[i]}")
                return False
            H = int(parts[0])
            W = int(parts[1])
            if W < 1 or W > L:
                print(f"FAIL: file {filename}, case {case_num}, book {j}: W={W}, L={L}")
                return False
            i += 1
        case_num += 1
    print(f"OK: {filename} ({case_num} cases)")
    return True

if __name__ == '__main__':
    import os
    all_ok = True
    for idx in range(1, 51):
        fname = f"{idx}.in"
        if not os.path.exists(fname):
            print(f"Missing {fname}")
            all_ok = False
            continue
        if not verify_file(fname):
            all_ok = False
    if all_ok:
        print("All files are valid.")
    else:
        print("Some files invalid.")
        sys.exit(1)