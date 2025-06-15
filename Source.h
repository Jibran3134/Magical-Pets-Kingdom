#pragma once
#include<iostream>
#include<iomanip>
#include<chrono>
#include<math.h>
#include<fstream>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace std::chrono;
class Pet;

class Guild {
	Pet* pets[4];
	bool roles[4][4]; // 0.Tank 1.Healer 2.DamageDealer 3.Flash
	int petCount;
public:
	void assignRole(int pet, int role) {
		roles[pet][role] = true;
	}
	int getRole(int pet) {
		for (int i = 0; i < 4; i++) {
			if (roles[pet][i] == true)
				return i + 1;
		}
	}
};
class Powerup {
	string power;
	bool active;
public:
	void setPower(string str) {
		power = str;
	}
	string getPower() {
		return power;
	}
	void setactiveStatus(bool value) {
		active = value;
	}
	bool getactiveStatus() {
		return active;
	}
};
class Arena {
protected:
	Pet* playerTeam[4];
	Pet* botTeam[4];
	Guild* guild;
	int petCountTeam1;
	int petCountTeam2;
	bool isAlive[4];
	bool botActive[4];
		Powerup powerups[5];
	//	Obstacle* obstacles[5];
	int score;
public:

	Arena() {
		for (int i = 0; i < 4; i++) {
			playerTeam[i] = NULL;
			botTeam[i] = NULL;
			isAlive[i] = false;
			botActive[i] = false;
		}
		guild = NULL;
		petCountTeam1 = 0;
		petCountTeam2 = 0;
		powerups[0].setPower("Health");
		powerups[1].setPower("Power");
		powerups[2].setPower("Defense");
		powerups[3].setPower("Speed");
		score = 0;
	}
	void increaseScore() {
		score++;
	}
	int getScore() {
		return score;
	}
	void usePowerUp(Pet* pet, string str); 
	bool getPstate(int index) {
		return powerups[index].getactiveStatus();
	}
	void setPstate(int index, bool value) {
		powerups[index].setactiveStatus(value);
	}
	bool getState(string str, int index) {
		if (str == "Player")
			return isAlive[index];
		else
			return botActive[index];

	}
	void setState(string str, int index, bool val) {
		if (str == "Player")
			isAlive[index] = val;
		else if (str == "AI")
			botActive[index] = val;
		else
			cout << "\nInvalid argument passed" << endl;
	}
	int getpetCount(string str) {
		if (str == "Player")
			return petCountTeam1;
		else if (str == "AI")
			return petCountTeam2;
		cout << "Invalid argument passed" << endl;
		return 0;
	}
	Pet* getPet(int index,string str) {
		if(str=="Player")
		return playerTeam[index];
		else if(str=="AI")
			return botTeam[index];
	}
	void addPet(Pet* pet, string team) {
		if (team == "Player") {
			playerTeam[petCountTeam1] =pet;
			isAlive[petCountTeam1] = true;
			petCountTeam1++;
		}
		else if (team == "AI") {
			botTeam[petCountTeam2] = pet;
			botActive[petCountTeam2] = true;
			petCountTeam2++;
		}
		else
			cout << "\nInvalid argument passed" << endl;
	}
	void setpetCount(int num, string str) {
		if (str == "Player")
			 petCountTeam1=num;
		else if (str == "AI")
			 petCountTeam2=num;
	}
};


class Abilities {
	string name;
	string Target_type;
	bool isActive;
	time_point<steady_clock> StartTime;
	
	Pet* pet;
	bool used; // to use the rebirth ability only once
public:
	Abilities(string a, string b) {
		name = a;
		Target_type = b;
		used = false;
		isActive = false;
	}
	bool getActiveStatus() {
		return isActive;
	}
	
	time_point<steady_clock> getStartTime() {
		return StartTime;
	}
	Pet* getTargetPet() {
		return pet;
	}

	void setActiveStatus(bool value) {
		isActive = value;
	}
	
