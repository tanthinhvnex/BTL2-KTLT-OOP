#include "knight2.h"

/* * * BEGIN implementation of class BaseBag * * */
BaseBag::~BaseBag()
{
    BaseItem *tmp = head;
    for (int i = 0; i < amount_items; i++)
    {
        head = head->next;
        delete tmp;
        tmp = head;
    }
    amount_items = 0;
}
/* * * END implementation of class BaseBag * * */

/* * * BEGIN implementation of class KnightBag * * */
bool KnightBag::insertFirst(BaseItem *item)
{
    if ((item->itemType == 2 && amount_phoenixdownI == 5) || (item->itemType == 1 && amount_antidote == 5) || (knight->knightType == 2 && item->itemType == 1))
    {
        return false;
    }
    if (amount_items < max_item || knight->knightType == 0)
    {
        item->next = this->head;
        head = item;
        ++amount_items;
        if (item->itemType == 2)
        {
            ++amount_phoenixdownI;
        }
        if (item->itemType == 1)
        {
            ++amount_antidote;
        }
        return true;
    }
    return false;
}
BaseItem *KnightBag::getHead(BaseItem *baseItem)
{
    // Tra ve BaseItem o vi tri dau tien trong danh sach
    BaseItem *tmp = baseItem;
    tmp = tmp->next;
    head = tmp;
    baseItem->next = nullptr;
    --amount_items;
    return baseItem;
}
BaseItem *KnightBag::getTail(BaseItem *preBaseItem, BaseItem *baseItem)
{
    // Tra ve BaseItem o vi tri cuoi trong danh sach
    // Dich chuyen head thanh tail
    // Doi node head thanh node tail
    if (head == preBaseItem)
    {
        head->next = nullptr;
    }
    else
    {
        BaseItem *tmpHead = head;
        head = head->next;
        tmpHead->next = nullptr;
        preBaseItem->next = tmpHead;
    }
    --amount_items;
    return baseItem;
}
BaseItem *KnightBag::getMiddle(BaseItem *preBaseItem, BaseItem *baseItem)
{
    // Lay node baseItem ra
    // Chen node head vao vi tri cua node baseItem
    BaseItem *afterItem = baseItem->next;
    BaseItem *tmpHead = head;
    if (head == preBaseItem)
    {
        head->next = baseItem->next;
    }
    else
    {
        head = head->next;
        preBaseItem->next = tmpHead;
        tmpHead->next = afterItem;
    }
    --amount_items;
    baseItem->next = nullptr;
    return baseItem;
}
BaseItem *KnightBag::get(ItemType itemType)
{
    BaseItem *tmp = this->head;
    BaseItem *pre = nullptr;
    for (int i = 0; i < amount_items; i++)
    {
        if (((itemType == tmp->itemType || (itemType == PHOENIXDOWNALL && tmp->itemType != ANTIDOTE)) && (tmp->canUse(knight))) || (itemType == ALL))
        {
            if (i == 0)
            {
                return getHead(tmp);
            }
            else if (i == amount_items - 1)
            {
                return getTail(pre, tmp);
            }
            else
            {
                return getMiddle(pre, tmp);
            }
        }
        pre = tmp;
        tmp = tmp->next;
    }
    return nullptr;
}
string KnightBag::toString() const
{
    string s = "Bag[count=";
    s += to_string(amount_items) + ";";
    BaseItem *tmp = head;
    for (int i = 0; i < amount_items; i++)
    {
        if (tmp->itemType == 1)
        {
            s += "Antidote,";
        }
        else if (tmp->itemType == 2)
        {
            s += "PhoenixI,";
        }
        else if (tmp->itemType == 3)
        {
            s += "PhoenixII,";
        }
        else if (tmp->itemType == 4)
        {
            s += "PhoenixIII,";
        }
        else
        {
            s += "PhoenixIV,";
        }
        tmp = tmp->next;
    }
    if (amount_items)
        s.erase(s.length() - 1, 1);
    s += "]";
    return s;
}
/* * * END implementation of class KnightBag * * */

