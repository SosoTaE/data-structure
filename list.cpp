#include <iostream>
#include <string>
typedef std::string Object;

using namespace std;

struct Node {
    public:
        Object value;
        Node* next;
        Node() {
            next = nullptr;
        }
};

class List {
    private:
        Node* Top;
    
    public:
        List() : Top(nullptr) {}

    void push(Object value) {
        Node* node = new Node();
        node -> value = value;
        if (Top == nullptr) {
            Top = node;
            return;
        }
        else if (value <= Top ->value) {
            node->next = Top;
            Top = node;
            return;
        }



        Node* y = Top;
        Node* k = nullptr;
        while (value > y->value) {
            k = y;
            if (y -> next == nullptr) {
                y ->next = node;
                return;
            }
            y = y->next;

        }

        node -> next = y;
        k -> next = node;

    }

    friend std::ostream& operator<<(std::ostream& os, const List &list);

};


std::ostream& operator<<(std::ostream& os, const List &list) {
    os<<"[";
    Node* newOne = list.Top;
    while (newOne != nullptr) {
        os<<newOne->value;

        newOne = newOne->next;

        if (newOne == nullptr || newOne == 0) {
            break;
        }

        os<<", ";
    }

    os<<"]";

    return os;
}


int main() {
    List list = List();
    list.push("gio");
    list.push("ana");
    list.push("aaa");


    cout<<list<<endl;
    return 0;
}