	void setStartTime(time_point<steady_clock> value) {
		StartTime = value;
	}
	void setTargetPet(Pet* target) {
		pet = target;
	}

	string getName() const {
		return name;
	}
	string getTargetType() const {
		return Target_type;
	}
	bool getusedState() {
		return used;
	}
	void setusedState(bool val) {
		used = val;
	}

};

//...................Pets................//
class Pet {
protected:
	string name;
	int health;
	int power;
	int speed;
	int defense;
	int abilityCount; // max=3
	Abilities* ability[2];
	int tempSpeed[4];
	int tempPower[4];
	int tempDefense[4];
public:
	void shoot() {

	}
	Pet() {}
	Pet(string str, int a, int b, int c, int d) {
		name = str;
		health = a;
		power = b;
		speed = c;
		defense = d;
		abilityCount = 3;
		ability[0] = nullptr;
		ability[1] = nullptr;
	}
	
	string getName() const {
		return name;
	}
	int getHealth() const {
		return health;
	}
	int getPower() const {
		return power;
	}
	int getSpeed() const {
		return speed;
	}
	int getDefense() const {
		return defense;
	}
	int getabilityCount() const {
		return abilityCount;
	}
	void restoreHealth(int amount) {
		health = amount;
	}
	void increasePower(int amount) {
		power = amount;
	}
	void increaseSpeed(int amount) {
		speed = amount;
	}
	void increaseDefense(int amount) {
		defense = amount;
	}
	void increaseAbility(int amount) {
		abilityCount = amount;
	}
	void iPower(int amount) {
		power+= amount;
	}
	void iSpeed(int amount) {
		speed+=amount;
	}
	void iDefense(int amount) {
		defense += amount;
	}
	void iHealth(int amount) {
		health+= amount;
	}

	void Damage(int amount) {
		health -= amount;
	}
	float getMaxHealth(Pet* pet) {
		if (pet->getName() == "Dragon") return 600.f;
		if (pet->getName() == "Phoenix") return 600.f;
		if (pet->getName() == "Unicorn") return 600.f;
		if (pet->getName() == "Griffin") return 600.f;
		return 100.f; 
	}
	float getMaxAIHealth(Pet* pet) {
		if (pet->getName() == "Dragon") return 150;
		if (pet->getName() == "Phoenix") return 150.f;
		if (pet->getName() == "Unicorn") return 150.f;
		if (pet->getName() == "Griffin") return 150.f;
		return 100.f;
	}
	float getMaxSpeed(Pet* pet) {
		if (pet->getName() == "Dragon") return 150.f;
		if (pet->getName() == "Phoenix") return 100.f;
		if (pet->getName() == "Unicorn") return 50.f;
		if (pet->getName() == "Griffin") return 100.f;
		return 100.f;
	}
	float getMaxDefense(Pet* pet) {
		if (pet->getName() == "Dragon") return 100;
		if (pet->getName() == "Phoenix") return 150.f;
		if (pet->getName() == "Unicorn") return 100.f;
		if (pet->getName() == "Griffin") return 100.f;
		return 100.f;
	}
	float getMaxPower(Pet* pet) {
		if (pet->getName() == "Dragon") return 150.f;
		if (pet->getName() == "Phoenix") return 100.f;
		if (pet->getName() == "Unicorn") return 50.f;
		if (pet->getName() == "Griffin") return 100.f;
		return 100.f;
	}
	virtual void useAbility(int num, Arena* arena = NULL);

