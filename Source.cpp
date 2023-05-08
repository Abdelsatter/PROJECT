#include<iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
using namespace std;
using namespace sf;
/////////////////////////////////////////////////////
RectangleShape test2;
////////////////////////////////////////////////////
void Game_Play(RenderWindow& window);
void Main_Menu(RenderWindow& window);

void Level1(RenderWindow& window);
void Level2(RenderWindow& window);
void fire_water_hitboxes(RenderWindow& window);
void MM_settings(RenderWindow& window, Sprite& mainmenu_Background, Sprite beam[], Sprite& mainmenu_title, Sprite& fb_MainMenu, Sprite& wg_MainMenu, Sprite& play_button, Sprite& settings, RectangleShape& settings_backgroundd, Sprite& Settings_background, RectangleShape& Settings_hitbox, Sprite& Music, Sprite& Sound, RectangleShape& Buttons_hitbox, Texture& music, Texture& sound, Sprite& Music2, Sprite& Sound2);
void collision_fireboy(RenderWindow& window, bool& isAnimationStandingFireBoy, double& velocityFireBoy, Sprite& FireBoy);
void collision_watergirl(RenderWindow& window, bool& isAnimationStandingWaterGirl, double& velocityWaterGirl, Sprite& WaterGirl);
void collision_boxes(RenderWindow& window);
void Animation(RenderWindow& window);
void button_collision();
void updatef_whitboxes(RenderWindow& window, Sprite& FireBoy, Sprite& WaterGirl);
void collision(RenderWindow& window, bool& isAnimationStandingFireBoy, double& velocityFireBoy, Sprite& FireBoy, bool& isAnimationStandingWaterGirl, double& velocityWaterGirl, Sprite& WaterGirl);
void draw(RenderWindow& window, Sprite& FireBoy, Sprite& WaterGirl);
struct {

	struct {
		Texture fireBoyImage;
		Sprite FireBoy;

