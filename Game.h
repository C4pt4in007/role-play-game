#ifndef GAME_H_
#define GAME_H_

#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <algorithm>
using std::string;

class Player; // forward declaration so that Object can refer to Player

// ------------------ Object and its subclasses -------------------

class Object {
public:

	// Constructor, specifying the name and the value of an object.
	Object(string name, int value);

	// Destructor
	~Object();

	// Return the name of the object.
	string getName() const;

	// Return the value of the object.
	int getValue() const;

	// Return a string giving details of the object, as specified in
	// the assignment webpage.
	virtual string print() const = 0;

private:
	// Use this object.
	// This function should not be public; it only makes sense to be
	// called from within a Player object (the player who owns it)
	virtual void use() = 0;

protected:
	// You probably want to have something like this.
	// For technical reason it may be easier to just use a raw pointer
	Player* owner_;

	// TODO: add any other protected/private member variables
private:
	string name_;
	int value_;

// Overloaded output stream redirection operator, printing the object to the
// given output stream
friend std::ostream& operator<<(std::ostream& os, const Object& o);

// You can "friend" other classes
friend Player;
};

class Food : public Object {
public:
	// Constructor
	Food(string name, int value);

	// Destructor
	~Food();
    
	// Add any member functions if needed
	// Return a string giving details of the object, as specified in
	// the assignment webpage.
	string print() const override;
	void use() override;
	
private:
	// Add any member variables if needed
};

class Weapon : public Object {
public:
	// Constructor
	Weapon(string name, int value);

	// Destructor
	~Weapon();

	// Add any member functions if needed
	string print() const override;
	void use() override;
private:
	// Add any member variables if needed
};

class Armour : public Object {
public:
	// Constructor
	Armour(string name, int value);

	// Destructor
	~Armour();

	// Add any member functions if needed
	string print() const override;
	void use() override;
private:
	// Add any member variables if needed

};

// ----------------- Player and its subclasses --------------------

class Player {
public:
	// Constructor, specifying the name of the player
	// Set the health and stamina both to 100
	Player(string name);

	// Destructor
	~Player();

	// Return the name of the player
	string getName() const;

	// Return the current health of the player
	int getHealth() const;

	// Return the current stamina of the player
	int getStamina() const;

	// Add the object pointed to by the unique pointer to the
	// inventory of objects this player carries.
	// As this is a unique pointer, it has to be "moved" into this
	// function using std::move().
	void pickup(std::unique_ptr<Object> obj);

	// Return a string listing all objects this player owns, in
	// the format specified in the assignment page
	string getInventory() const;

	// Return a string that contains all details of a player, as
	// specified in the assignment page
	virtual string print() const = 0;

	// Use the object with the given name. If the player does not
	// own any object of this name, return false and do nothing,
	// otherwise return true.
	bool use(string name);

protected:
	// TODO: add any protected or private member variables

private:
		string name_;
		int health_;
		int stamina_;
		std::vector<std::unique_ptr<Object>> listOfInventory_;
		Weapon* weaponInUse_;
		std::vector<Armour *> listOfArmourInUse_;
		
// Overloaded stream redirection operator, that prints the contents of
// the player to the given output stream
friend std::ostream& operator<<(std::ostream& os, const Player& p);

// You can "friend" other classes
friend class Fighter;
friend class Healer;
friend class Food;
friend class Weapon;
friend class Armour;
};

class Fighter : public Player {
public:
	// Constructor
	Fighter(string name);

	// Destructor
	~Fighter();

	// Attack the specified player, following the rules in the
	// assignment page
	bool attack(Player& other);

	// Add any other functions if needed

	// Return a string that contains all details of a player, as
	// specified in the assignment page
	string print() const override;

private:
	// add any member variables if needed

};

class Healer : public Player {
public:
	// Constructor
	Healer(string name);

	// Destructor
	~Healer();

	// Heal the specified player, following the rules in the
	// assignment page
	bool heal(Player& other);

	// Return a string that contains all details of a player, as
	// specified in the assignment page
	string print() const override;
private:
	// add any member variables if needed

};

#endif /* GAME_H_ */