	Pet(const Pet& pet) {
		name = pet.name;
		health = pet.health;
		power = pet.power;
		speed = pet.speed;
		defense = pet.defense;

		for (int i = 0; i < 2; ++i) {
			ability[i] = new Abilities(pet.ability[i]->getName(), pet.ability[i]->getTargetType());
		}
	}
	Pet& operator=(Pet& pet) {
		name = pet.name;
		health = pet.health;
		power = pet.power;
		speed = pet.speed;
		defense = pet.defense;

		for (int i = 0; i < 2; ++i) {
			ability[i] = new Abilities(pet.ability[i]->getName(), pet.ability[i]->getTargetType());
		}
		return *this;
	}
	void setActiveAbility(int index,bool value) {
		ability[index - 1]->setActiveStatus(value);
	}
	bool getActiveAbility(int index) {
		return ability[index - 1]->getActiveStatus();
	}
	virtual void AbilityTimeout(Arena* arena)  {}
	void setTempSpeed(int index, int value) {
		tempSpeed[index] = value;
	}
	void setTempPower(int index, int value) {
		tempPower[index] = value;
	}
	void setTempDefense(int index, int value) {
		tempDefense[index] = value;
	}
	int getTempSpeed(int index) {
		return tempSpeed[index];
	}
	int getTempPower(int index) {
		return tempPower[index];
	}
	int getTempDefense(int index) {
		return tempDefense[index];
	}
	friend std::ostream& operator<<(std::ostream& os, const Pet& p) {
		os <<"Name: "<< p.name<<endl;
		os << "Health: " << p.health << endl;
		os << "Power: " << p.power << endl;
		os << "Speed: " << p.speed << endl;
		os << "Defense: " << p.defense<<endl<<endl;
		return os;
	}
	friend std::istream& operator>>(std::istream& is, Pet& p) {
		string s;
		is >>s >> p.name ;
		is >> s >> p.health;
		is >> s >> p.power ;
		is >> s >> p.speed ;
		is >> s >> p.defense;
		cout << "Name: " << p.name << endl;
		cout << "Health: " << p.health << endl;
		cout << "Power: " << p.power << endl;
		cout << "Speed: " << p.speed << endl;
		cout << "Defense: " << p.defense << endl << endl;
	}
};
class Dragon :public Pet {
public:
	Dragon(string str, int a, int b, int c, int d) :Pet(str, a, b, c, d) {
		ability[0] = new Abilities("Fireball_Attack", "Enemy");
		ability[1] = new Abilities("Dragon's_Roar", "Enemy");
	}
	void useAbility(int num, Arena* arena ) {

		if (num==1) {
			cout << "\nThrowing fireball" << endl;
			ability[0]->setStartTime(steady_clock::now());
			ability[0]->setActiveStatus(true);
		}
		else if (num==2) {  
			cout << "\nStunning enenmies"<<endl;
			if (!arena) {
				cout << "\nArena is null" << endl;
			}
			ability[1]->setStartTime(steady_clock::now());
			ability[1]->setActiveStatus(true);
			for (int i = 0; i < arena->getpetCount("AI"); i++) {
				tempSpeed[i] = arena->getPet(i, "AI")->getSpeed();
				tempPower[i]= arena->getPet(i, "AI")->getPower();
				arena->getPet(i, "AI")->increaseSpeed(0);
				arena->getPet(i, "AI")->increasePower(0);
			}

		}
	}	
	void AbilityTimeout(Arena*arena) override{
		if (ability[0]->getActiveStatus()) {
			auto now = steady_clock::now();
			auto elapsed = duration_cast<seconds>(now - ability[0]->getStartTime()).count();
			if (elapsed >= 5) {
				cout << "\nAbility finished after " << elapsed << " s" << endl;
				ability[0]->setActiveStatus(false);
			}
		}
		if (ability[1]->getActiveStatus()) {
			auto now = steady_clock::now();
			auto elapsed = duration_cast<seconds>(now - ability[1]->getStartTime()).count();
			if (elapsed >= 5) {
				cout << "\nAbility finished after " << elapsed << " s" << endl;
				for (int i = 0; i < arena->getpetCount("AI"); i++) {
					arena->getPet(i, "AI")->increaseSpeed(tempSpeed[i]);
					arena->getPet(i, "AI")->increasePower(tempPower[i]);
				}
				ability[1]->setActiveStatus(false);
			}
		}
	}
};
class Phoenix :public Pet {
public:
	Phoenix(string str, int a, int b, int c, int d) :Pet(str, a, b, c, d) {
		ability[0] = new Abilities("Flame_Healing", "Ally");
		ability[1] = new Abilities("Rebirth", "Self");
		
	}
	void useAbility(int num, Arena* arena) {
		if (num==1) {
			cout << "\nHealing a pet" << endl;
			for (int i = 0; i < arena->getpetCount("Player"); i++) {
				if (health < 50) {
					restoreHealth(50); break;
				}
				else if (arena->getPet(i,"Player")->getName() == "Dragon" && arena->getPet(i, "Player")->getHealth() < 150) {
					arena->getPet(i, "Player")->restoreHealth(150); break;
				}
				else if (arena->getPet(i, "Player")->getName() == "Unicorn" && arena->getPet(i, "Player")->getHealth() < 30) {
					arena->getPet(i, "Player")->restoreHealth(30); break;
				}
				else if (arena->getPet(i, "Player")->getName() == "Griffin" && arena->getPet(i, "Player")->getHealth() < 100) {
					arena->getPet(i, "Player")->restoreHealth(100); break;
				}
			}
			ability[0]->setActiveStatus(false);
		}
		if (num==2 && ability[1]->getActiveStatus())
			cout << "\nAbility has been used once , Cannot use again..." << endl;
		else if (num==2) {
			for (int i = 0; i < arena->getpetCount("Player"); i++) {
				if (arena->getPet(i, "Player")->getName() == "Phoenix" && arena->getState("Player", i) == false) {
					arena->setState("Player", i, true);
					ability[1]->setActiveStatus(true);
					health = getMaxHealth(this);
					cout << "\nPlayer has  been reborn" << endl;
				}
			}
		}
	}
};
class Unicorn :public Pet {
public:
	Unicorn(string str, int a, int b, int c, int d) :Pet(str, a, b, c, d) {
		ability[0] = new Abilities("Speed_Burst", "Self");
		ability[1] = new Abilities("Magic_Shield", "Self");
		
	}

