//1) АиСД-2, 2023, задание 5
//2) Галкина Таисия Олеговна БПИ213
//3) Clion
//4) в коде все
//5) в отчете не все, я не успела построить так много графиков  я не гений экселя, мне грустно ахахаха
// хорошего дня!!!

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <chrono>
#include <fstream>

typedef long long ll;

std::ofstream inp, outp;

//для ввода
void inputt(std::vector<int> &mas) {
    inp.open("input.txt");
    for (int i = 0; i < mas.size(); i++) {
        inp << mas[i] << ' ';
    }
    inp.close();
}

// для вывода
void outputt(std::vector<int> &mas) {
    outp.open("output.txt");
    for (int i = 0; i < mas.size(); i++) {
        outp << mas[i] << ' ';
    }
    outp.close();
}

ll selectSort(std::vector<int> &mas) {
    auto start = std::chrono::high_resolution_clock::now();
    int min = 0;
    for (int i = 0; i < mas.size() - 1; i++) {
        min = i;
        // тут мы находим минимальный из той части мссива, что мы еще не обработали
        for (int j = i + 1; j < mas.size(); j++) {
            if (mas[j] < mas[min]) {
                min = j;
            }
        }
        // если нашли, то свопнули относительного смотрящего элемента
        if (i != min) {
            std::swap(mas[i], mas[min]);
        }
    }
    auto end = std::chrono::high_resolution_clock::now() - start;
    return std::chrono::duration_cast<std::chrono::nanoseconds>(end).count();
}

ll bubbleSort(std::vector<int> &mas) {
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < mas.size() - 1; i++) {
        for (int j = 0; j < mas.size() - 1 - i; j++) {
            // как только находим пару, что не удовлетворяет условию, то свопаем их, чтобы все было классно
            // => все отсортировано будет в итоге
            if (mas[j] > mas[j + 1]) {
                std::swap(mas[j], mas[j + 1]);
            }
        }
    }
    auto end = std::chrono::high_resolution_clock::now() - start;
    return std::chrono::duration_cast<std::chrono::nanoseconds>(end).count();
}

ll bubbleSortA1(std::vector<int> &mas) {
    auto start = std::chrono::high_resolution_clock::now();
    int i = 0;
    bool fl = true;
    // тут модификация в том, что как только мы прошли и нет ни одной "плохой" пары
    // => все отсортировано и нет смысла ходить просто так по массиву
    while (fl) {
        fl = false;
        for (int j = 0; j < mas.size() - i - 1; j++) {
            if (mas[j] > mas[j + 1]) {
                std::swap(mas[j], mas[j + 1]);
                fl = true;
            }
        }
        i++;
    }
    auto end = std::chrono::high_resolution_clock::now() - start;
    return std::chrono::duration_cast<std::chrono::nanoseconds>(end).count();
}

ll bubbleSortA2(std::vector<int> &mas) {
    auto start = std::chrono::high_resolution_clock::now();
    bool fl = true;
    int t = mas.size() - 1;
    int k = mas.size() - 1;
    // тут запоминаем верхную границу, когда мы сделали своп на прошлм шаге внещней итерации
    // t == 0 => нет обменов => конец
    while (t != 0) {
        t = 0;
        for (int i = 0; i < k; ++i) {
            fl = false;
            for (int j = 0; j < mas.size() - i - 1; ++j) {
                if (mas[j] > mas[j + 1]) {
                    std::swap(mas[j], mas[j + 1]);
                    fl = true;
                    t = j;
                }
            }
            if (!fl) {
                break;
            }
        }
        if (!fl) {
            break;
        }
        k = t;
    }
    auto end = std::chrono::high_resolution_clock::now() - start;
    return std::chrono::duration_cast<std::chrono::nanoseconds>(end).count();
}

ll insertSort(std::vector<int> &mas) {
    auto start = std::chrono::high_resolution_clock::now();
    int key, temp;
    for (int i = 0; i < mas.size() - 1; i++) {
        key = i + 1;
        temp = mas[key];
        for (int j = i + 1; j > 0; j--) {
            if (temp < mas[j - 1]) {
                mas[j] = mas[j - 1];
                key = j - 1;
            }
        }
        mas[key] = temp;
    }
    auto end = std::chrono::high_resolution_clock::now() - start;
    return std::chrono::duration_cast<std::chrono::nanoseconds>(end).count();
}

ll binInsertSort(std::vector<int> &mas) {
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 1; i < mas.size(); i++) {
        if (mas[i - 1] > mas[i]) {
            int m = mas[i];
            int l = 0;
            int r = i - 1;
            while (r - l >= 0) {
                int mid = l + (r - l) / 2;
                if (mas[mid] < m) {
                    l = mid + 1;
                } else {
                    r = mid - 1;
                }
            }
            for (int j = i - 1; j >= l; j--) {
                mas[j + 1] = mas[j];
            }
            mas[l] = m;
        }
    }

    auto end = std::chrono::high_resolution_clock::now() - start;
    return std::chrono::duration_cast<std::chrono::nanoseconds>(end).count();
}

