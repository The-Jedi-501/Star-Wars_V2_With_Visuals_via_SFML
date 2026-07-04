/* 
=============================================================
STAR WARS: FLEET BUILDER AND BATTLES V2 WITH A VISUAL/MAP ASPECT TO IT 
=============================================================

AUTHOR: Christopher DeMoura
Language: C++
Purpose: Create a project that allows me to better understand part of my current research for UUV and to apply those new skill and code to a personal project
        -Also anther big idea is to take a project i had and to further practice code (inheritiance, polymorphism) as well as UI architecture via SFML 
        -A UI articture overall is something I wanted to mess around with as it seems more interesting to have a visual aspect rather than just a code this terminal that 
        -My MAIN thing i want future code to do is to incorpate bare minumum one new thing to get me out of my comfort zone to build something wher i can look at it later and say "YEA I DID THAT"


Code walkthrough and Goals: 
First use alot of the code aspects I had created from the first star wars battle:
    -Main idea is to essentially be given a list of ships adn user is prompted to pick 3 ships followed by picking to either randomize or select the opponents ships (Note the reason why the stats if you will are the same was for simplicty and essnelly Republic vs Seperatist iconic vehicles)
    -After slecting "ship" they get stored into a vector for both player and enemey, now battle commences you take turns selecting your you want use and then the ship you wish to attack, a damage report will 
    -the enemy will do the same via a randomizer functon to keep it beign very different, once either a player or enemys ships are depleted (vecotrs are empty) you either win or lose
Second half that all new:
    -I want to have a visual aspect think window pops up and you see your ships adn enemy ships and rather than just a terminal game you can select arc-170 and fight vulture droid (mentally i think of it like a pokemon battle)
    -Can I let say arc-170 be a image of an arc-170 and do all this for each ship essenttially 
    -any way i could do this for multiple aspect ie set a background 
    -Could i do graphis ie when attacking arc-170 moves forward shoet then circles back and add the defesne shioled maechanci i wanted orignally 
-Please note there is alot of comments most are just notes I made along the way as you will see to either explain how a new piece of code worked or to show a new implemtentaion i had found that i found interesting and wanted to implement

Code topics used here and the purpose they served:
Classes --- Used to create the various "ships for the fleets (game mechanic)" which are just objects
Vectors --- A place in which needed to store information ie those objects themselves (vector a has ship 1 with all of its stats as well as ship 2 and its information)
Functions --- Used for repetive large chunks of code
BST --- Binary Search tree in the form of map reason for this over unordered map ie hash table was due to BST allowing a clean organized display
Randomizer --- Whilst not necessary from my lessons learnt was important for the code itself as well as the implementation itself
Basic Code functions (Loops, condiotional, variables, etc.) --- Its used literally everywhere 

 To build and run:
 cd "/mnt/c/Users/chris/Desktop/VS Code/C++ learnign/Projects/Star Wars Fleet V2 with visuals"

    rm -rf build    This is to clean up so no mess ups 
    mkdir build
    cd build
    cmake ..
    make            After you save changes you dont need to keep doing the above stuff just this line and whats below
    cd ..
    ./build/NAME OF PROGRAM     This program just do ./SW_V2

    alternaively coudl just run 
    ./run.sh

    cd build && make

Things to note for images i needed a assets folder just so i can have all the images of the backgrounds for this as well as ships and some other graphics
following dans code let main cpp sit in src 

## Assets
Background images sourced from Google Images / fan art communities.
All images are property of their respective owners (Lucasfilm/Disney).
This project is non-commercial and for educational purposes only.
I just like star wars and wanted to make a fun cool project to add to my collection 

//To get pictures just googled what i wanted them ships png becuase its got that cut out background if it was a fake and said it but donest do it just send to paing then save as png and then accomadate those picture chages where you see fit ie change background picutre or ships themselves 

Note this code will probably be a mess since im using the old code as refernce and then changing it so it fits into uui along side this there will be alot of comments so that for future refernce if i decide to do more SFML and if anyone views this code it hopefully makes more sense as this doesnt come natually to write and has alot of parts
*/



#include <iostream>
#include <vector> 
#include <unordered_map>
#include <map>
#include <random> //This is the new way 

#include <SFML/Graphics.hpp> // This library is all about grpahics we have seen this in the UUV research code project 

class Ship {
    public: //??? THIS MEANS will be modified view the code and or users later on 

        Ship(const int &current_pos, const std::string &name, const int &attack, const int &defense, const std::string &faction) { //THIS IS A CONSTRUCTO 
            this->current_pos = current_pos;
            this->name = name;
            this->attack = attack;
            this->defense = defense;
            this->faction = faction;
        }

        Ship() {//DO NOT DELETE THIS ITS A DUMB THING WHERE IT NEEDS A DEFAULT EVEN THOUGH I AM LITERLALLY NEVER USING IT 
            this->current_pos = 0;
            this->name = "";
            this->attack = 0;
            this->defense = 0;
            this->faction = "";
        }

//this section mostly stripped from dan code just so i didnt have to rewrite
        int getCurrent_Pos() const {
            return this->current_pos;
        }