	void useAbility(int num, Arena* arena) {
		if (num == 1) {
			cout << "\nSpeed burst ability activated" << endl;
			ability[0]->setStartTime(steady_clock::now());
			ability[0]->setActiveStatus(true);
			tempSpeed[2] = speed;
			increaseSpeed(200);
		}
		else if (num == 2) {
			cout << "Magic_Shield activated" << endl;
			ability[1]->setStartTime(steady_clock::now());
			ability[1]->setActiveStatus(true);
			tempDefense[2] = defense;
			increaseDefense(500);
		}
	}
	void AbilityTimeout(Arena* arena) override {
		if (ability[0]->getActiveStatus()) {
			auto now = steady_clock::now();
			auto elapsed = duration_cast<seconds>(now - ability[0]->getStartTime()).count();
			if (elapsed >= 5) {
				cout << "\nAbility finished after " << elapsed << " s" << endl;
				ability[0]->setActiveStatus(false);
				increaseSpeed(tempSpeed[2]);
			}
		}	
		if (ability[1]->getActiveStatus()) {
			auto now = steady_clock::now();
			auto elapsed = duration_cast<seconds>(now - ability[1]->getStartTime()).count();
			if (elapsed >= 5) {
				cout << "\nAbility finished after " << elapsed << " s" << endl;
				increaseDefense(tempDefense[2]);
				ability[1]->setActiveStatus(false);
			}
		}
	}
};
class Griffin :public Pet {
public:
	Griffin(string str, int a, int b, int c, int d) :Pet(str, a, b, c, d) {
		ability[0] = new Abilities("Claw_Strike", "Enemy");
		ability[1] = new Abilities("Dive_Bomb", "Enemy");
		
	}
	void useAbility(int num,Arena*arena) {
		if (num==1) {
			cout << "\nPowerfull meele attack" << endl;
			ability[0]->setStartTime(steady_clock::now());
			ability[0]->setActiveStatus(true);
			tempPower[2] = power;
			increasePower(200);
		}
		if (num == 2) {
			cout << "\nStunning enenmies" << endl;
			if (!arena) {
				cout << "\nArena is null" << endl;
			}
			ability[1]->setStartTime(steady_clock::now());
			ability[1]->setActiveStatus(true);
			for (int i = 0; i < arena->getpetCount("AI"); i++) {
				tempSpeed[i] = arena->getPet(i, "AI")->getSpeed();
				tempPower[i] = arena->getPet(i, "AI")->getPower();
				arena->getPet(i, "AI")->increaseSpeed(0);
				arena->getPet(i, "AI")->increasePower(0);
			}
		}
	}
	void AbilityTimeout(Arena* arena) override {
		if (ability[0]->getActiveStatus()) {
			auto now = steady_clock::now();
			auto elapsed = duration_cast<seconds>(now - ability[0]->getStartTime()).count();
			if (elapsed >= 5) {
				cout << "\nAbility finished after " << elapsed << " s" << endl;
				ability[0]->setActiveStatus(false);
				increaseDefense(tempDefense[2]);
			}
		}
		if (ability[1]->getActiveStatus()) {
			auto now = steady_clock::now();
			auto elapsed = duration_cast<seconds>(now - ability[1]->getStartTime()).count();
			if (elapsed >= 5) {
				cout << "\nAbility finished after " << elapsed << " s" << endl;
				for (int i = 0; i < arena->getpetCount("AI"); i++) {
					arena->getPet(i, "AI")->increaseSpeed(tempSpeed[i]);
					arena->getPet(i, "AI")->increasePower(tempPower[i]);
				}
				ability[1]->setActiveStatus(false);
			}
		}
	}
};

