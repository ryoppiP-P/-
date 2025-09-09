#include "GameManager.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <Windows.h>
#include <cmath>

using namespace std;

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    GameManager* pGameManager = new GameManager();
    pGameManager->Run();
    delete pGameManager;

    return 0;
}