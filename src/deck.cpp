#include "deck.h"

namespace CreatureAdventures
{

template <typename T>
void _sequence_uids(Deck<T>* deck, int length, int index)
{
    for (int i(0); i < length; ++i)
    {
        deck->at(i).uid = index++;
    }
}

DeckBase::DeckBase() :
_randGenerator(std::time(nullptr))
{
}

DeckBase::DeckBase(const DeckBase& ref) :
_randGenerator(ref._randGenerator)
{
}

DeckBase::~DeckBase()
{
}

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
void Deck<T>::reset_uids(int index)
{
    _sequence_uids(this, index);
}

template <typename T>
void Deck<T>::shuffle()
{
    std::shuffle(this->begin(), this->end(), std::random_device());
}

template <typename T>
T Deck<T>::draw()
{
    #if _DEBUG
    if (std::vector<T>::empty())
    {
        throw std::out_of_range("Deck empty");
    }
    #endif

    T drawn(this->back());
    this->pop_back();
    return drawn;
}

DeckBuilder::DeckBuilder() :
DeckBase()
{
}

DeckBuilder::DeckBuilder(const DeckBuilder& ref) :
DeckBase(ref)
{
}

DeckBuilder::~DeckBuilder()
{
}

Creature DeckBuilder::_create_creature(
        TierIndex tierNum,
        float maxPossibleStatPoints,
        float weightVariance
    )
{
    Creature newCreature(tierNum);

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

    /* Evasiveness */
    newCreature.baseEvasiveness = 0.05f;

    return newCreature;
}

template <typename T>
std::vector<int> DeckBuilder::_num_cards_per_tier(int totalMaxNumCards)
{
    /* Calculate nubmer of cards per tier */
    std::vector<int> cardsPerTier;
    cardsPerTier.reserve(T::numTiers);
    for (const float& ratio: T::tierVolumeRatios)
    {
        cardsPerTier.emplace_back(static_cast<int>(std::round(
                ratio * static_cast<float>(totalMaxNumCards)
            )));
    }

    /* Correct floating point or rounding errors
    by adding or removing common cards */
    int sum(0);
    for (const int& numCards: cardsPerTier)
    {
        sum += numCards;
    }
    cardsPerTier[0] += totalMaxNumCards - sum;
    return cardsPerTier;
}

Deck<Creature> DeckBuilder::create_creature_deck(
        int totalMaxNumCards,
        float maxPossibleStatPoints
    )
{
    Deck<Creature> deck;
    deck.reserve(totalMaxNumCards);

    /* Calculate nubmer of cards per tier */
    std::vector<int> cardsPerTier(
            _num_cards_per_tier<Creature>(totalMaxNumCards)
        );

    /* Add cards to each tier */
    float weightVariance(0.0);
    for (const TierIndex& tier: Creature::tiers)
    {
        /* Allow more chaotic stat distribution per tier */
        weightVariance += 0.035f;
        for (int j(0); j < cardsPerTier[tier]; ++j)
        {
            deck.emplace_back(_create_creature(
                    tier,
                    maxPossibleStatPoints,
                    weightVariance
                ));
        }
    }

    return deck;
};

Deck<Item> DeckBuilder::_create_single_item_deck(
        ItemIndex itemTypeIndex,
        int totalMaxNumCards,
        float maxPossibleStatPoints
    )
{
    Deck<Item> deck;

    /* Calculate nubmer of cards per tier */
    std::vector<int> cardsPerTier(_num_cards_per_tier<Item>(totalMaxNumCards));

    int sum(0);
    for (const auto& i: cardsPerTier)
    {
        sum += i;
    }
    deck.reserve(sum);

    /* Add cards to each tier */
    for (const TierIndex& tier: Item::tiers)
    {
        for (int i(0); i < cardsPerTier[tier]; ++i)
        {
            deck.emplace_back(Item(
                    tier,
                    itemTypeIndex,
                    maxPossibleStatPoints,
                    false
                ));
        }
    }

    return deck;
}

Deck<Item> DeckBuilder::create_item_deck(
        int totalMaxNumCards,
        float maxPossibleStatPoints
    )
{
    Deck<Item> deck;

    /* Use a portion for Potions and Elixirs */
    int chunk(static_cast<int>(std::round(
            static_cast<float>(totalMaxNumCards) * 0.6f
        )));
    chunk += (chunk % 2 ? 1 : 0);
    int designatedSlice(chunk / 2);

    /* Use remaining cards to create other items */
    int remainingSlice(static_cast<int>(std::round(
            static_cast<float>(totalMaxNumCards - chunk)
        ) / 3));

    Deck<Item> potions(_create_single_item_deck(
            POTION,
            designatedSlice,
            std::round(maxPossibleStatPoints / 3)
        ));
    Deck<Item> poisons(_create_single_item_deck(
            POISON,
            remainingSlice,
            -std::round(maxPossibleStatPoints / 3)
        ));
    Deck<Item> elixirs(_create_single_item_deck(
            ELIXIR,
            designatedSlice,
            std::round(maxPossibleStatPoints / 5)
        ));
    Deck<Item> revives(_create_single_item_deck(
            REVIVE,
            remainingSlice,
            std::round(maxPossibleStatPoints)
        ));
    Deck<Item> baits(_create_single_item_deck(
            BAIT,
            remainingSlice,
            std::round(maxPossibleStatPoints / 5)
        ));

    /* Correct rounding errors by adding
    or removing Potions and Elixirs */
    size_t numCards = (
            potions.size()
            + poisons.size()
            + elixirs.size()
            + revives.size()
            + baits.size()
        );
    int correction(totalMaxNumCards - static_cast<int>(numCards));
    int index(0);
    while(correction > 0)
    {
        switch (index)
        {
            case (0):
                potions.emplace_back(Item(
                        COMMON,
                        POTION,
                        maxPossibleStatPoints,
                        false
                    ));
                break;
            case (1):
                elixirs.emplace_back(Item(
                        COMMON,
                        ELIXIR,
                        maxPossibleStatPoints,
                        false
                    ));
                break;
        }
        ++index %= 2;
        --correction;
    }
    while (correction < 0)
    {
        switch (index)
        {
            case (0):
                potions.erase(potions.begin());
            case (1):
                elixirs.erase(elixirs.begin());
        }
        ++index %= 2;
        ++correction;
    }

    deck += potions;
    deck += poisons;
    deck += elixirs;
    deck += revives;
    deck += baits;

    return deck;
}

template void _sequence_uids(Deck<Creature>*, int, int);
template void _sequence_uids(Deck<Item>*, int, int);

template class Deck<Creature>;
template class Deck<Item>;

};

