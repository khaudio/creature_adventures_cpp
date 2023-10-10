#include "deck.h"

namespace CreatureAdventures
{

Deck::Deck()
{
}

Deck::~Deck()
{
}

Deck::Deck(const Deck& ref)
{
    reserve(ref.size());
    for (const auto& card: ref)
    {
        this->emplace_back(card);
    }
}

void Deck::_sequence_uids(std::vector<TieredObjectBase>* iterable, int index)
{
    size_t length(iterable->size());
    for (int i(index); i < length; ++i)
    {
        iterable->at(i).uid = i;
    }
}

void Deck::reset_uids(int index)
{
    _sequence_uids(this, index);
}

void Deck::shuffle()
{
    std::shuffle(this->begin(), this->end(), this->_randDevice);
}

TieredObjectBase Deck::draw()
{
    TieredObjectBase drawn(this->back());
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

Deck DeckBuilder::create_creature_deck(
        int totalNumCards,
        float maxPossibleStatPoints
    )
{
    Deck deck;
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

};

