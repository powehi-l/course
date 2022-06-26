#include <stdio.h>
#include <string.h>
char reflector[] = "YRUHQSLDPXNGOKMIEBFZCWVJAT";
char rotor_table[5][27] =
    {
        "EKMFLGDQVZNTOWYHXUSPAIBRCJ",
        "AJDKSIRUXBLHWTMCQGZNPYFVOE",
        "BDFHJLCPRTXVZNYEIWGAKMUSQO",
        "ESOVPZJAYQUIRHXLNFTGKDCMWB",
        "VZBRGITYUPSDNHLXAWMJQOFECK"};
char Messagekey[5], Ringsetting[5], rotornum[5];
char plugboard[10][2];
char secret[100];
char step_char[5] = "QEVJZ";
char stepback_char[5] = "RFWKA";
char cipher[500], plain[100], temp[100];
char result[500];

void print();
void stepback(int i);
void backone();
void enigma(char *message);
char plug(char temp);
char forward(char c);
char backward(char c);
void changestate();
char rotor(int i, char temp);
char ref(char temp);
char rerotor(int i, char temp);
int len(char *a);

int same(int i)
{
    int j;
    for (j = 0; j < strlen(plain); j++)
    {
        if (plain[j] == cipher[i + j])
        {
            return 1;
        }
    }
    return 0;
}

int main()
{
    int i, j, k, a, b, c, ro, p, q;
    for (i = 0; i < 10; i++)
    {
        scanf("%s", plugboard[i]);
    }
    scanf("%s", Ringsetting);
    scanf("%s", cipher);
    scanf("%s", plain);
    scanf("%d", &ro);
    rotornum[0] = '0' + ro;
    for (i = 0; i <= strlen(cipher) - strlen(plain); i++)
    {
        if (same(i))
            continue;
        for (p = 0; p < strlen(plain); p++)
        {
            temp[p] = cipher[i + p];
        }
        for (j = 1; j <= 5; j++)
        {
            if (j == rotornum[0] - '0')
                continue;
            rotornum[1] = '0' + j;
            for (k = 1; k <= 5; k++)
            {
                if (k == rotornum[0] - '0' || k == rotornum[1] - '0')
                    continue;
                rotornum[2] = '0' + k;
                for (a = 0; a < 26; a++)
                {
                    for (b = 0; b < 26; b++)
                    {
                        for (c = 0; c < 26; c++)
                        {
                            Messagekey[0] = 'A' + a;
                            Messagekey[1] = 'A' + b;
                            Messagekey[2] = 'A' + c;
                            enigma(temp);
                            if (strcmp(secret, plain) == 0)
                            {
                                Messagekey[0] = 'A' + a;
                                Messagekey[1] = 'A' + b;
                                Messagekey[2] = 'A' + c;
                                stepback(i);
                                print();
                                return 0;
                            }
                        }
                    }
                }
            }
        }
    }
}

int len(char *a)
{
    int count = 0;
    while (*a++ != '\0')
        count++;
    return count;
}
void enigma(char *message)
{
    char plu[3], temp;
    int i = 0, j, k;

    for (k = 0; k < len(message); k++)
    {
        temp = message[k];
        changestate();
        temp = plug(temp);
        for (i = 2; i >= 0; i--)
        {
            temp = rotor(i, temp);
        }
        temp = ref(temp);
        for (i = 0; i < 3; i++)
        {
            temp = rerotor(i, temp);
        }
        temp = plug(temp);
        secret[k] = temp;
    }
}

char plug(char temp)
{
    int i, j;
    for (i = 0; i < 10; i++)
    {
        for (j = 0; j < 2; j++)
        {
            if (plugboard[i][j] == temp)
                return plugboard[i][1 - j];
        }
    }
    return temp;
}

char forward(char c)
{
    if (c == 90)
        c = 'A';
    else
        c = c + 1;
    return c;
}

char backward(char c)
{
    return (c - 'A' - 1 + 26) % 26 + 'A';
}
void changestate()
{
    if (Messagekey[2] == step_char[rotornum[2] - '1'])
    {
        if (Messagekey[1] == step_char[rotornum[1] - '1'])
        {
            Messagekey[0] = forward(Messagekey[0]);
        }
        Messagekey[1] = forward(Messagekey[1]);
        Messagekey[2] = forward(Messagekey[2]);
    }
    else
    {
        if (Messagekey[1] == step_char[rotornum[1] - '1'])
        {
            Messagekey[0] = forward(Messagekey[0]);
            Messagekey[1] = forward(Messagekey[1]);
        }
        Messagekey[2] = forward(Messagekey[2]);
    }
}

char rotor(int i, char temp)
{
    int delta = Messagekey[i] - Ringsetting[i];
    temp = ((temp - 'A') + delta + 26) % 26 + 'A';
    temp = rotor_table[rotornum[i] - '1'][temp - 'A'];
    temp = (temp - 'A' - delta + 26) % 26 + 'A';
    return temp;
}

char ref(char temp)
{
    return reflector[temp - 'A'];
}

char rerotor(int i, char temp)
{
    int j = 0;
    int delta = Messagekey[i] - Ringsetting[i];
    temp = ((temp - 'A') + delta + 26) % 26 + 'A';
    while (temp != rotor_table[rotornum[i] - '1'][j])
        j++;
    temp = 'A' + j;
    temp = (temp - 'A' - delta + 26) % 26 + 'A';
    return temp;
}
void stepback(int i)
{
    while (i)
    {
        backone();
    }
}
void backone()
{
    if (Messagekey[2] == stepback_char[rotornum[2] - '1'])
    {
        if (Messagekey[1] == stepback_char[rotornum[1] - '1'])
        {
            Messagekey[0] = backward(Messagekey[0]);
        }
        Messagekey[1] = backward(Messagekey[1]);
        Messagekey[2] = backward(Messagekey[2]);
    }
    else
    {
        if (Messagekey[1] == stepback_char[rotornum[1] - '1'])
        {
            Messagekey[0] = backward(Messagekey[0]);
            Messagekey[1] = backward(Messagekey[1]);
        }
        Messagekey[2] = backward(Messagekey[2]);
    }
}

void print()
{
    printf("MessageKey=%s\n", Messagekey);
    enigma(cipher);
    printf("PlainText=%s\n", secret);
    printf("RotorNum=%s\n", rotornum);
}