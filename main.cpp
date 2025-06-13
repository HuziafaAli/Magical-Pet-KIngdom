
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <iostream>
#include <fstream>
#include <cmath>
#include <ctime>
#include <cstdlib>

using namespace sf;
using namespace std;

#define TANK 0
#define HEALER 1
#define DAMAGE_DEALER 2

// Power-up types
#define SPEED_BOOST 0
#define RAPID_FIRE  1
#define EMPTY       2


class Pet {
protected:
    int health, maxHealth;
    int speed, maxSpeed;
    int attack, maxAttack;
    int mana, maxMana;
    int defense, maxDefense;
    int level;
    int trainingPoints;
    int shieldRoundsRemaining;

public:
    Pet() {}

    Pet(int h, int s, int a, int d, int m)
        : health(h), maxHealth(h),
            speed(s), maxSpeed(s),
            attack(a), maxAttack(a),
            defense(d), maxDefense(d),
            mana(m), maxMana(m),
            level(1), trainingPoints(0) {}

    virtual ~Pet() {} 

    virtual void useAbility1() = 0;
    virtual void useAbility2() = 0;
    virtual string getName() = 0;

    //To Restore Health after returning from the battle.
    void RestoreHealth() {
        health = maxHealth;
    }

    void RestoreMana() {
        mana = maxMana;
    }

    //BOT DAMAGE DEAL
    void DamageDealt(int amount) {
        health -= amount;
    }

    //CHECK IF HEALTH IS FULL OR NOT
    bool checkHealth() {
        if(health == maxHealth)  return false;
        else return true;
    }

    bool checkMana() {
        if(mana == maxMana)  return false;
        else return true;
    }

    //INCREASE HEALTH ON USING ITEMS ETC
    void increaseHealth(int amount) {
        if (health < maxHealth) {
            health += amount;
            if (health > maxHealth) health = maxHealth;
            cout << "Health increased by " << amount << ".\n";
        } else {
            cout << "Health is already full.\n";
        }
    }

    void increaseMana(int amount) {
        if (mana < maxMana) {
            mana += amount;
            if (mana > maxMana) mana = maxMana;
            cout << "Health increased by " << amount << ".\n";
        } else {
            cout << "Health is already full.\n";
        }
    }

    void increaseSpeed(int amount) {
        if (speed < maxSpeed) {
            speed += amount;
            if (speed > maxSpeed) speed = maxSpeed;
            cout << "Speed increased by " << amount << ".\n";
        } else {
            cout << "Speed is already full.\n";
        }
    }

    void increaseAttack(int amount) {
        if (attack < maxAttack) {
            attack += amount;
            if (attack > maxAttack) attack = maxAttack;
            cout << "Attack increased by " << amount << ".\n";
        } else {
            cout << "Attack is already full.\n";
        }
    }

    void refillMana(int amount) {
        if (mana < maxMana) {
            mana += amount;
            if (mana > maxMana) mana = maxMana;
            cout << "Mana increased by " << amount << ".\n";
        } else {
            cout << "Mana is already full.\n";
        }
    }

    void increaseDefense(int amount) {
        if (defense < maxDefense) {
            defense += amount;
            if (defense > maxDefense) defense = maxDefense;
            cout << "Defense increased by " << amount << ".\n";
        } else {
            cout << "Defense is already full.\n";
        }
    }
    //SHEILD APPLICABLE
    void applyShield(int duration) {
        shieldRoundsRemaining = duration;
    }

    void onRoundEnd() {
        if (shieldRoundsRemaining > 0) {
            shieldRoundsRemaining--;
        }
    }

    bool isShieldActive() const {
        return shieldRoundsRemaining > 0;
    }

    //EVOLUTION OF THE PET
    void levelUp(int points) {
        if (level >= 5) {
            cout << "Maximum level reached.\n";
            return;
        }

        trainingPoints += points;

        if (trainingPoints >= 10 && level == 1) {
            level++;
            LevelboostStats(10);
        } else if (trainingPoints >= 30 && level == 2) {
            level++;
            LevelboostStats(20);
        } else if (trainingPoints >= 50 && level == 3) {
            level++;
            LevelboostStats(30);
        } else if (trainingPoints >= 70 && level == 4) {
            level++;
            LevelboostStats(40);
        } else if (trainingPoints >= 90 && level == 5) {
            level++;
            LevelboostStats(50);
            return;
        }

        cout << "Level Up! Pet is now level " << level
                << " and gained " << points << " training points.\n";
    }
    
    //BOOSTING THE STATS
    void boostMaxStats(int amount) {
        maxHealth += amount;
        maxSpeed += amount;
        maxAttack += amount;
        maxDefense += amount;
        maxMana += amount;

        levelUp(amount);
        setHealth(maxHealth);
        setAttack(maxAttack);
        setMana(maxMana);
        setDefense(maxDefense);
        setSpeed(maxSpeed);

        cout << "Max stats increased by " << amount << "!\n";
    }

    void LevelboostStats(int amount) {
        maxHealth += amount;
        maxSpeed += amount;
        maxAttack += amount;
        maxDefense += amount;
        maxMana += amount;
    }

    void displayStats() {
        cout << "\nPet Stats:"
                << "\nName: " << getName()
                << "\nLevel: " << level
                << "\nHealth: " << health << "/" << maxHealth
                << "\nSpeed: " << speed << "/" << maxSpeed
                << "\nAttack: " << attack << "/" << maxAttack
                << "\nMana: " << mana << "/" << maxMana
                << "\nDefense: " << defense << "/" << maxDefense
                << "\n";
    }

    // Health
    int getHealth() const { return health; }
    void setHealth(int h) { health = h; }

    int getMaxHealth() const { return maxHealth; }
    void setMaxHealth(int mh) { maxHealth = mh; }

    // Speed
    int getSpeed() const { return speed; }
    void setSpeed(int s) { speed = s; }

    int getMaxSpeed() const { return maxSpeed; }
    void setMaxSpeed(int ms) { maxSpeed = ms; }

    // Attack
    int getAttack() const { return attack; }
    void setAttack(int a) { attack = a; }

    int getMaxAttack() const { return maxAttack; }
    void setMaxAttack(int ma) { maxAttack = ma; }

    // Mana
    int getMana() const { return mana; }
    void setMana(int m) { mana = m; }

    int getMaxMana() const { return maxMana; }
    void setMaxMana(int mm) { maxMana = mm; }

    // Defense
    int getDefense() const { return defense; }
    void setDefense(int d) { defense = d; }

    int getMaxDefense() const { return maxDefense; }
    void setMaxDefense(int md) { maxDefense = md; }

    // Level
    int getLevel() const { return level; }
    void setLevel(int l) { level = l; }

    // Training Points
    int getTrainingPoints() const { return trainingPoints; }
    void setTrainingPoints(int tp) { trainingPoints = tp; }

    // Shield Rounds Remaining
    int getShieldRoundsRemaining() const { return shieldRoundsRemaining; }
    void setShieldRoundsRemaining(int sr) { shieldRoundsRemaining = sr; }

};
    
// ---------------- Derived Classes ----------------

class Dragon : public Pet {
public:
    Dragon() : Pet(100, 60, 100, 40, 40) {}

    string getName() override {
        return "Dragon";
    }

    void useAbility1() override {
        if (mana >= 20) {
            mana -= 20;
            cout << "Fireball Attack! Massive fire damage dealt.\n";
        } else {
            cout << "Not enough mana for Fireball Attack!\n";
        }
    }

    void useAbility2() override {
        if (mana >= 30) {
            mana -= 30;
            cout << "Dragon's Roar! Nearby enemies are stunned.\n";
        } else {
            cout << "Not enough mana for Dragon's Roar!\n";
        }
    }
};
    

class Phoenix : public Pet {
    bool rebirthUsed = false;

public:
    Phoenix() : Pet(60, 40, 40, 100, 100) {}

    string getName() override {
        return "Phoenix";
    }

    void useAbility1() override {
        if (mana >= 20) {
            mana -= 20;
            cout << "Flame Healing! Gradually heals itself or an ally.\n";
        } else {
            cout << "Not enough mana for Flame Healing!\n";
        }
    }

    void useAbility2() override {
        if (!rebirthUsed) {
            if (mana >= 50) {
                mana -= 50;
                cout << "Rebirth activated! The Phoenix rises again.\n";
                rebirthUsed = true;
            } else {
                cout << "Not enough mana for Rebirth!\n";
            }
        } else {
            cout << "Rebirth already used this match.\n";
        }
    }
};


class Unicorn : public Pet { //[Unicorn] - SPEED-BASED UTILITY
public:
    Unicorn() : Pet(40, 100, 60, 60, 60) {}

    string getName() override {
        return "Unicorn";
    }

    void useAbility1() override {
        if (mana >= 20) {
            mana -= 20;
            cout << "Speed Burst! Speed temporarily increased.\n";
        } else {
            cout << "Not enough mana for Speed Burst!\n";
        }
    }

    void useAbility2() override {
        if (mana >= 30) {
            mana -= 30;
            cout << "Magic Shield! Incoming damage absorbed for a while.\n";
        } else {
            cout << "Not enough mana for Magic Shield!\n";
        }
    }
};
        
class Griffin : public Pet { //[Griffin] - BALANCED FIGHTER
    public:
    Griffin() : Pet(60, 60, 60, 60, 100) {} 

    string getName() override {
        return "Griffin";
    }

    void useAbility1() override {
        if (mana >= 20) {
            mana -= 20;
            cout << "Claw Strike! Deals strong melee damage.\n";
        } else {
            cout << "Not enough mana for Claw Strike!\n";
        }
    }

    void useAbility2() override {
        if (mana >= 30) {
            mana -= 30;
            cout << "Dive Bomb! Enemy stunned by aerial assault.\n";
        } else {
            cout << "Not enough mana for Dive Bomb!\n";
        }
    }
};

// ---------------- Guilds ----------------

class GuildMember {
private:
    int role;  // Role of the member (TANK, HEALER, DAMAGE_DEALER)

public:
    
    GuildMember(){
        role = 0;
    }

    GuildMember(int r) : role(r) {}  

    int getRole() {
        return role;
    }
    //displaying of the role of the pet
    void displayRole() {
        switch (role) {
            case TANK: cout << "Tank"; break;
            case HEALER: cout << "Healer"; break;
            case DAMAGE_DEALER: cout << "Damage Dealer"; break;
            default: cout << "Unassigned"; break;
        }
    }
};


class Guild {
private:
    string name;
    Pet* pets[4];              
    GuildMember* members;      
    int memberCount;

public:
    Guild(string guildName) : name(guildName), memberCount(0) {
        for (int i = 0; i < 4; i++) {
            pets[i] = nullptr;
        }
        members = new GuildMember[4];
    }

    ~Guild() {
        for (int i = 0; i < 4; i++) {  
            if (pets[i] != nullptr) {  
                delete pets[i];
                pets[i] = nullptr;     
            }
        }
        delete[] members;
        members = nullptr;       
    }

    string getName() {        
        if(name == ""){
            return "Unknown Guild";
        }
        return name;
    }
    
    void addPet(Pet* pet, int role) {
        if (memberCount >= 4) {
            cout << "Guild is full. Cannot add more pets.\n";
            return;
        }

        pets[memberCount] = pet;
        members[memberCount] = GuildMember(role);  // Assigning the role to the member
        memberCount++;

        cout << pet->getName() << " has been added to the guild with role: ";
        members[memberCount - 1].displayRole();  // Display role for the newly added pet
        cout << "\n";
    }

    //Loading the pet of a specific player to ensure the pet is in the guild
    void setPet(string n, int tp, int l , int mh , int ma, int md, int mm , int ms , int index) {
        if(index == 0) {

            pets[index] = new Dragon();
            pets[index]->setTrainingPoints(tp);
            pets[index]->setLevel(l);
            pets[index]->setMaxHealth(mh);
            pets[index]->setMaxAttack(ma);
            pets[index]->setMaxDefense(md);
            pets[index]->setMaxMana(mm);
            pets[index]->setMaxSpeed(ms);
            members[index] = GuildMember(index);
            
            
        } else if(index == 1) {

            pets[index] = new Phoenix();
            pets[index]->setTrainingPoints(tp);
            pets[index]->setLevel(l);
            pets[index]->setMaxHealth(mh);
            pets[index]->setMaxAttack(ma);
            pets[index]->setMaxDefense(md);
            pets[index]->setMaxMana(mm);
            pets[index]->setMaxSpeed(ms);
            members[index] = GuildMember(index);

        } else if(index == 2) {
            
            pets[index] = new Unicorn();
            pets[index]->setTrainingPoints(tp);
            pets[index]->setLevel(l);
            pets[index]->setMaxHealth(mh);
            pets[index]->setMaxAttack(ma);
            pets[index]->setMaxDefense(md);
            pets[index]->setMaxMana(mm);
            pets[index]->setMaxSpeed(ms);
            members[index] = GuildMember(index);
        
        } else if (index == 3) {
            
            pets[index] = new Griffin();
            pets[index]->setTrainingPoints(tp);
            pets[index]->setLevel(l);
            pets[index]->setMaxHealth(mh);
            pets[index]->setMaxAttack(ma);
            pets[index]->setMaxDefense(md);
            pets[index]->setMaxMana(mm);
            pets[index]->setMaxSpeed(ms);
            members[index] = GuildMember(index - 1);
            
        }

        memberCount = 4;
    }

    Pet* getPet (int index) {
        return pets[index];
    }

};

//work as an inventory Class fot the player
class Item {
    protected:
        string name;
        int cost;
        int type;
        int bar;
        int count;
    
    public:
        Item(string name) : name(name) {
            count = 0;
            cost = 150;
        }
        virtual ~Item() {}
        
        int getType() {
            return type;
        }

        int getbar() {
            return bar;
        }

        int getCount() const {
            return count;
        }
        
        void setCount(int newCount) {
            count = newCount;
        }
        
        void incrementCount() { 
            count++;
        }

        string getName() const { return name; }
        int getCost() const { return cost; }
    
        virtual void use(Pet* pet) = 0;

};
    

//items are inherited from the item class
class HealingPotion : public Item {
private:
    int healingAmount;


public:
    HealingPotion(int HealingAmount, int t) : Item("Healing Potion"), healingAmount(HealingAmount) {
        type = t;
        bar = healingAmount;

    }

    void use(Pet* pet) override {
        pet->increaseHealth(healingAmount);
        cout << "Healed " << healingAmount << " HP.\n";
    }



};

class ManaPotion : public Item {
private:
    int manaAmount; 
    
public:
    ManaPotion(int manaAmount ,  int t) : Item("Mana Potion"), manaAmount(manaAmount) {
        type = t;
        bar = manaAmount;

    }

    void use(Pet* pet) override {
        pet->refillMana(manaAmount);
        cout << "Used Mana Potion! Mana increased by " << manaAmount << endl;
    }

    
};
    
class BuffItem : public Item {
private:
    int boostAmount;  
    
public:
    BuffItem(int boostAmount , int t) : Item("Buff Item"), boostAmount(boostAmount) {
        type = t;
        bar = boostAmount;

    }

    void use(Pet* pet) override {
        pet->increaseSpeed(boostAmount);
        cout << "Used Buff Item! Speed increased by " << boostAmount << endl;

    }
    
};
    
class Shield : public Item {
private:
    int shieldDuration;  

public:
    Shield(int shieldDuration ,  int t) : Item("Shield"), shieldDuration(shieldDuration) {
        type = t;
        bar = shieldDuration;

    }

    void use(Pet* pet) override {
        pet->applyShield(shieldDuration);
        cout << "Used Shield! Shield applied for " << shieldDuration << " rounds." << endl;
    }


};

    
class Shop {
private:
    Item* items[4];  // Example limit of 4 items in the shop
    
public:
    Shop() {
        items[0] = new HealingPotion(50,0);  // Heal 100 HP
        items[1] = new ManaPotion(30,1);      // Refill 50 mana
        items[2] = new BuffItem(40,2);  // Boost Speed by 20
        items[3] = new Shield(3,3);  // Shield for 7 secounds
    }
    
    void showItems() {
        cout << "Items available in the shop:\n";
        for (int i = 0; i < 4; i++) {
            cout << i + 1 << ". " << items[i]->getName() << " - Cost: " << items[i]->getCost() << " coins\n";
        }
    }

    // In Shop class
    Item* buyItem(int index) {
        switch (index) {
            case 0: return new HealingPotion(50 , 0);
            case 1: return new ManaPotion(40, 1);
            case 2: return new BuffItem(60, 2);
            case 3: return new Shield(3, 3);
            default: return nullptr;
        }
    }

    
};