ll stableCountingSort(std::vector<int> &mas) {
    auto start = std::chrono::high_resolution_clock::now();
    int maxx = mas[0];
    // тут находим максимальное число, чтобы узнать размер для массива подсчета
    for (int i = 1; i < mas.size(); i++) {
        if (mas[i] > maxx) {
            maxx = mas[i];
        }
    }
    // тут просто считаем сколько раз встречался каждый элемент
    std::vector<int> c(maxx + 1, 0);
    for (int i = 0; i < mas.size(); i++) {
        c[mas[i]]++;
    }
    // тут подсчет всех сумм до, чтобы сортировка была устойчивой
    for (int i = 1; i <= maxx; i++) {
        c[i] += c[i - 1];
    }
    // тут выставляем наши элементы именно в том порядке, в котором они шли
    std::vector<int> ans(mas.size());
    for (int i = 0; i < mas.size(); i++) {
        c[mas[i]]--;
        ans[c[mas[i]]] = mas[i];
    }
    mas = ans;
    auto end = std::chrono::high_resolution_clock::now() - start;
    return std::chrono::duration_cast<std::chrono::nanoseconds>(end).count();
}

ll radixSort(std::vector<int> &mas) {
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<int> c(256);
    for (int i = 0; i < 9; i++) {
        // обнуляем массив с разрядами
        for (int k = 0; k < 256; k++) {
            c[k] = 0;
        }
        for (int j = 0; j < mas.size(); j++) {
            int d = mas[j];
            for (int h = 0; h < i; h++) {
                d /= 256;
            }
            // тут находим требуемый разряд
            d %= 256;
            // и записываем соотвтетвенно сколько его было в числах
            c[d]++;
        }
        int count = 0;
        // далтше по мути продолжение сортировки подсчетом
        for (int j = 0; j < 256; j++) {
            int tmp = c[j];
            c[j] = count;
            count += tmp;
        }
        std::vector<int> b(count);
        for (int j = 0; j < mas.size(); j++) {
            int d = mas[j];
            for (int h = 0; h < i; h++) {
                d /= 256;
            }
            d %= 256;
            // вот тут именно число записываем
            b[c[d]] = mas[j];
            c[d]++;
        }
        mas = b;
    }
    auto end = std::chrono::high_resolution_clock::now() - start;
    return std::chrono::duration_cast<std::chrono::nanoseconds>(end).count();
}

void merge(std::vector<int> &mas, int start, int mid, int end) {
    std::vector<int> listt(end - start + 1);
    int i, j, k;
    i = start;
    j = mid + 1;
    k = 0;
    // тут просто проходим аля двумя указателями и записываем в вектор listt исходный массив в отсортированном виде
    while (i <= mid && j <= end) {
        if (mas[i] <= mas[j]) {
            listt[k] = mas[i];
            i++;
            k++;
        } else {
            listt[k] = mas[j];
            j++;
            k++;
        }
    }

    // тут дополняем если что-то не доложили
    while (i <= mid) {
        listt[k] = mas[i];
        i++;
        k++;
    }
    // аналогично
    while (j <= end) {
        listt[k] = mas[j];
        j++;
        k++;
    }
    // в исходный массив в нужную часть кладем упорядоченный массив
    for (i = start; i <= end; i++) {
        mas[i] = listt[i - start];
    }
}

ll mergeSort(std::vector<int> &arr, int start, int end) {
    auto startt = std::chrono::high_resolution_clock::now();
    if (start >= end) {
        auto endd = std::chrono::high_resolution_clock::now() - startt;
        return std::chrono::duration_cast<std::chrono::nanoseconds>(endd).count();;
    }
    // делим массив пополам пока можем и сортим его подчасти
    int mid = start + (end - start) / 2;
    mergeSort(arr, start, mid);
    mergeSort(arr, mid + 1, end);
    merge(arr, start, mid, end);
    auto endd = std::chrono::high_resolution_clock::now() - startt;
    return std::chrono::duration_cast<std::chrono::nanoseconds>(endd).count();
}

ll qSort(int l, int r, std::vector<int> &mas) {
    auto startt = std::chrono::high_resolution_clock::now();
    int i = l;
    int j = r;
    int mainn = mas[l]; // опорный элемент
    do {
        // находим последний меньший опорного
        while (mas[i] < mainn && i < r) {
            i++;
        }
        // находим первый (относительно середины слева направо) больший опорного
        while (mas[j] > mainn && j > l) {
            j--;
        }
        // если они не в правильном порядке, то свопаем их
        if (i <= j) {
            std::swap(mas[i], mas[j]);
            i++;
            j--;
        }
    } while (i <= j);
    // рекурсивно вызываем необходимую часть
    if (l < j) {
        qSort(l, j, mas);
    }
    if (i < r) {
        qSort(i, r, mas);
    }
    auto endd = std::chrono::high_resolution_clock::now() - startt;
    return std::chrono::duration_cast<std::chrono::nanoseconds>(endd).count();
}

void rebuild(int i, int n, std::vector<int> &mas) {
    int fl = 1;
    while (i <= n / 2 && fl == 1) {
        int max = i;
        if (2 * i + 1 < n && mas[max] <= mas[2 * i + 1]) {
            max = 2 * i + 1;
        }
        if (2 * i + 2 < n && mas[max] <= mas[2 * i + 2]) {
            max = 2 * i + 2;
        }
        if (max != i) {
            std::swap(mas[i], mas[max]);
        } else {
            fl = 0;
        }
        i = max;
    }
}

