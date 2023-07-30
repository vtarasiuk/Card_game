#include "deck.h"
#include <stdio.h>
#include <stdlib.h>

struct deck* initialize_deck(int current_cards_count, int max_cards_count)
{
  // this array represent how many cards are still available
  static int quantity[9][4] = {{0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}}; // magic number
  // allocating memory for new_deck struct pointer
  struct deck *new_deck = malloc(sizeof(struct deck));
  // allocating memory for card_list pointer
  new_deck->card_list = malloc(max_cards_count * sizeof(struct card));
  new_deck->available_cards = current_cards_count;

  // generating cards for player's deck
  for (int i = 0; i < current_cards_count; i++)
  {
    int card_index;
    int suit_index;
    do
    {
      card_index = rand() % 9; // magic number
      suit_index = rand() % 4; // magic number
    } 
    while (quantity[card_index][suit_index] == 1);
    
    quantity[card_index][suit_index] = 1;
    new_deck->card_list[i].card = card_index;
    new_deck->card_list[i].suit = suit_index + 3;
  }

  // initialize top and bottom pointers respectively
  new_deck->top = &new_deck->card_list[0];
  new_deck->bottom = &new_deck->card_list[current_cards_count - 1];

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
  const struct card *player1_card = players_decks[0]->top;
  const struct card *player2_card = players_decks[1]->top;

  // tie case processing
  if (player1_card->card == player2_card->card)
  {
    printf("TIE\n");
    return NULL;
  }

  // compare card values of players decks, choose the winner
  struct deck *winner = get_winner_or_loser(players_decks, 0, is_winner);
  struct deck *loser = get_winner_or_loser(players_decks, 0, is_loser); 

  printf("Winner is: %d\n", winner->top->card);
  printf("Loser is: %d\n", loser->top->card);

  // calculate indexes to put cards at
  const int index = (winner->bottom + 1 - winner->card_list) % 36; // magic number
  const int new_bottom_index = (index + 1) % 36;
  printf("Index: %d\n", index);
  printf("New bottom index: %d\n", new_bottom_index);

  winner->card_list[index].card = player1_card->card;
  winner->card_list[index].suit = player1_card->suit;

  winner->card_list[new_bottom_index].card = player2_card->card; // change in the future
  winner->card_list[new_bottom_index].suit = player2_card->suit; // change in the future

  winner->bottom = &winner->card_list[new_bottom_index];
  winner->available_cards += 1;
  loser->available_cards -= 1;

  // function in the future
  // calculate new indexes for top pointer  
  const int new_top_index_player1 = (players_decks[0]->top + 1 - players_decks[0]->card_list) % 36; // magic number
  const int new_top_index_player2 = (players_decks[1]->top + 1 - players_decks[1]->card_list) % 36; // magic number
  // move top card pointers
  players_decks[0]->top = &players_decks[0]->card_list[new_top_index_player1];
  players_decks[1]->top = &players_decks[1]->card_list[new_top_index_player2];

  return NULL;
}

static struct deck* get_winner_or_loser(struct deck **players_decks, int card_index, bool (*winner_or_loser) (int first_card, int second_card))
{ 
  const int card_number = get_winner_or_loser_card(&players_decks[0]->card_list[card_index], &players_decks[1]->card_list[card_index], winner_or_loser);
  
  for (int i = 0; i < 2; i++)
  {
    if (players_decks[i]->card_list[card_index].card == card_number)
    {
      return players_decks[i];
    }
  }
  
  return NULL;
}

static bool is_winner(int first_card, int second_card)
{
  return first_card > second_card;
}

static bool is_loser(int first_card, int second_card)
{
  return !is_winner(first_card, second_card);
}

static int get_winner_or_loser_card(struct card *first_card, struct card *second_card, bool (*winner_or_loser) (int first_card, int second_card))
{ 
  if (winner_or_loser(first_card->card, second_card->card))
  {
    return first_card->card;
  }
  
  return second_card->card;
}

void print_deck(struct deck *player)
{
  printf("Cards:  ");

  for (struct card *i = player->top; i <= player->bottom; i++)
  {
    printf("%d:%c    ", i->card, i->suit);
  }
  printf("\nTop: %d:%c\n", player->top->card, player->top->suit);
  printf("Bottom: %d:%c\n", player->bottom->card, player->bottom->suit);
  printf("Available cards: %d\n", player->available_cards);
}