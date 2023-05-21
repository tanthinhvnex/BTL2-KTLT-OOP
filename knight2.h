#ifndef __KNIGHT2_H__
#define __KNIGHT2_H__

#include "main.h"

// #define DEBUG
class BaseItem;
class Events;
class BaseKnight;
class BaseBag;
class ArmyKnights;

enum ItemType
{ /* TODO: */
  ANTIDOTE = 1,
  PHOENIXDOWNI,
  PHOENIXDOWNII,
  PHOENIXDOWNIII,
  PHOENIXDOWNIV,
  PHOENIXDOWNALL,
  ALL
};

class BaseBag
{
private:
protected:
    BaseKnight *knight; // de yeu cau
    // BaseBag *bag;
    BaseItem *head = NULL;
    int max_item;
    long long amount_items = 0;
    int amount_phoenixdownI = 0;
    int amount_antidote = 0;

public:
    virtual bool insertFirst(BaseItem *item) = 0;
    virtual BaseItem *get(ItemType itemType) = 0;
    virtual string toString() const = 0;
    ~BaseBag();
};
class KnightBag : public BaseBag
{
public:
    bool insertFirst(BaseItem *item);
    BaseItem *get(ItemType itemType);
    BaseItem *getHead(BaseItem *baseItem);
    BaseItem *getTail(BaseItem *preBaseItem, BaseItem *baseItem);
    BaseItem *getMiddle(BaseItem *preBaseItem, BaseItem *baseItem);
    string toString() const;
};
class PaladinBag : public KnightBag
{
private:
public:
    PaladinBag(BaseKnight *, int, int);
};
class LancelotBag : public KnightBag
{
private:
public:
    LancelotBag(BaseKnight *, int phoenix, int antidote);
};
class DragonBag : public KnightBag
{
private:
public:
    DragonBag(BaseKnight *, int phoenix, int antidote);
};
class NormalBag : public KnightBag
{
private:
public:
    NormalBag(BaseKnight *, int phoenix, int antidote);
};

class BaseOpponent
{
private:
    // BaseOpponent *opponent;
protected:
    int id_opponent;
    int levelO;

public:
    friend class ArmyKnights;
    virtual bool fight_opponent(ArmyKnights *, BaseKnight *, int) = 0;
};
class Opponent_1_5 : public BaseOpponent
{
protected:
    int baseDamage;
    int gil;

public:
    Opponent_1_5(int id_opponent, int baseDamage, int gil);
    friend class ArmyKnights;
    bool fight_opponent(ArmyKnights *, BaseKnight *knight, int index_event);
};
class Tornbery : public BaseOpponent
{
protected:
    int id_opponent = 6;

public:
    friend class ArmyKnights;
    bool fight_opponent(ArmyKnights *, BaseKnight *knight, int index_event);
};
class QueenOfCards : public BaseOpponent
{
protected:
    int id_opponent = 7;

public:
    friend class ArmyKnights;
    bool fight_opponent(ArmyKnights *, BaseKnight *knight, int index_event);
};

class NinaDeRings : public BaseOpponent
{
protected:
    int id_opponent = 8;

public:
    friend class ArmyKnights;
    bool fight_opponent(ArmyKnights *, BaseKnight *knight, int index_event);
};

class DurianGarden : public BaseOpponent
{
protected:
    int id_opponent = 9;

public:
    friend class ArmyKnights;
    bool fight_opponent(ArmyKnights *, BaseKnight *knight, int index_event);
};

class OmegaWeapon : public BaseOpponent
{
protected:
    int id_opponent = 10;

public:
    friend class ArmyKnights;
    bool fight_opponent(ArmyKnights *, BaseKnight *knight, int index_event);
};

class Hades : public BaseOpponent
{
protected:
    int id_opponent = 11;

public:
    friend class ArmyKnights;
    bool fight_opponent(ArmyKnights *, BaseKnight *knight, int index_event);
};

class Ultimecia : public BaseOpponent
{
protected:
    int id_opponent = 99;
    int HP = 5000;

public:
    friend class ArmyKnights;
    bool fight_opponent(ArmyKnights *, BaseKnight *knight, int index_event);
};

