Note: - This was a college assignment and the problem was given to us by professor. I do not take any credit in creating this problem, we were given a base structure of the project,
So, I had to only write code inside Game.h and Game.cpp which had empty constructor & empty function definitions. The test suit GameTester GameTesterMain was already developed.

# role-play-game
You are the most junior programmer in a development team, whose task is to develop some type of role-play game. Your team leader hasn't decided the details of the game yet, but you are tasked with developing some C++ classes to model some entities (namely players and objects) and their basic interactions, as described below. It is not a full game and most of the actual game logic are not being implemented here.

Your team leader hasn't really played much computer games, so some of the requirements below may seem too simplistic or just outright weird. Also, you may find some design decisions that you are asked to follow to be rather odd. It is almost like your team leader wants to test your knowledge on inheritance and virtual functions for some reason...

A number of different classes are used to model different "objects" and "players" of the game. The class hierarchy is as shown in this diagram:

          Object                             Player
            |                                  |
  -------------------------             -----------------
  |       |        |      |             |        |      |
Food    Weapon   Armour   ...         Fighter  Healer  ...

Again, since your team leader has not made up their mind on what exactly will be in the game, there may be some further types of objects or players to be added in the future (though not in this assignment).

The Object class
The Object class represent objects in the game that can be "picked up" and "used" by players, such as food, weapon, armour etc. All objects have a name (a string) and a value (a non-negative integer). Objects are assumed to have unique names. The meaning of "value" is different depending on what subtype of object it is.

In addition, you probably want each object to "know" who has picked it up, and therefore it probably should have a pointer that points to the "owner" of the object. Initially an object does not have any owner, and it can only be owned by one player (the one who picked it up via the pickup() function of the Player class).

The Object class is a base class and should be abstract (no object of this class should be instantiated). Nevertheless, it has a constructor:

Object(string name, int value)
Constructor with parameters specifying the name of the object and its value. The value must not be negative, otherwise the constructor should throw a std::invalid_argument exception. It should also initialise the object to have no owner (for example by setting the owner_ pointer to nullptr).
Furthermore, the Object class (and all its subclasses) should support the following functions:

string getName()
Return the name of the object.

int getValue()
Return the value of the object.

string print()
Return a string that has the following contents:
XXX, name: YYY, value: ZZZ
where XXX is the type of the object (so one of Food, Weapon or Armour, so far), YYY is the name of the object and ZZZ is its value. Here are three examples:
Food, name: apple, value: 5

Weapon, name: sword, value: 20

Armour, name: helmet, value: 10
(In this and all other similar functions that return a string to give a description of an object, you must have the exact whitespaces as shown, otherwise you will not pass the test cases. All whitespaces you see here are the single space character (' '). Please be careful not to include any extra invisible whitespaces. In the case of multi-line strings, the lines should be separated by inserting a '\n' character, but there should be no '\n' after the final line. All these functions return a string, or write something to the given output stream; the functions themselves do not print anything to the screen directly.)

void use()
Apply the effect of that object to the player who currently owns them. The effect depends on what type of object it is, as specified in the subclasses below. This should not be a public member function; it should only be accessed by the Player class (and its subclasses). See the use() function in the Player section.

ostream& operator<<(ostream& os, const Object& o):
Overloaded output stream redirection operator, to be implemented as a friend function (not a member function) of the Object class. It prints the content of the given object, as returned by the print() function, to the specified output stream.
The Food class
In addition to those inherited from the parent class, all Food objects should support the following operation:

Food(string name, int value)
Constructor of a food item, specifying its name and value.

void use()
Using a food object increases the owner's stamina by the value of the object, but is capped at the maximum stamina of 100. For example, if a player has stamina 80 and uses a food item of value 10, the stamina becomes 90. But if the food item has value 25 instead, the stamina becomes 100 (not 105). A food item once used is "consumed" and will no longer be in the player's list of items.
The Weapon class
In addition to those inherited from the parent class, all Weapon objects should support the following functions:

Weapon(string name, int value)
Constructor of a weapon, specifying its name and value.

void use()
Using a weapon means it is listed under the "weapon in use" of its owner (see the print() function of the Player class), and it affects the attacking strength of the player (see the attack() function of the Fighter class).