        std::string getName() const {
            return this->name;
        }
 
        int getAttack() const {
            return this->attack;
        }
 
        int getDefense() const {
            return this->defense;
        }

        std::string getFaction() const {
            return this->faction;
        }
 
        // These are setters 
        void setCurrent_Pos(const int &newCurrent_Pos) {
            this->current_pos = newCurrent_Pos;
        }

        void setName(const std::string &newName) {
            this->name = newName;
        }
 
        void setAttack(const int &newAttack) {
            this->attack = newAttack;
        }
 
        void setDefense(const int &newDefense) {
            this->defense = newDefense;
        }

        void setFaction(const std::string &newFaction) {
            this->faction = newFaction;
        }

    private: // THIS MEANS user cannot modify 
        int current_pos;
        std::string name;
        int attack;
        int defense;
        std::string faction;

};

void print_hangars(const std::vector<Ship>& hangar){ //YEA I REALIZED THAT I DIDNT NEED TO KEEP DOING << FOR COLORS THEN TO NEXT IT CAN TECHNICALLY ALL BE DONE  IN ONE LINE WOUDL HAVE BEEN NICE LEARNT THAT ON THE LAST COLOR GREAT IF STRING BUT FOR .GET NAME CANT 
    for (int i = 0; i < hangar.size(); i++) {
        std::cout << i+1 << ')' << " Name of ship: " << "\033[35m" << hangar[i].getName() << "\033[0m" << '\n';
        std::cout << '\t' << '\t' << "-Attack Power:  " << "\033[31m" << hangar[i].getAttack() << "\033[0m" <<'\n';
        std::cout << '\t' << '\t' << "-Defense Power: " << "\033[34m" << hangar[i].getDefense() << "\033[0m"<< '\n';
        std::cout << '\t' << '\t' << "-Faction:       " << hangar[i].getFaction() << '\n';
        std::cout << '\n';
    }
    std::cout << std::string(60, '=') << '\n'; //lazy me syaing hey put = down 60 times can update accordingly --- same as std:coud << "==================";
}

void Pick_Ships (std::vector<Ship>& hangar, std::map<int, Ship>& ShipDataBase, int max){// NOT const for the hangar since we are modifyign it rest not 
    int counter = 0;
    int ship_count = 3;
    
    while (counter < max){
        std::cout << "You have this many more Ships you can select from: " << ship_count << ", Pick your ships Captain, please tell me the number you want the correspond to the ships you just looked at: ";
            int choices;
            std::cin >> choices;

            while (!ShipDataBase.count(choices)) {  // keeps looping if invalid
                std::cout << "Invalid, pick 1-6: ";
                std::cin >> choices;
            }
    //UPDATE TO NEWEST VERION OF CPP CASUE I CANT USE .CONTAINS WOUDL HAVE BEEN PERFECT CASUE IT LITEALLY CHECK THE HASH IF IT EXSIT OR COANTIS THAT VALUE 
            hangar.push_back(ShipDataBase[choices]);//Yo since my choice "LAAT" exitst --- add this to my vector (push.back) whjich was (my hangar)
            counter++;
            ship_count--;
            std::cout << '\n';
    }
    std::cout << std::string(60, '=') << '\n'; //lazy me syaing hey put = down 60 times can update accordingly --- same as std:coud << "==================";
}


void Rand_Ships (std::vector<Ship>& hangar, std::map<int, Ship>& ShipDataBase, int max, std::mt19937& gen, std::uniform_int_distribution<int>&distrib){
    int new_counter = 0;
    while(new_counter < max){
        
        int rand_num = distrib(gen);                      // same job as rand() — generates the number

        if(ShipDataBase.count(rand_num)){
            hangar.push_back(ShipDataBase[rand_num]);//Yo since my choice "LAAT" exitst --- add this to my vector (push.back) whjich was (my hangar)
        }
        new_counter++;
    }
}

void damage_report (const Ship& attacker, const Ship& defender, int damage, int defense_before) {
    std::cout << std::string(60, '=') << '\n'; //lazy me syaing hey put = down 60 times can update accordingly --- same as std:coud << "==================";
        std::cout << "DAMAGE REPORT:\n";
        std::cout << "\033[35m" << attacker.getName() << "\033[0m" << " attacked " << "\033[35m" << defender.getName() << "\033[0m"<< '\n';
        std::cout << "Damage Inflicted: " << "\033[31m" << damage << "\033[0m" << '\n';
        std::cout << "\033[35m" << defender.getName() << "\033[0m" << " defense: " << "\033[34m" << defense_before << "\033[0m" << " --> " << "\033[34m" << defender.getDefense() << "\033[0m" << '\n';

}

void destroyed_in_battle(std::vector<Ship>& hangar, int position){

    if (hangar[position].getDefense() <= 0) {
            std::cout << "\033[35m"  << hangar[position].getName() << "\033[0m" << " destroyed!\n";
            hangar.erase(hangar.begin() + (position));
        }

}


