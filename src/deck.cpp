#include "deck.h"

namespace CreatureAdventures
{

template <typename T>
Deck<T>::Deck() :
std::vector<T>()
{
}

template <typename T>
Deck<T>::~Deck()
{
}

template <typename T>
Deck<T>::Deck(const Deck& ref) :
std::vector<T>(ref)
{
}

template <typename T>
void Deck<T>::_sequence_uids(Deck<T>* deck, int length, int index)
{
    for (int i(0); i < length; ++i)
    {
        deck->at(i).uid = index++;
    }
}

template <typename T>
void Deck<T>::reset_uids(int index)
{
    _sequence_uids(this, index);
}

template <typename T>
void Deck<T>::shuffle()
{
    std::shuffle(this->begin(), this->end(), this->_randDevice);
}

template <typename T>
T Deck<T>::draw()
{
    T drawn(this->back());
    this->pop_back();
    return drawn;
}

DeckBuilder::DeckBuilder()
{
}

DeckBuilder::DeckBuilder(const DeckBuilder& ref) :
uidIndex(ref.uidIndex)
{
}

DeckBuilder::~DeckBuilder()
{
}

Creature DeckBuilder::create_creature(
        int uidNum,
        int tierNum,
        float maxPossibleStatPoints,
        float weightVariance
    )
{
    Creature newCreature(uidNum, tierNum);

    /* Calculate total stat points available for this creature */
    std::uniform_real_distribution<float> dist(
            Creature::tierQualityThresholds.at(tierNum).first,
            Creature::tierQualityThresholds.at(tierNum).second
        );
    float remainingStatPoints(std::round(
            maxPossibleStatPoints
            * dist(this->_randGenerator)
        ));
    
    /* Determine how weighted towards HP stats will be distributed */
    dist = std::uniform_real_distribution<float>(
            (0.45f - weightVariance),
            (0.75f + weightVariance)
        );
    float weight(dist(this->_randGenerator));

    /* Assign base HP value */
    newCreature.baseMaxHP = std::round(remainingStatPoints * weight);
    newCreature.heal(newCreature.baseMaxHP);
    remainingStatPoints -= newCreature.baseMaxHP;

    /* Determine attack weighting */
    dist = std::uniform_real_distribution<float>(0.54f, 0.88f);
    newCreature.baseAttack = std::round(
            remainingStatPoints
            * dist(this->_randGenerator)
        );
    remainingStatPoints -= newCreature.baseAttack;

    /* Give remaining points to defense */
    newCreature.baseDefense = std::round(remainingStatPoints);

    return newCreature;
}

Deck<Creature> DeckBuilder::create_creature_deck(
        int totalNumCards,
        float maxPossibleStatPoints
    )
{
    Deck<Creature> deck;
    deck.reserve(totalNumCards);

    /* Calculate nubmer of cards per tier */
    std::vector<int> cardsPerTier;
    cardsPerTier.reserve(Creature::numTiers);
    for (const float& ratio: Creature::tierVolumeRatios)
    {
        cardsPerTier.emplace_back(static_cast<int>(std::round(
                ratio * static_cast<float>(totalNumCards)
            )));
    }

    /* Correct floating point or rounding errors
    by adding or removing common cards */
    int sum(0);
    for (const int& numCards: cardsPerTier)
    {
        sum += numCards;
    }
    cardsPerTier[0] += totalNumCards - sum;

    /* Add cards to each tier */
    float weightVariance(0.0);
    for (int tier(0); tier < Creature::numTiers; ++tier)
    {
        /* Allow more chaotic stat distribution per tier */
        weightVariance += 0.035f;
        for (int j(0); j < cardsPerTier[tier]; ++j)
        {
            deck.emplace_back(create_creature(
                    this->uidIndex++,
                    tier,
                    maxPossibleStatPoints,
                    weightVariance
                ));
        }
    }

    /* Deduplicate UIDs */
    deck.reset_uids();

    return deck;
};

Deck<Item> DeckBuilder::create_single_item_deck(
        int itemType,
        int totalNumCards,
        float maxPossibleStatPoints
    )
{
    Deck<Item> deck;

    deck.emplace_back(Potion(0, 0, maxPossibleStatPoints, false));
    deck.emplace_back(Poison(1, 1, maxPossibleStatPoints, false));

    return deck;
}

// Deck<Item> DeckBuilder::create_item_deck(
//         int totalNumCards,
//         float maxPossibleStatPoints
//     )
// {
//     Deck<Item> itemDeck = create_single_item_deck(0, 2, 30.0f);

//     return itemDeck;
// }

};
