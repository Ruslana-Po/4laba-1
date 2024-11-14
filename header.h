#include <iostream>
#include <thread>
#include <vector>
#include <random>
#include <chrono>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <barrier>
using namespace std;


void mutexFunc(int num_threads, vector<thread>& threads);

void Semap(int num_threads, vector<thread>& threads);

class Semaphore {
public:
    Semaphore(int guess = 0) : count(guess) {}

    //уменьшает счетчик семафора, блокируя поток, если счетчик равен нулю
    void acquire() {
        //блокирует поток и добавляет его в очередь
        unique_lock<mutex> lock(mtx);
        //пока не выполниться потомок
        syncрPrimitive.wait(lock, [this]() { return count > 0; });
        --count;
    }

    //увеличивает счетчик семафора и уведомляет ожидающие потоки.
    void release() {
        unique_lock<mutex> lock(mtx);
        ++count;
        //Разблокирует один из потоков
        syncрPrimitive.notify_one();
    }

private:
    mutex mtx;
    //примитив синхронизации, который работает поверх mutex 
    condition_variable syncрPrimitive;
    int count;
};

void Slim(int num_threads, vector<thread>& threads);

class SemaphoreSlim {
public:
    SemaphoreSlim(int initialCount = 0, int maxCount = 1) 
        : count(initialCount), max(maxCount) {}

    void acquire() {
        unique_lock<mutex> lock(mtx);
        synPrim.wait(lock, [this]() { return count > 0; });
        --count;
    }

    void release() {
        unique_lock<mutex> lock(mtx);
        if (count < max) {
            count++;
            synPrim.notify_one();
        }
    }

private:
    mutex mtx;
    condition_variable synPrim;
    int count;
    int max;
};

void Bar(int numThreads, vector<thread>& threads);


void Spin(int numThreads, vector<thread>& threads);
class SpinLock {
public:
    SpinLock() : znach(false) {}

    void lock() {
        bool expected = false;
        //memory_order_acquire гарантирует, что ни одна операция чтения не будет перемещена до текущей операции чтения.
        while (!znach.compare_exchange_strong(expected, true, memory_order_acquire)) {
            expected = false;
        }
    }

    void unlock() {
        //присваивания значения в атомарную операцию
        //memory_order_release: гарантирует, что ни одна операция записи не будет перемещена после текущей операции.
        znach.store(false, memory_order_release);
    }

private:
    atomic<bool> znach;
};


void SpinWa(int numThreads, vector<thread>& threads);
class SpinWait {
public:
    SpinWait() : znach(false) {}

    void lock() {
        //Назначает новое значение объекту и возвращает его старое значение
        while (znach.exchange(true, memory_order_acquire)) {
            //циклы ожидания
            this_thread::sleep_for(chrono::microseconds(10));
        }
    }

    void unlock() {
        znach.store(false, memory_order_release);
    }

private:
    atomic<bool> znach;
};

void Monit(int numThreads, vector<thread>& threads);
class Monitor {
public:
    Monitor() : znach(false) {}

    void lock() {
        unique_lock<mutex> lock(mtx);
        while (znach) {
            synPrim.wait(lock);
        }
        znach = true;
    }

    void unlock() {
        unique_lock<mutex> lock(mtx);
        znach = false;
        synPrim.notify_one();
    }

private:
    mutex mtx;
    condition_variable synPrim;
    bool znach;
};
