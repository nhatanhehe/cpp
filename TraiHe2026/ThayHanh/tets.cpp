#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define fast ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

const int N = 1e6 + 5;

int n, q, theta;
ll w[N];
ll dpl[N], dpr[N];
ll pref_min[N], pref_max[N];
ll suff_min[N], suff_max[N];
ll st_max[N][20], st_min[N][20];

// Xây dựng Sparse Table để lấy max, min đoạn [l, r] trong O(1)
void build_ST() {
    for (int i = 1; i <= n; i++) {
        st_max[i][0] = w[i];
        st_min[i][0] = w[i];
    }
    for (int j = 1; (1 << j) <= n; j++) {
        for (int i = 1; i + (1 << j) - 1 <= n; i++) {
            st_max[i][j] = max(st_max[i][j-1], st_max[i + (1 << (j-1))][j-1]);
            st_min[i][j] = min(st_min[i][j-1], st_min[i + (1 << (j-1))][j-1]);
        }
    }
}

// Hàm RMQ lấy max, min đoạn trong O(1) dùng __builtin_clz chuẩn
pair<ll, ll> get_rmq(int l, int r) {
    int k = 31 - __builtin_clz(r - l + 1);
    ll mx = max(st_max[l][k], st_max[r - (1 << k) + 1][k]);
    ll mn = min(st_min[l][k], st_min[r - (1 << k) + 1][k]);
    return {mx, mn};
}

int main() {
    fast;

    // Đọc dữ liệu đầu vào
    cin >> theta >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> w[i];
    }

    // 1. Tiền xử lý Quy hoạch động xuôi (từ 1 đến n)
    ll val_min = -w[1], val_max = w[1];
    pref_min[1] = val_min;
    pref_max[1] = val_max;
    dpl[1] = 0;

    for (int i = 2; i <= n; i++) {
        dpl[i] = max(val_min + w[i], val_max - w[i]);
        dpl[i] = max(dpl[i], dpl[i-1]);
        val_min = max(val_min, dpl[i-1] - w[i]);
        val_max = max(val_max, dpl[i-1] + w[i]);
        pref_min[i] = val_min;
        pref_max[i] = val_max;
    }

    // 2. Tiền xử lý Quy hoạch động ngược (từ n về 1)
    ll rev_min = -w[n], rev_max = w[n];
    suff_min[n] = rev_min;
    suff_max[n] = rev_max;
    dpr[n] = 0;

    for (int i = n - 1; i >= 1; i--) {
        dpr[i] = max(rev_min + w[i], rev_max - w[i]);
        dpr[i] = max(dpr[i], dpr[i+1]);
        rev_min = max(rev_min, dpr[i+1] - w[i]);
        rev_max = max(rev_max, dpr[i+1] + w[i]);
        suff_min[i] = rev_min;
        suff_max[i] = rev_max;
    }

    // 3. Xây dựng Sparse Table phục vụ RMQ
    build_ST();

    // In ra kết quả của bài toán gốc (không có ràng buộc)
    cout << dpl[n];

    // 4. Xử lý q truy vấn dạng L trong O(1)
    while (q--) {
        char type;
        int x, y;
        cin >> type >> x >> y;

        if (type == 'L') {
            if (x > y) swap(x, y);

            // Lấy max, min của đoạn bắt buộc [x, y]
            auto [seg_max, seg_min] = get_rmq(x, y);

            // Tích lũy tối ưu từ biên trái đi xuyên qua [x, y] sang biên phải
            ll Left_Min = max(pref_min[x], -seg_min);
            ll Left_Max = max(pref_max[x], seg_max);

            // Kết hợp O(1) với các mảng hậu tố ngược từ bên phải đổ về y
            ll ans1 = Left_Min + suff_max[y];
            ll ans2 = Left_Max + suff_min[y];

            cout << " " << max(ans1, ans2);
        }
        else if (type == 'H') {
            // Phần xử lý cho tình huống H (hai bạn ở 2 nhóm khác nhau)
            // Bạn có thể chèn code Sparse Table tìm điểm cắt lớn nhất đã sửa lỗi CLZ vào đây
        }
    }
    cout << "\n";

    return 0;
}
