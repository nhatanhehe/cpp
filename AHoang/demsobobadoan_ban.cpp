#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Struct để lưu giá trị tổng và số lượng đoạn có tổng đó
struct SumGroup {
    long long val;
    long long count;
};

// Hàm tính tổ hợp chập 2 của n: nC2 = n*(n-1)/2
long long nC2(long long n) {
    if (n < 2) return 0;
    return n * (n - 1) / 2;
}

// Hàm tính tổ hợp chập 3 của n: nC3 = n*(n-1)*(n-2)/6
long long nC3(long long n) {
    if (n < 3) return 0;
    return n * (n - 1) * (n - 2) / 6;
}

int main() {
    // Tối ưu nhập xuất
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    // 1. Tính tổng tiền tố
    vector<long long> P(n + 1, 0);
    for (int i = 0; i < n; i++) {
        P[i + 1] = P[i] + a[i];
    }

    // 2. Sinh tất cả các tổng đoạn con
    vector<long long> all_sums;
    // Dự trữ bộ nhớ để tránh reallocate nhiều lần
    all_sums.reserve(n * (n + 1) / 2);

    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            all_sums.push_back(P[j] - P[i - 1]);
        }
    }

    // 3. Sắp xếp để gom nhóm
    sort(all_sums.begin(), all_sums.end());

    // 4. Nén mảng thành các cặp (giá trị, số lượng)
    vector<SumGroup> groups;
    if (!all_sums.empty()) {
        long long current_val = all_sums[0];
        long long current_count = 1;
        for (size_t i = 1; i < all_sums.size(); i++) {
            if (all_sums[i] == current_val) {
                current_count++;
            } else {
                groups.push_back({current_val, current_count});
                current_val = all_sums[i];
                current_count = 1;
            }
        }
        groups.push_back({current_val, current_count});
    }

    // 5. Giải bài toán 3SUM đếm số lượng
    long long ans = 0;
    int m = groups.size();

    for (int i = 0; i < m; i++) {
        // Nếu giá trị hiện tại * 3 > 0 thì không thể tìm ra bộ 3 có tổng = 0 phía sau (do mảng đã sort tăng dần)
        if (groups[i].val * 3 > 0) break;

        int l = i;          // Bắt đầu từ i để cho phép chọn nhiều đoạn có cùng giá trị tổng
        int r = m - 1;

        while (l <= r) {
            long long sum = groups[i].val + groups[l].val + groups[r].val;

            if (sum < 0) {
                l++;
            } else if (sum > 0) {
                r--;
            } else {
                // Tìm thấy bộ ba có tổng = 0
                long long c1 = groups[i].count;
                long long c2 = groups[l].count;
                long long c3 = groups[r].count;

                if (i == l && l == r) {
                    // Trường hợp 3 giá trị giống nhau (ví dụ: 0, 0, 0)
                    // Chọn 3 đoạn phân biệt từ tập các đoạn có tổng bằng 0
                    ans += nC3(c1);
                } else if (i == l) {
                    // Trường hợp 2 giá trị đầu giống nhau (vd: -2, -2, 4)
                    // Chọn 2 đoạn từ nhóm i và 1 đoạn từ nhóm r
                    ans += nC2(c1) * c3;
                } else if (l == r) {
                    // Trường hợp 2 giá trị sau giống nhau (vd: -4, 2, 2)
                    ans += c1 * nC2(c2);
                } else {
                    // Trường hợp 3 giá trị khác nhau hoàn toàn
                    ans += c1 * c2 * c3;
                }

                l++;
                r--;
            }
        }
    }

    cout << ans << endl;

    return 0;
}