class Training_Complex {
public:
	void Train(Pet& pet) {
		cout << "\nTraining Complete" << endl << endl;
		int num = rand() % 4;
		switch (num) {
		case 0:
			pet.iHealth(40);
			cout << "\nHealth of "<<pet.getName()<<" increased by 40" << endl;
			break;

		case 1:
			pet.iPower(40);
			cout << "\nPower of " << pet.getName() << " increased by 40" << endl;
			break;

		case 2:
			pet.iDefense(40);
			cout << "\nDefense of " << pet.getName() << " increased by 40" << endl;
			break;

		case 3:
			pet.iSpeed(40);
			cout << "\nSpeed of " << pet.getName() << " increased by 40" << endl;
			break;
		}
	}

};


//...................Items................//


class Items {
protected:
	Pet* targetPet;
	string name;
	int price;
	bool isActive;
	time_point<steady_clock> StartTime;
	int tempSpeed;
	int tempPower;
	int tempDefense;
public:
	Items(string a, int b) :name(a), price(b) {
		targetPet = NULL;
		isActive = false;
	}
	virtual void use(Pet& target) = 0;
	virtual void AbilityTimeout() {}
	Items& operator=(const Items& item) {
		name = item.name;
		price = item.price;
		return *this;
	}
	string getName()const {
		return name;
	}
	int getPrice()const {
		return price;
	}
	virtual ~Items() {}
};
class Healing_Potion :public Items {
public:
	Healing_Potion(string name, int price = 0) :Items(name, price) {}
	void use(Pet& target)override {
		cout << "........Healing " << target.getName() << "........" << endl;
		target.restoreHealth(150);
	}
};
class Mana_Potion :public Items {
public:
	Mana_Potion(string name, int price = 0) :Items(name, price) {}
	void use(Pet& target)override {
		cout << "........Refilling ability of " << target.getName() << "........" << endl;
		target.increaseAbility(3);
	}
};
class Buff_Item :public Items {
public:
	Buff_Item(string name, int price = 0) :Items(name, price) {}
	void use(Pet& target)override {
		cout << "........Temporary boosting " << target.getName() << "........" << endl;
		tempSpeed = target.getSpeed();
		tempPower = target.getPower();

		StartTime = steady_clock::now();
		isActive = true;
		target.increaseSpeed(200);
		target.increasePower(200);
		targetPet = &target;
	}
	void AbilityTimeout()override {
		if (isActive) {
			auto now = steady_clock::now();
			auto elapsed = duration_cast<seconds>(now - StartTime).count();
			if (elapsed >= 5) {
				targetPet->increaseSpeed(tempSpeed);
				targetPet->increasePower(tempPower);
				cout << "\nAbility finished after " << elapsed << " s" << endl;
				isActive = false;
				targetPet = nullptr;
			}

		}
	}
};
class Shield :public Items {
public:
	Shield(string name, int price = 0) :Items(name, price) {}
	void use(Pet& target) override {
		cout << "........Temporary shielding " << target.getName() << "........" << endl;
		tempDefense = target.getDefense();
		StartTime = steady_clock::now();
		isActive = true;
		targetPet = &target;
		target.increaseDefense(200);
	}

