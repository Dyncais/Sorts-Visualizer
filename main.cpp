#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <ctime>
#include <vector>
#include <algorithm>
#include <random>
#include "raylib.h"
#include <thread> 
#include <functional>
#include <atomic>



class Vector
{
    private:
        std::vector<int> DataBase;
    public:

    Vector() = default;

    Vector (const Vector &vector)
    {
        DataBase = vector.DataBase;
    }

    operator std::vector<int>() const {
        return DataBase;
    }

    const int& operator[](size_t index) const {
        if (index >= DataBase.size()) {
            throw std::out_of_range("Индекс выходит за пределы вектора");
        }
        return DataBase[index];
    }

    void CreateWorkVector()
    {
        DataBase.clear();
        for (int i = 1; i <= 30; ++i) {
            DataBase.push_back(i);
        }
        std::random_device rd; 
        std::mt19937 gen(rd()); 
        std::shuffle(DataBase.begin(), DataBase.end(), gen);
        return;
    }
    
    void Bubble() {
    for (int i = 0; i < DataBase.size(); i++) {
        for (int j = 0; j < DataBase.size() - i - 1; j++) {
            if (DataBase[j] > DataBase[j + 1])
                std::swap(DataBase[j], DataBase[j + 1]);

            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }
}

    void Selection() {
        int start_index = 0;
        while (start_index < DataBase.size()) {
            int min_index = start_index;
            for (int i = start_index + 1; i < DataBase.size(); i++) {
                if (DataBase[i] < DataBase[min_index]) {
                    min_index = i;
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
            }
            std::swap(DataBase[start_index], DataBase[min_index]);
            start_index++;
        }
    }

    void Quicksort(int left = 0, int right = -1) {
        if (right == -1) {
            right = DataBase.size() - 1;
        }

        if (left >= right) return;

        int i = left;
        int j = right;
        int pivot = DataBase[(left + right) / 2];

        do {
            while (DataBase[i] < pivot) {
                i++;
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
            }
            while (DataBase[j] > pivot) {
                j--;
                std::this_thread::sleep_for(std::chrono::milliseconds(10)); 
            }

            if (i <= j) {
                std::swap(DataBase[i], DataBase[j]);
                i++;
                j--;
            }
        } while (i <= j);

        if (left < j) Quicksort(left, j);
        if (i < right) Quicksort(i, right);
    }

    void HeapSort() {
        std::function<void(int, int)> heapify = [&](int n, int i) {
            int largest = i;
            int left = 2 * i + 1;
            int right = 2 * i + 2;

            if (left < n && DataBase[left] > DataBase[largest])
                largest = left;

            if (right < n && DataBase[right] > DataBase[largest])
                largest = right;

            if (largest != i) {
                std::swap(DataBase[i], DataBase[largest]);
                heapify(n, largest);

                std::this_thread::sleep_for(std::chrono::milliseconds(10));
            }
        };

        int n = DataBase.size();

        for (int i = n / 2 - 1; i >= 0; i--)
            heapify(n, i);

        for (int i = n - 1; i >= 0; i--) {
            std::swap(DataBase[0], DataBase[i]);
            heapify(i, 0);

            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }

    void Insertion() {
        for (size_t i = 1; i < DataBase.size(); i++) {
            int key = DataBase[i];
            int j = i - 1;

            while (j >= 0 && DataBase[j] > key) {
                DataBase[j + 1] = DataBase[j];
                j--;
                std::this_thread::sleep_for(std::chrono::milliseconds(10)); 
            }
            DataBase[j + 1] = key;
        }
    }

    void Merge() {
        auto merge = [&](int left, int mid, int right) {
            int n1 = mid - left + 1;
            int n2 = right - mid;

            std::vector<int> L(n1), R(n2);

            for (int i = 0; i < n1; i++)
                L[i] = DataBase[left + i];
            for (int j = 0; j < n2; j++)
                R[j] = DataBase[mid + 1 + j];

            int i = 0, j = 0, k = left;

            while (i < n1 && j < n2) {
                if (L[i] <= R[j]) {
                    DataBase[k] = L[i];
                    i++;
                } else {
                    DataBase[k] = R[j];
                    j++;
                }
                k++;
                std::this_thread::sleep_for(std::chrono::milliseconds(10)); 
            }

            while (i < n1) {
                DataBase[k] = L[i];
                i++;
                k++;
                std::this_thread::sleep_for(std::chrono::milliseconds(10)); 
            }

            while (j < n2) {
                DataBase[k] = R[j];
                j++;
                k++;
                std::this_thread::sleep_for(std::chrono::milliseconds(10)); 
            }
        };

        std::function<void(int, int)> mergeSort = [&](int left, int right) {
            if (left >= right) return;

            int mid = left + (right - left) / 2;
            mergeSort(left, mid);
            mergeSort(mid + 1, right);
            merge(left, mid, right);
        };

        mergeSort(0, DataBase.size() - 1);
    }

    const int size()
    {
        return DataBase.size();
    }
};



int main() 
{
    
    InitWindow(1280, 720, "Sortings");
    Vector bvector,svector, qvector, hvector, ivector, mvector;
    std::atomic<int> activeThreads(0);
    
    while (!WindowShouldClose())
    {
        Rectangle button = {300, 350, 200, 50}; 
        Rectangle button1 = {700, 350, 200, 50}; 
        Color buttonColor = LIGHTGRAY;
        Color buttonColor1 = LIGHTGRAY;

        if (CheckCollisionPointRec(GetMousePosition(), button)) {
            buttonColor = GRAY;
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) and activeThreads == 0) {
                buttonColor = DARKGRAY; 
                TraceLog(LOG_INFO, "Кнопка нажата!");
                bvector.CreateWorkVector();
                svector = qvector = hvector = ivector = mvector = bvector;
            }
        } else {
            buttonColor = LIGHTGRAY;
        }

        if (CheckCollisionPointRec(GetMousePosition(), button1)) {
            buttonColor1 = GRAY;
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) and activeThreads == 0)  {
                activeThreads += 6;

                std::thread bubblethread([&]() {
                bvector.Bubble();
                activeThreads--;
                });
                bubblethread.detach();

                std::thread selectthread([&]() {
                    svector.Selection();
                    activeThreads--;
                });
                selectthread.detach();

                std::thread quickthread([&]() {
                    qvector.Quicksort(0, -1);
                    activeThreads--;
                });
                quickthread.detach();

                std::thread hubblethread([&]() {
                    hvector.HeapSort();
                    activeThreads--;
                });
                hubblethread.detach();

                std::thread insertthread([&]() {
                    ivector.Insertion();
                    activeThreads--;
                });
                insertthread.detach();

                std::thread mergethread([&]() {
                    mvector.Merge();
                    activeThreads--;
                });
                mergethread.detach();

            }
                
        }


