#ifndef CREATUREADVENTURESDECK_H
#define CREATUREADVENTURESDECK_H

#include "creature.h"
#include "item.h"

#include <algorithm>
#include <random>

namespace CreatureAdventures
{

class Deck : public std::vector<TieredObjectBase>
{

public:

    Deck();
    ~Deck();

    void _sequence_uids(std::vector<TieredObjectBase>* iterable, int index = 1);
    void reset_uids(int index = 1);
    void shuffle();
    TieredObjectBase draw();

    // inline Deck operator+(const Deck& other) const
    // {
    //     *this += other;
    //     _sequence_uids(this);
    //     return this;
    // }
    
    // inline Deck operator-(const Deck& other) const
    // {
    //     *this -= other;
    //     _sequence_uids(this);
    //     return this;
    // }

};

class DeckBuilder
{

protected:

    std::random_device _randDevice;
    std::mt19937 _randGenerator;

public:

    DeckBuilder();
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