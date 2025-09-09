#include "Pokemon.h"
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

Pokemon::Pokemon(const std::string& pokemonName)
    : m_name(pokemonName), m_maxHP(0), m_currentHP(0), m_attack(0), m_defense(0),
    m_spAttack(0), m_spDefense(0), m_speed(0), m_isActive(false) {
}

void Pokemon::TakeDamage(int damage) {
    m_currentHP = m_currentHP - damage;
    if (m_currentHP < 0) m_currentHP = 0;
}

void Pokemon::Heal(int amount) {
    m_currentHP = m_currentHP + amount;
    if (m_currentHP > m_maxHP) m_currentHP = m_maxHP;

    cout << m_name << "��" << amount << "�񕜂����I\n";
}

void Pokemon::SetStats(int hp, int atk, int def, int spatk, int spdef, int spd) {
    m_maxHP = hp;
    m_currentHP = hp;
    m_attack = atk;
    m_defense = def;
    m_spAttack = spatk;
    m_spDefense = spdef;
    m_speed = spd;
    m_isActive = true;
}

PlayerPokemon::PlayerPokemon(const std::string& pokemonName)
    : Pokemon(pokemonName), m_attackBoost(0) {
}

int PlayerPokemon::CalculateDamage(int moveType, const Pokemon& target) const {
    // ���̊֐��͎g��Ȃ��iBattleSystem�Œ��ڌv�Z�j
    return 0;
}

void PlayerPokemon::UseMove(int moveIndex, Pokemon& target) {
    // ���̊֐��͎g��Ȃ��iBattleSystem�Œ��ڏ����j
}

std::string PlayerPokemon::GetMoveDescription(int moveIndex) const {
    // ���̊֐��͎g��Ȃ�
    return "";
}

void PlayerPokemon::BoostAttack() {
    // ���̊֐��͎g��Ȃ��iBattleSystem�Œ��ڏ����j
}

void PlayerPokemon::CounterAttack(Pokemon& target) {
    // ���̊֐��͎g��Ȃ�
}

EnemyPokemon::EnemyPokemon(const std::string& pokemonName, int difficulty)
    : Pokemon(pokemonName), m_difficultyLevel(difficulty) {
}

int EnemyPokemon::CalculateDamage(int moveType, const Pokemon& target) const {
    // ���̊֐��͎g��Ȃ��iBattleSystem�Œ��ڌv�Z�j
    return 0;
}

void EnemyPokemon::UseMove(int moveIndex, Pokemon& target) {
    // ���̊֐��͎g��Ȃ��iBattleSystem�Œ��ڏ����j
}

std::string EnemyPokemon::GetMoveDescription(int moveIndex) const {
    // ���̊֐��͎g��Ȃ�
    return "";
}

int EnemyPokemon::SelectMove() const {
    return (rand() % 4) + 1;
}

void EnemyPokemon::ScaleWithDifficulty() {
    static constexpr int HP_MAX = 500;
    static constexpr int ATK_MAX = 300;
    static constexpr int DEF_MAX = 300;
    static constexpr int SPATK_MAX = 300;
    static constexpr int SPDEF_MAX = 300;
    static constexpr int SPEED_MAX = 300;

    int hp = ((HP_MAX * m_difficultyLevel) / 10);
    int atk = ((ATK_MAX * m_difficultyLevel) / 10);
    int def = ((DEF_MAX * m_difficultyLevel) / 10);
    int spatk = ((SPATK_MAX * m_difficultyLevel) / 10);
    int spdef = ((SPDEF_MAX * m_difficultyLevel) / 10);
    int speed = ((SPEED_MAX * m_difficultyLevel) / 10);

    SetStats(hp, atk, def, spatk, spdef, speed);
}