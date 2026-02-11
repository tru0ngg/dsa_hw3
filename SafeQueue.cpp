#include <iostream>
using std::cout, std::endl, std::cin;
#include <string>
using std::string;

int g_nodes = 0;

template <class E>
struct Node {
        E value;
        Node<E>* next;
        Node(E v, Node<E>* n) {
                value = v;
                next = n;
                g_nodes++;
                cout << "Node allocated. Count is " << g_nodes << endl;
        }
        ~Node() {
                g_nodes--;
                cout << "Node deallocated. Count is " << g_nodes << endl;
        }
};

// Write your SafeQueue class here, using the above Node class
template <class E>
class SafeQueue{
        private:
        Node<E>* head;
        Node<E>* tail;

        void clear(){
                while (head != nullptr){
                        Node<E>* old = head;
                        head = head->next;
                        delete old;
                }
                tail = nullptr;
        }

        public:
        SafeQueue(){
                head = nullptr;
                tail = nullptr;
        }

        ~SafeQueue(){
                clear();
        }

        void enqueue(E x) {
        Node<E>* newNode = new Node<E>(x, nullptr);

                if (tail == nullptr) {
                        head = newNode;
                        tail = newNode;
                }
                else {
                        tail->next = newNode;
                        tail = newNode;
                }
        }

        E dequeue() {
                if (head == nullptr) {
                        cout << "Queue is empty" << endl;
                        return E();
                }

                Node<E>* oldHead = head;
                E value = oldHead->value;

                head = head->next;
                if (head == nullptr) {
                        tail = nullptr;
                }

                delete oldHead;
                return value;
        }

        SafeQueue(const SafeQueue& other) {
                head = nullptr;
                tail = nullptr;

                Node<E>* current = other.head;
                while (current != nullptr) {
                        enqueue(current->value);
                        current = current->next;
                }
        }

        SafeQueue& operator=(const SafeQueue& other) {
                if (this != &other) {
                        clear();
                        Node<E>* current = other.head;
                        while (current != nullptr) {
                                enqueue(current->value);
                                current = current->next;
                        }
                }
                return *this;
        }
};

int main() {
        SafeQueue<string> words;
        bool quit = false;
        while (!quit) {
                string cmd = "quit";
                cin >> cmd;
                if (cmd == "enqueue") {
                        string x;
                        cin >> x;
                        words.enqueue(x);
                }
                else if (cmd == "dequeue") {
                        string x = words.dequeue();
                        cout << "Dequeue returned '" << x << "'" << endl;
                }
                else if (cmd == "quit") {
                        quit = true;
                }
        }
        cout << "Goodbye!" << endl;
        return 0;
}
