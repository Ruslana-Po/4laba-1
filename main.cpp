#include "header.h"
 
int main() {
    // Количество потоков
    int numberThr = 10; 

    cout<<"Выберете каким примитивов воспользуетесь: "<<endl;
    cout<<"1 - Mutexes\n";
    cout<<"2 - Semaphore\n";
    cout<<"3 - SemaphoreSlim\n";
    cout<<"4 - Barrier\n";
    cout<<"5 - SpinLock\n";
    cout<<"6 - SpinWait\n";
    cout<<"7 - Monitor\n";

    int number ;
    cin>> number;
    //все потоки
    vector<thread> threads;
    
    auto start = chrono::high_resolution_clock::now();
    if(number==1){
        mutexFunc(numberThr, threads);
    }else if(number==2){
        Semap(numberThr, threads);
    }else if(number==3){
        Slim(numberThr, threads);
    }else if(number==4){
       Bar(numberThr, threads);
    }else if(number==5){
       Spin(numberThr, threads);
    }else if(number==6){
       SpinWa(numberThr, threads);
    }else if(number==7){
       Monit(numberThr, threads);
    }
    
    // Ожидание завершения всех потоков
    for (auto& th : threads) {
        th.join();
    }
     auto end = chrono::high_resolution_clock::now();
      chrono::duration<double> result = end - start;
     cout<<"Time "<<result.count()<<" s."<<endl;
    return 0;
}
