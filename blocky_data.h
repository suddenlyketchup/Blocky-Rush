///this is a header file for the blocky rush project
///extern is necessary in order for the variables to use them in blocky_data
#ifndef BLOCKY_DATA_H_INCLUDED
#define BLOCKY_DATA_H_INCLUDED

#include <SFML/Graphics.hpp>
using namespace sf;

// Create the main window
RenderWindow app(sf::VideoMode(1000, 600), "Blocky Rush");

//data collection
extern std::string spikes_collection[2];
extern std::string blocks_collection[2];

extern Texture bg_texture;//texture for background
extern Texture box_texture;//texture for the box
extern Texture spike_obstacle_texture_1;//texture for the spike obstacles
extern Texture spike_obstacle_texture_2;
extern Texture block_obstacle_texture_1;//texture for the block obstacles
extern Texture block_obstacle_texture_2;



//function declaration
int displayMenu(RenderWindow &); //display menu
int selectCharacters(RenderWindow &,Sprite); // display character selection menu
int gameOver(RenderWindow &, Sprite&, Sprite [], int &);// display gameover
void spawnBackground(Sprite &, Sprite &);//generate the background
void spawnRandObst(Sprite [4], int &);// generate random obstacles
void setScore(Text &, Font &, int &);

#endif // BLOCKY_DATA_H_INCLUDED
