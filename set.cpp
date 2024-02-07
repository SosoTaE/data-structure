#include <iostream>
typedef int Object;
using namespace std;
    
struct Node {
    Object value;
    Node* next;
    Node(): value(0), next(0) {};
    Node(int value): value(value), next(0){};
    Node(int value, Node* next): value(value), next(next) {};
};


class Set {
    private:
        Node* first;
        Node* last;
        size_t length;

    public:
        Set() {
            first = 0;
            last = 0;
            length = 0;
        }

        bool includes(Object item) {
            if (first == 0) {
                return false;
            }   
            Node* copyOfFirst = first;
            while (copyOfFirst != 0)
            {
                if (copyOfFirst -> value == item) {
                    return true;
                }

                copyOfFirst = copyOfFirst -> next;
            }

            return false;
        }

        void add(Object value) {
            if (first == 0) {
                Node* node = new Node(value);
                first = node;
                last = node;
            }
            else {
                if (!includes(value)) {
                    Node* node = new Node(value);
                    last -> next = node;
                    last = last -> next;
                }
            }

            length++;
        }

        size_t size() {
            return length;
        }

        Set operator+(const Set& set) const {
            Set result = *this;
            Node* current = set.first;
            while (current != nullptr) {
                result.add(current->value);
                current = current->next;
            }
            return result;
        }
        
        Set operator=(Set other) {
            swap(first, other.first);
            swap(last, other.last);
            swap(length, other.length);
            return *this;
        }

        Set operator/(Set set) {
            Set result = Set();
            
            Node* copied = first;

            while (copied != 0) {
                if (!set.includes(copied->value)) {
                    result.add(copied->value);
                }
                copied = copied -> next;
            }

            return result;

        }

        Set operator|(Set set) {
            Set result = Set();
            
            Node* copied = first;

            while (copied != 0) {
                if (set.includes(copied->value)) {
                    result.add(copied->value);
                }
                copied = copied -> next;
            }

            return result;

        }

        friend ostream& operator<<(ostream &os, Set &set);
};

ostream& operator<<(ostream &os, Set &set) {
    os<< "[";

    Node* copyOfFirst = set.first;
    while (copyOfFirst != 0) {
        os<<copyOfFirst->value;
        copyOfFirst = copyOfFirst -> next;
        if (copyOfFirst) {
            os<<" ";
        }
    }

    os<< "]";

    return os;

}

int main() {
    Set set_1 = Set();
    for (int i = -1;i < 10;i++) {
        set_1.add(i);
    }

    Set set_2 = Set();
    for (int i = 0;i < 101;i++) {
        set_2.add(i);
    }


    cout<<"set_1:"<<set_1<<" size:"<<set_1.size()<<endl;
    cout<<"set_2:"<<set_2<<" size:"<<set_2.size()<<endl;


    Set UnionOfSets = set_1 + set_2;
    Set DifferenceOfSets = set_1 / set_2;
    Set IntersectionOfSets = set_1 | set_2;
    
    std::cout<<"UnionOfSets:"<<UnionOfSets<<endl;
    std::cout<<"DifferenceOfSets:"<<DifferenceOfSets<<endl;
    std::cout<<"IntersectionOfSets:"<<IntersectionOfSets<<endl;
    return 0;
}