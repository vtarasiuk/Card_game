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
      index = rand() % 9; // magic number
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

void free_deck(struct deck *player_deck)
{
  // deallocating memory for card_list pointer
  if (player_deck->card_list != NULL)
  {
    free(player_deck->card_list);
  }

  // deallocating memory for deck structure
  if (player_deck != NULL)
  {
    free(player_deck);
  }
}

struct deck* process_turn(struct deck **players_decks)
{
  // get players cards
  const int player1_card = *players_decks[0]->top;
  const int player2_card = *players_decks[1]->top;

  // compare card values of players decks, choose the winner
  struct deck *winner = get_winner(players_decks);
  if (winner == NULL)
  {
    printf("TIE\n");
    return NULL;
  }

  // calculate indexes to put cards at
  const int index = (winner->bottom + 1 - winner->card_list) % 36; // magic number
  const int new_bottom_index = (index + 1) % 36;
  printf("Index: %d\n", index);
  printf("New bottom index: %d\n", new_bottom_index);

  winner->card_list[index] = player1_card;
  winner->card_list[new_bottom_index] = player2_card; // change in the future
  winner->bottom = &winner->card_list[new_bottom_index];

  // calculate new indexes for top pointer  
  const int new_top_index_player1 = (players_decks[0]->top + 1 - players_decks[0]->card_list) % 36; // magic number
  const int new_top_index_player2 = (players_decks[1]->top + 1 - players_decks[1]->card_list) % 36; // magic number
  // move top card pointers
  players_decks[0]->top = &players_decks[0]->card_list[new_top_index_player1];
  players_decks[1]->top = &players_decks[1]->card_list[new_top_index_player2];

  return NULL;
}

static struct deck* get_winner(struct deck **players_decks)
{
  const bool first_player_winner = *players_decks[0]->top > *players_decks[1]->top;
  const bool tie = *players_decks[0]->top == *players_decks[1]->top;
  
  if (first_player_winner)
  {
    return players_decks[0];
  }
  else if (!tie)
  {
    return players_decks[1];
  }
  else
  {
    return NULL;
  }
}

void print_deck(struct deck *player)
{
  printf("Cards:  ");

  for (int* i = player->top; i <= player->bottom; i++)
  {
    printf("%d  ", *i);
  }
  printf("\nTop: %d\n", *player->top);
  printf("Bottom: %d\n", *player->bottom);
}