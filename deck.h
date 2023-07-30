#ifndef DECK_H
#define DECK_H

#include <stdbool.h>
#include <wchar.h> // unicode

struct card
{
  int card;
  int suit;
};

struct deck
{
  struct card *top;
  struct card *bottom;
  struct card *card_list;
  int available_cards;
};

struct deck* initialize_deck(int current_cards_count, int max_cards_count);
void free_deck(struct deck *player_deck);
void print_deck(struct deck *player);
struct deck* process_turn(struct deck **players_decks);
static struct deck* get_winner_or_loser(struct deck **players_decks, int card_index, bool (*winner_or_loser) (int first_card, int second_card));
static bool is_winner(int first_card, int second_card);
static bool is_loser(int first_card, int second_card);
static int get_winner_or_loser_card(struct card *first_card, struct card *second_card, bool (*winner_or_loser) (int first_card, int second_card));

#endif