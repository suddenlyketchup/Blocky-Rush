#include<iostream>
#include<SFML/Graphics.hpp>
#include <fstream>
#include <windows.h>
using namespace std;
using namespace sf;

//data collection
string spikes_collection[2] = {"data/1_spike.png","data/2_spikes.png"};
string blocks_collection[2] = {"data/red_block.jpg","data/red_block_and_spike.png"};

Texture bg_texture;//texture for background
Texture box_texture;//texture for the box
Texture spike_obstacle_texture_1;//texture for the spike obstacles
Texture spike_obstacle_texture_2;
Texture block_obstacle_texture_1;//texture for the block obstacles
Texture block_obstacle_texture_2;

//function definition
int selectCharacters(RenderWindow &app, Sprite background) {

    //array of boxes
    string box_collection[7] = {"data/normal_box.jpg","data/blue_box.png","data/pink_box.png","data/red_box.png","data/orange_box.png","data/yellow_box.png","data/green_box.png"};


    Texture box_selection;  //created texture and sprite for box collection
    box_selection.loadFromFile(box_collection[0]);
    Sprite box_selection_sprite(box_selection);

    Font font;  //created font for texts
    if(!font.loadFromFile("data/Pixeboy.ttf")) { //causes error if font file doesn't load
        cout<<"Error loading file"<<endl;
        system("pause");
    }

    RectangleShape rectangle;   //creates selection rectangle to go around box characters
    rectangle.setSize(Vector2f (70,70));    //sets size of rectangle
    rectangle.setOutlineColor(Color::White);    //sets outline color of rectangle
    rectangle.setOutlineThickness(3);   //sets size of rectangle outline
    rectangle.setPosition(145, 295); //sets rectangle original position
    rectangle.setFillColor(Color::Transparent); //sets no color to the rectangle fill

    Text choose;    //creates text "choose"
    choose.setFont(font);   //sets previous font to this text
    choose.setString("CHOOSE YOUR CHARACTER");  //assigns to text variable
    choose.setCharacterSize(50);    //sets text size
    choose.setFillColor(Color::White);  //sets text fill color to white
    choose.setOutlineThickness(3);  //sets text outline size to 3 pixels
    choose.setOutlineColor(Color::Black);   //sets text outline color to black
    choose.setPosition(260,400);    //sets text position

    //index counter
    int box_counter = 0;

    //keyboard
    Keyboard keyboard;

    while (app.isOpen()) {

        // Process events
        Event event;
        while (app.pollEvent(event))
        {
            // Close window : exit
            if (event.type == Event::Closed)
                app.close();

            if (keyboard.isKeyPressed(keyboard.Right))
                {
                    //rectangle moves to the right if right key is pressed
                    rectangle.move(100, 0);
                    box_counter++;  //index counter increases by 1 for each press
                }

            else if (keyboard.isKeyPressed(keyboard.Left))
                    {
                        //rectangle moves to the left if right key is pressed
                        rectangle.move(-100, 0);
                        box_counter--;  //index counter decreases by 1 for each press
                    }

            else if(keyboard.isKeyPressed(keyboard.Enter))
                {
                    //cout<<keyboard.isKeyPressed(keyboard.Enter)<<endl;
                    box_texture.loadFromFile(box_collection[box_counter]);
                    //selects box when pressing enter
                    app.clear();
                    return 0;
                }
//looping
            if(rectangle.getPosition().x>745)
                {
                    rectangle.setPosition(145, 295);
                    box_counter=0;
                    //rectangle loops back original position if it passes the last box
                }

            if(rectangle.getPosition().x<145 )
                {
                    rectangle.setPosition(745, 295);
                    box_counter=6;
                    //rectangle loops back to last position if it passes the first box

                }
        }


        app.clear();    //clears screen
        app.draw(background);   //draws menu texture
        app.draw(choose);   //draws choose text
        for (int i=0,dist=150; i<7; i++, dist+=100)
        {   //loop to display each box
            box_selection.loadFromFile(box_collection[i]);
            box_selection_sprite.setTexture(box_selection);
            box_selection_sprite.setPosition(dist, 300);
            app.draw(box_selection_sprite);

        }

        app.draw(rectangle);    //draws rectangle

        app.display();


    }
    return EXIT_SUCCESS;
}


