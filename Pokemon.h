#pragma once
#include <string>
#include <iostream>

class Pokemon {
private:
    std::string m_name;
    int m_maxHP;
    int m_currentHP;
    int m_attack;
    int m_defense;
    int m_spAttack;
    int m_spDefense;
    int m_speed;
    bool m_isActive;

public:
    Pokemon(const std::string& pokemonName);
    virtual ~Pokemon() {}

    virtual int CalculateDamage(int moveType, const Pokemon& target) const = 0;
    virtual void UseMove(int moveIndex, Pokemon& target) = 0;
    virtual std::string GetMoveDescription(int moveIndex) const = 0;

    std::string GetName() const { return m_name; }
    int GetCurrentHP() const { return m_currentHP; }
    int GetMaxHP() const { return m_maxHP; }
    int GetAttack() const { return m_attack; }
    int GetDefense() const { return m_defense; }
    int GetSpeed() const { return m_speed; }
    bool GetIsActive() const { return m_isActive; }

    void TakeDamage(int damage);
    void Heal(int amount);
    void SetStats(int hp, int atk, int def, int spatk, int spdef, int spd);
    bool IsFainted() const { return m_currentHP <= 0; }
    void SetActive(bool active) { m_isActive = active; }
};

class PlayerPokemon : public Pokemon {
private:
    int m_attackBoost;

public:
    PlayerPokemon(const std::string& pokemonName);

    int CalculateDamage(int moveType, const Pokemon& target) const override;
    void UseMove(int moveIndex, Pokemon& target) override;
    std::string GetMoveDescription(int moveIndex) const override;

    void BoostAttack();
    void CounterAttack(Pokemon& target);
};

class EnemyPokemon : public Pokemon {
private:
    int m_difficultyLevel;

public:
    EnemyPokemon(const std::string& pokemonName, int difficulty);

    int CalculateDamage(int moveType, const Pokemon& target) const override;
    void UseMove(int moveIndex, Pokemon& target) override;
    std::string GetMoveDescription(int moveIndex) const override;

    int SelectMove() const;
    void ScaleWithDifficulty();
};