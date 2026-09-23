#include <bits/stdc++.h>
using namespace std;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

long long rand_long(long long l, long long r) {
    uniform_int_distribution<long long> dist(l, r);
    return dist(rng);
}

int rand_int(int l, int r) {
    uniform_int_distribution<int> dist(l, r);
    return dist(rng);
}

void generate_subtask1(ofstream& fout, int test_case_id) {
    int T = rand_int(5, 7); // number of test cases in this file
    for (int t = 0; t < T; t++) {
        int n = rand_int(1, 10);
        int L = rand_int(1, 100); // L can be small since N is small
        fout << n << " " << L << "\n";
        for (int i = 0; i < n; i++) {
            int H = rand_int(1, 100);
            int W = rand_int(1, L);
            fout << H << " " << W << "\n";
        }
    }
}

void generate_subtask2(ofstream& fout, int test_case_id) {
    int T = rand_int(5, 7);
    for (int t = 0; t < T; t++) {
        int n = rand_int(1, 2000);
        int L = rand_int(1, 1000000);
        fout << n << " " << L << "\n";
        for (int i = 0; i < n; i++) {
            int H = rand_int(1, 1000000000);
            int W = rand_int(1, L);
            fout << H << " " << W << "\n";
        }
    }
}

void generate_subtask3(ofstream& fout, int test_case_id) {
    int T = rand_int(5, 7); // total test cases in file
    int K = rand_int(1, 2); // number of killer cases: 1 or 2
    vector<bool> is_killer(T, false);
    // choose K distinct positions for killer cases
    vector<int> positions(T);
    iota(positions.begin(), positions.end(), 0);
    shuffle(positions.begin(), positions.end(), rng);
    for (int i = 0; i < K; i++) {
        is_killer[positions[i]] = true;
    }

    long long total_N = 0;
    for (int t = 0; t < T; t++) {
        if (is_killer[t]) {
            int n = 100000;
            int L = 1000000000;
            fout << n << " " << L << "\n";
            for (int i = 0; i < n; i++) {
                int H = rand_int(1, 1000000000);
                int W = rand_int(1, 5); // width in [1,5]
                fout << H << " " << W << "\n";
            }
            total_N += n;
        } else {
            // normal case
            int max_normal_n = 50000;
            int min_normal_n = 20000;
            // remaining budget: 300000 - total_N
            long long remaining = 300000 - total_N;
            int normal_left = T - t - 1; // including current
            // we need to assign n for this normal case such that even if we assign min_normal_n to the rest, we don't exceed remaining
            int min_possible = min_normal_n * normal_left;
            int max_possible = remaining - min_possible;
            if (max_possible < min_normal_n) {
                // fallback: assign min_normal_n and hope the rest can be adjusted (should not happen with our constraints)
                int n = min_normal_n;
                int L = rand_int(1, 1000000000);
                fout << n << " " << L << "\n";
                for (int i = 0; i < n; i++) {
                    int H = rand_int(1, 1000000000);
                    int W = rand_int(1, L);
                    fout << H << " " << W << "\n";
                }
                total_N += n;
            } else {
                int n = rand_int(min_normal_n, min(max_normal_n, max_possible));
                int L = rand_int(1, 1000000000);
                fout << n << " " << L << "\n";
                for (int i = 0; i < n; i++) {
                    int H = rand_int(1, 1000000000);
                    int W = rand_int(1, L);
                    fout << H << " " << W << "\n";
                }
                total_N += n;
            }
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cerr << "Usage: " << argv[0] << " <subtask> <test_case_number> [seed]\n";
        return 1;
    }
    int subtask = stoi(argv[1]);
    int test_case_number = stoi(argv[2]);
    if (argc >= 4) {
        uint64_t seed = stoull(argv[3]);
        rng.seed(seed);
    }

    string filename = to_string(test_case_number) + ".in";
    ofstream fout(filename);
    if (!fout) {
        cerr << "Cannot open file " << filename << "\n";
        return 1;
    }

    if (subtask == 1) {
        generate_subtask1(fout, test_case_number);
    } else if (subtask == 2) {
        generate_subtask2(fout, test_case_number);
    } else if (subtask == 3) {
        generate_subtask3(fout, test_case_number);
    } else {
        cerr << "Invalid subtask: " << subtask << "\n";
        return 1;
    }

    fout.close();
    return 0;
}