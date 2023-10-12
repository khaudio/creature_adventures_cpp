#include "deck.h"

namespace CreatureAdventures
{

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
    if (std::vector<T>::empty())
    {
        DEBUG_ERR("Deck empty\n");
        throw std::out_of_range("Deck empty");
    }
    T drawn(this->back());
    this->pop_back();
    return drawn;
}

ItemDeck::ItemDeck() :
DeckBase()
{
}

ItemDeck::ItemDeck(const ItemDeck& ref) :
DeckBase(ref),
_potionDeck(ref._potionDeck),
_poisonDeck(ref._poisonDeck),
_elixirDeck(ref._elixirDeck),
_reviveDeck(ref._reviveDeck),
_baitDeck(ref._baitDeck)
{
}

ItemDeck::~ItemDeck()
{
}

size_t ItemDeck::size() const
{
return (
        this->_potionDeck.size()
        + this->_poisonDeck.size()
        + this->_elixirDeck.size()
        + this->_reviveDeck.size()
        + this->_baitDeck.size()
    );
}

bool ItemDeck::empty() const
{
return (
        this->_potionDeck.empty()
        && this->_poisonDeck.empty()
        && this->_elixirDeck.empty()
        && this->_reviveDeck.empty()
        && this->_baitDeck.empty()
    );
}

void ItemDeck::shuffle()
{
    this->_potionDeck.shuffle();
    this->_poisonDeck.shuffle();
    this->_elixirDeck.shuffle();
    this->_reviveDeck.shuffle();
    this->_baitDeck.shuffle();
}

Item ItemDeck::draw()
{
    if (empty())
    {
        DEBUG_ERR("Item deck empty\n");
        throw std::out_of_range("Item deck empty");
    }
    Item* itemPtr = nullptr;
    int typeIndex;

    std::uniform_real_distribution<float> dist(0, (Item::numTypes - 1));

    while (itemPtr == nullptr)
    {
        typeIndex = static_cast<int>(std::round(dist(this->_randGenerator)));
        switch (typeIndex)
        {
            case (0):
                if (!this->_potionDeck.empty())
                {
                    Potion classed = this->_potionDeck.draw();
                    Item item = static_cast<Item>(classed);
                    itemPtr = &item;
                    break;
                }
            case (1):
                if (!this->_poisonDeck.empty())
                {
                    Poison classed = this->_poisonDeck.draw();
                    Item item = static_cast<Item>(classed);
                    itemPtr = &item;
                    break;
                }
            case (2):
                if (!this->_elixirDeck.empty())
                {
                    Elixir classed = this->_elixirDeck.draw();
                    Item item = static_cast<Item>(classed);
                    itemPtr = &item;
                    break;
                }
            case (3):
                if (!this->_reviveDeck.empty())
                {
                    Revive classed = this->_reviveDeck.draw();
                    Item item = static_cast<Item>(classed);
                    itemPtr = &item;
                    break;
                }
            case (4):
                if (!this->_baitDeck.empty())
                {
                    Bait classed = this->_baitDeck.draw();
                    Item item = static_cast<Item>(classed);
                    itemPtr = &item;
                    break;
                }
        }
    }
    return *itemPtr;
}

DeckBuilder::DeckBuilder() :
DeckBase()
{
}

DeckBuilder::DeckBuilder(const DeckBuilder& ref) :
DeckBase(ref),
uidIndex(ref.uidIndex)
{
}

DeckBuilder::~DeckBuilder()
{
}

Creature DeckBuilder::_create_creature(
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
    for (int tier(0); tier < Creature::numTiers; ++tier)
    {
        /* Allow more chaotic stat distribution per tier */
        weightVariance += 0.035f;
        for (int j(0); j < cardsPerTier[tier]; ++j)
        {
            deck.emplace_back(_create_creature(
                    this->uidIndex++,
                    tier,
                    maxPossibleStatPoints,
                    weightVariance
                ));
        }
    }

    return deck;
};

template <typename T>
void DeckBuilder::_fill_single_item_deck(
        Deck<T>* deck,
        int totalMaxNumCards,
        float maxPossibleStatPoints
    )
{
    /* Calculate nubmer of cards per tier */
    std::vector<int> cardsPerTier(_num_cards_per_tier<T>(totalMaxNumCards));

    /* Add cards to each tier */
    for (int tier(0); tier < T::numTiers; ++tier)
    {
        for (int j(0); j < cardsPerTier[tier]; ++j)
        {
            deck->emplace_back(T(
                    this->uidIndex++,
                    tier,
                    maxPossibleStatPoints,
                    false
                ));
        }
    }
}

ItemDeck DeckBuilder::create_item_deck(
        int totalMaxNumCards,
        float maxPossibleStatPoints
    )
{
    ItemDeck itemDeck;
    
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

    _fill_single_item_deck<Potion>(
            &itemDeck._potionDeck,
            designatedSlice,
            std::round(maxPossibleStatPoints / 3)
        );
    _fill_single_item_deck<Poison>(
            &itemDeck._poisonDeck,
            remainingSlice,
            -std::round(maxPossibleStatPoints / 3)
        );
    _fill_single_item_deck<Elixir>(
            &itemDeck._elixirDeck,
            designatedSlice,
            std::round(maxPossibleStatPoints / 5)
        );
    _fill_single_item_deck<Revive>(
            &itemDeck._reviveDeck,
            remainingSlice,
            std::round(maxPossibleStatPoints)
        );
    _fill_single_item_deck<Bait>(
            &itemDeck._baitDeck,
            remainingSlice,
            std::round(maxPossibleStatPoints / 5)
        );

    /* Correct rounding errors by adding
    or removing Potions and Elixirs */
    int correction(totalMaxNumCards - static_cast<int>(itemDeck.size()));
    int index(0);
    while(correction > 0)
    {
        switch (index)
        {
            case (0):
                itemDeck._potionDeck.emplace_back(Potion(
                        this->uidIndex++,
                        0,
                        maxPossibleStatPoints,
                        false
                    ));
                break;
            case (1):
                itemDeck._elixirDeck.emplace_back(Elixir(
                        this->uidIndex++,
                        0,
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
                itemDeck._potionDeck.erase(itemDeck._potionDeck.begin());
            case (1):
                itemDeck._elixirDeck.erase(itemDeck._elixirDeck.begin());
        }
        ++index %= 2;
        ++correction;
    }

    return itemDeck;
}

};

template class CreatureAdventures::Deck<CreatureAdventures::Creature>;