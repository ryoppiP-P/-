#include "BattleSystem.h"
#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <cmath>

using namespace std;

const char BattleSystem::POKEMON_WAZA[4][256] = {
    "������",
    "�J�E���^�[",
    "�邬�̂܂�",
    "�܂���",
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
    m_pEnemy = new EnemyPokemon("�~���E�c�[", difficulty);
    m_pEnemy->ScaleWithDifficulty();
    m_battleEnded = false;
    m_playerAtkPlus = 0;
    m_enemyAtkPlus = 0;

    cout << "\n=======�y�����̍��@�T�J�L�z�Ƒΐ�=======\n\n";
    Sleep(800);
    cout << "�T�J�L�u�䂪�����I�v���m��I�v\n\n";
    Sleep(800);
}

bool BattleSystem::ExecuteTurn(int playerMove) {
    m_enemyCmd = m_pEnemy->SelectMove();

    DisplayBattleStatus();

    cin >> m_playerCmd;
    system("cls");

    // ����sansyou.cpp�ƑS������switch���\��
    switch (m_enemyCmd) {
    case 1:     // �G�̂�����
        switch (m_playerCmd) {
        case 1:     // ������
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
        case 2:     // �J�E���^�[
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
        case 3:     // �邬�̂܂�
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
        case 4:     // �܂���
            p1_Waza(m_pPlayer);
            p2_Waza(m_pEnemy);
            cout << "�����N����Ȃ������I\n";
            rewind(stdin);
            cin.get();
            break;
        default:
            cout << "����́B�P�`�S����͂��Ă�������\n";
            return false;
        }
        break;
    case 2:     // �G�̃J�E���^�[
        switch (m_playerCmd) {
        case 1:     // ������
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
        case 2:     // �J�E���^�[
            //====p1====
            p1_Waza(m_pPlayer);
            sikasi();
            //====p2====
            p2_Waza(m_pEnemy);
            sikasi();
            break;
        case 3:     // �邬�̂܂�
            //====p1====
            p1_Waza(m_pPlayer);
            turugi(m_pPlayer);
            //====p2====
            p2_Waza(m_pEnemy);
            sikasi();
            break;
        case 4:     // �܂���
            //====p1====
            p1_Waza(m_pPlayer);
            //====p2====
            p2_Waza(m_pEnemy);
            sikasi();
            break;
        default:
            cout << "����́B�P�`�S����͂��Ă�������\n";
            return false;
        }
        break;
    case 3:     // �G�̂邬�̂܂�
        switch (m_playerCmd) {
        case 1:     // ������
            //====p1====
            p1_Waza(m_pPlayer);
            m_damage = Damage(m_pPlayer, m_pEnemy);
            Damage_hyouzi(m_pPlayer, m_pEnemy);
            if (finCheak(m_pPlayer, m_pEnemy)) return true;
            //====p2====
            p2_Waza(m_pEnemy);
            en_turugi(m_pEnemy);
            break;
        case 2:     // �J�E���^�[
            //====p2====
            p2_Waza(m_pEnemy);
            en_turugi(m_pEnemy);
            //====p1====
            p1_Waza(m_pPlayer);
            sikasi();
            break;
        case 3:     // �邬�̂܂�
            //====p1====
            p1_Waza(m_pPlayer);
            turugi(m_pPlayer);
            //====p2====
            p2_Waza(m_pEnemy);
            en_turugi(m_pEnemy);
            break;
        case 4:     // �܂���
            //====p1====
            p1_Waza(m_pPlayer);
            sikasi();
            //====p2====
            p2_Waza(m_pEnemy);
            en_turugi(m_pEnemy);
            break;
        default:
            cout << "����́B�P�`�S����͂��Ă�������\n";
            return false;
        }
        break;
    case 4:     // �G�̂܂���
        switch (m_playerCmd) {
        case 1:     // ������
            //====p2====
            p2_Waza(m_pEnemy);
            //====p1====
            p1_Waza(m_pPlayer);
            sikasi();
            break;
        case 2:     // �J�E���^�[
            //====p2====
            p2_Waza(m_pEnemy);
            //====p1====
            p1_Waza(m_pPlayer);
            sikasi();
            break;
        case 3:     // �邬�̂܂�
            //====p2====
            p2_Waza(m_pEnemy);
            //====p1====
            p1_Waza(m_pPlayer);
            turugi(m_pPlayer);
            break;
        case 4:     // �܂���
            //====p1====
            p1_Waza(m_pPlayer);
            //====p2====
            p2_Waza(m_pEnemy);
            sikasi();
            break;
        default:
            cout << "����́B�P�`�S����͂��Ă�������\n";
            rewind(stdin);
            cin.get();
            return false;
        }
        break;
    }

    return false;
}