class BattleMode {
protected:
    int maxPoints;
public:
    virtual void startBattle() = 0;
    virtual ~BattleMode() {}
};
    
    
class Battle1v1 : public BattleMode {
protected:
    Pet* pet1;
    Pet* pet2;
    int pet1Points;
    int pet2Points;
    bool turn;

public:
    Battle1v1(Pet* p1, Pet* p2);
    void startBattle() override;
};

    
class Battle2v2 : public BattleMode {
protected:
    Pet* team1[2];
    Pet* team2[2];
    int team1Points;
    int team2Points;
    bool team1Turn;

public:
    Battle2v2(Pet* t1[2], Pet* t2[2]);
    void startBattle() override;
};
   
    
class GuildWar : public BattleMode {
protected:
    Pet* guild1[4];
    Pet* guild2[4];
    int guild1Points;
    int guild2Points;
    int activeIndex1, activeIndex2;
    bool guild1Turn;

public:
    GuildWar(Pet* g1[4], Pet* g2[4]);
    void startBattle() override;
};

class Player {
    private:
        string username;
        string password;
        int currency;
        Item** inventory;      
        int inventorySize;      
        int inventoryCapacity;  
        Shop shop;
        Guild* guild;
    
    public:

        Player() : username("") , password("") , currency(500) , inventorySize(0), inventoryCapacity(10){
            inventory = new Item*[inventoryCapacity];
            guild = nullptr;
        }

        ~Player() {

            guild = nullptr;  

            for (int i = 0; i < inventorySize; ++i) {
                delete inventory[i];  
            }
            delete[] inventory;
        }

        Player(string u, string p) : username(u), password(p), currency(500), inventorySize(0), inventoryCapacity(10), guild(nullptr) {
            inventory = new Item*[inventoryCapacity];
        }
        
        //Getting count of the Health item
        int getHcount(){
            int count = 0;
            Item * hitem = new HealingPotion(50, 0);
            count = hitem->getCount();
            return count;
        }

        int getCurrency(){
            return currency;
        }

        void setCurrency(int c){
            currency = c;
        }

        void setUsername(string u) {
            username = u;
        }

        void setpassword(string p) {
            password = p;
        }

        void addCurrency(int amount) { currency += amount; }
    
        bool deductCurrency(int amount) {

            if (currency >= amount) {
                currency -= amount;
                return true;
            }
            return false;
        }

        //resizing the inventory 
        void resizeInventory() {
            int newCapacity = inventoryCapacity * 5;
            Item** newInventory = new Item*[newCapacity];
        
            for (int i = 0; i < inventorySize; ++i) {
                newInventory[i] = inventory[i];
            }
        
            delete[] inventory;
            inventory = newInventory;
            inventoryCapacity = newCapacity;
        
            cout << "Inventory resized to capacity: " << inventoryCapacity << "\n";
        }
        
        Item* getInventoryItem(int index) {
            if (index >= 0 && index < inventorySize) {
                return inventory[index];
            }
            return nullptr; // Returning null if index is out of bounds
        }

        Item** getInventory() {
            return inventory;
        }
        
        void addItem(Item* newItem) {
            for (int i = 0; i < inventorySize; i++) {
                Item* existingItem = inventory[i];
                if (existingItem != nullptr && 
                    existingItem->getName() == newItem->getName() && 
                    existingItem->getType() == newItem->getType() && 
                    existingItem->getbar() == newItem->getbar()) {
                    
                    // Same item found, just increment count and delete the new one
                    existingItem->incrementCount();
                    delete newItem;
                    return;
                }
            }
            
            // No matching item found, add as new item with count of 1
            newItem->setCount(1);
            
            if (inventorySize >= inventoryCapacity) {
                resizeInventory();
            }
            
            if (inventorySize < inventoryCapacity) {
                inventory[inventorySize++] = newItem;
            } else {
                cout << "Inventory full!" << endl;
                delete newItem;
            }
            
            
        }

        // Using this only when loading items from a save file
        void addItemWithCount(Item* newItem) {
            
            if (inventorySize >= inventoryCapacity) {
                resizeInventory();
            }
            
            if (inventorySize < inventoryCapacity) {
                inventory[inventorySize++] = newItem;
            } else {
                cout << "Inventory full!" << endl;
                delete newItem;
            }
        }

        // Add this method to your Player class
        void clearInventory() {
            // Delete all items in the inventory to prevent memory leaks
            for (int i = 0; i < inventorySize; i++) {
                if (inventory[i] != nullptr) {
                    delete inventory[i];
                    inventory[i] = nullptr;
                }
            }
            
            // Reset inventory size to 0
            inventorySize = 0;
        }

        void setInventorySize(int is) {
            inventorySize = is;
        }

        void setInventoryCapacity(int ic) {
            inventoryCapacity = ic;
        }

        int getInventorySize() {
            return inventorySize;
        }
        
        int getInventoryCapacity() {
            return inventoryCapacity;
        }

        Shop& getShop() {
            return shop; }

        Guild* getGuild() {
                return guild;
          
        }

        string getguilname() {
            string name = guild->getName();
            return name;
        }


        void setGuild(string gn) {
            // Clean up existing guild if any
            if (guild != nullptr) {
                delete guild;
                guild = nullptr;
            }
            guild = new Guild(gn);
        }
        
        void addPetToGuild() {
            if (!guild) {
                cout << "No guild exists for this player!" << endl;
                return;
            }

            // Automatically create and assign pets with fixed roles
            Pet* dragon = new Dragon();       // Role: TANK
            Pet* phoenix = new Phoenix();     // Role: HEALER
            Pet* unicorn = new Unicorn();     // Role: DAMAGE_DEALER
            Pet* griffin = new Griffin();     // Role: DAMAGE_DEALER
        
            guild->addPet(dragon, TANK);
            guild->addPet(phoenix, HEALER);
            guild->addPet(unicorn, DAMAGE_DEALER);
            guild->addPet(griffin, DAMAGE_DEALER);
        }
    
        string getUsername() const { return username; }

    };
 
class GameManager {
    private:
        Player* player;  
    public:
    
    GameManager() {
        player = new Player();
    }

    ~GameManager() { 
        if (player != nullptr) {
            delete player;
            player = nullptr;
        }
    }
    
    void registerPlayer(const string& username, const string& password, const string& guildName) {

        if (player != nullptr) {
            delete player;
            player = nullptr;
        }
        
         player = new Player(username, password);
        
        // Set up the player's guild and add pets
        player->setGuild(guildName);
        player->addPetToGuild();
        player->setInventorySize(0);
        player->setInventoryCapacity(10);

    }

    bool resumePlayer(const string& username, const string& password) {

        ifstream inFile("players.txt");
        if (!inFile.is_open()) {
            cout << "Failed to open player data file!" << endl;
            return false;
        }
        
        // Create a temporary file to store other players' data
        ofstream tempFile("temp.txt");
        if (!tempFile.is_open()) {
            cout << "Failed to create temporary file!" << endl;
            inFile.close();
            return false;
        }
        
        bool foundUser = false;
        string currentUsername, currentPassword, currentGuildName;
        
        while (getline(inFile, currentUsername)) {
            
            getline(inFile, currentPassword);
            getline(inFile, currentGuildName);
            
            string currencyStr;
            getline(inFile, currencyStr);
            int currency = stoi(currencyStr);
            
            string inventorySizeStr;
            getline(inFile, inventorySizeStr);
            int inventorySize = stoi(inventorySizeStr);
            
            string inventoryCapacityStr;
            getline(inFile, inventoryCapacityStr);
            int inventoryCapacity = stoi(inventoryCapacityStr);
            
            if (currentUsername == username && currentPassword == password) {
                foundUser = true;
                
                // Load the player data
                player->setUsername(currentUsername);
                player->setpassword(currentPassword);
                player->setCurrency(currency);
                player->setInventoryCapacity(inventoryCapacity);
                player->clearInventory(); // Clear current inventory before loading
                player->setGuild(currentGuildName);
                
                Guild* playerGuild = player->getGuild();
                
                // Read and load inventory items
                for (int i = 0; i < inventorySize; i++) {
                    string itemName;
                    getline(inFile, itemName);
                    
                    if (itemName != "empty") {
                        string barStr, typeStr, Count;
                        getline(inFile, barStr);
                        int bar = stoi(barStr);
                        
                        getline(inFile, typeStr);
                        int type = stoi(typeStr);
    
                        getline(inFile, Count);
                        int count = stoi(Count);
                        
                        // Create the appropriate item based on type
                        Item* newItem = nullptr;
                        
                        switch(type) {
                            case 0:
                                newItem = new HealingPotion(bar, type);
                                break;
                            case 1:
                                newItem = new ManaPotion(bar, type);
                                break;
                            case 2:
                                newItem = new BuffItem(bar, type);
                                break;
                            case 3:
                                newItem = new Shield(bar, type);
                                break;
                            // Add more item types as needed
                        }
                        
                        if (newItem != nullptr) {
                            newItem->setCount(count);
                            player->addItemWithCount(newItem);
                        }
                    }
                }
    
                // Load pets
                for (int i = 0; i < 4; i++) {
                    string petName;
                    getline(inFile, petName);
                    
                    if (petName == "empty") {
                        continue; 
                    } else {
                        int trainingPoints, level, maxHealth, maxAttack, maxDefense, maxMana, maxSpeed;
                        
                        inFile >> trainingPoints >> level >> maxHealth >> maxAttack >> maxDefense >> maxMana >> maxSpeed;
                        inFile.ignore(); 
                        
                        if (playerGuild != nullptr) {
                            playerGuild->setPet(petName, trainingPoints, level, maxHealth, maxAttack, maxDefense, maxMana, maxSpeed, i);
                        }
                    }
                }
                
                cout << "Player data loaded successfully!" << endl;
                cout << "Welcome back to guild: " << currentGuildName << endl;
            } else {
                //  write this data to the temp file
                tempFile << currentUsername << endl;
                tempFile << currentPassword << endl;
                tempFile << currentGuildName << endl;
                tempFile << currency << endl;
                tempFile << inventorySize << endl;
                tempFile << inventoryCapacity << endl;
                
                // Copy inventory items to temp file
                for (int i = 0; i < inventorySize; i++) {
                    string itemName;
                    getline(inFile, itemName);
                    tempFile << itemName << endl;
                    
                    if (itemName != "empty") {
                        string barStr, typeStr, Count;
                        getline(inFile, barStr);
                        tempFile << barStr << endl;
                        
                        getline(inFile, typeStr);
                        tempFile << typeStr << endl;
    
                        getline(inFile, Count);
                        tempFile << Count << endl;
                    }
                }
                
                // Copy pets data to temp file
                for (int i = 0; i < 4; i++) {
                    string petName;
                    getline(inFile, petName);
                    tempFile << petName << endl;
                    
                    if (petName != "empty") {
                        // Read pet stats
                        int trainingPoints, level, maxHealth, maxAttack, maxDefense, maxMana, maxSpeed;
                        inFile >> trainingPoints >> level >> maxHealth >> maxAttack >> maxDefense >> maxMana >> maxSpeed;
                        inFile.ignore(); // Consume the newline
                        
                        // Write pet stats to temp file
                        tempFile << trainingPoints << endl << level << endl << maxHealth << endl
                                 << maxAttack << endl << maxDefense << endl << maxMana << endl << maxSpeed << endl;
                    }
                }
            }
        }
        
        // Close both files
        inFile.close();
        tempFile.close();
        
        // Replacing the original file with the temp file
        remove("players.txt");
        rename("temp.txt", "players.txt");
        
        if (foundUser) {
            cout << "Player data for " << username << " removed from file after loading." << endl;
        } else {
            cout << "Player not found or incorrect password." << endl;
        }
        
        return foundUser;
    }

    void savePlayerdata(const string& username, const string& password, const string& guildName) {
        // Save player info to file

        bool ishealthPotion = true;
        bool isbuffPotion = true;
        bool ismanaPotion = true;
        bool isSheildPotion = true;

        ofstream out("players.txt", ios::app);

        if (out.is_open()) {
            out << username << endl;
            out << password << endl;
            out << guildName << endl;
            out << player->getCurrency() << endl;
            
            // Use getter functions to access inventory information
            out << player->getInventorySize() << endl;
            out << player->getInventoryCapacity() << endl;
            
            // Save each inventory item using getter functions
            Item** playerInventory = player->getInventory();
            for (int i = 0; i < player->getInventorySize(); i++) {
                Item* currentItem = player->getInventoryItem(i);
                if (currentItem != nullptr) {
                    out << currentItem->getName() << endl;
                    out << currentItem->getbar() << endl;
                    out << currentItem->getType() << endl;

                    if(currentItem->getName() == "Healing Potion" && ishealthPotion) {
                        out << currentItem->getCount() << endl;
                        ishealthPotion = false;

                    }else if (currentItem->getName() == "Shield" && isSheildPotion) {
                        out << currentItem->getCount() << endl;
                        isSheildPotion = false;
                    
                    }else if (currentItem->getName() == "Mana Potion" && ismanaPotion) {
                        out << currentItem->getCount() << endl;
                        ismanaPotion = false;

                    }else if(currentItem->getName() == "Buff Item" && isbuffPotion) {
                        out << currentItem->getCount() << endl;
                        isbuffPotion = false;
                    }
                } 
            }

            Guild* currentGuild = player->getGuild();
            Pet *selectedPet = nullptr;

            for(int i = 0 ; i < 4 ; i++) {
                Pet *selectedPet = currentGuild->getPet(i);
                if(selectedPet != nullptr) {
                    out << selectedPet->getName() << endl;
                    out << selectedPet->getTrainingPoints() << endl;
                    out << selectedPet->getLevel() << endl;
                    out << selectedPet->getMaxHealth() << endl;
                    out << selectedPet->getMaxAttack() << endl;
                    out << selectedPet->getMaxDefense() << endl;
                    out << selectedPet->getMaxMana() << endl;
                    out << selectedPet->getMaxSpeed() << endl;
                } else {
                    out << "empty" << endl; 
                }
            }
            
            out.close();
            cout << "Player saved successfully!" << endl;
        } else {
            cout << "Failed to save player data!" << endl;
        }
    }

    Player* getPlayer() {
        return player;  
    }
};

// attacking struct objects vectors
struct Attack {
    RectangleShape shape;
    float directionX;
    float directionY;
    bool active;
};

//Powerup Struct
struct PowerUp {
    CircleShape shape;
    int type;         
    bool active;
    float lifetime;
};


struct Screen {
    int value;

    static const int START;
    static const int OPTIONS;
    static const int RESUME;
    static const int REGISTER;
    static const int GAME;
    static const int SHOP;
    static const int TRAINING_CAMP;
    static const int BATTLE;
    static const int ONE_V_ONE;
    static const int TWO_V_TWO;
    static const int GUILD_V_GUILD;
    static const int FIGHT;

    Screen(int v) : value(v) {}

    bool operator==(int v) const { return value == v; }
    bool operator!=(int v) const { return value != v; }
};

// Define the constants
const int Screen::START         = 0;
const int Screen::OPTIONS       = 1;
const int Screen::RESUME        = 2;
const int Screen::REGISTER      = 3;
const int Screen::GAME          = 4;
const int Screen::SHOP          = 5;
const int Screen::TRAINING_CAMP = 6;
const int Screen::BATTLE        = 7;
const int Screen::ONE_V_ONE     = 8;
const int Screen::TWO_V_TWO     = 9;
const int Screen::GUILD_V_GUILD = 10;
const int Screen::FIGHT         = 11;


struct InputField {
    int value;
    static const int NONE;
    static const int USERNAME;
    static const int PASSWORD;
    static const int GUILD;

    InputField(int v) : value(v) {}

    bool operator==(int v) const { return value == v; }
    bool operator!=(int v) const { return value != v; }
};

const int InputField::NONE     = 0;
const int InputField::USERNAME = 1;
const int InputField::PASSWORD = 2;
const int InputField::GUILD    = 3;

