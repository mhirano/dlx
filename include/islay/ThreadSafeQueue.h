//
// Created by Hirano Masahiro <masahiro.dll@gmail.com>
//

#ifndef THREADSAFEQUEUE_H
#define THREADSAFEQUEUE_H

#include <exception>

//std::mutex stdout_m; // std::cout の排他制御
//template <typename T>
//void ThreadSafePrint(T v) {
//    std::lock_guard<std::mutex> lock(stdout_m);
//    std::cout << v << std::endl;
//}


class EmptyQueue : std::exception {
public:
    const char* what() const throw() {
        return "Queue is empty";
    }
};

template <typename T>
class ThreadSafeQueue {
public:
    ThreadSafeQueue() {}
    ThreadSafeQueue(ThreadSafeQueue const& other) {
        std::lock_guard<std::mutex> lock(other.m);
        que = other.que;
    }
    ThreadSafeQueue& operator=(ThreadSafeQueue const&) = delete;

    void push(T value) {
        std::lock_guard<std::mutex> lock(m);
        que.push(value);
    }

    void pop(T& res) {
        std::lock_guard<std::mutex> lock(m);
        if(que.empty()) throw EmptyQueue();
        res = que.front();
        que.pop();
    }
    std::shared_ptr<T> pop() {
        std::lock_guard<std::mutex> lock(m);
        if(que.empty()) throw EmptyQueue();
        auto const res = std::make_shared<T>(que.front());
        que.pop();
        return res;
    }

    bool empty() const {
        std::lock_guard<std::mutex> lock(m);
        return que.empty();
    }

    size_t size() const {
        std::lock_guard<std::mutex> lock(m);
        return que.size();
    }

private:
    std::queue<T> que;
    mutable std::mutex m;
};


#endif //THREADSAFEQUEUE_H
