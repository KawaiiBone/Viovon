# Viovon
Creating a game engine for school.
Where i have to make the Qbert game on.


It is an engine that focusses performance over memory by not needing to constantly create and delete objects.
All of the scenes are already loaded when starting the game, but only one gets updated and rendered at the time.
Each base component has a reset function which can be used to reset certain variables that you want.
The reset function will be activated by the object controlling the component.
You can also reset the whole scene which resets all objects in that scene. 

The gameobjects components work like this: you have a vector of basecomponents, rendercomponents and a pair which is base and rendercomponents.
The existence of the pair components is that the basecomponent can interact with the rendercomponent and not the other way around.

Example of a good use for the pair component is an for calculating frames per second. 
The basecomponent calculates the frames and rendercomponent renders it.

There is a scenemanager that controls all of the scenes, this allows it to go from scene to scene.
The scenemanager has an add player, which is handy for remembering and using the player characters in your code and scenes. 
