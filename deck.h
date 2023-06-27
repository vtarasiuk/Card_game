#ifndef DECK_H
#define DECK_H

struct deck
{
  int *top;
  int *bottom;
  int *card_list;
};

struct deck* initialize_deck(int cards_count);
void print_deck(struct deck *player);

#endif