	void AbilityTimeout() override {
		if (isActive && targetPet) {
			auto now = steady_clock::now();
			auto elapsed = duration_cast<seconds>(now - StartTime).count();
			if (elapsed >= 5) {
				targetPet->increaseDefense(tempDefense);
				cout << "\nShield finished after " << elapsed << " s" << endl;
				isActive = false;
				targetPet = nullptr;
			}
		}
	}
};

//...................Shop................//
class Shop {
	Items* items[4];
public:
	void addItem(Items* item1, Items* item2, Items* item3, Items* item4) {
		items[0] = item1;
		items[1] = item2;
		items[2] = item3;
		items[3] = item4;
	}
	void display_items() {
		cout << "Item 1 " << items[0]->getName() << endl;
		cout << "Item 2 " << items[1]->getName() << endl;
		cout << "Item 3 " << items[2]->getName() << endl;
		cout << "Item 4 " << items[3]->getName() << endl;
	}
	Items* sellItem(int index) {
		return items[index];
	}
	int getPrice(int index) {
		return items[index]->getPrice();
	}
};
class Inventory {
	Items* items[10];
	int Itemcount;
public:
	Inventory() : Itemcount(0) {}
	void addItem(Items* item) {
		items[Itemcount] = item;
		Itemcount++;
	}
	void useItem(Items* item, Pet& target) {
		item->use(target);
		int i;
		for (i = 0; i < 10; i++) {
			if (items[i]->getName() == item->getName()) {
				Itemcount--;
				break;
			}
		}
		for (int j = i; j < Itemcount - 1; ++j) {
			items[j] = items[j + 1];
		}
		items[Itemcount] = nullptr;
		Itemcount--;
	}
	
	void removeItem(int index) {
		bool valid = false;
		for (int i = 0; i < Itemcount; i++) {
			if (items[i] && items[i]->getName() == "Healing_Potion" && index == 1)
				valid = true;
			else if (items[i] && items[i]->getName() == "Mana_Potion" && index == 2)
				valid = true;
			else if (items[i] && items[i]->getName() == "Buff_Item" && index == 3)
				valid = true;
			else if (items[i] && items[i]->getName() == "Shield" && index == 4)
				valid = true;
			if (valid) {
				delete items[i];
				for (int j = i; j < Itemcount - 1; j++) {
					items[j] = items[j + 1];
				}
				items[--Itemcount] = nullptr;
				return;
			}
		}
	}
	