ll heapSort(std::vector<int> &mas) {
    auto startt = std::chrono::high_resolution_clock::now();
    int n = mas.size();
    for (int i = n / 2 - 1; i >= 0; i--) {
        rebuild(i, n, mas);
    }
    for (int i = n - 1; i >= 0; i--) {
        std::swap(mas[0], mas[i]);
        rebuild(0, i, mas);
    }
    auto endd = std::chrono::high_resolution_clock::now() - startt;
    return std::chrono::duration_cast<std::chrono::nanoseconds>(endd).count();
}

ll sortShellCiura(std::vector<int> &mas) {
    auto startt = std::chrono::high_resolution_clock::now();
    std::vector<int> seqCiura = {1750, 701, 301, 132, 57, 23, 10, 4, 1};
    for (int i = 0; i < seqCiura.size(); i++) {
        for (int j = seqCiura[i]; j < mas.size(); j++) {
            int tmp = mas[j];
            int k = j;
            while (k >= seqCiura[i] && tmp < mas[k - seqCiura[i]]) {
                mas[k] = mas[k - seqCiura[i]];
                k -= seqCiura[i];
            }
            mas[k] = tmp;
        }
    }
    auto endd = std::chrono::high_resolution_clock::now() - startt;
    return std::chrono::duration_cast<std::chrono::nanoseconds>(endd).count();
}

ll sortShell(std::vector<int> &mas) {
    auto startt = std::chrono::high_resolution_clock::now();
    for (int i = mas.size() / 2; i > 0; i /= 2) {
        for (int j = i; j < mas.size(); j++) {
            int tmp = mas[j];
            int k = j;
            while (k >= i && tmp < mas[k - i]) {
                mas[k] = mas[k - i];
                k -= i;
            }
            mas[k] = tmp;
        }
    }
    auto endd = std::chrono::high_resolution_clock::now() - startt;
    return std::chrono::duration_cast<std::chrono::nanoseconds>(endd).count();
}

ll cnt;

void selectSort2(std::vector<int> &mas) {
    int min;
    cnt++; // i = 0
    for (int i = 0; i < mas.size() - 1; i++) {
        cnt++; // i++
        min = i;
        cnt++; // min = i
        cnt++; // j = i + 1
        for (int j = i + 1; j < mas.size(); j++) {
            cnt++; // j++
            if (mas[j] < mas[min]) {
                min = j;
                cnt++; // min = j
            }
        }
        if (i != min) {
            cnt += 3; //swap
            std::swap(mas[i], mas[min]);
        }
    }
}

void bubbleSort2(std::vector<int> &mas) {
    cnt++; // i = 0
    for (int i = 0; i < mas.size() - 1; i++) {
        cnt++; // i + 1
        cnt++; // j = 0
        for (int j = 0; j < mas.size() - 1 - i; j++) {
            cnt++; // j + 1
            if (mas[j] > mas[j + 1]) {
                cnt += 3; // swap
                std::swap(mas[j], mas[j + 1]);
            }
        }
    }
}

void bubbleSortA12(std::vector<int> &mas) {
    int i = 0;
    cnt++; // i = 0
    bool fl = true;
    cnt++; // fl = true
    cnt++; // while fl
    while (fl) {
        fl = false;
        cnt++; // fl = false
        cnt++; // j = 0
        for (int j = 0; j < mas.size() - i - 1; j++) {
            cnt++; // j + 1
            if (mas[j] > mas[j + 1]) {
                cnt += 3; // swap
                std::swap(mas[j], mas[j + 1]);
                fl = true;
                cnt++; // fl = true
            }
        }
        cnt++; // i + 1
        i++;
    }
}

void bubbleSortA22(std::vector<int> &mas) {
    bool fl = true;
    cnt++; // fl = true
    int t = mas.size() - 1;
    cnt++; // t = mas.size() - 1
    int k = mas.size() - 1;
    cnt++; // mas.size() - 1
    cnt++; // while (t != 0)
    while (t != 0) {
        t = 0;
        cnt++; // t = 0
        cnt++; // i = 0
        for (int i = 0; i < k; i++) {
            cnt++; // i + 1
            fl = false;
            cnt++; // fl = false
            cnt++; // j = 0
            for (int j = 0; j < mas.size() - i - 1; ++j) {
                cnt++; // j + 1
                if (mas[j] > mas[j + 1]) {
                    cnt += 3; // swap
                    std::swap(mas[j], mas[j + 1]);
                    cnt++; // fl = true
                    fl = true;
                    cnt++; // t = j
                    t = j;
                }
            }
            cnt++; // !fl
            if (!fl) {
                break;
            }
        }
        cnt++; // !fl
        if (!fl) {
            break;
        }
        k = t;
    }
}

void insertSort2(std::vector<int> &mas) {
    int key, temp;
    cnt++; // i = 0
    for (int i = 0; i < mas.size() - 1; i++) {
        cnt++; // i + 1
        key = i + 1;
        cnt += 2; // i + 1 -> key = i
        cnt++; // temp = mas[key];
        temp = mas[key];
        cnt++; // j = i + 1
        for (int j = i + 1; j > 0; j--) {
            cnt++; // j - 1
            if (temp < mas[j - 1]) {
                cnt++; // mas[j] = mas[j - 1];
                mas[j] = mas[j - 1];
                cnt += 2; // j - 1 -> key = j - 1;
                key = j - 1;
            }
        }
        cnt++; // mas[key] = temp;
        mas[key] = temp;
    }
}