void BattleSystem::DisplayBattleStatus() const {
    cout << "����������������������������������������������������������������\n";
    cout << "�� " << setw(10) << m_pPlayer->GetName() << setw(11) << "�@�@�G�F" << m_pEnemy->GetName() << "�@��\n";
    cout << "��  HP   �F" << setw(3) << m_pPlayer->GetCurrentHP() << "  ����  HP   �F" << setw(3) << m_pEnemy->GetCurrentHP() << "  ��\n";
    cout << "��  ATK  �F" << setw(3) << m_pPlayer->GetAttack() + m_playerAtkPlus << "  ����  ATK  �F???  ��\n";
    cout << "��  DEF  �F" << setw(3) << m_pPlayer->GetDefense() << "  ����  DEF  �F???  ��\n";
    cout << "��  SpATK�F" << setw(3) << "???" << "  ����  SpATK�F???  ��\n";
    cout << "��  SpDEF�F" << setw(3) << "???" << "  ����  SpDEF�F???  ��\n";
    cout << "��  SPEED�F" << setw(3) << m_pPlayer->GetSpeed() << "  ����  SPEED�F???  ��\n";
    cout << "����������������������������������������������������������������\n\n";

    cout << "�Z��I�����Ă��������B\n\n";
    cout << "�y" << POKEMON_WAZA[0] << "�z" << setw(18) << "�З�100\n";
    cout << "�y" << POKEMON_WAZA[1] << "�z" << setw(18) << "�K����U�ɂȂ�B�����Z���󂯂��_���[�W��2�{�ɂ��A���̑���ɕԂ�\n";
    cout << "�y" << POKEMON_WAZA[2] << "�z" << setw(18) << "�U�� x 1.1\n";
    cout << "�y" << POKEMON_WAZA[3] << "�z" << setw(18) << "����̍U����l�q������\n";
    cout << "�P�F������" << setw(20) << "�Q�F�J�E���^�[\n";
    cout << "�R�F�邬�̂܂�" << setw(20) << "�S�F�܂���\n";
    cout << ">>";
}

void BattleSystem::p1_Waza(PlayerPokemon* p1) {
    cout << p1->GetName() << "��" << POKEMON_WAZA[m_playerCmd - 1] << "�I\n";
    rewind(stdin);
    cin.get();
}

void BattleSystem::p2_Waza(EnemyPokemon* p2) {
    cout << p2->GetName() << "��" << POKEMON_WAZA[m_enemyCmd - 1] << "�I\n";
    rewind(stdin);
    cin.get();
}

void BattleSystem::sikasi() {
    cout << "�������A���܂����܂�Ȃ������I\n";
    rewind(stdin);
    cin.get();
}

void BattleSystem::turugi(PlayerPokemon* p1) {
    m_playerAtkPlus = static_cast<int>(floor((p1->GetAttack() + m_playerAtkPlus) * TURUGI_NO_MAI)) - (p1->GetAttack() + m_playerAtkPlus);
    cout << p1->GetName() << "�́@�U���͂��@�P�i�K�オ�����I\n";
    rewind(stdin);
    cin.get();
}

void BattleSystem::en_turugi(EnemyPokemon* p2) {
    m_enemyAtkPlus = static_cast<int>(floor((p2->GetAttack() + m_enemyAtkPlus) * TURUGI_NO_MAI)) - (p2->GetAttack() + m_enemyAtkPlus);
    cout << p2->GetName() << "�́@�U���͂��@�P�i�K�オ�����I\n";
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
    cout << target->GetName() << "��" << m_damage << "�_���[�W���󂯂��I\n";
    cout << target->GetName() << " HP�F" << target->GetCurrentHP() << "=>";
    target->TakeDamage(m_damage);
    cout << target->GetCurrentHP() << "\n\n";
    rewind(stdin);
    cin.get();
}

void BattleSystem::En_Damage_hyouzi(EnemyPokemon* attacker, Pokemon* target) {
    cout << target->GetName() << "��" << m_damage << "�_���[�W���󂯂��I\n";
    cout << target->GetName() << " HP�F" << target->GetCurrentHP() << "=>";
    target->TakeDamage(m_damage);
    cout << target->GetCurrentHP() << "\n\n";
    rewind(stdin);
    cin.get();
}

bool BattleSystem::finCheak(PlayerPokemon* p1, EnemyPokemon* p2) {
    if (p1->GetCurrentHP() <= 0) {
        cout << p1->GetName() << "�͓|�ꂽ�B\n";
        rewind(stdin);
        cin.get();
        cout << "�ڂ̑O���^���ÂɂȂ���...\n";
        rewind(stdin);
        cin.get();
        m_battleEnded = true;
        return true;
    } else if (p2->GetCurrentHP() <= 0) {
        cout << p2->GetName() << "�͓|�ꂽ�I\n";
        rewind(stdin);
        cin.get();
        cout << "�w" << p1->GetName() << "�x�̏����I�I�I\n";
        rewind(stdin);
        cin.get();
        m_battleEnded = true;
        return true;
    }
    return false;
}