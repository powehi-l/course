// char reflector[] = "YRUHQSLDPXNGOKMIEBFZCWVJAT";
// char rotor_table[5][27] =
//     {
//         "EKMFLGDQVZNTOWYHXUSPAIBRCJ",
//         "AJDKSIRUXBLHWTMCQGZNPYFVOE",
//         "BDFHJLCPRTXVZNYEIWGAKMUSQO",
//         "ESOVPZJAYQUIRHXLNFTGKDCMWB",
//         "VZBRGITYUPSDNHLXAWMJQOFECK"};
// char step_char[5] = "RFWKA"; // Royal Flags Wave Kings Above

#include <stdio.h>
#include <string.h>
#include <time.h>

char reflector[] = "YRUHQSLDPXNGOKMIEBFZCWVJAT";
char rotor_table[5][27] =
    {
        "EKMFLGDQVZNTOWYHXUSPAIBRCJ",
        "AJDKSIRUXBLHWTMCQGZNPYFVOE",
        "BDFHJLCPRTXVZNYEIWGAKMUSQO",
        "ESOVPZJAYQUIRHXLNFTGKDCMWB",
        "VZBRGITYUPSDNHLXAWMJQOFECK"};
char Messagekey[5], Ringsetting[5], rotornum[5];
char plugboard[40];
char message[500], secret[100];
char step_char[5] = "QEVJZ";
char forward(char c)
{
    if (c == 90)
        c = 'A';
    else
        c = c + 1;
    return c;
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

char plug(char temp)
{
    int i = 0;
    while (plugboard[i] != 0)
    {
        if (temp == plugboard[i])
        {
            if (i % 2 == 0)
                temp = plugboard[i + 1];
            else
                temp = plugboard[i - 1];
            return temp;
        }
        i++;
    }
    return temp;
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
int main()
{

    char temp;
    char plu[3];
    clock_t start, end;
    double duration;
    int i = 0, j, k;
    printf("Enter Messagekey:");
    scanf("%s", Messagekey);
    printf("Enter Ringseeting:");
    scanf("%s", Ringsetting);
    printf("Enter rotornum:");
    scanf("%s", rotornum);
    printf("Enter plugboard:");
    scanf("%s", plugboard);
    printf("Enter Massage: ");
    scanf("%s", message);
    start = clock();
    for (j = 0; j < 10000; j++)
    {
        for (k = 0; k < strlen(message); k++)
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
    end = clock();
    duration = (double)(end - start) / CLK_TCK;
    printf("%s\n", secret);
    printf("%lf", duration);
}
