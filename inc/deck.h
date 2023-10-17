#ifndef CREATUREADVENTURES_DECK_H
#define CREATUREADVENTURES_DECK_H

#include "creature.h"
#include "item.h"

#include <algorithm>
#include <random>

namespace CreatureAdventures
{

/* Declarations */
class DeckBase;
template <typename T> class Deck;
class DeckBuilder;

template <typename T>
void _sequence_uids(Deck<T>* deck, int length, int index = 0);

class DeckBase
{

protected:

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

public:

    void reset_uids(int index = 0);
    void shuffle();
    T draw();

    /* Add decks together */
    friend Deck<T> operator+(const Deck<T>& left, const Deck<T>& right)
    {
        Deck<T> deck;
        deck.reserve(left.size() + right.size());
        std::copy(left.begin(), left.end(), deck.begin());
        std::copy(right.begin(), right.end(), std::back_inserter(deck));
        return deck;
    }

    /* Remove cards with matching UIDs */
    friend Deck<T> operator-(const Deck<T>& left, const Deck<T>& right)
    {
        Deck<T> deck(left);
        for (
                auto existing = deck.begin();
                existing != deck.end();
                ++existing
            )
        {
            for (
                    auto it = right.begin();
                    it != right.end();
                    ++it
                )
                {
                    if (it->uid == existing->uid)
                    {
                        deck.erase(existing);
                        break;
                    }
                }
        }

        return deck;
    }

    /* Add decks together */
    Deck<T> operator+=(const Deck<T>& other)
    {
        std::copy(other.begin(), other.end(),  std::back_inserter(*this));
        return *this;
    }

    /* Remove cards with matching UIDs */
    Deck<T> operator-=(const Deck<T>& other)
    {
        *this = *this - other;
        return *this;
    }

};

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
        TierIndex tierNum,
        float maxPossibleStatPoints,
        float weightVariance
    );

public:

    Deck<Creature> create_creature_deck(
            int totalMaxNumCards,
            float maxPossibleStatPoints = 30.0
        );

protected:

    Deck<Item> _create_single_item_deck(
            ItemIndex itemTypeIndex,
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

