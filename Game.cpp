#include "Game.h"

// -------------------- Object class ----------------------

Object::Object(string name, int value) {
	
	if(value < 0)
		throw std::invalid_argument("negative value no/wrong exception");
		
	this->name_ = name;
	this->value_ = value;
	this->owner_ =  nullptr;
}

Object::~Object() {}

string Object::getName() const {
	// IMPLEMENT ME

	return name_; // dummy
}

int Object::getValue() const {
	// IMPLEMENT ME

	return value_; // dummy
}

string Object::print() const {
	// IMPLEMENT ME

	return ""; // dummy
}

void Object::use() {
	// IMPLEMENT ME

}

std::ostream& operator<<(std::ostream& os, const Object& o) {
	// IMPLEMENT ME
	return os << o.print();
}

// ------------------- Food class ----------------------

Food::Food(string name, int value) : Object(name, value) {
	// IMPLEMENT ME
	
}

Food::~Food() {}

string Food::print() const {
	// IMPLEMENT ME
	return "Food, name: " + this->getName() +", value: " + std::to_string(this->getValue());; // dummy
}

void Food::use() {
	// IMPLEMENT ME
	
	int ownerStamina = this->owner_->stamina_;
	if((ownerStamina + this->getValue()) >= 100)
	{
		this->owner_->stamina_= 100;
	}
	else if((ownerStamina + this->getValue()) < 100)
	{
		this->owner_->stamina_ = ownerStamina + this->getValue();
	}
	
	// to remove element from listof elements
	string name =  this->getName();
	auto item = find_if(this->owner_->listOfInventory_.begin(), this->owner_->listOfInventory_.end(), [name](const std::unique_ptr<Object>& lt) {
                        return lt.get()->getName() == name;
                   });
	this->owner_->listOfInventory_.erase(item);
}
// ------------------- Weapon class ----------------------

Weapon::Weapon(string name, int value) : Object(name, value){
	// IMPLEMENT ME

}

Weapon::~Weapon() {}
string Weapon::print() const {
	// IMPLEMENT ME
	return "Weapon, name: " + this->getName() +", value: " + std::to_string(this->getValue());; // dummy
}
void Weapon::use() {
	// IMPLEMENT ME
	

	if(this->owner_->weaponInUse_ != nullptr)
	{
		this->owner_->weaponInUse_ = nullptr;	
	}
	this->owner_->weaponInUse_ = this;
}
// ------------------- Armour class ----------------------

Armour::Armour(string name, int value) : Object(name, value){
	// IMPLEMENT ME

}

Armour::~Armour() {}

string Armour::print() const {
	// IMPLEMENT ME
	return "Armour, name: " + this->getName() +", value: " + std::to_string(this->getValue());; // dummy
}

void Armour::use() {
		
	owner_->listOfArmourInUse_.push_back(this);
}
// ------------------- Player class ----------------------

Player::Player(string name) {
	// IMPLEMENT ME
	this->name_ = name;
	this->health_ = 100;
	this->stamina_ = 100;
	this->weaponInUse_ = nullptr;
}

Player::~Player() {}

string Player::getName() const {
	// IMPLEMENT ME

	return name_; // dummy
}

int Player::getHealth() const {
	// IMPLEMENT ME

	return health_; // dummy
}

int Player::getStamina() const {
	// IMPLEMENT ME

	return stamina_; // dummy
}

void Player::pickup(std::unique_ptr<Object> o) {
	// IMPLEMENT ME
	if(this->getHealth()<=0)
		throw std::logic_error("");
	else
	{
		o.get()->owner_ = this;
		listOfInventory_.push_back(std::move(o));
	}	
}

string Player::getInventory() const {
	// IMPLEMENT ME
	if(listOfInventory_.size() == 0 )
		return "List of items: none";

	else
	{
		string inventory = "List of items:";
		for(auto& a : listOfInventory_)
		{
			inventory = inventory + "\n " + std::string(a.get()->print());
		}

		return inventory;
	}
		 // dummy
}

string Player::print() const {
	// IMPLEMENT ME
	return ""; // dummy
}