void binInsertSort2(std::vector<int> &mas) {
    cnt++; // i = 1
    for (int i = 1; i < mas.size(); ++i) {
        cnt++;
        cnt += 3;
        if (mas[i - 1] > mas[i]) {
            int m = mas[i];
            cnt++;
            int l = 0;
            cnt++;
            int r = i - 1;
            cnt++;
            cnt += 3;
            while (r - l >= 0) {
                int mid = l + (r - l) / 2;
                cnt++;
                cnt += 2;
                if (mas[mid] < m) {
                    l = mid + 1;
                    cnt++;
                } else {
                    r = mid - 1;
                    cnt++;
                }
            }
            cnt++;
            for (int j = i - 1; j >= l; --j) {
                cnt++;
                mas[j + 1] = mas[j];
                cnt++;
            }
            cnt++;
            mas[l] = m;
        }
    }
}

void stableCountingSort2(std::vector<int> &mas) {
    int maxx = mas[0];
    cnt++;
    cnt++;
    for (int i = 1; i < mas.size(); i++) {
        cnt++;
        cnt += 2;
        if (mas[i] > maxx) {
            maxx = mas[i];
            cnt++;
        }
    }
    cnt++;
    std::vector<int> c(maxx + 1, 0);
    cnt++;
    for (int i = 0; i < mas.size(); i++) {
        cnt++;
        c[mas[i]]++;
        cnt++;
    }
    cnt++;
    for (int i = 1; i <= maxx; i++) {
        cnt++;
        c[i] += c[i - 1];
        cnt++;
        cnt++;
    }
    cnt++;
    std::vector<int> ans(mas.size());
    cnt++;
    for (int i = 0; i < mas.size(); i++) {
        cnt++;
        c[mas[i]]--;
        cnt++;
        ans[c[mas[i]]] = mas[i];
        cnt++;
    }
    mas = ans;
    cnt++;
}

void radixSort2(std::vector<int> &mas) {
    cnt++;
    std::vector<int> c(256);
    cnt++;
    for (int i = 0; i < 9; i++) {
        cnt++;
        cnt++;
        for (int k = 0; k < 256; k++) {
            cnt++;
            c[k] = 0;
            cnt++;
        }
        cnt++;
        for (int j = 0; j < mas.size(); j++) {
            cnt++;
            int d = mas[j];
            cnt++;
            cnt++;
            for (int h = 0; h < i; h++) {
                cnt++;
                d /= 256;
                cnt++;
            }
            cnt++;
            d %= 256;
            cnt++;
            c[d]++;
        }
        int count = 0;
        cnt++;
        cnt++;
        for (int j = 0; j < 256; j++) {
            cnt++;
            int tmp = c[j];
            cnt++;
            c[j] = count;
            cnt++;
            count += tmp;
            cnt++;
            cnt++;
        }
        cnt++;
        std::vector<int> b(count);
        cnt++;
        for (int j = 0; j < mas.size(); j++) {
            cnt++;
            int d = mas[j];
            cnt++;
            cnt++;
            for (int h = 0; h < i; h++) {
                cnt++;
                d /= 256;
                cnt++;
            }
            cnt++;
            d %= 256;
            cnt++;
            b[c[d]] = mas[j];
            cnt++;
            c[d]++;
        }
        cnt++;
        mas = b;
    }
}

void merge2(std::vector<int> &mas, int start, int mid, int end) {
    std::vector<int> listt(end - start + 1);
    cnt++;
    int i, j, k;
    i = start;
    j = mid + 1;
    k = 0;
    cnt += 4;
    cnt += 3;
    while (i <= mid && j <= end) {
        cnt += 1;
        if (mas[i] <= mas[j]) {
            listt[k] = mas[i];
            cnt++;
            i++;
            cnt++;
            k++;
            cnt++;
        } else {
            listt[k] = mas[j];
            cnt++;
            j++;
            cnt++;
            k++;
            cnt++;
        }
    }
    cnt++;
    while (i <= mid) {
        listt[k] = mas[i];
        cnt++;
        i++;
        cnt++;
        k++;
        cnt++;
    }
    cnt++;
    while (j <= end) {
        listt[k] = mas[j];
        cnt++;
        j++;
        cnt++;
        k++;
        cnt++;
    }
    cnt++;
    for (i = start; i <= end; i++) {
        cnt++;
        mas[i] = listt[i - start];
        cnt++;
    }
}

void mergeSort2(std::vector<int> &arr, int start, int end) {
    cnt++;
    if (start >= end) {
        return;
    }

    cnt += 3;
    int mid = start + (end - start) / 2;
    mergeSort2(arr, start, mid);
    mergeSort2(arr, mid + 1, end);
    merge2(arr, start, mid, end);
}

