#pragma once
template <typename T>
class CustomStack {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& data, Node* next = nullptr) : data(data), next(next) {}
    };
    Node* topNode; ///< Pointer to the top of the stack

public:
    CustomStack() : topNode(nullptr) {}

    ~CustomStack() {
        while (!empty()) {
            pop();
        }
    }

    void push(const T& value) {
        topNode = new Node(value, topNode);
    }

    void pop() {
        if (topNode) {
            Node* temp = topNode;
            topNode = topNode->next;
            delete temp;
        }
    }

    T top() const {
        if (!topNode) {
            throw std::runtime_error("Stack is empty");
        }
        return topNode->data;
    }

    bool empty() const {
        return topNode == nullptr;
    }
};

template <typename T>
class CustomQueue {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& data, Node* next = nullptr) : data(data), next(next) {}
    };
    Node* frontNode; ///< Pointer to the front of the queue
    Node* rearNode;  ///< Pointer to the rear of the queue
    int count;      ///< Size of the queue
public:
    CustomQueue() : frontNode(nullptr), rearNode(nullptr), count(0) {}

    ~CustomQueue() {
        while (!empty()) {
            pop();
        }
    }

    void push(const T& value) {
        Node* newNode = new Node(value);
        if (rearNode) {
            rearNode->next = newNode;
        }
        else {
            frontNode = newNode;
        }
        rearNode = newNode;
        ++count; // Increment size
    }

    void pop() {
        if (!empty()) {
            Node* temp = frontNode;
            frontNode = temp->next;
            delete temp;
            --count; // Decrement size
            if (!frontNode) {
                rearNode = nullptr; // If queue is empty, reset rear pointer
            }
        }
    }

    T front() const {
        if (!frontNode) {
            throw std::runtime_error("Queue is empty");
        }
        return frontNode->data;
    }

    bool empty() const {
        return frontNode == nullptr;
    }

    int size() const {
        return count;
    }

    CustomQueue(const CustomQueue& other) : frontNode(nullptr), rearNode(nullptr), count(0) {
        Node* current = other.frontNode;
        while (current) {
            push(current->data); // Use `push` to add elements to the new queue
            current = current->next;
        }
    }

    CustomQueue& operator=(const CustomQueue& other) {
        if (this != &other) {
            while (!empty()) {
                pop(); // Clear the current queue
            }
            Node* current = other.frontNode;
            while (current) {
                push(current->data); // Copy elements
                current = current->next;
            }
        }
        return *this;
    }
};

