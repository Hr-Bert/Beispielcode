// Erstes benutzbares SFML-Programm/Spiel
// Noch keine Objektorientierung

#include <SFML/Graphics.hpp>  // alle SFML Funktionen
#include <SFML/Audio.hpp>
#include <iostream>          // Standard cin, cout
#include <conio.h>          // z.B. _getch()         // wird nicht mehr gebracuht, durch andere ähnliche SFML Funktionen
#include <string>
#include <random>

void menu(sf::RenderWindow&, sf::Font&, sf::Event&);
void gameover(sf::RenderWindow&, sf::Font&);
void spiel(sf::RenderWindow&, sf::Font&);

int main()
{
    sf::RenderWindow window(sf::VideoMode(600, 900), "Pong", sf::Style::Close);  // SFML-Fenster, dass nur geschlossen werde  kann
    
    sf::Font pixeboy{};
    if (!pixeboy.loadFromFile("Pixeboy.ttf")) std::cout << "Fehler beim Laden der Schriftart!";  // Schriftart aus Datei ins Programm laden, falls es nicht klappt Fehlermeldung

    spiel(window, pixeboy);

    return 0;
}

void spiel(sf::RenderWindow& window, sf::Font& pixeboy)
{
    // Sound fürs Abprallen vom Spieler
    sf::SoundBuffer spielerbuffer;                 
    if (!spielerbuffer.loadFromFile("Poing.mp3")) { std::cout << "Fehler beim Laden des Sounds (Spieler)"; exit(0); }  
    sf::Sound poing;
    poing.setBuffer(spielerbuffer);            

    // Sound fürs Abprallen von den Wänden
    sf::SoundBuffer wandBuffer;
    if (!wandBuffer.loadFromFile("Wand.mp3")) { std::cout << "Fehler beim Laden des Sounds (Wand)"; exit(0); }
    sf::Sound wandPoing;
    wandPoing.setBuffer(wandBuffer);
    wandPoing.setPlayingOffset(sf::Time(sf::milliseconds(300)));

    // Text und Variable zum Hochzählen der Punkte
    unsigned long long int counter = 0;
    sf::Text zaehler;
    zaehler.setFont(pixeboy);
    zaehler.setCharacterSize(70);
    zaehler.setFillColor(sf::Color(0, 255, 26));                                               

    //  roter Ball
    sf::CircleShape ball(12.0f);        
    ball.setFillColor(sf::Color::Red);
    ball.setOrigin(12.0f, 12.0f); 
    ball.setPosition(((rand() % 580) + 10), 200.0f);  // Ball beginnt auf "zufälliger" x Position zwischen 10 und 590, auf der Höhe 200 (von oben gesehen)

    // Spieler (lilaner Balken)
    sf::RectangleShape spieler(sf::Vector2f(100.0f, 12.0f));  
    spieler.setFillColor(sf::Color(153, 50, 204));
    spieler.setOrigin(50.0f, 6.0f);
    spieler.setPosition(300.0f, 850.0f);

    window.setFramerateLimit(60);       // Maximal 60 fps 

    float speedx = 6.5f;
    float speedy = 7.5f;
    
    while (window.isOpen())  // Startbildschirm
    {
        sf::Event event;

        sf::Text pong = {"Pong", pixeboy, 125}; 
        pong.setFillColor(sf::Color::Green);
        pong.setOrigin((pong.getGlobalBounds().getSize().x / 2), (pong.getGlobalBounds().getSize().y / 2));
        pong.setPosition((window.getSize().x / 2.f), 50.f);

        sf::Text start = { "press enter to start", pixeboy, 50 };
        start.setFillColor(sf::Color::Red);
        start.setOrigin((start.getGlobalBounds().getSize().x / 2), (start.getGlobalBounds().getSize().y / 2));
        start.setPosition((window.getSize().x / 2.f), (window.getSize().y / 2.f));

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) break; // wartet auf Tasteneingabe, bevor das Spiel gestartet wird

        while (window.pollEvent(event))  // Schleife um schließen zu ermöglichen
        {
            if (event.type == sf::Event::Closed) window.close();
        }

        window.clear(sf::Color(28, 28, 28));
        window.draw(start);
        window.draw(pong);
        window.display();
    }


    while (window.isOpen())
    {
        sf::Event event;

        zaehler.setString(std::to_string(counter));   // unsigned long long int zu string konvertieren um ihn ausgeben zu können

        sf::Vector2f ballPos = ball.getPosition();
        sf::Vector2f spielerPos = spieler.getPosition();

        if (counter == 0 || counter == 10 || counter == 100)  // Wenn die Zahl einstellig, zweistellig, dreistellig wird, wird sie erneut in die Mitte gerückt  
        {
            zaehler.setOrigin((zaehler.getGlobalBounds().getSize().x / 2), (zaehler.getGlobalBounds().getSize().y / 2));
            zaehler.setPosition((window.getSize().x / 2.f), 180.f);
        }

        if (ballPos.x <= 0 + 12 || ballPos.x >= 600 - 12)  // Richtung umkehren & Sound spielen, bei Berührung des Randes (rechts oder links)  
        { 
            speedx *= -1; 
            wandPoing.play();
            wandPoing.setPlayingOffset(sf::Time(sf::milliseconds(300)));
        }    
        if (ballPos.y <= 0 + 12 || ballPos.y >= 900 - 12)    // Richtung umkehren & Sound spielen, bei Berührung des Randes (oben oder unten)
        { 
            speedy *= -1; 
            wandPoing.play();
            wandPoing.setPlayingOffset(sf::Time(sf::milliseconds(300)));
        }  


        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))  spieler.move(-5.0f, 0.0f);  // Spieler nach links bewegen mit 'A' oder '<-'
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) spieler.move(5.0f, 0.0f);  // Spieler nach rechts bewegen mit 'D' oder '->'

        if (spielerPos.x > 600 - 50) spieler.move(-5.0f, 0.0f);                                     // Wenn Balken weiter als rechter Rand, dann zurück
        if (spielerPos.x < 0 + 50) spieler.move(5.0f, 0.0f);                                       // Wenn Balken weiter als linker Rand, dann zurück

        if ((ballPos.y >= 900.0f - 50.0f - 12.0f - 3.75f) && (spielerPos.x - ballPos.x <= 50.0f + 5.f) && (spielerPos.x - ballPos.x >= -50.0f - 5.f))  // Wenn der Balken / Spieler berührt (Kollision)
        {
            speedy *= -1;
            counter++;  
            poing.play();
            
            if (!(counter % 5))
            {
                if (speedy < 0) speedy -= 1.5;
                else speedy += 1.5;
                if (speedx < 0) speedx -= 1.5;
                else speedx += 1.5;
            }
        }


        ball.move(speedx, speedy);

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();
        }

        window.clear(sf::Color(28, 28, 28));    // window.clear(sf::Color::Cyan), etc auch möglich. / (28, 28, 28) -> dunkelgrau (nicht als sf::Color verfügbar)
        window.draw(ball);
        window.draw(zaehler); 
        window.draw(spieler);
        window.display();

        if (ballPos.y > 900.0f - 50.0f - 12.0f + 4.0f)
        {
            gameover(window, pixeboy); // Wenn der Ball eine bestimmte Position unterschreitet wird die Funktion game over aufgerufen
            ball.setPosition(sf::Vector2f(300.f, 200.f));
            spieler.setPosition(sf::Vector2f(300.f, 850.f));
            counter = 0;
            speedy = 7.5;
            speedx = 7.5;
        }
    }
     
}