void qSort2(int l, int r, std::vector<int> &mas) {
    cnt++;
    int i = l;
    cnt++;
    int j = r;
    cnt++;
    int mainn = mas[l];
    do {
        cnt += 3;
        while (mas[i] < mainn && i < r) {
            i++;
            cnt++;
        }
        cnt += 3;
        while (mas[j] > mainn && j > l) {
            j--;
            cnt++;
        }
        cnt++;
        if (i <= j) {
            cnt += 3;
            std::swap(mas[i], mas[j]);
            i++;
            cnt++;
            j--;
            cnt++;
        }
    } while (i <= j);
    if (l < j) {
        qSort2(l, j, mas);
    }
    if (i < r) {
        qSort2(i, r, mas);
    }
}

void rebuild2(int i, int n, std::vector<int> &mas) {
    cnt++;
    int fl = 1;
    cnt += 3;
    while (i <= n / 2 && fl == 1) {
        int max = i;
        cnt++;
        cnt += 3;
        if (2 * i + 1 < n && mas[max] <= mas[2 * i + 1]) {
            max = 2 * i + 1;
            cnt++;
        }
        cnt += 3;
        if (2 * i + 2 < n && mas[max] <= mas[2 * i + 2]) {
            max = 2 * i + 2;
            cnt++;
        }
        cnt += 1;
        if (max != i) {
            cnt += 3;
            std::swap(mas[i], mas[max]);
        } else {
            cnt++;
            fl = 0;
        }
        cnt++;
        i = max;
    }
}

ll heapSort2(std::vector<int> &mas) {
    int n = mas.size();
    cnt++;
    cnt++;
    for (int i = n / 2 - 1; i >= 0; i--) {
        cnt++;
        rebuild2(i, n, mas);
    }
    cnt++;
    for (int i = n - 1; i >= 0; i--) {
        cnt++;
        cnt += 3;
        std::swap(mas[0], mas[i]);
        rebuild2(0, i, mas);
    }
}

void sortShellCiura2(std::vector<int> &mas) {
    cnt++;
    std::vector<int> seqCiura = {1750, 701, 301, 132, 57, 23, 10, 4, 1};
    cnt++;
    for (int i = 0; i < seqCiura.size(); i++) {
        cnt++;
        for (int j = seqCiura[i]; j < mas.size(); j++) {
            cnt++;
            int tmp = mas[j];
            cnt++;
            int k = j;
            cnt++;
            cnt += 4;
            while (k >= seqCiura[i] && tmp < mas[k - seqCiura[i]]) {
                cnt++;
                mas[k] = mas[k - seqCiura[i]];
                cnt++;
                k -= seqCiura[i];
            }
            mas[k] = tmp;
            cnt++;
        }
    }
}

void sortShell2(std::vector<int> &mas) {
    cnt++;
    for (int i = mas.size() / 2; i > 0; i /= 2) {
        cnt++;
        cnt++;
        for (int j = i; j < mas.size(); j++) {
            cnt++;
            int tmp = mas[j];
            cnt++;
            int k = j;
            cnt++;
            cnt += 3;
            while (k >= i && tmp < mas[k - i]) {
                mas[k] = mas[k - i];
                cnt++;
                k -= i;
                cnt++;
            }
            mas[k] = tmp;
            cnt++;
        }
    }
}

//проверка что массив отсортирован. как только это не так, то выводим 0
int check(std::vector<int> &mas) {
    for (int i = 0; i < mas.size() - 1; i++) {
        if (mas[i] > mas[i + 1]) {
            return 0;
        }
    }
    return 1;
}