	Items* getItem(int index) {
		if (index < 0 || index >= Itemcount) return NULL;
		return items[index];
	}
	int getItemCount() {
		return Itemcount;
	}
	int getCount(int index) {
		int count = 0;
		for (int i = 0; i < Itemcount; i++) {
			if (items[i]&&items[i]->getName() == "Healing_Potion" && index == 1)
				count++;
			else if (items[i] && items[i]->getName() == "Mana_Potion" && index == 2)
				count++;
			else if (items[i] && items[i]->getName() == "Buff_Item" && index == 3)
				count++;
			else if (items[i] && items[i]->getName() == "Shield" && index == 4)
				count++;
		}
		return count;

	}

};
class Player {
	string name;
	string kingdomName;
	int level;
	int cash;
	int petCount;
	Inventory inventory;
	Shop shop;
	int games_won;
	Pet pets[4];
public:
	Player() {}
	Player(string player, string kingdom, int level, int cash) {
		name = player;
		kingdomName = kingdom;
		this->level = level;
		this->cash = cash;
		petCount = 0;
		games_won = 0;
	}
	void increaseGamesWon() {
		games_won++;
	}
	int getGamesWon() {
		return games_won;
	}
	void visitShop(Shop& shp) {
		shop = shp;
	}
	void addPet(Pet pet) {
		pets[petCount] = pet;
		petCount++;
		cout <<"\n"<< pet.getName() << " has been added" << endl;
	}
	Pet* getPet(int index) {
		return &pets[index];
	}
	int get_petCount() {
		return petCount;
	}
	void buyItem(int index) {
		if (index < 0 || index >= 4) {
			cout << "Invalid item index.\n";
			return;
		}
		if (shop.getPrice(index) > cash) {
			cout << "\nInsufficient Balance\n";
			return;
		}
		if (inventory.getItemCount() >= 10) {
			cout << "\nInventory is full\n";
			return;
		}
		Items* temp = shop.sellItem(index);
		if (!temp) {
			cout << "\nShop returned null item.\n";
			return;
		}
		Items* newItem = nullptr;
		if (temp->getName() == "Healing_Potion")
			newItem = new Healing_Potion("Healing_Potion", 200);
		else if (temp->getName() == "Mana_Potion")
			newItem = new Mana_Potion("Mana_Potion", 200);
		else if (temp->getName() == "Buff_Item")
			newItem = new Buff_Item("Buff_Item", 200);
		else if (temp->getName() == "Shield")
			newItem = new Shield("Shield", 200);
		if (newItem) {
			inventory.addItem(newItem);
			cash -= shop.getPrice(index);
			cout << newItem->getName() << " has been bought." << endl;
		}
	}
	Inventory* Getinventory() {
		return &inventory;
	}
	int getCash() {
		return cash;
	}
	void IncreaseLevel() {
		level++;
	}
	int getLevel() {
		return level;
	}
	string getName() {
		return name;
	}
	friend ostream& operator<<(ostream& os, const Player& p) {
		os << "Name: " << p.name << endl;
		os << "Kingdom_Name: " << p.kingdomName << endl;
		os << "Coins: " << p.cash << endl;
		os << "Games won" << p.games_won << endl;
		os << "Level: " << p.level << endl<<endl;	
			return os;
	}
	friend istream& operator>>(istream& is, Player& p) {
		string s;
		is >> s >> p.name;
		is >> s >> p.kingdomName;
		is >> s >> p.cash;
		is >> s >> p.games_won;
		is >> s >> p.level;
		cout << "Name: " << p.name << endl;
		cout << "Kingdom_Name: " << p.kingdomName << endl;
		cout << "Coins: " << p.cash << endl;
		cout << "Games won" << p.games_won << endl;
		cout << "Level: " << p.level << endl << endl;
		return is;
	}
};

class GameManager {
	Player* players[10];
	Player* enemy;
	int playerCount;
	Arena *arena;
	Pet* pets[4];
	Pet* AI[4];
	Shop* shop;
	Guild* guild;
	Training_Complex training;
public:
	GameManager()  {
		playerCount = 0;
		enemy = NULL;
		arena = NULL;
		for (int i = 0; i < 4; i++) {
			pets[i] = NULL;
			AI[i] = NULL;
		}
			shop = NULL;
			guild = NULL;
	}
	Player* getPlayer(int num) {
		return players[num];
	}
	Player* getEnemy() {
		return enemy;
	}
	
