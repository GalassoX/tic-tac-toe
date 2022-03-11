#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "ai.cpp"

using namespace std;

char table[5][5] = {
    {' ', '|', ' ', '|', ' '},
    {'-', '|', '-', '|', '-'},
    {' ', '|', ' ', '|', ' '},
    {'-', '|', '-', '|', '-'},
    {' ', '|', ' ', '|', ' '},
};

bool gIsEnded, gActiveAI;

void PrintTable()
{
    int line = 0;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++) 
        {
            cout << table[i][j];
        }
        cout << "\n";
    }
}

int *CheckPlay(int play, int *results)
{
    if (play >= 0 && play <= 8) 
    {
        int fila;
        int index;
        if (play >= 0 && play <= 2) 
        {
            fila = 0;
            index = play;
        }
        else if (play >= 3 && play <= 5) 
        {
            fila = 2;
            index = play - 3;
        } 
        else if (play >= 6 && play <= 8) 
        {
            fila = 4;
            index = play - 6;
        }
        results[0] = fila;
        results[1] = index;
        return results;
    } 
    else 
    {
        cout << "Numero invalido, ingresa uno del 0 al 8\n";
        cin >> play;
        if (play < 0 || play > 8) 
        {
            CheckPlay(play, results);
        }
    }
    return results;
}

int CheckWin() {
    if ((table[0][0] == 'X' && table[0][2] == 'X' && table[0][4] == 'X') 
        || (table[2][0] == 'X' && table[2][2] == 'X' && table[2][4] == 'X') 
        || (table[4][0] == 'X' && table[4][2] == 'X' && table[4][4] == 'X') 
        || (table[0][0] == 'X' && table[2][2] == 'X' && table[4][4] == 'X') 
        || (table[4][0] == 'X' && table[2][2] == 'X' && table[0][4] == 'X') 
        || (table[0][2] == 'X' && table[2][2] == 'X' && table[4][2] == 'X') 
        || (table[0][0] == 'X' && table[2][0] == 'X' && table[4][0] == 'X') 
        || (table[0][4] == 'X' && table[2][4] == 'X' && table[4][4] == 'X')
    ) 
    {
        return 1;
    } 
    else if ((table[0][0] == 'O' && table[0][2] == 'O' && table[0][4] == 'O') 
        || (table[2][0] == 'O' && table[2][2] == 'O' && table[2][4] == 'O') 
        || (table[4][0] == 'O' && table[4][2] == 'O' && table[4][4] == 'O') 
        || (table[0][0] == 'O' && table[2][2] == 'O' && table[4][4] == 'O') 
        || (table[4][0] == 'O' && table[2][2] == 'O' && table[0][4] == 'O') 
        || (table[0][2] == 'O' && table[2][2] == 'O' && table[4][2] == 'O') 
        || (table[0][0] == 'O' && table[2][0] == 'O' && table[4][0] == 'O') 
        || (table[0][4] == 'O' && table[2][4] == 'O' && table[4][4] == 'O')
    ) 
    {
        return 2;
    }
    else return 0;
}

bool AvalibleGame() {
    bool avalible = false;
    for (int i = 0; i < 3; i ++) 
    {
        for (int j = 0; j < 3; j++) 
        {
            if (table[i][j] == ' ') 
            {
                avalible = true;
                break;
            }
            j++;
        }
        i++;
    }
    return avalible;
}

void RestartGame() {
    char answer;
    cout << "\n\nDesea jugar otra partida?\n\nResponda con Si(s) o No(n)\n";
    cin >> answer;
    if (answer == 's')
    {
        char newTab[5][5] = {
            {' ', '|', ' ', '|', ' '},
            {'-', '|', '-', '|', '-'},
            {' ', '|', ' ', '|', ' '},
            {'-', '|', '-', '|', '-'},
            {' ', '|', ' ', '|', ' '},
        };
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                table[i][j] = newTab[i][j];
            }
        }
    }
    else if (answer == 'n')
    {
        gIsEnded = true;
    }
    else 
    {
        cout << "Opcion invalida\n";
        RestartGame();
    }
}

int main(int argc, char const *argv[])
{
    cout << "[< - TIC TAC TOE  - >]" << "\n\n";

    bool playerOne = true;
    int play = 0;

    gIsEnded = false;

    int opt;
    cout << "Selecciona con 1 y 2:\n1) Jugar contra persona.\n2) Jugar contra la PC.\n";
    cin >> opt;

    gActiveAI = opt == 2;

    while (!gIsEnded)
    {
        PrintTable();

        cout << "Realiza una jugada, para hacerlo introduce un numero del 0 al 8!\n";
        cin >> play;

        int results[2];
        CheckPlay(play, results);

        int fila = results[0];
        int index;
        if (results[1] == 0) 
        {
            index = 0;
        }
        else if (results[1] == 1) 
        {
            index = 2;
        }
        else if (results[1] == 2) 
        {
            index = 4;
        }

        if (table[fila][index] == ' ')
        {
            table[fila][index] = playerOne ? 'X' : 'O';
            if (!gActiveAI)
            {
                //table[fila][index] = playerOne ? 'X' : 'O';
                playerOne = !playerOne;
            }
            else
            {
                PlayAI(table, 0);
            }
        }
        else 
        {
            cout << "Espacio ocupado\n";
        }

        int winner = CheckWin();
        if (winner != 0) 
        {
            PrintTable();
            if (gActiveAI)
            {
                cout << (winner == 1 ? "Ganaste!\n" : "La PC te ha ganado :(\n");
            }
            else
            {
                cout << "Jugador " << winner << " gano!\n";
            }
            RestartGame();
            //gIsEnded = true;
        }

        if (!AvalibleGame()) 
        {
            cout << "Empate.";
            RestartGame();
        }
    }
    system("pause");
    return 0;
}
