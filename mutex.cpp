#include "header.h"
 // Глобальный мьютекс для синхронизации вывода
mutex mut;
// Функция, которая будет выполняться в каждом потоке
void thread_mutex(int id) {
    // Инициализация генератора случайных чисел
    random_device rd;
    mt19937 gen(rd());
    // Диапазон ASCII символов от 32 до 126
    uniform_int_distribution<> dis(32, 126); 

    // Генерация случайной строки
    string random_string;
    random_string += static_cast<char>(dis(gen));
    

    // Вывод строки с синхронизацией
    lock_guard<mutex> lock(mut);
    cout << "Thread " << id << ": " << random_string << endl;
}

void mutexFunc(int numThreads, vector<thread>& threads){
    // Создание и запуск потоков
    for (int i = 0; i < numThreads; ++i) {
        threads.emplace_back(thread_mutex, i);
    }
}
