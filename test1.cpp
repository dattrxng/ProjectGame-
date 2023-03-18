#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    int A[n];
    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }
    sort(A, A+n);
    int left = 0, right = n-1;
    while (left < right) {
        if (A[left] + A[right] >= k) {
            cout << A[left] << " " << A[right] << endl;
            right--;
        } else {
            left++;
        }
    }
    return 0;
}
