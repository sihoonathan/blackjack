#include <iostream>
#include <array>
#include <utility>
#include <cstdlib>

enum Rank
{
    RANK_TWO,
    RANK_THREE,
    RANK_FOUR,
    RANK_FIVE,
    RANK_SIX,
    RANK_SEVEN,
    RANK_EIGHT,
    RANK_NINE,
    RANK_TEN,
    RANK_JACK,
    RANK_QUEEN,
    RANK_KING,
    RANK_ACE,
    MAX_RANKS
};

enum Suits
{
    SUITS_HEART,
    SUITS_SPADE,
    SUITS_CLUB,
    SUITS_DIAMOND,
    MAX_SUITS
};

struct Card
{
    Rank rank;
    Suits suits;
};

void printCard(const Card &selectedCard)
{
    using namespace std;

    switch(selectedCard.rank)
    {
        case RANK_TWO:      cout << "2";  break;
        case RANK_THREE:    cout << "3";  break;
        case RANK_FOUR:     cout << "4";  break;
        case RANK_FIVE:     cout << "5";  break;
        case RANK_SIX:      cout << "6";  break;
        case RANK_SEVEN:    cout << "7";  break;
        case RANK_EIGHT:    cout << "8";  break;
        case RANK_NINE:     cout << "9";  break;
        case RANK_TEN:      cout << "T";  break;
        case RANK_JACK:     cout << "J";  break;
        case RANK_QUEEN:    cout << "Q";  break;
        case RANK_KING:     cout << "K";  break;
        case RANK_ACE:      cout << "A";  break;
    }

    switch(selectedCard.suits)
    {
        case SUITS_CLUB:    cout << "C"; break;
        case SUITS_DIAMOND: cout << "D"; break;
        case SUITS_HEART:   cout << "H"; break;
        case SUITS_SPADE:   cout << "S"; break;
    }
}

void printDeck(const std::array<Card, 52> &deck)
{
    for(const auto &element : deck)
    {
        printCard(element);
        std::cout << ' ';
    }

    std::cout << std::endl;
}

int PRNG(const int min, const int max)
{

    static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);

    return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

void swapCard(Card &card1, Card &card2)
{
    Card temp = card1;
    card1 = card2;
    card2 = temp;
}

void shuffleDeck(std::array<Card, 52> &deck )
{
    for(int index = 0; index < 52; ++index)
    {
        int swapIndex = PRNG(0, 51);
        swapCard(deck[index], deck[swapIndex]);
    }
}

int getCardValue(const Card &card)
{
    switch(card.rank) {

        case RANK_TWO:      return 2;
        case RANK_THREE:    return 3;
        case RANK_FOUR:     return 4;
        case RANK_FIVE:     return 5;
        case RANK_SIX:      return 6;
        case RANK_SEVEN:    return 7;
        case RANK_EIGHT:    return 8;
        case RANK_NINE:     return 9;
        case RANK_TEN:
        case RANK_JACK:
        case RANK_QUEEN:
        case RANK_KING:     return 10;
        case RANK_ACE:      return 11;
    }
}

char getPlayerChoice()
{
    char choice;

    do
    {
        std::cout << "(h) To hit or (s) to stand: ";
        std::cin >> choice;
    } while(choice != 'h' && choice != 's');

    return choice;
}

bool playBlackJack(std::array<Card, 52> &deck)
{

    int dealerScore = 0;
    int playerScore = 0;
    int dealerAce = 0;
    int playerAce = 0;

    const Card *cardPtr = &deck[0];

    std::cout << "Dealer Card: "; printCard(*cardPtr) ; std::cout << std::endl;
    if(cardPtr->rank == RANK_ACE)
        ++dealerAce;
    dealerScore += getCardValue(*cardPtr++);
    std::cout << "Dealer Score: " << dealerScore << std::endl;

    std::cout << "Player Card: "; printCard(*cardPtr); std::cout << std::endl;
    if(cardPtr->rank == RANK_ACE)
        ++playerAce;
    playerScore += getCardValue(*cardPtr++);
    std::cout << "Player Card: "; printCard(*cardPtr); std::cout << std::endl;
    if(cardPtr->rank == RANK_ACE)
        ++playerAce;
    playerScore += getCardValue(*cardPtr++);


    while (true)
    {

        if(playerScore > 21 && playerAce != 0) {
            playerScore -= 10;
            --playerAce;
        }

        std::cout << "Player Score: " << playerScore << std::endl;

        if(playerScore > 21 && playerAce == 0)
        {
            std::cout << "Player Busted!" << '\n';
            return false;
        }

        if(getPlayerChoice() == 's')
            break;

        std::cout << "Player Card: "; printCard(*cardPtr); std::cout << std::endl;
        playerScore += getCardValue(*cardPtr++);
    }

    while(dealerScore <17)
    {
        std::cout << "Dealer Card: "; printCard(*cardPtr) ; std::cout << '\n';
        dealerScore += getCardValue(*cardPtr++);

        if(dealerScore > 21 && dealerAce != 0)
        {
            dealerScore -= 10;
            --dealerAce;
        }

        std::cout << "Dealer Score: " << dealerScore << std::endl;
    }

    if(dealerScore > 21 && dealerAce == 0)
    {
        std::cout << "Dealer Busted!" << std::endl;
        return true;
    }

    return playerScore > dealerScore;
}


int main()
{
    srand(time(0));
    rand();

    std::array<Card, 52> deck;

    int card = 0;

    for(int suit = 0; suit < MAX_SUITS; ++suit)
        for(int rank = 0; rank < MAX_RANKS; ++rank)
        {
            deck[card].suits = static_cast<Suits>(suit);
            deck[card].rank = static_cast<Rank>(rank);
            ++card;
        }

    printDeck(deck);
    shuffleDeck(deck);
    printDeck(deck);

    if(playBlackJack(deck) == true)
        std::cout << "Player Wins." << std::endl;
    else
        std::cout << "Player Loses" << std::endl;

    return 0;
}