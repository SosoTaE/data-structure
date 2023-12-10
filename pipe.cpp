#include <variant>
#include <iostream>
#include <string>

using namespace std;

using object = std::variant<int, float, std::string,char, size_t, double>;

struct Node {
    object value;
    Node* next;
    Node* prev;
    Node() {
        next = nullptr;
        prev = nullptr;
    }

    Node(object value) {
        this -> value = value;
        next = nullptr;
        prev = nullptr;
    }
};

class Pipe {
    private:
        size_t maxItems;
        Node* top;
        Node* last;
        size_t length;

        void unshifter(Node* item) {
            if (length >= maxItems) {
                pop();
            }
            if (top == nullptr) {
                top = item;
                last = item;
            }
            else {
                item -> next = top;
                top -> prev = item;
                top = item;
            }

            length++;
        }

        void appender(Node* item) {
            if (length >= maxItems) {
                shift();
            }

            if (top == nullptr) {
                top = item;
                last = item;
            }
            else {
                last -> next = item;
                item -> prev = last;
                last = item;
            }

            length++;
        }

    public:
        Pipe(size_t length): maxItems(length), length(0), top(nullptr), last(nullptr) {} 

        ~Pipe() {
            Node* current = top;
            while (current != nullptr) {
                Node* next = current->next;
                delete current;
                current = next;
            }
    }

        void append(object value) {
            Node* item = new Node(value);
            appender(item);
        }

        void append(Node node) {
            Node* item = new Node(node.value);
            appender(item);
        }

        void append(Node* node) {
            Node* item = new Node(node -> value);
            appender(item);
        }

        void unshift(object value) {
            Node* item = new Node(value);
            unshifter(item);
        }

        void unshift(Node node) {
            Node* item = new Node(node.value);
            unshifter(item);
        }

        void unshift(Node* node) {
            Node* item = new Node(node -> value);
            unshifter(item);
        }

        void shift() {
            if (top == nullptr) {
                return;
            }

            Node* temp = top;
            top = top -> next;
            if (top == nullptr) {
                last = nullptr;
            }
            else {
                top->prev = nullptr;
            }
            length--;
            delete temp;
        }

        void pop() {
            if (last == nullptr) {
                return;
            }

            Node* temp = last;
            last = last -> prev;
            if (last == nullptr) {
                top = nullptr;
            }
            else {
                last->next = nullptr;
            }
            length--;
            delete temp;
        }
        
        size_t size() {
            return length;
        }
    
        friend std::ostream& operator<<(std::ostream& os, Pipe& pipe);
};

std::ostream& operator<<(std::ostream& os, Pipe& pipe) {
    os << "[";
    Node* subnode = pipe.top;

    while (subnode != nullptr) {
        std::visit([&os](auto&& arg) { os << arg; }, subnode->value);
        subnode = subnode->next;
        if (subnode != nullptr) {
            os << ", ";
        }
    }

    os << ']';

    return os;
}

int main() {
    Pipe pipe(5);
    for (int i = 0;i < 6;i++) {
        cout<<pipe<<endl;
        pipe.unshift(i);
    }

     for (int i = 0;i < 6;i++) {
        cout<<pipe<<endl;
        pipe.append(i);
    }

    for (int i = 0;i < 2;i++) {
        cout<<pipe<<endl;
        pipe.pop();
    }

    for (int i = 0;i <= 2;i++) {
        cout<<pipe<<endl;
        pipe.shift();
    }

    pipe.shift();
    cout<<pipe<<endl;

    return 0;
}
