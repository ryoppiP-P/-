#include "PokemonCenter.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <Windows.h>
#include <conio.h>

using namespace std;

static const char* POKEMON_NAMES[] = {
    "リザードン", "カメックス", "フシギバナ", "サーナイト", "ゲンガー",
    "ギギギアル", "カイリュー", "メタグロス", "ガブリアス", "ウルガモス",
    "ギルガルド", "ドヒドイデ", "イシツブテ", "ダストダス", "ベベノム"
};
static constexpr int POKEMON_COUNT = sizeof(POKEMON_NAMES) / sizeof(POKEMON_NAMES[0]);

static const char MONDAI[30][1000] = {
    "友達と旅行に行くとしたら【過去】or【未来】",
    "【洋服】or【着物】",
    "海に泳ぎに行くなら【昼間】or【夜間】",
    "気を遣うときは【自分から】or【相手から】",
    "スマホは【iPhone】or【Android】",
    "【漫画】or【ドラマ】",
    "【眼鏡】or【コンタクト】",
    "【デニム】or【スラックス】",
    "どちらかと言えば【パーカー】or【カーディガン】",
    "新婚で住むのは【遊園地付近】or【ジェットコースター】",
    "旅行に行くなら【北海道】or【沖縄】",
    "お金を貯めるなら【過去】or【未来】",
    "一生続けるなら【読書】or【映画】",
    "一生住むなら【都市】or【田舎】",
    "毎年出すなら【年賀状なし正月】or【喪中なし正月】",
    "ドライブするなら【タイムマシン】or【どこでもドア】",
    "今の気分は【サイクリング】or【ガスト】",
    "【読書】or【読書以外】",
    "どちらかを選ぶとしたら【Switch】or【PS5】",
    "どちらの色が好き【赤】or【青】",
    "好きな季節【春・夏・秋】or【それ以外】",
    "どちらかと言えば【朝起き】or【夜更かし】",
    "朝食を食べるなら【ご飯系】or【パン系】",
    "コンビニでコーヒー50円引きされると【嬉しい】or【なし】",
    "HAL東京でAS入学すると【嬉しい】or【なし】",
    "旅行するなら【国内】or【海外】",
    "理想の住む場所は【マンション】or【一軒家】",
    "海に行くとしたら【海】or【プール】",
    "ディズニー行くなら【ランド】or【シー】",
    "どちらの料理が好き【洋食系】or【和食系】",
};

static const char SENTAKUSI1[30][1000] = {
    "過去", "洋服", "昼間", "自分から", "iPhone", "漫画", "眼鏡", "デニム", "パーカー", "遊園地付近",
    "北海道", "過去", "読書", "都市", "年賀状なし正月", "タイムマシン", "サイクリング", "読書",
    "Switch", "赤", "春夏秋", "朝起き", "ご飯系", "嬉しい", "嬉しい", "国内", "マンション", "海", "ランド", "洋食系"
};

static const char SENTAKUSI2[30][1000] = {
    "未来", "着物", "夜間", "相手から", "Android", "ドラマ", "コンタクト", "スラックス", "カーディガン", "ジェットコースター",
    "沖縄", "未来", "映画", "田舎", "喪中なし正月", "どこでもドア", "ガスト", "読書以外",
    "PS5", "青", "それ以外", "夜更かし", "パン系", "なし", "なし", "海外", "一軒家", "プール", "シー", "和食系"
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
                cout << "性格診断を始めます。全10問です。\n";
                
                // ステータスアップ用変数をリセット
                int HP_UP = 0;
                int ATK_UP = 0;
                int DEF_UP = 0;
                int SPATK_UP = 0;
                int SPDEF_UP = 0;
                int SPEED_UP = 0;
                
                // 10問ランダム出題
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
                string sei = "性格診断により、ステータスを生成します...";
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

                cout << "できた！\n\n";
                Sleep(500);

                cout << setw(8) << "名前：" << pokemonName << "\n";
                cout << setw(8) << "HP：" << m_pPokemonParty[i]->GetMaxHP() << "\n";
                cout << setw(8) << "ATK：" << m_pPokemonParty[i]->GetAttack() << "\n";
                cout << setw(8) << "DEF：" << m_pPokemonParty[i]->GetDefense() << "\n";
                cout << setw(8) << "SP.ATK：" << "???" << "\n";
                cout << setw(8) << "SP.DEF：" << "???" << "\n";
                cout << setw(8) << "SPEED：" << m_pPokemonParty[i]->GetSpeed() << "\n\n";
                break;
                
            } else if (i == (PARTY_MAX - 1)) {
                cout << "BOXが満杯のため、育成を行うことができません。\n";
                cout << "ポケモンを逃がしますか？\n\n";
                cout << "１：はい / ２：いいえ\n";
                int Cmd;
                cin >> Cmd;
                if (Cmd == 1) {
                    DisplayPokemonList();
                    cout << "逃がすポケモンの番号を入力してください: ";
                    int index;
                    cin >> index;
                    if (ReleasePokemon(index - 1)) {
                        cout << "ポケモンを逃がしました。\n";
                        continue; // 再度空きスロットを探す
                    }
                } else if (Cmd == 2) {
                    cout << "ご利用ありがとうございます...BOXを出ます。\n";
                    Sleep(1500);
                    return false;
                }
                cout << "BOXを出ます...";
                Sleep(1500);
                return false;
            }
        }
        
        cout << "育成しますか？\n";
        cout << "１：はい / ２：いいえ\n";
        cout << ">>";
        int Value;
        cin >> Value;
        if (Value == 1) {
            if (iCheak >= 0 && iCheak < PARTY_MAX) {
                // 育成取り消し処理は削除
            } else {
                cout << "バッファオーバーです。プログラムを強制終了します。\n";
                exit(999);
            }
        } else {
            cout << "育成を続行しますか？\n";
            cout << "１：はい / ２：いいえ\n";
            cout << ">>";
            cin >> Value;
            if (Value == 2) {
                cout << "BOXを出ます...";
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
        cout << "第 " << Ikumon + 1 << " 問\n";
        cout << Mondai << "\n";
        cout << "\n「a」キーで←に　「d」キーで→に　「f」キーで決定\n\n";
        if (getchCmd == 'a') {
            cout << ">>" << Sentakusi1 << "　　" << Sentakusi2 << "\n";
        } else if (getchCmd == 'd') {
            cout << "  " << Sentakusi1 << "　>>" << Sentakusi2 << "\n";
        } else {
            cout << ">>" << Sentakusi1 << "　　" << Sentakusi2 << "\n";
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
            cout << "不正な入力です。a または d を入力してください。\n";
        }
    }
    return parameter;
}

