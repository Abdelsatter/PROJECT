#include<iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
using namespace std;
using namespace sf;

void Game_Play(RenderWindow& window);
void Main_Menu(RenderWindow& window);
void Levels(RenderWindow& window);
void collision(RenderWindow& window, RectangleShape& firboy_down, RectangleShape& firboy_top, bool& isAnimationStandingWaterGirl, bool& isAnimationStandingFireBoy, double& velocityFireBoy, double& velocityWaterGirl, RectangleShape& firboy_left, RectangleShape& firboy_right);
struct grounds {
	RectangleShape ground[30];
	Texture gr_levels[10], bgr_background[10];
	Sprite ground_levels[10], background_levels[10];

}level[10];

int main()
{
	// load fireboy & water girl
	RenderWindow window(VideoMode(1280, 720), "FireBoy&WaterGirl");
	window.setFramerateLimit(40);


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
void Levels(RenderWindow& window) {




	//ground
	level[1].gr_levels[1].loadFromFile("Level_1_ground.png");
	level[1].ground_levels[1].setTexture(level[1].gr_levels[1]);

	level[1].ground_levels[1].setScale(1.6, 1.2);



	//background
	level[1].bgr_background[1].loadFromFile("gamplay_background.png");
	level[1].background_levels[1].setTexture(level[1].bgr_background[1]);
	//level[1].background_levels[1].setScale(1.6, 1.2);

	//game levels
	level[1].ground[0].setSize(Vector2f(593, 10));
	level[1].ground[0].setPosition(Vector2f(0, 710));

	level[1].ground[1].setSize(Vector2f(107, 10));
	level[1].ground[1].setPosition(Vector2f(752, 710));

	level[1].ground[2].setSize(Vector2f(260, 10));
	level[1].ground[2].setPosition(Vector2f(1016, 710));

	level[1].ground[3].setSize(Vector2f(20, 100));
	level[1].ground[3].setPosition(Vector2f(1157, 660));

	//////
	level[1].ground[16].setFillColor(Color::Color(100, 200, 100));


	level[1].ground[4].setSize(Vector2f(240, 60));
	level[1].ground[4].setPosition(Vector2f(1177, 635));

	level[1].ground[5].setSize(Vector2f(137, 10));
	level[1].ground[5].setPosition(Vector2f(950, 565));

	level[1].ground[6].setSize(Vector2f(180, 15));
	level[1].ground[6].setPosition(Vector2f(600, 560));

	level[1].ground[7].setSize(Vector2f(30, 70));
	level[1].ground[7].setRotation(131.f);
	level[1].ground[7].setPosition(Vector2f(620, 560));

	level[1].ground[8].setSize(Vector2f(570, 20));
	level[1].ground[8].setPosition(Vector2f(0, 515));

	level[1].ground[9].setSize(Vector2f(415, 20));
	level[1].ground[9].setPosition(Vector2f(0, 610));

	level[1].ground[10].setSize(Vector2f(470, 20));
	level[1].ground[10].setPosition(Vector2f(170, 390));

	level[1].ground[11].setSize(Vector2f(25, 45));
	level[1].ground[11].setRotation(127.f);
	level[1].ground[11].setPosition(Vector2f(685, 415));

	level[1].ground[12].setSize(Vector2f(650, 15));
	level[1].ground[12].setPosition(Vector2f(675, 415));

	level[1].ground[13].setSize(Vector2f(20, 45));
	level[1].ground[13].setRotation(130.f);
	level[1].ground[13].setPosition(Vector2f(1114, 445));

	level[1].ground[14].setSize(Vector2f(20, 120));
	level[1].ground[14].setRotation(130.f);
	level[1].ground[14].setPosition(Vector2f(1198, 495));

	level[1].ground[15].setSize(Vector2f(90, 20));
	level[1].ground[15].setPosition(Vector2f(1187, 488));

	level[1].ground[16].setSize(Vector2f(185, 120));
	level[1].ground[16].setPosition(Vector2f(0, 190));

	level[1].ground[17].setSize(Vector2f(485, 20));
	level[1].ground[17].setPosition(Vector2f(145, 290));

	level[1].ground[18].setSize(Vector2f(230, 60));
	level[1].ground[18].setPosition(Vector2f(660, 245));

	level[1].ground[19].setSize(Vector2f(220, 40));
	level[1].ground[19].setPosition(Vector2f(890, 265));
	/* ========================================*/
	level[1].ground[20].setSize(Vector2f(760, 20));
	level[1].ground[20].setPosition(Vector2f(550, 163));

	level[1].ground[21].setSize(Vector2f(155, 70));
	level[1].ground[21].setPosition(Vector2f(400, 163));

	level[1].ground[22].setSize(Vector2f(70, 20));
	level[1].ground[22].setPosition(Vector2f(360, 115));

	level[1].ground[23].setSize(Vector2f(130, 20));
	level[1].ground[23].setPosition(Vector2f(370, 140));

	level[1].ground[24].setSize(Vector2f(157, 20));
	level[1].ground[24].setPosition(Vector2f(953, 306));

	level[1].ground[25].setSize(Vector2f(50, 50));
	level[1].ground[25].setRotation(133.f);
	level[1].ground[25].setPosition(Vector2f(525, 170));

	level[1].ground[26].setSize(Vector2f(50, 40));
	level[1].ground[26].setRotation(133.f);
	level[1].ground[26].setPosition(Vector2f(455, 145));

	level[1].ground[27].setSize(Vector2f(15, 45));
	level[1].ground[27].setRotation(133.f);
	level[1].ground[27].setPosition(Vector2f(390, 150));

	level[1].ground[28].setSize(Vector2f(15, 110));
	level[1].ground[28].setRotation(133.f);
	level[1].ground[28].setPosition(Vector2f(970, 320));



}
void collision(RenderWindow& window, RectangleShape& firboy_down, RectangleShape& firboy_top, bool& isAnimationStandingWaterGirl, bool& isAnimationStandingFireBoy, double& velocityFireBoy, double& velocityWaterGirl, RectangleShape& firboy_left, RectangleShape& firboy_right) {


	bool top = 0, down = 0, r = 0, l = 0;

	for (int i = 0; i < 30; i++) {
		if (level[1].ground[i].getGlobalBounds().intersects(firboy_down.getGlobalBounds())&& level[1].ground[i].getPosition().y+5>= firboy_down.getPosition().y) {

			down = 1;
		}
	}
	if (down)
	{
		isAnimationStandingFireBoy = 1;
		velocityFireBoy = 0;
		if (Keyboard::isKeyPressed(Keyboard::Key::W)) {
			velocityFireBoy = 7.5;
			isAnimationStandingFireBoy = 0;

		}

	}
	else if (!down)
	{
		isAnimationStandingFireBoy = 0;
		velocityFireBoy -= 0.2;
	}
	for (int i = 0; i < 30; i++) {
		if (level[1].ground[i].getGlobalBounds().intersects(firboy_top.getGlobalBounds())) {
			top = 1;
		}
	}
	if (top && !isAnimationStandingFireBoy) {
		velocityFireBoy = -1;

	}
	/*for (int i = 0; i < 30; i++) {
		if (level[1].ground[i].getGlobalBounds().intersects(firboy_right.getGlobalBounds())) {
			r = 1;
		}
	}
	if (r) {

	}*/
}

void Game_Play(RenderWindow& window)
{
	Texture fireBoyImage, waterGirlImage;
	Sprite FireBoy, WaterGirl;

	//levels
	Levels(window);


	//set fireboy
	fireBoyImage.loadFromFile("Fireboy.png");
	FireBoy.setTexture(fireBoyImage);
	FireBoy.setPosition(100, 100);
	FireBoy.setOrigin(FireBoy.getLocalBounds().width / 38, FireBoy.getLocalBounds().height / 2);
	FireBoy.setScale(0.7f, 0.7f);


	//set watergirl
	waterGirlImage.loadFromFile("Watergirl.png");
	WaterGirl.setPosition(400, 650);
	WaterGirl.setTexture(waterGirlImage);
	WaterGirl.setOrigin(WaterGirl.getLocalBounds().width / 60, WaterGirl.getLocalBounds().height / 2);
	WaterGirl.setScale(0.7f, 0.7f);


	// rectangle the box
	RectangleShape RectangleDown(Vector2f(1280, 10));
	RectangleDown.setPosition(0, 715);
	RectangleDown.setFillColor(Color::Red);


	// hitbox (up_firboy)
	RectangleShape firboy_top;
	firboy_top.setSize(Vector2f(5, 5));
	firboy_top.setFillColor(Color::Blue);
	firboy_top.setOrigin(2.5, 2.5);

	// hitbox (down_firboy)
	RectangleShape firboy_down;
	firboy_down.setSize(Vector2f(5, 5));
	firboy_down.setFillColor(Color::Blue);
	firboy_down.setOrigin(2.5, 2.5);

	// hitbox (right_firboy)
	RectangleShape firboy_right;
	firboy_right.setSize(Vector2f(6, 30));
	firboy_right.setFillColor(Color::Blue);
	firboy_right.setOrigin(3, 15);

	// hitbox (left_firboy)
	RectangleShape firboy_left;
	firboy_left.setSize(Vector2f(6, 30));
	firboy_left.setFillColor(Color::Blue);
	firboy_left.setOrigin(3, 15);





	//sentaces
	int animationStandingFireBoy = 0, animationStandingWaterGirl = 0;
	int moveFireBoy = 0, moveWaterGirl = 0;
	double velocityFireBoy = 0, velocityWaterGirl = 0;
	bool isAnimationStandingWaterGirl = true, isAnimationStandingFireBoy = true, isMoveFireBoy = true, isMoveWaterGirl = true;
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

		bool ff = 1;
		////hitbox fire boy
		//RectangleShape hitpoxf(Vector2f(60, 100));
		//hitpoxf.setOrigin(30, 35);
		//hitpoxf.setPosition(FireBoy.getPosition().x, FireBoy.getPosition().y);
		////hitbox water girl
		//RectangleShape hitpoxw(Vector2f(60, 93));
		//hitpoxw.setOrigin(30, 41);
		//hitpoxw.setFillColor(Color::Blue);
		//hitpoxw.setPosition(WaterGirl.getPosition().x, WaterGirl.getPosition().y);

		if (RectangleDown.getGlobalBounds().intersects(WaterGirl.getGlobalBounds()))
		{
			velocityWaterGirl = 0;
			if (Keyboard::isKeyPressed(Keyboard::Key::Up))
			{


				velocityWaterGirl = 5;
			}
		}
		else
		{

			velocityWaterGirl -= 0.2;
		}



		//Animation standing player
		FireBoy.setTextureRect(IntRect(149 * animationStandingFireBoy, 0, 149, 160));
		WaterGirl.setTextureRect(IntRect(149 * animationStandingWaterGirl, 0, 149, 160));




		if (isAnimationStandingFireBoy)
		{
			if (clocksf.getElapsedTime().asSeconds() >= 0.10)
			{
				animationStandingFireBoy++; animationStandingFireBoy %= 19;
				clocksf.restart();
			}
		}
		if (isAnimationStandingWaterGirl)
		{
			if (clocksw.getElapsedTime().asSeconds() >= 0.10)
			{
				animationStandingWaterGirl++; animationStandingWaterGirl %= 30;
				clocksw.restart();
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::Key::Right) && Keyboard::isKeyPressed(Keyboard::Key::Left))
		{
			isMoveWaterGirl = false;
			isAnimationStandingWaterGirl = true;

		}
		else { isMoveWaterGirl = true; }


		if (Keyboard::isKeyPressed(Keyboard::Key::D) && Keyboard::isKeyPressed(Keyboard::Key::A))
		{
			isMoveFireBoy = false;
			isAnimationStandingFireBoy = true;
		}
		else { isMoveFireBoy = true; }







		if (isMoveFireBoy)
		{
			if (Keyboard::isKeyPressed(Keyboard::Key::W))
			{
				//	isAnimationStandingFireBoy = false;
				FireBoy.setTextureRect(IntRect(149 * moveFireBoy, 3 * 160, 149, 160));
				if (clockf.getElapsedTime().asSeconds() >= 0.05)
				{
					moveFireBoy++;
					if (moveFireBoy > 4)moveFireBoy = 0;
					clockf.restart();
				}
				if (velocityWaterGirl == 6.5)
				{
					FireBoy.setTextureRect(IntRect(149 * moveFireBoy, 2 * 160, 149, 160));

				}
			}
			if (Keyboard::isKeyPressed(Keyboard::Key::A) && FireBoy.getPosition().x > 50)
			{
				isAnimationStandingFireBoy = false;
				FireBoy.setTextureRect(IntRect(149 * moveFireBoy, 1 * 160, 149, 160));
				if (clockf.getElapsedTime().asSeconds() >= 0.05)
				{
					moveFireBoy++;
					if (moveFireBoy > 6)moveFireBoy = 0;
					clockf.restart();
				}
				FireBoy.setScale(-0.7f, 0.7f);
				FireBoy.move(-5, 0);

			}


			else if (Keyboard::isKeyPressed(Keyboard::Key::D) && FireBoy.getPosition().x < 1230)
			{

				isAnimationStandingFireBoy = false;
				FireBoy.setTextureRect(IntRect(149 * moveFireBoy, 1 * 160, 149, 160));
				if (clockf.getElapsedTime().asSeconds() >= 0.05)
				{
					moveFireBoy++;
					if (moveFireBoy > 6)moveFireBoy = 0;
					clockf.restart();
				}
				FireBoy.setScale(0.7f, 0.7f);
				FireBoy.move(5, 0);

			}
			else { isAnimationStandingFireBoy = true; }

		}

		if (isMoveWaterGirl)
		{
			if (Keyboard::isKeyPressed(Keyboard::Key::Up))
			{
				isAnimationStandingWaterGirl = false;
				WaterGirl.setTextureRect(IntRect(149 * moveWaterGirl, 3 * 160, 149, 160));
				if (clockf.getElapsedTime().asSeconds() >= 0.05)
				{
					moveWaterGirl++;
					if (moveWaterGirl > 10)moveWaterGirl = 0;
					clockf.restart();
				}
				if (velocityWaterGirl == 7)
				{
					WaterGirl.setTextureRect(IntRect(149 * moveWaterGirl, 2 * 160, 149, 160));

				}
			}
			if (Keyboard::isKeyPressed(Keyboard::Key::Right) && WaterGirl.getPosition().x < 1230)
			{
				isAnimationStandingWaterGirl = false;
				WaterGirl.setTextureRect(IntRect(149 * moveWaterGirl, 1 * 160, 149, 160));
				if (clockw.getElapsedTime().asSeconds() >= 0.05)
				{
					moveWaterGirl++;
					if (moveWaterGirl > 10)moveWaterGirl = 0;

					clockw.restart();
				}
				WaterGirl.setScale(0.7f, 0.7f);
				WaterGirl.move(5, 0);

			}
			else if (Keyboard::isKeyPressed(Keyboard::Key::Left) && WaterGirl.getPosition().x > 50)
			{
				isAnimationStandingWaterGirl = false;
				WaterGirl.setTextureRect(IntRect(149 * moveWaterGirl, 1 * 160, 149, 160));
				if (clockw.getElapsedTime().asSeconds() >= 0.05)
				{
					moveWaterGirl++;
					if (moveWaterGirl > 10)moveWaterGirl = 0;

					clockw.restart();
				}
				WaterGirl.setScale(-0.7f, 0.7f);
				WaterGirl.move(-5, 0);

			}
			else { isAnimationStandingWaterGirl = true; }
		}


		//////////////////////
		///test
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
			sf::Vector2i mouse_position = sf::Mouse::getPosition(window);
			std::cout << mouse_position.x << "  " << mouse_position.y << "\n";
		}
		////////////////////////



		// set position hit box fireboy ( up )
		firboy_top.setPosition(Vector2f(FireBoy.getPosition().x, FireBoy.getPosition().y - 170));

		// set position hit box fireboy ( dowm )
		firboy_down.setPosition(Vector2f(FireBoy.getPosition().x, FireBoy.getPosition().y - 125));

		// set position hit box fireboy ( right )
		firboy_right.setPosition(Vector2f(FireBoy.getPosition().x + 20, FireBoy.getPosition().y - 150));

		// set position hit box fireboy ( left )
		firboy_left.setPosition(Vector2f(FireBoy.getPosition().x - 20, FireBoy.getPosition().y - 150));

		collision(window, firboy_down, firboy_top, isAnimationStandingWaterGirl, isAnimationStandingFireBoy, velocityFireBoy, velocityWaterGirl, firboy_left, firboy_right);

		bool r = 0;
		for (int i = 0; i < 30; i++) {
			if (level[1].ground[i].getGlobalBounds().intersects(firboy_right.getGlobalBounds()) && FireBoy.getPosition().x + 75 >= level[1].ground[i].getPosition().x && Keyboard::isKeyPressed(Keyboard::Key::D)) {

				//if (!isAnimationStandingFireBoy )
				FireBoy.move(-5, 0);
				firboy_down.setPosition(Vector2f(FireBoy.getPosition().x - 10, FireBoy.getPosition().y - 125));
			}
		}

		///

		for (int i = 0; i < 30; i++) {

			if (level[1].ground[i].getGlobalBounds().intersects(firboy_left.getGlobalBounds()) && firboy_left.getPosition().x <= (level[1].ground[i].getPosition().x + level[1].ground[i].getSize().x + 20) && Keyboard::isKeyPressed(Keyboard::Key::A)) {

				//	if (!isAnimationStandingFireBoy )
				FireBoy.move(5, 0);
				firboy_down.setPosition(Vector2f(FireBoy.getPosition().x + 10, FireBoy.getPosition().y - 125));


			}

		}


		window.clear();
		window.draw(level[1].background_levels[1]);
		window.draw(level[1].ground_levels[1]);
		/*for (int i = 0; i < 30; i++) {
			window.draw(level[1].ground[i]);
		}*/

		// window.draw(level[1].background_levels[1]);
	//	 window.draw(level[1].ground_levels[1]);
		window.draw(FireBoy);
		window.draw(WaterGirl);
		window.draw(firboy_top);
		window.draw(firboy_down);
		window.draw(firboy_right);
		window.draw(firboy_left);
		/*window.draw(hitpoxf);
		window.draw(hitpoxw);*/

		/*	window.draw(RectangleUp);
			window.draw(RectangleDown);
			window.draw(RectangleLeft);
			window.draw(RectangleRight);*/
		FireBoy.move(0, -velocityFireBoy);
		WaterGirl.move(0, -velocityWaterGirl);
		window.display();

	}
}

//modsas