// функция измерения времени для графика, где все функции
void timeMeasure2(std::vector<int> &mas, std::string name1, std::string name2) {
    std::vector<int> vec1(4100);
    vec1 = mas;
    // тут записываем в csv файл
    std::ofstream myfile;
    myfile.open(name1);
    myfile
            << "; selectSort; bubbleSort; bubbleSortA1; bubbleSortA2; insertSort; binInsertSort; stableCountingSort; radixSort; mergeSort; qSort; heapSort; sortShellCiura; sortShell;\n";

    // можно я опишу для одной сортировки? там дальше все аналогично((
    // тут для массивов 50, 100, 150...
    for (int i = 50; i <= 300; i += 50) {
        myfile << i << "; "; // вводим размер массива
        std::vector<int> coppy(i);
        cnt = 0; // обнуляем счветсчик
        std::copy(vec1.begin(), vec1.begin() + i, coppy.begin()); // копируем
        selectSort2(coppy);
        myfile << cnt << "; "; // пишем файлш кол-во операций

        cnt = 0;
        std::copy(vec1.begin(), vec1.begin() + i, coppy.begin());
        bubbleSort2(coppy);
        myfile << cnt << "; ";

        cnt = 0;
        std::copy(vec1.begin(), vec1.begin() + i, coppy.begin());
        bubbleSortA12(coppy);
        myfile << cnt << "; ";

        cnt = 0;
        std::copy(vec1.begin(), vec1.begin() + i, coppy.begin());
        bubbleSortA22(coppy);
        myfile << cnt << "; ";

        cnt = 0;
        std::copy(vec1.begin(), vec1.begin() + i, coppy.begin());
        insertSort2(coppy);
        myfile << cnt << "; ";

        cnt = 0;
        std::copy(vec1.begin(), vec1.begin() + i, coppy.begin());
        binInsertSort2(coppy);
        myfile << cnt << "; ";

        cnt = 0;
        std::copy(vec1.begin(), vec1.begin() + i, coppy.begin());
        stableCountingSort2(coppy);
        myfile << cnt << "; ";

        cnt = 0;
        std::copy(vec1.begin(), vec1.begin() + i, coppy.begin());
        radixSort2(coppy);
        myfile << cnt << "; ";

        cnt = 0;
        std::copy(vec1.begin(), vec1.begin() + i, coppy.begin());
        mergeSort2(coppy, 0, coppy.size() - 1);
        myfile << cnt << "; ";

        cnt = 0;
        std::copy(vec1.begin(), vec1.begin() + i, coppy.begin());
        qSort2(0, coppy.size() - 1, coppy);
        myfile << cnt << "; ";

        cnt = 0;
        std::copy(vec1.begin(), vec1.begin() + i, coppy.begin());
        heapSort2(coppy);
        myfile << cnt << "; ";

        cnt = 0;
        std::copy(vec1.begin(), vec1.begin() + i, coppy.begin());
        sortShellCiura2(coppy);
        myfile << cnt << "; ";

        cnt = 0;
        std::copy(vec1.begin(), vec1.begin() + i, coppy.begin());
        sortShell2(coppy);
        myfile << cnt << "; ";

        myfile << "\n";
    }
    myfile.close();

    myfile.open(name2);
    myfile
            << "; selectSort; bubbleSort; bubbleSortA1; bubbleSortA2; insertSort; binInsertSort; stableCountingSort; radixSort; mergeSort; qSort; heapSort; sortShellCiura; sortShell\n";

    for (int i = 100; i <= 4100; i += 100) {
        myfile << i << "; ";
        std::vector<int> coppy(i);
        cnt = 0;
        std::copy(vec1.begin(), vec1.begin() + i, coppy.begin());
        selectSort2(coppy);
        myfile << cnt << "; ";

        cnt = 0;
        std::copy(vec1.begin(), vec1.begin() + i, coppy.begin());
        bubbleSort2(coppy);
        myfile << cnt << "; ";

        cnt = 0;
        std::copy(vec1.begin(), vec1.begin() + i, coppy.begin());
        bubbleSortA12(coppy);
        myfile << cnt << "; ";

        cnt = 0;
        std::copy(vec1.begin(), vec1.begin() + i, coppy.begin());
        bubbleSortA22(coppy);
        myfile << cnt << "; ";

        cnt = 0;
        std::copy(vec1.begin(), vec1.begin() + i, coppy.begin());
        insertSort2(coppy);
        myfile << cnt << "; ";

        cnt = 0;
        std::copy(vec1.begin(), vec1.begin() + i, coppy.begin());
        binInsertSort2(coppy);
        myfile << cnt << "; ";

        cnt = 0;
        std::copy(vec1.begin(), vec1.begin() + i, coppy.begin());
        stableCountingSort2(coppy);
        myfile << cnt << "; ";

        cnt = 0;
        std::copy(vec1.begin(), vec1.begin() + i, coppy.begin());
        radixSort2(coppy);
        myfile << cnt << "; ";

        cnt = 0;
        std::copy(vec1.begin(), vec1.begin() + i, coppy.begin());
        mergeSort2(coppy, 0, coppy.size() - 1);
        myfile << cnt << "; ";

        cnt = 0;
        std::copy(vec1.begin(), vec1.begin() + i, coppy.begin());
        qSort2(0, coppy.size() - 1, coppy);
        myfile << cnt << "; ";

        cnt = 0;
        std::copy(vec1.begin(), vec1.begin() + i, coppy.begin());
        heapSort2(coppy);
        myfile << cnt << "; ";

        cnt = 0;
        std::copy(vec1.begin(), vec1.begin() + i, coppy.begin());
        sortShellCiura2(coppy);
        myfile << cnt << "; ";

        cnt = 0;
        std::copy(vec1.begin(), vec1.begin() + i, coppy.begin());
        sortShell2(coppy);
        myfile << cnt << "; ";

        myfile << "\n";
    }
    myfile.close();
}

