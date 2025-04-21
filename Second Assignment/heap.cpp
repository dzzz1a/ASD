#include <iostream>

using namespace std;

class Node {
private:
    int iData;

public:
    Node(int key) {
        iData = key;
    }

    int getKey() {
        return iData;
    }
};

class Heap {
private:
    Node** heapArray;
    int maxSize;
    int currentSize;

public:
    Heap(int mx) {
        maxSize = mx;
        currentSize = 0;
        heapArray = new Node*[maxSize + 1];
    }

    bool isEmpty() {
        return currentSize == 0;
    }

    bool isFull() {
        return currentSize == maxSize;
    }

    bool insert(int key) {
        if (isFull()) {
            return false;
        }
        Node* newNode = new Node(key);
        heapArray[++currentSize] = newNode;
        trickleUp(currentSize);
        return true;
    }

    void trickleUp(int index) {
        int parent = index / 2;
        Node* bottom = heapArray[index];

        while (index > 1 && heapArray[parent]->getKey() > bottom->getKey()) {
            heapArray[index] = heapArray[parent];
            index = parent;
            parent = parent / 2;
        }
        heapArray[index] = bottom;
    }

    Node* remove() {
        if (isEmpty()) {
            return NULL;
        }
        Node* root = heapArray[1];
        heapArray[1] = heapArray[currentSize--];
        trickleDown(1);
        return root;
    }

    void trickleDown(int index) {
        int smallerChild;
        Node* top = heapArray[index];

        while (index * 2 <= currentSize) {
            int leftChild = 2 * index;
            int rightChild = 2 * index + 1;

            if (rightChild <= currentSize && heapArray[leftChild]->getKey() > heapArray[rightChild]->getKey()) {
                smallerChild = rightChild;
            } else {
                smallerChild = leftChild;
            }

            if (top->getKey() <= heapArray[smallerChild]->getKey()) {
                break;
            }

            heapArray[index] = heapArray[smallerChild];
            index = smallerChild;
        }
        heapArray[index] = top;
    }

    void displayHeap() {
        for (int i = 1; i <= currentSize; i++) {
            cout << heapArray[i]->getKey() << " ";
        }
        cout << endl;
    }
    void heapSort(int sortedArray[], bool ascending = true) {
    Heap tempHeap(currentSize);

    for (int i = 1; i <= currentSize; i++) {
        tempHeap.insert(heapArray[i]->getKey());
    }

    for (int i = 0; i < currentSize; i++) {
        sortedArray[i] = tempHeap.remove()->getKey();
    }

    if (!ascending) {
        for (int i = 0; i < currentSize / 2; i++) {
            swap(sortedArray[i], sortedArray[currentSize - 1 - i]);
        }
      }
    }
};

int main() {
    int arr[] = {12, 3, 5, 7, 19, 1, 8, 15, 4, 11, 6, 9, 14};
    int size = sizeof(arr) / sizeof(arr[0]);

    Heap heap(size + 1);

    for (int i = 0; i < size; ++i) {
        heap.insert(arr[i]);
    }

    cout << "Min-heap: ";
    heap.displayHeap();

    heap.insert(2);
    cout << "Min-heap after inserting 2: ";
    heap.displayHeap();

    int sortedDec[14];
    heap.heapSort(sortedDec, false);
    cout << "Heap Sort in Decreasing Order: ";
    for (int i = 0; i < size + 1; i++) {
        cout << sortedDec[i] << " ";
    }
    cout << endl;

    int sortedAsc[14];
    heap.heapSort(sortedAsc, true);
    cout << "Heap Sort in Ascending Order: ";
    for (int i = 0; i < size + 1; i++) {
        cout << sortedAsc[i] << " ";
    }
    cout << endl;

    cout << "Priority Queue 1: " << heap.remove()->getKey() << endl;

    cout << "Min-heap after delete section: ";
    heap.displayHeap();

    cout << "Priority Queue 2: " << heap.remove()->getKey() << endl;

    return 0;
}
