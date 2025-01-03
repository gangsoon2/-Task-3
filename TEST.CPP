#include <iostream>
#include <algorithm>
using namespace std;

template<typename T>
class DynamicArray {
private:
    T* arr;
    int size;
    int capacity;
public:
    // 기본 생성자
    DynamicArray() : arr(nullptr), size(0), capacity(1) {}

    // 소멸자
    ~DynamicArray() { delete[] arr; }

    // 원소 삽입
    void insert(int index, const T& value) {
        if (index > size) throw out_of_range("Index is out of range");

        // 배열 크기 확장
        if (size == capacity) {
            capacity *= 2;
            T* newArr = new T[capacity];

            // 기존 원소 복사
            for (int i = 0; i < size; ++i) {
                newArr[i] = arr[i];
            }

            // 새로운 원소 추가
            newArr[index] = value;

            // 메모리 해제 및 새 배열로 교체
            delete[] arr;
            arr = newArr;
        }
        else {
            // 인덱스 이동
            for (int i = size - 1; i >= index; --i) {
                arr[i + 1] = arr[i];
            }

            // 새로운 원소 추가
            arr[index] = value;
        }

        // 원소 개수 증가
        ++size;
    }

    // 원소 삭제
    void erase(int index) {
        if (index >= size) throw out_of_range("Index is out of range");

        // 인덱스 이동
        for (int i = index; i < size - 1; ++i) {
            arr[i] = arr[i + 1];
        }

        // 원소 개수 감소
        --size;
    }

    // 배열 크기 확장 및 정렬
    void sort() {
        sort(arr, arr + size);
    }
};

int main() {
    try {
        DynamicArray<int> arr;

        arr.insert(0, 10);
        arr.insert(1, 20);
        arr.insert(2, 30);

        cout << "Before sorting: ";
        for (int i = 0; i < arr.size(); ++i) {
            cout << arr[i] << " ";
        }
        cout << endl;

        arr.sort();

        cout << "After sorting: ";
        for (int i = 0; i < arr.size(); ++i) {
            cout << arr[i] << " ";
        }
        cout << endl;

        arr.erase(1);

        cout << "After erasing: ";
        for (int i = 0; i < arr.size(); ++i) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
    catch (const exception& e) {
        cerr << "Exception caught: " << e.what() << endl;
    }

    return 0;
}
