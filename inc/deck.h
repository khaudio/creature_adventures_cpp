#ifndef CREATUREADVENTURES_DECK_H
#define CREATUREADVENTURES_DECK_H

#include "creature.h"
#include "item.h"

#include <algorithm>
#include <random>

namespace CreatureAdventures
{

template <typename T>
class Deck : public std::vector<T>
{

protected:

    std::random_device _randDevice;

public:

    Deck();
    ~Deck();

    Deck(const Deck& ref);

protected:

    virtual void _sequence_uids(Deck<T>* deck, int length, int index = 1);

public:

    virtual void reset_uids(int index = 1);
    virtual void shuffle();
    virtual T draw();

    /* Add decks together and reset UIDs */
    friend Deck<T> operator+(const Deck<T>& left, const Deck<T>& right)
    {
        Deck<T> deck;
        int length(left.size() + right.size());
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

class ItemDeck
{

    // std::vector for each item type

    // abstract draw so that it chooses from a random type deck

public:

    ItemDeck();
    ItemDeck(const ItemDeck& ref);

    ~ItemDeck();


};

class DeckBuilder
{

protected:

    std::random_device _randDevice;
    std::mt19937 _randGenerator;

    /* UIDs for cards in a decks begin with 1, rather than 0 */
    int uidIndex = 1;

public:

    DeckBuilder();
    DeckBuilder(const DeckBuilder& ref);

    ~DeckBuilder();

    /* Create and return a new creature */
    Creature create_creature(
        int uidNum,
        int tierNum,
        float maxPossibleStatPoints,
        float weightVariance
    );

    Deck<Creature> create_creature_deck(
            int totalNumCards,
            float maxPossibleStatPoints = 30.0
        );

    ItemDeck create_single_item_deck(
            int itemType,
            int totalNumCards,
            float maxPossibleStatPoints
        );

    // ItemDeck create_item_deck(
    //         int totalNumCards,
    //         float maxPossibleStatPoints
    //     );

};

};

#endif