enum class GameState { //Were using a class to show the different screens --- enum is essentlly us having one active "GameState" at a time think Red Yellow and Green lights you will only have one at a time 
    TITLE,       // showing title + play button
    SHIP_SELECT, // picking ships screen
    ENEMY_TEAM_COMP, // For enemy comp i wnaa screen taht says to either randomize or select two "buttons" same logic as ships rancomize does logic from og code vs selct is just last screen  
    BATTLE       // the actual fight
};

GameState state = GameState::TITLE; // start on title screen and the syntax important saying the current state = Gamestate::the screen in question

//struct each Ships card ie all its contents (picture = sprite, name, stats, the box stuff is imporatant due to different sides ie Red/Blue or Sepratist/Republic logic, the key is refering to the hash I perfrom later that has all this essnlly takign teh hash i did from original code so it has all the info ther an then hen i call upon it alter its easy to jsut use.getDefense for example )
    struct ShipCard {
        sf::Sprite sprite;
        sf::Text nameText;
        sf::Text statsText;
        sf::RectangleShape box;
        sf::RectangleShape glow;
        bool hovered = false;
        int shipKey;

        // constructor — every member needs to exist when the card is created think of this as the blueprint for all things that will be passed inside which is the image/sprite, were passing the font since were using the SFML library and we want to say create an object in whcih will use this font to draw itself later, and key which is the hash of which derives from the ShipDataBase 
        ShipCard(sf::Texture& tex, sf::Font& font, int key)
            : sprite(tex), nameText(font), statsText(font), shipKey(key) {}
    };