enum KnightType
{
    PALADIN = 0,
    LANCELOT = 1,
    DRAGON = 2,
    NORMAL = 3
};
class BaseKnight
{
protected:
    int id;
    int hp;
    int maxhp;
    int level;
    int gil;
    int antidote;
    int phoenixdownI;
    BaseBag *bag;
    KnightType knightType;

public:
    friend void ResidualItem(ArmyKnights *, BaseKnight *, BaseItem *);
    friend void ResidualGil(ArmyKnights *, BaseKnight *);
    friend bool Recuperate(BaseKnight *);
    friend class Antidote;
    friend class PhoenixDownI;
    friend class PhoenixDownII;
    friend class PhoenixDownIII;
    friend class PhoenixDownIV;
    friend class Opponent_1_5;
    friend class Tornbery;
    friend class QueenOfCards;
    friend class NinaDeRings;
    friend class DurianGarden;
    friend class OmegaWeapon;
    friend class Hades;
    friend class Ultimecia;
    friend class BaseBag;
    friend class KnightBag;
    friend class PaladinBag;
    friend class DragonBag;
    friend class LancelotBag;
    friend class NormalBag;
    friend class ArmyKnights;
    friend class KnightAdventure;
    static BaseKnight *create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
    string toString() const;
    ~BaseKnight();
};

class PaladinKnight : public BaseKnight
{
public:
    PaladinKnight(int, int, int, int, int, int);
};

class LancelotKnight : public BaseKnight
{
public:
    LancelotKnight(int, int, int, int, int, int);
};

class DragonKnight : public BaseKnight
{
public:
    DragonKnight(int, int, int, int, int, int);
};

class NormalKnight : public BaseKnight
{
public:
    NormalKnight(int, int, int, int, int, int);
};

class ArmyKnights
{
private:
    int amount_knights;
    int index_event; // Bắt đầu tính từ 0
    BaseKnight *ptr_knight;
    BaseKnight *last_knight;
    BaseKnight **arr_knights;
    bool isOmega;
    bool isHades;
    bool isPaladinShield;
    bool isLancelotSpear;
    bool isGuinevereHair;
    bool isExcaliburSword;

public:
    friend void ResidualItem(ArmyKnights *, BaseKnight *, BaseItem *);
    friend void ResidualGil(ArmyKnights *, BaseKnight *);
    friend class Ultimecia;
    friend class Hades;
    friend class OmegaWeapon;
    friend class KnightAdventure;
    ArmyKnights(const string &file_armyknights);
    ~ArmyKnights();
    bool fight(BaseOpponent *opponent);
    bool adventure(Events *events);
    int count() const;
    BaseKnight *lastKnight() const;

    bool hasPaladinShield() const;
    bool hasLancelotSpear() const;
    bool hasGuinevereHair() const;
    bool hasExcaliburSword() const;

    void printInfo() const;
    void printResult(bool win) const;
};

class BaseItem
{
private:
protected:
    BaseItem *next;
    ItemType itemType;

public:
    friend class BaseBag;
    friend class KnightBag;
    friend class PaladinBag;
    friend class DragonBag;
    friend class NormalBag;
    friend class LancelotBag;
    virtual bool canUse(BaseKnight *knight) = 0;
    virtual void use(BaseKnight *knight) = 0;
    ~BaseItem();
};

class Antidote : public BaseItem
{
private:
    bool isPoison;

public:
    Antidote();
    bool canUse(BaseKnight *knight);
    void use(BaseKnight *knight);
};

class PhoenixDownI : public BaseItem
{
public:
    PhoenixDownI();
    bool canUse(BaseKnight *knight);
    void use(BaseKnight *knight);
};

class PhoenixDownII : public BaseItem
{
public:
    PhoenixDownII();
    bool canUse(BaseKnight *knight);
    void use(BaseKnight *knight);
};

class PhoenixDownIII : public BaseItem
{
public:
    PhoenixDownIII();
    bool canUse(BaseKnight *knight);
    void use(BaseKnight *knight);
};

class PhoenixDownIV : public BaseItem
{
public:
    PhoenixDownIV();
    bool canUse(BaseKnight *knight);
    void use(BaseKnight *knight);
};

class Events
{
private:
    int amount_events;
    int *arr_events;

public:
    friend class ArmyKnights;
    friend class KnightAdventure;
    Events(const string &file_events);
    int count() const;
    int get(int i) const;
    ~Events();
};

class KnightAdventure
{
private:
    ArmyKnights *armyKnights;
    Events *events;

public:
    KnightAdventure();
    ~KnightAdventure(); // TODO:

    void loadArmyKnights(const string &);
    void loadEvents(const string &);
    void run();
};

bool isPrime(int);
bool isPytago(int);
bool Recuperate(BaseKnight *);
void ResidualGil(ArmyKnights *army, BaseKnight *knight);

#endif // __KNIGHT2_H__