/* * * BEGIN implementation of class PaladinBag * * */
PaladinBag::PaladinBag(BaseKnight *knight, int phoenixdownI, int antidote)
{
    this->knight = knight;
    this->max_item = 1e6;
    for (int i = 0; i < phoenixdownI; i++)
    {
        PhoenixDownI *tmp = new PhoenixDownI();
        if (!this->insertFirst(tmp))
        {
            break;
        }
    }
    for (int i = 0; i < antidote; i++)
    {
        Antidote *tmp = new Antidote;
        if (!this->insertFirst(tmp))
        {
            break;
        }
    }
}
/* * * END implementation of class PaladinBag * * */

/* * * BEGIN implementation of class LancelotBag * * */
LancelotBag::LancelotBag(BaseKnight *knight, int phoenixdownI, int antidote)
{
    this->knight = knight;
    this->max_item = 16;
    for (int i = 0; i < phoenixdownI; i++)
    {
        PhoenixDownI *tmp = new PhoenixDownI();
        this->insertFirst(tmp);
    }
    for (int i = 0; i < antidote; i++)
    {
        Antidote *tmp = new Antidote;
        this->insertFirst(tmp);
    }
}

/* * * END implementation of class LancelotBag * * */

/* * * BEGIN implementation of class DragonBag * * */
DragonBag::DragonBag(BaseKnight *knight, int phoenixdownI, int antidote)
{
    // Dragon khong bi trung doc nen tui do khong co antidote
    this->knight = knight;
    this->max_item = 14;
    for (int i = 0; i < phoenixdownI; i++)
    {
        PhoenixDownI *tmp = new PhoenixDownI();
        this->insertFirst(tmp);
    }
}
/* * * END implementation of class DragonBag * * */

/* * * BEGIN implementation of class NormalBag * * */
NormalBag::NormalBag(BaseKnight *knight, int phoenixdownI, int antidote)
{
    this->knight = knight;
    this->max_item = 19;
    for (int i = 0; i < phoenixdownI; i++)
    {
        PhoenixDownI *tmp = new PhoenixDownI();
        this->insertFirst(tmp);
    }
    for (int i = 0; i < antidote; i++)
    {
        Antidote *tmp = new Antidote;
        this->insertFirst(tmp);
    }
}
/* * * END implementation of class NormalBag * * */

/* * * BEGIN implementation of class BaseOpponent * * */
/* * * END implementation of class BaseOpponent * * */

/* * * BEGIN implementation of class Opponent_1_5 * * */
Opponent_1_5::Opponent_1_5(int id_opponent, int baseDamage, int gil)
{
    this->id_opponent = id_opponent;
    this->baseDamage = baseDamage;
    this->gil = gil;
    this->levelO = 0;
}
bool Opponent_1_5::fight_opponent(ArmyKnights *army, BaseKnight *knight, int index_event)
{
    // Gia tri tra ve bool the hien knight con song hay khong
    bool flag = true;
    this->levelO = (index_event + this->id_opponent) % 10 + 1;
    // if win
    if (knight->level >= levelO || knight->knightType == 1 || knight->knightType == 0)
    {
        knight->gil += gil;
        if (knight->gil > 999)
        {
            ResidualGil(army, knight);
        }
        return true;
    }
    // if close
    else
    {
        knight->hp -= baseDamage * (levelO - knight->level);
        flag = Recuperate(knight);
    }
    return flag || (knight->hp > 0);
}
/* * * END implementation of class Opponent_1_5 * * */