string PokemonCenter::GetRandomPokemonName() const {
    int index = rand() % POKEMON_COUNT;
    return string(POKEMON_NAMES[index]);
}

void PokemonCenter::GenerateRandomStats(PlayerPokemon& pokemon) {
    // この関数は使わない（CreatePokemon内で直接処理）
}

void PokemonCenter::DisplayPokemonList() const {
    cout << "どのポケモンの様子を見ますか？\n";

    for (int i = 0; i < PARTY_MAX; ++i) {
        cout << " No " << (i + 1) << "：";
        if (m_pPokemonParty[i] != nullptr && m_pPokemonParty[i]->GetIsActive()) {
            cout << m_pPokemonParty[i]->GetName() << "\n";
        } else {
            cout << "\n";
        }
    }

    cout << "BOXを出る ： ９\n\n";
}

void PokemonCenter::ViewPokemonDetails(int index) const {
    if (index < 0 || index >= PARTY_MAX || m_pPokemonParty[index] == nullptr) {
        cout << "データが存在しません。\n";
        return;
    }

    const PlayerPokemon* pokemon = m_pPokemonParty[index];
    cout << " 名前 ：" << pokemon->GetName() << "\n";
    cout << " HP   ：" << pokemon->GetMaxHP() << "\n";
    cout << " ATK  ：" << pokemon->GetAttack() << "\n";
    cout << " DEF  ：" << pokemon->GetDefense() << "\n";
    cout << " SpATK：" << "???" << "\n";
    cout << " SpDEF：" << "???" << "\n";
    cout << " SPEED：" << pokemon->GetSpeed() << "\n";
}

bool PokemonCenter::ReleasePokemon(int index) {
    if (index < 0 || index >= PARTY_MAX || m_pPokemonParty[index] == nullptr) {
        return false;
    }

    cout << "「" << m_pPokemonParty[index]->GetName() << "」を逃がします。本当によろしいですか？\n";
    cout << "はい　← １ ・ いいえ　← ２\n番号を入力してください>>";
    int choice;
    cin >> choice;

    if (choice == 1) {
        cout << "\n「" << m_pPokemonParty[index]->GetName() << "」を逃がしました。ばいばい\n";
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
        cout << "どのポケモンで戦いますか？\n\n";

        DisplayPokemonList();

        cout << "番号を入力してください>>";
        int choice;
        cin >> choice;

        if (choice < 1 || choice > PARTY_MAX) {
            cout << "エラー\n";
            continue;
        }

        int index = choice - 1;
        if (m_pPokemonParty[index] != nullptr && m_pPokemonParty[index]->GetIsActive()) {
            ViewPokemonDetails(index);

            cout << "このポケモンでよろしいですか？\n";
            cout << "はい ： １ / いいえ ： ２\n>>";
            int confirm;
            cin >> confirm;

            if (confirm == 1) {
                cout << m_pPokemonParty[index]->GetName() << "　君に決めた！\n";
                return m_pPokemonParty[index];
            }
        } else {
            cout << "データが存在しません。\n";
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
        cout << "■ポケモンセンター\n\n";
        cout << "「どうした？」博士は言った\n\n";
        Sleep(800);
        cout << "１：ポケモンの様子を見る\n";
        cout << "２：ポケモン育成\n";
        cout << "３：ポケモンを逃がす\n";
        cout << "４：■ポケモンセンターを出る　(サカキを倒す)\n";
        cout << "番号を選択してください";

        cin >> MenuNo;
        system("cls");

        switch (MenuNo) {
        case 1: {
            DisplayPokemonList();
            cout << "番号を入力してください>>";
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
            cout << "逃がすポケモンの番号を入力してください>>";
            int index;
            cin >> index;
            if (index != 9) {
                ReleasePokemon(index - 1);
            }
            break;
        }
        case 4:
            cout << "ポケモンセンターを出ます...";
            Sleep(500);
            break;
        default:
            cout << "誤入力。１～４を入力してください";
        }

    } while (MenuNo != 4);
}