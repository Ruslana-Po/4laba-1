#include "header.h"
SemaphoreSlim slimm(1, 1);

void SemaphoreSlimFunc(int id) {
    // Инициализация генератора случайных чисел
    random_device rd;
    mt19937 gen(rd());
    // Диапазон ASCII символов от 32 до 126
    uniform_int_distribution<> dis(32, 126); 
    // Генерация случайной строки
    string random_string;
    random_string += static_cast<char>(dis(gen));

    slimm.acquire();
    cout << "Thread " << id << ": " << random_string << endl;
    slimm.release();
}

void Slim(int numThreads, vector<thread>& threads){
    // Создание и запуск потоков
    for (int i = 0; i < numThreads; ++i) {
        threads.emplace_back(SemaphoreSlimFunc, i);
    }
}