/* * * BEGIN implementation of class Tornbery * * */
bool Tornbery::fight_opponent(ArmyKnights *army, BaseKnight *knight, int index_event)
{
    bool flag = true;
    this->levelO = (index_event + this->id_opponent) % 10 + 1;
    // if win
    if (knight->level >= levelO)
    {
        knight->level += 1;
        if (knight->level > 10)
        {
            knight->level = 10;
        }
        return true;
    }
    // if close
    else if (knight->knightType != 2)
    {
        BaseItem *tmpBaseItem = knight->bag->get(ANTIDOTE);
        // Co duoc thuoc giai doc
        if (tmpBaseItem)
        {
            tmpBaseItem->use(knight);
            delete tmpBaseItem;
            return true;
        }
        // Khong co thuoc giai doc
        else
        {
            for (int i = 0; i < 3; i++)
            {
                tmpBaseItem = knight->bag->get(ALL);
                if (!tmpBaseItem)
                {
                    break;
                }
                delete tmpBaseItem;
            }
            knight->hp -= 10;
            flag = Recuperate(knight);
        }
    }
    return flag || (knight->hp > 0);
}
/* * * END implementation of class Tornbery * * */

/* * * BEGIN implementation of class QueenOfCards * * */
bool QueenOfCards::fight_opponent(ArmyKnights *army, BaseKnight *knight, int index_event)
{
    this->levelO = (index_event + this->id_opponent) % 10 + 1;
    // if win
    if (knight->level >= levelO)
    {
        knight->gil *= 2;
        if (knight->gil > 999)
        {
            ResidualGil(army, knight);
        }
    }
    // if close
    else if (knight->knightType != 0)
    {
        knight->gil /= 2;
    }
    return true;
}
/* * * END implementation of class QueenOfCards * * */

/* * * BEGIN implementation of class NinaDeRings * * */
bool NinaDeRings::fight_opponent(ArmyKnights *army, BaseKnight *knight, int index_event)
{
    if (knight->gil >= 50 || knight->knightType == 0)
    {
        if (knight->hp < knight->maxhp / 3)
        {
            knight->hp += knight->maxhp / 5;
            if (knight->knightType != 0)
            {
                knight->gil -= 50;
            }
        }
    }
    return true;
}
/* * * END implementation of class NinaDeRings * * */

/* * * BEGIN implementation of class DurianGarden * * */
bool DurianGarden::fight_opponent(ArmyKnights *army, BaseKnight *knight, int index_event)
{
    knight->hp = knight->maxhp;
    return true;
}
/* * * END implementation of class DurianGarden * * */

/* * * BEGIN implementation of class OmegaWeapon * * */
bool OmegaWeapon::fight_opponent(ArmyKnights *army, BaseKnight *knight, int index_event)
{
    bool flag = true;
    // if win
    if ((knight->level == 10 && knight->hp == knight->maxhp) || (knight->knightType == 2))
    {
        knight->level = 10;
        knight->gil = 999;
        army->isOmega = true;
    }
    // if close
    else
    {
        knight->hp = 0;
        flag = Recuperate(knight);
    }
    return flag || (knight->hp > 0);
}
/* * * END implementation of class OmegaWeapon * * */

/* * * BEGIN implementation of class Hades * * */
bool Hades::fight_opponent(ArmyKnights *army, BaseKnight *knight, int index_event)
{
    bool flag = true;
    if ((knight->level == 10) || (knight->knightType == 0 && knight->level >= 8))
    {
        army->isHades = true;
        army->isPaladinShield = true;
        return true;
    }
    else
    {
        knight->hp = 0;
        flag = Recuperate(knight);
    }
    return flag || (knight->hp > 0);
}
/* * * END implementation of class Hades * * */

/* * * BEGIN implementation of class Ultimecia * * */
bool Ultimecia::fight_opponent(ArmyKnights *army, BaseKnight *knight, int index_event)
{
    // Bien count la index
    // Bien amount_knights luc nay khong the hien duoc so luong knight con song
    // Ma danh dau index cua last_knight
    int count = army->amount_knights;
    while (count > 0)
    {
        if (knight->knightType == 0)
        {
            HP -= (knight->hp) * (knight->level) * 0.06;
        }
        else if (knight->knightType == 1)
        {
            HP -= (knight->hp) * (knight->level) * 0.05;
        }
        else if (knight->knightType == 2)
        {
            HP -= (knight->hp) * (knight->level) * 0.075;
        }
        if (HP <= 0)
        {
            return true;
        }
        if (knight->knightType != 3)
        {
            knight->hp = -1e6;
            // Bien amount_knights luc nay khong the hien duoc so luong knight con song
            // Ma danh dau index cua last_knight
            --army->amount_knights;
            if (knight->id == army->last_knight->id)
            {
                army->last_knight = army->arr_knights[army->amount_knights - 1];
            }
        }
        --count;
        knight = army->arr_knights[count - 1];
    }
    army->amount_knights = 0;
    return false;
}
/* * * END implementation of class Ultimecia * * */