// функция измерения времени для графика, где все функции
void timeMeasure(std::vector<int> &mas, std::string name1, std::string name2) {
    std::vector<int> vec1(4100);
    vec1.assign(mas.begin(), mas.end());
    for (int i = 0; i < 4100; i++) {
        vec1[i] = mas[i];
    }
    // тут записываем в csv файл
    std::ofstream myfile;
    myfile.open(name1);
    myfile
            << "; selectSort; bubbleSort; bubbleSortA1; bubbleSortA2; insertSort; binInsertSort; stableCountingSort; radixSort; mergeSort; qSort; heapSort; sortShellCiura; sortShell;\n";

    // можно я опишу для одной сортировки? там дальше все аналогично((
    // тут для массивов 50, 100, 150...
    for (int i = 50; i <= 300; i += 50) {
        myfile << i << "; ";
        std::vector<int> coppy(i);
        ll time = 0;
        for (int j = 0; j < 20; j++) {
            std::copy(vec1.begin(), vec1.begin() + i, coppy.begin());
            time += selectSort(coppy);
            // проверка внутри на отсортированность
            if (check(coppy) == 0) {
                std::cout << "Капец1!!!"; // это чтобы было понять где плохо
            }
        }
        //усреднение времени
        myfile << time / 20 << "; ";

        time = 0;
        for (int j = 0; j < 20; j++) {
            std::copy(vec1.begin(), vec1.begin() + i, coppy.begin());
            time += bubbleSort(coppy);
            if (check(coppy) == 0) {
                std::cout << "Капец2!!!";
            }
        }
        myfile << time / 20 << "; ";

        time = 0;
        for (int j = 0; j < 20; j++) {
            std::copy(vec1.begin(), vec1.begin() + i, coppy.begin());
            time += bubbleSortA1(coppy);
            if (check(coppy) == 0) {
                std::cout << "Капец3!!!";
            }
        }
        myfile << time / 20 << "; ";

        time = 0;
        for (int j = 0; j < 20; j++) {
            std::copy(vec1.begin(), vec1.begin() + i, coppy.begin());
            time += bubbleSortA2(coppy);
            if (check(coppy) == 0) {
                std::cout << "Капец4!!!";
            }
        }
        myfile << time / 20 << "; ";

        time = 0;
        for (int j = 0; j < 20; j++) {
            std::copy(vec1.begin(), vec1.begin() + i, coppy.begin());
            time += insertSort(coppy);
            if (check(coppy) == 0) {
                std::cout << "Капец5!!!";
            }
        }
        myfile << time / 20 << "; ";

        time = 0;
        for (int j = 0; j < 20; j++) {
            std::copy(vec1.begin(), vec1.begin() + i, coppy.begin());
            time += binInsertSort(coppy);
            if (check(coppy) == 0) {
                std::cout << "Капец6!!!";
            }
        }
        myfile << time / 20 << "; ";

        time = 0;
        for (int j = 0; j < 20; j++) {
            std::copy(vec1.begin(), vec1.begin() + i, coppy.begin());
            time += stableCountingSort(coppy);
            if (check(coppy) == 0) {
                std::cout << "Капец7!!!";
            }
        }
        myfile << time / 20 << "; ";

        time = 0;
        for (int j = 0; j < 20; j++) {
            std::copy(vec1.begin(), vec1.begin() + i, coppy.begin());
            time += radixSort(coppy);
            if (check(coppy) == 0) {
                std::cout << "Капец8!!!";
            }
        }
        myfile << time / 20 << "; ";

        time = 0;
        for (int j = 0; j < 20; j++) {
            std::copy(vec1.begin(), vec1.begin() + i, coppy.begin());
            time += mergeSort(coppy, 0, coppy.size() - 1);
            if (check(coppy) == 0) {
                std::cout << "Капец9!!!";
            }
        }
        myfile << time / 20 << "; ";

        time = 0;
        for (int j = 0; j < 20; j++) {
            std::copy(vec1.begin(), vec1.begin() + i, coppy.begin());
            time += qSort(0, coppy.size() - 1, coppy);
            if (check(coppy) == 0) {
                std::cout << "Капец10!!!";
            }
        }
        myfile << time / 20 << "; ";

        time = 0;
        for (int j = 0; j < 20; j++) {
            std::copy(vec1.begin(), vec1.begin() + i, coppy.begin());
            time += heapSort(coppy);
            if (check(coppy) == 0) {
                std::cout << "Капец11!!!";
            }
        }
        myfile << time / 20 << "; ";

        time = 0;
        for (int j = 0; j < 20; j++) {
            std::copy(vec1.begin(), vec1.begin() + i, coppy.begin());
            time += sortShellCiura(coppy);
            if (check(coppy) == 0) {
                std::cout << "Капец12!!!";
            }
        }
        myfile << time / 20 << "; ";

        time = 0;
        for (int j = 0; j < 20; j++) {
            std::copy(vec1.begin(), vec1.begin() + i, coppy.begin());
            time += sortShell(coppy);
            if (check(coppy) == 0) {
                std::cout << "Капец13!!!";
            }
        }
        myfile << time / 20 << "; ";

        myfile << "\n";
    }
    myfile.close();

    myfile.open(name2);
    myfile
            << "; selectSort; bubbleSort; bubbleSortA1; bubbleSortA2; insertSort; binInsertSort; stableCountingSort; radixSort; mergeSort; qSort; heapSort; sortShellCiura; sortShell\n";

    for (int i = 100; i <= 4100; i += 100) {
        myfile << i << "; ";
        std::vector<int> coppy(i);
        ll time = 0;
        for (int j = 0; j < 20; j++) {
            std::copy(vec1.begin(), vec1.begin() + i, coppy.begin());
            time += selectSort(coppy);
            if (check(coppy) == 0) {
                std::cout << "Капец!!!";
            }
        }
        myfile << time / 20 << "; ";

        time = 0;
        for (int j = 0; j < 20; j++) {
            std::copy(vec1.begin(), vec1.begin() + i, coppy.begin());
            time += bubbleSort(coppy);
            if (check(coppy) == 0) {
                std::cout << "Капец!!!";
            }
        }
        myfile << time / 20 << "; ";

        time = 0;
        for (int j = 0; j < 20; j++) {
            std::copy(vec1.begin(), vec1.begin() + i, coppy.begin());
            time += bubbleSortA1(coppy);
            if (check(coppy) == 0) {
                std::cout << "Капец!!!";
            }
        }
        myfile << time / 20 << "; ";

        time = 0;
        for (int j = 0; j < 20; j++) {
            std::copy(vec1.begin(), vec1.begin() + i, coppy.begin());
            time += bubbleSortA2(coppy);
            if (check(coppy) == 0) {
                std::cout << "Капец!!!";
            }
        }
        myfile << time / 20 << "; ";

        time = 0;
        for (int j = 0; j < 20; j++) {
            std::copy(vec1.begin(), vec1.begin() + i, coppy.begin());
            time += insertSort(coppy);
            if (check(coppy) == 0) {
                std::cout << "Капец!!!";
            }
        }
        myfile << time / 20 << "; ";

        time = 0;
        for (int j = 0; j < 20; j++) {
            std::copy(vec1.begin(), vec1.begin() + i, coppy.begin());
            time += binInsertSort(coppy);
            if (check(coppy) == 0) {
                std::cout << "Капец!!!";
            }
        }
        myfile << time / 20 << "; ";

        time = 0;
        for (int j = 0; j < 20; j++) {
            std::copy(vec1.begin(), vec1.begin() + i, coppy.begin());
            time += stableCountingSort(coppy);
            if (check(coppy) == 0) {
                std::cout << "Капец!!!";
            }
        }
        myfile << time / 20 << "; ";

        time = 0;
        for (int j = 0; j < 20; j++) {
            std::copy(vec1.begin(), vec1.begin() + i, coppy.begin());
            time += radixSort(coppy);
            if (check(coppy) == 0) {
                std::cout << "Капец!!!";
            }
        }
        myfile << time / 20 << "; ";

        time = 0;
        for (int j = 0; j < 20; j++) {
            std::copy(vec1.begin(), vec1.begin() + i, coppy.begin());
            time += mergeSort(coppy, 0, coppy.size() - 1);
            if (check(coppy) == 0) {
                std::cout << "Капец!!!";
            }
        }
        myfile << time / 20 << "; ";

        time = 0;
        for (int j = 0; j < 20; j++) {
            std::copy(vec1.begin(), vec1.begin() + i, coppy.begin());
            time += qSort(0, coppy.size() - 1, coppy);
            if (check(coppy) == 0) {
                std::cout << "Капец!!!";
            }
        }
        myfile << time / 20 << "; ";

        time = 0;
        for (int j = 0; j < 20; j++) {
            std::copy(vec1.begin(), vec1.begin() + i, coppy.begin());
            time += heapSort(coppy);
            if (check(coppy) == 0) {
                std::cout << "Капец!!!";
            }
        }
        myfile << time / 20 << "; ";

        time = 0;
        for (int j = 0; j < 20; j++) {
            std::copy(vec1.begin(), vec1.begin() + i, coppy.begin());
            time += sortShellCiura(coppy);
            if (check(coppy) == 0) {
                std::cout << "Капец!!!";
            }
        }
        myfile << time / 20 << "; ";

        time = 0;
        for (int j = 0; j < 20; j++) {
            std::copy(vec1.begin(), vec1.begin() + i, coppy.begin());
            time += sortShell(coppy);
            if (check(coppy) == 0) {
                std::cout << "Капец!!!";
            }
        }
        myfile << time / 20 << "; ";

        myfile << "\n";
    }
    myfile.close();
}


