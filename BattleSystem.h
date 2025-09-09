#pragma once
#include "Pokemon.h"
#include <string>

class BattleSystem {
private:
    PlayerPokemon* m_pPlayer;
    EnemyPokemon* m_pEnemy;
    bool m_battleEnded;

    static constexpr double TURUGI_NO_MAI = 1.1;
    static const char POKEMON_WAZA[4][256];

    int m_playerAtkPlus;
    int m_enemyAtkPlus;
    int m_damage;
    int m_playerCmd;
    int m_enemyCmd;

public:
    BattleSystem();
    ~BattleSystem();

    void InitializeBattle(PlayerPokemon* playerPokemon, int difficulty);
    bool ExecuteTurn(int playerMove);
    void DisplayBattleStatus() const;
    bool IsBattleEnded() const { return m_battleEnded; }

private:
    void p1_Waza(PlayerPokemon* p1);
    void p2_Waza(EnemyPokemon* p2);
    void sikasi();
    void turugi(PlayerPokemon* p1);
    void en_turugi(EnemyPokemon* p2);
    int Damage(PlayerPokemon* p1, EnemyPokemon* p2);
    int En_Damage(EnemyPokemon* p1, PlayerPokemon* p2);
    void Damage_hyouzi(PlayerPokemon* attacker, Pokemon* target);
    void En_Damage_hyouzi(EnemyPokemon* attacker, Pokemon* target);
    bool finCheak(PlayerPokemon* p1, EnemyPokemon* p2);
};