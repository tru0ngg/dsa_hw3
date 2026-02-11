#include <iostream>
#include <cassert>
#include <string>
using namespace std;

template <class E>
struct Node {
    E value;
    Node<E>* next;
    Node(E v, Node* n) {
        value = v;
        next = n;
    }
};

template <class E>
class LinkedStack {
    private:
    Node<E>* head;
    int m_count;

    public:
    LinkedStack() {
        head = nullptr;
        m_count = 0;
    }

    ~LinkedStack() {
        Node<E>* current = head;
        while (current != nullptr) {
            Node<E>* todelete = current;
            current = current->next;
            delete todelete;
        }
    }

    void push(E x) {
        Node<E>* old_head = head;
        head = new Node<E>(x, old_head);
        m_count++;
    }

    E pop() {
        Node<E>* old_head = head;
        assert(head != nullptr);
        head = head->next;
        E ret = old_head->value;
        delete old_head;
        m_count--;
        return ret;
    }

    int count() {
        return m_count;
    }

    bool is_empty() {
        return (head == nullptr);
    }

    E peek() {
            assert(head != nullptr);
            return head->value;
    }
};

bool is_operator(string t){
        return (t == "+" or t == "-" or t == "/" or t == "*");
}

int operators_preced(const string& op){
        if (op == "*" or op == "/"){
                return 2;
        }
        if (op == "+" or op == "-"){
                return 1;
        }
        return 0;
}

int main(){
        string token;
        LinkedStack<string> post;
        while (cin >> token and token != "="){
                if (!is_operator(token)){
                        cout << token << " ";
                }
                else {
                        while (!post.is_empty() and operators_preced(post.peek()) >= operators_preced(token)){
                                cout << post.pop() << " ";
                        }
                        post.push(token);
                }
        }
        while (!post.is_empty()){
                cout << post.pop() << " ";
        }
        cout << endl;
        return 0;
}
