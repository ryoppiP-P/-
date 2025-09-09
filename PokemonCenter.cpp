#include "PokemonCenter.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <Windows.h>
#include <conio.h>

using namespace std;

static const char* POKEMON_NAMES[] = {
    "���U�[�h��", "�J���b�N�X", "�t�V�M�o�i", "�T�[�i�C�g", "�Q���K�[",
    "�M�M�M�A��", "�J�C�����[", "���^�O���X", "�K�u���A�X", "�E���K���X",
    "�M���K���h", "�h�q�h�C�f", "�C�V�c�u�e", "�_�X�g�_�X", "�x�x�m��"
};
static constexpr int POKEMON_COUNT = sizeof(POKEMON_NAMES) / sizeof(POKEMON_NAMES[0]);

static const char MONDAI[30][1000] = {
    "�F�B�Ɨ��s�ɍs���Ƃ�����y�ߋ��zor�y�����z",
    "�y�m���zor�y�����z",
    "�C�ɉj���ɍs���Ȃ�y���ԁzor�y��ԁz",
    "�C�������Ƃ��́y��������zor�y���肩��z",
    "�X�}�z�́yiPhone�zor�yAndroid�z",
    "�y����zor�y�h���}�z",
    "�y�ዾ�zor�y�R���^�N�g�z",
    "�y�f�j���zor�y�X���b�N�X�z",
    "�ǂ��炩�ƌ����΁y�p�[�J�[�zor�y�J�[�f�B�K���z",
    "�V���ŏZ�ނ̂́y�V���n�t�߁zor�y�W�F�b�g�R�[�X�^�[�z",
    "���s�ɍs���Ȃ�y�k�C���zor�y����z",
    "�����𒙂߂�Ȃ�y�ߋ��zor�y�����z",
    "�ꐶ������Ȃ�y�Ǐ��zor�y�f��z",
    "�ꐶ�Z�ނȂ�y�s�s�zor�y�c�Ɂz",
    "���N�o���Ȃ�y�N���Ȃ������zor�y�r���Ȃ������z",
    "�h���C�u����Ȃ�y�^�C���}�V���zor�y�ǂ��ł��h�A�z",
    "���̋C���́y�T�C�N�����O�zor�y�K�X�g�z",
    "�y�Ǐ��zor�y�Ǐ��ȊO�z",
    "�ǂ��炩��I�ԂƂ�����ySwitch�zor�yPS5�z",
    "�ǂ���̐F���D���y�ԁzor�y�z",
    "�D���ȋG�߁y�t�E�āE�H�zor�y����ȊO�z",
    "�ǂ��炩�ƌ����΁y���N���zor�y��X�����z",
    "���H��H�ׂ�Ȃ�y���ьn�zor�y�p���n�z",
    "�R���r�j�ŃR�[�q�[50�~���������Ɓy�������zor�y�Ȃ��z",
    "HAL������AS���w����Ɓy�������zor�y�Ȃ��z",
    "���s����Ȃ�y�����zor�y�C�O�z",
    "���z�̏Z�ޏꏊ�́y�}���V�����zor�y�ꌬ�Ɓz",
    "�C�ɍs���Ƃ�����y�C�zor�y�v�[���z",
    "�f�B�Y�j�[�s���Ȃ�y�����h�zor�y�V�[�z",
    "�ǂ���̗������D���y�m�H�n�zor�y�a�H�n�z",
};

static const char SENTAKUSI1[30][1000] = {
    "�ߋ�", "�m��", "����", "��������", "iPhone", "����", "�ዾ", "�f�j��", "�p�[�J�[", "�V���n�t��",
    "�k�C��", "�ߋ�", "�Ǐ�", "�s�s", "�N���Ȃ�����", "�^�C���}�V��", "�T�C�N�����O", "�Ǐ�",
    "Switch", "��", "�t�ďH", "���N��", "���ьn", "������", "������", "����", "�}���V����", "�C", "�����h", "�m�H�n"
};

static const char SENTAKUSI2[30][1000] = {
    "����", "����", "���", "���肩��", "Android", "�h���}", "�R���^�N�g", "�X���b�N�X", "�J�[�f�B�K��", "�W�F�b�g�R�[�X�^�[",
    "����", "����", "�f��", "�c��", "�r���Ȃ�����", "�ǂ��ł��h�A", "�K�X�g", "�Ǐ��ȊO",
    "PS5", "��", "����ȊO", "��X����", "�p���n", "�Ȃ�", "�Ȃ�", "�C�O", "�ꌬ��", "�v�[��", "�V�[", "�a�H�n"
};

