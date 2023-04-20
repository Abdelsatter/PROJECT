#include<iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
using namespace std;
using namespace sf;

void Game_Play(RenderWindow& window);
void Main_Menu(RenderWindow& window);

int main()
{
	// load fireboy & water girl
	RenderWindow window(VideoMode(1280, 720), "FireBoy&WaterGirl");
	window.setFramerateLimit(60);


	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}
		}
		Main_Menu(window);

	}
	return 0;
}

void Main_Menu(RenderWindow& window)
{
	bool playclicked = 0;
	bool settingsclicked = 0;
	Clock clock;
	int nav = 0;



	//Main Menu

	Texture MainMenu_title;
	MainMenu_title.loadFromFile("GameNameForest.png");
	Sprite mainmenu_title;
	mainmenu_title.setTexture(MainMenu_title);
	mainmenu_title.setPosition(384, 80);

	Texture MainMenu_Background;
	MainMenu_Background.loadFromFile("TempleHallForest.png");
	Sprite mainmenu_Background;
	mainmenu_Background.setTexture(MainMenu_Background);

	Texture Play_button;
	Play_button.loadFromFile("Play_button.png");
	Sprite play_button;
	play_button.setTexture(Play_button);
	play_button.setPosition(580, 340.5);

	Texture Settings;
	Settings.loadFromFile("Settings_button.png");
	Sprite settings;
	settings.setTexture(Settings);
	settings.setPosition(35, 600);

	Texture Beam[3];
	Sprite beam[3];
	for (int i = 0; i < 3; i++) {
		Beam[i].loadFromFile("Beam.png");
		beam[i].setTexture(Beam[i]);
	}

	beam[0].setPosition(510, -30);
	beam[0].setRotation(15);
	beam[1].setPosition(560, -10);
	beam[2].setPosition(610, -30);
	beam[2].setRotation(-15);

	//Fireboy

	int fb = 0;

	Texture fb_mainmenu;
	fb_mainmenu.loadFromFile("IDLE_Fireboy.png");
	Sprite fb_MainMenu;
	fb_MainMenu.setTexture(fb_mainmenu);
	fb_MainMenu.setTextureRect(IntRect(0, 0, 64, 130));
	fb_MainMenu.setPosition(200, 560);

	//Watergirl

	int wg = 0;

	Texture wg_mainmenu;
	wg_mainmenu.loadFromFile("IDLE_wg.png");
	Sprite wg_MainMenu;
	wg_MainMenu.setTexture(wg_mainmenu);
	wg_MainMenu.setTextureRect(IntRect(0, 0, 70, 130));
	wg_MainMenu.setPosition(1000, 570);


	while (window.isOpen())
	{
		fb_MainMenu.setTextureRect(IntRect(fb * 64, 0, 64, 130));
		fb++;
		fb %= 19;

		wg_MainMenu.setTextureRect(IntRect(wg * 70, 0, 70, 130));
		wg++;
		wg %= 30;

		Event On;
		while (window.pollEvent(On))
		{
			if (On.type == Event::Closed)
				window.close();
		}
		if (Mouse::isButtonPressed(Mouse::Left)) {
			clock.restart();
			Vector2i mousepos = Mouse::getPosition(window);
			if (mousepos.x > 580 && mousepos.x < 700 && mousepos.y>340.5 && mousepos.y < 379.5) {
				play_button.setScale(0.9, 0.9);
				play_button.setPosition(584, 344.5);
				playclicked = 1;
			}
			else if (mousepos.x > 35 && mousepos.x < 82 && mousepos.y>600 && mousepos.y < 649) {
				settings.setScale(0.9, 0.9);
				settingsclicked = 1;
			}
		}

		if (clock.getElapsedTime().asSeconds() > 0.3) {
			if (playclicked)
				nav = 1;
			else if (settingsclicked)
				nav = 2;
		}

		window.clear();
		if (nav == 0) {
			window.draw(mainmenu_Background);
			for (int i = 0; i < 3; i++) {
				window.draw(beam[i]);
			}
			window.draw(mainmenu_title);
			window.draw(fb_MainMenu);
			window.draw(wg_MainMenu);
			window.draw(play_button);
			window.draw(settings);
			//W1.draw(settings_button);
		}
		else if (nav == 1) {
			//W1.draw(level_select);
			Game_Play(window);

		}
		else if (nav == 2) {

		}
		window.display();
	}

}
void Game_Play(RenderWindow& window)
{
	Texture F, W;
	Sprite FireBoy, WaterGirl;





	//set fireboy
	F.loadFromFile("Fireboy.png");
	FireBoy.setTexture(F);
	FireBoy.setPosition(450, 650);
	FireBoy.setOrigin(FireBoy.getLocalBounds().width / 124, FireBoy.getLocalBounds().height / 2);


	//set watergirl
	W.loadFromFile("water_girl.png");
	WaterGirl.setPosition(400, 650);
	WaterGirl.setTexture(W);
	WaterGirl.setOrigin(WaterGirl.getLocalBounds().width / 106, WaterGirl.getLocalBounds().height / 2);


	// rectangle the box
	RectangleShape RectangleDown(Vector2f(1280, 10));
	RectangleDown.setPosition(0, 710);
	RectangleDown.setFillColor(Color::Red);
	


	//sentaces
	int animationStandingFireBoy = 0, animationStandingWaterGirl = 0;
	int moveFireBoy = 17, moveWaterGirl = 6;
	double velocityFireBoy = 0, velocityWaterGirl = 0;
	bool isAnimationStandingWaterGirl = true, isAnimationStandingFireBoy = true, isMoveFireBoy = true,  isMoveWaterGirl = true;
	Clock clocksf, clocksw, clockf, clockw;


	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}
		}


		//hitbox fire boy
		RectangleShape hitpoxf(Vector2f(60, 100));
		hitpoxf.setOrigin(30, 35);
		hitpoxf.setPosition(FireBoy.getPosition().x, FireBoy.getPosition().y);
		//hitbox water girl
		RectangleShape hitpoxw(Vector2f(60, 93));
		hitpoxw.setOrigin(30, 41);
		hitpoxw.setFillColor(Color::Blue);
		hitpoxw.setPosition(WaterGirl.getPosition().x, WaterGirl.getPosition().y);

		if (RectangleDown.getGlobalBounds().intersects(hitpoxw.getGlobalBounds()))
		{

			velocityWaterGirl = 0;
			if (Keyboard::isKeyPressed(Keyboard::Key::Up))
			{
				FireBoy.setTextureRect(IntRect(118 * moveFireBoy, 0, 118, 130));

				velocityWaterGirl = 7;
			}
		}
		else
		{

			velocityWaterGirl -= 0.2;
		}
		if (RectangleDown.getGlobalBounds().intersects(hitpoxf.getGlobalBounds()))
		{

			velocityFireBoy = 0;
			if (Keyboard::isKeyPressed(Keyboard::Key::W))
			{
				velocityFireBoy = 7;
			}
		}
		else
		{

			velocityFireBoy -= 0.2;
		}
		//Animation standing player

		FireBoy.setTextureRect(IntRect(118 * animationStandingFireBoy, 0, 118, 130));
		WaterGirl.setTextureRect(IntRect(117.8 * animationStandingWaterGirl, 0, 117.8, 130));




		if (isAnimationStandingFireBoy)
		{
			if (clocksf.getElapsedTime().asSeconds() >= 0.10)
			{
				animationStandingFireBoy++; animationStandingFireBoy %= 17;
				clocksf.restart();
			}
		}
		if (isAnimationStandingWaterGirl)
		{
			if (clocksw.getElapsedTime().asSeconds() >= 0.10)
			{
				animationStandingWaterGirl++; animationStandingWaterGirl %= 6;
				clocksw.restart();
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::Key::Right) && Keyboard::isKeyPressed(Keyboard::Key::Left))
		{
			isMoveWaterGirl = false;
		}
		else { isMoveWaterGirl = true; }


		if (Keyboard::isKeyPressed(Keyboard::Key::D) && Keyboard::isKeyPressed(Keyboard::Key::A))
		{
			isMoveFireBoy = false;
			isAnimationStandingFireBoy = true;
		}
		else{ isMoveFireBoy = true; }
		






		if (isMoveFireBoy)
		{
			if (Keyboard::isKeyPressed(Keyboard::Key::A) && FireBoy.getPosition().x > 35)
			{
				isAnimationStandingFireBoy = false;
				FireBoy.setTextureRect(IntRect(118 * moveFireBoy, 0, 118, 130));
				if (clockf.getElapsedTime().asSeconds() >= 0.05)
				{
					moveFireBoy++;
					if (moveFireBoy > 27)moveFireBoy -= 11;
					clockf.restart();
				}
				FireBoy.setScale(-1, 1);
				FireBoy.move(-5, 0);

			}
			

			else if (Keyboard::isKeyPressed(Keyboard::Key::D) && FireBoy.getPosition().x < 1245)
			{

				isAnimationStandingFireBoy = false;
				FireBoy.setTextureRect(IntRect(118 * moveFireBoy, 0, 118, 130));
				if (clockf.getElapsedTime().asSeconds() >= 0.05)
				{
					moveFireBoy++;
					if (moveFireBoy > 27)moveFireBoy -= 11;
					clockf.restart();
				}
				FireBoy.setScale(1, 1);
				FireBoy.move(5, 0);

			}
			else { isAnimationStandingFireBoy = true; }

		}

		if (isMoveWaterGirl)
		{

			if (Keyboard::isKeyPressed(Keyboard::Key::Right) && WaterGirl.getPosition().x < 1245)
			{
				isAnimationStandingWaterGirl = false;
				WaterGirl.setTextureRect(IntRect(118 * moveWaterGirl, 0, 118, 130));
				if (clockw.getElapsedTime().asSeconds() >= 0.05)
				{
					moveWaterGirl++;
					if (moveWaterGirl > 15)moveWaterGirl -= 6;

					clockw.restart();
				}
				WaterGirl.setScale(1, 1);
				WaterGirl.move(5, 0);

			}
			else { isAnimationStandingWaterGirl = true; }


			if (Keyboard::isKeyPressed(Keyboard::Key::Left) && WaterGirl.getPosition().x > 35)
			{
				isAnimationStandingWaterGirl = false;
				WaterGirl.setTextureRect(IntRect(118 * moveWaterGirl, 0, 118, 130));
				if (clockw.getElapsedTime().asSeconds() >= 0.05)
				{
					moveWaterGirl++;
					if (moveWaterGirl > 15)moveWaterGirl -= 6;

					clockw.restart();
				}
				WaterGirl.setScale(-1, 1);
				WaterGirl.move(-5, 0);

			}
			else { isAnimationStandingWaterGirl = true; }
		}

		window.clear();

		window.draw(FireBoy);
		window.draw(WaterGirl);
		//window.draw(hitpoxf);
	//	window.draw(hitpoxw);

	/*	window.draw(RectangleUp);
		window.draw(RectangleDown);
		window.draw(RectangleLeft);
		window.draw(RectangleRight);*/
		FireBoy.move(0, -velocityFireBoy);
		WaterGirl.move(0, -velocityWaterGirl);
		window.display();

	}
}

