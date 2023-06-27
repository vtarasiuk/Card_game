#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "deck.h"

#define CARDS_LENGTH_36 9
#define DECK_SIZE 36
static const char *cards[CARDS_LENGTH_36] = {"6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace"};

// int get_card_index(char *card);
int get_winner(struct deck **players);

int main()
{
  srand(time(NULL));
  int players_count = 0;
  printf("How many players? ");
  scanf("%d", &players_count);
  // players validation
  
  struct deck** players_decks = malloc(players_count * sizeof(struct deck *));
  for (int i = 0; i < players_count; i++)
  {
    players_decks[i] = initialize_deck(36 / players_count);
  }
  
  for (int i = 0; i < players_count; i++)
  {
    printf("\nPlayer %d\n", i + 1);
    print_deck(players_decks[i]);
  }

  printf("Winner is %d\n", get_winner(players_decks));
  
  return 0;
}

// int get_card_index(char *card)
// {
//   for (int i = 0; i < CARDS_LENGTH_36; i++)
//   {
//     if (strcmp(card, cards[i]) == 0) // equal
//     {
//       return i;
//     }
//   }
//   return EXIT_FAILURE;
// }

int get_winner(struct deck **players)
{
  return ((*players[0]->top > *players[1]->top) ? *players[0]->top : *players[1]->top);
}