		// hitbox (up_firboy)
		RectangleShape firboy_top;
		// hitbox (down_firboy)
		RectangleShape firboy_down;
		// hitbox (right_firboy)
		RectangleShape firboy_right;
		// hitbox (left_firboy)
		RectangleShape firboy_left;
		int animationStandingFireBoy = 0, moveFireBoy = 0;
		double velocityFireBoy = 0;
		bool isAnimationStandingFireBoy = true, isMoveFireBoy = true, animationUpFireBoy = 1, grounded = 0;
	}fireboy_st;
	struct {
		Texture  waterGirlImage;
		Sprite WaterGirl;
		// hitbox (up_watergirl)
		RectangleShape watergirl_top;
		// hitbox (down_watergirl)
		RectangleShape watergirl_down;
		// hitbox (right_watergirl)
		RectangleShape watergirl_right;
		// hitbox (left_watergirl)
		RectangleShape watergirl_left;
		int  animationStandingWaterGirl = 0;
		int  moveWaterGirl = 0;
		double  velocityWaterGirl = 0;
		bool isAnimationStandingWaterGirl = true, isMoveWaterGirl = true, grounded = 0;

	}watergirl_st;
}f_w;
struct {
	RectangleShape ground[60], boxes_down[10], boxes_right[10], boxes_top[10], boxes_left[10], button_up[10], button_down[10], lever_left_hitbox, lever_right_hitbox;
	Texture button, elevator, fireboyDoorStand, watergirlDoorStand, fireboydoormoving, watergirldoormoving, fireboydooropening, watergirldooropening, cubeImage, pause, smokeImage;
	Texture gr_levels[10], bgr_background[10], pondFireImage, pondWaterImage, coinFireImage, coinWaterImage, pondBlackImage, lever_off, lever_on, BlueLeverOff1, elevator2, lever_button_on;
	Sprite Button[10], Elevator[10], FireBoy_DoorStand, WaterGirl_DoorStand, FireBoy_DoorMoving, WaterGirl_DoorMoving, FireBoy_DoorOpening, WaterGirl_DoorOpening, cube[10], Pause, smoke[3];
	Sprite ground_levels[10], background_levels[10], pondFireBoy[10], pondWaterGirl[10], coinFireBoy[10], coinWaterGirl[10], pondBlack[10];
	ConvexShape convexs[60];
	bool  fireboy_dooropening = 0, watergirl_dooropening = 0, both_dooropening = 0, pauseclicked = 0;
	int animationDoorFireBoy = 0, animationDoorWaterGirl = 0, animationBothDoor = 0, animationSmoke[3] = { 0,0,0 }, animationPond[5] = { 0,0,0,0 }, isSmoke[3] = { 0,0,0 };
	Clock clockStandingFireBoy, clockStandingWaterGirl, clockMoveFireBoy, clockMoveWaterGirl, clockPond[5], clockSmoke[5], clockDoor[10], timer, ingame_setings_c;
	Time sa3a_s, sa3a_m;
	double velocityboxes[10];
	bool isStandingboxes[10], g_f_b_w[10] = {}, g_w_b_f[10] = {}, w_b_f_g[10] = {}, f_b_w_g[10] = {}, lever_open = 0, elevator_open = 0;
	Music mainMenu, soundLevel[10];
	SoundBuffer soundDeath, soundJumpFire, soundJumpWater, soundMainDeath, soundCoin, soundelevator, soundDoor;
	Sound death[3], Jump[3], mainDeath, Coin, elevatorSound, door[3];
	int fb_sc[20] = {}, wg_sc[20] = {};
	Font f, f2;
	Text fb_count, wg_count, elwaqt_s, elwaqt_m;
}level[10];
struct {
	RectangleShape Background, Settings_hitbox, Return_MM_hb, back_hb;
	Sprite settings_menu, Back_button;
	Texture settings_Menu, back_button;
	int number_Level = 2;
	bool return_to_MM = 0, win = 0;
}in_game;
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
void updatef_whitboxes(RenderWindow& window, Sprite& FireBoy, Sprite& WaterGirl) {

	// set position hit box fireboy ( up )
	f_w.fireboy_st.firboy_top.setPosition(Vector2f(FireBoy.getPosition().x, FireBoy.getPosition().y - 170));

	// set position hit box fireboy ( dowm )
	f_w.fireboy_st.firboy_down.setPosition(Vector2f(FireBoy.getPosition().x, FireBoy.getPosition().y - 127));

	// set position hit box fireboy ( right )
	f_w.fireboy_st.firboy_right.setPosition(Vector2f(FireBoy.getPosition().x + 11, FireBoy.getPosition().y - 150));

	// set position hit box fireboy ( left )
	f_w.fireboy_st.firboy_left.setPosition(Vector2f(FireBoy.getPosition().x - 5, FireBoy.getPosition().y - 150));


	//////////////////////////////////////////////////////////////
	// set position hit box fireboy ( up )
	f_w.watergirl_st.watergirl_top.setPosition(Vector2f(WaterGirl.getPosition().x, WaterGirl.getPosition().y - 170));

	// set position hit box fireboy ( dowm )
	f_w.watergirl_st.watergirl_down.setPosition(Vector2f(WaterGirl.getPosition().x, WaterGirl.getPosition().y - 130));

	// set position hit box fireboy ( right )
	f_w.watergirl_st.watergirl_right.setPosition(Vector2f(WaterGirl.getPosition().x + 11, WaterGirl.getPosition().y - 150));

	// set position hit box fireboy ( left )
	f_w.watergirl_st.watergirl_left.setPosition(Vector2f(WaterGirl.getPosition().x - 5, WaterGirl.getPosition().y - 150));

	///the box hit_boxes 
	level[1].boxes_down[1].setPosition(level[1].cube[1].getPosition().x, level[1].cube[1].getPosition().y + 25);
	level[1].boxes_top[1].setPosition(level[1].cube[1].getPosition().x, level[1].cube[1].getPosition().y - 25);
	level[1].boxes_left[1].setPosition(level[1].cube[1].getPosition().x - 25, level[1].cube[1].getPosition().y);
	level[1].boxes_right[1].setPosition(level[1].cube[1].getPosition().x + 25, level[1].cube[1].getPosition().y);

	///hit boxes elevator1 (up)
	level[1].ground[14].setPosition(Vector2f(level[1].Elevator[1].getPosition().x, level[1].Elevator[1].getPosition().y + 2));

	///hit boxes elevator1 (down)
	level[1].ground[25].setPosition(Vector2f(Vector2f(level[1].Elevator[1].getPosition().x, level[1].Elevator[1].getPosition().y + 28)));

	///hit boxes elevator1 (left)
	level[1].ground[26].setPosition(Vector2f(level[1].Elevator[1].getPosition().x, level[1].Elevator[1].getPosition().y));

	//hit boxes elevator2 (up)
	level[1].ground[27].setPosition(Vector2f(level[1].Elevator[2].getPosition().x, level[1].Elevator[2].getPosition().y + 2));

	///hit boxes elevator1 (down)
	level[1].ground[28].setPosition(Vector2f(Vector2f(level[1].Elevator[2].getPosition().x, level[1].Elevator[2].getPosition().y + 28)));

	///hit boxes elevator2 (right)
	level[1].ground[46].setPosition(Vector2f(level[1].Elevator[2].getPosition().x + 144, level[1].Elevator[2].getPosition().y));



}
void fire_water_hitboxes(RenderWindow& window) {

	// hitbox (up_firboy)
	f_w.fireboy_st.firboy_top.setSize(Vector2f(5, 20));
	f_w.fireboy_st.firboy_top.setFillColor(Color::Blue);
	f_w.fireboy_st.firboy_top.setOrigin(2.5, 10);

	// hitbox (down_firboy)
	f_w.fireboy_st.firboy_down.setSize(Vector2f(5, 7));
	f_w.fireboy_st.firboy_down.setFillColor(Color::Blue);
	f_w.fireboy_st.firboy_down.setOrigin(2.5f, 3.5f);

	// hitbox (right_firboy)
	f_w.fireboy_st.firboy_right.setSize(Vector2f(10, 40));
	f_w.fireboy_st.firboy_right.setFillColor(Color::Blue);
	f_w.fireboy_st.firboy_right.setOrigin(5, 20);

	// hitbox (left_firboy)
	f_w.fireboy_st.firboy_left.setSize(Vector2f(20, 40));
	f_w.fireboy_st.firboy_left.setFillColor(Color::Blue);
	f_w.fireboy_st.firboy_left.setOrigin(10, 20);

	////////////////////////////////////////////////////////////////////

	// hitbox (up_watergirl)
	f_w.watergirl_st.watergirl_top.setSize(Vector2f(5, 20));
	f_w.watergirl_st.watergirl_top.setFillColor(Color::Blue);
	f_w.watergirl_st.watergirl_top.setOrigin(2.5, 10);

	// hitbox (down_watergirl)
	f_w.watergirl_st.watergirl_down.setSize(Vector2f(5, 10));
	f_w.watergirl_st.watergirl_down.setFillColor(Color::Blue);
	f_w.watergirl_st.watergirl_down.setOrigin(2.5f, 5.f);

	// hitbox (right_watergirl)
	f_w.watergirl_st.watergirl_right.setSize(Vector2f(10, 40));
	f_w.watergirl_st.watergirl_right.setFillColor(Color::Blue);
	f_w.watergirl_st.watergirl_right.setOrigin(5, 20);

	// hitbox (left_watergirl)
	f_w.watergirl_st.watergirl_left.setSize(Vector2f(20, 40));
	f_w.watergirl_st.watergirl_left.setFillColor(Color::Blue);
	f_w.watergirl_st.watergirl_left.setOrigin(10, 20);
}
void Main_Menu(RenderWindow& window) {


	//sound main menu
	level[0].mainMenu.openFromFile("Menu_Music.wav");
	level[0].mainMenu.play();
	level[0].mainMenu.setLoop(true);


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

	/////////////---Settings Background---////////////////

	RectangleShape Settings_hitbox;
	Settings_hitbox.setSize(Vector2f(1280, 70));
	Settings_hitbox.setPosition(0, 0);
	RectangleShape settings_backgroundd;
	settings_backgroundd.setFillColor(Color(0, 0, 0, 156));
	settings_backgroundd.setSize(Vector2f(1280, 720));
	Sprite Settings_background;
	Texture settings_background;
	settings_background.loadFromFile("MM_Settings.png");
	Settings_background.setTexture(settings_background);
	//Settings_background.setPosition(130.5, 70);
	Settings_background.setPosition(130.5, 720);


	//Music, Sound and back buttons

	Sprite Music, Music2;
	Texture music, music2;
	music.loadFromFile("Music_on.png");
	music2.loadFromFile("Music_off.png");
	Music.setTexture(music);
	Music2.setTexture(music2);
	//Music.setPosition(408,315);
	Music.setPosition(408, 965);
	Music2.setPosition(408, 965);

	Sprite Sound, Sound2;
	Texture sound, sound2;
	sound.loadFromFile("Sound_on.png");
	sound2.loadFromFile("Sound_off.png");
	Sound.setTexture(sound);
	Sound2.setTexture(sound2);
	Sound.setPosition(760, 965);
	Sound2.setPosition(760, 965);
	in_game.back_button.loadFromFile("Back_button.png");
	in_game.Back_button.setTexture(in_game.back_button);
	in_game.Back_button.setPosition(452, 965);

	//Buttons and background hitboxes
	RectangleShape Buttons_hitbox;
	Buttons_hitbox.setSize(Vector2f(1280, 315));
	Buttons_hitbox.setPosition(0, 0);
	in_game.Return_MM_hb.setSize(Vector2f(1280, 5));
	in_game.Return_MM_hb.setPosition(0, 1338);
	in_game.back_hb.setSize(Vector2f(1280, 5));
	in_game.back_hb.setPosition(0, 520);



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
			if (nav == 0 && mousepos.x > 580 && mousepos.x < 700 && mousepos.y>340.5 && mousepos.y < 379.5) {
				play_button.setScale(0.9f, 0.9f);
				playclicked = 1;
			}
			else if (nav == 0 && mousepos.x > 35 && mousepos.x < 82 && mousepos.y>600 && mousepos.y < 649) {
				settings.setScale(0.9f, 0.9f);
				settingsclicked = 1;
			}

		}
		if (clock.getElapsedTime().asSeconds() > 0.10) {
			play_button.setScale(1.0f, 1.0f);
			settings.setScale(1.0f, 1.0f);

		}

		if (clock.getElapsedTime().asSeconds() > 0.3) {
			if (playclicked) {
				play_button.setScale(1.0f, 1.0f);
				nav = 1;
			}

			else if (settingsclicked) {
				settings.setScale(1.0f, 1.0f);
				nav = 2;
			}
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
			/*window.draw(in_game.back_hb);*/
		}
		else if (nav == 1) {
			level[0].mainMenu.stop();
			Game_Play(window);

		}
		else if (nav == 2) {
			MM_settings(window, mainmenu_Background, beam, mainmenu_title, fb_MainMenu, wg_MainMenu, play_button, settings, settings_backgroundd, Settings_background, Settings_hitbox, Music, Sound, Buttons_hitbox, music, sound, Music2, Sound2);
		}
		window.display();
	}

}
bool musicclicked = 0, soundclicked = 0;
void MM_settings(RenderWindow& window, Sprite& mainmenu_Background, Sprite beam[], Sprite& mainmenu_title, Sprite& fb_MainMenu, Sprite& wg_MainMenu, Sprite& play_button, Sprite& settings, RectangleShape& settings_backgroundd, Sprite& Settings_background, RectangleShape& Settings_hitbox, Sprite& Music, Sprite& Sound, RectangleShape& Buttons_hitbox, Texture& music, Texture& sound, Sprite& Music2, Sprite& Sound2) {



	//while (window.isOpen())
	//{
	Vector2i mousepos = Mouse::getPosition(window);


	if (Mouse::isButtonPressed(Mouse::Left)) {
		if (!(mousepos.x > 130.5 && mousepos.x < 1162.5 && mousepos.y > 115 && mousepos.y < 713)) {
			in_game.return_to_MM = 1;
		}
		else if (mousepos.x > 452 && mousepos.x < 716 && mousepos.y > 545 && mousepos.y < 636) {
			in_game.Back_button.setScale(0.9f, 0.9f);
			in_game.return_to_MM = 1;
		}
		else {
			in_game.Back_button.setScale(1.0f, 1.0f);
		}
		if (mousepos.x > 428 && mousepos.x < 493 && mousepos.y > 305 && mousepos.y < 365) {

			musicclicked = !musicclicked;
			Music2.setPosition(Music.getPosition().x, Music.getPosition().y);

		}
		else if (mousepos.x > 760 && mousepos.x < 840 && mousepos.y > 305 && mousepos.y < 365) {
			soundclicked = !soundclicked;
			Sound2.setPosition(Sound.getPosition().x, Sound.getPosition().y);
		}
	}
	if (in_game.return_to_MM == 0) {
		if (!Settings_hitbox.getGlobalBounds().intersects(Settings_background.getGlobalBounds()))
			Settings_background.move(0, -30);

		if (!Buttons_hitbox.getGlobalBounds().intersects(Music.getGlobalBounds())) {
			Music.move(0, -30);
			Music2.move(0, -30);
		}
		if (!Buttons_hitbox.getGlobalBounds().intersects(Sound.getGlobalBounds())) {
			Sound.move(0, -30);
			Sound2.move(0, -30);
		}
		if (!in_game.back_hb.getGlobalBounds().intersects(in_game.Back_button.getGlobalBounds())) {
			in_game.Back_button.move(0, -30);
		}
	}
	if (in_game.return_to_MM == 1) {
		if (!in_game.Return_MM_hb.getGlobalBounds().intersects(Settings_background.getGlobalBounds())) {
			Settings_background.move(0, 30);
			Music.move(0, 30);
			Sound.move(0, 30);
			Music2.move(0, 30);
			Sound2.move(0, 30);
			in_game.Back_button.move(0, 30);
		}
		else {
			in_game.return_to_MM = 0;
			Main_Menu(window);
		}
	}
	//	window.clear();
	window.draw(mainmenu_Background);
	for (int i = 0; i < 3; i++) {
		window.draw(beam[i]);
	}

	window.draw(mainmenu_title);
	window.draw(fb_MainMenu);
	window.draw(wg_MainMenu);
	window.draw(play_button);
	window.draw(settings);
	window.draw(settings_backgroundd);
	window.draw(Settings_background);
	if (!musicclicked)
		window.draw(Music);
	else
		window.draw(Music2);
	if (!soundclicked)
		window.draw(Sound);
	else
		window.draw(Sound2);
	window.draw(in_game.Back_button);
	//	window.display();
	//}
}
void Level1(RenderWindow& window) {


	//sound level1
	level[1].soundLevel[1].openFromFile("Level_Music.wav");
	level[1].soundLevel[1].play();
	level[1].soundLevel[1].setLoop(true);

	//sounds
	level[1].soundMainDeath.loadFromFile("death_sound.wav");
	level[1].mainDeath.setBuffer(level[1].soundMainDeath);
	level[1].soundCoin.loadFromFile("Diamond.wav");
	level[1].Coin.setBuffer(level[1].soundCoin);

	level[1].soundJumpFire.loadFromFile("Jump_fb.wav");
	level[1].Jump[1].setBuffer(level[1].soundJumpFire);
	level[1].soundDeath.loadFromFile("Death.wav");
	level[1].death[1].setBuffer(level[1].soundDeath);


	level[1].soundJumpWater.loadFromFile("Jump_wg.wav");
	level[1].Jump[2].setBuffer(level[1].soundJumpWater);
	level[1].soundDeath.loadFromFile("Death.wav");
	level[1].death[2].setBuffer(level[1].soundDeath);

	level[1].soundelevator.loadFromFile("elevator.wav");
	level[1].elevatorSound.setBuffer(level[1].soundelevator);

	level[1].soundDoor.loadFromFile("Door.wav");
	level[1].door[1].setBuffer(level[1].soundDoor);
	level[1].door[2].setBuffer(level[1].soundDoor);

	// button
	level[1].button.loadFromFile("CyanButton.png");
	level[1].Button[1].setTexture(level[1].button);
	level[1].Button[1].setPosition(Vector2f(986.5f, 280.f));
	level[1].Button[1].setScale(0.8f, 0.8f);

	/// hit_box button1_up
	level[1].button_up[1].setSize(Vector2f(4, 3));
	level[1].button_up[1].setPosition(Vector2f(level[1].Button[1].getPosition().x + 20, level[1].Button[1].getPosition().y - 4));

	/// hit_box button1_down
	level[1].button_down[1].setSize(Vector2f(4, 3));
	level[1].button_down[1].setPosition(Vector2f(level[1].Button[1].getPosition().x + 20, level[1].Button[1].getPosition().y + 20));

	level[1].Button[2].setTexture(level[1].button);
	level[1].Button[2].setPosition(Vector2f(363.5f, 381.f));
	level[1].Button[2].setScale(0.8f, 0.8f);

	/// hit_box button2_up
	level[1].button_up[2].setSize(Vector2f(4, 3));
	level[1].button_up[2].setPosition(Vector2f(level[1].Button[2].getPosition().x + 20, level[1].Button[2].getPosition().y - 4));

	/// hit_box button2_down
	level[1].button_down[2].setSize(Vector2f(4, 3));
	level[1].button_down[2].setPosition(Vector2f(level[1].Button[2].getPosition().x + 20, level[1].Button[2].getPosition().y + 20));

	///BlueLever_off2
	level[1].lever_off.loadFromFile("BlueLeverOff2.png");
	level[1].Button[3].setTexture(level[1].lever_off);
	level[1].Button[3].setScale(0.48f, 0.48f);
	level[1].Button[3].setPosition(Vector2f(263.5f, 470.f));

	///BlueLever_on2
	level[1].lever_button_on.loadFromFile("BlueLeverOn2.png");
	level[1].Button[6].setTexture(level[1].lever_button_on);
	level[1].Button[6].setScale(0.48f, 0.48f);
	level[1].Button[6].setPosition(Vector2f(263.5f, 470.f));




	///BlueLeverOff1
	level[1].BlueLeverOff1.loadFromFile("BlueLeverOff1.png");
	level[1].Button[4].setTexture(level[1].BlueLeverOff1);
	level[1].Button[4].setRotation(34.f);
	level[1].Button[4].setScale(0.48f, 0.48f);
	level[1].Button[4].setOrigin(69.5, 130.f);
	level[1].Button[4].setPosition(Vector2f(288.5f, 520.f));

	///BlueLever_on1
	level[1].lever_on.loadFromFile("BlueLeverOn1.png");
	level[1].Button[5].setTexture(level[1].lever_on);
	level[1].Button[5].setRotation(-34.f);
	level[1].Button[5].setScale(0.48f, 0.48f);
	level[1].Button[5].setOrigin(69.5, 130.f);



	//lever_left_hitbox
	level[1].lever_left_hitbox.setSize(Vector2f(2.f, 3.f));
	level[1].lever_left_hitbox.setPosition(Vector2f(270.5f, 500.f));

	//lever_right_hitbox
	level[1].lever_right_hitbox.setSize(Vector2f(2.f, 3.f));
	level[1].lever_right_hitbox.setPosition(Vector2f(317.5f, 500.f));



	// elevator
	level[1].elevator.loadFromFile("Cyanelevator.png");
	level[1].Elevator[1].setTexture(level[1].elevator);
	level[1].Elevator[1].setPosition(Vector2f(1107.f, 330.f));
	level[1].Elevator[1].setScale(0.65f, 0.5f);

	/// elevator
	level[1].elevator2.loadFromFile("BlueElevatorH.png");
	level[1].Elevator[2].setTexture(level[1].elevator2);
	level[1].Elevator[2].setPosition(Vector2f(23.f, 387.f));
	level[1].Elevator[2].setScale(0.65f, 0.5f);

	//smoke die
	level[1].smokeImage.loadFromFile("Smoke.png");
	level[1].smoke[1].setTexture(level[1].smokeImage);
	level[1].smoke[2].setTexture(level[1].smokeImage);

	//Pause
	level[1].pause.loadFromFile("Pause.png");
	level[1].Pause.setTexture(level[1].pause);
	level[1].Pause.setPosition(1230, 8);
	level[1].Pause.setScale(0.85, 0.85);

	//pond fireboy
	level[1].pondFireImage.loadFromFile("Lava.png");
	level[1].pondFireBoy[1].setTexture(level[1].pondFireImage);
	level[1].pondFireBoy[1].setPosition(594, 707);

	//pond watergirl
	level[1].pondWaterImage.loadFromFile("Water.png");
	level[1].pondWaterGirl[1].setTexture(level[1].pondWaterImage);
	level[1].pondWaterGirl[1].setPosition(858, 707);

	//pond black
	level[1].pondBlackImage.loadFromFile("Acid.png");
	level[1].pondBlack[1].setTexture(level[1].pondBlackImage);
	level[1].pondBlack[1].setPosition(790, 558);

	// coin fireboy
	level[1].coinFireImage.loadFromFile("fireGem.png");
	level[1].coinFireBoy[1].setTexture(level[1].coinFireImage);
	level[1].coinFireBoy[1].setPosition(657.5f, 647.5f);
	level[1].coinFireBoy[1].setScale(0.5f, 0.5f);
	level[1].coinFireBoy[1].setOrigin(level[1].coinFireBoy[1].getGlobalBounds().width / 2, level[1].coinFireBoy[1].getGlobalBounds().height / 2);

	level[1].coinFireBoy[2].setTexture(level[1].coinFireImage);
	level[1].coinFireBoy[2].setPosition(255.5f, 338.5f);
	level[1].coinFireBoy[2].setScale(0.5f, 0.5f);
	level[1].coinFireBoy[2].setOrigin(level[1].coinFireBoy[2].getGlobalBounds().width / 2, level[1].coinFireBoy[2].getGlobalBounds().height / 2);

	level[1].coinFireBoy[3].setTexture(level[1].coinFireImage);
	level[1].coinFireBoy[3].setPosition(381.5f, 62.f);
	level[1].coinFireBoy[3].setScale(0.5f, 0.5f);
	level[1].coinFireBoy[3].setOrigin(level[1].coinFireBoy[3].getGlobalBounds().width / 2, level[1].coinFireBoy[3].getGlobalBounds().height / 2);

	level[1].coinFireBoy[4].setTexture(level[1].coinFireImage);
	level[1].coinFireBoy[4].setPosition(601.f, 99.5f);
	level[1].coinFireBoy[4].setScale(0.5f, 0.5f);
	level[1].coinFireBoy[4].setOrigin(level[1].coinFireBoy[4].getGlobalBounds().width / 2, level[1].coinFireBoy[4].getGlobalBounds().height / 2);


	// coin watergirl
	level[1].coinWaterImage.loadFromFile("waterGem.png");
	level[1].coinWaterGirl[1].setTexture(level[1].coinWaterImage);
	level[1].coinWaterGirl[1].setPosition(920.3f, 647.5f);
	level[1].coinWaterGirl[1].setScale(0.5f, 0.5f);
	level[1].coinWaterGirl[1].setOrigin(level[1].coinWaterGirl[1].getGlobalBounds().width / 2, level[1].coinWaterGirl[1].getGlobalBounds().height / 2);

	level[1].coinWaterGirl[2].setTexture(level[1].coinWaterImage);
	level[1].coinWaterGirl[2].setPosition(755.f, 353.5f);
	level[1].coinWaterGirl[2].setScale(0.5f, 0.5f);
	level[1].coinWaterGirl[2].setOrigin(level[1].coinWaterGirl[2].getGlobalBounds().width / 2, level[1].coinWaterGirl[2].getGlobalBounds().height / 2);

	level[1].coinWaterGirl[3].setTexture(level[1].coinWaterImage);
	level[1].coinWaterGirl[3].setPosition(60.f, 129.5f);
	level[1].coinWaterGirl[3].setScale(0.5f, 0.5f);
	level[1].coinWaterGirl[3].setOrigin(level[1].coinWaterGirl[3].getGlobalBounds().width / 2, level[1].coinWaterGirl[3].getGlobalBounds().height / 2);

	level[1].coinWaterGirl[4].setTexture(level[1].coinWaterImage);
	level[1].coinWaterGirl[4].setPosition(756.5f, 99.5f);
	level[1].coinWaterGirl[4].setScale(0.5f, 0.5f);
	level[1].coinWaterGirl[4].setOrigin(level[1].coinWaterGirl[4].getGlobalBounds().width / 2, level[1].coinWaterGirl[4].getGlobalBounds().height / 2);


	//set fireboy
	f_w.fireboy_st.fireBoyImage.loadFromFile("Fireboy.png");
	f_w.fireboy_st.FireBoy.setTexture(f_w.fireboy_st.fireBoyImage);
	f_w.fireboy_st.FireBoy.setPosition(50, 830);
	f_w.fireboy_st.FireBoy.setOrigin(f_w.fireboy_st.FireBoy.getLocalBounds().width / 38, f_w.fireboy_st.FireBoy.getLocalBounds().height / 2);
	f_w.fireboy_st.FireBoy.setScale(0.7f, 0.7f);
	//set watergirl
	f_w.watergirl_st.waterGirlImage.loadFromFile("Watergirl.png");
	f_w.watergirl_st.WaterGirl.setTexture(f_w.watergirl_st.waterGirlImage);
	f_w.watergirl_st.WaterGirl.setPosition(50, 730);
	f_w.watergirl_st.WaterGirl.setOrigin(f_w.watergirl_st.WaterGirl.getLocalBounds().width / 60, f_w.watergirl_st.WaterGirl.getLocalBounds().height / 2);
	f_w.watergirl_st.WaterGirl.setScale(0.7f, 0.7f);
	//set fireboy's door
	level[1].fireboyDoorStand.loadFromFile("fbDoor.png");
	level[1].FireBoy_DoorStand.setTexture(level[1].fireboyDoorStand);
	level[1].FireBoy_DoorStand.setPosition(1050, 61);
	level[1].FireBoy_DoorStand.setScale(0.7f, 0.7f);
	//set watergirl's door
	level[1].watergirlDoorStand.loadFromFile("wgDoor.png");
	level[1].WaterGirl_DoorStand.setTexture(level[1].watergirlDoorStand);
	level[1].WaterGirl_DoorStand.setPosition(1150, 61);
	level[1].WaterGirl_DoorStand.setScale(0.7f, 0.7f);
	//set Fireboy door opening
	level[1].fireboydooropening.loadFromFile("fb_door.png");
	level[1].FireBoy_DoorOpening.setTexture(level[1].fireboydooropening);
	level[1].FireBoy_DoorOpening.setPosition(1060, 78);
	level[1].FireBoy_DoorOpening.setScale(0.71f, 0.72f);
	//set Watergirl door opening
	level[1].watergirldooropening.loadFromFile("wg_door.png");
	level[1].WaterGirl_DoorOpening.setTexture(level[1].watergirldooropening);
	level[1].WaterGirl_DoorOpening.setPosition(1160, 78);
	level[1].WaterGirl_DoorOpening.setScale(0.71f, 0.71f);
	//set Fireboy moving door
	level[1].fireboydoormoving.loadFromFile("fbWin.png");
	level[1].FireBoy_DoorMoving.setTexture(level[1].fireboydoormoving);
	level[1].FireBoy_DoorMoving.setPosition(1050, 61);
	level[1].FireBoy_DoorMoving.setScale(0.7f, 0.7f);
	//set Watergirl moving door
	level[1].watergirldoormoving.loadFromFile("wgWin.png");
	level[1].WaterGirl_DoorMoving.setTexture(level[1].watergirldoormoving);
	level[1].WaterGirl_DoorMoving.setPosition(1150, 61);
	level[1].WaterGirl_DoorMoving.setScale(0.7f, 0.7f);

	// set cube
	level[1].cubeImage.loadFromFile("moveCube.png");
	level[1].cube[1].setTexture(level[1].cubeImage);
	level[1].cube[1].setPosition(728, 215);
	level[1].cube[1].setOrigin(level[1].cube[1].getGlobalBounds().width / 2, level[1].cube[1].getGlobalBounds().height / 2);
	level[1].cube[1].setScale(0.7f, 0.7f);

	///set the box hit box
	level[1].boxes_down[1].setSize(Vector2f(50, 5));
	level[1].boxes_down[1].setOrigin(25.f, 2.5f);

	level[1].boxes_top[1].setSize(Vector2f(50.f, 5.f));
	level[1].boxes_top[1].setOrigin(25.f, 2.5f);

	level[1].boxes_left[1].setSize(Vector2f(5, 50));
	level[1].boxes_left[1].setOrigin(2.5f, 25.f);

	level[1].boxes_right[1].setSize(Vector2f(5, 50));
	level[1].boxes_right[1].setOrigin(2.5f, 25.f);
	//////////////////////////////////////////////////////////////////////////////
	//ground
	level[1].gr_levels[1].loadFromFile("Level_1_ground.png");
	level[1].ground_levels[1].setTexture(level[1].gr_levels[1]);


	level[1].ground_levels[1].setScale(1.6, 1.2);


	//background
	level[1].bgr_background[1].loadFromFile("gamplay_background.png");
	level[1].background_levels[1].setTexture(level[1].bgr_background[1]);
	//level[1].background_levels[1].setScale(1.6, 1.2);

	//game levels
	level[1].ground[0].setSize(Vector2f(593, 20));
	level[1].ground[0].setPosition(Vector2f(0, 710));
	level[1].ground[0].setFillColor(Color::Cyan);

	level[1].ground[1].setSize(Vector2f(107, 2));
	level[1].ground[1].setPosition(Vector2f(752, 710));
	level[1].ground[1].setFillColor(Color::Cyan);

	level[1].ground[2].setSize(Vector2f(260, 2));
	level[1].ground[2].setPosition(Vector2f(1016, 710));
	level[1].ground[2].setFillColor(Color::Cyan);

	level[1].ground[3].setSize(Vector2f(2, 100));    //vertical
	level[1].ground[3].setPosition(Vector2f(1157, 664));
	level[1].ground[3].setFillColor(Color::Yellow);


	level[1].ground[4].setSize(Vector2f(240, 2));
	level[1].ground[4].setPosition(Vector2f(1188, 640));
	level[1].ground[4].setFillColor(Color::Cyan);

	level[1].ground[5].setSize(Vector2f(137, 2));
	level[1].ground[5].setPosition(Vector2f(950, 565));
	level[1].ground[5].setFillColor(Color::Cyan);

	level[1].ground[6].setSize(Vector2f(190, 2));
	level[1].ground[6].setPosition(Vector2f(600, 560));
	level[1].ground[6].setFillColor(Color::Cyan);

	/////////////////// lava && water//////////////////////
	level[1].ground[7].setSize(Vector2f(1700, 2));
	level[1].ground[7].setPosition(Vector2f(300, 719));
	level[1].ground[7].setFillColor(Color::Cyan);




	level[1].ground[8].setSize(Vector2f(563, 2));
	level[1].ground[8].setPosition(Vector2f(0, 515));
	level[1].ground[8].setFillColor(Color::Cyan);

	level[1].ground[9].setSize(Vector2f(415, 2));
	level[1].ground[9].setPosition(Vector2f(0, 610));
	level[1].ground[9].setFillColor(Color::Cyan);

	level[1].ground[10].setSize(Vector2f(480, 2));
	level[1].ground[10].setPosition(Vector2f(170, 390));
	level[1].ground[10].setFillColor(Color::Cyan);



	level[1].ground[12].setSize(Vector2f(650, 2));
	level[1].ground[12].setPosition(Vector2f(675, 415));
	level[1].ground[12].setFillColor(Color::Cyan);

	/////////////hit box elevator up////////////
	level[1].ground[14].setSize(Vector2f(144, 2));
	level[1].ground[14].setFillColor(Color::Cyan);


	level[1].ground[15].setSize(Vector2f(90, 2));
	level[1].ground[15].setPosition(Vector2f(1183, 507));
	level[1].ground[15].setFillColor(Color::Cyan);

	level[1].ground[16].setSize(Vector2f(188, 2));
	level[1].ground[16].setPosition(Vector2f(0, 190));
	level[1].ground[16].setFillColor(Color::Cyan);

	level[1].ground[17].setSize(Vector2f(550, 2));
	level[1].ground[17].setPosition(Vector2f(145, 290));
	level[1].ground[17].setFillColor(Color::Cyan);

	level[1].ground[18].setSize(Vector2f(230, 2));
	level[1].ground[18].setPosition(Vector2f(660, 245));
	level[1].ground[18].setFillColor(Color::Cyan);

	level[1].ground[19].setSize(Vector2f(220, 2));
	level[1].ground[19].setPosition(Vector2f(890, 290));
	level[1].ground[19].setFillColor(Color::Cyan);


	level[1].ground[20].setSize(Vector2f(790, 2));
	level[1].ground[20].setPosition(Vector2f(520, 163));
	level[1].ground[20].setFillColor(Color::Cyan);



	level[1].ground[22].setSize(Vector2f(70, 2));
	level[1].ground[22].setPosition(Vector2f(360, 115));
	level[1].ground[22].setFillColor(Color::Cyan);

	level[1].ground[23].setSize(Vector2f(80, 2));
	level[1].ground[23].setPosition(Vector2f(420, 140));
	level[1].ground[23].setFillColor(Color::Cyan);

	level[1].ground[24].setSize(Vector2f(157, 2));
	level[1].ground[24].setPosition(Vector2f(953, 330));
	level[1].ground[24].setFillColor(Color::Cyan);

	////////////////hit box elevator down////////////
	level[1].ground[25].setSize(Vector2f(144, 2));
	level[1].ground[25].setFillColor(Color::Cyan);

	////////////////hit box elevator left////////////
	level[1].ground[26].setSize(Vector2f(2, 30));
	level[1].ground[26].setFillColor(Color::Yellow);

	////////////////hit box elevator2 up////////////
	level[1].ground[27].setSize(Vector2f(144, 2));
	level[1].ground[27].setFillColor(Color::Cyan);

	////////////////hit box elevator2 down////////////
	level[1].ground[28].setSize(Vector2f(144, 2));
	level[1].ground[28].setFillColor(Color::Cyan);


	level[1].ground[21].setSize(Vector2f(390, 2));
	level[1].ground[21].setPosition(Vector2f(24, 631));
	level[1].ground[21].setFillColor(Color::Cyan);

	level[1].ground[29].setSize(Vector2f(2, 20));
	level[1].ground[29].setPosition(Vector2f(415, 611));
	level[1].ground[29].setFillColor(Color::Yellow);


	level[1].ground[30].setSize(Vector2f(450, 2));
	level[1].ground[30].setPosition(Vector2f(556, 577));
	level[1].ground[30].setFillColor(Color::Cyan);


	level[1].ground[31].setSize(Vector2f(175, 2));
	level[1].ground[31].setPosition(Vector2f(929, 576));
	level[1].ground[31].setFillColor(Color::Cyan);


	level[1].ground[32].setSize(Vector2f(440, 2));
	level[1].ground[32].setPosition(Vector2f(622, 430));
	level[1].ground[32].setFillColor(Color::Cyan);


	level[1].ground[33].setSize(Vector2f(420, 2));
	level[1].ground[33].setPosition(Vector2f(173, 408));
	level[1].ground[33].setFillColor(Color::Cyan);


	level[1].ground[34].setSize(Vector2f(470, 2));
	level[1].ground[34].setPosition(Vector2f(23, 529));
	level[1].ground[34].setFillColor(Color::Cyan);


	level[1].ground[35].setSize(Vector2f(900, 2));
	level[1].ground[35].setPosition(Vector2f(23, 310));
	level[1].ground[35].setFillColor(Color::Cyan);


	level[1].ground[36].setSize(Vector2f(800, 2));
	level[1].ground[36].setPosition(Vector2f(554, 184));
	level[1].ground[36].setFillColor(Color::Cyan);


	level[1].ground[37].setSize(Vector2f(157, 2));
	level[1].ground[37].setPosition(Vector2f(397, 232));
	level[1].ground[37].setFillColor(Color::Cyan);


	level[1].ground[38].setSize(Vector2f(1300, 2));
	level[1].ground[38].setPosition(Vector2f(23, 34));
	level[1].ground[38].setFillColor(Color::Cyan);


	level[1].ground[39].setSize(Vector2f(2, 75));
	level[1].ground[39].setPosition(Vector2f(397, 157));
	level[1].ground[39].setFillColor(Color::Yellow);


	level[1].ground[40].setSize(Vector2f(2, 50));
	level[1].ground[40].setPosition(Vector2f(553, 183));
	level[1].ground[40].setFillColor(Color::Yellow);


	level[1].ground[41].setSize(Vector2f(2, 50));
	level[1].ground[41].setPosition(Vector2f(660, 245));
	level[1].ground[41].setFillColor(Color::Yellow);


	level[1].ground[42].setSize(Vector2f(2, 45));
	level[1].ground[42].setPosition(Vector2f(1107, 289));
	level[1].ground[42].setFillColor(Color::Yellow);


	level[1].ground[43].setSize(Vector2f(2, 20));
	level[1].ground[43].setPosition(Vector2f(170, 389));
	level[1].ground[43].setFillColor(Color::Yellow);


	level[1].ground[44].setSize(Vector2f(2, 100));
	level[1].ground[44].setPosition(Vector2f(184, 190));
	level[1].ground[44].setFillColor(Color::Yellow);


	level[1].ground[45].setSize(Vector2f(25, 2));
	level[1].ground[45].setPosition(Vector2f(341, 135));
	level[1].ground[45].setFillColor(Color::Cyan);

	////////////////hit box elevator2 down////////////
	level[1].ground[46].setSize(Vector2f(2, 30));
	level[1].ground[46].setFillColor(Color::Yellow);

	//////////////////the ground for the elevator2 to stop down////////////
	level[1].ground[47].setSize(Vector2f(20, 2));
	level[1].ground[47].setPosition(Vector2f(20, 490));



	//level[1].ground[48].setSize(Vector2f(40, 2));
	//level[1].ground[48].setRotation(37.f);      //////////
	//level[1].ground[48].setPosition(Vector2f(924, 309));
	//level[1].ground[48].setFillColor(Color::Magenta);


	//level[1].ground[49].setSize(Vector2f(80, 2));
	//level[1].ground[49].setRotation(37.f);      //////////
	//level[1].ground[49].setPosition(Vector2f(492, 529));
	//level[1].ground[49].setFillColor(Color::Magenta);


	//level[1].ground[50].setSize(Vector2f(40, 2));
	//level[1].ground[50].setRotation(27.f);      //////////
	//level[1].ground[50].setPosition(Vector2f(779, 559));
	//level[1].ground[50].setFillColor(Color::Magenta);


	//level[1].ground[51].setSize(Vector2f(25, 2));
	//level[1].ground[51].setRotation(147.f);      //////////
	//level[1].ground[51].setPosition(Vector2f(952, 565));
	//level[1].ground[51].setFillColor(Color::Magenta);


	//level[1].ground[52].setSize(Vector2f(25, 2));
	//level[1].ground[52].setRotation(27.f);      //////////
	//level[1].ground[52].setPosition(Vector2f(1084, 565));
	//level[1].ground[52].setFillColor(Color::Magenta);


	//level[1].ground[53].setSize(Vector2f(2, 40));
	//level[1].ground[53].setRotation(47.f);      //////////
	//level[1].ground[53].setPosition(Vector2f(1186, 639));
	//level[1].ground[53].setFillColor(Color::Magenta);


	level[1].ground[54].setSize(Vector2f(34, 2));
	level[1].ground[54].setPosition(Vector2f(1087, 454));
	level[1].ground[54].setFillColor(Color::Cyan);


	////////////////////////////convexshapes//////////////////////////////////

	level[1].convexs[0].setPointCount(3);
	level[1].convexs[0].setFillColor(Color::Green);
	level[1].convexs[0].setPoint(0, sf::Vector2f(889.f, 243.f));
	level[1].convexs[0].setPoint(1, sf::Vector2f(915.f, 264.f));
	level[1].convexs[0].setPoint(2, sf::Vector2f(908.f, 266.f));

	//////////////////////

	level[1].convexs[1].setPointCount(3);
	level[1].convexs[1].setFillColor(Color::Green);
	level[1].convexs[1].setPoint(0, sf::Vector2f(918.f, 266.f));
	level[1].convexs[1].setPoint(1, sf::Vector2f(945.f, 287.f));
	level[1].convexs[1].setPoint(2, sf::Vector2f(935.f, 292.f));

	level[1].convexs[2].setPointCount(3);
	level[1].convexs[2].setFillColor(Color::Red);
	level[1].convexs[2].setPoint(0, sf::Vector2f(357.5f, 115.5f));
	level[1].convexs[2].setPoint(1, sf::Vector2f(335.f, 137.5f));
	level[1].convexs[2].setPoint(2, sf::Vector2f(341.f, 137.5f));

	level[1].convexs[3].setPointCount(3);
	level[1].convexs[3].setFillColor(Color::Green);
	level[1].convexs[3].setPoint(0, sf::Vector2f(424.f, 115.5f));
	level[1].convexs[3].setPoint(1, sf::Vector2f(451.f, 137.5f));
	level[1].convexs[3].setPoint(2, sf::Vector2f(457.f, 137.5f));

	level[1].convexs[4].setPointCount(3);
	level[1].convexs[4].setFillColor(Color::Green);
	level[1].convexs[4].setPoint(0, sf::Vector2f(490.5f, 130.5f));
	level[1].convexs[4].setPoint(1, sf::Vector2f(526.f, 166.f));
	level[1].convexs[4].setPoint(2, sf::Vector2f(522.f, 166.f));


	level[1].convexs[5].setPointCount(3);
	level[1].convexs[5].setFillColor(Color::Green);
	level[1].convexs[5].setPoint(0, sf::Vector2f(652.5f, 388.5f));
	level[1].convexs[5].setPoint(1, sf::Vector2f(689.f, 415.f));
	level[1].convexs[5].setPoint(2, sf::Vector2f(685.f, 415.f));

	level[1].convexs[6].setPointCount(3);
	level[1].convexs[6].setFillColor(Color::Green);
	level[1].convexs[6].setPoint(0, sf::Vector2f(557.f, 512.f));
	level[1].convexs[6].setPoint(1, sf::Vector2f(582.f, 530.5f));
	level[1].convexs[6].setPoint(2, sf::Vector2f(571.f, 528.5f));
	////////////////////////////////////////////////////////

	/// right
	level[1].convexs[8].setPointCount(3);
	level[1].convexs[8].setFillColor(Color::Green);
	level[1].convexs[8].setPoint(0, sf::Vector2f(785.f, 557.f));
	level[1].convexs[8].setPoint(1, sf::Vector2f(818.f, 579.f));
	level[1].convexs[8].setPoint(2, sf::Vector2f(805.f, 579.f));

	////rignt 
	level[1].convexs[9].setPointCount(3);
	level[1].convexs[9].setFillColor(Color::Green);
	level[1].convexs[9].setPoint(0, sf::Vector2f(1086.f, 565.f));
	level[1].convexs[9].setPoint(1, sf::Vector2f(1107.f, 579.f));
	level[1].convexs[9].setPoint(2, sf::Vector2f(1092.f, 579.f));

	////rignt 
	level[1].convexs[10].setPointCount(3);
	level[1].convexs[10].setFillColor(Color::Green);
	level[1].convexs[10].setPoint(0, sf::Vector2f(596.f, 712.f));
	level[1].convexs[10].setPoint(1, sf::Vector2f(616.f, 725.f));
	level[1].convexs[10].setPoint(2, sf::Vector2f(597.f, 729.f));

	////rignt 
	level[1].convexs[11].setPointCount(3);
	level[1].convexs[11].setFillColor(Color::Green);
	level[1].convexs[11].setPoint(0, sf::Vector2f(858.f, 712.f));
	level[1].convexs[11].setPoint(1, sf::Vector2f(870.f, 721.f));
	level[1].convexs[11].setPoint(2, sf::Vector2f(864.f, 723.f));

	////left
	level[1].convexs[12].setPointCount(3);
	level[1].convexs[12].setFillColor(Color::Red);
	level[1].convexs[12].setPoint(0, sf::Vector2f(951.5f, 562.f));
	level[1].convexs[12].setPoint(1, sf::Vector2f(922.f, 579.5f));
	level[1].convexs[12].setPoint(2, sf::Vector2f(932.f, 577.5f));

	////left
	level[1].convexs[13].setPointCount(3);
	level[1].convexs[13].setFillColor(Color::Red);
	level[1].convexs[13].setPoint(0, sf::Vector2f(1185.f, 642.f));
	level[1].convexs[13].setPoint(1, sf::Vector2f(1155.f, 665.f));
	level[1].convexs[13].setPoint(2, sf::Vector2f(1164.f, 665.f));

	////left/////////
	level[1].convexs[14].setPointCount(3);
	level[1].convexs[14].setFillColor(Color::Red);
	level[1].convexs[14].setPoint(0, sf::Vector2f(1015.f, 712.f));
	level[1].convexs[14].setPoint(1, sf::Vector2f(1001.f, 723.f));
	level[1].convexs[14].setPoint(2, sf::Vector2f(1012.f, 723.f));

	////left
	level[1].convexs[15].setPointCount(3);
	level[1].convexs[15].setFillColor(Color::Red);
	level[1].convexs[15].setPoint(0, sf::Vector2f(752.f, 712.f));
	level[1].convexs[15].setPoint(1, sf::Vector2f(735.f, 725.f));
	level[1].convexs[15].setPoint(2, sf::Vector2f(753.f, 725.f));

	////down----------------------//////////////////////////////////////////////////



	level[1].convexs[16].setPointCount(3);
	level[1].convexs[16].setFillColor(Color::Black);
	level[1].convexs[16].setPoint(0, sf::Vector2f(494.f, 527.f));
	level[1].convexs[16].setPoint(1, sf::Vector2f(524.f, 551.f));
	level[1].convexs[16].setPoint(2, sf::Vector2f(537.f, 551.f));

	level[1].convexs[23].setPointCount(3);
	level[1].convexs[23].setFillColor(Color::Black);
	level[1].convexs[23].setPoint(0, sf::Vector2f(524.f, 551.f));
	level[1].convexs[23].setPoint(1, sf::Vector2f(557.f, 576.f));
	level[1].convexs[23].setPoint(2, sf::Vector2f(569.f, 576.f));

	level[1].convexs[7].setPointCount(3);
	level[1].convexs[7].setFillColor(Color::Black);
	level[1].convexs[7].setPoint(0, sf::Vector2f(365.f, 138.f));
	level[1].convexs[7].setPoint(1, sf::Vector2f(397.f, 160.f));
	level[1].convexs[7].setPoint(2, sf::Vector2f(405.f, 160.f));

	level[1].convexs[20].setPointCount(3);
	level[1].convexs[20].setFillColor(Color::Black);
	level[1].convexs[20].setPoint(0, sf::Vector2f(926.5f, 310.5f));
	level[1].convexs[20].setPoint(1, sf::Vector2f(951.f, 331.5f));
	level[1].convexs[20].setPoint(2, sf::Vector2f(955.f, 331.f));

	level[1].convexs[17].setPointCount(3);
	level[1].convexs[17].setFillColor(Color::Black);
	level[1].convexs[17].setPoint(0, sf::Vector2f(596.5f, 412.f));
	level[1].convexs[17].setPoint(1, sf::Vector2f(622.5f, 432.5f));
	level[1].convexs[17].setPoint(2, sf::Vector2f(620.f, 432.5f));

	level[1].convexs[18].setPointCount(3);
	level[1].convexs[18].setFillColor(Color::Black);
	level[1].convexs[18].setPoint(0, sf::Vector2f(1058.f, 433.5f));
	level[1].convexs[18].setPoint(1, sf::Vector2f(1088.f, 455.5f));
	level[1].convexs[18].setPoint(2, sf::Vector2f(1094.f, 455.5f));



	level[1].convexs[19].setPointCount(3);
	level[1].convexs[19].setFillColor(Color::Black);
	level[1].convexs[19].setPoint(0, sf::Vector2f(1120.f, 457.5f));
	level[1].convexs[19].setPoint(1, sf::Vector2f(1156.5f, 486.5f));
	level[1].convexs[19].setPoint(2, sf::Vector2f(1173.f, 486.5f));

	level[1].convexs[22].setPointCount(3);
	level[1].convexs[22].setFillColor(Color::Black);
	level[1].convexs[22].setPoint(0, sf::Vector2f(1156.5f, 486.5f));
	level[1].convexs[22].setPoint(1, sf::Vector2f(1186.5f, 506.5f));
	level[1].convexs[22].setPoint(2, sf::Vector2f(1192.f, 506.5f));

	level[1].convexs[21].setPointCount(3);
	level[1].convexs[21].setFillColor(Color::Green);
	level[1].convexs[21].setPoint(0, sf::Vector2f(579.f, 528.5f));
	level[1].convexs[21].setPoint(1, sf::Vector2f(617.f, 558.5f));
	level[1].convexs[21].setPoint(2, sf::Vector2f(598.f, 554.5f));



	///main pause
	in_game.Settings_hitbox.setSize(Vector2f(1280, 315));
	in_game.Background.setSize(Vector2f(1280, 720));
	in_game.Background.setFillColor(Color(0, 0, 0, 156));
	in_game.settings_Menu.loadFromFile("MM_Settings.png");
	in_game.settings_menu.setTexture(in_game.settings_Menu);
	in_game.settings_menu.setPosition(130.5, 720);
	//settings_menu.setPosition(130.5,70); 
	//draw(window);
	///////////////////fb_wg_score///////////////

	level[1].f.loadFromFile("Game_Of_Squids.ttf");
	level[1].fb_count.setFont(level[1].f);
	level[1].wg_count.setFont(level[1].f);
	level[1].fb_count.setString(to_string(level[1].fb_sc[1]));
	level[1].wg_count.setString(to_string(level[1].wg_sc[1]));
	level[1].wg_count.setPosition(1180, 32);
	level[1].fb_count.setPosition(50, 32);
	level[1].fb_count.setFillColor(Color::Red);
	level[1].wg_count.setFillColor(Color::Blue);
	level[1].fb_count.setScale(1.4, 1.4);
	level[1].wg_count.setScale(1.4, 1.4);

	////////////////////////timer//////////////////////////

	level[1].timer.getElapsedTime().asSeconds();
	level[1].timer.restart();
	level[1].sa3a_s = level[1].timer.getElapsedTime();
	level[1].elwaqt_s.setFont(level[1].f);
	level[1].elwaqt_s.setString(to_string((int)level[1].sa3a_s.asSeconds()));
	level[1].elwaqt_s.setPosition(600, 0);
	level[1].elwaqt_s.setFillColor(Color::Magenta);
	////////////////////settings call///////////////////////

	in_game.Settings_hitbox.setSize(Vector2f(1280, 100));
	in_game.Background.setSize(Vector2f(1280, 720));
	in_game.Background.setFillColor(Color(0, 0, 0, 156));
	in_game.settings_Menu.loadFromFile("MM_Settings.png");
	in_game.settings_menu.setTexture(in_game.settings_Menu);
	in_game.settings_menu.setPosition(130.5, 720);
	//settings_menu.setPosition(130.5,70); 
	//draw(window);


}
void Level2(RenderWindow& window) {

	//sound
	level[2].soundJumpFire.loadFromFile("Jump_fb.wav");
	level[2].Jump[1].setBuffer(level[2].soundJumpFire);
	level[2].soundDeath.loadFromFile("Death.wav");
	level[2].death[1].setBuffer(level[2].soundDeath);


	level[2].soundJumpWater.loadFromFile("Jump_wg.wav");
	level[2].Jump[2].setBuffer(level[2].soundJumpWater);
	level[2].soundDeath.loadFromFile("Death.wav");
	level[2].death[2].setBuffer(level[2].soundDeath);

	level[2].soundMainDeath.loadFromFile("death_sound.wav");
	level[2].mainDeath.setBuffer(level[2].soundMainDeath);
	level[2].soundCoin.loadFromFile("Diamond.wav");
	level[2].Coin.setBuffer(level[2].soundCoin);

	level[2].soundDoor.loadFromFile("Door.wav");
	level[2].door[1].setBuffer(level[2].soundDoor);
	level[2].door[2].setBuffer(level[2].soundDoor);

	//Pause
	level[2].pause.loadFromFile("Pause.png");
	level[2].Pause.setTexture(level[2].pause);
	level[2].Pause.setPosition(1230, 8);
	level[2].Pause.setScale(0.85, 0.85);

	// coin fireboy
	//level[2].coinFireImage.loadFromFile("fireGem.png");
	//level[2].coinFireBoy[1].setTexture(level[2].coinFireImage);
	//level[2].coinFireBoy[1].setPosition(657.5f, 647.5f);
	//level[2].coinFireBoy[1].setScale(0.5f, 0.5f);
	//level[2].coinFireBoy[1].setOrigin(level[2].coinFireBoy[1].getGlobalBounds().width / 2, level[2].coinFireBoy[1].getGlobalBounds().height / 2);

	// coin watergirl
	//level[2].coinWaterImage.loadFromFile("waterGem.png");
	//level[2].coinWaterGirl[1].setTexture(level[2].coinWaterImage);
	//level[2].coinWaterGirl[1].setPosition(920.3f, 647.5f);
	//level[2].coinWaterGirl[1].setScale(0.5f, 0.5f);
	//level[2].coinWaterGirl[1].setOrigin(level[2].coinWaterGirl[1].getGlobalBounds().width / 2, level[2].coinWaterGirl[1].getGlobalBounds().height / 2);

	//set fireboy
	f_w.fireboy_st.fireBoyImage.loadFromFile("Fireboy.png");
	f_w.fireboy_st.FireBoy.setTexture(f_w.fireboy_st.fireBoyImage);
	f_w.fireboy_st.FireBoy.setPosition(80, 600);
	f_w.fireboy_st.FireBoy.setOrigin(f_w.fireboy_st.FireBoy.getLocalBounds().width / 38, f_w.fireboy_st.FireBoy.getLocalBounds().height / 2);
	f_w.fireboy_st.FireBoy.setScale(0.7f, 0.7f);
	//set watergirl
	f_w.watergirl_st.waterGirlImage.loadFromFile("Watergirl.png");
	f_w.watergirl_st.WaterGirl.setTexture(f_w.watergirl_st.waterGirlImage);
	f_w.watergirl_st.WaterGirl.setPosition(80, 450);
	f_w.watergirl_st.WaterGirl.setOrigin(f_w.watergirl_st.WaterGirl.getLocalBounds().width / 60, f_w.watergirl_st.WaterGirl.getLocalBounds().height / 2);
	f_w.watergirl_st.WaterGirl.setScale(0.7f, 0.7f);



	////set fireboy's door
	//level[2].fireboyDoorStand.loadFromFile("fbDoor.png");
	//level[2].FireBoy_DoorStand.setTexture(level[2].fireboyDoorStand);
	//level[2].FireBoy_DoorStand.setPosition(1050, 61);
	//level[2].FireBoy_DoorStand.setScale(0.7f, 0.7f);
	// 
	////set watergirl's door
	//level[2].watergirlDoorStand.loadFromFile("wgDoor.png");
	//level[2].WaterGirl_DoorStand.setTexture(level[2].watergirlDoorStand);
	//level[2].WaterGirl_DoorStand.setPosition(1150, 61);
	//level[2].WaterGirl_DoorStand.setScale(0.7f, 0.7f);
	// 
	////set Fireboy door opening
	//level[2].fireboydooropening.loadFromFile("fb_door.png");
	//level[2].FireBoy_DoorOpening.setTexture(level[2].fireboydooropening);
	//level[2].FireBoy_DoorOpening.setPosition(1060, 78);
	//level[2].FireBoy_DoorOpening.setScale(0.71f, 0.72f);
	// 
	////set Watergirl door opening
	//level[2].watergirldooropening.loadFromFile("wg_door.png");
	//level[2].WaterGirl_DoorOpening.setTexture(level[2].watergirldooropening);
	//level[2].WaterGirl_DoorOpening.setPosition(1160, 78);
	//level[2].WaterGirl_DoorOpening.setScale(0.71f, 0.71f);
	// 
	////set Fireboy moving door
	//level[2].fireboydoormoving.loadFromFile("fbWin.png");
	//level[2].FireBoy_DoorMoving.setTexture(level[2].fireboydoormoving);
	//level[2].FireBoy_DoorMoving.setPosition(1050, 61);
	//level[2].FireBoy_DoorMoving.setScale(0.7f, 0.7f);
	// 
	////set Watergirl moving door
	//level[2].watergirldoormoving.loadFromFile("wgWin.png");
	//level[2].WaterGirl_DoorMoving.setTexture(level[2].watergirldoormoving);
	//level[2].WaterGirl_DoorMoving.setPosition(1150, 61);
	//level[2].WaterGirl_DoorMoving.setScale(0.7f, 0.7f);

	// set cube
	/*level[2].cubeImage.loadFromFile("moveCube.png");
	level[2].cube[1].setTexture(level[2].cubeImage);
	level[2].cube[1].setPosition(728, 215);
	level[2].cube[1].setOrigin(level[2].cube[1].getGlobalBounds().width / 2, level[2].cube[1].getGlobalBounds().height / 2);
	level[2].cube[1].setScale(0.7f, 0.7f);*/

	///set the box hit box
	/*level[2].boxes_down[1].setSize(Vector2f(50, 5));
	level[2].boxes_down[1].setOrigin(25.f, 2.5f);

	level[2].boxes_top[1].setSize(Vector2f(50.f, 5.f));
	level[2].boxes_top[1].setOrigin(25.f, 2.5f);

	level[2].boxes_left[1].setSize(Vector2f(5, 50));
	level[2].boxes_left[1].setOrigin(2.5f, 25.f);

	level[2].boxes_right[1].setSize(Vector2f(5, 50));
	level[2].boxes_right[1].setOrigin(2.5f, 25.f);*/


	//ground
	level[2].gr_levels[2].loadFromFile("Level_2_ground.png");
	level[2].ground_levels[2].setTexture(level[2].gr_levels[2]);

	//background
	level[2].bgr_background[2].loadFromFile("background.png");
	level[2].background_levels[2].setTexture(level[2].bgr_background[2]);

	//level 2 ground 
	/////////////horizontal//////////////////////
	level[2].ground[0].setSize(Vector2f(1190, 2));
	level[2].ground[0].setPosition(Vector2f(45, 683));
	level[2].ground[0].setFillColor(Color::Cyan);

	level[2].ground[1].setSize(Vector2f(1190, 2));
	level[2].ground[1].setPosition(Vector2f(45, 43));
	level[2].ground[1].setFillColor(Color::Cyan);

	level[2].ground[2].setSize(Vector2f(545, 2));
	level[2].ground[2].setPosition(Vector2f(80, 597));
	level[2].ground[2].setFillColor(Color::Cyan);

	level[2].ground[3].setSize(Vector2f(547, 2));
	level[2].ground[3].setPosition(Vector2f(75, 566));
	level[2].ground[3].setFillColor(Color::Cyan);

	level[2].ground[4].setSize(Vector2f(615, 2));
	level[2].ground[4].setPosition(Vector2f(175, 443));
	level[2].ground[4].setFillColor(Color::Cyan);

	level[2].ground[5].setSize(Vector2f(630, 2));
	level[2].ground[5].setPosition(Vector2f(168, 478));
	level[2].ground[5].setFillColor(Color::Cyan);

	level[2].ground[6].setSize(Vector2f(500, 2));
	level[2].ground[6].setPosition(Vector2f(45, 202));
	level[2].ground[6].setFillColor(Color::Cyan);

	level[2].ground[7].setSize(Vector2f(480, 2));
	level[2].ground[7].setPosition(Vector2f(45, 235));
	level[2].ground[7].setFillColor(Color::Cyan);

	level[2].ground[8].setSize(Vector2f(100, 2));
	level[2].ground[8].setPosition(Vector2f(240, 355));
	level[2].ground[8].setFillColor(Color::Cyan);

	level[2].ground[9].setSize(Vector2f(159, 2));
	level[2].ground[9].setPosition(Vector2f(208, 377));
	level[2].ground[9].setFillColor(Color::Cyan);

	level[2].ground[10].setSize(Vector2f(260, 2));
	level[2].ground[10].setPosition(Vector2f(690, 111));
	level[2].ground[10].setFillColor(Color::Cyan);

	level[2].ground[11].setSize(Vector2f(295, 2));
	level[2].ground[11].setPosition(Vector2f(652, 141));
	level[2].ground[11].setFillColor(Color::Cyan);

	level[2].ground[12].setSize(Vector2f(210, 2));
	level[2].ground[12].setPosition(Vector2f(1000, 156));
	level[2].ground[12].setFillColor(Color::Cyan);

	level[2].ground[13].setSize(Vector2f(230, 2));
	level[2].ground[13].setPosition(Vector2f(1005, 185));
	level[2].ground[13].setFillColor(Color::Cyan);

	level[2].ground[14].setSize(Vector2f(320, 2));
	level[2].ground[14].setPosition(Vector2f(918, 253));
	level[2].ground[14].setFillColor(Color::Cyan);

	level[2].ground[15].setSize(Vector2f(250, 2));
	level[2].ground[15].setPosition(Vector2f(978, 382));
	level[2].ground[15].setFillColor(Color::Cyan);

	level[2].ground[16].setSize(Vector2f(415, 2));
	level[2].ground[16].setPosition(Vector2f(815, 468));
	level[2].ground[16].setFillColor(Color::Cyan);

	level[2].ground[17].setSize(Vector2f(250, 2));
	level[2].ground[17].setPosition(Vector2f(940, 572));
	level[2].ground[17].setFillColor(Color::Cyan);

	level[2].ground[18].setSize(Vector2f(42, 2));
	level[2].ground[18].setPosition(Vector2f(265, 130));
	level[2].ground[18].setFillColor(Color::Cyan);

	level[2].ground[19].setSize(Vector2f(50, 2));
	level[2].ground[19].setPosition(Vector2f(260, 277));
	level[2].ground[19].setFillColor(Color::Cyan);

	level[2].ground[20].setSize(Vector2f(60, 2));
	level[2].ground[20].setPosition(Vector2f(665, 618));
	level[2].ground[20].setFillColor(Color::Cyan);

	level[2].ground[21].setSize(Vector2f(35, 2));
	level[2].ground[21].setPosition(Vector2f(685, 642));
	level[2].ground[21].setFillColor(Color::Cyan);

	level[2].ground[22].setSize(Vector2f(60, 2));
	level[2].ground[22].setPosition(Vector2f(813, 503));
	level[2].ground[22].setFillColor(Color::Cyan);

	level[2].ground[23].setSize(Vector2f(66, 2));
	level[2].ground[23].setPosition(Vector2f(50, 394));
	level[2].ground[23].setFillColor(Color::Cyan);

	level[2].ground[24].setSize(Vector2f(30, 2));
	level[2].ground[24].setPosition(Vector2f(75, 430));
	level[2].ground[24].setFillColor(Color::Cyan);

	level[2].ground[25].setSize(Vector2f(65, 2));
	level[2].ground[25].setPosition(Vector2f(849, 280));
	level[2].ground[25].setFillColor(Color::Cyan);

	level[2].ground[26].setSize(Vector2f(40, 2));
	level[2].ground[26].setPosition(Vector2f(717, 377));
	level[2].ground[26].setFillColor(Color::Cyan);

	level[2].ground[27].setSize(Vector2f(45, 2));
	level[2].ground[27].setPosition(Vector2f(905, 406));
	level[2].ground[27].setFillColor(Color::Cyan);

	level[2].ground[28].setSize(Vector2f(70, 2));
	level[2].ground[28].setPosition(Vector2f(755, 328));
	level[2].ground[28].setFillColor(Color::Cyan);

	level[2].ground[29].setSize(Vector2f(66, 2));
	level[2].ground[29].setPosition(Vector2f(785, 354));
	level[2].ground[29].setFillColor(Color::Cyan);

	level[2].ground[30].setSize(Vector2f(35, 2));
	level[2].ground[30].setPosition(Vector2f(625, 204));
	level[2].ground[30].setFillColor(Color::Cyan);

	level[2].ground[31].setSize(Vector2f(35, 2));
	level[2].ground[31].setPosition(Vector2f(620, 236));
	level[2].ground[31].setFillColor(Color::Cyan);
	/////////////////vertical//////////////////////////
	level[2].ground[32].setSize(Vector2f(2, 45));
	level[2].ground[32].setPosition(Vector2f(263, 85));
	level[2].ground[32].setFillColor(Color::Yellow);

	level[2].ground[33].setSize(Vector2f(2, 45));
	level[2].ground[33].setPosition(Vector2f(307, 85));
	level[2].ground[33].setFillColor(Color::Yellow);

	level[2].ground[34].setSize(Vector2f(2, 170));
	level[2].ground[34].setPosition(Vector2f(520, 40));
	level[2].ground[34].setFillColor(Color::Yellow);

	level[2].ground[35].setSize(Vector2f(2, 170));
	level[2].ground[35].setPosition(Vector2f(560, 40));
	level[2].ground[35].setFillColor(Color::Yellow);

	level[2].ground[36].setSize(Vector2f(2, 75));
	level[2].ground[36].setPosition(Vector2f(682, 255));
	level[2].ground[36].setFillColor(Color::Yellow);

	level[2].ground[37].setSize(Vector2f(2, 75));
	level[2].ground[37].setPosition(Vector2f(725, 255));
	level[2].ground[37].setFillColor(Color::Yellow);

	level[2].ground[38].setSize(Vector2f(2, 27));
	level[2].ground[38].setPosition(Vector2f(715, 350));
	level[2].ground[38].setFillColor(Color::Yellow);

	level[2].ground[39].setSize(Vector2f(2, 30));
	level[2].ground[39].setPosition(Vector2f(973, 325));
	level[2].ground[39].setFillColor(Color::Yellow);

	level[2].ground[40].setSize(Vector2f(2, 30));
	level[2].ground[40].setPosition(Vector2f(918, 230));
	level[2].ground[40].setFillColor(Color::Yellow);

	level[2].ground[41].setSize(Vector2f(2, 40));
	level[2].ground[41].setPosition(Vector2f(670, 620));
	level[2].ground[41].setFillColor(Color::Yellow);

	level[2].ground[42].setSize(Vector2f(30, 2));
	level[2].ground[42].setPosition(Vector2f(44.5f, 577.5f));
	level[2].ground[42].setFillColor(Color::Cyan);

	level[2].ground[43].setSize(Vector2f(2, 720));
	level[2].ground[43].setPosition(Vector2f(50.5f, 20.5f));
	level[2].ground[43].setFillColor(Color::Yellow);

	////////////////////convexshapes///////////////////////
	level[2].convexs[0].setPointCount(3);
	level[2].convexs[0].setFillColor(Color::Red);
	level[2].convexs[0].setPoint(0, sf::Vector2f(85.f, 569.f));
	level[2].convexs[0].setPoint(1, sf::Vector2f(70.f, 570.f));
	level[2].convexs[0].setPoint(2, sf::Vector2f(45.f, 586.f));

	level[2].convexs[1].setPointCount(3);
	level[2].convexs[1].setFillColor(Color::Black);
	level[2].convexs[1].setPoint(0, sf::Vector2f(50.f, 619.f));
	level[2].convexs[1].setPoint(1, sf::Vector2f(80.f, 596.f));
	level[2].convexs[1].setPoint(2, sf::Vector2f(60.f, 600.f));

	level[2].convexs[2].setPointCount(3);
	level[2].convexs[2].setFillColor(Color::Green);
	level[2].convexs[2].setPoint(0, sf::Vector2f(620.f, 565.f));
	level[2].convexs[2].setPoint(1, sf::Vector2f(653.f, 588.f));
	level[2].convexs[2].setPoint(2, sf::Vector2f(648.f, 588.f));

	level[2].convexs[37].setPointCount(3);
	level[2].convexs[37].setFillColor(Color::Green);
	level[2].convexs[37].setPoint(0, sf::Vector2f(648.f, 585.f));
	level[2].convexs[37].setPoint(1, sf::Vector2f(685.f, 620.f));
	level[2].convexs[37].setPoint(2, sf::Vector2f(693.f, 620.f));

	level[2].convexs[3].setPointCount(3);
	level[2].convexs[3].setFillColor(Color::Black);
	level[2].convexs[3].setPoint(0, sf::Vector2f(625.f, 600.f));
	level[2].convexs[3].setPoint(1, sf::Vector2f(653.f, 618.f));
	level[2].convexs[3].setPoint(2, sf::Vector2f(640.f, 605.f));

	level[2].convexs[38].setPointCount(3);
	level[2].convexs[38].setFillColor(Color::Black);
	level[2].convexs[38].setPoint(0, sf::Vector2f(653.f, 618.f));
	level[2].convexs[38].setPoint(1, sf::Vector2f(683.f, 640.f));
	level[2].convexs[38].setPoint(2, sf::Vector2f(675.f, 625.f));

	level[2].convexs[4].setPointCount(3);
	level[2].convexs[4].setFillColor(Color::Green);
	level[2].convexs[4].setPoint(0, sf::Vector2f(721.f, 614.f));
	level[2].convexs[4].setPoint(1, sf::Vector2f(758.f, 648.f));
	level[2].convexs[4].setPoint(2, sf::Vector2f(767.f, 648.f));

	level[2].convexs[39].setPointCount(3);
	level[2].convexs[39].setFillColor(Color::Green);
	level[2].convexs[39].setPoint(0, sf::Vector2f(760.f, 644.f));
	level[2].convexs[39].setPoint(1, sf::Vector2f(790.f, 682.f));
	level[2].convexs[39].setPoint(2, sf::Vector2f(810.f, 682.f));

	level[2].convexs[5].setPointCount(3);
	level[2].convexs[5].setFillColor(Color::Black);
	level[2].convexs[5].setPoint(0, sf::Vector2f(720.f, 642.f));
	level[2].convexs[5].setPoint(1, sf::Vector2f(753.f, 667.f));
	level[2].convexs[5].setPoint(2, sf::Vector2f(744.f, 651.f));

	level[2].convexs[40].setPointCount(3);
	level[2].convexs[40].setFillColor(Color::Black);
	level[2].convexs[40].setPoint(0, sf::Vector2f(770.f, 670.f));
	level[2].convexs[40].setPoint(1, sf::Vector2f(753.f, 667.f));
	level[2].convexs[40].setPoint(2, sf::Vector2f(780.f, 685.f));

	level[2].convexs[6].setPointCount(3);
	level[2].convexs[6].setFillColor(Color::Black);
	level[2].convexs[6].setPoint(0, sf::Vector2f(57.f, 435.f));
	level[2].convexs[6].setPoint(1, sf::Vector2f(50.f, 448.f));
	level[2].convexs[6].setPoint(2, sf::Vector2f(75.f, 430.f));

	level[2].convexs[7].setPointCount(3);
	level[2].convexs[7].setFillColor(Color::Green);
	level[2].convexs[7].setPoint(0, sf::Vector2f(123.f, 414.f));
	level[2].convexs[7].setPoint(1, sf::Vector2f(142.f, 418.f));
	level[2].convexs[7].setPoint(2, sf::Vector2f(115.f, 395.f));

	level[2].convexs[41].setPointCount(3);
	level[2].convexs[41].setFillColor(Color::Green);
	level[2].convexs[41].setPoint(0, sf::Vector2f(171.f, 441.f));
	level[2].convexs[41].setPoint(1, sf::Vector2f(142.f, 418.f));
	level[2].convexs[41].setPoint(2, sf::Vector2f(150.f, 431.f));

	level[2].convexs[8].setPointCount(3);
	level[2].convexs[8].setFillColor(Color::Black);
	level[2].convexs[8].setPoint(0, sf::Vector2f(105.f, 430.f));
	level[2].convexs[8].setPoint(1, sf::Vector2f(143.f, 457.f));
	level[2].convexs[8].setPoint(2, sf::Vector2f(125.f, 435.f));

	level[2].convexs[42].setPointCount(3);
	level[2].convexs[42].setFillColor(Color::Black);
	level[2].convexs[42].setPoint(0, sf::Vector2f(170.f, 480.f));
	level[2].convexs[42].setPoint(1, sf::Vector2f(143.f, 457.f));
	level[2].convexs[42].setPoint(2, sf::Vector2f(160.f, 457.f));

	level[2].convexs[9].setPointCount(3);
	level[2].convexs[9].setFillColor(Color::Green);
	level[2].convexs[9].setPoint(0, sf::Vector2f(795.f, 460.f));
	level[2].convexs[9].setPoint(1, sf::Vector2f(816.f, 467.f));
	level[2].convexs[9].setPoint(2, sf::Vector2f(785.f, 443.f));

	level[2].convexs[10].setPointCount(3);
	level[2].convexs[10].setFillColor(Color::Black);
	level[2].convexs[10].setPoint(0, sf::Vector2f(785.f, 480.f));
	level[2].convexs[10].setPoint(1, sf::Vector2f(805.f, 485.f));
	level[2].convexs[10].setPoint(2, sf::Vector2f(813.f, 502.f));

	level[2].convexs[11].setPointCount(3);
	level[2].convexs[11].setFillColor(Color::Black);
	level[2].convexs[11].setPoint(0, sf::Vector2f(848.f, 503.f));
	level[2].convexs[11].setPoint(1, sf::Vector2f(897.f, 539.f));
	level[2].convexs[11].setPoint(2, sf::Vector2f(880.f, 516.f));

	level[2].convexs[43].setPointCount(3);
	level[2].convexs[43].setFillColor(Color::Black);
	level[2].convexs[43].setPoint(0, sf::Vector2f(940.f, 571.f));
	level[2].convexs[43].setPoint(1, sf::Vector2f(897.f, 539.f));
	level[2].convexs[43].setPoint(2, sf::Vector2f(915.f, 540.f));

	level[2].convexs[12].setPointCount(3);
	level[2].convexs[12].setFillColor(Color::Black);
	level[2].convexs[12].setPoint(0, sf::Vector2f(1168.f, 572.f));
	level[2].convexs[12].setPoint(1, sf::Vector2f(1200.f, 587.f));
	level[2].convexs[12].setPoint(2, sf::Vector2f(1230.f, 618.f));

	level[2].convexs[13].setPointCount(3);
	level[2].convexs[13].setFillColor(Color::Red);
	level[2].convexs[13].setPoint(0, sf::Vector2f(208.f, 377.f));
	level[2].convexs[13].setPoint(1, sf::Vector2f(240.f, 365.f));
	level[2].convexs[13].setPoint(2, sf::Vector2f(240.f, 355.f));

	level[2].convexs[14].setPointCount(3);
	level[2].convexs[14].setFillColor(Color::Green);
	level[2].convexs[14].setPoint(0, sf::Vector2f(335.f, 367.f));
	level[2].convexs[14].setPoint(1, sf::Vector2f(340.f, 355.f));
	level[2].convexs[14].setPoint(2, sf::Vector2f(368.f, 377.f));

	level[2].convexs[15].setPointCount(3);
	level[2].convexs[15].setFillColor(Color::Black);
	level[2].convexs[15].setPoint(0, sf::Vector2f(340.f, 245.f));
	level[2].convexs[15].setPoint(1, sf::Vector2f(365.f, 235.f));
	level[2].convexs[15].setPoint(2, sf::Vector2f(330.f, 260.f));

	level[2].convexs[44].setPointCount(3);
	level[2].convexs[44].setFillColor(Color::Black);
	level[2].convexs[44].setPoint(0, sf::Vector2f(317.f, 262.f));
	level[2].convexs[44].setPoint(1, sf::Vector2f(310.f, 277.f));
	level[2].convexs[44].setPoint(2, sf::Vector2f(330.f, 260.f));

	level[2].convexs[16].setPointCount(3);
	level[2].convexs[16].setFillColor(Color::Black);
	level[2].convexs[16].setPoint(0, sf::Vector2f(205.f, 235.f));
	level[2].convexs[16].setPoint(1, sf::Vector2f(233.f, 255.f));
	level[2].convexs[16].setPoint(2, sf::Vector2f(233.f, 245.f));

	level[2].convexs[45].setPointCount(3);
	level[2].convexs[45].setFillColor(Color::Black);
	level[2].convexs[45].setPoint(0, sf::Vector2f(260.f, 276.f));
	level[2].convexs[45].setPoint(1, sf::Vector2f(233.f, 255.f));
	level[2].convexs[45].setPoint(2, sf::Vector2f(256.f, 258.f));

	level[2].convexs[17].setPointCount(3);
	level[2].convexs[17].setFillColor(Color::Black);
	level[2].convexs[17].setPoint(0, sf::Vector2f(534.f, 219.f));
	level[2].convexs[17].setPoint(1, sf::Vector2f(560.f, 210.f));
	level[2].convexs[17].setPoint(2, sf::Vector2f(525.f, 235.f));

	level[2].convexs[18].setPointCount(3);
	level[2].convexs[18].setFillColor(Color::Black);
	level[2].convexs[18].setPoint(0, sf::Vector2f(335.f, 67.f));
	level[2].convexs[18].setPoint(1, sf::Vector2f(368.f, 42.f));
	level[2].convexs[18].setPoint(2, sf::Vector2f(345.f, 50.f));

	level[2].convexs[46].setPointCount(3);
	level[2].convexs[46].setFillColor(Color::Black);
	level[2].convexs[46].setPoint(0, sf::Vector2f(335.f, 67.f));
	level[2].convexs[46].setPoint(1, sf::Vector2f(307.f, 87.f));
	level[2].convexs[46].setPoint(2, sf::Vector2f(315.f, 70.f));

	level[2].convexs[19].setPointCount(3);
	level[2].convexs[19].setFillColor(Color::Black);
	level[2].convexs[19].setPoint(0, sf::Vector2f(239.f, 52.f));
	level[2].convexs[19].setPoint(1, sf::Vector2f(202.f, 42.f));
	level[2].convexs[19].setPoint(2, sf::Vector2f(232.f, 62.f));

	level[2].convexs[47].setPointCount(3);
	level[2].convexs[47].setFillColor(Color::Black);
	level[2].convexs[47].setPoint(0, sf::Vector2f(264.f, 84.f));
	level[2].convexs[47].setPoint(1, sf::Vector2f(253.f, 68.f));
	level[2].convexs[47].setPoint(2, sf::Vector2f(232.f, 62.f));

	level[2].convexs[20].setPointCount(3);
	level[2].convexs[20].setFillColor(Color::Green);
	level[2].convexs[20].setPoint(0, sf::Vector2f(572.f, 171.f));
	level[2].convexs[20].setPoint(1, sf::Vector2f(560.f, 160.f));
	level[2].convexs[20].setPoint(2, sf::Vector2f(591.f, 182.f));

	level[2].convexs[48].setPointCount(3);
	level[2].convexs[48].setFillColor(Color::White);
	level[2].convexs[48].setPoint(0, sf::Vector2f(589.f, 183.f));
	level[2].convexs[48].setPoint(1, sf::Vector2f(618.f, 202.f));
	level[2].convexs[48].setPoint(2, sf::Vector2f(591.f, 182.f));

	level[2].convexs[21].setPointCount(3);
	level[2].convexs[21].setFillColor(Color::Black);
	level[2].convexs[21].setPoint(0, sf::Vector2f(560.f, 195.f));
	level[2].convexs[21].setPoint(1, sf::Vector2f(590.f, 215.f));
	level[2].convexs[21].setPoint(2, sf::Vector2f(580.f, 200.f));

	level[2].convexs[49].setPointCount(3);
	level[2].convexs[49].setFillColor(Color::Black);
	level[2].convexs[49].setPoint(0, sf::Vector2f(619.f, 235.f));
	level[2].convexs[49].setPoint(1, sf::Vector2f(590.f, 215.f));
	level[2].convexs[49].setPoint(2, sf::Vector2f(613.f, 215.f));

	level[2].convexs[22].setPointCount(3);
	level[2].convexs[22].setFillColor(Color::Green);
	level[2].convexs[22].setPoint(0, sf::Vector2f(670.f, 225.f));
	level[2].convexs[22].setPoint(1, sf::Vector2f(688.f, 229.f));
	level[2].convexs[22].setPoint(2, sf::Vector2f(660.f, 205.f));

	level[2].convexs[50].setPointCount(3);
	level[2].convexs[50].setFillColor(Color::Green);
	level[2].convexs[50].setPoint(0, sf::Vector2f(722.f, 252.f));
	level[2].convexs[50].setPoint(1, sf::Vector2f(688.f, 228.f));
	level[2].convexs[50].setPoint(2, sf::Vector2f(700.f, 240.f));

	level[2].convexs[23].setPointCount(3);
	level[2].convexs[23].setFillColor(Color::Black);
	level[2].convexs[23].setPoint(0, sf::Vector2f(655.f, 237.f));
	level[2].convexs[23].setPoint(1, sf::Vector2f(685.f, 255.f));
	level[2].convexs[23].setPoint(2, sf::Vector2f(682.f, 255.f));

	level[2].convexs[24].setPointCount(3);
	level[2].convexs[24].setFillColor(Color::Green);
	level[2].convexs[24].setPoint(0, sf::Vector2f(730.f, 320.f));
	level[2].convexs[24].setPoint(1, sf::Vector2f(755.f, 330.f));
	level[2].convexs[24].setPoint(2, sf::Vector2f(725.f, 310.f));

	level[2].convexs[25].setPointCount(3);
	level[2].convexs[25].setFillColor(Color::Black);
	level[2].convexs[25].setPoint(0, sf::Vector2f(685.f, 330.f));
	level[2].convexs[25].setPoint(1, sf::Vector2f(713.f, 339.f));
	level[2].convexs[25].setPoint(2, sf::Vector2f(715.f, 350.f));

	level[2].convexs[26].setPointCount(3);
	level[2].convexs[26].setFillColor(Color::Black);
	level[2].convexs[26].setPoint(0, sf::Vector2f(770.f, 359.f));
	level[2].convexs[26].setPoint(1, sf::Vector2f(788.f, 352.f));
	level[2].convexs[26].setPoint(2, sf::Vector2f(758.f, 377.f));

	level[2].convexs[27].setPointCount(3);
	level[2].convexs[27].setFillColor(Color::Green);
	level[2].convexs[27].setPoint(0, sf::Vector2f(825.f, 330.f));
	level[2].convexs[27].setPoint(1, sf::Vector2f(855.f, 355.f));
	level[2].convexs[27].setPoint(2, sf::Vector2f(833.f, 345.f));

	level[2].convexs[28].setPointCount(3);
	level[2].convexs[28].setFillColor(Color::Red);
	level[2].convexs[28].setPoint(0, sf::Vector2f(880.f, 256.f));
	level[2].convexs[28].setPoint(1, sf::Vector2f(847.f, 280.f));
	level[2].convexs[28].setPoint(2, sf::Vector2f(872.f, 269.f));

	level[2].convexs[51].setPointCount(3);
	level[2].convexs[51].setFillColor(Color::Red);
	level[2].convexs[51].setPoint(0, sf::Vector2f(880.f, 256.f));
	level[2].convexs[51].setPoint(1, sf::Vector2f(917.f, 227.f));
	level[2].convexs[51].setPoint(2, sf::Vector2f(908.f, 247.f));

	level[2].convexs[29].setPointCount(3);
	level[2].convexs[29].setFillColor(Color::Black);
	level[2].convexs[29].setPoint(0, sf::Vector2f(914.f, 280.f));
	level[2].convexs[29].setPoint(1, sf::Vector2f(945.f, 305.f));
	level[2].convexs[29].setPoint(2, sf::Vector2f(940.f, 290.f));

	level[2].convexs[52].setPointCount(3);
	level[2].convexs[52].setFillColor(Color::Black);
	level[2].convexs[52].setPoint(0, sf::Vector2f(973.f, 325.f));
	level[2].convexs[52].setPoint(1, sf::Vector2f(945.f, 305.f));
	level[2].convexs[52].setPoint(2, sf::Vector2f(956.f, 308.f));

	level[2].convexs[30].setPointCount(3);
	level[2].convexs[30].setFillColor(Color::Black);
	level[2].convexs[30].setPoint(0, sf::Vector2f(965.f, 380.f));
	level[2].convexs[30].setPoint(1, sf::Vector2f(945.f, 405.f));
	level[2].convexs[30].setPoint(2, sf::Vector2f(980.f, 380.f));

	level[2].convexs[31].setPointCount(3);
	level[2].convexs[31].setFillColor(Color::Red);
	level[2].convexs[31].setPoint(0, sf::Vector2f(938.f, 380.f));
	level[2].convexs[31].setPoint(1, sf::Vector2f(924.f, 398.f));
	level[2].convexs[31].setPoint(2, sf::Vector2f(905.f, 407.f));

	level[2].convexs[53].setPointCount(3);
	level[2].convexs[53].setFillColor(Color::Red);
	level[2].convexs[53].setPoint(0, sf::Vector2f(938.f, 380.f));
	level[2].convexs[53].setPoint(1, sf::Vector2f(972.f, 353.f));
	level[2].convexs[53].setPoint(2, sf::Vector2f(960.f, 370.f));

	level[2].convexs[32].setPointCount(3);
	level[2].convexs[32].setFillColor(Color::Black);
	level[2].convexs[32].setPoint(0, sf::Vector2f(1205.f, 380.f));
	level[2].convexs[32].setPoint(1, sf::Vector2f(1223.f, 386.f));
	level[2].convexs[32].setPoint(2, sf::Vector2f(1230.f, 400.f));

	level[2].convexs[33].setPointCount(3);
	level[2].convexs[33].setFillColor(Color::Red);
	level[2].convexs[33].setPoint(0, sf::Vector2f(1205.f, 155.f));
	level[2].convexs[33].setPoint(1, sf::Vector2f(1230.f, 140.f));
	level[2].convexs[33].setPoint(2, sf::Vector2f(1224.f, 156.f));

	level[2].convexs[34].setPointCount(3);
	level[2].convexs[34].setFillColor(Color::Red);
	level[2].convexs[34].setPoint(0, sf::Vector2f(690.f, 112.f));
	level[2].convexs[34].setPoint(1, sf::Vector2f(650.f, 140.f));
	level[2].convexs[34].setPoint(2, sf::Vector2f(672.f, 130.f));

	level[2].convexs[35].setPointCount(3);
	level[2].convexs[35].setFillColor(Color::Green);
	level[2].convexs[35].setPoint(0, sf::Vector2f(989.f, 154.f));
	level[2].convexs[35].setPoint(1, sf::Vector2f(978.f, 135.f));
	level[2].convexs[35].setPoint(2, sf::Vector2f(1005.f, 155.f));

	level[2].convexs[54].setPointCount(3);
	level[2].convexs[54].setFillColor(Color::Green);
	level[2].convexs[54].setPoint(0, sf::Vector2f(951.f, 115.f));
	level[2].convexs[54].setPoint(1, sf::Vector2f(978.f, 135.f));
	level[2].convexs[54].setPoint(2, sf::Vector2f(963.f, 130.f));

	level[2].convexs[36].setPointCount(3);
	level[2].convexs[36].setFillColor(Color::Black);
	level[2].convexs[36].setPoint(0, sf::Vector2f(962.f, 144.f));
	level[2].convexs[36].setPoint(1, sf::Vector2f(975.f, 163.f));
	level[2].convexs[36].setPoint(2, sf::Vector2f(945.f, 140.f));

	level[2].convexs[55].setPointCount(3);
	level[2].convexs[55].setFillColor(Color::Black);
	level[2].convexs[55].setPoint(0, sf::Vector2f(1004.f, 183.f));
	level[2].convexs[55].setPoint(1, sf::Vector2f(975.f, 163.f));
	level[2].convexs[55].setPoint(2, sf::Vector2f(993.f, 172.f));

}
void collision_fireboy(RenderWindow& window, bool& isAnimationStandingFireBoy, double& velocityFireBoy, Sprite& FireBoy)
{
	bool top = 0, down = 0, r = 0, l = 0;
	//collision fireboy_down
	for (int i = 0; i < 60; i++) {
		if (level[in_game.number_Level].ground[i].getGlobalBounds().intersects(f_w.fireboy_st.firboy_down.getGlobalBounds()) && (level[in_game.number_Level].ground[i].getFillColor() == Color::Cyan)) {
			down = 1;
			f_w.fireboy_st.grounded = 1;
		}
	}

	if (down)
	{
		isAnimationStandingFireBoy = 1;
		velocityFireBoy = 0;
		if (Keyboard::isKeyPressed(Keyboard::Key::W)) {
			level[in_game.number_Level].Jump[1].play();
			velocityFireBoy = 5.5;
			isAnimationStandingFireBoy = 0;

		}

	}
	else if (!down)
	{
		isAnimationStandingFireBoy = 0;
		velocityFireBoy -= 0.2;
		f_w.fireboy_st.grounded = 0;
	}
	//collision fireboy_top
	for (int i = 0; i < 60; i++) {
		if (level[in_game.number_Level].ground[i].getGlobalBounds().intersects(f_w.fireboy_st.firboy_top.getGlobalBounds()) && (level[in_game.number_Level].ground[i].getFillColor() == Color::Cyan)) {
			top = 1;
		}

	}
	if (top && !isAnimationStandingFireBoy) {
		velocityFireBoy = -1.7;

	}
	//collision fireboy_right
	for (int i = 0; i < 60; i++) {
		if (level[in_game.number_Level].ground[i].getGlobalBounds().intersects(f_w.fireboy_st.firboy_right.getGlobalBounds()) && Keyboard::isKeyPressed(Keyboard::Key::D) && level[in_game.number_Level].ground[i].getFillColor() == Color::Yellow) {
			FireBoy.move(-5, 0);

		}
	}

	/////collision fireboy_left

	for (int i = 0; i < 60; i++) {
		if (level[in_game.number_Level].ground[i].getGlobalBounds().intersects(f_w.fireboy_st.firboy_left.getGlobalBounds()) && Keyboard::isKeyPressed(Keyboard::Key::A) && level[in_game.number_Level].ground[i].getFillColor() == Color::Yellow) {
			FireBoy.move(5, 0);
		}
	}


	///////////////////////////---------------collision convexs---------------------///////////////////////////

	for (int i = 0; i < 60; i++)
	{


		if (f_w.fireboy_st.firboy_down.getGlobalBounds().intersects(level[in_game.number_Level].convexs[i].getGlobalBounds()) && level[in_game.number_Level].convexs[i].getFillColor() == Color::Green) {
			isAnimationStandingFireBoy = 1;
			velocityFireBoy = 0;
			if (Keyboard::isKeyPressed(Keyboard::Key::A))
			{
				FireBoy.move(5, 0);
				FireBoy.move(-4, -4);
			}
			if (!f_w.fireboy_st.grounded || i == 9) {
				if (Keyboard::isKeyPressed(Keyboard::Key::D))
				{
					FireBoy.move(3, 3);
					FireBoy.move(-5, 0);
					//cout << "no\n";
				}

				FireBoy.move(2.5, 2);
				//cout << "YES\n";
			}
			if (Keyboard::isKeyPressed(Keyboard::Key::W))
			{
				level[in_game.number_Level].Jump[1].play();
				velocityFireBoy = 5.5;
			}

		}
		else if (f_w.fireboy_st.firboy_down.getGlobalBounds().intersects(level[in_game.number_Level].convexs[i].getGlobalBounds()) && level[in_game.number_Level].convexs[i].getFillColor() == Color::Red) {
			isAnimationStandingFireBoy = 1;
			velocityFireBoy = 0;
			if (Keyboard::isKeyPressed(Keyboard::Key::A) && (!f_w.fireboy_st.grounded))
			{
				FireBoy.move(5, 0);
				FireBoy.move(-2, 2);
			}

			if (Keyboard::isKeyPressed(Keyboard::Key::D))
			{
				FireBoy.move(4, -4);
				FireBoy.move(-5, 0);
				if (f_w.fireboy_st.grounded)
					FireBoy.move(-5, 0);
				//cout << "no\n";
			}

			if (!f_w.fireboy_st.grounded)
			{
				FireBoy.move(-2.0, 2.0);
				//cout << "YES\n";
			}

			if (Keyboard::isKeyPressed(Keyboard::Key::W))
			{
				level[in_game.number_Level].Jump[1].play();
				velocityFireBoy = 5.5;
			}

		}
		if (f_w.fireboy_st.firboy_top.getGlobalBounds().intersects(level[in_game.number_Level].convexs[i].getGlobalBounds()) && level[in_game.number_Level].convexs[i].getFillColor() == Color::Black) {

			if (!f_w.fireboy_st.grounded)
				f_w.fireboy_st.velocityFireBoy = -3.7;
		}
	}
	if (f_w.fireboy_st.firboy_left.getGlobalBounds().intersects(level[in_game.number_Level].convexs[9].getGlobalBounds()) && !(f_w.fireboy_st.firboy_down.getGlobalBounds().intersects(level[in_game.number_Level].convexs[9].getGlobalBounds()))) {
		if (in_game.number_Level == 1)
			FireBoy.move(5.2f, 0);
	}

	if (f_w.fireboy_st.firboy_right.getGlobalBounds().intersects(level[in_game.number_Level].convexs[2].getGlobalBounds()) && !(f_w.fireboy_st.firboy_down.getGlobalBounds().intersects(level[in_game.number_Level].convexs[2].getGlobalBounds()))) {
		if (in_game.number_Level == 1)
			FireBoy.move(-5.2f, 0);
	}

	/////////// collision fireboy with water and black pond //////////////////
	if (f_w.fireboy_st.firboy_down.getGlobalBounds().intersects(level[in_game.number_Level].pondWaterGirl[1].getGlobalBounds()) || f_w.fireboy_st.firboy_down.getGlobalBounds().intersects(level[in_game.number_Level].pondBlack[1].getGlobalBounds()))
	{
		if (!level[in_game.number_Level].isSmoke[1])
			level[in_game.number_Level].death[1].play();
		level[in_game.number_Level].isSmoke[1] = 1;
		level[in_game.number_Level].smoke[1].setPosition(f_w.fireboy_st.firboy_top.getPosition().x - 30, f_w.fireboy_st.firboy_top.getPosition().y - 40);


		f_w.fireboy_st.FireBoy.setScale(0, 0);
	}
	else level[in_game.number_Level].isSmoke[1] = 0;

	/////////// collision fireboy with coin //////////////////
	for (int i = 0; i < 5; i++)
	{
		if (f_w.fireboy_st.firboy_left.getGlobalBounds().intersects(level[in_game.number_Level].coinFireBoy[i].getGlobalBounds()) || f_w.fireboy_st.firboy_right.getGlobalBounds().intersects(level[in_game.number_Level].coinFireBoy[i].getGlobalBounds()))
		{
			level[in_game.number_Level].fb_sc[1]++;
			level[in_game.number_Level].fb_count.setString(to_string(level[in_game.number_Level].fb_sc[1]));
			level[in_game.number_Level].Coin.play();
			level[in_game.number_Level].coinFireBoy[i].setScale(0, 0);
		}
	}
	///////////////////// collision with boxes /////////////////////////
	if (f_w.fireboy_st.firboy_left.getGlobalBounds().intersects(level[in_game.number_Level].boxes_right[1].getGlobalBounds()) && !(level[in_game.number_Level].g_w_b_f[1])) {
		level[in_game.number_Level].cube[1].move(-2.5f, 0.0f);
		f_w.fireboy_st.FireBoy.move(3.0f, 0.0f);
		if (f_w.watergirl_st.watergirl_left.getGlobalBounds().intersects(level[in_game.number_Level].ground[44].getGlobalBounds())) {
			//level[in_game.number_Level].cube[1].move(-2.5f, 0.0f);
			f_w.fireboy_st.FireBoy.move(2.5f, 0.0f);
			f_w.watergirl_st.WaterGirl.move(2.0f, 0.0f);
		}
	}
	if (f_w.fireboy_st.firboy_left.getGlobalBounds().intersects(level[in_game.number_Level].boxes_right[1].getGlobalBounds()) && (level[in_game.number_Level].g_w_b_f[1])) {
		// level[in_game.number_Level].cube[1].move(-2.5f, 0.0f);
		//f_w.watergirl_st.WaterGirl.move(5.0f, 0.0f);
		f_w.fireboy_st.FireBoy.move(3.0f, 0.0f);
	}
	if (f_w.fireboy_st.firboy_right.getGlobalBounds().intersects(level[in_game.number_Level].boxes_left[1].getGlobalBounds()) && !(level[in_game.number_Level].f_b_w_g[1])) {
		level[in_game.number_Level].cube[1].move(2.5f, 0.0f);
		f_w.fireboy_st.FireBoy.move(-3.0f, 0.0f);
		if (f_w.watergirl_st.watergirl_right.getGlobalBounds().intersects(level[in_game.number_Level].ground[41].getGlobalBounds())) {
			//level[in_game.number_Level].cube[1].move(-2.5f, 0.0f);
			f_w.fireboy_st.FireBoy.move(-2.5f, 0.0f);
			f_w.watergirl_st.WaterGirl.move(-2.0f, 0.0f);
		}
	}
	if (f_w.fireboy_st.firboy_right.getGlobalBounds().intersects(level[in_game.number_Level].boxes_left[1].getGlobalBounds()) && (level[in_game.number_Level].f_b_w_g[1])) {
		level[in_game.number_Level].cube[1].move(-2.5f, 0.0f);
		f_w.fireboy_st.FireBoy.move(-6.0f, 0.0f);
		f_w.watergirl_st.WaterGirl.move(-4.0f, 0.0f);

		cout << "yes" << "\n";
	}
	if (f_w.fireboy_st.firboy_down.getGlobalBounds().intersects(level[in_game.number_Level].boxes_top[1].getGlobalBounds())) {
		f_w.fireboy_st.grounded = 1;
		f_w.fireboy_st.velocityFireBoy = 0;
		f_w.fireboy_st.isAnimationStandingFireBoy = 1;

		if (Keyboard::isKeyPressed(Keyboard::Key::W)) {
			level[in_game.number_Level].Jump[1].play();
			velocityFireBoy = 5.5;
			isAnimationStandingFireBoy = 0;

		}
	}

}
void collision_watergirl(RenderWindow& window, bool& isAnimationStandingWaterGirl, double& velocityWaterGirl, Sprite& WaterGirl)
{
	bool top = 0, down = 0, r = 0, l = 0;
	//collision watergirl_down
	for (int i = 0; i < 60; i++) {
		if (level[in_game.number_Level].ground[i].getGlobalBounds().intersects(f_w.watergirl_st.watergirl_down.getGlobalBounds()) && (level[in_game.number_Level].ground[i].getFillColor() == Color::Cyan)) {
			down = 1;
			f_w.watergirl_st.grounded = 1;
		}
	}
	if (down)
	{
		isAnimationStandingWaterGirl = 1;
		velocityWaterGirl = 0;
		if (Keyboard::isKeyPressed(Keyboard::Key::Up)) {
			level[in_game.number_Level].Jump[2].play();
			velocityWaterGirl = 5.5;
			isAnimationStandingWaterGirl = 0;

		}

	}
	else if (!down)
	{
		isAnimationStandingWaterGirl = 0;
		velocityWaterGirl -= 0.2;
		f_w.watergirl_st.grounded = 0;
	}
	//collision watergirl_top
	for (int i = 0; i < 60; i++) {
		if (level[in_game.number_Level].ground[i].getGlobalBounds().intersects(f_w.watergirl_st.watergirl_top.getGlobalBounds()) && (level[in_game.number_Level].ground[i].getFillColor() == Color::Cyan)) {
			top = 1;
		}

	}
	if (top && !isAnimationStandingWaterGirl) {
		velocityWaterGirl = -1;

	}
	//collision watergirl_right
	for (int i = 0; i < 60; i++) {
		if (level[in_game.number_Level].ground[i].getGlobalBounds().intersects(f_w.watergirl_st.watergirl_right.getGlobalBounds()) && Keyboard::isKeyPressed(Keyboard::Key::Right) && level[in_game.number_Level].ground[i].getFillColor() == Color::Yellow) {
			WaterGirl.move(-5, 0);
		}
	}

	/////collision watergirl_left

	for (int i = 0; i < 60; i++) {
		if (level[in_game.number_Level].ground[i].getGlobalBounds().intersects(f_w.watergirl_st.watergirl_left.getGlobalBounds()) && Keyboard::isKeyPressed(Keyboard::Key::Left) && level[in_game.number_Level].ground[i].getFillColor() == Color::Yellow) {
			WaterGirl.move(5, 0);
		}
	}

	//collision convexes
	for (int i = 0; i < 60; i++)
	{


		if (f_w.watergirl_st.watergirl_down.getGlobalBounds().intersects(level[in_game.number_Level].convexs[i].getGlobalBounds()) && level[in_game.number_Level].convexs[i].getFillColor() == Color::Green) {
			isAnimationStandingWaterGirl = 1;
			velocityWaterGirl = 0;
			if (Keyboard::isKeyPressed(Keyboard::Key::Left))
			{
				WaterGirl.move(5, 0);
				WaterGirl.move(-4, -4);
			}
			if (!f_w.watergirl_st.grounded || i == 9) {
				if (Keyboard::isKeyPressed(Keyboard::Key::Right))
				{
					WaterGirl.move(3, 3);
					WaterGirl.move(-5, 0);
					//cout << "no\n";
				}

				WaterGirl.move(2.0, 2.0);
				//cout << "YES\n";
			}
			if (Keyboard::isKeyPressed(Keyboard::Key::Up))
			{
				level[in_game.number_Level].Jump[2].play();
				velocityWaterGirl = 5.5;
			}

		}
		else if (f_w.watergirl_st.watergirl_down.getGlobalBounds().intersects(level[in_game.number_Level].convexs[i].getGlobalBounds()) && level[in_game.number_Level].convexs[i].getFillColor() == Color::Red)
		{
			isAnimationStandingWaterGirl = 1;
			velocityWaterGirl = 0;
			if (Keyboard::isKeyPressed(Keyboard::Key::Left) && !f_w.watergirl_st.grounded)
			{
				WaterGirl.move(5, 0);
				WaterGirl.move(-2, 2);
			}


			if (Keyboard::isKeyPressed(Keyboard::Key::Right))
			{
				WaterGirl.move(4, -4);
				WaterGirl.move(-5, 0);
				if (f_w.watergirl_st.grounded)
					WaterGirl.move(-5, 0);
				//cout << "no\n";
			}
			if (!f_w.watergirl_st.grounded)
			{
				WaterGirl.move(-2.0, 2.0);
				//cout << "YES\n";
			}

			if (Keyboard::isKeyPressed(Keyboard::Key::Up))
			{
				level[in_game.number_Level].Jump[2].play();
				velocityWaterGirl = 5.5;
			}


		}
		if (f_w.watergirl_st.watergirl_top.getGlobalBounds().intersects(level[in_game.number_Level].convexs[i].getGlobalBounds()) && level[in_game.number_Level].convexs[i].getFillColor() == Color::Black) {

			if (!f_w.watergirl_st.grounded)
				velocityWaterGirl = -3.5;

		}
	}
	//// ////////////////////////////////////////////////////
	if (f_w.watergirl_st.watergirl_left.getGlobalBounds().intersects(level[in_game.number_Level].convexs[9].getGlobalBounds()) && !(f_w.watergirl_st.watergirl_down.getGlobalBounds().intersects(level[in_game.number_Level].convexs[9].getGlobalBounds()))) {
		WaterGirl.move(5.2f, 0);
	}
	if (f_w.watergirl_st.watergirl_right.getGlobalBounds().intersects(level[in_game.number_Level].convexs[2].getGlobalBounds()) && !(f_w.watergirl_st.watergirl_down.getGlobalBounds().intersects(level[in_game.number_Level].convexs[2].getGlobalBounds()))) {
		WaterGirl.move(-5.2f, 0);
	}

	/////////// collision watergirl with fire and black pond //////////////////
	if (f_w.watergirl_st.watergirl_down.getGlobalBounds().intersects(level[in_game.number_Level].pondFireBoy[1].getGlobalBounds()) || f_w.watergirl_st.watergirl_down.getGlobalBounds().intersects(level[in_game.number_Level].pondBlack[1].getGlobalBounds()))
	{
		if (!level[in_game.number_Level].isSmoke[2])
			level[in_game.number_Level].death[2].play();
		level[in_game.number_Level].isSmoke[2] = 1;
		level[in_game.number_Level].smoke[2].setPosition(f_w.watergirl_st.watergirl_top.getPosition().x - 30, f_w.watergirl_st.watergirl_top.getPosition().y - 40);

		f_w.watergirl_st.WaterGirl.setScale(0, 0);
	}
	else level[in_game.number_Level].isSmoke[2] = 0;
	/////////// collision watergirl with coin //////////////////
	for (int i = 0; i < 5; i++)
	{
		if (f_w.watergirl_st.watergirl_left.getGlobalBounds().intersects(level[in_game.number_Level].coinWaterGirl[i].getGlobalBounds()) || f_w.watergirl_st.watergirl_right.getGlobalBounds().intersects(level[1].coinWaterGirl[i].getGlobalBounds()))
		{
			level[in_game.number_Level].wg_sc[1]++;
			level[in_game.number_Level].wg_count.setString(to_string(level[in_game.number_Level].wg_sc[1]));
			level[in_game.number_Level].Coin.play();
			level[in_game.number_Level].coinWaterGirl[i].setScale(0, 0);
		}
	}
	///////////////////// collision with boxes /////////////////////////
	if (f_w.watergirl_st.watergirl_left.getGlobalBounds().intersects(level[in_game.number_Level].boxes_right[1].getGlobalBounds()) && !(level[in_game.number_Level].g_f_b_w[1])) {
		level[in_game.number_Level].cube[1].move(-2.5f, 0.0f);
		f_w.watergirl_st.WaterGirl.move(3.0f, 0.0f);
	}
	if (f_w.watergirl_st.watergirl_left.getGlobalBounds().intersects(level[in_game.number_Level].boxes_right[1].getGlobalBounds()) && (level[in_game.number_Level].g_f_b_w[1])) {
		//	level[in_game.number_Level].cube[1].move(-2.5f, 0.0f);
		f_w.watergirl_st.WaterGirl.move(5.0f, 0.0f);
	}
	if (f_w.watergirl_st.watergirl_right.getGlobalBounds().intersects(level[in_game.number_Level].boxes_left[1].getGlobalBounds()) && !(level[in_game.number_Level].w_b_f_g[1])) {
		level[in_game.number_Level].cube[1].move(2.5f, 0.0f);
		f_w.watergirl_st.WaterGirl.move(-3.0f, 0.0f);
	}
	if (f_w.watergirl_st.watergirl_right.getGlobalBounds().intersects(level[in_game.number_Level].boxes_left[1].getGlobalBounds()) && (level[in_game.number_Level].w_b_f_g[1])) {
		// level[in_game.number_Level].cube[1].move(2.5f, 0.0f);
		f_w.watergirl_st.WaterGirl.move(-5.0f, 0.0f);
	}
	if (f_w.watergirl_st.watergirl_down.getGlobalBounds().intersects(level[in_game.number_Level].boxes_top[1].getGlobalBounds())) {
		f_w.watergirl_st.grounded = 1;
		isAnimationStandingWaterGirl = 1;
		velocityWaterGirl = 0;
		if (Keyboard::isKeyPressed(Keyboard::Key::Up)) {
			level[in_game.number_Level].Jump[2].play();
			velocityWaterGirl = 5.5;
			isAnimationStandingWaterGirl = 0;

		}
	}
}
void collision_boxes(RenderWindow& window)
{

	bool top = 0, down = 0;
	//collision fireboy_down
	for (int i = 0; i < 60; i++) {
		if (level[in_game.number_Level].ground[i].getGlobalBounds().intersects(level[in_game.number_Level].boxes_down[1].getGlobalBounds()) && (level[in_game.number_Level].ground[i].getFillColor() == Color::Cyan)) {
			down = 1;
			level[in_game.number_Level].isStandingboxes[1] = 1;
		}
	}
	if (down)
	{
		level[in_game.number_Level].velocityboxes[1] = 0;
	}
	else if (!down)
	{
		level[in_game.number_Level].velocityboxes[1] -= 0.2;
	}
	////////////////collision box_right with ground ///////////////
	for (int i = 0; i < 60; i++) {
		if (level[in_game.number_Level].ground[i].getGlobalBounds().intersects(level[in_game.number_Level].boxes_right[1].getGlobalBounds()) && level[in_game.number_Level].ground[i].getFillColor() == Color::Yellow) {
			if (f_w.fireboy_st.firboy_right.getGlobalBounds().intersects(level[in_game.number_Level].boxes_left[1].getGlobalBounds())) {
				level[in_game.number_Level].cube[1].move(-2.5f, 0.0f);
				f_w.fireboy_st.FireBoy.move(-3.0f, 0.0f);
			}
			if (f_w.watergirl_st.watergirl_right.getGlobalBounds().intersects(level[in_game.number_Level].boxes_left[1].getGlobalBounds())) {
				level[in_game.number_Level].cube[1].move(-2.5f, 0.0f);
				f_w.watergirl_st.WaterGirl.move(-3.0f, 0.0f);
			}
		}
	}

	//////////////collision box_left with ground /////////////


	for (int i = 0; i < 60; i++) {
		if (level[in_game.number_Level].ground[i].getGlobalBounds().intersects(level[in_game.number_Level].boxes_left[1].getGlobalBounds()) && level[in_game.number_Level].ground[i].getFillColor() == Color::Yellow) {
			if (f_w.fireboy_st.firboy_left.getGlobalBounds().intersects(level[in_game.number_Level].boxes_right[1].getGlobalBounds())) {
				level[in_game.number_Level].cube[1].move(2.5f, 0.0f);
				f_w.fireboy_st.FireBoy.move(3.0f, 0.0f);

			}
			if (f_w.watergirl_st.watergirl_left.getGlobalBounds().intersects(level[in_game.number_Level].boxes_right[1].getGlobalBounds())) {
				level[in_game.number_Level].cube[1].move(2.5f, 0.0f);
				f_w.watergirl_st.WaterGirl.move(3.0f, 0.0f);
			}
		}
	}
	///////////////////////////---------------collision convexs---------------------///////////////////////////

	for (int i = 0; i < 60; i++)
	{
		if (level[in_game.number_Level].boxes_down[1].getGlobalBounds().intersects(level[in_game.number_Level].convexs[i].getGlobalBounds()) && level[in_game.number_Level].convexs[i].getFillColor() == Color::Green) {
			level[in_game.number_Level].isStandingboxes[1] = 1;
			level[in_game.number_Level].cube[1].move(4.0, 4.0);
			//cout << "YES\n";
		}
		if (level[in_game.number_Level].boxes_down[1].getGlobalBounds().intersects(level[in_game.number_Level].convexs[i].getGlobalBounds()) && level[in_game.number_Level].convexs[i].getFillColor() == Color::Red) {
			level[in_game.number_Level].isStandingboxes[1] = 1;
			level[in_game.number_Level].cube[1].move(-4.0, 4.0);
		}
	}


	///////////////////collision the box between fireboy and watergirl and ground ////////////////
	bool state_1 = 0, state_2 = 0, state_3 = 0, state_4 = 0;
	for (int i = 0; i < 60; i++) {
		if (f_w.fireboy_st.firboy_right.getGlobalBounds().intersects(level[in_game.number_Level].boxes_left[1].getGlobalBounds())) {
			////case 1:  //  g f  b w
			////case 1:  //    b w
			if (f_w.fireboy_st.firboy_left.getGlobalBounds().intersects(level[in_game.number_Level].ground[i].getGlobalBounds()) && level[in_game.number_Level].ground[i].getFillColor() == Color::Yellow)
			{
				if (f_w.watergirl_st.watergirl_left.getGlobalBounds().intersects(level[in_game.number_Level].boxes_right[1].getGlobalBounds())) {
					//	f_w.fireboy_st.FireBoy.move(5.0f, 0.0f);
					if (Keyboard::isKeyPressed(Keyboard::Left))
						state_1 = 1;
				}
			}
			if (state_1)level[in_game.number_Level].g_f_b_w[1] = 1;
			else level[in_game.number_Level].g_f_b_w[1] = 0;


			////case 2:   //f b w g 
			if (level[in_game.number_Level].ground[i].getFillColor() == Color::Yellow && f_w.watergirl_st.watergirl_right.getGlobalBounds().intersects(level[in_game.number_Level].ground[i].getGlobalBounds()))
			{
				if (level[in_game.number_Level].boxes_right[1].getGlobalBounds().intersects(f_w.watergirl_st.watergirl_left.getGlobalBounds())) {
					// f_w.watergirl_st.WaterGirl.move(5.0f, 0.0f);
					if (Keyboard::isKeyPressed(Keyboard::D)) {
						state_2 = 1;
					}
				}
			}
			if (state_2)level[in_game.number_Level].f_b_w_g[1] = 1;
			else level[in_game.number_Level].f_b_w_g[1] = 0;

		}


		if (level[in_game.number_Level].boxes_right[1].getGlobalBounds().intersects(f_w.fireboy_st.firboy_left.getGlobalBounds())) {
			////case 3:   //g w b f
			if (f_w.watergirl_st.watergirl_left.getGlobalBounds().intersects(level[in_game.number_Level].ground[i].getGlobalBounds()) && level[in_game.number_Level].ground[i].getFillColor() == Color::Yellow) {
				if (level[in_game.number_Level].boxes_left[1].getGlobalBounds().intersects(f_w.watergirl_st.watergirl_right.getGlobalBounds())) {
					//	f_w.watergirl_st.WaterGirl.move(7.25f, 0.0f);
					if (Keyboard::isKeyPressed(Keyboard::A)) {
						state_3 = 1;
					}
				}

			}
			if (state_3)level[in_game.number_Level].g_w_b_f[1] = 1;
			else level[in_game.number_Level].g_w_b_f[1] = 0;
			////case 4:  //w b f g
			if (f_w.fireboy_st.firboy_right.getGlobalBounds().intersects(level[in_game.number_Level].ground[i].getGlobalBounds()) && level[in_game.number_Level].ground[i].getFillColor() == Color::Yellow) {
				if (f_w.watergirl_st.watergirl_right.getGlobalBounds().intersects(level[in_game.number_Level].boxes_left[1].getGlobalBounds())) {
					//	f_w.fireboy_st.FireBoy.move(-5.0f, 0.0f);
					if (Keyboard::isKeyPressed(Keyboard::Right)) {
						state_4 = 1;
					}
				}

			}
			if (state_4)level[in_game.number_Level].w_b_f_g[1] = 1;
			else level[in_game.number_Level].w_b_f_g[1] = 0;

		}
	}
	///////////////////collision the box between fireboy and watergirl ////////////////
	if (f_w.fireboy_st.firboy_left.getGlobalBounds().intersects(level[in_game.number_Level].boxes_right[1].getGlobalBounds()) && f_w.watergirl_st.watergirl_right.getGlobalBounds().intersects(level[in_game.number_Level].boxes_left[1].getGlobalBounds())) {
		f_w.fireboy_st.FireBoy.move(3.0f, 0.0f);
		f_w.watergirl_st.WaterGirl.move(-3.0f, 0.0f);
		bool wg_touch = 0, fb_touch = 0;
		for (int i = 0; i < 60; i++) {
			if (!wg_touch && f_w.watergirl_st.watergirl_left.getGlobalBounds().intersects(level[in_game.number_Level].ground[i].getGlobalBounds()) && level[in_game.number_Level].ground[i].getFillColor() == Color::Yellow) {
				wg_touch = 1;
				f_w.watergirl_st.WaterGirl.move(6.2f, 0.0f);
				f_w.fireboy_st.FireBoy.move(1.f, 0.0f);
			}
			if (!fb_touch && f_w.fireboy_st.firboy_right.getGlobalBounds().intersects(level[in_game.number_Level].ground[i].getGlobalBounds()) && level[in_game.number_Level].ground[i].getFillColor() == Color::Yellow) {
				fb_touch = 1;
				f_w.fireboy_st.FireBoy.move(-3.0f, 0.0f);
			}
		}

	}
	if (f_w.watergirl_st.watergirl_left.getGlobalBounds().intersects(level[in_game.number_Level].boxes_right[1].getGlobalBounds()) && f_w.fireboy_st.firboy_right.getGlobalBounds().intersects(level[in_game.number_Level].boxes_left[1].getGlobalBounds())) {

		f_w.fireboy_st.FireBoy.move(-3.0f, 0.0f);
		f_w.watergirl_st.WaterGirl.move(3.0f, 0.0f);
		bool wg_touch = 0, fb_touch = 0;
		for (int i = 0; i < 60; i++) {
			if (!wg_touch && f_w.watergirl_st.watergirl_right.getGlobalBounds().intersects(level[in_game.number_Level].ground[i].getGlobalBounds()) && level[in_game.number_Level].ground[i].getFillColor() == Color::Yellow) {
				wg_touch = 1;
				f_w.watergirl_st.WaterGirl.move(-3.0f, 0.0f);
			}
			if (!fb_touch && f_w.fireboy_st.firboy_left.getGlobalBounds().intersects(level[in_game.number_Level].ground[i].getGlobalBounds()) && level[in_game.number_Level].ground[i].getFillColor() == Color::Yellow) {
				fb_touch = 1;
				f_w.fireboy_st.FireBoy.move(3.0f, 0.0f);
			}
		}
	}

}
void button_collision() {
	short int in = 0;
	for (int i = 1; i < 3; i++) {
		if (f_w.fireboy_st.firboy_down.getGlobalBounds().intersects(level[1].Button[i].getGlobalBounds())) {
			if (!level[1].Button[i].getGlobalBounds().intersects(level[1].button_down[i].getGlobalBounds())) {
				level[1].Button[i].move(0.f, 0.7f);
				if (!level[1].elevator_open) {
					level[1].elevator_open = 1;
				}
			}
		}
		if (f_w.watergirl_st.watergirl_down.getGlobalBounds().intersects(level[1].Button[i].getGlobalBounds())) {

			if (!level[1].Button[i].getGlobalBounds().intersects(level[1].button_down[i].getGlobalBounds())) {
				level[1].Button[i].move(0.f, 0.7f);
				if (!level[1].elevator_open) {
					level[1].elevator_open = 1;
				}
			}

		}
		if (level[1].elevator_open) {
			if (!level[1].Elevator[1].getGlobalBounds().intersects(level[1].ground[12].getGlobalBounds())) {
				if (!level[1].Elevator[1].getGlobalBounds().intersects(f_w.fireboy_st.firboy_top.getGlobalBounds()) && !level[1].Elevator[1].getGlobalBounds().intersects(f_w.watergirl_st.watergirl_top.getGlobalBounds()))
				{

					level[1].Elevator[1].move(0.f, 5.0f);
				}
				if (f_w.fireboy_st.firboy_down.getGlobalBounds().intersects(level[1].ground[14].getGlobalBounds())) {
					f_w.fireboy_st.FireBoy.move(0.0f, 5.f);
				}
				if (f_w.watergirl_st.watergirl_down.getGlobalBounds().intersects(level[1].ground[14].getGlobalBounds())) {
					f_w.watergirl_st.WaterGirl.move(0.0f, 5.f);
				}


			}


		}

		if (!f_w.fireboy_st.firboy_down.getGlobalBounds().intersects(level[1].Button[i].getGlobalBounds()) && !f_w.watergirl_st.watergirl_down.getGlobalBounds().intersects(level[1].Button[i].getGlobalBounds())) {
			in++;

			if (!level[1].Button[i].getGlobalBounds().intersects(level[1].button_up[i].getGlobalBounds())) {
				level[1].Button[i].move(0.f, -0.4f);
			}

		}
		if (in == 2)level[1].elevator_open = 0;
		if (!level[1].elevator_open) {
			if (!level[1].Elevator[1].getGlobalBounds().intersects(level[1].ground[42].getGlobalBounds())) {

				if (!f_w.fireboy_st.firboy_top.getGlobalBounds().intersects(level[1].ground[42].getGlobalBounds()) && !f_w.watergirl_st.watergirl_top.getGlobalBounds().intersects(level[1].ground[42].getGlobalBounds())) {
					{
						level[1].Elevator[1].move(0.f, -5.f);
						if (f_w.fireboy_st.firboy_down.getGlobalBounds().intersects(level[1].ground[14].getGlobalBounds())) {
							f_w.fireboy_st.FireBoy.move(0.0f, -5.f);
						}
						if (f_w.watergirl_st.watergirl_down.getGlobalBounds().intersects(level[1].ground[14].getGlobalBounds())) {
							f_w.watergirl_st.WaterGirl.move(0.0f, -5.f);
						}
					}
				}
			}
		}



	}
	////////////////////////////////////////////    lever   ////////////////////////////////////////////////////
	if (f_w.fireboy_st.firboy_left.getGlobalBounds().intersects(level[1].lever_right_hitbox.getGlobalBounds())) {
		if (level[1].lever_open == 0 && Keyboard::isKeyPressed(Keyboard::A)) {

			level[1].Button[4].setPosition(Vector2f(295.5f, 520.f));
			level[1].Button[4].setRotation(-34.f);
			level[1].Button[5].setPosition(Vector2f(295.5f, 520.f));
			level[1].lever_open = 1;
		}
	}
	if (f_w.watergirl_st.watergirl_left.getGlobalBounds().intersects(level[1].lever_right_hitbox.getGlobalBounds())) {

		if (level[1].lever_open == 0 && Keyboard::isKeyPressed(Keyboard::Left)) {
			level[1].Button[4].setPosition(Vector2f(295.5f, 520.f));
			level[1].Button[4].setRotation(-34.f);
			level[1].Button[5].setPosition(Vector2f(295.5f, 520.f));
			level[1].lever_open = 1;

		}
	}
	if (level[1].lever_open) {
		if (!level[1].Elevator[2].getGlobalBounds().intersects(level[1].ground[47].getGlobalBounds())) {
			if (!level[1].Elevator[2].getGlobalBounds().intersects(f_w.fireboy_st.firboy_top.getGlobalBounds()) && !level[1].Elevator[2].getGlobalBounds().intersects(f_w.watergirl_st.watergirl_top.getGlobalBounds()))
			{

				level[1].Elevator[2].move(0.f, 5.0f);
			}
			if (f_w.fireboy_st.firboy_down.getGlobalBounds().intersects(level[1].ground[27].getGlobalBounds())) {
				f_w.fireboy_st.FireBoy.move(0.0f, 5.f);
			}
			if (f_w.watergirl_st.watergirl_down.getGlobalBounds().intersects(level[1].ground[27].getGlobalBounds())) {
				f_w.watergirl_st.WaterGirl.move(0.0f, 5.f);
			}
		}
	}
	if (f_w.fireboy_st.firboy_right.getGlobalBounds().intersects(level[1].lever_left_hitbox.getGlobalBounds())) {
		if (level[1].lever_open == 1 && Keyboard::isKeyPressed(Keyboard::D)) {
			level[1].Button[4].setPosition(Vector2f(288.5f, 520.f));
			level[1].Button[4].setRotation(34.f);
			level[1].lever_open = 0;
		}
	}
	if (f_w.watergirl_st.watergirl_right.getGlobalBounds().intersects(level[1].lever_left_hitbox.getGlobalBounds())) {

		if (level[1].lever_open == 1 && Keyboard::isKeyPressed(Keyboard::Right)) {
			level[1].Button[4].setPosition(Vector2f(288.5f, 520.f));
			level[1].Button[4].setRotation(34.f);
			level[1].lever_open = 0;
		}
	}
	if (level[1].lever_open == 0) {
		if (!level[1].Elevator[2].getGlobalBounds().intersects(level[1].ground[10].getGlobalBounds())) {

			if (!f_w.fireboy_st.firboy_top.getGlobalBounds().intersects(level[1].ground[43].getGlobalBounds()) && !f_w.watergirl_st.watergirl_top.getGlobalBounds().intersects(level[1].ground[43].getGlobalBounds())) {
				{
					level[1].Elevator[2].move(0.f, -5.f);
					if (f_w.fireboy_st.firboy_down.getGlobalBounds().intersects(level[1].ground[27].getGlobalBounds())) {
						f_w.fireboy_st.FireBoy.move(0.0f, -5.f);
					}
					if (f_w.watergirl_st.watergirl_down.getGlobalBounds().intersects(level[1].ground[27].getGlobalBounds())) {
						f_w.watergirl_st.WaterGirl.move(0.0f, -5.f);
					}
				}
			}
		}
	}

}
void collision(RenderWindow& window, bool& isAnimationStandingFireBoy, double& velocityFireBoy, Sprite& FireBoy, bool& isAnimationStandingWaterGirl, double& velocityWaterGirl, Sprite& WaterGirl) {
	collision_fireboy(window, isAnimationStandingFireBoy, velocityFireBoy, FireBoy);
	collision_watergirl(window, isAnimationStandingWaterGirl, velocityWaterGirl, WaterGirl);
	collision_boxes(window);
	button_collision();

	///----Pause Collision----//
	Vector2i mousepos = Mouse::getPosition(window);
	if (Mouse::isButtonPressed(Mouse::Left) && mousepos.x > 1230 && mousepos.x < 1261 && mousepos.y> 8 && mousepos.y < 42) {
		level[1].Pause.setScale(0.8f, 0.8f);
		level[1].pauseclicked = 1;
		level[1].Pause.setPosition(1232, 9);
		level[1].ingame_setings_c.restart();
	}
	else {
		level[1].Pause.setPosition(1230, 8);
		level[1].Pause.setScale(1.0f, 1.0f);
	}

}
void Animation(RenderWindow& window) {



	//animation smoke fireboy
	level[1].smoke[1].setTextureRect(IntRect(90 * level[1].animationSmoke[1], 0, 90, 75));
	if (level[1].clockSmoke[1].getElapsedTime().asSeconds() >= 0.08)
	{
		level[1].animationSmoke[1]++;
		level[1].clockSmoke[1].restart();
	}
	if (level[1].isSmoke[1] == 0) level[1].animationSmoke[1] = 0;


	//animation smoke watergirl
	level[1].smoke[2].setTextureRect(IntRect(90 * level[1].animationSmoke[2], 0, 90, 75));
	if (level[1].clockSmoke[2].getElapsedTime().asSeconds() >= 0.08)
	{
		level[1].animationSmoke[2]++;
		level[1].clockSmoke[2].restart();
	}
	if (level[1].isSmoke[2] == 0) level[1].animationSmoke[2] = 0;

	//animation pond fireboy
	level[1].pondFireBoy[1].setTextureRect(IntRect(level[1].animationPond[1] * 160, 0, 160, 21));
	if (level[1].clockPond[1].getElapsedTime().asSeconds() >= 0.15)
	{
		level[1].animationPond[1]++; level[1].animationPond[1] %= 4;
		level[1].clockPond[1].restart();
	}

	//animation pond watergirl
	level[1].pondWaterGirl[1].setTextureRect(IntRect(level[1].animationPond[2] * 160, 0, 160, 21));
	if (level[1].clockPond[2].getElapsedTime().asSeconds() >= 0.14)
	{
		level[1].animationPond[2]++; level[1].animationPond[2] %= 4;
		level[1].clockPond[2].restart();
	}

	//animation pond black
	level[1].pondBlack[1].setTextureRect(IntRect(level[1].animationPond[3] * 160, 0, 160, 21));
	if (level[1].clockPond[3].getElapsedTime().asSeconds() >= 0.13)
	{
		level[1].animationPond[3]++; level[1].animationPond[3] %= 4;
		level[1].clockPond[3].restart();


	}

	//Animation standing player
	f_w.fireboy_st.FireBoy.setTextureRect(IntRect(149 * f_w.fireboy_st.animationStandingFireBoy, 0, 149, 160));
	f_w.watergirl_st.WaterGirl.setTextureRect(IntRect(149 * f_w.watergirl_st.animationStandingWaterGirl, 0, 149, 160));



	if (f_w.fireboy_st.isAnimationStandingFireBoy)
	{
		if (level[1].clockStandingFireBoy.getElapsedTime().asSeconds() >= 0.10)
		{
			f_w.fireboy_st.animationStandingFireBoy++;  f_w.fireboy_st.animationStandingFireBoy %= 19;
			level[1].clockStandingFireBoy.restart();
		}
	}
	if (f_w.watergirl_st.isAnimationStandingWaterGirl)
	{
		if (level[1].clockStandingWaterGirl.getElapsedTime().asSeconds() >= 0.10)
		{
			f_w.watergirl_st.animationStandingWaterGirl++; f_w.watergirl_st.animationStandingWaterGirl %= 30;
			level[1].clockStandingWaterGirl.restart();
		}
	}

	if (Keyboard::isKeyPressed(Keyboard::Key::Right) && Keyboard::isKeyPressed(Keyboard::Key::Left))
	{
		f_w.watergirl_st.isMoveWaterGirl = false;
		f_w.watergirl_st.isAnimationStandingWaterGirl = true;

	}
	else { f_w.watergirl_st.isMoveWaterGirl = true; }


	if (Keyboard::isKeyPressed(Keyboard::Key::D) && Keyboard::isKeyPressed(Keyboard::Key::A))
	{
		f_w.fireboy_st.isMoveFireBoy = false;
		f_w.fireboy_st.isAnimationStandingFireBoy = true;
	}
	else { f_w.fireboy_st.isMoveFireBoy = true; }


	////////////////////////////////////////////////////////////
	//move fireboy
	if (f_w.fireboy_st.isMoveFireBoy)
	{


		if (f_w.fireboy_st.velocityFireBoy > 0) {
			//	isAnimationStandingFireBoy = false;
			f_w.fireboy_st.FireBoy.setTextureRect(IntRect(149 * f_w.fireboy_st.moveFireBoy, 3 * 160, 149, 160));
			if (level[1].clockMoveFireBoy.getElapsedTime().asSeconds() >= 0.05)
			{
				f_w.fireboy_st.moveFireBoy++;
				if (f_w.fireboy_st.moveFireBoy > 4) f_w.fireboy_st.moveFireBoy = 0;
				level[1].clockMoveFireBoy.restart();
			}
			//if (f_w.fireboy_st.velocityFireBoy <0)f_w.fireboy_st.animationUpFireBoy = 0;
		}
		else if (f_w.fireboy_st.velocityFireBoy < 0)
		{
			f_w.fireboy_st.FireBoy.setTextureRect(IntRect(149 * f_w.fireboy_st.moveFireBoy, 2 * 160, 149, 160));
			if (level[1].clockMoveFireBoy.getElapsedTime().asSeconds() >= 0.05)
			{
				f_w.fireboy_st.moveFireBoy++;
				if (f_w.fireboy_st.moveFireBoy > 4) f_w.fireboy_st.moveFireBoy = 0;
				level[1].clockMoveFireBoy.restart();
			}
		}
		//	if (f_w.fireboy_st.grounded&&f_w.fireboy_st.velocityFireBoy ==0)f_w.fireboy_st.animationUpFireBoy = 1;

	//	cout << f_w.fireboy_st.velocityFireBoy << "\n";
		if (Keyboard::isKeyPressed(Keyboard::Key::A) && f_w.fireboy_st.FireBoy.getPosition().x > 50)
		{

			f_w.fireboy_st.isAnimationStandingFireBoy = false;
			f_w.fireboy_st.FireBoy.setTextureRect(IntRect(149 * f_w.fireboy_st.moveFireBoy, 1 * 160, 149, 160));
			if (level[1].clockMoveFireBoy.getElapsedTime().asSeconds() >= 0.05)
			{
				f_w.fireboy_st.moveFireBoy++;
				if (f_w.fireboy_st.moveFireBoy > 6) f_w.fireboy_st.moveFireBoy = 0;
				level[1].clockMoveFireBoy.restart();
			}
			f_w.fireboy_st.FireBoy.setScale(-0.7f, 0.7f);
			f_w.fireboy_st.FireBoy.move(-5, 0);

		}


		else if (Keyboard::isKeyPressed(Keyboard::Key::D) && f_w.fireboy_st.FireBoy.getPosition().x < 1230)
		{

			f_w.fireboy_st.isAnimationStandingFireBoy = false;
			f_w.fireboy_st.FireBoy.setTextureRect(IntRect(149 * f_w.fireboy_st.moveFireBoy, 1 * 160, 149, 160));
			if (level[1].clockMoveFireBoy.getElapsedTime().asSeconds() >= 0.05)
			{
				f_w.fireboy_st.moveFireBoy++;
				if (f_w.fireboy_st.moveFireBoy > 6) f_w.fireboy_st.moveFireBoy = 0;
				level[1].clockMoveFireBoy.restart();
			}
			f_w.fireboy_st.FireBoy.setScale(0.7f, 0.7f);
			f_w.fireboy_st.FireBoy.move(5, 0);

		}
		else { f_w.fireboy_st.isAnimationStandingFireBoy = true; }

	}

	//////////////////////////////////
	//move watergirl
	if (f_w.watergirl_st.isMoveWaterGirl)
	{
		if (f_w.watergirl_st.velocityWaterGirl > 0) {
			//	isAnimationStandingFireBoy = false;
			f_w.watergirl_st.WaterGirl.setTextureRect(IntRect(149 * f_w.watergirl_st.moveWaterGirl, 3 * 160, 149, 160));
			if (level[1].clockMoveWaterGirl.getElapsedTime().asSeconds() >= 0.05)
			{
				f_w.watergirl_st.moveWaterGirl++;
				if (f_w.watergirl_st.moveWaterGirl > 4) f_w.watergirl_st.moveWaterGirl = 0;
				level[1].clockMoveWaterGirl.restart();
			}
			//if (f_w.fireboy_st.velocityFireBoy <0)f_w.fireboy_st.animationUpFireBoy = 0;
		}
		else if (f_w.watergirl_st.velocityWaterGirl < 0)
		{
			f_w.watergirl_st.WaterGirl.setTextureRect(IntRect(149 * f_w.watergirl_st.moveWaterGirl, 2 * 160, 149, 160));
			if (level[1].clockMoveWaterGirl.getElapsedTime().asSeconds() >= 0.05)
			{
				f_w.watergirl_st.moveWaterGirl++;
				if (f_w.watergirl_st.moveWaterGirl > 4) f_w.watergirl_st.moveWaterGirl = 0;
				level[1].clockMoveWaterGirl.restart();
			}
		}




		if (Keyboard::isKeyPressed(Keyboard::Key::Right) && f_w.watergirl_st.WaterGirl.getPosition().x < 1230)
		{

			f_w.watergirl_st.isAnimationStandingWaterGirl = false;
			f_w.watergirl_st.WaterGirl.setTextureRect(IntRect(149 * f_w.watergirl_st.moveWaterGirl, 1 * 160, 149, 160));
			if (level[1].clockMoveWaterGirl.getElapsedTime().asSeconds() >= 0.05)
			{
				f_w.watergirl_st.moveWaterGirl++;
				if (f_w.watergirl_st.moveWaterGirl > 10)f_w.watergirl_st.moveWaterGirl = 0;

				level[1].clockMoveWaterGirl.restart();
			}
			f_w.watergirl_st.WaterGirl.setScale(0.7f, 0.7f);
			f_w.watergirl_st.WaterGirl.move(5, 0);

		}
		else if (Keyboard::isKeyPressed(Keyboard::Key::Left) && f_w.watergirl_st.WaterGirl.getPosition().x > 50)
		{

			f_w.watergirl_st.isAnimationStandingWaterGirl = false;
			f_w.watergirl_st.WaterGirl.setTextureRect(IntRect(149 * f_w.watergirl_st.moveWaterGirl, 1 * 160, 149, 160));
			if (level[1].clockMoveWaterGirl.getElapsedTime().asSeconds() >= 0.05)
			{
				f_w.watergirl_st.moveWaterGirl++;
				if (f_w.watergirl_st.moveWaterGirl > 10)f_w.watergirl_st.moveWaterGirl = 0;

				level[1].clockMoveWaterGirl.restart();
			}
			f_w.watergirl_st.WaterGirl.setScale(-0.7f, 0.7f);
			f_w.watergirl_st.WaterGirl.move(-5, 0);

		}
		else { f_w.watergirl_st.isAnimationStandingWaterGirl = true; }
	}


	//animation door fireboy
	if (f_w.fireboy_st.firboy_down.getGlobalBounds().intersects(level[1].FireBoy_DoorOpening.getGlobalBounds())) {
		if (!level[1].fireboy_dooropening)
		{
			level[1].door[1].setLoop(false);
			level[1].door[1].play();

		}
		level[1].fireboy_dooropening = 1;
		if (level[1].clockDoor[1].getElapsedTime().asSeconds() >= 0.036)
		{
			level[1].FireBoy_DoorOpening.setTextureRect(IntRect(level[1].animationDoorFireBoy * 114, 0, 114, 123));
			if (level[1].animationDoorFireBoy != 21) { level[1].animationDoorFireBoy++; }
			level[1].clockDoor[1].restart();
		}
		if (level[1].animationDoorFireBoy == 21)level[1].door[1].stop();
	}
	else {
		if (level[1].fireboy_dooropening)
		{
			level[1].door[1].setLoop(false);
			level[1].door[1].play();

		}
		level[1].fireboy_dooropening = 0;
		if (level[1].clockDoor[1].getElapsedTime().asSeconds() >= 0.036)
		{
			level[1].FireBoy_DoorOpening.setTextureRect(IntRect(level[1].animationDoorFireBoy * 114, 0, 114, 123));
			if (level[1].animationDoorFireBoy != 0) { level[1].animationDoorFireBoy--; }
			level[1].clockDoor[1].restart();
		}
		if (level[1].animationDoorFireBoy == 0)level[1].door[1].stop();

	}
	//animation door watergirl
	if (f_w.watergirl_st.watergirl_down.getGlobalBounds().intersects(level[1].WaterGirl_DoorOpening.getGlobalBounds()))
	{
		if (!level[1].watergirl_dooropening)
		{
			level[1].door[2].setLoop(false);
			level[1].door[2].play();
		}
		level[1].watergirl_dooropening = 1;
		if (level[1].clockDoor[2].getElapsedTime().asSeconds() >= 0.036)
		{
			level[1].WaterGirl_DoorOpening.setTextureRect(IntRect(level[1].animationDoorWaterGirl * 114, 0, 114, 122));
			if (level[1].animationDoorWaterGirl != 21) { level[1].animationDoorWaterGirl++; }
			level[1].clockDoor[2].restart();
		}
		if (level[1].animationDoorWaterGirl == 21)level[1].door[2].stop();

	}
	else {
		if (level[1].watergirl_dooropening)
		{
			level[1].door[2].setLoop(false);
			level[1].door[2].play();
		}
		level[1].watergirl_dooropening = 0;
		if (level[1].clockDoor[2].getElapsedTime().asSeconds() >= 0.036)
		{
			level[1].WaterGirl_DoorOpening.setTextureRect(IntRect(level[1].animationDoorWaterGirl * 114, 0, 114, 122));
			if (level[1].animationDoorWaterGirl != 0) { level[1].animationDoorWaterGirl--; }
			level[1].clockDoor[2].restart();
		}
		if (level[1].animationDoorWaterGirl == 0)level[1].door[2].stop();
	}


	if (level[1].animationDoorFireBoy == 21 && level[1].animationDoorWaterGirl == 21) {
		level[1].both_dooropening = 1;
		level[1].FireBoy_DoorMoving.setTextureRect(IntRect(level[1].animationBothDoor * 149, 0, 149, 160));
		level[1].WaterGirl_DoorMoving.setTextureRect(IntRect(level[1].animationBothDoor * 149, 0, 149, 160));
		f_w.fireboy_st.FireBoy.setScale(0, 0);
		f_w.watergirl_st.WaterGirl.setScale(0, 0);
		in_game.win = 1;
		if (level[1].animationBothDoor != 28) { level[1].animationBothDoor++; }
	}
	if (in_game.win)
	{
		in_game.number_Level = 2;
		in_game.win = 0;
	}
}
void Game_Play(RenderWindow& window)
{
	//levels
	/*switch (in_game.number_Level)
	{
	case 1:
		Level1(window); break;

	case 2:
		Level2(window); break;

	}*/
	if (in_game.number_Level == 1) {
		Level1(window);
	}
	else if (in_game.number_Level == 2) {
		Level2(window);
	}
	fire_water_hitboxes(window);



	///////////////////////////////////////////////////////


	test2.setSize(Vector2f(5, 5));
	test2.setFillColor(Color::Red);
	test2.setOrigin(2.5, 2.5);
	test2.setPosition(892, 245);

	///////////////////////


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


		//timer
		level[1].sa3a_s = level[1].timer.getElapsedTime();
		level[1].elwaqt_s.setString(to_string((int)level[1].sa3a_s.asSeconds()));

		//////////////////////
		///test
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
			sf::Vector2i mouse_position = sf::Mouse::getPosition(window);
			std::cout << mouse_position.x << "  " << mouse_position.y << "\n";
		}
		////////////////////////


		///////////////// call all functions////////////////////////////
		updatef_whitboxes(window, f_w.fireboy_st.FireBoy, f_w.watergirl_st.WaterGirl);
		collision(window, f_w.fireboy_st.isAnimationStandingFireBoy, f_w.fireboy_st.velocityFireBoy, f_w.fireboy_st.FireBoy, f_w.watergirl_st.isAnimationStandingWaterGirl, f_w.watergirl_st.velocityWaterGirl, f_w.watergirl_st.WaterGirl);
		Animation(window);
		////////////////////////////////////////////////////////////////////////////////////////



		{if (Keyboard::isKeyPressed(Keyboard::Key::I))
			test2.move(0, -0.5);

		if (Keyboard::isKeyPressed(Keyboard::Key::L))
			test2.move(0.5, 0);

		if (Keyboard::isKeyPressed(Keyboard::Key::K))
			test2.move(0, 0.5);

		if (Keyboard::isKeyPressed(Keyboard::Key::J))
			test2.move(-0.5, 0);
		if (Keyboard::isKeyPressed(Keyboard::Key::P))
			cout << test2.getPosition().x << "   " << test2.getPosition().y << endl;
		}


		window.clear();
		draw(window, f_w.fireboy_st.FireBoy, f_w.watergirl_st.WaterGirl);
		level[in_game.number_Level].cube[1].move(0.0f, -level[in_game.number_Level].velocityboxes[1]);
		f_w.fireboy_st.FireBoy.move(0, -f_w.fireboy_st.velocityFireBoy);
		f_w.watergirl_st.WaterGirl.move(0, -f_w.watergirl_st.velocityWaterGirl);

		window.draw(level[1].fb_count);
		window.draw(level[1].wg_count);
		window.draw(level[1].elwaqt_s);
		window.display();
	}
}
void draw(RenderWindow& window, Sprite& FireBoy, Sprite& WaterGirl)
{

	///////////////// draw level1 ///////////////////////
	if (in_game.number_Level == 1)
	{
		window.draw(level[1].background_levels[1]);
		window.draw(level[1].Button[1]);
		window.draw(level[1].Button[2]);
		window.draw(level[1].ground_levels[1]);
		if (level[1].lever_open) window.draw(level[1].Button[5]);
		else 	window.draw(level[1].Button[4]);
		if (level[1].lever_open)window.draw(level[1].Button[6]);
		else window.draw(level[1].Button[3]);

		for (int i = 0; i < 60; i++)
		{

			//window.draw(level[1].ground[i]);
			if (i < 11)
			{
				window.draw(level[1].coinFireBoy[i]);
				window.draw(level[1].coinWaterGirl[i]);
				if (i < 3)
				{
					if (level[1].isSmoke[1] == 1) window.draw(level[1].smoke[1]);
					if (level[1].isSmoke[2] == 1) window.draw(level[1].smoke[2]);
				}
			}
		}
		window.draw(level[1].cube[1]);

		window.draw(level[1].Elevator[2]);
		window.draw(level[1].Elevator[1]);

		//	window.draw(level[1].lever_left_hitbox);
		//	window.draw(level[1].lever_right_hitbox);

			// window.draw(f_w.fireboy_st.firboy_down);
			// window.draw(f_w.watergirl_st.watergirl_down);

			//  window.draw(level[1].button_up[1]);
			//   window.draw(level[1].button_down[1]);
			//  window.draw(level[1].button_up[2]);
			//  window.draw(level[1].button_down[2]);
			/*window.draw(level[1].boxes_down[1]);
			window.draw(level[1].boxes_top[1]);
			window.draw(level[1].boxes_left[1]);
			window.draw(level[1].boxes_right[1]);*/

			// window.draw(level[1].background_levels[1]);
		//     window.draw(level[1].ground_levels[1]);
		window.draw(level[1].FireBoy_DoorStand);
		window.draw(level[1].WaterGirl_DoorStand);
		/*    window.draw(RectangleUp);
			window.draw(RectangleDown);
			window.draw(RectangleLeft);
			window.draw(RectangleRight);*/
		if (level[1].animationDoorFireBoy != 0) {
			window.draw(level[1].FireBoy_DoorOpening);
		}
		if (level[1].animationDoorWaterGirl != 0) {
			window.draw(level[1].WaterGirl_DoorOpening);
		}
		if (level[1].both_dooropening) {
			window.draw(level[1].FireBoy_DoorMoving);
			window.draw(level[1].WaterGirl_DoorMoving);
		}
		window.draw(FireBoy);
		window.draw(WaterGirl);
		//	window.draw(level[1].convexs[2]);
			//window.draw(firboy_top);
			//window.draw(firboy_down);
			// 
			//    window.draw(firboy_right);
			//    window.draw(firboy_left);
				//window.draw(test);
		window.draw(level[1].pondFireBoy[1]);
		window.draw(level[1].pondWaterGirl[1]);
		window.draw(level[1].pondBlack[1]);
		window.draw(test2);

		window.draw(level[1].Pause);
		if (level[1].pauseclicked) {
			window.draw(in_game.Background);
			window.draw(in_game.settings_menu);
			if (!in_game.Settings_hitbox.getGlobalBounds().intersects(in_game.settings_menu.getGlobalBounds())) {
				in_game.settings_menu.move(0, -30);
			}
		}
	}
	/*if (in_game.number_Level == 2)Game_Play(window);*/

	///////////////// draw level2 ///////////////////////
	if (in_game.number_Level == 2)
	{
		window.draw(level[2].background_levels[2]);
		/*window.draw(level[1].Button[1]);
		window.draw(level[1].Button[2]);*/
		window.draw(level[2].ground_levels[2]);
		/*if (level[1].lever_open) window.draw(level[1].Button[5]);
		else 	window.draw(level[1].Button[4]);
		if (level[1].lever_open)window.draw(level[1].Button[6]);
		else window.draw(level[1].Button[3]);*/

		for (int i = 0; i < 60; i++)
		{

			window.draw(level[2].ground[i]);
			window.draw(level[2].convexs[i]);
		}
		/*window.draw(level[1].cube[1]);

		window.draw(level[1].Elevator[2]);
		window.draw(level[1].Elevator[1]);*/

		//	window.draw(level[1].lever_left_hitbox);
		//	window.draw(level[1].lever_right_hitbox);

			// window.draw(f_w.fireboy_st.firboy_down);
			// window.draw(f_w.watergirl_st.watergirl_down);

			//  window.draw(level[1].button_up[1]);
			//   window.draw(level[1].button_down[1]);
			//  window.draw(level[1].button_up[2]);
			//  window.draw(level[1].button_down[2]);
			/*window.draw(level[1].boxes_down[1]);
			window.draw(level[1].boxes_top[1]);
			window.draw(level[1].boxes_left[1]);
			window.draw(level[1].boxes_right[1]);*/

			// window.draw(level[1].background_levels[1]);
		//     window.draw(level[1].ground_levels[1]);
		/*window.draw(level[1].FireBoy_DoorStand);
		window.draw(level[1].WaterGirl_DoorStand);*/
		/*    window.draw(RectangleUp);
			window.draw(RectangleDown);
			window.draw(RectangleLeft);
			window.draw(RectangleRight);*/
			/*if (level[1].animationDoorFireBoy != 0) {
				window.draw(level[1].FireBoy_DoorOpening);
			}
			if (level[1].animationDoorWaterGirl != 0) {
				window.draw(level[1].WaterGirl_DoorOpening);
			}
			if (level[1].both_dooropening) {
				window.draw(level[1].FireBoy_DoorMoving);
				window.draw(level[1].WaterGirl_DoorMoving);
			}*/
		window.draw(WaterGirl);
		window.draw(FireBoy);
		//	window.draw(level[1].convexs[2]);
			//window.draw(firboy_top);
			//window.draw(firboy_down);
			// 
		window.draw(f_w.fireboy_st.firboy_right);
		window.draw(f_w.watergirl_st.watergirl_right);
		//    window.draw(firboy_left);
			//window.draw(test);
	/*window.draw(level[1].pondFireBoy[1]);
	window.draw(level[1].pondWaterGirl[1]);
	window.draw(level[1].pondBlack[1]);*/
		window.draw(test2);

		/*window.draw(level[2].Pause);
		if (level[2].pauseclicked) {
			window.draw(in_game.Background);
			window.draw(in_game.settings_menu);
			if (!in_game.Settings_hitbox.getGlobalBounds().intersects(in_game.settings_menu.getGlobalBounds())) {
				in_game.settings_menu.move(0, -30);
			}
		}*/
	}
}
