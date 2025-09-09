#include "BattleSystem.h"
#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <cmath>

using namespace std;

const char BattleSystem::POKEMON_WAZA[4][256] = {
    "じしん",
    "カウンター",
    "つるぎのまい",
    "まもる",
};

BattleSystem::BattleSystem()
    : m_pPlayer(nullptr), m_pEnemy(nullptr), m_battleEnded(false),
    m_playerAtkPlus(0), m_enemyAtkPlus(0), m_damage(0), m_playerCmd(0), m_enemyCmd(0) {
}

BattleSystem::~BattleSystem() {
    delete m_pEnemy;
}

void BattleSystem::InitializeBattle(PlayerPokemon* playerPokemon, int difficulty) {
    m_pPlayer = playerPokemon;
    m_pEnemy = new EnemyPokemon("ミュウツー", difficulty);
    m_pEnemy->ScaleWithDifficulty();
    m_battleEnded = false;
    m_playerAtkPlus = 0;
    m_enemyAtkPlus = 0;

    cout << "\n=======【魔王の国　サカキ】と対戦=======\n\n";
    Sleep(800);
    cout << "サカキ「我が強さ！思い知れ！」\n\n";
    Sleep(800);
}

bool BattleSystem::ExecuteTurn(int playerMove) {
    m_enemyCmd = m_pEnemy->SelectMove();

    DisplayBattleStatus();

    cin >> m_playerCmd;
    system("cls");

    // 元のsansyou.cppと全く同じswitch文構造
    switch (m_enemyCmd) {
    case 1:     // 敵のじしん
        switch (m_playerCmd) {
        case 1:     // じしん
            if (m_pEnemy->GetSpeed() > m_pPlayer->GetSpeed()) {
                //====p2====
                p2_Waza(m_pEnemy);
                m_damage = En_Damage(m_pEnemy, m_pPlayer);
                En_Damage_hyouzi(m_pEnemy, m_pPlayer);
                if (finCheak(m_pPlayer, m_pEnemy)) return true;
                //====p1====
                p1_Waza(m_pPlayer);
                m_damage = Damage(m_pPlayer, m_pEnemy);
                Damage_hyouzi(m_pPlayer, m_pEnemy);
                if (finCheak(m_pPlayer, m_pEnemy)) return true;
            } else {
                //====p1====
                p1_Waza(m_pPlayer);
                m_damage = Damage(m_pPlayer, m_pEnemy);
                Damage_hyouzi(m_pPlayer, m_pEnemy);
                if (finCheak(m_pPlayer, m_pEnemy)) return true;
                //====p2====
                p2_Waza(m_pEnemy);
                m_damage = En_Damage(m_pEnemy, m_pPlayer);
                En_Damage_hyouzi(m_pEnemy, m_pPlayer);
                if (finCheak(m_pPlayer, m_pEnemy)) return true;
            }
            break;
        case 2:     // カウンター
            //====p2====
            p2_Waza(m_pEnemy);
            m_damage = En_Damage(m_pEnemy, m_pPlayer);
            En_Damage_hyouzi(m_pEnemy, m_pPlayer);
            if (finCheak(m_pPlayer, m_pEnemy)) return true;
            //====p1====
            p1_Waza(m_pPlayer);
            m_damage = Damage(m_pPlayer, m_pEnemy);
            Damage_hyouzi(m_pPlayer, m_pEnemy);
            if (finCheak(m_pPlayer, m_pEnemy)) return true;
            break;
        case 3:     // つるぎのまい
            if (m_pEnemy->GetSpeed() > m_pPlayer->GetSpeed()) {
                //====p2====
                p2_Waza(m_pEnemy);
                m_damage = En_Damage(m_pEnemy, m_pPlayer);
                En_Damage_hyouzi(m_pEnemy, m_pPlayer);
                if (finCheak(m_pPlayer, m_pEnemy)) return true;
                //====p1====
                p1_Waza(m_pPlayer);
                turugi(m_pPlayer);
            } else {
                //====p1====
                p1_Waza(m_pPlayer);
                turugi(m_pPlayer);
                //====p2====
                p2_Waza(m_pEnemy);
                m_damage = En_Damage(m_pEnemy, m_pPlayer);
                En_Damage_hyouzi(m_pEnemy, m_pPlayer);
                if (finCheak(m_pPlayer, m_pEnemy)) return true;
            }
            break;
        case 4:     // まもる
            p1_Waza(m_pPlayer);
            p2_Waza(m_pEnemy);
            cout << "何も起こらなかった！\n";
            rewind(stdin);
            cin.get();
            break;
        default:
            cout << "誤入力。１～４を入力してください\n";
            return false;
        }
        break;
    case 2:     // 敵のカウンター
        switch (m_playerCmd) {
        case 1:     // じしん
            //====p1====
            p1_Waza(m_pPlayer);
            m_damage = Damage(m_pPlayer, m_pEnemy);
            Damage_hyouzi(m_pPlayer, m_pEnemy);
            if (finCheak(m_pPlayer, m_pEnemy)) return true;
            //====p2====
            p2_Waza(m_pEnemy);
            m_damage = En_Damage(m_pEnemy, m_pPlayer);
            En_Damage_hyouzi(m_pEnemy, m_pPlayer);
            if (finCheak(m_pPlayer, m_pEnemy)) return true;
            break;
        case 2:     // カウンター
            //====p1====
            p1_Waza(m_pPlayer);
            sikasi();
            //====p2====
            p2_Waza(m_pEnemy);
            sikasi();
            break;
        case 3:     // つるぎのまい
            //====p1====
            p1_Waza(m_pPlayer);
            turugi(m_pPlayer);
            //====p2====
            p2_Waza(m_pEnemy);
            sikasi();
            break;
        case 4:     // まもる
            //====p1====
            p1_Waza(m_pPlayer);
            //====p2====
            p2_Waza(m_pEnemy);
            sikasi();
            break;
        default:
            cout << "誤入力。１～４を入力してください\n";
            return false;
        }
        break;
    case 3:     // 敵のつるぎのまい
        switch (m_playerCmd) {
        case 1:     // じしん
            //====p1====
            p1_Waza(m_pPlayer);
            m_damage = Damage(m_pPlayer, m_pEnemy);
            Damage_hyouzi(m_pPlayer, m_pEnemy);
            if (finCheak(m_pPlayer, m_pEnemy)) return true;
            //====p2====
            p2_Waza(m_pEnemy);
            en_turugi(m_pEnemy);
            break;
        case 2:     // カウンター
            //====p2====
            p2_Waza(m_pEnemy);
            en_turugi(m_pEnemy);
            //====p1====
            p1_Waza(m_pPlayer);
            sikasi();
            break;
        case 3:     // つるぎのまい
            //====p1====
            p1_Waza(m_pPlayer);
            turugi(m_pPlayer);
            //====p2====
            p2_Waza(m_pEnemy);
            en_turugi(m_pEnemy);
            break;
        case 4:     // まもる
            //====p1====
            p1_Waza(m_pPlayer);
            sikasi();
            //====p2====
            p2_Waza(m_pEnemy);
            en_turugi(m_pEnemy);
            break;
        default:
            cout << "誤入力。１～４を入力してください\n";
            return false;
        }
        break;
    case 4:     // 敵のまもる
        switch (m_playerCmd) {
        case 1:     // じしん
            //====p2====
            p2_Waza(m_pEnemy);
            //====p1====
            p1_Waza(m_pPlayer);
            sikasi();
            break;
        case 2:     // カウンター
            //====p2====
            p2_Waza(m_pEnemy);
            //====p1====
            p1_Waza(m_pPlayer);
            sikasi();
            break;
        case 3:     // つるぎのまい
            //====p2====
            p2_Waza(m_pEnemy);
            //====p1====
            p1_Waza(m_pPlayer);
            turugi(m_pPlayer);
            break;
        case 4:     // まもる
            //====p1====
            p1_Waza(m_pPlayer);
            //====p2====
            p2_Waza(m_pEnemy);
            sikasi();
            break;
        default:
            cout << "誤入力。１～４を入力してください\n";
            rewind(stdin);
            cin.get();
            return false;
        }
        break;
    }

    return false;
}