	void StartNewGame() {
		players[playerCount] = new Player("Jibran", "My_Kingdom", 1, 1000);
		playerCount++;
		enemy = new Player("AI", "The Destructer", 0, 0);
	
		Dragon *dragon= new Dragon("Dragon", 600, 150, 50, 100);
		Phoenix *phoenix=new Phoenix("Phoenix", 600, 100, 30, 150);
		Unicorn* unicorn=new Unicorn("Unicorn", 600, 50, 150, 100);
		Griffin *griffin=new Griffin("Griffin", 600, 100, 100, 100);

		SetPets(dragon, phoenix, unicorn, griffin);

		Dragon* dragonAI= new Dragon("Dragon", 150, 150, 50, 100);
		Phoenix* phoenixAI = new Phoenix("Phoenix", 50, 100, 30, 150);
		Unicorn* unicornAI = new Unicorn("Unicorn", 30, 50, 150, 100);
		Griffin* griffinAI = new Griffin("Griffin", 100, 100, 100, 100);

		SetAI(dragonAI, phoenixAI, unicornAI, griffinAI);

		 Healing_Potion *healing_potion=new Healing_Potion("Healing_Potion", 200); // price 
		 Mana_Potion *mana_potion= new Mana_Potion("Mana_Potion", 150);
		 Buff_Item *buff_item=new Buff_Item("Buff_Item", 100);
		 Shield *shield=new Shield("Shield", 250);

		shop = new Shop;
		
		shop->addItem(healing_potion, mana_potion, buff_item, shield);

		players[0]->visitShop(*shop);
	
		 arena = new Arena();

		 guild = new Guild;
	}
	void setArena(Arena& arena) {
		this->arena = &arena;
	}
	Arena* getArena() {
		return arena;
	}
	void SetPets(Pet* pet1 , Pet* pet2 , Pet* pet3 , Pet* pet4) {
		pets[0] = pet1;
		pets[1] = pet2;
		pets[2] = pet3;
		pets[3] = pet4;
	}
	Pet* GetPet(int i) {
		return pets[i];
	}
	void SetAI(Pet* pet1, Pet* pet2, Pet* pet3, Pet* pet4) {
		AI[0] = pet1;
		AI[1] = pet2;
		AI[2] = pet3;
		AI[3] = pet4;
	}
	Pet* GetAI(int i) {
		return AI[i];
	}
	void setShop(Shop* shp) {
		shop= shp;
	}
	Shop* getShop() {
		return shop;
	}
	Guild* getGuild() {
		return guild;
	}
	Training_Complex* get_training_Complex() {
		return &training;
	}
};


class FileHandeling {
public:
	void saveGame(GameManager& MyGame, string fileName) {
		cout << "\nSaving Game" << endl;
		ofstream myfile;
		myfile.open(fileName);
		if (!myfile.is_open()) {
			cout << "\nUnable to open file" << endl;
			return;
		}
		Player* p = MyGame.getPlayer(0);
		myfile << *p;
		for (int i = 0; i < 4; i++) {
			myfile << "Pet_" << i + 1 << ": " << endl;
			myfile << *MyGame.GetPet(i);
		}
		myfile.close();
	}
	void loadGame(GameManager& MyGame, string fileName) {
		
			string s;
			cout << "\nLoading Game" << endl;
			ifstream myfile;
			myfile.open(fileName);
			if (!myfile.is_open()) {
				cout << "\nUnable to open file" << endl;
				return;
			}
			myfile >> *MyGame.getPlayer(0);
			for (int i = 0; i < 4; i++) {
				getline(myfile, s);
				myfile >> *MyGame.GetPet(i);
			}
			myfile.close();
		}
	
	 
};