#include "header.h"

mutex bm;
void BarFunc(int id) {
    // Инициализация генератора случайных чисел
    random_device rd;
    mt19937 gen(rd());
    // Диапазон ASCII символов от 32 до 126
    uniform_int_distribution<> dis(32, 126); 
    // Генерация случайной строки
    string random_string;
    random_string += static_cast<char>(dis(gen));
     // Ожидание всех потоков на барьере
    this_thread::sleep_for(chrono::milliseconds(200));
    bm.lock();
    cout << "Thread " << id << ": " << random_string << endl;
    bm.unlock();
}

void Bar(int numThreads, vector<thread>& threads){

    // Создание и запуск потоков
    for (int i = 0; i < numThreads; ++i) {
       threads.emplace_back(BarFunc, i);
    }
}
