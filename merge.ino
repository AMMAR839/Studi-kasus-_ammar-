#include <iostream>
#include <cstdlib>  // Untuk fungsi rand()
#include <ctime>    // Untuk fungsi time()
#include <vector>   // Untuk penggunaan std::vector

using namespace std;

// Fungsi untuk menggabungkan dua subarray
void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    // Menggunakan vector untuk dynamic array
    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int i = 0; i < n2; i++)
        R[i] = arr[m + 1 + i];

    int i = 0, j = 0, k = l;

    while (i < n1 && j < n2) {
        // Untuk sorting dari terbesar ke terkecil, ubah kondisi di sini
        if (L[i] >= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Fungsi merge sort
void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

int main() {
    srand(time(0));  // Seed untuk random number generator

    int arr[10];

    // Mengisi array dengan angka random
    for (int i = 0; i < 10; i++) {
        arr[i] = rand() % 100;  // Angka random dari 0 sampai 99
    }

    // Menampilkan array sebelum disorting
    cout << "Array sebelum disort:" << endl;
    for (int i = 0; i < 10; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    // Sorting array menggunakan merge sort
    mergeSort(arr, 0, 9);

    // Menampilkan array setelah disorting dari terbesar ke terkecil
    cout << "Array setelah disort dari terbesar ke terkecil:" << endl;
    for (int i = 0; i < 10; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}