int parameter = 0;

PokemonCenter::PokemonCenter() {
    for (int i = 0; i < PARTY_MAX; i++) {
        m_pPokemonParty[i] = nullptr;
    }
}

PokemonCenter::~PokemonCenter() {
    for (int i = 0; i < PARTY_MAX; i++) {
        delete m_pPokemonParty[i];
    }
}

bool PokemonCenter::CreatePokemon() {
    string mondai;
    string sentakusi1;
    string sentakusi2;
    
    while (true) {
        int iCheak = -1;
        system("cls");
        
        for (int i = 0; i < PARTY_MAX; i++) {
            if (m_pPokemonParty[i] == nullptr) {
                cout << "���i�f�f���n�߂܂��B�S10��ł��B\n";
                
                // �X�e�[�^�X�A�b�v�p�ϐ������Z�b�g
                int HP_UP = 0;
                int ATK_UP = 0;
                int DEF_UP = 0;
                int SPATK_UP = 0;
                int SPDEF_UP = 0;
                int SPEED_UP = 0;
                
                // 10�⃉���_���o��
                int RAND = 0;
                bool isUsed[QUIZ_MAX] = {false};
                for (int j = 0; j < 10; j++) {
                    do {
                        RAND = (rand() % QUIZ_MAX);
                    } while (isUsed[RAND]);
                    isUsed[RAND] = true;
                    
                    mondai = MONDAI[RAND];
                    sentakusi1 = SENTAKUSI1[RAND];
                    sentakusi2 = SENTAKUSI2[RAND];
                    
                    int SeikakuUp = Seikaku(j, mondai, sentakusi1, sentakusi2, RAND);
                    
                    if (RAND < 5) {
                        HP_UP += SeikakuUp;
                    } else if (RAND < 10) {
                        ATK_UP += SeikakuUp;
                    } else if (RAND < 15) {
                        DEF_UP += SeikakuUp;
                    } else if (RAND < 20) {
                        SPATK_UP += SeikakuUp;
                    } else if (RAND < 25) {
                        SPDEF_UP += SeikakuUp;
                    } else {
                        SPEED_UP += SeikakuUp;
                    }
                }
                
                cout << "\n";
                string sei = "���i�f�f�ɂ��A�X�e�[�^�X�𐶐����܂�...";
                for (char c : sei) {
                    cout << c << flush;
                    Sleep(20);
                }
                Sleep(300);
                system("cls");
                
                iCheak = i;
                string pokemonName = GetRandomPokemonName();
                m_pPokemonParty[i] = new PlayerPokemon(pokemonName);
                
                int hp = (rand() % 200) + (301 + HP_UP);
                int atk = (rand() % 120) + (181 + ATK_UP);
                int def = (rand() % 120) + (181 + DEF_UP);
                int spatk = (rand() % 120) + (181 + SPATK_UP);
                int spdef = (rand() % 120) + (181 + SPDEF_UP);
                int speed = (rand() % 120) + (181 + SPEED_UP);
                
                m_pPokemonParty[i]->SetStats(hp, atk, def, spatk, spdef, speed);

                cout << "�ł����I\n\n";
                Sleep(500);

                cout << setw(8) << "���O�F" << pokemonName << "\n";
                cout << setw(8) << "HP�F" << m_pPokemonParty[i]->GetMaxHP() << "\n";
                cout << setw(8) << "ATK�F" << m_pPokemonParty[i]->GetAttack() << "\n";
                cout << setw(8) << "DEF�F" << m_pPokemonParty[i]->GetDefense() << "\n";
                cout << setw(8) << "SP.ATK�F" << "???" << "\n";
                cout << setw(8) << "SP.DEF�F" << "???" << "\n";
                cout << setw(8) << "SPEED�F" << m_pPokemonParty[i]->GetSpeed() << "\n\n";
                break;
                
            } else if (i == (PARTY_MAX - 1)) {
                cout << "BOX�����t�̂��߁A�琬���s�����Ƃ��ł��܂���B\n";
                cout << "�|�P�����𓦂����܂����H\n\n";
                cout << "�P�F�͂� / �Q�F������\n";
                int Cmd;
                cin >> Cmd;
                if (Cmd == 1) {
                    DisplayPokemonList();
                    cout << "�������|�P�����̔ԍ�����͂��Ă�������: ";
                    int index;
                    cin >> index;
                    if (ReleasePokemon(index - 1)) {
                        cout << "�|�P�����𓦂����܂����B\n";
                        continue; // �ēx�󂫃X���b�g��T��
                    }
                } else if (Cmd == 2) {
                    cout << "�����p���肪�Ƃ��������܂�...BOX���o�܂��B\n";
                    Sleep(1500);
                    return false;
                }
                cout << "BOX���o�܂�...";
                Sleep(1500);
                return false;
            }
        }
        
        cout << "�琬���܂����H\n";
        cout << "�P�F�͂� / �Q�F������\n";
        cout << ">>";
        int Value;
        cin >> Value;
        if (Value == 1) {
            if (iCheak >= 0 && iCheak < PARTY_MAX) {
                // �琬�����������͍폜
            } else {
                cout << "�o�b�t�@�I�[�o�[�ł��B�v���O�����������I�����܂��B\n";
                exit(999);
            }
        } else {
            cout << "�琬�𑱍s���܂����H\n";
            cout << "�P�F�͂� / �Q�F������\n";
            cout << ">>";
            cin >> Value;
            if (Value == 2) {
                cout << "BOX���o�܂�...";
                Sleep(1000);
                break;
            }
        }
    }

    system("cls");
    return true;
}