int main() {

    srand(time(0));

    GameManager* gameManager = new GameManager();
    Guild* currentGuild = nullptr; //For getting current guild of the player
    Pet *selectedPet = nullptr; // For the pets of the current player usually used in battle and training
    Player* currentPlayer = nullptr; // For the current player of the game
    Item* selected = nullptr; // For the items of the current player usually used in shop 

    bool petSelected = false; // For checking if a pet is selected in training
    int petCount = 0; // For counting the number of pets of the current player

    bool inShopMode = false; //Cecking the screens used for rendering
    bool inBattleMode = false;
    bool inTrainingMode = false;
    
    int Hcount = 0; // To show the item counts on the screen for all the potion
    int Mcount = 0;
    int Bcount = 0;
    int Scount = 0;

    int maxhealth = 0; // To these on the screen for training camp near the stats
    int maxattack = 0;
    int maxdefense = 0;
    int maxMana = 0;
    int maxspeed = 0;

    bool startTraining = false; // To start the training
    bool setscore = false; // To set the score of the player in the game for trainig camp

    bool OneVOneMode = false; // Battle Screens
    bool TwoVTwoMode = false;
    bool GuildVGuildMode = false;
    bool FightMode = false;

    RenderWindow window(VideoMode(1280, 720), "Game Menu");

    // Loading background texture
    Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("background.png")) {
        cerr << "Failed to load background image!" << endl;
        return -1;
    }
    Sprite background(backgroundTexture);
    background.setScale(
        float(window.getSize().x) / backgroundTexture.getSize().x,
        float(window.getSize().y) / backgroundTexture.getSize().y
    );

    // Loading font
    Font font;
    if (!font.loadFromFile("arial.ttf")) {
        cerr << "Failed to load font!" << endl;
        return -1;
    }

    Music music;
    if (!music.openFromFile("music.ogg")) {
        cout << "Could not load music file.\n";
        return -1;
    }
    music.setLoop(true);
    music.play();

    // Screen state
    Screen currentScreen = Screen::START;

    // Shared Parameters fot the game used in setting the position
    Vector2f buttonSize(200, 80);
    float centerX = 640;
    float rightX = 850;
    float firstButtonY = 200;
    float gap = 30;

    //For the Game Menu
    Texture petTextures[4];
    Sprite petSprites[4];

    //For the Training Camp
    Texture petMiniTextures[4];
    Sprite petMiniSprites[4];

    petTextures[0].loadFromFile("dragon.png");
    petTextures[1].loadFromFile("phoenix.png");
    petTextures[2].loadFromFile("unicorn.png");
    petTextures[3].loadFromFile("griffin.png");

    petSprites[0].setTexture(petTextures[0]);
    petSprites[0].setScale(0.5f, 0.5f);
    petSprites[0].setPosition(100,100);

    petSprites[1].setTexture(petTextures[1]);
    petSprites[1].setScale(0.45f, 0.45f);
    petSprites[1].setPosition(500,100);

    petSprites[2].setTexture(petTextures[2]);
    petSprites[2].setScale(0.5f, 0.5f);
    petSprites[2].setPosition(100,400);

    petSprites[3].setTexture(petTextures[3]);
    petSprites[3].setScale(0.5f, 0.5f);
    petSprites[3].setPosition(500,400);

    petMiniTextures[0].loadFromFile("dragon.png");
    petMiniTextures[1].loadFromFile("phoenix.png");
    petMiniTextures[2].loadFromFile("unicorn.png");
    petMiniTextures[3].loadFromFile("griffin.png");

    petMiniSprites[0].setTexture(petMiniTextures[0]);
    petMiniSprites[0].setScale(0.25f, 0.25f);
    petMiniSprites[0].setPosition(90, 100);

    petMiniSprites[1].setTexture(petMiniTextures[1]);
    petMiniSprites[1].setScale(0.21f, 0.21f);
    petMiniSprites[1].setPosition(90, 240);

    petMiniSprites[2].setTexture(petMiniTextures[2]);
    petMiniSprites[2].setScale(0.25f, 0.25f);
    petMiniSprites[2].setPosition(90, 380);

    petMiniSprites[3].setTexture(petMiniTextures[3]);
    petMiniSprites[3].setScale(0.25f, 0.25f);
    petMiniSprites[3].setPosition(90, 500);

    //For the Training Camp To show that pet is selected
    Sprite petGameSprites[4];
    for (int i = 0; i < 4; ++i) {
        petGameSprites[i].setTexture(petMiniTextures[i]);
        petGameSprites[i].setScale(0.25f, 0.25f); 
        petGameSprites[i].setPosition(900, 550);  
    }

    // Define a square for the Training
    RectangleShape gameSquare(Vector2f(650.f, 580.f));
    gameSquare.setPosition(800.f - 250.f, 110.f);  
    gameSquare.setFillColor(Color(0, 0, 0, 120));  
    gameSquare.setOutlineColor(Color::White);
    gameSquare.setOutlineThickness(3.f);

    Texture TrainingbackgroundTexture;
    if (!TrainingbackgroundTexture.loadFromFile("TrainingBackground.jpg")) {
        return -1; 
    }

    Sprite TrainigbackgroundSprite;
    TrainigbackgroundSprite.setTexture(TrainingbackgroundTexture);

    TrainigbackgroundSprite.setPosition(gameSquare.getPosition());
    TrainigbackgroundSprite.setScale(
        gameSquare.getSize().x / TrainingbackgroundTexture.getSize().x,
        gameSquare.getSize().y / TrainingbackgroundTexture.getSize().y
    );

    Texture rockTexture;
    if (!rockTexture.loadFromFile("rock.png")) {
        return -1; 
    }

    Sprite boxes[20];  
    bool boxActive[20] = { false }; 
    Clock boxSpawnClock; //Clock for the Spawing of the boxes
    bool TraininggameOver = false;
    int score = 0;
    Clock scoreClock;

    Text TrainingscoreText;
    TrainingscoreText.setFont(font);
    TrainingscoreText.setCharacterSize(24);
    TrainingscoreText.setFillColor(Color::White);
    TrainingscoreText.setPosition(820, 10);  

    // For shop
    Texture itemTextures[4];
    Sprite itemSprites[4];

    // Mini item sprites for top right corner
    Texture miniItemTextures[4];
    Sprite miniItemSprites[4];

    // Load textures
    itemTextures[0].loadFromFile("Health.png");
    itemTextures[1].loadFromFile("Mana.png");
    itemTextures[2].loadFromFile("Buffitem.png");
    itemTextures[3].loadFromFile("Sheild.png");

    itemSprites[0].setTexture(itemTextures[0]);
    itemSprites[0].setScale(0.2f, 0.2f);  
    itemSprites[0].setPosition(250 + 80, 300); 
    
    itemSprites[1].setTexture(itemTextures[1]);
    itemSprites[1].setScale(0.12f, 0.12f);  
    itemSprites[1].setPosition(300 + 190, 300); 
    
    itemSprites[2].setTexture(itemTextures[2]);
    itemSprites[2].setScale(0.21f, 0.21f);  
    itemSprites[2].setPosition(365 + 300, 305); 
    
    itemSprites[3].setTexture(itemTextures[3]);
    itemSprites[3].setScale(0.55f, 0.55f);  
    itemSprites[3].setPosition(400 + 410, 300); 

    // Set up mini sprites for top right corner
    miniItemSprites[0].setTexture(itemTextures[0]);
    miniItemSprites[0].setScale(0.1f, 0.1f);  
    miniItemSprites[0].setPosition(950, 20); 

    miniItemSprites[1].setTexture(itemTextures[1]);
    miniItemSprites[1].setScale(0.06f, 0.06f); 
    miniItemSprites[1].setPosition(1020, 20); 

    miniItemSprites[2].setTexture(itemTextures[2]);
    miniItemSprites[2].setScale(0.11f, 0.11f);  
    miniItemSprites[2].setPosition(1090, 20); 

    miniItemSprites[3].setTexture(itemTextures[3]);
    miniItemSprites[3].setScale(0.275f, 0.275f); 
    miniItemSprites[3].setPosition(1160, 20); 

    Text shopScreenText("Shop", font, 60);
    shopScreenText.setFillColor(Color::White);
    shopScreenText.setPosition(centerX - 120, 50);

    Text itemNames[4] = {
        Text("Health Potion", font, 16),
        Text("Mana Potion", font, 16),
        Text("Buff Potion", font, 16),
        Text("Shield Potion", font, 16)
    };
    
    Text itemCosts[4] = {
        Text("150 coins", font, 14),
        Text("150 coins", font, 14),
        Text("150 coins", font, 14),
        Text("150 coins", font, 14)
    };
    
    itemNames[0].setFillColor(Color::White);
    itemNames[0].setPosition(itemSprites[0].getPosition().x - 60, itemSprites[0].getPosition().y + 130);
    
    itemCosts[0].setFillColor(Color::Yellow);
    itemCosts[0].setPosition(itemSprites[0].getPosition().x - 3, itemSprites[0].getPosition().y + 160);

    itemNames[1].setFillColor(Color::White);
    itemNames[1].setPosition(itemSprites[1].getPosition().x - 13, itemSprites[0].getPosition().y + 130);
    
    itemCosts[1].setFillColor(Color::Yellow);
    itemCosts[1].setPosition(itemSprites[1].getPosition().x + 15, itemSprites[0].getPosition().y + 160);

    itemNames[2].setFillColor(Color::White);
    itemNames[2].setPosition(itemSprites[2].getPosition().x - 13, itemSprites[0].getPosition().y + 130);
    
    itemCosts[2].setFillColor(Color::Yellow);
    itemCosts[2].setPosition(itemSprites[2].getPosition().x + 8, itemSprites[0].getPosition().y + 160);

    itemNames[3].setFillColor(Color::White);
    itemNames[3].setPosition(itemSprites[3].getPosition().x - 3, itemSprites[0].getPosition().y + 130);
    
    itemCosts[3].setFillColor(Color::Yellow);
    itemCosts[3].setPosition(itemSprites[3].getPosition().x + 16, itemSprites[0].getPosition().y + 160);

    // Input values
    InputField currentInput = InputField::NONE;
    string username, password, LegitPassword ,guildName;
    
    // Message text for invalid inputs
    Text messageText("", font, 24);
    messageText.setFillColor(Color::Red);
    messageText.setPosition(350, 590);
    string message = "";

    // --- Main Menu Buttons (Centered) ---
    RectangleShape startButton(Vector2f(240, 60));
    startButton.setFillColor(Color::Black);
    startButton.setPosition(centerX - 120, 354);

    Text startText("Start Game", font, 24);
    startText.setFillColor(Color::White);
    startText.setPosition(centerX - 105, 364);

    RectangleShape resumeButton(Vector2f(200, 60));
    resumeButton.setFillColor(Color::Black);
    resumeButton.setPosition(centerX - 100, 270);

    Text resumeText("Resume", font, 24);
    resumeText.setFillColor(Color::White);
    resumeText.setPosition(centerX - 67, 286);

    RectangleShape registerButton(Vector2f(200, 60));
    registerButton.setFillColor(Color::Black);
    registerButton.setPosition(centerX - 100, 430);

    Text registerText("Register", font, 24);
    registerText.setFillColor(Color::White);
    registerText.setPosition(centerX - 71, 446);

    RectangleShape submitButton(Vector2f(200, 60));
    submitButton.setFillColor(Color::Black);
    submitButton.setPosition(centerX - 100, 510);

    Text submitText("Submit", font, 24);
    submitText.setFillColor(Color::White);
    submitText.setPosition(centerX - 65, 526);

    RectangleShape backButton(Vector2f(100, 40));
    backButton.setFillColor(Color::Black);
    backButton.setPosition(50, 660);

    Text backText("Back", font, 20);
    backText.setFillColor(Color::White);
    backText.setPosition(70, 668);

    // --- Game Buttons (Right Side) ---
    RectangleShape battleButton(buttonSize);
    battleButton.setFillColor(Color::Black);
    battleButton.setPosition(rightX, firstButtonY);

    Text battleText("Battle", font, 24);
    battleText.setFillColor(Color::White);
    FloatRect textBounds = battleText.getLocalBounds();
    battleText.setPosition(
        rightX + (buttonSize.x - textBounds.width) / 2 - textBounds.left,
        firstButtonY + (buttonSize.y - textBounds.height) / 2 - textBounds.top
    );

    RectangleShape trainingButton(buttonSize);
    trainingButton.setFillColor(Color::Black);
    trainingButton.setPosition(rightX, firstButtonY + (buttonSize.y + gap) * 1);

    Text trainingText("Training", font, 20);
    trainingText.setFillColor(Color::White);
    textBounds = trainingText.getLocalBounds();
    trainingText.setPosition(
        rightX + (buttonSize.x - textBounds.width) / 2 - textBounds.left,
        trainingButton.getPosition().y + (buttonSize.y - textBounds.height) / 2 - textBounds.top
    );

    RectangleShape shopButton(buttonSize);
    shopButton.setFillColor(Color::Black);
    shopButton.setPosition(rightX, firstButtonY + (buttonSize.y + gap) * 2);

    Text shopText("Shop", font, 24);
    shopText.setFillColor(Color::White);
    textBounds = shopText.getLocalBounds();
    shopText.setPosition(
        rightX + (buttonSize.x - textBounds.width) / 2 - textBounds.left,
        shopButton.getPosition().y + (buttonSize.y - textBounds.height) / 2 - textBounds.top
    );

    RectangleShape exitButton(buttonSize);
    exitButton.setFillColor(Color::Black);
    exitButton.setPosition(rightX, firstButtonY + (buttonSize.y + gap) * 3);

    Text exitText("Exit", font, 24);
    exitText.setFillColor(Color::White);
    textBounds = exitText.getLocalBounds();
    exitText.setPosition(
        rightX + (buttonSize.x - textBounds.width) / 2 - textBounds.left,
        exitButton.getPosition().y + (buttonSize.y - textBounds.height) / 2 - textBounds.top
    );

    // --- Input Boxes ---
    RectangleShape usernameBox(Vector2f(400, 50));
    usernameBox.setFillColor(Color(200, 200, 200));
    usernameBox.setPosition(centerX - 200, 170);

    RectangleShape passwordBox(Vector2f(400, 50));
    passwordBox.setFillColor(Color(200, 200, 200));
    passwordBox.setPosition(centerX - 200, 250);

    RectangleShape guildBox(Vector2f(400, 50));
    guildBox.setFillColor(Color(200, 200, 200));
    guildBox.setPosition(centerX - 200, 330);

    // --- Input Labels ---
    Text usernameLabelText("Username:", font, 20);
    usernameLabelText.setFillColor(Color::White);
    usernameLabelText.setPosition(centerX - 200, 140);

    Text passwordLabelText("Password:", font, 20);
    passwordLabelText.setFillColor(Color::White);
    passwordLabelText.setPosition(centerX - 200, 220);

    Text guildLabelText("Guild Name:", font, 20);
    guildLabelText.setFillColor(Color::White);
    guildLabelText.setPosition(centerX - 200, 300);

    // --- Input Texts ---
    Text usernameText("", font, 24);
    usernameText.setFillColor(Color::Black);

    Text passwordText("", font, 24);
    passwordText.setFillColor(Color::Black);

    Text guildText("", font, 24);
    guildText.setFillColor(Color::Black);

    // --- Game Screen Text for the player Info ---
    Text gameScreenText("", font, 28);
    gameScreenText.setFillColor(Color::White);
    gameScreenText.setPosition(300, 200);

    Text guildInfoText("", font, 24);
    guildInfoText.setFillColor(Color::White);
    guildInfoText.setPosition(300, 250);

    // Training Camp Screen
    Text trainingScreenText("Training Camp", font, 40);
    trainingScreenText.setFillColor(Color::White);
    trainingScreenText.setPosition(centerX - 200, 30);

    RectangleShape StartTrainingButton(Vector2f(100, 40));
    StartTrainingButton.setFillColor(Color::Black);
    StartTrainingButton.setPosition(rightX + (buttonSize.x - textBounds.width) / 2 - textBounds.left - 500,
        trainingButton.getPosition().y + (buttonSize.y - textBounds.height) / 2 - textBounds.top + 50
    );

    Text StartTrainingButtonText("Start", font, 20);
    StartTrainingButtonText.setFillColor(Color::White);
    StartTrainingButtonText.setPosition(    rightX + (buttonSize.x - textBounds.width) / 2 - textBounds.left - 500,
        trainingButton.getPosition().y + (buttonSize.y - textBounds.height) / 2 - textBounds.top + 50
    );

    // Battle Screen
    Text battleScreenText("Battle Arena", font, 40);
    battleScreenText.setFillColor(Color::White);
    battleScreenText.setPosition(centerX - 180, 100);
    
    Text battleDescription("Choose Battle Type!!", font, 34);
    battleDescription.setFillColor(Color::White);
    battleDescription.setPosition(centerX - 240, 200);

    //1v1, 2v2 Screen text
    Text One_V_OneButtonText("One Vs One", font, 32); 
    One_V_OneButtonText.setFillColor(Color::White);
    One_V_OneButtonText.setPosition(centerX - 150, 350);

    RectangleShape One_V_OneButton(Vector2f(280, 60));
    One_V_OneButton.setFillColor(Color::Black);
    One_V_OneButton.setPosition(centerX - 160, 342);

    Text Two_V_TwoButtonText("Two Vs Two", font, 32); 
    Two_V_TwoButtonText.setFillColor(Color::White);
    Two_V_TwoButtonText.setPosition(centerX - 150, 450);

    RectangleShape Two_V_TwoButton(Vector2f(310, 60));
    Two_V_TwoButton.setFillColor(Color::Black);
    Two_V_TwoButton.setPosition(centerX - 160, 440);
    
    Text Guild_V_GuildButtonText("Guild Vs Guild", font, 32); 
    Guild_V_GuildButtonText.setFillColor(Color::White);
    Guild_V_GuildButtonText.setPosition(centerX - 150, 550);

    RectangleShape Guild_V_GuildButton(Vector2f(360, 60));
    Guild_V_GuildButton.setFillColor(Color::Black);
    Guild_V_GuildButton.setPosition(centerX - 160, 540);

    Text petSelectionText("Select Pets For the Battle!!", font, 24);
    petSelectionText.setFillColor(Color::White);
    petSelectionText.setPosition(centerX - 240, 50);
    
    Texture petSelectionTextures[4];
    Sprite petSelectionSprites[4];

    petSelectionTextures[0].loadFromFile("dragon.png");
    petSelectionTextures[1].loadFromFile("phoenix.png");
    petSelectionTextures[2].loadFromFile("unicorn.png");
    petSelectionTextures[3].loadFromFile("griffin.png");

    petSelectionSprites[0].setTexture(petSelectionTextures[0]);
    petSelectionSprites[0].setScale(0.4f, 0.4f);
    petSelectionSprites[0].setPosition(300,120);

    petSelectionSprites[1].setTexture(petSelectionTextures[1]);
    petSelectionSprites[1].setScale(0.35f, 0.35f);
    petSelectionSprites[1].setPosition(900,130);

    petSelectionSprites[2].setTexture(petSelectionTextures[2]);
    petSelectionSprites[2].setScale(0.4f, 0.4f);
    petSelectionSprites[2].setPosition(300,400);

    petSelectionSprites[3].setTexture(petSelectionTextures[3]);
    petSelectionSprites[3].setScale(0.4f, 0.4f);
    petSelectionSprites[3].setPosition(900,400);

    Texture petBattleTextures[4];
    Sprite petBattleSprites[4];

    petBattleTextures[0].loadFromFile("dragon.png");
    petBattleTextures[1].loadFromFile("phoenix.png");
    petBattleTextures[2].loadFromFile("unicorn.png");
    petBattleTextures[3].loadFromFile("griffin.png");

    petBattleSprites[0].setTexture(petBattleTextures[0]);
    petBattleSprites[0].setScale(0.25f, 0.25f);
    petBattleSprites[0].setPosition(100,320);

    petBattleSprites[1].setTexture(petBattleTextures[1]);
    petBattleSprites[1].setScale(0.2f, 0.2f);
    petBattleSprites[1].setPosition(100,320);

    petBattleSprites[2].setTexture(petBattleTextures[2]);
    petBattleSprites[2].setScale(0.25f, 0.25f);
    petBattleSprites[2].setPosition(100,320);

    petBattleSprites[3].setTexture(petBattleTextures[3]);
    petBattleSprites[3].setScale(0.25f, 0.25f);
    petBattleSprites[3].setPosition(100,320);

    Sprite botPetBattleSprites[4];
    botPetBattleSprites[0].setTexture(petBattleTextures[0]);
    botPetBattleSprites[0].setScale(00.25f, 0.25f);
    botPetBattleSprites[0].setPosition(1100,320);

    botPetBattleSprites[1].setTexture(petBattleTextures[1]);
    botPetBattleSprites[1].setScale(0.2f, 0.2f);
    botPetBattleSprites[1].setPosition(1100,320);

    botPetBattleSprites[2].setTexture(petBattleTextures[2]);
    botPetBattleSprites[2].setScale(0.25f, 0.25f);
    botPetBattleSprites[2].setPosition(1100,320);

    botPetBattleSprites[3].setTexture(petBattleTextures[3]);
    botPetBattleSprites[3].setScale(0.25f, 0.25f);
    botPetBattleSprites[3].setPosition(1100,320);

    Text DragonSelectButtonText("Select", font, 24); 
    DragonSelectButtonText.setFillColor(Color::White);
    DragonSelectButtonText.setPosition(170, 200);

    RectangleShape DragonSelectButton(Vector2f(130, 40));
    DragonSelectButton.setFillColor(Color::Black);
    DragonSelectButton.setPosition(160, 200);

    Text PhoenixSelectButtonText("Select", font, 24); 
    PhoenixSelectButtonText.setFillColor(Color::White);
    PhoenixSelectButtonText.setPosition(770, 200);

    RectangleShape PhoenixSelectButton(Vector2f(130, 40));
    PhoenixSelectButton.setFillColor(Color::Black);
    PhoenixSelectButton.setPosition(760, 200);

    Text UnicornSelectButtonText("Select", font, 24); 
    UnicornSelectButtonText.setFillColor(Color::White);
    UnicornSelectButtonText.setPosition(170, 500);

    RectangleShape UnicornSelectButton(Vector2f(130, 40));
    UnicornSelectButton.setFillColor(Color::Black);
    UnicornSelectButton.setPosition(160, 500);

    Text GriffinSelectButtonText("Select", font, 24); 
    GriffinSelectButtonText.setFillColor(Color::White);
    GriffinSelectButtonText.setPosition(770, 500);

    RectangleShape GriffinSelectButton(Vector2f(130, 40));
    GriffinSelectButton.setFillColor(Color::Black);
    GriffinSelectButton.setPosition(760, 500);

    Pet *pet1= nullptr;  //Curren Pet for the battle
    Pet *botpet = nullptr;
    int random = 0;
    int petindex = 0;

    float width = petBattleSprites[petindex].getGlobalBounds().width;
    float height = petBattleSprites[petindex].getGlobalBounds().height;
    FloatRect bounds = petBattleSprites[petindex].getGlobalBounds();

    float PLAYER_SPEED = 1.5f;
    float ENEMY_SPEED = 1.5f;  // Increased enemy speed
    float BULLET_SPEED = 3.0f;
    int MAX_ATTACKS = 100;
    int MAX_ENEMY_ATTACKS = 100;
    float ENEMY_SHOOT_COOLDOWN = 0.7f;  // Reduced cooldown for more frequent shots
    int SCORE_TO_WIN = 15; 
    int WINDOW_WIDTH = 1280;
    int WINDOW_HEIGHT = 720;

    // Initialize Attack
    Attack attacks[MAX_ATTACKS];
    for (int i = 0; i < MAX_ATTACKS; i++) {
        attacks[i].shape.setSize(Vector2f(15.0f, 15.0f));
        attacks[i].shape.setFillColor(Color::Yellow);
        attacks[i].active = false;
    }

    // Initialize enemy Attack
    Attack enemyAttacks[MAX_ENEMY_ATTACKS];
    for (int i = 0; i < MAX_ENEMY_ATTACKS; i++) {
        enemyAttacks[i].shape.setSize(Vector2f(15.0f, 15.0f));
        enemyAttacks[i].shape.setFillColor(Color::Cyan);
        enemyAttacks[i].active = false;
    }

    // Initialize power-up
    PowerUp powerUp;
    powerUp.shape.setRadius(15.0f);
    powerUp.shape.setFillColor(Color::White);
    powerUp.active = false;
    powerUp.type = EMPTY;
    
     // Game state variables
    float enemyShootTimer = 0.0f;
    float playerShootCooldown = 0.3f;
    float currentPlayerShootCooldown = 0.0f;
    float powerUpSpawnTimer = 5.0f;
    float powerUpDuration = 0.0f;
    
    bool BattlegameOver = false;
    bool playerWon = false;
    bool botWon = false;
    bool playerHasShield = false;
    bool playerHasSpeedBoost = false;
    bool playerHasRapidFire = false;

    // Enemy AI variables
    float enemyTargetX = botPetBattleSprites[0].getPosition().x;
    float enemyTargetY = botPetBattleSprites[0].getPosition().y;
    float enemyDodgeChance = 0.7f;
    Clock enemyAIClock;
    
    // Set up power-up text
    Text powerUpText;
    powerUpText.setFont(font);
    powerUpText.setCharacterSize(16);
    powerUpText.setPosition(700.0f, 40.0f);
    powerUpText.setFillColor(Color::White);
    
    // Set up score
    int playerScore = 0;
    
    Text BattlescoreText;
    BattlescoreText.setFont(font);
    BattlescoreText.setCharacterSize(24);
    BattlescoreText.setPosition(10.0f, 10.0f);
    BattlescoreText.setString("Points: " + to_string(playerScore) + " | To " + to_string(SCORE_TO_WIN) + " wins!");
                    
    // Game clock for delta time calculation
    Clock clock;
    bool gameStarted = false;
    bool PlayerUsesBuffitem = false;
    float BuffitemDuratiion = 0.0f;
    float SheildPotionDuratiion = 0.0f;
    
    Text ItemMessage;
    Clock ItemMessageTimer;
    float ItemMessageDuration = 3.0f;
    bool ItemShowMessage = false;
    
    ItemMessage.setFont(font);
    ItemMessage.setCharacterSize(24);
    ItemMessage.setFillColor(Color::Red);
    ItemMessage.setPosition(1280 / 2 - 200, 100);

    Text GameOverMssgText;
    GameOverMssgText.setFont(font);
    GameOverMssgText.setCharacterSize(40);
    GameOverMssgText.setFillColor(Color::Red);
 
    FloatRect GameOvertextRect = GameOverMssgText.getLocalBounds();
    GameOverMssgText.setOrigin(GameOvertextRect.left + GameOvertextRect.width / 2.0f, GameOvertextRect.top + GameOvertextRect.height / 2.0f);
    GameOverMssgText.setPosition(1280 / 2.0f - 200, 720 / 2.0f - 50);

    //For Guild V GUild
    Clock BotChangetimer;
    float BotChangeDuration = 10.0f;

    //For 2v2.
    int pet1index = -1;
    int pet2index = -1;
    bool selectionComplete = false;
    int currentPetTurn = 0;

    int botPet1Index = 0;
    int botPet2Index = 0;
    int currentBotTurn = 0;

    Clock Bot2v2Changetimer;
    float Bot2v2ChangeDuration = 10.0f;

    Text warningText;
    Clock warningClock; 

    warningText.setFont(font);
    warningText.setCharacterSize(24);
    warningText.setFillColor(Color::Red);
    warningText.setPosition(640 - 200, 90); 
    warningText.setString(""); 

    //Arena
    Texture arenaTextures[4];
    Sprite arenaSprites[4];

    arenaTextures[0].loadFromFile("arena_1.png");
    arenaTextures[1].loadFromFile("arena_2.png");
    arenaTextures[2].loadFromFile("arena_3.png");
    arenaTextures[3].loadFromFile("arena_4.png");

    //Scaling the Arena
    for (int i = 0; i < 4; i++) {
        arenaSprites[i].setTexture(arenaTextures[i]);
        Vector2u textureSize = arenaTextures[i].getSize();
        
        float scaleX = 1280.0f / textureSize.x;
        float scaleY = 720.0f / textureSize.y;

        arenaSprites[i].setScale(scaleX, scaleY);
    }

    int selectedArenaIndex = 0; 
    int currentArenaIndex = 0;

    while (window.isOpen()) {
        Time deltaTime = clock.restart();
        float dt = deltaTime.asSeconds();
 
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();

            
            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
    
                // START SCREEN
                if (currentScreen == Screen::START && startButton.getGlobalBounds().contains(mousePos)) {
                    currentScreen = Screen::OPTIONS;
                    message = "";
                }
                
                // OPTIONS SCREEN
                else if (currentScreen == Screen::OPTIONS) {
                    if (resumeButton.getGlobalBounds().contains(mousePos)) {
                        currentScreen = Screen::RESUME;
                        currentInput = InputField::NONE;
                        username.clear(); password.clear();
                        message = "";
                    }
                    else if (registerButton.getGlobalBounds().contains(mousePos)) {
                        currentScreen = Screen::REGISTER;
                        currentInput = InputField::NONE;
                        username.clear(); password.clear(); guildName.clear();
                        message = "";
                    }
                }
                
                // BACK BUTTON FOR RESUME/REGISTER
                else if ((currentScreen == Screen::RESUME || currentScreen == Screen::REGISTER) && backButton.getGlobalBounds().contains(mousePos)) {
                    currentScreen = Screen::OPTIONS;
                    message = "";
                }
                
                // RESUME/REGISTER SCREENS
                else if (currentScreen == Screen::RESUME || currentScreen == Screen::REGISTER) {
                    if (usernameBox.getGlobalBounds().contains(mousePos))
                        currentInput = InputField::USERNAME;
                    else if (passwordBox.getGlobalBounds().contains(mousePos))
                        currentInput = InputField::PASSWORD;
                    else if (currentScreen == Screen::REGISTER && guildBox.getGlobalBounds().contains(mousePos))
                        currentInput = InputField::GUILD;
                    else if (submitButton.getGlobalBounds().contains(mousePos)) {
                        // Handle submit button click
                        if (currentScreen == Screen::REGISTER) {
                            if (username.empty() || password.empty() || guildName.empty()) {
                                message = "Please fill in all fields!";
                            } else {
                                gameManager->registerPlayer(username, password, guildName);
                                currentScreen = Screen::GAME;
                                inShopMode = false;
                                inTrainingMode = false;
                                inBattleMode = false;
                                message = "";
                            }
                        } else if (currentScreen == Screen::RESUME) {
                            if (username.empty() || password.empty()) {
                                message = "Please enter username and password!";
                            } else if (gameManager->resumePlayer(username, password)) {
                                currentScreen = Screen::GAME;
                                inShopMode = false;
                                inTrainingMode = false;
                                inBattleMode = false;
                                message = "";
                            } else {
                                message = "Invalid username or password!";
                            }
                        }
                    }
                    else
                        currentInput = InputField::NONE;
                }
                
                // GAME SCREEN NAVIGATION
                else if (currentScreen == Screen::GAME) {
                    currentPlayer = gameManager->getPlayer();
                    currentGuild = currentPlayer->getGuild();
                    
                    // Shop Button
                    if (shopButton.getGlobalBounds().contains(mousePos)) {
                        inShopMode = true;
                        inTrainingMode = false;
                        inBattleMode = false;
                        currentScreen = Screen::SHOP;
                    }
                    
                    // Training Button
                    else if (trainingButton.getGlobalBounds().contains(mousePos)) {
                        inTrainingMode = true;
                        inShopMode = false;
                        inBattleMode = false;
                        currentScreen = Screen::TRAINING_CAMP;
                    }
                    
                    // Battle Button
                    else if (battleButton.getGlobalBounds().contains(mousePos)) {
                        inBattleMode = true;
                        inShopMode = false;
                        inTrainingMode = false;
                        currentScreen = Screen::BATTLE;
                    }
                    
                    // Exit Button
                    else if (exitButton.getGlobalBounds().contains(mousePos)) {
                        inShopMode = false;
                        inTrainingMode = false;
                        inBattleMode = false;
                       
                        
                        guildName = currentGuild->getName();
                        gameManager->savePlayerdata(username, password, guildName);

                        // Clean up resources
                        delete gameManager; // This will handle deleting the Player and associated objects
                        return 0;
                    }
                }
                
                // SHOP SCREEN
                else if (currentScreen == Screen::SHOP) {
                    if (backButton.getGlobalBounds().contains(mousePos)) {
                        currentScreen = Screen::GAME;
                        inShopMode = false;
                    }
                    
                    // Item purchase handling (using existing code logic)
                    if (currentPlayer != nullptr) {
                        // Check item clicks
                        for (int i = 0; i < 4; ++i) {
                            if (itemSprites[i].getGlobalBounds().contains(mousePos)) {
                                selected = currentPlayer->getShop().buyItem(i);
                                if (selected) {
                                    int cost = selected->getCost();
                                    if (currentPlayer->deductCurrency(cost)) {    
                                        currentPlayer->addItem(selected);
                                        message = "Item purchased successfully!";
                                    } else {
                                        delete selected; // Only delete if not added to inventory
                                        message = "Not enough currency!";
                                    }
                                }
                                break; // Ensure only one item is processed
                            }
                        }
                    }
                }
                
                //Training Camp
                else if (currentScreen == Screen::TRAINING_CAMP) {
                    if (backButton.getGlobalBounds().contains(mousePos)) {
                        currentScreen = Screen::GAME;
                        inTrainingMode = false;
                    }
                    if (currentPlayer != nullptr) {
                    
                        currentGuild = currentPlayer->getGuild();
                        if (currentGuild != nullptr)  {
                            // Check item clicks with improved debug output
                            for (int petIdx = 0; petIdx < 4; ++petIdx) {
                                if (petMiniSprites[petIdx].getGlobalBounds().contains(mousePos)) {
                                    selectedPet = currentGuild->getPet(petIdx);
                                    petCount = petIdx;
                            
                                    if (selectedPet) {
                                        petSelected = true;
                                        TraininggameOver = false;
                                        score = 0;
                                        scoreClock.restart();
                                    }
                                    
                                    break;
                                }
                            }

                            if(petSelected && StartTrainingButton.getGlobalBounds().contains(mousePos)) {
                                startTraining = true;
                                scoreClock.restart();
                            }
                            
                        }
                    } 
                }
                
                
                // BATTLE SCREEN
                else if (currentScreen == Screen::BATTLE) {

                    if (backButton.getGlobalBounds().contains(mousePos)) {
                        currentScreen = Screen::GAME;
                        inBattleMode = false;
                    }

                    if (One_V_OneButton.getGlobalBounds().contains(mousePos)) {
                        currentScreen = Screen::ONE_V_ONE;                        
                        OneVOneMode = true;
                        inBattleMode = false;
                        TwoVTwoMode = false;
                        GuildVGuildMode = false;

                    }

                    if (Two_V_TwoButton.getGlobalBounds().contains(mousePos)) {
                        currentScreen = Screen::TWO_V_TWO;                        
                        OneVOneMode = false;
                        inBattleMode = false;
                        TwoVTwoMode = true;
                        GuildVGuildMode = false;

                    }

                    if (Guild_V_GuildButton.getGlobalBounds().contains(mousePos)) {
                        currentScreen = Screen::GUILD_V_GUILD;                        
                        OneVOneMode = false;
                        inBattleMode = false;
                        TwoVTwoMode = false;
                        GuildVGuildMode = true;

                    }

                    selectedArenaIndex = rand() % 4; // random 0–3  
                    currentArenaIndex = selectedArenaIndex;
                //Implement logic for all the battles    
                } 
                
                else if (currentScreen == Screen::ONE_V_ONE) {

                    if (backButton.getGlobalBounds().contains(mousePos)) {
                        currentScreen = Screen::BATTLE;
                        inBattleMode = true;
                        OneVOneMode = false;
                    }


                    if(DragonSelectButton.getGlobalBounds().contains(mousePos)) {
                        currentScreen = Screen::FIGHT;
                        FightMode = true;
                        if (currentGuild && currentGuild->getPet(0)) {
                            pet1 = currentGuild->getPet(0);
                            petindex = 0;
                        } else {
                            cout << "Guild does not exits" << endl;
                            // handle error: maybe show a message or default pet
                        }

                         botpet = nullptr;
                         random = rand() % 4;
                         
                         if (random == 0) {
                            botpet = new Dragon();
                         } else if (random == 1) {
                            botpet = new Phoenix();
                         } else if (random == 2) {
                            botpet = new Unicorn();
                         } else if (random == 3) {
                            botpet = new Griffin();
                         }
                    }

                    if(UnicornSelectButton.getGlobalBounds().contains(mousePos)) {
                        currentScreen = Screen::FIGHT;
                        FightMode = true;
                         pet1= currentGuild->getPet(2);
                         botpet = nullptr;
                         random = rand() % 4;
                         petindex = 2;
                         if (random == 0) {
                            botpet = new Dragon();
                         } else if (random == 1) {
                            botpet = new Phoenix();
                         } else if (random == 2) {
                            botpet = new Unicorn();
                         } else if (random == 3) {
                            botpet = new Griffin();
                         }

                    }

                    if(GriffinSelectButton.getGlobalBounds().contains(mousePos)) {
                        currentScreen = Screen::FIGHT;
                        FightMode = true;

                         pet1= currentGuild->getPet(3);
                         botpet = nullptr;
                         random = rand() % 4;
                         petindex = 3;
                         if (random == 0) {
                            botpet = new Dragon();
                         } else if (random == 1) {
                            botpet = new Phoenix();
                         } else if (random == 2) {
                            botpet = new Unicorn();
                         } else if (random == 3) {
                            botpet = new Griffin();
                         }
                    }

                    if(PhoenixSelectButton.getGlobalBounds().contains(mousePos)) {
                        currentScreen = Screen::FIGHT;
                        FightMode = true;
                        
                         pet1= currentGuild->getPet(1);
                         botpet = nullptr;
                         random = rand() % 4;
                         petindex = 1;
                         
                         if (random == 0) {
                            botpet = new Dragon();
                         } else if (random == 1) {
                            botpet = new Phoenix();
                         } else if (random == 2) {
                            botpet = new Unicorn();
                         } else if (random == 3) {
                            botpet = new Griffin();
                         }
                    }
                    

                } else if (currentScreen == Screen::TWO_V_TWO) {

                    if (backButton.getGlobalBounds().contains(mousePos)) {
                        currentScreen = Screen::BATTLE;
                        inBattleMode = true;
                        TwoVTwoMode = false;

                        // Reset selection state
                        pet1index = -1;
                        pet2index = -1;
                        selectionComplete = false;
                    }

                    // Dragon selected
                    if (DragonSelectButton.getGlobalBounds().contains(mousePos)) {
                        int selectedIndex = 0;
                        if (pet1index == selectedIndex || pet2index == selectedIndex) {
                            warningText.setString("Pet already selected!");
                            warningClock.restart(); 
                        } else if (pet1index == -1) {
                            pet1index = selectedIndex;
                            cout << "Pet 1 selected: Index " << pet1index << endl;
                        } else if (pet2index == -1) {
                            pet2index = selectedIndex;
                            cout << "Pet 2 selected: Index " << pet2index << endl;
                        }
                    }

                    // Phoenix selected
                    if (PhoenixSelectButton.getGlobalBounds().contains(mousePos)) {
                        int selectedIndex = 1;
                        if (pet1index == selectedIndex || pet2index == selectedIndex) {
                            warningText.setString("Pet already selected!");
                            warningClock.restart(); 
                        } else if (pet1index == -1) {
                            pet1index = selectedIndex;
                            cout << "Pet 1 selected: Index " << pet1index << endl;
                        } else if (pet2index == -1) {
                            pet2index = selectedIndex;
                            cout << "Pet 2 selected: Index " << pet2index << endl;
                        }
                    }

                    // Unicorn selected
                    if (UnicornSelectButton.getGlobalBounds().contains(mousePos)) {
                        int selectedIndex = 2;
                        if (pet1index == selectedIndex || pet2index == selectedIndex) {
                            warningText.setString("Pet already selected!");
                            warningClock.restart();
                        } else if (pet1index == -1) {
                            pet1index = selectedIndex;
                            cout << "Pet 1 selected: Index " << pet1index << endl;
                        } else if (pet2index == -1) {
                            pet2index = selectedIndex;
                            cout << "Pet 2 selected: Index " << pet2index << endl;
                        }
                    }

                    // Griffin selected
                    if (GriffinSelectButton.getGlobalBounds().contains(mousePos)) {
                        int selectedIndex = 3;
                        if (pet1index == selectedIndex || pet2index == selectedIndex) {
                            warningText.setString("Pet already selected!");
                            warningClock.restart(); 
                        } else if (pet1index == -1) {
                            pet1index = selectedIndex;
                            cout << "Pet 1 selected: Index " << pet1index << endl;
                        } else if (pet2index == -1) {
                            pet2index = selectedIndex;
                            cout << "Pet 2 selected: Index " << pet2index << endl;
                        }
                    }

                    // If both pets selected
                    if (pet1index != -1 && pet2index != -1 && !selectionComplete) {
                        selectionComplete = true;
                        cout << "Both pets selected: " << pet1index << " and " << pet2index << endl;

                        currentScreen = Screen::FIGHT;
                        FightMode = true;
                        pet1 = currentGuild->getPet(pet1index);
                        petindex = pet1index;
                        currentPetTurn = 0;


                        botPet1Index = rand() % 4;
                        botPet2Index = rand() % 4;
                        while (botPet2Index == botPet1Index) {
                            botPet2Index = rand() % 4;
                        }

                        random = botPet1Index;
                        currentBotTurn = 0;
                    }
                }

                if (GuildVGuildMode) {
                    
                    pet1 = currentGuild->getPet(0);
                    currentScreen = Screen::FIGHT;
                }
            }

            // TEXT INPUT HANDLING
            if (event.type == Event::TextEntered && (currentScreen == Screen::REGISTER || currentScreen == Screen::RESUME)) {
                if (event.text.unicode == 8) { // Backspace
                    if (currentInput == InputField::USERNAME && !username.empty())
                        username.pop_back();
                    else if (currentInput == InputField::PASSWORD && !password.empty())
                        password.pop_back();
                    else if (currentInput == InputField::GUILD && !guildName.empty())
                        guildName.pop_back();
                }
                else if (event.text.unicode == '\r' || event.text.unicode == '\n') { // Enter
                    // Handle form submission on Enter key
                    if (currentScreen == Screen::REGISTER) {
                        if (!username.empty() && !password.empty() && !guildName.empty()) {
                            gameManager->registerPlayer(username, password, guildName);
                            currentScreen = Screen::GAME;
                            message = "";
                        } else {
                            message = "Please fill in all fields!";
                        }
                    } else if (currentScreen == Screen::RESUME) {
                        if (!username.empty() && !password.empty()) {
                            if (gameManager->resumePlayer(username, password)) {
                                currentScreen = Screen::GAME;
                                message = "";
                            } else {
                                message = "Invalid username or password!";
                            }
                        } else {
                            message = "Please enter username and password!";
                        }
                    }
                }
                else if (event.text.unicode >= 32 && event.text.unicode < 128) {
                    char typed = static_cast<char>(event.text.unicode);
                    if (currentInput == InputField::USERNAME)
                        username += typed;
                    else if (currentInput == InputField::PASSWORD)
                        password += typed;
                    else if (currentInput == InputField::GUILD)
                        guildName += typed;
                }
            }

            if (event.type == Event::KeyPressed && currentScreen == Screen::FIGHT && gameStarted) {
                if (event.key.code == Keyboard::Space && !BattlegameOver) {
                    if (currentPlayerShootCooldown <= 0) {
                        // Shoot bullet
                        for (int i = 0; i < MAX_ATTACKS; i++) {
                             width = petBattleSprites[petindex].getGlobalBounds().width;
                             height = petBattleSprites[petindex].getGlobalBounds().height;
                            
                            if (!attacks[i].active) {
                                attacks[i].active = true;
                                bounds = petBattleSprites[petindex].getGlobalBounds();

                                attacks[i].shape.setPosition(
                                    bounds.left + bounds.width,                                 // Right edge (x)
                                    bounds.top + bounds.height / 2 - attacks[i].shape.getSize().y / 2  // Vertical center (y)
                                );
                                
                                // Straight bullet
                                attacks[i].directionX = 1.0f;
                                attacks[i].directionY = 0.0f;
                                
                                break;
                            }
                        }
                        
                        currentPlayerShootCooldown = playerHasRapidFire ? playerShootCooldown * 0.5f : playerShootCooldown;
                    }
                }

                // Health potion
                if (event.key.code == Keyboard::H && !BattlegameOver) {
                    if (Hcount > 0) {
                        if(pet1->checkHealth()) {
                            Hcount--;
                            pet1->increaseHealth(30);
                        } else {
                            ItemMessage.setString("Health is Full");
                            ItemMessageTimer.restart();
                            ItemShowMessage = true;
                        }
                    } else {
                        ItemMessage.setString("No more Health Potion");
                        ItemMessageTimer.restart();
                        ItemShowMessage = true;
                    }
                }

                //Mana Potion
                if (event.key.code == Keyboard::J && !BattlegameOver) {
                    if (Mcount > 0) {
                        if(pet1->checkMana()) {
                            Mcount--;
                            pet1->increaseMana(30);
                        } else {
                            ItemMessage.setString("Mana is Full");
                            ItemMessageTimer.restart();
                            ItemShowMessage = true;
                        }
                    } else {
                        ItemMessage.setString("No more Mana Potion");
                        ItemMessageTimer.restart();
                        ItemShowMessage = true;
                    }
                }

                //Buff item
                if (event.key.code == Keyboard::K && !BattlegameOver) {
                    if (BuffitemDuratiion <= 0) {
                        if (Bcount > 0) {
                            Bcount--;
                            BuffitemDuratiion = 7.0f;
                            PlayerUsesBuffitem = true;
                            pet1->increaseSpeed(30);
                        } else {
                            ItemMessage.setString("No more Buff Potion");
                            ItemMessageTimer.restart();
                            ItemShowMessage = true;
                        }
                    } else {
                        ItemMessage.setString("Buff Potion is Active");
                        ItemMessageTimer.restart();
                        ItemShowMessage = true;
                    }
                }

                //Sheild Potion
                if (event.key.code == Keyboard::L && !BattlegameOver) {
                    if (SheildPotionDuratiion <= 0) {
                        if (Scount > 0) {
                            Scount--;
                            SheildPotionDuratiion = 7.0f;
                            pet1->applyShield(3);
                        } else {
                            ItemMessage.setString("No more Shield Potion");
                            ItemMessageTimer.restart();
                            ItemShowMessage = true;
                        }
                    } else {
                        ItemMessage.setString("Shield Potion is Active");
                        ItemMessageTimer.restart();
                        ItemShowMessage = true;
                    }
                }

                //To change pet
                if (event.key.code == Keyboard::E && !BattlegameOver && TwoVTwoMode) {

                    if (currentPetTurn == 0) {
                        pet1 = currentGuild->getPet(pet2index); // switch to second pet
                        currentPetTurn = 1;
                        petindex = pet2index;
                    } else {
                        pet1 = currentGuild->getPet(pet1index); // switch to first pet
                        currentPetTurn = 0;
                        petindex = pet1index;
                    }

                }

                //To change Pet FOr the GuilD V Guild
                if (event.key.code == Keyboard::E && !BattlegameOver && GuildVGuildMode) {
                    int newIndex;
                    
                    do {
                        newIndex = rand() % 4; // Generates 0, 1, 2, or 3
                    } while (newIndex == petindex); // Repeat if same as previous

                    petindex = newIndex;
                    pet1 = currentGuild->getPet(petindex);
                }


            }
        }


        if (startTraining && !TraininggameOver) {
            // Handle player movement 
            if (Keyboard::isKeyPressed(Keyboard::Left) && petGameSprites[petCount].getPosition().x > 580) {
                petGameSprites[petCount].move(-7.f, 0);
            }
            if (Keyboard::isKeyPressed(Keyboard::Right) && petGameSprites[petCount].getPosition().x + petGameSprites[petCount].getGlobalBounds().width < 1200) {
                petGameSprites[petCount].move(7.f, 0);
            }
        
            // Spawn boxes every 1 second inside the square
            if (boxSpawnClock.getElapsedTime().asSeconds() > 1.f) {
                for (int boxIdx = 0; boxIdx < 20; ++boxIdx) {
                    if (!boxActive[boxIdx]) {
                        float xPos = static_cast<float>(550 + rand() % (int)(650 - 40));  // x between 550 and 1110
                        boxes[boxIdx].setTexture(rockTexture);
                        boxes[boxIdx].setPosition(xPos, 110.f);
                        boxActive[boxIdx] = true;
                        boxSpawnClock.restart();
                        break;
                    }
                }
            }
            
        
            // Move boxes and check collisions
            for (int boxIdx = 0; boxIdx < 20; ++boxIdx) {
                if (boxActive[boxIdx]) {
                    boxes[boxIdx].move(0, 3.f);
        
                    // Check collision with selected pet
                    if (petGameSprites[petCount].getGlobalBounds().intersects(boxes[boxIdx].getGlobalBounds())) {
                        TraininggameOver = true;
                        setscore = true;
                        petSelected = false;
                        startTraining = false;

                        // Clear all active boxes
                        for (int i = 0; i < 20; ++i) {
                            boxActive[i] = false;
                            boxes[i].setPosition(-100.f, -100.f);  // Move off-screen
                        }
                    }
        
                    // Deactivate if out of view
                    if (boxes[boxIdx].getPosition().y > 600) {
                        boxActive[boxIdx] = false;
                    }
                }
            }

            if (scoreClock.getElapsedTime().asSeconds() >= 1.f) {
                score += 1;
                scoreClock.restart();
            }
        }

        // Restart the game if 'R' is pressed and game is over
        if (TraininggameOver && Keyboard::isKeyPressed(Keyboard::R)) {
            TraininggameOver = false;
            petSelected = true;
            score = 0;
            setscore = true;

            // Reset pet position
            petGameSprites[petCount].setPosition(600.f, 580.f);  // Adjust as needed

            // Deactivate and reset all boxes
            for (int i = 0; i < 20; ++i) {
                boxActive[i] = false;
                boxes[i].setPosition(-100.f, -100.f);
            }

            // Reset clocks
            boxSpawnClock.restart();
            scoreClock.restart();
        }
        

        // game logic
        if (!BattlegameOver && currentScreen == Screen::FIGHT) {
            // Update cooldown timers
            if (currentPlayerShootCooldown > 0) {
                currentPlayerShootCooldown -= dt;
            }

            //Bot Change for 2v2
            if(TwoVTwoMode && Bot2v2Changetimer.getElapsedTime().asSeconds() > Bot2v2ChangeDuration) {

                if (currentBotTurn == 0) {
                    random = botPet2Index;
                    currentBotTurn = 1;
                } else {
                    random = botPet1Index;
                    currentBotTurn = 0;
                }
                Bot2v2Changetimer.restart();
            }
            
            // Bot Change for Guild V GUild
            if(GuildVGuildMode && BotChangetimer.getElapsedTime().asSeconds() > BotChangeDuration ) {

                int newRandom;
                do {
                    newRandom = rand() % 4; 
                } while (newRandom == random);
                random = newRandom;
                BotChangetimer.restart();
            }

            // Update power-up duration
            if (playerHasSpeedBoost || playerHasRapidFire || playerHasShield) {
                powerUpDuration -= dt;
                
                if (powerUpDuration <= 0) {
                    playerHasSpeedBoost = false;
                    playerHasRapidFire = false;
                    playerHasShield = false;
                    powerUpText.setString("");
                } else {
                    string activePowerUp = "";
                    if (playerHasSpeedBoost) activePowerUp = "Speed Boost";
                    else if (playerHasRapidFire) activePowerUp = "Rapid Fire";
                    else if (playerHasShield) activePowerUp = "Shield";
                    
                    powerUpText.setString(activePowerUp + ": " + to_string(static_cast<int>(powerUpDuration)) + "s");
                }
            }
            
            // Updating the power-up spawn timer
            powerUpSpawnTimer -= dt;
            if (powerUpSpawnTimer <= 0 && !powerUp.active) {
                // Spawning power-up
                // Don't spawn if player already has a power-up
                if (!(playerHasSpeedBoost || playerHasRapidFire || playerHasShield)) {
                    powerUp.active = true;
                    powerUp.type = rand() % 2;  // Random power-up type
                    
                    // Set color based on type
                    switch (powerUp.type) {
                        case SPEED_BOOST:
                            powerUp.shape.setFillColor(Color::Yellow);
                            break;
                        case RAPID_FIRE:
                            powerUp.shape.setFillColor(Color::Magenta);
                            break;
                        
                    }
                    
                    // Place randomly on the map, but not too close to either player or enemy
                    float x, y;
                    do {
                        x = static_cast<float>(rand() % (WINDOW_WIDTH - 30));
                        y = static_cast<float>(rand() % (WINDOW_HEIGHT - 30));
                    } while (
                        (abs(x - petBattleSprites[petindex].getPosition().x) < 100 && abs(y - petBattleSprites[petindex].getPosition().y) < 100) ||
                        (abs(x - botPetBattleSprites[random].getPosition().x) < 100 && abs(y - botPetBattleSprites[random].getPosition().y) < 100)
                    );
                    
                    powerUp.shape.setPosition(x, y);
                    powerUp.lifetime = 10.0f;  // Power-up disappears after 10 seconds
                }
                
                powerUpSpawnTimer = 10.0f + (rand() % 10);  // Random time between 10-20 seconds
            }
            
            // Update power-up lifetime
            if (powerUp.active) {
                powerUp.lifetime -= dt;
                if (powerUp.lifetime <= 0) {
                    powerUp.active = false;
                }
            }
            
            // Player movement
            float currentPlayerSpeed;

            //Checking if Player has Buffitem
            if(BuffitemDuratiion > 0 ) {
                BuffitemDuratiion -= dt;    
                currentPlayerSpeed = PLAYER_SPEED * 2.5f;
            } else {
                currentPlayerSpeed = playerHasSpeedBoost ? PLAYER_SPEED * 1.5f : PLAYER_SPEED;
            }
            
            if (Keyboard::isKeyPressed(Keyboard::W) && petBattleSprites[petindex].getPosition().y > 0) {
                petBattleSprites[petindex].move(0, -currentPlayerSpeed);
            }
            if (Keyboard::isKeyPressed(Keyboard::S) && petBattleSprites[petindex].getPosition().y < WINDOW_HEIGHT - petBattleSprites[petindex].getGlobalBounds().height) {
                petBattleSprites[petindex].move(0, currentPlayerSpeed);
            }
            if (Keyboard::isKeyPressed(Keyboard::A) && petBattleSprites[petindex].getPosition().x > 0) {
                petBattleSprites[petindex].move(-currentPlayerSpeed, 0);
            }
            if (Keyboard::isKeyPressed(Keyboard::D) && petBattleSprites[petindex].getPosition().x < WINDOW_WIDTH - petBattleSprites[petindex].getGlobalBounds().width) {
                petBattleSprites[petindex].move(currentPlayerSpeed, 0);
            }
            
            // Enemy AI
            enemyShootTimer += dt;
            if (enemyShootTimer >= ENEMY_SHOOT_COOLDOWN) {
                // Enemy shoot
                for (int i = 0; i < MAX_ENEMY_ATTACKS; i++) {
                    if (!enemyAttacks[i].active) {
                        enemyAttacks[i].active = true;
                        enemyAttacks[i].shape.setPosition(
                            botPetBattleSprites[random].getPosition().x,
                            botPetBattleSprites[random].getPosition().y + botPetBattleSprites[random].getGlobalBounds().height / 2 - enemyAttacks[i].shape.getSize().y / 2
                        );
                        
                        // Calculate direction towards player with some inaccuracy
                        float dx = petBattleSprites[petindex].getPosition().x - botPetBattleSprites[random].getPosition().x;
                        float dy = (petBattleSprites[petindex].getPosition().y + petBattleSprites[petindex].getGlobalBounds().height/2) - (botPetBattleSprites[random].getPosition().y + botPetBattleSprites[random].getGlobalBounds().height/2);
                        
                        // Add some randomness to make it more challenging but not impossible
                        dy += (rand() % 100 - 50) * 0.5f;
                        
                        // Normalize the direction
                        float length = sqrt(dx * dx + dy * dy);
                        if (length > 0) {
                            enemyAttacks[i].directionX = dx / length;
                            enemyAttacks[i].directionY = dy / length;
                        } else {
                            enemyAttacks[i].directionX = -1.0f;
                            enemyAttacks[i].directionY = 0.0f;
                        }
                        
                        break;
                    }
                }
                
                enemyShootTimer = 0.0f;
            }
            
            // Make enemy AI decision every 0.5 seconds
            if (enemyAIClock.getElapsedTime().asSeconds() >= 0.5f) {
                enemyAIClock.restart();
                
                // Enemy movement decision
                float targetX, targetY;
                
                // Check if any player bullets are close to the enemy
                bool bulletNearby = false;
                Vector2f dodgeDirection(0, 0);
                
                for (int i = 0; i < MAX_ATTACKS; i++) {
                    if (attacks[i].active) {
                        Vector2f bulletPos = attacks[i].shape.getPosition();
                        Vector2f enemyPos = botPetBattleSprites[random].getPosition();
                        
                        // Check if bullet is approaching from the left
                        if (bulletPos.x < enemyPos.x && 
                            bulletPos.x > enemyPos.x - 200 && 
                            abs(bulletPos.y - (enemyPos.y + botPetBattleSprites[random].getGlobalBounds().height/2)) < 100) {
                            
                            bulletNearby = true;
                            
                            // Decide whether to dodge up or down
                            if (rand() % 2 == 0 && enemyPos.y > 50) {
                                dodgeDirection.y = -1; // Dodge up
                            } else if (enemyPos.y < WINDOW_HEIGHT - botPetBattleSprites[random].getGlobalBounds().height - 50) {
                                dodgeDirection.y = 1;  // Dodge down
                            } else {
                                dodgeDirection.y = -1; // Default to up if at bottom
                            }
                            
                            // Sometimes dodge horizontally too
                            if (rand() % 3 == 0) {
                                if (enemyPos.x < WINDOW_WIDTH - botPetBattleSprites[random].getGlobalBounds().width- 100) {
                                    dodgeDirection.x = 1; // Move right
                                } else {
                                    dodgeDirection.x = -1; // Move left if near edge
                                }
                            }
                            
                            break;
                        }
                    }
                }
                
                if (bulletNearby && (rand() % 100) < enemyDodgeChance * 100) {
                    // Dodge the bullet
                    targetX = botPetBattleSprites[random].getPosition().x + dodgeDirection.x * ENEMY_SPEED * 10;
                    targetY = botPetBattleSprites[random].getPosition().y + dodgeDirection.y * ENEMY_SPEED * 10;
                } else {
                    // Normal behavior: follow player with some randomness
                    targetY = petBattleSprites[petindex].getPosition().y;
                    
                    // Sometimes move horizontally to be more unpredictable
                    if (rand() % 100 < 40) {
                        // Approach player horizontally
                        targetX = petBattleSprites[petindex].getPosition().x + 200 + rand() % 100;
                        
                        // But don't get too close
                        if (targetX < WINDOW_WIDTH / 4) {
                            targetX = WINDOW_WIDTH / 4;
                        }
                    } else {
                        // Stay at current x position with some randomness
                        targetX = botPetBattleSprites[random].getPosition().x + (rand() % 200 - 100);
                    }
                }
                
                // Ensure enemy stays within bounds
                if (targetX < WINDOW_WIDTH / 4) targetX = WINDOW_WIDTH / 4;
                if (targetX > WINDOW_WIDTH - botPetBattleSprites[random].getGlobalBounds().width) targetX = WINDOW_WIDTH - botPetBattleSprites[random].getGlobalBounds().width;
                if (targetY < 0) targetY = 0;
                if (targetY > WINDOW_HEIGHT - botPetBattleSprites[random].getGlobalBounds().height) targetY = WINDOW_HEIGHT - botPetBattleSprites[random].getGlobalBounds().height;
                
                // Set target position for smooth movement
                enemyTargetX = targetX;
                enemyTargetY = targetY;
            }
            
            // Smooth movement towards target position
            float enemyX = botPetBattleSprites[random].getPosition().x;
            float enemyY = botPetBattleSprites[random].getPosition().y;
            
            if (abs(enemyX - enemyTargetX) > 5.0f) {
                if (enemyX < enemyTargetX) {
                    botPetBattleSprites[random].move(ENEMY_SPEED, 0);
                } else {
                    botPetBattleSprites[random].move(-ENEMY_SPEED, 0);
                }
            }
            
            if (abs(enemyY - enemyTargetY) > 5.0f) {
                if (enemyY < enemyTargetY) {
                    botPetBattleSprites[random].move(0, ENEMY_SPEED);
                } else {
                    botPetBattleSprites[random].move(0, -ENEMY_SPEED);
                }
            }
            
            // Update bullets
            for (int i = 0; i < MAX_ATTACKS; i++) {
                if (attacks[i].active) {
                    attacks[i].shape.move(
                        attacks[i].directionX * BULLET_SPEED,
                        attacks[i].directionY * BULLET_SPEED
                    );
                    
                    // Deactivate bullets that are out of bounds
                    if (attacks[i].shape.getPosition().x > WINDOW_WIDTH ||
                        attacks[i].shape.getPosition().x < 0 ||
                        attacks[i].shape.getPosition().y > WINDOW_HEIGHT ||
                        attacks[i].shape.getPosition().y < 0) {
                        attacks[i].active = false;
                    }
                }
            }
            
            // Update enemy bullets
            for (int i = 0; i < MAX_ENEMY_ATTACKS; i++) {
                if (enemyAttacks[i].active) {
                    enemyAttacks[i].shape.move(
                        enemyAttacks[i].directionX * BULLET_SPEED,
                        enemyAttacks[i].directionY * BULLET_SPEED
                    );
                    
                    // Deactivate bullets that are out of bounds
                    if (enemyAttacks[i].shape.getPosition().x < 0 ||
                        enemyAttacks[i].shape.getPosition().x > WINDOW_WIDTH ||
                        enemyAttacks[i].shape.getPosition().y < 0 ||
                        enemyAttacks[i].shape.getPosition().y > WINDOW_HEIGHT) {
                        enemyAttacks[i].active = false;
                    }
                }
            }
            
            // Check collisions - player bullets hitting enemy
            for (int i = 0; i < MAX_ATTACKS; i++) {
                if (attacks[i].active) {
                    if (attacks[i].shape.getGlobalBounds().intersects(botPetBattleSprites[random].getGlobalBounds())) {
                        attacks[i].active = false;
                        playerScore++;
                        // Update score text
                        BattlescoreText.setString("Points: " + to_string(playerScore) + " | To " + to_string(SCORE_TO_WIN) + " wins!");
                    
                        // Make enemy faster as player scores
                        enemyDodgeChance = min(0.9f, 0.7f + playerScore * 0.02f);
                        
                        if (playerScore >= SCORE_TO_WIN) {
                            BattlegameOver = true;
                            playerWon = true;

                        }
                    }
                }
            }
            
            // Check enemy bullets hitting player
            for (int i = 0; i < MAX_ENEMY_ATTACKS; i++) {
                if (enemyAttacks[i].active) {
                    if (enemyAttacks[i].shape.getGlobalBounds().intersects(petBattleSprites[petindex].getGlobalBounds())) {
                        enemyAttacks[i].active = false;

                        if(SheildPotionDuratiion <= 0) {
                                pet1->DamageDealt(10);
                        }
                        int HealthPet = pet1->getHealth();
                        if (HealthPet <= 0) {
                            BattlegameOver = true;
                            botWon = true;
                        }    
                        // Update score text
                        BattlescoreText.setString("Points: " + to_string(playerScore) + " | To " + to_string(SCORE_TO_WIN) + " wins!");
                     }
                }
            }
            
            SheildPotionDuratiion -= dt;

            // Check power-up collision
            if (powerUp.active) {
                if (petBattleSprites[petindex].getGlobalBounds().intersects(powerUp.shape.getGlobalBounds())) {
                    // Activate power-up
                    powerUpDuration = 7.0f;  // Power-ups last for 7 seconds
                    
                    switch (powerUp.type) {
                        case SPEED_BOOST:
                            playerHasSpeedBoost = true;
                            playerHasRapidFire = false;
                            playerHasShield = false;
                            powerUpText.setString("Speed Boost: 7s");
                            powerUpText.setFillColor(sf::Color::Yellow);
                            break;
                        case RAPID_FIRE:
                            playerHasRapidFire = true;
                            playerHasSpeedBoost = false;
                            playerHasShield = false;
                            powerUpText.setString("Rapid Fire: 7s");
                            powerUpText.setFillColor(sf::Color::Magenta);
                            break;
                        default:
                            break;
                    }
                    
                    powerUp.active = false;

                }
            }
        }


        // RENDERING
        window.clear();
        window.draw(background);

        // START SCREEN
        if (currentScreen == Screen::START) {
            window.draw(startButton);
            window.draw(startText);
        }
        
        // OPTIONS SCREEN
        else if (currentScreen == Screen::OPTIONS) {
            window.draw(resumeButton);
            window.draw(resumeText);
            window.draw(registerButton);
            window.draw(registerText);
        }
        
        // RESUME/REGISTER SCREENS
        else if (currentScreen == Screen::RESUME || currentScreen == Screen::REGISTER) {
            // Username label and box
            window.draw(usernameLabelText);
            window.draw(usernameBox);
            usernameText.setString(username);
            usernameText.setPosition(usernameBox.getPosition().x + 10, usernameBox.getPosition().y + 10);
            window.draw(usernameText);

            // Password label and box (masked)
            window.draw(passwordLabelText);
            window.draw(passwordBox);
            string maskedPass(password.length(), '*');
            passwordText.setString(maskedPass);
            passwordText.setPosition(passwordBox.getPosition().x + 10, passwordBox.getPosition().y + 10);
            window.draw(passwordText);

            // Guild box only in Register screen
            if (currentScreen == Screen::REGISTER) {
                window.draw(guildLabelText);
                window.draw(guildBox);
                guildText.setString(guildName);
                guildText.setPosition(guildBox.getPosition().x + 10, guildBox.getPosition().y + 10);
                window.draw(guildText);
            }
            
            // Submit button
            window.draw(submitButton);
            window.draw(submitText);
            
            // Back button
            window.draw(backButton);
            window.draw(backText);
            
            // Display message if any
            if (!message.empty()) {
                messageText.setString(message);
                window.draw(messageText);
            }
        }
        
        // GAME SCREEN
        else if (currentScreen == Screen::GAME) {
            currentPlayer = gameManager->getPlayer();
            if (currentPlayer) {
                // Display player info
                int currency = currentPlayer->getCurrency();

                string info = "Name: " + currentPlayer->getUsername() + " , Guild: "+ currentPlayer->getguilname() +" , Coins: " + to_string(currency);

                Hcount = 0;
                Mcount = 0;
                Bcount = 0;
                Scount = 0;

                Item** playerInventory = currentPlayer->getInventory();
                for (int i = 0; i < currentPlayer->getInventorySize(); i++) {
                    Item* currentItem = currentPlayer->getInventoryItem(i);
                    if (currentItem != nullptr) {

                        if(currentItem->getName() == "Healing Potion") {
                            Hcount = currentItem->getCount();
   
                        }else if (currentItem->getName() == "Shield" ) {
                            Scount = currentItem->getCount();

                        
                        }else if (currentItem->getName() == "Mana Potion") {
                            Mcount = currentItem->getCount();
   

                        }else if(currentItem->getName() == "Buff Item") {
                            Bcount = currentItem->getCount();

                        }

                    }

                }

                // Create text objects for counts (if not already defined as class members)
                Text healthText, manaText, buffText, shieldText;
                
                // Set up the count texts
                healthText.setFont(font); // Assuming font is defined elsewhere
                healthText.setCharacterSize(14);
                healthText.setFillColor(Color::White);
                healthText.setString("x" + to_string(Hcount));
                
                manaText.setFont(font);
                manaText.setCharacterSize(14);
                manaText.setFillColor(Color::White);
                manaText.setString("x" + to_string(Mcount));
                
                buffText.setFont(font);
                buffText.setCharacterSize(14);
                buffText.setFillColor(Color::White);
                buffText.setString("x" + to_string(Bcount));
                
                shieldText.setFont(font);
                shieldText.setCharacterSize(14);
                shieldText.setFillColor(Color::White);
                shieldText.setString("x" + to_string(Scount));
                
                // Draw mini sprites and their count texts
                for (int i = 0; i < 4; ++i) {
                    window.draw(miniItemSprites[i]);
                }

                for (int i = 0; i < 4; ++i) {
                    window.draw(petSprites[i]);
                }
                
                // Position and draw the count texts next to their sprites
                healthText.setPosition(miniItemSprites[0].getPosition().x + miniItemSprites[0].getGlobalBounds().width - 12, 
                                    miniItemSprites[0].getPosition().y);
                window.draw(healthText);
                
                manaText.setPosition(miniItemSprites[1].getPosition().x + miniItemSprites[1].getGlobalBounds().width - 15, 
                                    miniItemSprites[1].getPosition().y);
                window.draw(manaText);
                
                buffText.setPosition(miniItemSprites[2].getPosition().x + miniItemSprites[2].getGlobalBounds().width - 15, 
                                    miniItemSprites[2].getPosition().y);
                window.draw(buffText);
                
                shieldText.setPosition(miniItemSprites[3].getPosition().x + miniItemSprites[3].getGlobalBounds().width - 20, 
                                    miniItemSprites[3].getPosition().y);
                window.draw(shieldText);

                gameScreenText.setString(info);
                gameScreenText.setCharacterSize(16);
                gameScreenText.setOrigin(0, 0);
                gameScreenText.setPosition(10, 10);
                window.draw(gameScreenText);
        
                // Draw game buttons
                window.draw(battleButton);   window.draw(battleText);
                window.draw(trainingButton); window.draw(trainingText);
                window.draw(shopButton);     window.draw(shopText);
                window.draw(exitButton);     window.draw(exitText);
            }
        }
        
        // SHOP SCREEN
        else if (currentScreen == Screen::SHOP) {
            window.draw(shopScreenText);
            window.draw(backButton);
            window.draw(backText);

            for (int i = 0; i < 4; ++i) {
                window.draw(miniItemSprites[i]);
            }
            
            // Draw all items
            for (int i = 0; i < 4; ++i) {
                window.draw(itemSprites[i]);
                window.draw(itemNames[i]);
                window.draw(itemCosts[i]);
            }
            
            // Draw player info at top
            if (currentPlayer) {
                int currency = currentPlayer->getCurrency();
                string info = "Name: " + currentPlayer->getUsername() + " , Guild: "+ currentPlayer->getguilname() +" , Coins: " + to_string(currency);
                gameScreenText.setString(info);
                gameScreenText.setCharacterSize(16);
                gameScreenText.setPosition(10, 10);
                window.draw(gameScreenText);

                Hcount = 0;
                Mcount = 0;
                Bcount = 0;
                Scount = 0;

                Item** playerInventory = currentPlayer->getInventory();
                for (int i = 0; i < currentPlayer->getInventorySize(); i++) {
                    Item* currentItem = currentPlayer->getInventoryItem(i);
                    if (currentItem != nullptr) {

                        if(currentItem->getName() == "Healing Potion") {
                            Hcount = currentItem->getCount();
    
                        }else if (currentItem->getName() == "Shield" ) {
                            Scount = currentItem->getCount();
        
                        
                        }else if (currentItem->getName() == "Mana Potion" ) {
                            Mcount = currentItem->getCount();
          

                        }else if(currentItem->getName() == "Buff Item" ) {
                            Bcount = currentItem->getCount();
            
                        }

                    }

                }
                // Create text objects for counts (if not already defined as class members)
                Text healthText, manaText, buffText, shieldText;
                
                // Set up the count texts
                healthText.setFont(font); // Assuming font is defined elsewhere
                healthText.setCharacterSize(14);
                healthText.setFillColor(Color::White);
                healthText.setString("x" + to_string(Hcount));
                
                manaText.setFont(font);
                manaText.setCharacterSize(14);
                manaText.setFillColor(Color::White);
                manaText.setString("x" + to_string(Mcount));
                
                buffText.setFont(font);
                buffText.setCharacterSize(14);
                buffText.setFillColor(Color::White);
                buffText.setString("x" + to_string(Bcount));
                
                shieldText.setFont(font);
                shieldText.setCharacterSize(14);
                shieldText.setFillColor(Color::White);
                shieldText.setString("x" + to_string(Scount));
                
                // Draw mini sprites and their count texts
                for (int i = 0; i < 4; ++i) {
                    window.draw(miniItemSprites[i]);
                }
                
                // Position and draw the count texts next to their sprites
                healthText.setPosition(miniItemSprites[0].getPosition().x + miniItemSprites[0].getGlobalBounds().width - 12, 
                                    miniItemSprites[0].getPosition().y);
                window.draw(healthText);
                
                manaText.setPosition(miniItemSprites[1].getPosition().x + miniItemSprites[1].getGlobalBounds().width - 15, 
                                    miniItemSprites[1].getPosition().y);
                window.draw(manaText);
                
                buffText.setPosition(miniItemSprites[2].getPosition().x + miniItemSprites[2].getGlobalBounds().width - 15, 
                                    miniItemSprites[2].getPosition().y);
                window.draw(buffText);
                
                shieldText.setPosition(miniItemSprites[3].getPosition().x + miniItemSprites[3].getGlobalBounds().width - 20, 
                                    miniItemSprites[3].getPosition().y);
                window.draw(shieldText);

                gameScreenText.setString(info);
                gameScreenText.setCharacterSize(16);
                gameScreenText.setOrigin(0, 0);
                gameScreenText.setPosition(10, 10);
                window.draw(gameScreenText);
            }
            
            // Display message if any
            if (!message.empty()) {
                messageText.setString(message);
                window.draw(messageText);
            }
        }
        
        // TRAINING CAMP SCREEN
        else if (currentScreen == Screen::TRAINING_CAMP) {

            window.draw(trainingScreenText);
            window.draw(backButton);
            window.draw(backText);
            
            // Draw player info at top
            if (currentPlayer) {
                int currency = currentPlayer->getCurrency();
                string info = "Name: " + currentPlayer->getUsername() + " , Guild: "+ currentPlayer->getguilname() +" , Coins: " + to_string(currency);
                gameScreenText.setString(info);
                gameScreenText.setCharacterSize(16);
                gameScreenText.setPosition(10, 10);
                window.draw(gameScreenText);
            }

            for (int i = 0; i < 4; ++i) {
                window.draw(petMiniSprites[i]);
            }

            if (selectedPet)
            {
                string name = selectedPet->getName();
                maxhealth = selectedPet->getMaxHealth();
                maxattack = selectedPet->getMaxAttack();
                maxdefense = selectedPet->getMaxDefense();
                maxMana = selectedPet->getMaxMana();
                maxspeed = selectedPet->getMaxSpeed();
                int level = selectedPet->getLevel();

                if(score > 0 && TraininggameOver && setscore) {
                     selectedPet->boostMaxStats(score);
                }

                Text petStatsText;
                petStatsText.setFont(font); // Make sure to use your game's font
                petStatsText.setCharacterSize(20);
                petStatsText.setFillColor(Color::White);
                
                string stats = name + " Stats:\n";

                petStatsText.setString(stats);
                petStatsText.setPosition(250,225);
                window.draw(petStatsText);

                // Display pet stats
                Text petStats1Text;
                petStats1Text.setFont(font); // Make sure to use your game's font
                petStats1Text.setCharacterSize(18);
                petStats1Text.setFillColor(Color::White);
                
                string stats1 = "Level: " + to_string(level) + "\n";
                stats1 += "Health: " + to_string(maxhealth) + "\n";
                stats1 += "Attack: " + to_string(maxattack) + "\n";
                stats1 += "Defense: " + to_string(maxdefense) + "\n";
                stats1 += "Mana: " + to_string(maxMana) + "\n";
                stats1 += "Speed: " + to_string(maxspeed) + "\n";

                petStats1Text.setString(stats1);
                petStats1Text.setPosition(320, 250); // Adjust position as needed
                window.draw(petStats1Text);

            }

            window.draw(TrainigbackgroundSprite); 
            window.draw(gameSquare);

            for (int i = 0; i < 20; ++i) {
                if (boxActive[i]) {
                    window.draw(boxes[i]);
                }
            }
            
            // Draw the selected pet
            if (petSelected) {
                window.draw(petGameSprites[petCount]);
                window.draw(StartTrainingButton);
                window.draw(StartTrainingButtonText);
            }

            // Draw the score
            TrainingscoreText.setString("Score: " + to_string(score));
            TrainingscoreText.setPosition(1000.f,60.f);
            window.draw(TrainingscoreText);

            if (TraininggameOver) {
                Text gameOverText;
                gameOverText.setFont(font);  // Make sure 'font' is loaded
                gameOverText.setString("Training Over! Press R to Train Again");
                gameOverText.setCharacterSize(20);
                gameOverText.setFillColor(Color::White);
                gameOverText.setPosition(600.f, 300.f);  // Adjust for your layout
                window.draw(gameOverText);
                startTraining = false;
                setscore = false;
            }           

        }
        
        // BATTLE SCREEN
        else if (currentScreen == Screen::BATTLE) {
            window.draw(battleScreenText);
            window.draw(battleDescription);
            window.draw(backButton);
            window.draw(backText);
            
            // Draw player info at top
            if (currentPlayer) {
                int currency = currentPlayer->getCurrency();
                string info = "Name: " + currentPlayer->getUsername() + " , Guild: "+ currentPlayer->getguilname() +" , Coins: " + to_string(currency);
                gameScreenText.setString(info);
                gameScreenText.setCharacterSize(16);
                gameScreenText.setPosition(10, 10);
                window.draw(gameScreenText);
            }

            window.draw(One_V_OneButton);
            window.draw(One_V_OneButtonText);
            window.draw(Two_V_TwoButton);
            window.draw(Two_V_TwoButtonText);
            window.draw(Guild_V_GuildButton);
            window.draw(Guild_V_GuildButtonText);

        }

        else if (currentScreen == Screen::ONE_V_ONE) {


            for (int i = 0; i < 4; ++i) {
                window.draw(petSelectionSprites[i]);
            }
            window.draw(DragonSelectButton);
            window.draw(DragonSelectButtonText);
            window.draw(UnicornSelectButton);
            window.draw(UnicornSelectButtonText);
            window.draw(GriffinSelectButton);
            window.draw(GriffinSelectButtonText);
            window.draw(PhoenixSelectButton);
            window.draw(PhoenixSelectButtonText);    
            window.draw(petSelectionText);
            window.draw(backButton);
            window.draw(backText);

        } 

        else if (currentScreen == Screen::TWO_V_TWO) {

            for (int i = 0; i < 4; ++i) {
                window.draw(petSelectionSprites[i]);
            }
            
            if (warningClock.getElapsedTime().asSeconds() < 2.0f) {
                    window.draw(warningText);
            }

            window.draw(DragonSelectButton);
            window.draw(DragonSelectButtonText);
            window.draw(UnicornSelectButton);
            window.draw(UnicornSelectButtonText);
            window.draw(GriffinSelectButton);
            window.draw(GriffinSelectButtonText);
            window.draw(PhoenixSelectButton);
            window.draw(PhoenixSelectButtonText);
            window.draw(petSelectionText);
            window.draw(backButton);
            window.draw(backText);


        }

        else if (currentScreen == Screen::FIGHT) {

            window.draw(arenaSprites[currentArenaIndex]);

            if(OneVOneMode) {

                gameStarted = true;

                string battlePetName = pet1->getName();
                
                Text battlepetStatsText;
                battlepetStatsText.setFont(font); // Make sure to use your game's font
                battlepetStatsText.setCharacterSize(20);
                battlepetStatsText.setFillColor(Color::Green);
                int PetHealth = pet1->getHealth();
                int PetMana = pet1->getMana();
                
                string stats = battlePetName + " Health:\n" + to_string(PetHealth) + "\n" + " Mana:\n" + to_string(PetMana);

                battlepetStatsText.setString(stats);
                battlepetStatsText.setPosition(20, 40);
                window.draw(battlepetStatsText);

                Item** playerInventory = currentPlayer->getInventory();
                for (int i = 0; i < currentPlayer->getInventorySize(); i++) {
                    Item* currentItem = currentPlayer->getInventoryItem(i);
                    if (currentItem != nullptr) {

                        if(currentItem->getName() == "Healing Potion") {
                            currentItem->setCount(Hcount);
   
                        }else if (currentItem->getName() == "Shield" ) {
                            currentItem->setCount(Scount);

                        
                        }else if (currentItem->getName() == "Mana Potion") {
                            currentItem->setCount(Mcount);
   

                        }else if(currentItem->getName() == "Buff Item") {
                            currentItem->setCount(Bcount);

                        }

                    }

                }

                // Create text objects for counts (if not already defined as class members)
                Text healthText, manaText, buffText, shieldText;
                
                // Set up the count texts
                healthText.setFont(font); // Assuming font is defined elsewhere
                healthText.setCharacterSize(14);
                healthText.setFillColor(Color::White);
                healthText.setString("x" + to_string(Hcount));
                
                manaText.setFont(font);
                manaText.setCharacterSize(14);
                manaText.setFillColor(Color::White);
                manaText.setString("x" + to_string(Mcount));
                
                buffText.setFont(font);
                buffText.setCharacterSize(14);
                buffText.setFillColor(Color::White);
                buffText.setString("x" + to_string(Bcount));
                
                shieldText.setFont(font);
                shieldText.setCharacterSize(14);
                shieldText.setFillColor(Color::White);
                shieldText.setString("x" + to_string(Scount));

                // Position and draw the count texts next to their sprites
                healthText.setPosition(miniItemSprites[0].getPosition().x + miniItemSprites[0].getGlobalBounds().width - 12, 
                                    miniItemSprites[0].getPosition().y);
                window.draw(healthText);
                
                manaText.setPosition(miniItemSprites[1].getPosition().x + miniItemSprites[1].getGlobalBounds().width - 15, 
                                    miniItemSprites[1].getPosition().y);
                window.draw(manaText);
                
                buffText.setPosition(miniItemSprites[2].getPosition().x + miniItemSprites[2].getGlobalBounds().width - 15, 
                                    miniItemSprites[2].getPosition().y);
                window.draw(buffText);
                
                shieldText.setPosition(miniItemSprites[3].getPosition().x + miniItemSprites[3].getGlobalBounds().width - 20, 
                                    miniItemSprites[3].getPosition().y);
                window.draw(shieldText);
                
                // Draw mini sprites and their count texts
                for (int i = 0; i < 4; ++i) {
                    window.draw(miniItemSprites[i]);
                }

                if (ItemShowMessage) {
                    if (ItemMessageTimer.getElapsedTime().asSeconds() < ItemMessageDuration) {
                        window.draw(ItemMessage);
                    } else {
                        ItemShowMessage = false;
                    }
                }

                for (int i = 0; i < 20; ++i) {
                    if (boxActive[i]) {
                        window.draw(boxes[i]);
                    }
                }

                
                if (powerUp.active) {
                    window.draw(powerUp.shape);

                }

                window.draw(petBattleSprites[petindex]);
                window.draw(botPetBattleSprites[random]);

                for (int i = 0; i < MAX_ATTACKS; i++) {
                    if (attacks[i].active) {
                        window.draw(attacks[i].shape);
                    }
                }
                
                // Draw enemy bullets
                for (int i = 0; i < MAX_ENEMY_ATTACKS; i++) {
                    if (enemyAttacks[i].active) {
                        window.draw(enemyAttacks[i].shape);
                    }
                }
                
                // Draw score and power-up text
                window.draw(BattlescoreText);
                if (!powerUpText.getString().isEmpty()) {
                    window.draw(powerUpText);
                }
                
                if (playerWon ) {
                    GameOverMssgText.setString("You Win!!!\n You got 500 Coins");
                    GameOverMssgText.setFillColor(Color::Green);
                    currentPlayer->addCurrency(500);
                } 

                if (botWon) {
                    GameOverMssgText.setString("You Lost!!!");
                    GameOverMssgText.setFillColor(Color::Red);
                }


                
                
                // Draw game over text if game is over
                if (BattlegameOver) {
                    // Reset game
                    petBattleSprites[petindex].setPosition(100.0f, 720 / 2 - 25.0f);
                    botPetBattleSprites[random].setPosition(1280 - 150.0f, 720 / 2 - 25.0f);
                    
                    // Reset bullets
                    for (int i = 0; i < MAX_ATTACKS; i++) {
                        attacks[i].active = false;
                    }
 
                    for (int i = 0; i < MAX_ENEMY_ATTACKS; i++) {
                        enemyAttacks[i].active = false;
                    }
                    
                    // Reset power-ups
                    powerUp.active = false;
                    playerHasSpeedBoost = false;
                    playerHasRapidFire = false;
                    playerHasShield = false;
                    powerUpText.setString("");
                    powerUpSpawnTimer = 5.0f;
                    
                    pet1->RestoreHealth();
                    pet1->RestoreMana();
                    // Reset enemy AI
                    enemyDodgeChance = 0.7f;
                    
                    playerScore = 0;
                    BattlescoreText.setString("Points: " + to_string(playerScore) + " | To " + to_string(SCORE_TO_WIN) + " wins!");
                    
                    Clock tempClock;

                    // Blocking display loop for 3 seconds
                    while (tempClock.getElapsedTime().asSeconds() < 3.0f) {
                        window.draw(GameOverMssgText);
                        window.display();
                    }
                    
                    BattlegameOver = false;
                    currentScreen = Screen::GAME;
                    
                    botWon = false;
                    playerWon = false;
                    OneVOneMode = false;
                }

            } else if (GuildVGuildMode) {

                gameStarted = true;

                string battlePetName = pet1->getName();
                
                Text battlepetStatsText;
                battlepetStatsText.setFont(font); // Make sure to use your game's font
                battlepetStatsText.setCharacterSize(20);
                battlepetStatsText.setFillColor(Color::Green);
                int PetHealth = pet1->getHealth();
                int PetMana = pet1->getMana();
                
                string stats = battlePetName + " Health:\n" + to_string(PetHealth) + "\n" + " Mana:\n" + to_string(PetMana);

                battlepetStatsText.setString(stats);
                battlepetStatsText.setPosition(20, 40);
                window.draw(battlepetStatsText);

                Item** playerInventory = currentPlayer->getInventory();
                for (int i = 0; i < currentPlayer->getInventorySize(); i++) {
                    Item* currentItem = currentPlayer->getInventoryItem(i);
                    if (currentItem != nullptr) {

                        if(currentItem->getName() == "Healing Potion") {
                            currentItem->setCount(Hcount);
   
                        }else if (currentItem->getName() == "Shield" ) {
                            currentItem->setCount(Scount);

                        
                        }else if (currentItem->getName() == "Mana Potion") {
                            currentItem->setCount(Mcount);
   

                        }else if(currentItem->getName() == "Buff Item") {
                            currentItem->setCount(Bcount);

                        }

                    }

                }

                // Create text objects for counts (if not already defined as class members)
                Text healthText, manaText, buffText, shieldText;
                
                // Set up the count texts
                healthText.setFont(font); // Assuming font is defined elsewhere
                healthText.setCharacterSize(14);
                healthText.setFillColor(Color::White);
                healthText.setString("x" + to_string(Hcount));
                
                manaText.setFont(font);
                manaText.setCharacterSize(14);
                manaText.setFillColor(Color::White);
                manaText.setString("x" + to_string(Mcount));
                
                buffText.setFont(font);
                buffText.setCharacterSize(14);
                buffText.setFillColor(Color::White);
                buffText.setString("x" + to_string(Bcount));
                
                shieldText.setFont(font);
                shieldText.setCharacterSize(14);
                shieldText.setFillColor(Color::White);
                shieldText.setString("x" + to_string(Scount));

                // Position and draw the count texts next to their sprites
                healthText.setPosition(miniItemSprites[0].getPosition().x + miniItemSprites[0].getGlobalBounds().width - 12, 
                                    miniItemSprites[0].getPosition().y);
                window.draw(healthText);
                
                manaText.setPosition(miniItemSprites[1].getPosition().x + miniItemSprites[1].getGlobalBounds().width - 15, 
                                    miniItemSprites[1].getPosition().y);
                window.draw(manaText);
                
                buffText.setPosition(miniItemSprites[2].getPosition().x + miniItemSprites[2].getGlobalBounds().width - 15, 
                                    miniItemSprites[2].getPosition().y);
                window.draw(buffText);
                
                shieldText.setPosition(miniItemSprites[3].getPosition().x + miniItemSprites[3].getGlobalBounds().width - 20, 
                                    miniItemSprites[3].getPosition().y);
                window.draw(shieldText);
                
                // Draw mini sprites and their count texts
                for (int i = 0; i < 4; ++i) {
                    window.draw(miniItemSprites[i]);
                }

                if (ItemShowMessage) {
                    if (ItemMessageTimer.getElapsedTime().asSeconds() < ItemMessageDuration) {
                        window.draw(ItemMessage);
                    } else {
                        ItemShowMessage = false;
                    }
                }

                for (int i = 0; i < 20; ++i) {
                    if (boxActive[i]) {
                        window.draw(boxes[i]);
                    }
                }

                
                if (powerUp.active) {
                    window.draw(powerUp.shape);

                }

                window.draw(petBattleSprites[petindex]);
                window.draw(botPetBattleSprites[random]);

                for (int i = 0; i < MAX_ATTACKS; i++) {
                    if (attacks[i].active) {
                        window.draw(attacks[i].shape);
                    }
                }
                
                // Draw enemy bullets
                for (int i = 0; i < MAX_ENEMY_ATTACKS; i++) {
                    if (enemyAttacks[i].active) {
                        window.draw(enemyAttacks[i].shape);
                    }
                }
                
                // Draw score and power-up text
                window.draw(BattlescoreText);
                if (!powerUpText.getString().isEmpty()) {
                    window.draw(powerUpText);
                }
                
                if (playerWon ) {
                    GameOverMssgText.setString("You Win!!!\n You got 500 Coins");
                    GameOverMssgText.setFillColor(Color::Green);
                    currentPlayer->addCurrency(500);
                } 

                if (botWon) {
                    GameOverMssgText.setString("You Lost!!!");
                    GameOverMssgText.setFillColor(Color::Red);
                }


                
                
                // Draw game over text if game is over
                if (BattlegameOver) {
                    // Reset game
                    petBattleSprites[petindex].setPosition(100.0f, 720 / 2 - 25.0f);
                    botPetBattleSprites[random].setPosition(1280 - 150.0f, 720 / 2 - 25.0f);
                    
                    // Reset bullets
                    for (int i = 0; i < MAX_ATTACKS; i++) {
                        attacks[i].active = false;
                    }
 
                    for (int i = 0; i < MAX_ENEMY_ATTACKS; i++) {
                        enemyAttacks[i].active = false;
                    }
                    
                    // Reset power-ups
                    powerUp.active = false;
                    playerHasSpeedBoost = false;
                    playerHasRapidFire = false;
                    playerHasShield = false;
                    powerUpText.setString("");
                    powerUpSpawnTimer = 5.0f;

                    for (int i = 0; i < 4; ++i) {
                        pet1 = currentGuild->getPet(i);
                        if (pet1 != nullptr) {
                            pet1->RestoreHealth();
                            pet1->RestoreMana();
                        }
                    }

                    // Reset enemy AI
                    enemyDodgeChance = 0.7f;
                    
                    playerScore = 0;
                    BattlescoreText.setString("Points: " + to_string(playerScore) + " | To " + to_string(SCORE_TO_WIN) + " wins!");
                    
                    Clock tempClock;

                    // Blocking display loop for 3 seconds
                    while (tempClock.getElapsedTime().asSeconds() < 3.0f) {
                        window.draw(GameOverMssgText);
                        window.display();
                    }
                    
                    BattlegameOver = false;
                    currentScreen = Screen::GAME;
                    petindex = 0;
                    botWon = false;
                    playerWon = false;
                    GuildVGuildMode = false;
                }


            } else if (TwoVTwoMode) {

                gameStarted = true;

                string battlePetName = pet1->getName();
                
                Text battlepetStatsText;
                battlepetStatsText.setFont(font); // Make sure to use your game's font
                battlepetStatsText.setCharacterSize(20);
                battlepetStatsText.setFillColor(Color::Green);
                int PetHealth = pet1->getHealth();
                int PetMana = pet1->getMana();
                
                string stats = battlePetName + " Health:\n" + to_string(PetHealth) + "\n" + " Mana:\n" + to_string(PetMana);

                battlepetStatsText.setString(stats);
                battlepetStatsText.setPosition(20, 40);
                window.draw(battlepetStatsText);

                Item** playerInventory = currentPlayer->getInventory();
                for (int i = 0; i < currentPlayer->getInventorySize(); i++) {
                    Item* currentItem = currentPlayer->getInventoryItem(i);
                    if (currentItem != nullptr) {

                        if(currentItem->getName() == "Healing Potion") {
                            currentItem->setCount(Hcount);
   
                        }else if (currentItem->getName() == "Shield" ) {
                            currentItem->setCount(Scount);

                        
                        }else if (currentItem->getName() == "Mana Potion") {
                            currentItem->setCount(Mcount);
   

                        }else if(currentItem->getName() == "Buff Item") {
                            currentItem->setCount(Bcount);

                        }

                    }

                }

                // Create text objects for counts (if not already defined as class members)
                Text healthText, manaText, buffText, shieldText;
                
                // Set up the count texts
                healthText.setFont(font); // Assuming font is defined elsewhere
                healthText.setCharacterSize(14);
                healthText.setFillColor(Color::White);
                healthText.setString("x" + to_string(Hcount));
                
                manaText.setFont(font);
                manaText.setCharacterSize(14);
                manaText.setFillColor(Color::White);
                manaText.setString("x" + to_string(Mcount));
                
                buffText.setFont(font);
                buffText.setCharacterSize(14);
                buffText.setFillColor(Color::White);
                buffText.setString("x" + to_string(Bcount));
                
                shieldText.setFont(font);
                shieldText.setCharacterSize(14);
                shieldText.setFillColor(Color::White);
                shieldText.setString("x" + to_string(Scount));

                // Position and draw the count texts next to their sprites
                healthText.setPosition(miniItemSprites[0].getPosition().x + miniItemSprites[0].getGlobalBounds().width - 12, 
                                    miniItemSprites[0].getPosition().y);
                window.draw(healthText);
                
                manaText.setPosition(miniItemSprites[1].getPosition().x + miniItemSprites[1].getGlobalBounds().width - 15, 
                                    miniItemSprites[1].getPosition().y);
                window.draw(manaText);
                
                buffText.setPosition(miniItemSprites[2].getPosition().x + miniItemSprites[2].getGlobalBounds().width - 15, 
                                    miniItemSprites[2].getPosition().y);
                window.draw(buffText);
                
                shieldText.setPosition(miniItemSprites[3].getPosition().x + miniItemSprites[3].getGlobalBounds().width - 20, 
                                    miniItemSprites[3].getPosition().y);
                window.draw(shieldText);
                
                // Draw mini sprites and their count texts
                for (int i = 0; i < 4; ++i) {
                    window.draw(miniItemSprites[i]);
                }

                if (ItemShowMessage) {
                    if (ItemMessageTimer.getElapsedTime().asSeconds() < ItemMessageDuration) {
                        window.draw(ItemMessage);
                    } else {
                        ItemShowMessage = false;
                    }
                }

                for (int i = 0; i < 20; ++i) {
                    if (boxActive[i]) {
                        window.draw(boxes[i]);
                    }
                }

                
                if (powerUp.active) {
                    window.draw(powerUp.shape);

                }

                window.draw(petBattleSprites[petindex]);
                window.draw(botPetBattleSprites[random]);

                for (int i = 0; i < MAX_ATTACKS; i++) {
                    if (attacks[i].active) {
                        window.draw(attacks[i].shape);
                    }
                }
                
                // Draw enemy bullets
                for (int i = 0; i < MAX_ENEMY_ATTACKS; i++) {
                    if (enemyAttacks[i].active) {
                        window.draw(enemyAttacks[i].shape);
                    }
                }
                
                // Draw score and power-up text
                window.draw(BattlescoreText);
                if (!powerUpText.getString().isEmpty()) {
                    window.draw(powerUpText);
                }

                if (playerWon ) {
                    GameOverMssgText.setString("You Win!!!\n You got 500 Coins");
                    GameOverMssgText.setFillColor(Color::Green);
                    currentPlayer->addCurrency(500);
                } 

                if (botWon) {
                    GameOverMssgText.setString("You Lost!!!");
                    GameOverMssgText.setFillColor(Color::Red);
                }

                // Draw game over text if game is over
                if (BattlegameOver) {
                    // Reset game
                    petBattleSprites[petindex].setPosition(100.0f, 720 / 2 - 25.0f);
                    botPetBattleSprites[random].setPosition(1280 - 150.0f, 720 / 2 - 25.0f);
                    
                    // Reset bullets
                    for (int i = 0; i < MAX_ATTACKS; i++) {
                        attacks[i].active = false;
                    }
 
                    for (int i = 0; i < MAX_ENEMY_ATTACKS; i++) {
                        enemyAttacks[i].active = false;
                    }
                    
                    // Reset power-ups
                    powerUp.active = false;
                    playerHasSpeedBoost = false;
                    playerHasRapidFire = false;
                    playerHasShield = false;
                    powerUpText.setString("");
                    powerUpSpawnTimer = 5.0f;

                    for (int i = 0; i < 4; ++i) {
                        pet1 = currentGuild->getPet(i);
                        if (pet1 != nullptr) {
                            pet1->RestoreHealth();
                            pet1->RestoreMana();
                        }
                    }

                    // Reset enemy AI
                    enemyDodgeChance = 0.7f;
                    
                    playerScore = 0;
                    BattlescoreText.setString("Points: " + to_string(playerScore) + " | To " + to_string(SCORE_TO_WIN) + " wins!");
                    
                    Clock tempClock;

                    // Blocking display loop for 3 seconds
                    while (tempClock.getElapsedTime().asSeconds() < 3.0f) {
                        window.draw(GameOverMssgText);
                        window.display();
                    }
                    
                    BattlegameOver = false;
                    currentScreen = Screen::GAME;
                    petindex = 0;
                    botWon = false;
                    playerWon = false;
                    TwoVTwoMode = false;
                    pet1index = -1;
                    pet2index = -1;
                    selectionComplete = false;
                }

            }

        }

        window.display();
    }

    guildName = currentGuild->getName();
    gameManager->savePlayerdata(username, password, guildName);

    // Clean up resources
    delete gameManager; // This will handle deleting the Player and associated objects
    return 0;
}