int main(){

// --- WINDOW -----------------------------------------------
    sf::RenderWindow window( //This is like the im about to use the window function if you will 
        sf::VideoMode({1280, 720}), //set the resoltion ---  DO NOT TOUCH THIS AT ALL THERE ARE ALOT OF VALUES YOU WOULD HAVE TO CHANGE YES I PROPABLY SHOULD HAVE DONE VARIBALES BUT TOO LATE
        std::string("Star Wars Battle") //this is the name at the top of the window looks like
    );

// --- BACKGROUND ---------------------------------------
    //Background for main menu 
    sf::Texture bgTexture; // notice anytime we do anythign visual we do sf:: think same as std:: --- this line also declares a texture ie an image will be sitting here 
    if (!bgTexture.loadFromFile("assets/backgrounds/BattleOverCoruscant.png")) {//read the image in this case its located in a folder and everything is named to tell where it is and loads that into bgTexture adn the whole if(! ) is just a check i fpath is wrong 
        std::cerr << "Failed to load background\n";
        return -1;  // exit program immediatelyy because theres no point in contuning since i want my background
    }
    std::cerr << "Background loaded OK\n"; // add this temporarily

    sf::Sprite background(bgTexture); //This is us taking that texture and turning it into a sprite which is just picture 
    background.setScale(sf::Vector2f( //this is the "math" behind the background hence set scale --- If image is 1920 wide and window is 1280, scale = 1280/1920 = 0.667 — shrinks it to fit. Same logic for height. --- cool math logic --- sf::Vector2f is just a container holding 2 floats 
        1280.f / bgTexture.getSize().x, //take that image regardless of size and fit to the scale/resolution of the window we chose above in the sf::VideoMode({1280, 720}) all about x axis 
        720.f / bgTexture.getSize().y //Same as above but for y axis 
    ));

    //Background for the ship select 
    sf::Texture ShipSelectTexture;
    if (!ShipSelectTexture.loadFromFile("assets/backgrounds/Space.jpg")) {
        std::cerr << "Failed to load background\n";
        return -1;  // bail out, nothing works without this
    }
    std::cerr << "Background loaded OK\n"; // add this temporarily

    sf::Sprite ShipSelectPic(ShipSelectTexture);
    ShipSelectPic.setScale(sf::Vector2f(
        1280.f / ShipSelectTexture.getSize().x,
        720.f / ShipSelectTexture.getSize().y
    ));

// --- FONT + TEXT goes here, before the loop ---------------------
    //Font
    sf::Font font; //Same sort code as we do for background and safety checks 
    if (!font.openFromFile("assets/fonts/StarWarsFont.ttf")) {
        std::cerr << "Failed to load font\n";
        return -1;
    }
//Text for main menu 
    sf::Text title(font); // think for the title i want all this stuff included (text itselt, font size, color whcih can be code or name the bounds is also important read below)
    title.setString("Star Wars Fleet Battles");
    title.setCharacterSize(36); //font size 
    title.setFillColor(sf::Color::Yellow);
    sf::FloatRect textBounds = title.getLocalBounds(); //How wide and tall is this object??? that wher elocal bound solves 
    title.setOrigin(sf::Vector2f(textBounds.size.x / 2.f, textBounds.size.y / 2.f)); //set origin moves the "anchor point" to its one center rather than top left corner --- think when we move it do we want to "grab via middle or corner"
    title.setPosition(sf::Vector2f(640.f, 60.f)); //setPosition puts the cento of the text at 640 rather than left edge 

//Text for Hangar
    sf::Text hangar_txt(font);
    hangar_txt.setString("Please Select You Ship");
    hangar_txt.setCharacterSize(28); //font size 
    hangar_txt.setFillColor(sf::Color::White);
    sf::FloatRect hangartextBounds = hangar_txt.getLocalBounds();
    hangar_txt.setOrigin(sf::Vector2f(hangartextBounds.size.x / 2.f, hangartextBounds.size.y / 2.f));
    hangar_txt.setPosition(sf::Vector2f(640.f, 60.f)); //so this says to postion it half of the resoltion os in a 640x480 640/2=320 adn the y is something ill have to mess around with 


    int RemainingShipToSelect = 3; // this varibale is used in game loop

    sf::Text hangar_Ship_Select_txt(font);
    hangar_Ship_Select_txt.setCharacterSize(20);
    hangar_Ship_Select_txt.setFillColor(sf::Color::Red);
    hangar_Ship_Select_txt.setPosition({640.f, 100.f}); 
    

    //Text for Enemy Selction of team compostion 
    sf::Text Enemy_Selection_Comp_txt(font);
    Enemy_Selection_Comp_txt.setString("How would you like to select you opponents");
    Enemy_Selection_Comp_txt.setCharacterSize(28); //font size 
    Enemy_Selection_Comp_txt.setFillColor(sf::Color::White);
    sf::FloatRect Enemy_Select_Comp_textBounds = Enemy_Selection_Comp_txt.getLocalBounds();
    Enemy_Selection_Comp_txt.setOrigin(sf::Vector2f(Enemy_Select_Comp_textBounds.size.x / 2.f, Enemy_Select_Comp_textBounds.size.y / 2.f));
    Enemy_Selection_Comp_txt.setPosition(sf::Vector2f(640.f, 60.f)); //so this says to postion it half of the resoltion os in a 640x480 640/2=320 adn the y is something ill have to mess around with 


//- WE GOT THE STATS----------------

    //HASH'S SOLE PURPOSE IS TO LOOK UP VIA KEY TAHTS IT 
    std::map<int, Ship> ShipDataBase; //So this shoudl input the number from designated ship (LAAT is 1 bc 1)) and then wodul go to the class its
    ShipDataBase[1] = Ship(1, "V Wing", 300, 100, "Republic"); // Dps -- High attak low def
    ShipDataBase[2] = Ship(2, "ARC 170", 150, 150, "Republic"); // med -- med 
    ShipDataBase[3] = Ship(3, "Y Wing", 100, 300, "Republic"); // Tank -- high def low attk

    ShipDataBase[4] = Ship(4, "Droid Tri-Fighter", 300, 100, "Seperatist");
    ShipDataBase[5] = Ship(5, "Vulture Droid", 150, 150, "Seperatist");
    ShipDataBase[6] = Ship(6, "Hyena Class Droid-bomber", 100, 300, "Seperatist");


    
// -- Ships ------------------------------------
    
    sf::Texture shipTextures[6];
    shipTextures[0].loadFromFile("assets/ships/V-Wing.png");
    shipTextures[1].loadFromFile("assets/ships/arc-170.png");
    shipTextures[2].loadFromFile("assets/ships/Y-Wing.png");
    shipTextures[3].loadFromFile("assets/ships/Tri Fighter.png");
    shipTextures[4].loadFromFile("assets/ships/Vulture_Droid.png");
    shipTextures[5].loadFromFile("assets/ships/Hyena-Bomber.png");

    // build 6 cards — keys 1-6 match your ShipDataBase keys
    std::vector<ShipCard> cards;
    for (int i = 0; i < 6; i++) {
        cards.push_back(ShipCard(shipTextures[i], font, i + 1));
    }
//DONT UNDERSTAND NGL
    // positions — row 1 = Republic (y=100), row 2 = Separatist (y=280)
    float cardX[3] = {150.f, 565.f, 980.f};  // spread across 1280 --- we need to do 1280/3 and then kinda jsut move everythign over so it looks nice no real idea on math here 
    for (int i = 0; i < 6; i++) {
        float x = cardX[i % 3];
        float y = (i < 3) ? 150.f : 400.f;        // spread across 720 --- we can use ? and : as Ternary operators whcih are is essnallyu if else --- I needed ai for this and holy is it cool 
/*--- OMG thats the same as the main idea is to essentally plac them on the y axis ie row i want and the i<3 is for the hwo many per row 
        float y;
        if (i < 3) {
            y = 100.f;
        } else {
            y = 280.f;
        }*/

        cards[i].sprite.setScale(sf::Vector2f(
            150.f / shipTextures[i].getSize().x,
            100.f / shipTextures[i].getSize().y
        ));
        cards[i].sprite.setPosition(sf::Vector2f(x, y));

        cards[i].box.setSize(sf::Vector2f(190.f, 140.f));
        cards[i].box.setPosition(sf::Vector2f(x - 5.f, y - 5.f));
        cards[i].box.setFillColor(sf::Color::Transparent);
        cards[i].box.setOutlineThickness(3.f);
        if (cards[i].shipKey <= 3) {
            cards[i].box.setOutlineColor(sf::Color(80, 150, 255)); // blue for Republic
        } 
        else {
            cards[i].box.setOutlineColor(sf::Color(255, 80, 80));  // red for Separatist
        }

        cards[i].glow.setSize(sf::Vector2f(200.f, 160.f));
        cards[i].glow.setPosition(sf::Vector2f(x - 20.f, y - 20.f));
        cards[i].glow.setFillColor(sf::Color::Transparent);


        cards[i].nameText.setCharacterSize(14);
        cards[i].nameText.setFillColor(sf::Color::Green);
        cards[i].nameText.setPosition(sf::Vector2f(x, y + 105.f)); // below the bigger 300x200 sprite now
        cards[i].nameText.setString(ShipDataBase[cards[i].shipKey].getName());

        cards[i].statsText.setCharacterSize(12);
        cards[i].statsText.setFillColor(sf::Color::Yellow);
        cards[i].statsText.setPosition(sf::Vector2f(x, y + 130.f)); // just below name
        cards[i].statsText.setString(  // ← ADD THIS
            "ATK:" + std::to_string(ShipDataBase[cards[i].shipKey].getAttack())
            + " DEF:" + std::to_string(ShipDataBase[cards[i].shipKey].getDefense())
        );


    }


// REPUBLIC label — sits right above the first row of ships (y=150)
    sf::Text republicLabel(font);
    republicLabel.setString("REPUBLIC");
    republicLabel.setCharacterSize(16);
    republicLabel.setFillColor(sf::Color(80, 150, 255)); //Blue
    republicLabel.setPosition(sf::Vector2f(90.f, 110.f));  // 40px above row 1

// Divider line — sits between row 1's text (ends ~y=280) and row 2 (starts y=400)
    sf::RectangleShape divider;
    divider.setSize(sf::Vector2f(1100.f, 2.f));
    divider.setPosition(sf::Vector2f(90.f, 330.f));  // halfway in the gap

// SEPARATIST label — sits right above the second row of ships (y=400)
    sf::Text separatistLabel(font);
    separatistLabel.setString("SEPARATIST");
    separatistLabel.setCharacterSize(16);
    separatistLabel.setFillColor(sf::Color(255, 80, 80)); //Red
    separatistLabel.setPosition(sf::Vector2f(90.f, 360.f));  // 40px above row 2



//The little pop out in selction screen to show your roster
//Approach woudl be to draw the rectangle make yellow woudl want to then just have if for what 





// Card ie button for randomzer and ship select which will from a terminal code persepcte ie if i presss randomize do that 
    sf::Text RandomizerButtonLabel(font);
        RandomizerButtonLabel.setString("Randomize");
        RandomizerButtonLabel.setCharacterSize(20);
        RandomizerButtonLabel.setFillColor(sf::Color::White);
        RandomizerButtonLabel.setPosition(sf::Vector2f(280.f, 340.f));  // 40px above row 1

    //Buildin the Boxes for randomize then do another for manual
    sf::RectangleShape Randomizer_Button_Box;
        Randomizer_Button_Box.setSize(sf::Vector2f(200.f, 75.f));
        Randomizer_Button_Box.setPosition(sf::Vector2f(250.f, 315.f)); //DO NOT TOUCH THESE VALUES 
        Randomizer_Button_Box.setFillColor(sf::Color::Transparent);
        Randomizer_Button_Box.setOutlineThickness(3.f);
        Randomizer_Button_Box.setOutlineColor(sf::Color::White);

    sf::RectangleShape Randomizer_Glow;
        Randomizer_Glow.setSize(sf::Vector2f(200.f, 75.f));
        Randomizer_Glow.setPosition(sf::Vector2f(250.f, 315.f));
        Randomizer_Glow.setFillColor(sf::Color::Transparent);

    sf::RectangleShape Manual_Glow;
        Manual_Glow.setSize(sf::Vector2f(200.f, 75.f));
        Manual_Glow.setPosition(sf::Vector2f(740.f, 315.f));
        Manual_Glow.setFillColor(sf::Color::Transparent);

    sf::Text Enemy_Selection_Label(font); // Yea idk for some reason i codede this out of order and this has diff name idk why i did that maybe ill fix later but code works tho so 
        Enemy_Selection_Label.setString("Manual");
        Enemy_Selection_Label.setCharacterSize(20);
        Enemy_Selection_Label.setFillColor(sf::Color::White);
        Enemy_Selection_Label.setPosition(sf::Vector2f(790.f, 340.f));  // 40px above row 1
   
    sf::RectangleShape Manual_Button_Box;
        Manual_Button_Box.setSize(sf::Vector2f(200.f, 75.f));
        Manual_Button_Box.setPosition(sf::Vector2f(740.f, 315.f));
        Manual_Button_Box.setFillColor(sf::Color::Transparent);
        Manual_Button_Box.setOutlineThickness(3.f);
        Manual_Button_Box.setOutlineColor(sf::Color::White);

//My Storage via vecotr (array)
    std::vector<Ship> My_Hangar;
    int pickCount = 0;

// --- GAME LOOP --------------------------------------
//Importatnt to know becasue we are using a real time sorta demo code we CANNOT use things like while loops or things taht keep waitign rather it needs to always be moving its odd
//sp theres alot of stuff that goes before teh game loop thing of game loop like a pseduo main code it odd im still learning 

    while (window.isOpen()) {
        //NGL No idea ask Claude
        while (const std::optional<sf::Event> event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
            window.close();


        // when they click anywhere for now, switch to ship select
        if (event->is<sf::Event::MouseButtonPressed>()){
            state = GameState::SHIP_SELECT;

            sf::Vector2i mousePos = sf::Mouse::getPosition(window);

            if (event->is<sf::Event::MouseButtonPressed>()) {
                for (int i = 0; i < 6; i++) {
                    hangar_Ship_Select_txt.setString("Ships Remaining: " + std::to_string(RemainingShipToSelect));
                    if (cards[i].sprite.getGlobalBounds().contains(sf::Vector2f(mousePos))) {
                        if (pickCount < 3) {
                            My_Hangar.push_back(ShipDataBase[cards[i].shipKey]);

                            pickCount++;
                            if (pickCount == 3) { // for now leave here might make seperate later if i add that are you done with this screen 
                                state = GameState::ENEMY_TEAM_COMP;

                                //std::cout << "Picked: " << << "\n"; // terminal check i like this from now on keep doing stuff like this to prove the idea of waht happening 


                            }

                            RemainingShipToSelect--;

                            std::cout << "Picked: " << cards[i].nameText.getString().toAnsiString() << "\n"; // terminal check i like this from now on keep doing stuff like this to prove the idea of waht happening 
                            
                        }
                    }
                }
            }
        }
        /*next things to add make the rand or manual buttons work and use the std cout to help out there ranomize shoudl just then start game for now just maybe hit randomize then in termianl it tells me then show it 
            - ADD THE glow affect that i did for ship select and fix the selction screen boxes there not ceneterd properly 
            - the manyal screen woudl essenlly be the select ship screen 
            - during selction screen have a little pop up thats drop down shows current roster maybe when i get max of 3 a little pop up at bottom goes are you happy with ship selection
            - clean up code later keep it messy for now 
            -For real game stuff maybe enemoy on tp in on bttom and mayeb flip the all the cards so the can look at each other adn have an animaiton for shoot, shilds/ take dagame and then one for destroyed ie explostion 
            
    Function example for text to clean it all up     im do it later tired now first big thing to do and contiune super commenting   
            sf::Text makeText(sf::Font& font, const std::string& str, int size, sf::Color color, float x, float y) {
            sf::Text t(font);
            t.setString(str);
            t.setCharacterSize(size);
            t.setFillColor(color);
            sf::FloatRect b = t.getLocalBounds();
            t.setOrigin(sf::Vector2f(b.size.x / 2.f, b.size.y / 2.f));
            t.setPosition(sf::Vector2f(x, y));
            return t;
        }

        sf::Text title = makeText(font, "Star Wars Fleet Battles", 36, sf::Color::Yellow, 640.f, 60.f);
            
            
            */

    }

//This is hover logic ie mouse sits over a desired box and i want the glow affect
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        for (int i = 0; i < 6; i++) {
            if (cards[i].sprite.getGlobalBounds().contains(sf::Vector2f(mousePos))) {
                if (cards[i].shipKey <= 3) {
                        cards[i].glow.setFillColor(sf::Color(80, 150, 255, 60));  // blue glow
                } 

                else {
                    cards[i].glow.setFillColor(sf::Color(255, 80, 80, 60));   // red glow
                }
            } 
            
            else {
                cards[i].glow.setFillColor(sf::Color::Transparent);
            }
        }
//Hover Logic for Randomizer Button 
        if (Randomizer_Button_Box.getGlobalBounds().contains(sf::Vector2f(mousePos))) {
            Randomizer_Glow.setFillColor(sf::Color(255, 255, 100, 40)); //As we seen thru code we can use color code or real names ie white
        } 
        else {
            Randomizer_Glow.setFillColor(sf::Color::Transparent);
        }
//Hover Logic for Manual Button 
        if (Manual_Button_Box.getGlobalBounds().contains(sf::Vector2f(mousePos))) {
            Manual_Glow.setFillColor(sf::Color(255, 255, 100, 40));
        } 
        else {
            Manual_Glow.setFillColor(sf::Color::Transparent);
        }


        window.clear();

        if (state == GameState::TITLE) { // 1. background
        window.draw(background);
        window.draw(title);
        }


        else if (state == GameState::SHIP_SELECT) { // 2. text on top
            window.draw(ShipSelectPic);             // new back ground 
            window.draw(hangar_txt);                
            window.draw(hangar_Ship_Select_txt);    //this is the dynamic you have n number of ships left to pick and add to vector ie array 
            window.draw(divider);   
            window.draw(republicLabel);    
            window.draw(separatistLabel);
            
            for (int i = 0; i < 6; i++) { //This loop actlly puts all that ship stuff up for printing if you will to display
                window.draw(cards[i].glow);
                window.draw(cards[i].sprite);
                window.draw(cards[i].box);
                window.draw(cards[i].nameText);
                window.draw(cards[i].statsText);
            }
        }

        else if (state == GameState::ENEMY_TEAM_COMP){
            window.draw(ShipSelectPic);
            window.draw(Enemy_Selection_Comp_txt);

            window.draw(Randomizer_Glow);
            window.draw(Randomizer_Button_Box);
            window.draw(RandomizerButtonLabel);

            window.draw(Manual_Glow);
            window.draw(Manual_Button_Box);
            window.draw(Enemy_Selection_Label);

        }
   
        window.display();         // 3. show it
    }

//EVERYTHING BELOW THIS IS ALL OLD CODE DONT NEED TO LOOK 



//Hash map to make easier --- BEFORE WE RUN CODE RATHER THAN ME PUTTING IN LAAT DO ANTOHER OBJECT PARTS CALL IT CALL_VAL ADN DO 1,2, ETC OTHERWISE CHAGE INT TO STD:STRING


//Reoloring in Terminal --- a;wyus "\033" for cahracters --- followed by [numbers color adn then before next line essnally use [0 to rest all mu changes 
//Trivia hwo to let say seperatist be one color and republic be another 
        std::cout << "Captain choose ur ships" << '\n';
    //HOW I WOULD PRINT OUT A HASH I GUES 
    for (const auto& pair : ShipDataBase) {
    std::cout << pair.first << " -> " << "\033[35m" << pair.second.getName() << "\033[0m"
                            << " | ATK: " << "\033[31m" << pair.second.getAttack() << "\033[0m"
                            << " | DEF: " << "\033[34m" << pair.second.getDefense() << "\033[0m"
                            << " | Faction: " << pair.second.getFaction()
                            << '\n'; // PARI FIRST IS TEH KEY ADN PAIR SECODN IS VALUE  
    }
    std::cout << std::string(60, '=') << '\n'; //lazy me syaing hey put = down 60 times can update accordingly --- same as std:coud << "==================";
//-Defense Power: " << "\033[34" << hangar[i].getDefense() << "\033[0m"<< '\n';

//This is func call as well as the max ship count we pick 
    int max_ship_count = 3;
    Pick_Ships(My_Hangar, ShipDataBase, max_ship_count);


//Printing what USERS fleet/hangar is
    std::cout << "Captain your fleet: " << '\n'; 
    print_hangars(My_Hangar);




    std::vector<Ship> Enemy_Hangar;
    //all for new randomizer could use old way tho --- leave outside think this as setting eveerythign up 
    std::random_device rd;                            // same job as time(0) — gets a seed --- seed: gives a random starting point 
    std::mt19937 gen(rd());                           // same job as srand() — sets up the engine --- engine: generate from there  
    std::uniform_int_distribution<int> distrib(1,6);  // same job as % 6 — sets the range


    std::cout << "Captain do you want to have the enemy fleet randomized [1] or do you want to pick [2]: ";
        int enemy_fleet_pick;
        std::cin >> enemy_fleet_pick;
            //cond to make sure u pick 
            while (enemy_fleet_pick != 1 && enemy_fleet_pick != 2) {  // keeps looping if invalid
                std::cout << "Invalid, pick 1 or 2: ";
                std::cin >> enemy_fleet_pick;
            } 
    std::cout << std::string(60, '=') << '\n'; //lazy me syaing hey put = down 60 times can update accordingly --- same as std:coud << "==================";
    switch (enemy_fleet_pick) {

        case (1):
            Rand_Ships(Enemy_Hangar, ShipDataBase, max_ship_count, gen, distrib);
            break;
        case (2):
            Pick_Ships(Enemy_Hangar, ShipDataBase, max_ship_count);
            break;

    }
    std::cout << "Captain the Enemy fleet appears to have: " << '\n';
    print_hangars(Enemy_Hangar);

//turn the display of vecotr hangars into fucntions 
//clen up so in termianl eveytgin is easier to look at ie player anems are colored maybe do liek a ========================= to split up large sextion 



//Actual turn based sorta idea of User goes first i pick a ship to attk then have the Enemy attack once --- idk seems kinda odd 
int turn = 1;
while(!My_Hangar.empty() && !Enemy_Hangar.empty()){ // Checking if the vectors are empty
   
    std::cout << "\033[33m" << "TURN " << turn << "\033[0m" << std::string(60, '-') << '\n';

//User Picks Ship to use --- print get value let that value -1 is ship then let that be variubel 
    std::cout << "My fleet: " << '\n';
    print_hangars(My_Hangar);
    std::cout << "Which ship do you want to use Captain (Pick number): ";
        int ship_select;
        std::cin >> ship_select; //display who we have chosen as well as expected outcomes of attacking a certain ship and dsipaly left over 
            while (ship_select < 1 || ship_select > (int)My_Hangar.size()) {  // keeps looping if invalid
                std::cout << "Invalid, pick a number that corresponds to one of the ships you got: ";
                std::cin >> ship_select;
            } 
    std::cout << ship_select << ')' << " Name of ship: " << "\033[35m" << My_Hangar[ship_select-1].getName() << "\033[0m" << '\n';
    std::cout << '\t' << '\t' << "-Attack Power:  " << "\033[31m" << My_Hangar[ship_select-1].getAttack() << "\033[0m" <<'\n';
    std::cout << '\t' << '\t' << "-Defense Power: " << "\033[34m" << My_Hangar[ship_select-1].getDefense() << "\033[0m" << '\n';
    std::cout << '\t' << '\t' << "-Faction:       " << My_Hangar[ship_select-1].getFaction() << '\n';
    std::cout << '\n';

//User picks which enemy ship to attack
    std::cout << "Enemy Fleet:" << '\n';
    print_hangars(Enemy_Hangar);
    std::cout << "Captain, who are we attacking!!!!! (Pick the number associtate to ship): ";
        int target;
        std::cin >> target;
            while (target < 1 || target > (int)Enemy_Hangar.size()) {  // keeps looping if invalid
                std::cout << "Invalid, pick a number that corresponds to one of the ships enemy has, Note that the ships did move essnally or get pushed down so just go by new numbers: ";
                std::cin >> target;
            } 
    
//if i said attack first thate located at elemtn 1 so target which i said 1 minus 1 so when i say attak the thrid ship vector says thats 2 to target minus 
    int defense_before_1 = Enemy_Hangar[target-1].getDefense(); // save first    
    Enemy_Hangar[target - 1].setDefense(Enemy_Hangar[target - 1].getDefense() - My_Hangar[ship_select - 1].getAttack());
        
    
    //DAMAGE REPORT OF WHAT JSUT HAPPENED --- this was the ship we used > damage done > what enemy has left 
    damage_report(My_Hangar[ship_select-1], Enemy_Hangar[target-1], My_Hangar[ship_select-1].getAttack(), defense_before_1);

//Ship hits 0 defense, remove it
    destroyed_in_battle(Enemy_Hangar, target-1); 
    
        // if (Enemy_Hangar[target - 1].getDefense() <= 0) {
        //     std::cout << Enemy_Hangar[target - 1].getName() << " destroyed!\n";
        //     Enemy_Hangar.erase(Enemy_Hangar.begin() + (target - 1));
        // }
  
    std::cout << std::string(60, '=') << '\n'; //lazy me syaing hey put = down 60 times can update accordingly --- same as std:coud << "==================";



// Enemy attacks random player ship
    if(!Enemy_Hangar.empty()) { // Purpose of this loop si to check beofre enemy attack ig
        
        std::cout << "Captain, the enemy appears to be getting ready for an attack" << '\n';

        //Enemy behind the scenes --- need to do same idea of rand generate ship number to attack 
        int enemy_select = distrib(gen) % Enemy_Hangar.size();
//Enemy ship display
        std::cout << "Enemy is attacking with: " << "\033[35m" << Enemy_Hangar[enemy_select].getName() << "\033[0m" << '\n';

        std::cout << enemy_select+1 << ')' << " Name of ship: " << "\033[35m" << Enemy_Hangar[enemy_select].getName() << "\033[0m" << '\n';
        std::cout << '\t' << '\t' << "-Attack Power:  " << "\033[31m" << Enemy_Hangar[enemy_select].getAttack() << "\033[0m" <<'\n';
        std::cout << '\t' << '\t' << "-Defense Power: " << "\033[34m" << Enemy_Hangar[enemy_select].getDefense() << "\033[0m" <<'\n';
        std::cout << '\t' << '\t' << "-Faction:       " << Enemy_Hangar[enemy_select].getFaction() << '\n';
        std::cout << '\n';

        int rand_target = distrib(gen) % My_Hangar.size();
        int defense_before_2 = My_Hangar[rand_target].getDefense(); // save first    
        My_Hangar[rand_target].setDefense(My_Hangar[rand_target].getDefense() - Enemy_Hangar[enemy_select].getAttack());

        damage_report(Enemy_Hangar[enemy_select], My_Hangar[rand_target], Enemy_Hangar[enemy_select].getAttack(), defense_before_2);
        destroyed_in_battle(My_Hangar, rand_target); 
        std::cout << std::string(60, '=') << '\n'; //lazy me syaing hey put = down 60 times can update accordingly --- same as std:coud << "==================";
        }
    turn++;
    }

    // Winner
    if (My_Hangar.empty()) {
        std::cout << "YOU LOST!?!?!?!? WHAT DID U FIGHT A SUPERIOR CLANKER LIKE GENERAL GREVIOUS THAT WANNA BE SITH LORD AND YOU LOST TO HIM WOW!!!!! WERE BOUT TO GET COMMANDER YULARN IN HERE TO WIN THIS BATTLE AGAINST THOSE CLANKERS\n";
    } 

    else {
        std::cout << "YOU WON!!!!!!ITS JUST LIKE THE SIMULATIONS\n"; //HAHA funny star wars reference
    }



    return 0;
}
      