void BattleSystem::DisplayBattleStatus() const {
    cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";
    cout << "■ " << setw(10) << m_pPlayer->GetName() << setw(11) << "　　敵：" << m_pEnemy->GetName() << "　■\n";
    cout << "■  HP   ：" << setw(3) << m_pPlayer->GetCurrentHP() << "  ■■  HP   ：" << setw(3) << m_pEnemy->GetCurrentHP() << "  ■\n";
    cout << "■  ATK  ：" << setw(3) << m_pPlayer->GetAttack() + m_playerAtkPlus << "  ■■  ATK  ：???  ■\n";
    cout << "■  DEF  ：" << setw(3) << m_pPlayer->GetDefense() << "  ■■  DEF  ：???  ■\n";
    cout << "■  SpATK：" << setw(3) << "???" << "  ■■  SpATK：???  ■\n";
    cout << "■  SpDEF：" << setw(3) << "???" << "  ■■  SpDEF：???  ■\n";
    cout << "■  SPEED：" << setw(3) << m_pPlayer->GetSpeed() << "  ■■  SPEED：???  ■\n";
    cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n";

    cout << "技を選択してください。\n\n";
    cout << "【" << POKEMON_WAZA[0] << "】" << setw(18) << "威力100\n";
    cout << "【" << POKEMON_WAZA[1] << "】" << setw(18) << "必ず後攻になる。物理技を受けたダメージを2倍にし、その相手に返す\n";
    cout << "【" << POKEMON_WAZA[2] << "】" << setw(18) << "攻撃 x 1.1\n";
    cout << "【" << POKEMON_WAZA[3] << "】" << setw(18) << "相手の攻撃を様子見する\n";
    cout << "１：じしん" << setw(20) << "２：カウンター\n";
    cout << "３：つるぎのまい" << setw(20) << "４：まもる\n";
    cout << ">>";
}