/* * * BEGIN implementation of class BaseKnight * * */
BaseKnight *BaseKnight::create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI)
{
    if (isPrime(maxhp))
    {
        return new PaladinKnight(id, maxhp, level, gil, antidote, phoenixdownI);
    }
    else if (maxhp == 888)
    {
        return new LancelotKnight(id, maxhp, level, gil, antidote, phoenixdownI);
    }
    else if ((maxhp > 99 && maxhp < 1000) && isPytago(maxhp))
    {
        return new DragonKnight(id, maxhp, level, gil, antidote, phoenixdownI);
    }
    else
    {
        return new NormalKnight(id, maxhp, level, gil, antidote, phoenixdownI);
    }

    return 0;
}

string BaseKnight::toString() const
{
    string typeString[4] = {"PALADIN", "LANCELOT", "DRAGON", "NORMAL"};
    // inefficient version, students can change these code
    //      but the format output must be the same
    string s("");
    s += "[Knight:id:" + to_string(id) + ",hp:" + to_string(hp) + ",maxhp:" + to_string(maxhp) + ",level:" + to_string(level) + ",gil:" + to_string(gil) + "," + bag->toString() + ",knight_type:" + typeString[knightType] + "]";
    return s;
}
BaseKnight::~BaseKnight()
{
    delete bag;
}

/* * * END implementation of class BaseKnight * * */

/* * * BEGIN implementation of class PaladinKnight * * */
PaladinKnight::PaladinKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI)
{
    this->id = id;
    this->hp = maxhp;
    this->maxhp = maxhp;
    this->level = level;
    this->gil = gil;
    this->antidote = antidote;
    this->phoenixdownI = phoenixdownI;
    this->knightType = PALADIN;
    this->bag = new PaladinBag(this, phoenixdownI, antidote);
}
/* * * END implementation of class PaladinKnight * * */

/* * * BEGIN implementation of class LancelotKnight * * */
LancelotKnight::LancelotKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI)
{
    this->id = id;
    this->hp = maxhp;
    this->maxhp = maxhp;
    this->level = level;
    this->gil = gil;
    this->antidote = antidote;
    this->phoenixdownI = phoenixdownI;
    this->knightType = LANCELOT;
    this->bag = new LancelotBag(this, phoenixdownI, antidote);
}
/* * * END implementation of class LancelotKnight * * */

/* * * BEGIN implementation of class DragonKnight * * */
DragonKnight::DragonKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI)
{
    this->id = id;
    this->hp = maxhp;
    this->maxhp = maxhp;
    this->level = level;
    this->gil = gil;
    this->antidote = antidote;
    this->phoenixdownI = phoenixdownI;
    this->knightType = DRAGON;
    this->bag = new DragonBag(this, phoenixdownI, antidote);
}
/* * * END implementation of class DragonKnight * * */

/* * * BEGIN implementation of class NormalKnight * * */
NormalKnight::NormalKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI)
{
    this->id = id;
    this->hp = maxhp;
    this->maxhp = maxhp;
    this->level = level;
    this->gil = gil;
    this->antidote = antidote;
    this->phoenixdownI = phoenixdownI;
    this->knightType = NORMAL;
    this->bag = new NormalBag(this, phoenixdownI, antidote);
}
/* * * END implementation of class NormalKnight * * */

