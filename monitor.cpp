#include "header.h"
Monitor monitor;


void MonitorFunc(int id) {
    // Инициализация генератора случайных чисел
    random_device rd;
    mt19937 gen(rd());
    // Диапазон ASCII символов от 32 до 126
    uniform_int_distribution<> dis(32, 126); 
    // Генерация случайной строки
    string random_string;
    random_string += static_cast<char>(dis(gen));

    monitor.lock();
    cout << "Thread " << id << ": " << random_string << endl;
    monitor.unlock();
}

void Monit(int numThreads, vector<thread>& threads){
    // Создание и запуск потоков
    for (int i = 0; i < numThreads; ++i) {
        threads.emplace_back(MonitorFunc, i);
    }
}