void runner() {
    std::vector<int> begin(4100);

    srand(time(nullptr)); // запускаем рандом орт времени
    for (int i = 0; i < 4100; i++) {
        begin[i] = rand() % 6;
    }

    timeMeasure(begin, "1first_type_array.csv", "2second_type_array.csv");
    timeMeasure2(begin, "cnt_1first_type_array.csv", "cnt_2second_type_array.csv");

    for (int i = 0; i < 4100; i++) {
        begin[i] = rand() % 4001 + 5;
    }
    timeMeasure(begin, "3third_type_array.csv", "4fourth_type_array.csv");
    timeMeasure2(begin, "cnt_3third_type_array.csv", "cnt_4fourth_type_array.csv");

    begin[0] = rand() % 10;
    for (int i = 1; i < 150; i++) {
        begin[i] = rand() % 10 + begin[i - 1];
    }
    for (int i = 150; i < 300; i++) {
        begin[i] = rand() % 300;
    }
    for (int i = 301; i < 2050; i++) {
        begin[i] = rand() % 10 + begin[i - 1];
    }
    for (int i = 2050; i < 4100; i++) {
        begin[i] = rand() % 300;
    }
    timeMeasure(begin, "5fifth_type_array.csv", "6sixth_type_array.csv");
    timeMeasure2(begin, "cnt_fifth_type_array.csv", "cnt_sixth_type_array.csv");

    begin[0] = (rand() % 10) * 1000000;
    for (int i = 1; i < 4100; i++) {
        begin[i] = -rand() % 10 + begin[i - 1];
    }
    timeMeasure(begin, "7seventh_type_array.csv", "8eighths_type_array.csv");
    timeMeasure2(begin, "cnt_seventh_type_array.csv", "cnt_eighths_type_array.csv");
}


int main() {
    runner();
    return 0;
}
