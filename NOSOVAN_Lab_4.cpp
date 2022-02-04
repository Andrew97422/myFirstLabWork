#include <iostream>
#include <fstream>


using namespace std;
void readMassive(int *, int);
void createMassive(int*, int*, int);
int countUniqueElements(int*, int);
void createRandomMassiv(int*, int);
int minValue = 2147483647; /* Минимальное значение элемента исходного целочисленного массива. Инициализация переменной */
int maxValue = -2147483648; /* Максимальное значение элемента исходного целочисленного массива. Инициализация переменной */

int main()
{
    /*Обьявляем переменные в зоне видимости main функции */
    ifstream inputStreamFile("INPUT.txt");
    ofstream outputStreamFile("OUTPUT.txt");    
    int massiveLength = 0; /* Длина исходного массива Инициализация переменной*/
    int choice = 0; /* выбор пользователя варианта ввода данных*/
    /* Переменные объявлены и инициализированы */
    do {
        cout << endl;
        cout << "Please make your choice:" << endl;
        cout << endl;
        cout << "1. Read from file" << endl;
        cout << "2. Random enter" << endl;
        cout << "3. Exit" << endl;
        cout << endl;

        cin >> choice;
        if ((choice != 1) && (choice != 2) && (choice != 3)) {
            cout << endl;
            cout << "It's not correct choice. Choose between 1, 2, 3";  
            cout << endl;
            continue;
        }

        /* выбор сделан, начинаем действовать */

        switch (choice) {
        case 1: { /* вариант заполнения массива из файла */
                    outputStreamFile << endl;
                    outputStreamFile << "Choice is file" << endl << endl;
                    
                    /* Узнаём количество элементов массива */
                    inputStreamFile >> massiveLength;
                    outputStreamFile << "We have an " << massiveLength << " elements of massive" << endl << endl;
                    
                    /* создаем динамический массив */
                    int* inputMassive = new int[massiveLength];
                    
                    /* вызываем функцию наполнение массива*/
                    readMassive(inputMassive, massiveLength);                    
                    outputStreamFile << endl << "Minimal value is: " << minValue << endl << ' ' << "Maximum value is: " << maxValue << endl << endl;
                                                       
                    /* Считаем количество элементов нового массива */
                    int newMassiveCounter = 0; /* объявление и инициализация */
                    newMassiveCounter = (maxValue - minValue) - massiveLength - countUniqueElements(inputMassive, massiveLength) + 1;
                   
                    /* Создаём новый массив */
                    int* newMassive = new int[newMassiveCounter];
                    createMassive(newMassive, inputMassive, massiveLength);
                    outputStreamFile << "New massiv:" << endl;
                    for (int i = 0; i < newMassiveCounter; i++) {
                        outputStreamFile << newMassive[i] << "  ";
                    }
                    break;

                    
                  }
        case 2: { /* вариант заполнения массива случайными числами */
                    
                    outputStreamFile << endl;
                    outputStreamFile << "Choice is random" << endl << endl;

                    /* Узнаём количество элементов массива */
                    int randomMassiveLength = 1 + rand()%1000;
                    outputStreamFile << "We have an " << randomMassiveLength << " elements of massive" << endl << endl;

                    /* создаем динамический массив */
                    int* randomMassive = new int[randomMassiveLength];
                    
                    /* вызываем функцию наполнение массива*/
                    createRandomMassiv(randomMassive, randomMassiveLength);
                    outputStreamFile << endl << "Minimal value is: " << minValue << endl << "Maximum value is: " << maxValue << endl << endl;
                    
                    /* Считаем количество элементов нового массива */
                    int newMassiveCounter = 0; /* объявление и инициализация */
                    newMassiveCounter = (maxValue - minValue) - randomMassiveLength - countUniqueElements(randomMassive, randomMassiveLength) + 1;
                    
                    /* Создаём новый массив */
                    int* newMassive = new int[newMassiveCounter];
                    createMassive(newMassive, randomMassive, randomMassiveLength);
                    outputStreamFile << "New massiv counter" << endl;
                    outputStreamFile << "New massiv:" << newMassiveCounter << endl;
                    for (int i = 0; i < newMassiveCounter; i++) {
                        outputStreamFile << newMassive[i] << "  ";
                    }

                    break;                                       
                }
              
        }

    } while (choice != 3);

    outputStreamFile << endl;
    outputStreamFile << "Success exit";
    outputStreamFile << endl;
    cout << "Success exit" << endl;

  
    return 0;
}

void readMassive(int* inputMassive, int massiveLength) {
    ifstream inputStreamFile("INPUT.txt");
    int readingValue = 0; /* временная переменная */
    inputStreamFile >> readingValue; /* Читаем и игнорируем длину массива, поскольку она нам известна*/
    for (int i = 0; i < massiveLength; i++) {
        inputStreamFile >> readingValue;
        inputMassive[i] = readingValue;
        if (readingValue < minValue) minValue = readingValue;
        if (readingValue > maxValue) maxValue = readingValue;
        
    }
    return;
}

int countUniqueElements(int* inputMassive, int massiveLength) {
    int count = 0;
    for (int i = 0; i < massiveLength - 1; i++) {
        for (int j = i + 1; j < massiveLength; j++) {
            if (inputMassive[i] > inputMassive[j]) {
                int x = inputMassive[j];
                inputMassive[j] = inputMassive[i];
                inputMassive[i] = x;
            }
        }
    }
    for (int i = 0; i < massiveLength - 1; i++) { 
        if (inputMassive[i] == inputMassive[i + 1])  count++;
    }
    return count;
}

void createMassive(int* newMassive, int* inputMassive, int massiveLength) {
    int index = 0;
    bool flag = false;
    for (int i = maxValue - 1; i > minValue; i--) {
       
    /* Проверяем на наличие числа в массиве */
        for (int k = 0; k < massiveLength; k++) {
            if (inputMassive[k] == i) flag = true;
        }
    /* Если значение не попадалось в массиве (flag = 0) заносим значение в новый массив */
        if (not flag) {
            newMassive[index] = i;
            index++;
        }
        else flag = false;
    }
    return;
}

void createRandomMassiv(int* randomMassive, int randomMassiveLength) {
    for (int i = 0; i < randomMassiveLength; i++) {
        int randomNumber = 1 + rand() % 100;
        int randomSign = rand() % 2;
        if (randomSign == 0) randomNumber = -randomNumber;
        randomMassive[i] = randomNumber;
        if (randomNumber < minValue) minValue = randomNumber;
        if (randomNumber > maxValue) maxValue = randomNumber;
    }
    return;
}