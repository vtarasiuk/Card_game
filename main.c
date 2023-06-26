#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CARDS_LENGTH_36 9
static const char *cards[CARDS_LENGTH_36] = {"6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace"};

struct deck
{
  char *top;
  char *bottom;
  int  *card_list;
};

int get_card_index(char *card);
char* get_winner(char *card1, char *card2);
struct deck* create_deck(int size);

int main()
{
  struct deck* player1 = create_deck(36);

  for(int i = 0; i < 36; i++)
  {
    printf("Card: %d\n", player1->card_list[i]);
  }

  return 0;
}


void generate_card_set(size / 2)
{
  
}

struct deck* create_deck(int size)
{
  struct deck *new_deck = malloc(sizeof(struct deck));
  new_deck->card_list = malloc(size * sizeof(int));

  for (int i = 0; i < size; i++)
  {
    new_deck->card_list[i] = rand() % 10;
  }
  generate_card_set(struct deck *, size / 2); // players

  new_deck->top = &new_deck->card_list[0];
  new_deck->bottom = &new_deck->card_list[size - 1];

  return new_deck;
};

int get_card_index(char *card)
{
  for (int i = 0; i < CARDS_LENGTH_36; i++)
  {
    if (strcmp(card, cards[i]) == 0) // equal
    {
      return i;
    }
  }
  return EXIT_FAILURE;
}

char* get_winner(char *card1, char *card2)
{
  int index1 = get_card_index(card1);
  int index2 = get_card_index(card2);

  return ((index1 > index2) ? card1 : card2);
}