        BeginDrawing();
            
            ClearBackground(RAYWHITE);

            DrawRectangleLines(0, 0, 300, 300, BLACK);
            DrawText("Bubble",100, 310, 20, LIGHTGRAY);
            DrawRectangleLines(490, 0, 300, 300, BLACK);
            DrawText("Selection",590, 310, 20, LIGHTGRAY);
            DrawRectangleLines(980, 0, 300, 300, BLACK);
            DrawText("Quick",1080, 310, 20, LIGHTGRAY);

            DrawRectangleLines(0, 420, 300, 300, BLACK);
            DrawText("HeapSort",100, 400, 20, LIGHTGRAY);
            DrawRectangleLines(490, 420, 300, 300, BLACK);
            DrawText("Insertion",590, 400, 20, LIGHTGRAY);
            DrawRectangleLines(980, 420, 300, 300, BLACK);
            DrawText("Merge",1080, 400, 20, LIGHTGRAY);
            
            DrawRectangleRec(button, buttonColor);
            DrawText("Generate",340, 370, 20, BLUE);
            DrawRectangleRec(button1, buttonColor1);
            DrawText("Start",760, 370, 20, BLUE);
            

            for(int i = 0;i<bvector.size();i++)
            {
                DrawRectangle(10*i, 300 - bvector[i]*10, 10, bvector[i] * 10, RED);
                DrawRectangleLines(10*i, 300 - bvector[i]*10, 10, bvector[i] * 10, BLACK);
            
                DrawRectangle(490+10*i, 300 - svector[i]*10, 10, svector[i] * 10, RED);
                DrawRectangleLines(490+10*i, 300 - svector[i]*10, 10, svector[i] * 10, BLACK);

                DrawRectangle(980+10*i, 300 - qvector[i]*10, 10, qvector[i] * 10, RED);
                DrawRectangleLines(980+10*i, 300 - qvector[i]*10, 10, qvector[i] * 10, BLACK);
            
                DrawRectangle(10*i, 720 - hvector[i]*10, 10, hvector[i] * 10, RED);
                DrawRectangleLines(10*i, 720 - hvector[i]*10, 10, hvector[i] * 10, BLACK);
            
                DrawRectangle(490+10*i, 720 - ivector[i]*10, 10, ivector[i] * 10, RED);
                DrawRectangleLines(490+10*i, 720 - ivector[i]*10, 10, ivector[i] * 10, BLACK);
            
                DrawRectangle(980+10*i, 720 - mvector[i]*10, 10, mvector[i] * 10, RED);
                DrawRectangleLines(980+10*i, 720 - mvector[i]*10, 10, mvector[i] * 10, BLACK);
            }
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
