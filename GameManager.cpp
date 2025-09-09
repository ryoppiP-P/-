#include "GameManager.h"
#include <iostream>
#include <Windows.h>
#include <iomanip>

using namespace std;

GameManager::GameManager() : m_difficultyLevel(3) {
    m_pPokemonCenter = new PokemonCenter();
    m_pBattleSystem = new BattleSystem();
}

GameManager::~GameManager() {
    delete m_pPokemonCenter;
    delete m_pBattleSystem;
}

void GameManager::Run() {
    ShowTitle();
    SelectDifficulty();
    ShowStory();
    m_pPokemonCenter->ShowMainMenu();
    StartBattle();

    cout << "Enterでゲームを終了します";
    cin.ignore();
    cin.get();
}

void GameManager::ShowTitle() {
    system("cls");

    int title[25][80] = {
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
        {0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
        {0,0,0,0,0,0,1,1,1,1,1,1,2,2,1,1,1,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,},
        {0,0,0,0,0,0,1,1,2,2,1,1,2,2,1,1,1,2,2,2,1,1,1,1,1,1,1,1,1,2,2,1,1,0,0,1,1,2,2,2,2,2,2,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,1,2,2,2,2,2,2,2,1,1,0,0,0,0,0,0,0,0,0,0,},
        {0,0,1,1,1,1,1,1,2,2,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,1,1,1,2,2,1,1,0,0,1,1,1,1,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,1,1,2,2,1,1,1,2,2,1,1,0,0,0,0,0,0,0,0,0,0,},
        {0,0,1,1,2,2,2,2,2,2,2,2,2,2,1,2,2,1,1,1,1,2,2,1,1,1,1,1,1,2,2,1,1,1,1,1,1,1,1,2,2,1,1,1,1,1,2,2,1,1,1,1,2,2,1,1,2,2,1,1,2,2,2,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,0,},
        {0,0,1,1,1,1,1,1,2,2,1,1,1,1,1,1,1,1,1,1,1,2,2,1,1,1,1,1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,2,2,2,1,1,2,2,1,1,2,2,1,1,2,2,1,1,1,2,2,1,1,1,2,2,1,1,2,2,2,2,2,2,2,2,1,1,0,}
    };

    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 80; j++) {
            if (title[i][j] == 0) {
                cout << "\x1b[48;2;255;255;255m \x1b[0m";
            } else if (title[i][j] == 1) {
                cout << "\x1b[48;2;38;92;167m \x1b[0m";
            } else if (title[i][j] == 2) {
                cout << "\x1b[48;2;249;207;1m \x1b[0m";
            }
        }
        cout << "\n";
    }

    cout << "\n\x1b[38;2;255;255;0m★ オブジェクト指向リメイク版 ★\x1b[0m\n";
    cout << "Enterキーを押してください...";
    cin.ignore();
    cin.get();
}

void GameManager::SelectDifficulty() {
    system("cls");
    int choice = 0;

    while (choice == 0) {
        cout << "ゲームの難易度を選択してください\n\n\n";
        cout << "　　１：\x1b[38;2;0;232;243mかんたん\x1b[0m" << setw(19) << "２：ふつう\n\n";
        cout << "　　３：\x1b[38;2;12;146;25mむずかしい\x1b[0m" << setw(40) << "４：\x1b[38;2;255;0;0m地獄\x1b[0m\n\n";
        cout << ">>";
        cin >> choice;

        switch (choice) {
        case 1: m_difficultyLevel = 3; break;
        case 2: m_difficultyLevel = 6; break;
        case 3: m_difficultyLevel = 8; break;
        case 4: m_difficultyLevel = 13; break;
        default:
            cout << "誤入力。１～４の値を入力してください。\n";
            choice = 0;
        }
    }
}

void GameManager::ShowStory() {
    system("cls");

    string story1 = "昔は　\x1b[38;2;117;0;255m魔王の国で\x1b[0m　\x1b[38;2;255;0;0mサカキ\x1b[0mにより　支配されている\n";
    for (char c : story1) {
        cout << c << flush;
        Sleep(20);
    }
    Sleep(500);

    string story2 = "\x1b[38;2;255;0;0mサカキ\x1b[0mを　倒すべく　君は　■ポケモンセンターへと　やってきた\n";
    for (char c : story2) {
        cout << c << flush;
        Sleep(20);
    }
    Sleep(1000);

    cin.ignore();
    cin.get();
}

void GameManager::StartBattle() {
    PlayerPokemon* battlePokemon = m_pPokemonCenter->SelectPokemonForBattle();
    if (battlePokemon == nullptr) {
        cout << "ポケモンが選択されませんでした。\n";
        return;
    }

    m_pBattleSystem->InitializeBattle(battlePokemon, m_difficultyLevel);

    system("cls");

    bool battleEnded = false;
    do {
        m_pBattleSystem->DisplayBattleStatus();

        int playerMove;
        cin >> playerMove;

        if (playerMove >= 1 && playerMove <= 4) {
            battleEnded = m_pBattleSystem->ExecuteTurn(playerMove);
        } else {
            cout << "誤入力。１～４を入力してください。\n";
            cin.ignore();
            cin.get();
            continue;
        }

    } while (!battleEnded);

    cin.ignore();
    cin.get();
}