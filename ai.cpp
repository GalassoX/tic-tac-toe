

void PlayAI(char table[5][5], int ex)
{
    srand((unsigned)time(NULL));
    int random = rand() % 9;
    int fila;
    int index;
    if (random >= 0 && random <= 2)
    {
        fila = 0;
        index = random;
    }
    else if (random >= 3 && random <= 5)
    {
        fila = 2;
        index = random - 3;
    }
    else if (random >= 6 && random <= 8)
    {
        fila = 4;
        index = random - 6;
    }

    if (index == 0)
    {
        index = 0;
    }
    else if (index == 1)
    {
        index = 2;
    }
    else if (index == 2)
    {
        index = 4;
    }
    if (table[fila][index] != ' ')
    {
        PlayAI(table, ex + 1);
    }
    else
    {
        table[fila][index] = 'O';
    }
}