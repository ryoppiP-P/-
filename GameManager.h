#pragma once
#include "PokemonCenter.h"
#include "BattleSystem.h"

class GameManager {
private:
    PokemonCenter* m_pPokemonCenter;
    BattleSystem* m_pBattleSystem;
    int m_difficultyLevel;

public:
    GameManager();
    ~GameManager();

    void Run();

private:
    void ShowTitle();
    void SelectDifficulty();
    void ShowStory();
    void StartBattle();
};