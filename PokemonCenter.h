#pragma once
#include "Pokemon.h"
#include <conio.h>

class PokemonCenter {
private:
    PlayerPokemon* m_pPokemonParty[5];
    
public:
    static constexpr int PARTY_MAX = 5;
    static constexpr int QUIZ_MAX = 30;
    
    PokemonCenter();
    ~PokemonCenter();
    
    bool CreatePokemon();
    void DisplayPokemonList() const;
    void ViewPokemonDetails(int index) const;
    bool ReleasePokemon(int index);
    PlayerPokemon* SelectPokemonForBattle();
    void ShowMainMenu();
    
    int GetPartySize() const;
    bool IsPartyFull() const;
    
private:
    std::string GetRandomPokemonName() const;
    void GenerateRandomStats(PlayerPokemon& pokemon);
    int Seikaku(int Ikumon, std::string Mondai, std::string Sentakusi1, std::string Sentakusi2, int Rand);
    int FindEmptySlot() const;
};