Only one weapon can be in use at any time. If this function is called while the player is already using another weapon, the old weapon will be "unloaded" and the new weapon takes its place as the "weapon in use". The old weapon remains in the player's possession (and the player may choose to use it again later). A weapon once in use will remain in use until it is replaced by another weapon.
As you will see in the Fighter section, only fighters can attack, and therefore really make use of a weapon. Nevertheless, any player type can use the pickup() and use() functions to pick up and indeed "use" weapons, but if they don't have an attack() function it is pointless for them to do so.

The Armour class
In addition to those inherited from the parent class, all Armour objects should support the following functions:

Armour(string name, int value)
Constructor, specifying the name and value of this piece of armour.

void use()
Using an armour means it is listed under the "armour in use" of its owner (see the print() function of the Player class), and it affects the defending strength of the player (see the attack() function of the Fighter class).

Unlike weapons, players can use multiple armour items at the same time. A call to this function will add this armour to the list of armour "in use" by this player. An armour once used will continue to be in use forever.

#The Player class hierarchy

The Player class
The Player class models a player in the game. Each player has a health value and a stamina value; both are integers between 0 and 100. They may also carry a number of objects with them, which (as you will see below) you probably want to represent as a collection of unique pointers. Each player may, at any one moment, have a "weapon in use" and/or a number of "armour in use".

If a player's health drops to 0, they are dead. Dead players can no longer take any action and are supposed to be "removed" from the game somehow, but once again your team leader hasn't figured out what to do with them yet, so in the following a player may be dead but still around, and some special action needs to be taken about them.

The Player class is a base class and should be abstract (no object of this class should be instantiated). Nevertheless, it has a constructor:

Player(string name)
Constructor with parameter specifying the name of the player. It should also initialise its health and stamina to 100, and to have an empty list of items. It is therefore not using any weapon or armour.
Furthermore, the Player class (and all its subclasses) should support the following functions:

string getName()
Return the name of this player.

int getHealth()
Return the health value of this player.

int getStamina()
Return the stamina value of this player.

void pickup(unique_ptr<Object> p)
Add the object pointed to by the specified unique pointer to the list of items of this player. The object is represented by a unique pointer with the intention being that once it is picked up by one player, it cannot be picked up by another player. As a result, it is to be passed into this function with the std::move() function like this:

unique_ptr<Food> apple = make_unique<Food>("apple", 5);
Fighter alice("alice");
alice.pickup(std::move(apple));
and you probably would want to use the same mechanism to "move" the incoming pointer to some data structure that stores all pointers to objects this player currently has.

If the player is already dead, throw a std::logic_error exception and do not do any of the above.

bool use(string name)
"Use" the item with the specified name. Depending on what type of item it is, its effect of being used is different. Essentially you should call the use() function of that object and let it do its job.

If the player is already dead, throw a std::logic_error exception and do not do anything. If the player does not currently possess an item of that name, return false (and do nothing else). Otherwise (the item is successfully used), return true.

string getInventory()
Return a string listing all the items the player currently possesses, in precisely the following format:

List of items:
 Food, name: xxx, value: xx
 Weapon, name: xxx, value: xx
 ...
where each line prints the details of an object exactly as in the print() function of the Object class, but with one extra space character in front.

The items must be listed in the order they were picked up.

If there are no items, the one-line string "List of items: none" should be returned instead.

Any weapon/armour that are added as "in use" by the use() function continue to appear under this list of items. Likewise any weapon "unloaded" (replaced by another weapon as "in use") is also listed here.

string print()
Return a string that prints all information about the player, in exactly the following format:
Name: xxx
Type: xxx
Health: xx
Stamina: xx
List of items:
 xxx, name: xxx, value: xx
 xxx, name: xxx, value: xx
Weapon in use: xxx
Armour in use: xxx, xxx
It should be clear what most of this means. The type is either Fighter or Healer. The "List of items" is exactly the output produced by getInventory(). The weapon/armour in use states the names of the weapon/armour. If no weapon/armour is in use, it should say "none" in place of the xxx. Multiple armours in use should be listed in the order they were first "used".

The line "weapon in use" should not appear for healers, since they cannot attack, even though theoretically they can pickup and "use" weapons.

ostream& operator<<(ostream& os, const Player& p)
Overloaded output stream redirection operator, to be implemented as a friend function (not a member function) of the Player class. It prints the contents of the given player, as returned by the print() function, to the specified output stream.