void BattleSystem::p1_Waza(PlayerPokemon* p1) {
    cout << p1->GetName() << "の" << POKEMON_WAZA[m_playerCmd - 1] << "！\n";
    rewind(stdin);
    cin.get();
}

void BattleSystem::p2_Waza(EnemyPokemon* p2) {
    cout << p2->GetName() << "の" << POKEMON_WAZA[m_enemyCmd - 1] << "！\n";
    rewind(stdin);
    cin.get();
}

void BattleSystem::sikasi() {
    cout << "しかし、うまく決まらなかった！\n";
    rewind(stdin);
    cin.get();
}

void BattleSystem::turugi(PlayerPokemon* p1) {
    m_playerAtkPlus = static_cast<int>(floor((p1->GetAttack() + m_playerAtkPlus) * TURUGI_NO_MAI)) - (p1->GetAttack() + m_playerAtkPlus);
    cout << p1->GetName() << "は　攻撃力が　１段階上がった！\n";
    rewind(stdin);
    cin.get();
}

void BattleSystem::en_turugi(EnemyPokemon* p2) {
    m_enemyAtkPlus = static_cast<int>(floor((p2->GetAttack() + m_enemyAtkPlus) * TURUGI_NO_MAI)) - (p2->GetAttack() + m_enemyAtkPlus);
    cout << p2->GetName() << "は　攻撃力が　１段階上がった！\n";
    rewind(stdin);
    cin.get();
}

int BattleSystem::Damage(PlayerPokemon* p1, EnemyPokemon* p2) {
    float damage = 50 * 100 * m_playerCmd * 2 / 5 + 2;
    damage = (damage * (p1->GetAttack() + m_playerAtkPlus)) / p2->GetDefense();
    damage = (damage / 50) + 2;
    damage = damage * (((rand() % 5) + 30) / 20);
    damage = floor(damage);
    return static_cast<int>(damage);
}

int BattleSystem::En_Damage(EnemyPokemon* p1, PlayerPokemon* p2) {
    float damage = 50 * 100 * m_enemyCmd * 2 / 5 + 2;
    damage = (damage * (p1->GetAttack() + m_enemyAtkPlus)) / p2->GetDefense();
    damage = (damage / 50) + 2;
    damage = damage * (((rand() % 5) + 30) / 20);
    damage = floor(damage);
    return static_cast<int>(damage);
}

void BattleSystem::Damage_hyouzi(PlayerPokemon* attacker, Pokemon* target) {
    cout << target->GetName() << "は" << m_damage << "ダメージを受けた！\n";
    cout << target->GetName() << " HP：" << target->GetCurrentHP() << "=>";
    target->TakeDamage(m_damage);
    cout << target->GetCurrentHP() << "\n\n";
    rewind(stdin);
    cin.get();
}

void BattleSystem::En_Damage_hyouzi(EnemyPokemon* attacker, Pokemon* target) {
    cout << target->GetName() << "は" << m_damage << "ダメージを受けた！\n";
    cout << target->GetName() << " HP：" << target->GetCurrentHP() << "=>";
    target->TakeDamage(m_damage);
    cout << target->GetCurrentHP() << "\n\n";
    rewind(stdin);
    cin.get();
}

bool BattleSystem::finCheak(PlayerPokemon* p1, EnemyPokemon* p2) {
    if (p1->GetCurrentHP() <= 0) {
        cout << p1->GetName() << "は倒れた。\n";
        rewind(stdin);
        cin.get();
        cout << "目の前が真っ暗になった...\n";
        rewind(stdin);
        cin.get();
        m_battleEnded = true;
        return true;
    } else if (p2->GetCurrentHP() <= 0) {
        cout << p2->GetName() << "は倒れた！\n";
        rewind(stdin);
        cin.get();
        cout << "『" << p1->GetName() << "』の勝利！！！\n";
        rewind(stdin);
        cin.get();
        m_battleEnded = true;
        return true;
    }
    return false;
}