void gameover(sf::RenderWindow& window, sf::Font& pixeboy)
{
    sf::SoundBuffer verlorenBuffer;
    if (!verlorenBuffer.loadFromFile("gameover.mp3")) { std::cout << "Fehler beim Laden des gameover-Sounds!"; }
    sf::Sound verlorenSound;
    verlorenSound.setBuffer(verlorenBuffer);
    verlorenSound.play();

    sf::Text verloren;
    verloren.setFont(pixeboy);
    verloren.setFillColor(sf::Color::Red);               // Alle möglichen Einstellungen des "game over" Schriftzugs, wie Farbe, Größe, etc. 
    verloren.setCharacterSize(100);
    verloren.setString("game over");
    verloren.setOrigin((verloren.getGlobalBounds().getSize().x / 2), (verloren.getGlobalBounds().getSize().y / 2));
    verloren.setPosition((window.getSize().x / 2.f), 60.f);

    sf::Text enter;
    enter.setFont(pixeboy);
    enter.setFillColor(sf::Color::Red);
    enter.setCharacterSize(35);                        // Alle möglichen Einstellungen des "press enter" Schriftzugs
    enter.setString("press enter");
    enter.setOrigin((enter.getGlobalBounds().getSize().x / 2), (enter.getGlobalBounds().getSize().y / 2));
    enter.setPosition((window.getSize().x / 2.f), 140.f);

    // window.clear(); wird in diesem Fall nicht verwendet, da sonst das Ende des Spiel nicht mehr mit angezeigt wird
    window.draw(verloren);
    window.draw(enter);
    window.display();
    

    while (window.isOpen())  
    {
        sf::Event event;
       
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) break; // wartet auf Tasteneingabe bevor die Schleife beendet wird und das Spiel wieder beginnt

        while (window.pollEvent(event))  // zusammen mit der äußeren Schleife das schließen des Fensters auch in der game-over-Funktion möglich
        {
            if (event.type == sf::Event::Closed) window.close();
        }
    }
}
