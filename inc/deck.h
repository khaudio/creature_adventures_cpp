#ifndef CREATUREADVENTURES_DECK_H
#define CREATUREADVENTURES_DECK_H

#include "creature.h"
#include "item.h"

#include <algorithm>
#include <random>

namespace CreatureAdventures
{

class DeckBase;
template <typename T> class Deck;
class ItemDeck;
class DeckBuilder;

class DeckBase
{

protected:

    std::random_device _randDevice;
    std::mt19937_64 _randGenerator;

public:

    DeckBase();
    DeckBase(const DeckBase& ref);

    ~DeckBase();

};

template <typename T>
class Deck : public std::vector<T>, public DeckBase
{

public:

    Deck();
    ~Deck();

    Deck(const Deck& ref);

protected:

    void _sequence_uids(Deck<T>* deck, int length, int index = 1);

public:

    void reset_uids(int index = 1);
    void shuffle();
    T draw();

    /* Add decks together and reset UIDs */
    friend Deck<T> operator+(const Deck<T>& left, const Deck<T>& right)
    {
        Deck<T> deck;
        size_t length(left.size() + right.size());
        deck.reserve(length);
        for (const auto& card: left) deck.emplace_back(card);
        for (const auto& card: right) deck.emplace_back(card);
        deck.reset_uids(1);
        return deck;
    }

    /* Remove cards with matching UIDs */
    friend Deck<T> operator-(const Deck<T>& left, const Deck<T>& right)
    {
        Deck<T> deck;
        deck.reserve(left.size());
        for (const auto& card: left) deck.emplace_back(card);
        for (const auto& card: right)
        {
            for (
                    auto existing = deck.begin();
                    existing != deck.end();
                    ++existing
                )
            {
                if (existing->uid == card.uid)
                {
                    deck.erase(existing);
                    break;
                }
            }
        }
        return deck;
    }

};

// class ItemDeck : public DeckBase
// {

// friend class DeckBuilder;

// protected:

//     // Deck<Potion> _potionDeck;
//     // Deck<Poison> _poisonDeck;
//     // Deck<Elixir> _elixirDeck;
//     // Deck<Revive> _reviveDeck;
//     // Deck<Bait> _baitDeck;

// public:

//     ItemDeck();
//     ItemDeck(const ItemDeck& ref);

//     ~ItemDeck();

//     size_t size() const;
//     bool empty() const;

//     /* Shuffle the deck */
//     void shuffle();

//     /* Draw an item from the deck and return it */
//     Item draw();

// };

class DeckBuilder : public DeckBase
{

protected:

    /* UIDs for cards in a decks begin with 1, rather than 0 */
    int uidIndex = 1;

public:

    DeckBuilder();
    DeckBuilder(const DeckBuilder& ref);

    ~DeckBuilder();

protected:

    template <typename T>
    std::vector<int> _num_cards_per_tier(int totalMaxNumCards);

    /* Create and return a new creature */
    Creature _create_creature(
        int uidNum,
        int tierNum,
        float maxPossibleStatPoints,
        float weightVariance
    );

public:

    Deck<Creature> create_creature_deck(
            int totalMaxNumCards,
            float maxPossibleStatPoints = 30.0
        );

protected:

    template <typename T>
    void _fill_single_item_deck(
            Deck<T>* deck,
            int totalMaxNumCards,
            float maxPossibleStatPoints
        );

public:

    Deck<Item> create_item_deck(
            int totalMaxNumCards,
            float maxPossibleStatPoints
        );

};

};

#endif