int displayMenu(RenderWindow &app)
{
    //creates texture for main menu
    Texture menu_texture;
    if(!menu_texture.loadFromFile("data/menu.png"))
    {
        cout<<"Error loading file"<<endl;
        system("pause");
    }

    //sets font from file
    Font font;
    if(!font.loadFromFile("data/Pixeboy.ttf"))
    {
        cout<<"Error loading file"<<endl;
        system("pause");
    }

    //sets title text with font
    Text text;
    text.setFont(font);
    text.setString("BLOCKY RUSH");
    text.setCharacterSize(100);
    text.setFillColor(Color::White);
    text.setOutlineColor(Color::Black);
    text.setOutlineThickness(5);
    text.setPosition(260,200);

    //sets prompt text
    Text play;
    play.setFont(font);
    play.setString("PRESS ENTER TO START THE GAME");
    play.setCharacterSize(25);
    play.setFillColor(Color::White);
    play.setPosition(340,400);

    //creates menu sprite
    Sprite menu_sprite (menu_texture);
    menu_sprite.setPosition (0,0);

    //keyboard
    Keyboard keyboard;

    while (app.isOpen()) {

        // Process events
        Event event;
        while (app.pollEvent(event))
        {
            // Close window : exit
            if (event.type == Event::Closed)
                app.close();
        }


        if (keyboard.isKeyPressed(keyboard.Enter))
        {
            //goes into characters function if user presses enter
            selectCharacters(app,menu_sprite);
            return 0;
        }

        app.clear();
        app.draw(menu_sprite);  //draw menu sprite
        app.draw(text); //draws title text
        app.draw(play); //draws prompt text
        app.display();
    }
    return EXIT_SUCCESS;
}

int gameOver(RenderWindow &app, Sprite &box, Sprite obst_collection[], int &score_num)
{
    //info structure
    int highscore;

    ifstream infile;
    infile.open("score.txt");
    Texture menu_texture;
    if(!menu_texture.loadFromFile("data/menu.png"))
        {
            cout<<"Error loading file"<<endl;
            system("pause");
        }

    Sprite menu_sprite (menu_texture);
    menu_sprite.setPosition (0,0);

    Font font;
    if(!font.loadFromFile("data/Pixeboy.ttf"))
    {
        cout<<"Error loading file"<<endl;
        system("pause");
    }


    Text text;
    text.setFont(font);
    text.setString("GAME   OVER!");
    text.setCharacterSize(100);
    text.setFillColor(Color::White);
    text.setOutlineColor(Color::Black);
    text.setOutlineThickness(5);
    text.setPosition(280,200);

     //player score
    Text player_score;
    player_score.setFont(font);
    player_score.setString("CURRENT SCORE: ");
    player_score.setCharacterSize(50);
    player_score.setFillColor(Color::White);
    player_score.setPosition(340,600);


    //player current score
    Text current_score;
    current_score.setFont(font);
    current_score.setString("DEFAULT");
    current_score.setCharacterSize(40);
    current_score.setFillColor(Color::White);
    current_score.setPosition(700,600);


    //sets prompt text
    Text play;
    play.setFont(font);
    play.setString("HIGH SCORE: ");
    play.setCharacterSize(50);
    play.setFillColor(Color::White);
    play.setPosition(340,400);

    //score
    Text score_text;
    score_text.setFont(font);
    score_text.setString("");
    score_text.setCharacterSize(40);
    score_text.setFillColor(Color::White);
    score_text.setPosition(700,400);


   /* //player score
    Text player_score;
    player_score.setFont(font);
    player_score.setString("CURRENT SCORE: ");
    player_score.setCharacterSize(50);
    player_score.setFillColor(Color::White);
    player_score.setPosition(340,600);


    //player current score
    Text current_score;
    current_score.setFont(font);
    current_score.setString("DEFAULT");
    current_score.setCharacterSize(40);
    current_score.setFillColor(Color::White);
    current_score.setPosition(700,600);*/

    Keyboard keyboard;

    for(int i=0; i<4; i++)
    {
        if(box.getGlobalBounds().intersects(obst_collection[i].getGlobalBounds()))
        {
            while(infile){
            infile>>highscore;
            }
            infile.close();


            if(score_num>highscore)
            {
                ofstream outfile;
                outfile.open("score.txt");
                outfile<<score_num<<endl;
                outfile.close();
                highscore=score_num;
            }
            score_text.setString(to_string(highscore));
            current_score.setString(to_string(score_num));


            while(app.isOpen())
           {

               if(Keyboard::isKeyPressed(keyboard.Enter))
               {
                   break;
               }
                app.clear();
                app.draw(menu_sprite);
                app.draw(text);//game over
                app.draw(play);//high score
                app.draw(score_text);//high score amount
                app.draw(player_score);//current score
                app.draw(current_score);//current score amount
                app.display();
           }

           displayMenu(app);//call displayMenu function
           score_num = 0;//set score to 0

           //set sprites position again
           box.setPosition(70,350);
           obst_collection[0].setPosition((rand() % 4000)+1000,345);
           obst_collection[1].setPosition((rand() % 4000)+1000,335);
           obst_collection[2].setPosition((rand() % 4000)+1000,373);
           obst_collection[3].setPosition((rand() % 4000)+1000,373);
           app.clear();
           break;
    }
}


    return EXIT_SUCCESS;
}