bool Player::use(string name) {
	// IMPLEMENT ME
	if(this->health_ <=0)
		throw std::logic_error("");
	auto item = find_if(listOfInventory_.begin(), listOfInventory_.end(), [name](const std::unique_ptr<Object>& lt) {
                        return lt.get()->getName() == name;
                   });
	if(item!=listOfInventory_.end())
	{
		item.base()->get()->use();
		// after element is used, check item in player's inventory or in listofarmourinuse or weaponInUse
		auto foodExist = find_if(listOfInventory_.begin(), listOfInventory_.end(), [name](const std::unique_ptr<Object>& lt) {
                        return lt.get()->getName() == name;
                   });
		auto armour = find_if(listOfArmourInUse_.begin(), listOfArmourInUse_.end(), [name](const Armour* lt) {
                        return lt->getName() == name;
                   });		   
		if((armour!=listOfArmourInUse_.end()) || (foodExist == listOfInventory_.end()) || (item.base()->get()->getName() == weaponInUse_->getName())){
			return true;
		}	
	}   
	
	return false; // dummy
}

std::ostream& operator<<(std::ostream& os, const Player& p) {
	// IMPLEMENT ME

	return os << p.print();
}

// ------------------- Fighter class ----------------------

Fighter::Fighter(string name) : Player(name){
	// IMPLEMENT ME

}

Fighter::~Fighter() {}

bool Fighter::attack(Player& other) {
	// IMPLEMENT ME
	if(this->getHealth() <= 0)
		throw std::logic_error("Stop! " + this->getName() + " is already dead.");
	else if(other.getHealth() <= 0)
		throw std::logic_error("Stop! " + other.getName() + " is already dead.");
	else
	{
		if(this->getStamina()>=10)
		{
			stamina_ =  stamina_-10;
			int attackStrengthOfAttacker = 10, defendingStrengthOfDefender = 0;
			if(weaponInUse_!=nullptr)
			{
				attackStrengthOfAttacker = attackStrengthOfAttacker + this->weaponInUse_->getValue();
			}

			for(auto x : other.listOfArmourInUse_)
			{
				defendingStrengthOfDefender = defendingStrengthOfDefender + x->getValue();
			}

			if(attackStrengthOfAttacker > defendingStrengthOfDefender)
			{
				if((other.health_ - (attackStrengthOfAttacker - defendingStrengthOfDefender)) > 0)
					other.health_ = other.health_ - (attackStrengthOfAttacker - defendingStrengthOfDefender);
				else
					other.health_ = 0;
				
				return true;
			}

		}
		return false;
	}
	 // dummy
}

string Fighter::print() const
{
	string playerDetails = "Name: " + getName() + "\nType: Fighter\nHealth: " + std::to_string(this->getHealth());
	playerDetails =  playerDetails + "\nStamina: " + std::to_string(getStamina()) + "\n";
	playerDetails = playerDetails + getInventory() + "\nWeapon in use: ";
	if(weaponInUse_ == nullptr)
	{
		playerDetails = playerDetails + "none\n";
	}
	else
	{
		playerDetails = playerDetails + weaponInUse_->getName() + "\n";
	}
	playerDetails = playerDetails + "Armour in use: ";
	if(listOfArmourInUse_.size() == 0)
	{
		playerDetails = playerDetails + "none";
	}
	else
	{
		for(auto& a : listOfArmourInUse_)
		{
			if(a == listOfArmourInUse_.front())
			{
				playerDetails = playerDetails + a->getName();
			}
			else 
			{
				playerDetails = playerDetails + ", " + a->getName();
			}
		}
	}
	return playerDetails;
}

// ------------------- Healer class ----------------------

Healer::Healer(string name) : Player(name){
	// IMPLEMENT ME

}

Healer::~Healer() {}

bool Healer::heal(Player& other) {
	// IMPLEMENT ME
	if((this->getHealth() <= 0) || (other.getHealth() <= 0) )
		throw std::logic_error("");
	
	if(this->getStamina() >= 10)
	{
		this->stamina_ =  this->stamina_-10;
		if((other.getHealth() > 80) && (other.getHealth() < 100))
		{
			other.health_ = 100;
			return true;
		}			
		else if (other.getHealth() < 80)
		{
			other.health_ = other.health_ + 20;
			return true;
		}			
	}
	return false; // dummy
}

string Healer::print() const
{
	string playerDetails = "Name: " + getName() + "\nType: Healer\nHealth: " + std::to_string(this->getHealth());
	playerDetails =  playerDetails + "\nStamina: " + std::to_string(getStamina()) + "\n";
	playerDetails = playerDetails + getInventory() + "\nArmour in use: ";
	if(listOfArmourInUse_.size() == 0)
	{
		playerDetails = playerDetails + "none";
	}
	else
	{
		for(auto& a : listOfArmourInUse_)
		{
			if(a == listOfArmourInUse_.front())
			{
				playerDetails = playerDetails + a->getName();
			}
			else 
			{
				playerDetails = playerDetails + ", " + a->getName();
			}
		}
	}
	return playerDetails;
}