int PokemonCenter::Seikaku(int Ikumon, string Mondai, string Sentakusi1, string Sentakusi2, int Rand) {
    char getchCmd = ' ';
    getchCmd = ' ';
    while (!(getchCmd == 'f')) {
        system("cls");
        cout << "�� " << Ikumon + 1 << " ��\n";
        cout << Mondai << "\n";
        cout << "\n�ua�v�L�[�Ł��Ɂ@�ud�v�L�[�Ł��Ɂ@�uf�v�L�[�Ō���\n\n";
        if (getchCmd == 'a') {
            cout << ">>" << Sentakusi1 << "�@�@" << Sentakusi2 << "\n";
        } else if (getchCmd == 'd') {
            cout << "  " << Sentakusi1 << "�@>>" << Sentakusi2 << "\n";
        } else {
            cout << ">>" << Sentakusi1 << "�@�@" << Sentakusi2 << "\n";
        }
        getchCmd = getch();
        switch (getchCmd) {
        case 'a':
            if (Rand < 10) {
                parameter = 10;
            } else if (Rand < 20) {
                parameter = 30;
            } else {
                parameter = 40;
            }
            break;
        case 'd':
            if (Rand < 10) {
                parameter = 40;
            } else if (Rand < 20) {
                parameter = 20;
            } else {
                parameter = 10;
            }
            break;
        case 'f':
            return parameter;
        default:
            cout << "�s���ȓ��͂ł��Ba �܂��� d ����͂��Ă��������B\n";
        }
    }
    return parameter;
}

string PokemonCenter::GetRandomPokemonName() const {
    int index = rand() % POKEMON_COUNT;
    return string(POKEMON_NAMES[index]);
}

void PokemonCenter::GenerateRandomStats(PlayerPokemon& pokemon) {
    // ���̊֐��͎g��Ȃ��iCreatePokemon���Œ��ڏ����j
}

void PokemonCenter::DisplayPokemonList() const {
    cout << "�ǂ̃|�P�����̗l�q�����܂����H\n";

    for (int i = 0; i < PARTY_MAX; ++i) {
        cout << " No " << (i + 1) << "�F";
        if (m_pPokemonParty[i] != nullptr && m_pPokemonParty[i]->GetIsActive()) {
            cout << m_pPokemonParty[i]->GetName() << "\n";
        } else {
            cout << "\n";
        }
    }

    cout << "BOX���o�� �F �X\n\n";
}

void PokemonCenter::ViewPokemonDetails(int index) const {
    if (index < 0 || index >= PARTY_MAX || m_pPokemonParty[index] == nullptr) {
        cout << "�f�[�^�����݂��܂���B\n";
        return;
    }

    const PlayerPokemon* pokemon = m_pPokemonParty[index];
    cout << " ���O �F" << pokemon->GetName() << "\n";
    cout << " HP   �F" << pokemon->GetMaxHP() << "\n";
    cout << " ATK  �F" << pokemon->GetAttack() << "\n";
    cout << " DEF  �F" << pokemon->GetDefense() << "\n";
    cout << " SpATK�F" << "???" << "\n";
    cout << " SpDEF�F" << "???" << "\n";
    cout << " SPEED�F" << pokemon->GetSpeed() << "\n";
}