/* * * BEGIN implementation of class ArmyKnights * * */
ArmyKnights::ArmyKnights(const string &file_armyknights)
{
    ifstream fileIn;
    fileIn.open(file_armyknights);
    fileIn >> amount_knights;
    index_event = 0; // Bắt đầu tính từ 0
    isOmega = false;
    isHades = false;
    isPaladinShield = false;
    isLancelotSpear = false;
    isGuinevereHair = false;
    isExcaliburSword = false;
    arr_knights = new BaseKnight *[amount_knights];
    int maxhp, level, gil, antidote, phoenixdownI;
    for (int i = 0; i < amount_knights; i++)
    {
        fileIn >> maxhp;
        fileIn >> level;
        fileIn >> phoenixdownI;
        fileIn >> gil;
        fileIn >> antidote;
        arr_knights[i] = BaseKnight::create(i + 1, maxhp, level, gil, antidote, phoenixdownI);
    }
    last_knight = arr_knights[amount_knights - 1];
    fileIn.close();
}

ArmyKnights::~ArmyKnights()
{
    for (int i = 0; i < amount_knights; i++)
    {
        delete[] arr_knights[i];
        arr_knights[i] = nullptr;
    }
    delete[] arr_knights;
    arr_knights = nullptr;
    amount_knights = 0;
}

bool ArmyKnights::fight(BaseOpponent *opponent)
{
    // Ham nay tra ve true neu sau khi chien dau voi 1 opponent
    // ma doi quan van con song sot (hiep si co the hy sinh, nhung doi quan van con)
    if (!opponent->fight_opponent(this, last_knight, index_event))
    {
        --amount_knights;
        if (amount_knights <= 0)
        {
            amount_knights = 0;
            return false;
        }
        last_knight = arr_knights[amount_knights - 1];
    }
    return true;
}
bool ArmyKnights::adventure(Events *events)
{
    bool flag = true;
    for (int i = 0; i < events->amount_events; i++)
    {
        if (events->get(i) == 1)
        {
            Opponent_1_5 opponent_1_5(1, 10, 100);
            flag = this->fight(&opponent_1_5);
        }
        else if (events->get(i) == 2)
        {
            Opponent_1_5 opponent_1_5(2, 15, 150);
            flag = this->fight(&opponent_1_5);
        }
        else if (events->get(i) == 3)
        {
            Opponent_1_5 opponent_1_5(3, 45, 450);
            flag = this->fight(&opponent_1_5);
        }
        else if (events->get(i) == 4)
        {
            Opponent_1_5 opponent_1_5(4, 75, 750);
            flag = this->fight(&opponent_1_5);
        }
        else if (events->get(i) == 5)
        {
            Opponent_1_5 opponent_1_5(5, 95, 800);
            flag = this->fight(&opponent_1_5);
        }
        else if (events->get(i) == 6)
        {
            Tornbery tornbery;
            flag = this->fight(&tornbery);
        }
        else if (events->get(i) == 7)
        {
            QueenOfCards queenOfCards;
            flag = this->fight(&queenOfCards);
        }
        else if (events->get(i) == 8)
        {
            NinaDeRings ninaDeRings;
            flag = this->fight(&ninaDeRings);
        }
        else if (events->get(i) == 9)
        {
            DurianGarden durianGarden;
            flag = this->fight(&durianGarden);
        }
        else if (events->get(i) == 10 && !this->isOmega)
        {
            OmegaWeapon omegaWeapon;
            flag = this->fight(&omegaWeapon);
        }
        else if (events->get(i) == 11 && !this->isHades)
        {
            Hades hades;
            flag = this->fight(&hades);
        }
        else if (events->get(i) == 99)
        {
            if (this->isExcaliburSword)
            {
                flag = true;
            }
            // neu co 3 bao vat
            else if (this->isPaladinShield && this->isGuinevereHair && this->isLancelotSpear)
            {
                Ultimecia ultimecia;
                flag = this->fight(&ultimecia);
            }
            // thua cuoc
            else
            {
                flag = false;
                amount_knights = 0;
            }
        }
        else if (events->get(i) == 112)
        {
            PhoenixDownII *phoenixDownII = new PhoenixDownII();
            ResidualItem(this, this->last_knight, phoenixDownII);
        }
        else if (events->get(i) == 113)
        {
            PhoenixDownIII *phoenixDownIII = new PhoenixDownIII();
            ResidualItem(this, this->last_knight, phoenixDownIII);
        }
        else if (events->get(i) == 114)
        {
            PhoenixDownIV *phoenixDownIV = new PhoenixDownIV();
            ResidualItem(this, this->last_knight, phoenixDownIV);
        }
        else if (events->get(i) == 95)
        {
            this->isPaladinShield = true;
        }
        else if (events->get(i) == 96)
        {
            this->isLancelotSpear = true;
        }
        else if (events->get(i) == 97)
        {
            this->isGuinevereHair = true;
        }
        else if (events->get(i) == 98)
        {
            if (this->isPaladinShield && this->isLancelotSpear && this->isGuinevereHair)
            {
                this->isExcaliburSword = true;
            }
        }
        ++index_event;
        this->printInfo();
        if (!flag)
        {
            break;
        }
    }
    return amount_knights;
}

