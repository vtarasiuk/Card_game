#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h> // setlocale  
#include "deck.h"

#define CARDS_LENGTH_36 9
#define DECK_SIZE 36
static const char *cards[CARDS_LENGTH_36] = {"6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace"};
const int PLAYERS = 2;

void print(int players_count, struct deck **players_decks)
{
  for (int i = 0; i < players_count; i++)
  {
    printf("\nPlayer %d\n", i + 1);
    print_deck(players_decks[i]);
  }
}

int main()
{
  srand(time(NULL));
  
  struct deck** players_decks = malloc(PLAYERS * sizeof(struct deck *)); // [PLAYERS]
  for (int i = 0; i < PLAYERS; i++)
  {
    players_decks[i] = initialize_deck(18, 36); // magic number
  }

  for (int i = 0; i < 10; i++)
  {
    print(PLAYERS, players_decks);
    process_turn(players_decks);
    printf("\n\n");
    getchar();
  }

  for (int i = 0; i < PLAYERS; i++)
  {
    free_deck(players_decks[i]);
  }
  free(players_decks);

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