bool PokemonCenter::ReleasePokemon(int index) {
    if (index < 0 || index >= PARTY_MAX || m_pPokemonParty[index] == nullptr) {
        return false;
    }

    cout << "�u" << m_pPokemonParty[index]->GetName() << "�v�𓦂����܂��B�{���ɂ�낵���ł����H\n";
    cout << "�͂��@�� �P �E �������@�� �Q\n�ԍ�����͂��Ă�������>>";
    int choice;
    cin >> choice;

    if (choice == 1) {
        cout << "\n�u" << m_pPokemonParty[index]->GetName() << "�v�𓦂����܂����B�΂��΂�\n";
        delete m_pPokemonParty[index];
        m_pPokemonParty[index] = nullptr;
        Sleep(800);
        return true;
    }

    return false;
}

PlayerPokemon* PokemonCenter::SelectPokemonForBattle() {
    while (true) {
        system("cls");
        cout << "�ǂ̃|�P�����Ő킢�܂����H\n\n";

        DisplayPokemonList();

        cout << "�ԍ�����͂��Ă�������>>";
        int choice;
        cin >> choice;

        if (choice < 1 || choice > PARTY_MAX) {
            cout << "�G���[\n";
            continue;
        }

        int index = choice - 1;
        if (m_pPokemonParty[index] != nullptr && m_pPokemonParty[index]->GetIsActive()) {
            ViewPokemonDetails(index);

            cout << "���̃|�P�����ł�낵���ł����H\n";
            cout << "�͂� �F �P / ������ �F �Q\n>>";
            int confirm;
            cin >> confirm;

            if (confirm == 1) {
                cout << m_pPokemonParty[index]->GetName() << "�@�N�Ɍ��߂��I\n";
                return m_pPokemonParty[index];
            }
        } else {
            cout << "�f�[�^�����݂��܂���B\n";
        }

        rewind(stdin);
        cin.get();
    }
}

int PokemonCenter::GetPartySize() const {
    int count = 0;
    for (int i = 0; i < PARTY_MAX; i++) {
        if (m_pPokemonParty[i] != nullptr) {
            count++;
        }
    }
    return count;
}

bool PokemonCenter::IsPartyFull() const {
    return FindEmptySlot() == -1;
}

int PokemonCenter::FindEmptySlot() const {
    for (int i = 0; i < PARTY_MAX; i++) {
        if (m_pPokemonParty[i] == nullptr) {
            return i;
        }
    }
    return -1;
}

void PokemonCenter::ShowMainMenu() {
    int MenuNo;
    do {
        system("cls");
        cout << "���|�P�����Z���^�[\n\n";
        cout << "�u�ǂ������H�v���m�͌�����\n\n";
        Sleep(800);
        cout << "�P�F�|�P�����̗l�q������\n";
        cout << "�Q�F�|�P�����琬\n";
        cout << "�R�F�|�P�����𓦂���\n";
        cout << "�S�F���|�P�����Z���^�[���o��@(�T�J�L��|��)\n";
        cout << "�ԍ���I�����Ă�������";

        cin >> MenuNo;
        system("cls");

        switch (MenuNo) {
        case 1: {
            DisplayPokemonList();
            cout << "�ԍ�����͂��Ă�������>>";
            int index;
            cin >> index;
            if (index != 9) {
                ViewPokemonDetails(index - 1);
                rewind(stdin);
                cin.get();
            }
            break;
        }
        case 2:
            CreatePokemon();
            break;
        case 3: {
            DisplayPokemonList();
            cout << "�������|�P�����̔ԍ�����͂��Ă�������>>";
            int index;
            cin >> index;
            if (index != 9) {
                ReleasePokemon(index - 1);
            }
            break;
        }
        case 4:
            cout << "�|�P�����Z���^�[���o�܂�...";
            Sleep(500);
            break;
        default:
            cout << "����́B�P�`�S����͂��Ă�������";
        }

    } while (MenuNo != 4);
}