int ArmyKnights::count() const
{
    return this->amount_knights;
}

BaseKnight *ArmyKnights::lastKnight() const
{
    if (amount_knights)
        return last_knight;
    return nullptr;
}
bool ArmyKnights::hasPaladinShield() const
{
    return isPaladinShield;
}
bool ArmyKnights::hasLancelotSpear() const
{
    return isLancelotSpear;
}
bool ArmyKnights::hasGuinevereHair() const
{
    return isGuinevereHair;
}
bool ArmyKnights::hasExcaliburSword() const
{
    return isExcaliburSword;
}

void ArmyKnights::printInfo() const
{
    cout << "No. knights: " << this->count();
    if (this->count() > 0)
    {
        BaseKnight *lknight = lastKnight(); // last knight
        cout << ";" << lknight->toString();
    }
    cout << ";PaladinShield:" << this->hasPaladinShield()
         << ";LancelotSpear:" << this->hasLancelotSpear()
         << ";GuinevereHair:" << this->hasGuinevereHair()
         << ";ExcaliburSword:" << this->hasExcaliburSword()
         << endl
         << string(50, '-') << endl;
}

void ArmyKnights::printResult(bool win) const
{
    cout << (win ? "WIN" : "LOSE") << endl;
}

/* * * END implementation of class ArmyKnights * * */

/* * * BEGIN implementation of class BaseItem * * */
BaseItem::~BaseItem()
{
    next = nullptr;
}
/* * * END implementation of class BaseItem * * */

/* * * BEGIN implementation of class Antidote * * */
Antidote::Antidote()
{
    isPoison = false;
    itemType = ANTIDOTE;
}
bool Antidote::canUse(BaseKnight *knight)
{
    return true;
}

void Antidote::use(BaseKnight *knight)
{
    //    khong lam gi ca
}
/* * * END implementation of class Antidote * * */

/* * * BEGIN implementation of class PhoenixDownI * * */
PhoenixDownI::PhoenixDownI()
{
    itemType = PHOENIXDOWNI;
}

bool PhoenixDownI::canUse(BaseKnight *knight)
{
    return knight->hp <= 0;
}

void PhoenixDownI::use(BaseKnight *knight)
{
    knight->hp = knight->maxhp;
}

/* * * END implementation of class PhoenixDownI * * */

/* * * BEGIN implementation of class PhoenixDownII * * */
PhoenixDownII::PhoenixDownII()
{
    itemType = PHOENIXDOWNII;
}

bool PhoenixDownII::canUse(BaseKnight *knight)
{
    return knight->hp < knight->maxhp / 4;
}

void PhoenixDownII::use(BaseKnight *knight)
{
    knight->hp = knight->maxhp;
}
/* * * END implementation of class PhoenixDownII * * */

/* * * BEGIN implementation of class PhoenixDownIII * * */
PhoenixDownIII::PhoenixDownIII()
{
    itemType = PHOENIXDOWNIII;
}

bool PhoenixDownIII::canUse(BaseKnight *knight)
{
    return knight->hp < knight->maxhp / 3;
}

