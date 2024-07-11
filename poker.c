//Prosta gra poker, która z talii 24 kart od 9 do asa rozdaje graczom po 5 kart

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>

#define DECK_SIZE 24
#define MAX_PLAYERS 4
#define HAND_SIZE 5
#define NUM_VALUES 6
#define NUM_SUITS 4

const char *values[] = {"9", "10", "J", "Q", "K", "A"}; // J - jopek, Q - dama, K - król, A - as 
const char *suits[] = {"Serce", "Karo", "Trefl", "Pik"};

struct Card
{
    const char *value;
    const char *suit;
};

//funkcja tworząca talię kart
void create_deck(struct Card *deck)
{
    unsigned k = 0;
    for (unsigned i = 0; i < NUM_SUITS; i++)
    {
        for (unsigned j = 0; j < NUM_VALUES; j++)
        {
            deck[k].value = values[j];
            deck[k].suit = suits[i];
            k++;
        }
    }
}

//funkcja tasująca talię
void shuffle_deck(struct Card *deck)
{
    srand(time(NULL));
    for (unsigned i = DECK_SIZE - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        struct Card temp = deck[i];
        deck[i] = deck[j];
        deck[j] = temp;
    }
}

//funkcja wyswietlająca karty graczy
void print_hand(struct Card *hand)
{
    for (unsigned i = 0; i < HAND_SIZE; i++)
    {
        printf("%s of %s\n", hand[i].value, hand[i].suit);
    }
}

//poniżej funkcje sprawdzające kombinacje 
int has_pair(struct Card *hand)
{
    for (int i = 0; i < HAND_SIZE; i++)
    {
        for (int j = i + 1; j < HAND_SIZE; j++)
        {
            if (hand[i].value == hand[j].value)
            {
                return 1;
            }
        }
    }
    return 0;
}

int has_two_pairs(struct Card *hand)
{
    int pairs = 0;
    for (int i = 0; i < HAND_SIZE; i++)
    {
        for (int j = i + 1; j < HAND_SIZE; j++)
        {
            if (hand[i].value = hand[j].value);
            pairs++;
        }
    }
    return pairs == 2;
}

int has_three(struct Card *hand)
{
    for (int i = 0; i < HAND_SIZE; i++)
    {
        int count = 0;
        for (int j = 0; j < HAND_SIZE; j++)
        {
            if (hand[i].value == hand[j].value)
            {
                count++;
            }
        }
        if (count == 3)
        {
            return 1;
        }
    }
    return 0;
}

int has_full_house(struct Card *hand)
{
    return has_pair(hand) && has_three(hand);
}

int has_four(struct Card *hand)
{
    for (int i = 0; i < HAND_SIZE; i++)
    {
        int count = 0;
        for (int j = 0; j < HAND_SIZE; j++)
        {
            if (hand[i].value == hand[j].value)
            {
                count++;
            }
        }
        if (count == 4)
        {
            return 1;
        }
    }
    return 0;
}

int has_flush(struct Card *hand)
{
    for (int i = 0; i < HAND_SIZE; i++)
    {
        if (hand[i].suit != hand[0].suit)
        {
            return 0;
        }
    }
    return 1;
}

//funkcja określająca zwycięzcę (nie jest skończona)
//nie działa w skrócie
int determine_winner(struct Card hand[][HAND_SIZE])
{
    int winner = 0;

    for (int i = 0; i < MAX_PLAYERS; i++)
    {
        if (has_pair(hand[i]))
        {
            return 1;
        }
    }

    for (int i = 0; i < MAX_PLAYERS; i++)
    {
        if (has_two_pairs(hand[i]))
        {
            return 1;
        }
    }

    for (int i = 0; i < MAX_PLAYERS; i++)
    {
        if (has_three(hand[i]))
        {
            return 1;
        }
    }

    for (int i = 0; i < MAX_PLAYERS; i++)
    {
        if (has_four(hand[i]))
        {
            return 1;
        }
    }

    for (int i = 0; i < MAX_PLAYERS; i++)
    {
        if (has_full_house(hand[i]))
        {
            return 1;
        }
    }

    for (int i = 0; i < MAX_PLAYERS; i++)
    {
        if (has_flush(hand[i]))
        {
            return 1;
        }
    }
}

int main()
{
    struct Card deck[DECK_SIZE];
    struct Card hand[MAX_PLAYERS][HAND_SIZE];

    create_deck(deck);
    shuffle_deck(deck);
    
    //rozdanie kart
    unsigned index = 0;
    for (unsigned i = 0; i < HAND_SIZE; i++)
    {
        for (unsigned j = 0; j < MAX_PLAYERS; j++)
        {
            hand[j][i] = deck[index++];
        }
    }

    for (unsigned i = 0; i < MAX_PLAYERS; i++)
    {
        printf("Karty gracza %d:\n", i + 1);
        print_hand(hand[i]);
        printf("\n");
    }

    // okreslenie zwycięzcy nie działa
    // int winner = determine_winner(hand);
    // printf("Wygral: %d\n", winner + 1);
    
    return 0;
}