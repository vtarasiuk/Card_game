#ifndef DECK_H
#define DECK_H

#include <stdbool.h>

struct deck
{
  int *top;
  int *bottom;
  int *card_list;
};

struct deck* initialize_deck(int cards_count);
void free_deck(struct deck *player_deck);
void print_deck(struct deck *player);
struct deck* process_turn(struct deck **players_decks);
static struct deck* get_winner(struct deck **players_decks);

#endif