void PhoenixDownIII::use(BaseKnight *knight)
{
    if (knight->hp <= 0)
    {
        knight->hp = knight->maxhp / 3;
    }
    else
    {
        knight->hp += knight->maxhp / 4;
    }
}
/* * * END implementation of class PhoenixDownIII * * */

/* * * BEGIN implementation of class PhoenixDownIII * * */
PhoenixDownIV::PhoenixDownIV()
{
    itemType = PHOENIXDOWNIV;
}

bool PhoenixDownIV::canUse(BaseKnight *knight)
{
    return knight->hp < knight->maxhp / 2;
}

void PhoenixDownIV::use(BaseKnight *knight)
{
    if (knight->hp <= 0)
    {
        knight->hp = knight->maxhp / 2;
    }
    else
    {
        knight->hp += knight->maxhp / 5;
    }
}
/* * * END implementation of class PhoenixDownIV * * */

/* * * BEGIN implementation of class KnightAdventure * * */
KnightAdventure::KnightAdventure()
{
    armyKnights = nullptr;
    events = nullptr;
}

KnightAdventure::~KnightAdventure()
{
}

void KnightAdventure::loadArmyKnights(const string &file_armyknights)
{
    armyKnights = new ArmyKnights(file_armyknights);
}

void KnightAdventure::loadEvents(const string &file_events)
{
    events = new Events(file_events);
}

void KnightAdventure::run()
{
    armyKnights->adventure(this->events);
    armyKnights->printResult(armyKnights->amount_knights > 0);
}

/* * * END implementation of class KnightAdventure * * */

/* * * BEGIN implementation of class Events * * */
Events::Events(const string &file_events)
{
    ifstream fileIn;
    fileIn.open(file_events);
    fileIn >> amount_events;
    arr_events = new int[amount_events];
    for (int i = 0; i < amount_events; i++)
    {
        fileIn >> arr_events[i];
    }
    fileIn.close();
}

Events::~Events()
{
    delete[] arr_events;
    arr_events = nullptr;
    amount_events = 0;
}

int Events::count() const
{
    return amount_events;
}

int Events::get(int i) const
{
    return arr_events[i];
}

/* * * END implementation of class Events * * */

// *********** Begin Function *************************

bool isPrime(int n)
{
    if (n < 2)
        return false;
    for (int i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
            return false;
    }
    return true;
}

bool isPytago(int n)
{
    int n_1 = n % 10;
    n /= 10;
    int n_2 = n % 10;
    n /= 10;
    if (n_1 == 0 || n_2 == 0 || n == 0)
        return false;
    if ((n_1 * n_1 + n_2 * n_2 == n * n) || (n * n + n_2 * n_2 == n_1 * n_1) || (n_1 * n_1 + n * n == n_2 * n_2))
        return true;
    return false;
}

bool Recuperate(BaseKnight *knight)
{
    BaseItem *tmpBaseItem = knight->bag->get(PHOENIXDOWNALL);
    if (tmpBaseItem)
    {
        tmpBaseItem->use(knight);
        delete tmpBaseItem;
        return true;
    }
    else if (knight->gil >= 100 && knight->hp <= 0)
    {
        knight->gil -= 100;
        knight->hp = knight->maxhp / 2;
        return true;
    }
    return false;
}

void ResidualGil(ArmyKnights *army, BaseKnight *knight)
{
    int residualGil = knight->gil - 999;
    int idx = army->amount_knights - 1;
    while (knight->gil >= 999)
    {
        knight->gil = 999;
        --idx;
        if (idx < 0)
            break;
        knight = army->arr_knights[idx];
        knight->gil += residualGil;
        if (knight->gil > 999)
        {
            residualGil = knight->gil - 999;
            knight->gil = 999;
        }
    }
}

void ResidualItem(ArmyKnights *army, BaseKnight *knight, BaseItem *baseBag)
{
    int idx = army->amount_knights - 1;
    while (!knight->bag->insertFirst(baseBag))
    {
        knight->bag->insertFirst(baseBag);
        --idx;
        if (idx < 0)
            break;
        knight = army->arr_knights[idx];
    }
}

// *********** End Function *************************