void spawnBackground(Sprite &bg_first, Sprite &bg_second)
{

//looping the background
        if(bg_second.getPosition().x == 0)
                bg_first.setPosition(1000,0);//looping the background

        if(bg_first.getPosition().x == 0)
                bg_second.setPosition(1000,0);//looping the background

        //moving the sprites
        bg_first.move(-5,0);
        bg_second.move(-5,0);

}


void spawnRandObst(Sprite obstacle_collection[4], int &score_num)
{
    /// generates random obstacles block, block with spike, spike 1 and spike 2 without touching eachother
    int pos_0 = (rand() % 4000)+1000, pos_1 = (rand()%4000) + 1000, pos_2 = (rand()%4000) + 1000, pos_3 = (rand()%4000) + 1000;//generate random number from 1000 - 4000

        if(obstacle_collection[0].getPosition().x + 80 < 0)
        {
            obstacle_collection[0].setPosition(pos_0, 345);//looping the block obstacle sprite

            for(int i=0; i<4; i++)
            {
                if(i==0)
                    continue;

                if(obstacle_collection[0].getGlobalBounds().intersects(obstacle_collection[i].getGlobalBounds()))
                {
                    obstacle_collection[0].setPosition(pos_0 + 500, 345);
                    break;
                }
            }

        score_num+=5;
        }


        if(obstacle_collection[1].getPosition().x + 111.35 < 0)
        {
            obstacle_collection[1].setPosition(pos_1, 335);//looping the block obstacle sprite

            for(int i=0; i<4; i++)
            {
                if(i==1)
                    continue;
                 if(obstacle_collection[1].getGlobalBounds().intersects(obstacle_collection[i].getGlobalBounds()) )
                    {   obstacle_collection[1].setPosition(pos_1 + 500, 335);
                        break;
                    }
            }
            score_num+=5;

        }


        if(obstacle_collection[2].getPosition().x + 33.8 < 0)
        {
            obstacle_collection[2].setPosition(pos_2, 373);//looping the obstacle sprite
            for(int i=0; i<4; i++)
            {
                if(i==2)
                    continue;
                 if(obstacle_collection[2].getGlobalBounds().intersects(obstacle_collection[i].getGlobalBounds()))
                    {   obstacle_collection[2].setPosition(pos_2 + 500, 373);
                        break;
                    }
            }
            score_num+=5;
        }


        if(obstacle_collection[3].getPosition().x + 78 < 0)
        {
            obstacle_collection[3].setPosition(pos_3, 373);//looping the obstacle sprite

            for(int i=0; i<4; i++)
            {
                if(i==3)
                    continue;
                 if(obstacle_collection[3].getGlobalBounds().intersects(obstacle_collection[i].getGlobalBounds()))
                    {   obstacle_collection[3].setPosition(pos_3 + 500, 373);
                        break;
                    }
            }
            score_num+=5;
        }

    for(int i=0; i<4; i++)
    {
         obstacle_collection[i].move(-10,0);
    }

}

void setScore(Text &score, Font &font, int &score_num)
{
    score.setFont(font);   //sets previous font to this text
    score.setString(to_string(score_num));  //assigns to text variable
    score.setCharacterSize(50);    //sets text size
    score.setFillColor(Color::White);  //sets text fill color to white
    score.setOutlineThickness(3);  //sets text outline size to 3 pixels
    score.setOutlineColor(Color::Black);   //sets text outline color to black
    score.setPosition(850,30);    //sets text position
}
