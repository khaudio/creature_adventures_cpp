#ifndef CREATUREADVENTURES_DECK_H
#define CREATUREADVENTURES_DECK_H

#include "creature.h"
#include "item.h"

#include <algorithm>
#include <random>

namespace CreatureAdventures
{

class Deck : public std::vector<Creature>
{

protected:

    std::random_device _randDevice;

public:

    Deck();
    ~Deck();

    Deck(const Deck& ref);

protected:

    void _sequence_uids(std::vector<Creature>* iterable, int index = 1);

public:

    void reset_uids(int index = 1);
    void shuffle();
    Creature draw();

    // inline Deck operator+(const Deck& other) const
    // {
    //     *this += other;
    //     return this;
    // }
    
    // inline Deck operator-(const Deck& other) const
    // {
    //     *this -= other;
    //     return this;
    // }

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

    Deck create_creature_deck(
            int totalNumCards,
            float maxPossibleStatPoints = 30.0
        );

};

};

#endif