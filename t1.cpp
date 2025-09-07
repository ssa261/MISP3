#include <memory>
#include <utility>

using namespace std;

template <typename T>
class Fl {
    struct Node {
        unique_ptr<T> data;
        unique_ptr<Node> next;
    };
    unique_ptr<Node> start;
    
public:
    Fl() {
        start = nullptr;
    }
    
    Fl(const T& x) {
        start = make_unique<Node>();
        start->data = make_unique<T>(x);
    }
    
    Fl(T&& x) {
        start = make_unique<Node>();
        start->data = make_unique<T>(std::move(x));
    }
    
    ~Fl() = default;
    
    void pushFront(const T& x) {
        unique_ptr<Node> newNode = make_unique<Node>();
        newNode->data = make_unique<T>(x);
        newNode->next = std::move(start);
        start = std::move(newNode);
    }
    
    void popFront() {
        if (start) {
            start = std::move(start->next);
        }
    }
    
    bool empty() const {
        return start == nullptr;
    }
    
    const T& front() const {
        return *(start->data);
    }
};
