/**
-i increased the size of the window
-create functions for some part of the code
-removed the 3rd spike
-create a sprite for each obstacles
and array that contain the sprites
-scaled down all the sprites
*/


#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include "blocky_data.h"//blocky header file
#include<iostream>
#include<windows.h>
#include<time.h>
#include<string>
using namespace std;
using namespace sf;


int main()
{
    //set seed for random function
    srand(time(0));

    //defines music
    Music mainMusic;

    //displays error if theme music file doesn't open
    if(!mainMusic.openFromFile("data/audio/game_music.wav"))
    {
        cout<<"Error loading file"<<endl;
        system("pause");
    }

    mainMusic.play();       //plays music
    mainMusic.setLoop(1);   //creates loop for music when it ends

    //defines sound buffer
    SoundBuffer jumpBuffer;

    //displays error if jump music file doesn't open
    if(!jumpBuffer.loadFromFile("data/audio/jump_music.wav")) {
        cout<<"Error loading file"<<endl;
        system("pause");
    }

    //defines sound for jumping
    Sound jumpSound;
    jumpSound.setBuffer(jumpBuffer);


    //calls menu function
    displayMenu(app);

    //theme music plays and loops when menu exits
    mainMusic.play();
    mainMusic.setLoop(1);

    bg_texture.loadFromFile("data/background_and_ground.png");//load the data
    spike_obstacle_texture_1.loadFromFile(spikes_collection[0]);
    spike_obstacle_texture_2.loadFromFile(spikes_collection[1]);
    block_obstacle_texture_1.loadFromFile(blocks_collection[0]);
    block_obstacle_texture_2.loadFromFile(blocks_collection[1]);


    //background sprite
    Sprite back_ground_first(bg_texture);//create sprites or characters
    back_ground_first.setPosition(0,0);//setting the background position
    Sprite back_ground_second(bg_texture);//second background
    back_ground_second.setPosition(1000,0);

    //box sprite
    Sprite box_sprite(box_texture);
    box_sprite.setPosition(70,350); //needs to move to the right
    box_sprite.setScale(0.8,0.8);
    //box_sprite.setColor(Color::Cyan);//set color

    //spike obstacle sprites
    Sprite spike_obstacle_sprite_1(spike_obstacle_texture_1);
    Sprite spike_obstacle_sprite_2(spike_obstacle_texture_2);
    spike_obstacle_sprite_1.setScale(1,1);
    spike_obstacle_sprite_2.setScale(1,1);
    spike_obstacle_sprite_1.setPosition((rand() % 4000)+1000,373);
    spike_obstacle_sprite_2.setPosition((rand() % 4000)+1000,373);

    //block obstacle sprites
    Sprite block_obstacle_sprite_1(block_obstacle_texture_1);
    Sprite block_obstacle_sprite_2(block_obstacle_texture_2);
    block_obstacle_sprite_1.setScale(0.7,0.7);
    block_obstacle_sprite_1.setPosition((rand() % 4000)+1000,345);
    block_obstacle_sprite_2.setScale(0.6,0.6);
    block_obstacle_sprite_2.setPosition((rand() % 400)+1000,335);

    //array of obstacle sprites
    Sprite obstacle_collection[4]= {block_obstacle_sprite_1,block_obstacle_sprite_2,spike_obstacle_sprite_1,spike_obstacle_sprite_2};

    bool jump = false;
    float velocity = -13;
    int pos_limit = 350;

    //keyboard
    Keyboard keyboard;

    //score
    int score_num=0;
    Font score_font;  //created font for score
    if(!score_font.loadFromFile("data/Pixeboy.ttf")) { //causes error if font file doesn't load
        cout<<"Error loading file"<<endl;
        system("pause");
    }
    Text score_text;   //creates text for score

    // Start the game loop
    while (app.isOpen())
    {

        // Process events
        Event event;
        while (app.pollEvent(event))
        {
            // Close window : exit
            if (event.type == Event::Closed)
                app.close();
        }

        if(keyboard.isKeyPressed(keyboard.Space))
        {
            jump = true;
            jumpSound.play();
        }

        if(jump)
        {
            velocity+=1.0;
            box_sprite.move(0,velocity*3.0);// jumping algorithm

            if(box_sprite.getPosition().y >pos_limit)
            {
                box_sprite.setPosition(70,350);
                jump = false;
                velocity = -13;
            }

            // jump on blocks
            if(box_sprite.getGlobalBounds().intersects(obstacle_collection[0].getGlobalBounds()))
            {
                box_sprite.setPosition(70,obstacle_collection[0].getPosition().y - 60);
                velocity=-13;
                jumpSound.play();
            }

        }

        //bug fix
        if(box_sprite.getPosition().y == obstacle_collection[0].getPosition().y - 60 && jump==false)
        {
            box_sprite.setPosition(70,350);
        }


          //game over
        /**1. sleep 2. display game over 3. get score and compare it to the high score, if true
         then display "congrats u beat the high score", then prompt user to enter name
         then write high score and name in file. else display prev highscore and name 4. if enter key pressed display menu again*/
        gameOver(app,box_sprite,obstacle_collection,score_num);


        //back ground
        spawnBackground(back_ground_first, back_ground_second);

        //obstacle
        spawnRandObst(obstacle_collection, score_num);

        //set score
        setScore(score_text,score_font,score_num);


        // Clear screen
        app.clear();

        // Draw the sprite
        app.draw(back_ground_first);
        app.draw(back_ground_second);
        for(int i=0; i<5; i++)//draw the obstacles
        {
            app.draw(obstacle_collection[i]);
        }
        app.draw(box_sprite);
        ///score
        app.draw(score_text);
        ///score end
        app.setVerticalSyncEnabled(true);//??
        app.setFramerateLimit(60);//fps(frame rate per second)


        // Update the window
        app.display();
    }
    return EXIT_SUCCESS;

}
