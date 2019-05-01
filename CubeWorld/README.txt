Current implementation for Rustsplinter (Cubeworld) as of 4/17/2019

Current status: Midway through handling how attacks work, changing from flat "you do x damage with this weapon" to being based on velocity at the time of impact


Made by Zackery Mason
Available at (and probably downloaded from) ZackeryMason.com



The current code is unplayable except in the debugger made specifically for my version of eclipse with the GDC plugin: aka, it won't work when you try to run it.
This is here solely to get a glimpse of my code in all its unholy, barely commented glory.
This was done by a single person, and wasn't exactly done in the mindset of being "user friendly" for other group members,
But it certainly could be if the need presented itself.
I know the code inside and out, so most of the comments are just little notes / reminders / suggestions to myself


This game engine is derived from the code for Trick of the Light (Gridworld), which I refactored to become "3d" from a 2d system, and some previous implementations aren't finished yet.
That means there are a few commented out functions in World.h and other places that should / will be in but aren't a priority yet.


The general game is described on the website, but heres a few specifics about the classes and how they work / interact:
Setting up starting characters / blocks to see how they interact is done in CubeWorld.cpp with a simple string editor for now.
Game loop / startup / entity handling is done in World.cpp
The few interactable game objects are in Entities folder.
--- Blocks are just the platforms things stand on for now. They handle collision detection between tiles in a very complicated way.
------ Simplification: Every block is a cube. Edges can be sharp preventing diagonal movement. Centers can be solid or passable to imply its used as a ramp or ladder upwards.
--- Items are any kind of object that exist, such as legs, rocks, swords, etc
------ Items can be attached to one another, forming large blob connection systems in a linked list kind of fashion
--------- They can also act as armor to eachother: a low health heart usually is armored by the body it's inside that blocks incoming damage
--------- There are other semi-connections as well: grabbing, being stored in something, embedding something into something else, that all keep things part of the same "item blob" and move together
------ Items carry their own set of possible actions with them: hands have the ability to grab, guns have an action to shoot / reload, etc
-------- Some actions are just something "taught" to the owner: a spellbook may have an action to cast a fireball, but require the user is holding a magic staff in another hand and thus can't be cast alone
--- Units are abstract clusters of objects that think and act independantly from eachother
------ A typical "human" unit may contain leg, hand, body and head objects, each of which are different items attached together
--------- A spider may be 8 legs and a body, a robot may be mechanical parts put together, etc
------ Units have tasks they try to accomplish, such as wandering around or attacking nearby enemies
--------- They cycle through their items looking for what actions are available to them, and work with what they have
------ Units don't have typical "HP", but instead live or die based on what happens to their item bodies
--------- Destroying the brain = instant death, but typically limbs can be injured to the point bloodloss or other permanent damage renders the unit immobile and useless
Gravity physics is handled in Physics/Gravity.cpp
--- If things don't have functioning wings, they fall towards the ground.
--- Colliding with other things does damage, transfers some of the gravity between them and handles friction
------ Things skid as they fly across the floor, rebound off walls, and hitting another mobile item makes them both fly away from eachother after handling collision damage
Status effects are in Stati (currently just a levitation effect)
--- Can be applied to specific item parts (Poison injected into an arm), can be encompassing of the whole connected blob (A spreading fire expanding from limb to limb), or may effect a unit personally without being connected to his item parts (A mind control spell)


Some of the better / cooler code examples at the moment are: World::intRaycastHit/Path, World::starPath, World::moveUnit, Item::attach, Item::sever, Item::damage, Item::getBlob, Unit::canWalk
I could go on for hours about the intricacies of designing / implimenting them, explanations about decision making and debugging, expected use cases and imagined scenarios. 

Questions / comments / concerns / suggestions / death threats? Want to see more or get updates? Is there something apparantly wrong I don't seem to notice?
Send it all to Z.Mason333@gmail.com. It will make my day to get feedback
