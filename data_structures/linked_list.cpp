
#include <list> // double linked list
#include <array>
#include <iostream>
using namespace std;

template <typename T>
class element {
public:
    element* prev;
    element* next;
    T value;
};

template <typename T>
class bear_list {
public:
    element<T>* begin() {return dummy.next;}
    element<T>* end() {return &dummy;}
    void insert(element<T>* position, T val) { // Insert new element before specified position
        element<T>* new_ptr = new element<T>();
        new_ptr->prev = position->prev;
        new_ptr->next = position;
        new_ptr->value = val;
        position->prev = new_ptr;
        new_ptr->prev->next = new_ptr;
    }
    bear_list() {
        dummy.next = &dummy;
        dummy.prev = &dummy;
        dummy.value = (T)0;
    }
private:
    element<T> dummy;
};

int main() {
    array<int, 10> array = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    {
        cout << "Using standard template library" << endl;
        list<int> cpp_list;
        for (int i = 0; i < array.size(); i++) {
            cpp_list.insert(cpp_list.begin(), array[i]);
        }
        for (auto ptr = cpp_list.begin(); ptr != cpp_list.end(); ptr++) {
            cout << (*ptr) << " ";
        }
        cout << endl;
    }

    {
        cout << "Bear implementation" << endl;
        bear_list<int> bear_list;
        for (int i = 0; i < array.size(); i++) {
            bear_list.insert(bear_list.begin(), array[i]);
        }
        for (auto ptr = bear_list.begin(); ptr != bear_list.end(); ptr = ptr->next) {
            cout << ptr->value << " ";
        }
        cout << endl;
    }

    return 0;
}