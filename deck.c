#include "deck.h"
#include <stdio.h>
#include <stdlib.h>

struct deck* initialize_deck(int cards_count)
{
  // this array represent how many cards are still available
  static int quantity[9] = {4, 4, 4, 4, 4, 4, 4, 4, 4};
  // allocating memory for new_deck struct pointer
  struct deck *new_deck = malloc(sizeof(struct deck));
  // allocating memory for card_list pointer
  new_deck->card_list = malloc(36 * sizeof(int)); // magic number

  // generating cards for player's deck
  for (int i = 0; i < cards_count; i++)
  {
    int index;
    do
    {
      index = rand() % 9;
    } 
    while (quantity[index] == 0);
    
    quantity[index] -= 1;
    new_deck->card_list[i] = index;
  }

  // remove in the future
  for (int i = cards_count; i < 36; i++)
  {
    new_deck->card_list[i] = -1;
  }

  // initialize top and bottom pointers respectivly
  new_deck->top = &new_deck->card_list[0];
  new_deck->bottom = &new_deck->card_list[cards_count - 1];

  return new_deck;
};

void print_deck(struct deck *player)
{
  printf("Cards:  ");

  for (int i = 0; i < 36; i++)
  {
    printf("%d  ", player->card_list[i]);
  }
  printf("\nTop: %d\n", *player->top);
  printf("Bottom: %d\n", *player->bottom);
}