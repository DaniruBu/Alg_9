#include <iostream>
#include <stdio.h> 
#include <vector>
#include <queue>
#include <unordered_map>


using namespace std;

// Проверяет, предпочитает ли женщина нового кандидата своему текущему партнеру
bool prefersNewCandidate(const vector<vector<int>>& womenPrefs, int woman, int newMan, int currentMan) {
    for (int man : womenPrefs[woman]) {
        if (man == newMan) return true;  // Новый мужчина предпочтительнее
        if (man == currentMan) return false;  // Текущий мужчина предпочтительнее
    }
    return false;  // Этот случай не должен происходить
}

// Реализация алгоритма Гейла — Шепли для нахождения стабильных пар
vector<int> stableMatching(int n, const vector<vector<int>>& menPrefs, const vector<vector<int>>& womenPrefs) {
    vector<int> womenPartners(n, -1); // Хранит текущих партнеров женщин (-1 = свободна)
    vector<bool> freeMen(n, true);    // Отслеживает, какие мужчины свободны
    queue<int> freeMenQueue;          // Очередь свободных мужчин

    // Изначально все мужчины свободны
    for (int i = 0; i < n; i++) {
        freeMenQueue.push(i);
    }

    // Пока есть свободные мужчины
    while (!freeMenQueue.empty()) {
        int man = freeMenQueue.front(); // Берем свободного мужчину из очереди
        freeMenQueue.pop();

        // Мужчина делает предложения женщинам по порядку
        for (int woman : menPrefs[man]) {
            if (womenPartners[woman] == -1) {
                // Женщина свободна, принимает предложение
                womenPartners[woman] = man;
                freeMen[man] = false; // Мужчина теперь занят
                break;
            } else {
                int currentMan = womenPartners[woman];
                // Женщина сравнивает нового и текущего партнера
                if (prefersNewCandidate(womenPrefs, woman, man, currentMan)) {
                    // Женщина предпочитает нового мужчину
                    womenPartners[woman] = man;
                    freeMen[man] = false;
                    freeMen[currentMan] = true; // Текущий мужчина становится свободным
                    freeMenQueue.push(currentMan); // Вернуть его в очередь
                    break;
                }
            }
        }
    }

    // Возвращает массив партнеров женщин (женщина -> мужчина)
    return womenPartners;
}

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8"); // Это для рус. языка
    int n = 6; // Количество мужчин и женщин

    // Предпочтения мужчин (индексы женщин)
    vector<vector<int>> menPrefs = {
        {2, 4, 0, 5, 1, 3},  // M1
        {3, 0, 4, 1, 2, 5},  // M2
        {0, 5, 3, 2, 4, 1},  // M3
        {5, 1, 4, 3, 0, 2},  // M4
        {1, 2, 5, 0, 3, 4},  // M5
        {4, 3, 2, 5, 1, 0}   // M6
    };

    // Предпочтения женщин (индексы мужчин)
    vector<vector<int>> womenPrefs = {
        {2, 1, 5, 0, 4, 3},  // W1
        {3, 4, 0, 1, 2, 5},  // W2
        {0, 4, 3, 5, 1, 2},  // W3
        {1, 5, 2, 3, 0, 4},  // W4
        {5, 0, 1, 4, 2, 3},  // W5
        {3, 2, 4, 0, 5, 1}   // W6
    };

    // Выполняем алгоритм и получаем пары
    vector<int> result = stableMatching(n, menPrefs, womenPrefs);

    // Выводим стабильные пары
    cout << "Стабильные пары (женщина -> мужчина):" << endl;
    for (int i = 0; i < n; i++) {
        cout << "W" << i + 1 << " -> M" << result[i] + 1 << endl;
    }

    return 0;
}
