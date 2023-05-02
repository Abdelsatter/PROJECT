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
void Levels(RenderWindow& window);
void fire_water_hitboxes(RenderWindow& window);
void collision_fireboy(RenderWindow& window, bool& isAnimationStandingFireBoy, double& velocityFireBoy, Sprite& FireBoy);
void collision_watergirl(RenderWindow& window, bool& isAnimationStandingWaterGirl, double& velocityWaterGirl, Sprite& WaterGirl);
void Animation(RenderWindow& window);
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
//struct {
//	RectangleShape ground[60];
//	Texture gr_levels[10], bgr_background[10];
//	Sprite ground_levels[10], background_levels[10];
//	ConvexShape convexs[30];
//	bool grounded = 0;
//
//}level[10];
struct {
	RectangleShape ground[60];
	Texture gr_levels[10], bgr_background[10], pondFireImage, pondWaterImage, coinFireImage, coinWaterImage, fireboyDoorStand, watergirlDoorStand, fireboydoormoving, watergirldoormoving, fireboydooropening, watergirldooropening;
	Sprite ground_levels[10], background_levels[10], pondFireBoy[10], pondWaterGirl[10], coinFireBoy[10], coinWaterGirl[10], FireBoy_DoorStand, WaterGirl_DoorStand, FireBoy_DoorMoving, WaterGirl_DoorMoving, FireBoy_DoorOpening, WaterGirl_DoorOpening;
	ConvexShape convexs[30];
	bool  fireboy_dooropening = 0, watergirl_dooropening = 0, both_dooropening = 0, isAnimationLava = 0;
	int animationDoorFireBoy = 0, animationDoorWaterGirl = 0, AnimationBothDoor = 0;
	int animationPond = 0;
	Clock clockStandingFireBoy, clockStandingWaterGirl, clockMoveFireBoy, clockMoveWaterGirl, clockPondFireBoy;
	Music music;

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
void updatef_whitboxes(RenderWindow& window, Sprite& FireBoy, Sprite& WaterGirl) {

	// set position hit box fireboy ( up )
	f_w.fireboy_st.firboy_top.setPosition(Vector2f(FireBoy.getPosition().x, FireBoy.getPosition().y - 170));

	// set position hit box fireboy ( dowm )
	f_w.fireboy_st.firboy_down.setPosition(Vector2f(FireBoy.getPosition().x, FireBoy.getPosition().y - 127));

	// set position hit box fireboy ( right )
	f_w.fireboy_st.firboy_right.setPosition(Vector2f(FireBoy.getPosition().x + 5, FireBoy.getPosition().y - 150));

	// set position hit box fireboy ( left )
	f_w.fireboy_st.firboy_left.setPosition(Vector2f(FireBoy.getPosition().x - 5, FireBoy.getPosition().y - 150));


	//////////////////////////////////////////////////////////////
	// set position hit box fireboy ( up )
	f_w.watergirl_st.watergirl_top.setPosition(Vector2f(WaterGirl.getPosition().x, WaterGirl.getPosition().y - 170));

	// set position hit box fireboy ( dowm )
	f_w.watergirl_st.watergirl_down.setPosition(Vector2f(WaterGirl.getPosition().x, WaterGirl.getPosition().y - 130));

	// set position hit box fireboy ( right )
	f_w.watergirl_st.watergirl_right.setPosition(Vector2f(WaterGirl.getPosition().x + 5, WaterGirl.getPosition().y - 150));

	// set position hit box fireboy ( left )
	f_w.watergirl_st.watergirl_left.setPosition(Vector2f(WaterGirl.getPosition().x - 5, WaterGirl.getPosition().y - 150));

}
void fire_water_hitboxes(RenderWindow& window) {

	// hitbox (up_firboy)
	f_w.fireboy_st.firboy_top.setSize(Vector2f(5, 20));
	f_w.fireboy_st.firboy_top.setFillColor(Color::Blue);
	f_w.fireboy_st.firboy_top.setOrigin(2.5, 10);

	// hitbox (down_firboy)
	f_w.fireboy_st.firboy_down.setSize(Vector2f(5, 15));
	f_w.fireboy_st.firboy_down.setFillColor(Color::Blue);
	f_w.fireboy_st.firboy_down.setOrigin(2.5, 7.5);

	// hitbox (right_firboy)
	f_w.fireboy_st.firboy_right.setSize(Vector2f(20, 40));
	f_w.fireboy_st.firboy_right.setFillColor(Color::Blue);
	f_w.fireboy_st.firboy_right.setOrigin(10, 20);

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
	f_w.watergirl_st.watergirl_down.setSize(Vector2f(5, 15));
	f_w.watergirl_st.watergirl_down.setFillColor(Color::Blue);
	f_w.watergirl_st.watergirl_down.setOrigin(2.5, 7.5);

	// hitbox (right_watergirl)
	f_w.watergirl_st.watergirl_right.setSize(Vector2f(20, 40));
	f_w.watergirl_st.watergirl_right.setFillColor(Color::Blue);
	f_w.watergirl_st.watergirl_right.setOrigin(10, 20);

	// hitbox (left_watergirl)
	f_w.watergirl_st.watergirl_left.setSize(Vector2f(20, 40));
	f_w.watergirl_st.watergirl_left.setFillColor(Color::Blue);
	f_w.watergirl_st.watergirl_left.setOrigin(10, 20);
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
				play_button.setScale(0.9f, 0.9f);
				play_button.setPosition(584, 344.5);
				playclicked = 1;
			}
			else if (mousepos.x > 35 && mousepos.x < 82 && mousepos.y>600 && mousepos.y < 649) {
				settings.setScale(0.9f, 0.9f);
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


	//MUSIC Game_play
	level[1].music.openFromFile("background-music.ogg");
	level[1].music.play();
	level[1].music.setLoop(1);
	
	//pond fireboy
	level[1].pondFireImage.loadFromFile("Lava.png");
	level[1].pondFireBoy[1].setTexture(level[1].pondFireImage);
	level[1].pondFireBoy[1].setPosition(594, 708);
	//pond watergirl
	// coin fireboy
	// coin watergirl
	//set fireboy
	f_w.fireboy_st.fireBoyImage.loadFromFile("Fireboy.png");
	f_w.fireboy_st.FireBoy.setTexture(f_w.fireboy_st.fireBoyImage);
	f_w.fireboy_st.FireBoy.setPosition(600, 200);
	f_w.fireboy_st.FireBoy.setOrigin(f_w.fireboy_st.FireBoy.getLocalBounds().width / 38, f_w.fireboy_st.FireBoy.getLocalBounds().height / 2);
	f_w.fireboy_st.FireBoy.setScale(0.7f, 0.7f);
	//set watergirl
	f_w.watergirl_st.waterGirlImage.loadFromFile("Watergirl.png");
	f_w.watergirl_st.WaterGirl.setPosition(600, 200);
	f_w.watergirl_st.WaterGirl.setTexture(f_w.watergirl_st.waterGirlImage);
	f_w.watergirl_st.WaterGirl.setOrigin(f_w.watergirl_st.WaterGirl.getLocalBounds().width / 60, f_w.watergirl_st.WaterGirl.getLocalBounds().height / 2);
	f_w.watergirl_st.WaterGirl.setScale(0.7f, 0.7f);
	//set fireboy's door
	level[1].fireboyDoorStand.loadFromFile("fbDoor.png");
	level[1].FireBoy_DoorStand.setPosition(1050, 61);
	level[1].FireBoy_DoorStand.setTexture(level[1].fireboyDoorStand);
	level[1].FireBoy_DoorStand.setScale(0.7f, 0.7f);
	//set watergirl's door
	level[1].watergirlDoorStand.loadFromFile("wgDoor.png");
	level[1].WaterGirl_DoorStand.setPosition(1150, 61);
	level[1].WaterGirl_DoorStand.setTexture(level[1].watergirlDoorStand);
	level[1].WaterGirl_DoorStand.setScale(0.7f, 0.7f);
	//set Fireboy door opening
	level[1].fireboydooropening.loadFromFile("fb_door.png");
	level[1].FireBoy_DoorOpening.setPosition(1060, 78);
	level[1].FireBoy_DoorOpening.setTexture(level[1].fireboydooropening);
	level[1].FireBoy_DoorOpening.setScale(0.71f, 0.72f);
	//set Watergirl door opening
	level[1].watergirldooropening.loadFromFile("wg_door.png");
	level[1].WaterGirl_DoorOpening.setPosition(1160, 78);
	level[1].WaterGirl_DoorOpening.setTexture(level[1].watergirldooropening);
	level[1].WaterGirl_DoorOpening.setScale(0.71f, 0.71f);
	//set Fireboy moving door
	level[1].fireboydoormoving.loadFromFile("fbWin.png");
	level[1].FireBoy_DoorMoving.setPosition(1050, 61);
	level[1].FireBoy_DoorMoving.setTexture(level[1].fireboydoormoving);
	level[1].FireBoy_DoorMoving.setScale(0.7f, 0.7f);
	//set Watergirl moving door
	level[1].watergirldoormoving.loadFromFile("wgWin.png");
	level[1].WaterGirl_DoorMoving.setPosition(1150, 61);
	level[1].WaterGirl_DoorMoving.setTexture(level[1].watergirldoormoving);
	level[1].WaterGirl_DoorMoving.setScale(0.7f, 0.7f);

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
	level[1].ground[0].setSize(Vector2f(593, 2));
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


	level[1].ground[14].setSize(Vector2f(2, 120));
	level[1].ground[14].setRotation(130.f);         ///////
	level[1].ground[14].setPosition(Vector2f(1185, 507));
	level[1].ground[14].setFillColor(Color::Magenta);

	level[1].ground[15].setSize(Vector2f(90, 2));
	level[1].ground[15].setPosition(Vector2f(1183, 507));
	level[1].ground[15].setFillColor(Color::Cyan);

	level[1].ground[16].setSize(Vector2f(185, 2));
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

	//  level[1].ground[21].setSize(Vector2f(155, 2));
	//	level[1].ground[21].setPosition(Vector2f(400, 163));

	level[1].ground[22].setSize(Vector2f(70, 2));
	level[1].ground[22].setPosition(Vector2f(360, 115));
	level[1].ground[22].setFillColor(Color::Cyan);

	level[1].ground[23].setSize(Vector2f(80, 2));
	level[1].ground[23].setPosition(Vector2f(420, 140));
	level[1].ground[23].setFillColor(Color::Cyan);

	level[1].ground[24].setSize(Vector2f(157, 2));
	level[1].ground[24].setPosition(Vector2f(953, 330));
	level[1].ground[24].setFillColor(Color::Cyan);

	level[1].ground[25].setSize(Vector2f(2, 43));
	level[1].ground[25].setRotation(140.f);      //////////
	level[1].ground[25].setPosition(Vector2f(525, 170));
	level[1].ground[25].setFillColor(Color::Magenta);

	level[1].ground[26].setSize(Vector2f(2, 40));
	level[1].ground[26].setRotation(130.f);    ////////
	level[1].ground[26].setPosition(Vector2f(459, 140));
	level[1].ground[26].setFillColor(Color::Magenta);

	level[1].ground[27].setSize(Vector2f(2, 45));
	level[1].ground[27].setRotation(130.f);     //////
	level[1].ground[27].setPosition(Vector2f(397, 157));
	level[1].ground[27].setFillColor(Color::Magenta);

	level[1].ground[28].setSize(Vector2f(2, 110));
	level[1].ground[28].setRotation(125.f);    //////
	level[1].ground[28].setPosition(Vector2f(980, 310));
	level[1].ground[28].setFillColor(Color::Magenta);


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


	level[1].ground[46].setSize(Vector2f(2, 28));
	level[1].ground[46].setRotation(40.f);      //////////
	level[1].ground[46].setPosition(Vector2f(359, 114));
	level[1].ground[46].setFillColor(Color::Magenta);


	level[1].ground[47].setSize(Vector2f(40, 2));
	level[1].ground[47].setRotation(35.f);      //////////
	level[1].ground[47].setPosition(Vector2f(592, 407));
	level[1].ground[47].setFillColor(Color::Magenta);


	level[1].ground[48].setSize(Vector2f(40, 2));
	level[1].ground[48].setRotation(37.f);      //////////
	level[1].ground[48].setPosition(Vector2f(924, 309));
	level[1].ground[48].setFillColor(Color::Magenta);


	level[1].ground[49].setSize(Vector2f(80, 2));
	level[1].ground[49].setRotation(37.f);      //////////
	level[1].ground[49].setPosition(Vector2f(492, 529));
	level[1].ground[49].setFillColor(Color::Magenta);


	level[1].ground[50].setSize(Vector2f(40, 2));
	level[1].ground[50].setRotation(27.f);      //////////
	level[1].ground[50].setPosition(Vector2f(779, 559));
	level[1].ground[50].setFillColor(Color::Magenta);


	level[1].ground[51].setSize(Vector2f(25, 2));
	level[1].ground[51].setRotation(147.f);      //////////
	level[1].ground[51].setPosition(Vector2f(952, 565));
	level[1].ground[51].setFillColor(Color::Magenta);


	level[1].ground[52].setSize(Vector2f(25, 2));
	level[1].ground[52].setRotation(27.f);      //////////
	level[1].ground[52].setPosition(Vector2f(1084, 565));
	level[1].ground[52].setFillColor(Color::Magenta);


	level[1].ground[53].setSize(Vector2f(2, 40));
	level[1].ground[53].setRotation(47.f);      //////////
	level[1].ground[53].setPosition(Vector2f(1186, 639));
	level[1].ground[53].setFillColor(Color::Magenta);


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

}
void collision_fireboy(RenderWindow& window, bool& isAnimationStandingFireBoy, double& velocityFireBoy, Sprite& FireBoy)
{

	bool top = 0, down = 0, r = 0, l = 0;
	//collision fireboy_down
	for (int i = 0; i < 60; i++) {
		if (level[1].ground[i].getGlobalBounds().intersects(f_w.fireboy_st.firboy_down.getGlobalBounds()) && (level[1].ground[i].getFillColor() == Color::Cyan)) {
			down = 1;
			f_w.fireboy_st.grounded = 1;
		}
	}

	if (down)
	{
		isAnimationStandingFireBoy = 1;
		velocityFireBoy = 0;
		if (Keyboard::isKeyPressed(Keyboard::Key::W)) {
			velocityFireBoy = 6.5;
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
		if (level[1].ground[i].getGlobalBounds().intersects(f_w.fireboy_st.firboy_top.getGlobalBounds()) && (level[1].ground[i].getFillColor() == Color::Cyan)) {
			top = 1;
		}

	}
	if (top && !isAnimationStandingFireBoy) {
		velocityFireBoy = -1.7;

	}
	//collision fireboy_right
	for (int i = 0; i < 60; i++) {
		if (level[1].ground[i].getGlobalBounds().intersects(f_w.fireboy_st.firboy_right.getGlobalBounds()) && Keyboard::isKeyPressed(Keyboard::Key::D) && level[1].ground[i].getFillColor() == Color::Yellow) {
			FireBoy.move(-5, 0);
		}
	}

	/////collision fireboy_left

	for (int i = 0; i < 60; i++) {
		if (level[1].ground[i].getGlobalBounds().intersects(f_w.fireboy_st.firboy_left.getGlobalBounds()) && Keyboard::isKeyPressed(Keyboard::Key::A) && level[1].ground[i].getFillColor() == Color::Yellow) {
			FireBoy.move(5, 0);
		}
	}


	///////////////////////////---------------collision convexs---------------------///////////////////////////

	for (int i = 0; i < 30; i++)
	{


		if (f_w.fireboy_st.firboy_down.getGlobalBounds().intersects(level[1].convexs[i].getGlobalBounds()) && level[1].convexs[i].getFillColor() == Color::Green) {
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
					cout << "no\n";
				}

				FireBoy.move(2.0, 2.0);
				cout << "YES\n";
			}
			if (Keyboard::isKeyPressed(Keyboard::Key::W))
				velocityFireBoy = 5.5;

		}
		else if (f_w.fireboy_st.firboy_down.getGlobalBounds().intersects(level[1].convexs[i].getGlobalBounds()) && level[1].convexs[i].getFillColor() == Color::Red) {
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
				cout << "no\n";
			}

			if (!f_w.fireboy_st.grounded)
			{
				FireBoy.move(-2.0, 2.0);
				cout << "YES\n";
			}

			if (Keyboard::isKeyPressed(Keyboard::Key::W))
				velocityFireBoy = 5.5;

		}
		if (f_w.fireboy_st.firboy_top.getGlobalBounds().intersects(level[1].convexs[i].getGlobalBounds()) && level[1].convexs[i].getFillColor() == Color::Black) {

			f_w.fireboy_st.velocityFireBoy = -3.7;
		}
	}
	if (f_w.fireboy_st.firboy_left.getGlobalBounds().intersects(level[1].convexs[2].getGlobalBounds()) && !(f_w.fireboy_st.firboy_down.getGlobalBounds().intersects(level[1].convexs[2].getGlobalBounds()))) {
		FireBoy.move(5.2f, 0);
	}

	if (f_w.fireboy_st.firboy_right.getGlobalBounds().intersects(level[1].convexs[2].getGlobalBounds()) && !(f_w.fireboy_st.firboy_down.getGlobalBounds().intersects(level[1].convexs[2].getGlobalBounds()))) {
		FireBoy.move(-5.2f, 0);
	}


}
void collision_watergirl(RenderWindow& window, bool& isAnimationStandingWaterGirl, double& velocityWaterGirl, Sprite& WaterGirl)
{
	bool top = 0, down = 0, r = 0, l = 0;
	//collision watergirl_down
	for (int i = 0; i < 60; i++) {
		if (level[1].ground[i].getGlobalBounds().intersects(f_w.watergirl_st.watergirl_down.getGlobalBounds()) && (level[1].ground[i].getFillColor() == Color::Cyan)) {
			down = 1;
			f_w.watergirl_st.grounded = 1;
		}
	}
	if (down)
	{
		isAnimationStandingWaterGirl = 1;
		velocityWaterGirl = 0;
		if (Keyboard::isKeyPressed(Keyboard::Key::Up)) {
			velocityWaterGirl = 6.5;
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
		if (level[1].ground[i].getGlobalBounds().intersects(f_w.watergirl_st.watergirl_top.getGlobalBounds()) && (level[1].ground[i].getFillColor() == Color::Cyan)) {
			top = 1;
		}

	}
	if (top && !isAnimationStandingWaterGirl) {
		velocityWaterGirl = -1;

	}
	//collision watergirl_right
	for (int i = 0; i < 60; i++) {
		if (level[1].ground[i].getGlobalBounds().intersects(f_w.watergirl_st.watergirl_right.getGlobalBounds()) && Keyboard::isKeyPressed(Keyboard::Key::Right) && level[1].ground[i].getFillColor() == Color::Yellow) {
			WaterGirl.move(-5, 0);
		}
	}

	/////collision watergirl_left

	for (int i = 0; i < 60; i++) {
		if (level[1].ground[i].getGlobalBounds().intersects(f_w.watergirl_st.watergirl_left.getGlobalBounds()) && Keyboard::isKeyPressed(Keyboard::Key::Left) && level[1].ground[i].getFillColor() == Color::Yellow) {
			WaterGirl.move(5, 0);
		}
	}

	//collision convexes
	for (int i = 0; i < 30; i++)
	{


		if (f_w.watergirl_st.watergirl_down.getGlobalBounds().intersects(level[1].convexs[i].getGlobalBounds()) && level[1].convexs[i].getFillColor() == Color::Green) {
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
					cout << "no\n";
				}

				WaterGirl.move(2.0, 2.0);
				cout << "YES\n";
			}
			if (Keyboard::isKeyPressed(Keyboard::Key::Up))
				velocityWaterGirl = 5.5;

		}
		else if (f_w.watergirl_st.watergirl_down.getGlobalBounds().intersects(level[1].convexs[i].getGlobalBounds()) && level[1].convexs[i].getFillColor() == Color::Red)
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
				cout << "no\n";
			}
			if (!f_w.watergirl_st.grounded)
			{
				WaterGirl.move(-2.0, 2.0);
				cout << "YES\n";
			}

			if (Keyboard::isKeyPressed(Keyboard::Key::Up))
				velocityWaterGirl = 5.5;


		}
		if (f_w.watergirl_st.watergirl_top.getGlobalBounds().intersects(level[1].convexs[i].getGlobalBounds()) && level[1].convexs[i].getFillColor() == Color::Black) {

			velocityWaterGirl = -3.5;
		}
	}
	if (f_w.watergirl_st.watergirl_left.getGlobalBounds().intersects(level[1].convexs[2].getGlobalBounds()) && !(f_w.watergirl_st.watergirl_down.getGlobalBounds().intersects(level[1].convexs[2].getGlobalBounds()))) {
		WaterGirl.move(5.2f, 0);
	}
	if (f_w.watergirl_st.watergirl_right.getGlobalBounds().intersects(level[1].convexs[2].getGlobalBounds()) && !(f_w.watergirl_st.watergirl_down.getGlobalBounds().intersects(level[1].convexs[2].getGlobalBounds()))) {
		WaterGirl.move(-5.2f, 0);
	}
}
void collision(RenderWindow& window, bool& isAnimationStandingFireBoy, double& velocityFireBoy, Sprite& FireBoy, bool& isAnimationStandingWaterGirl, double& velocityWaterGirl, Sprite& WaterGirl) {
	collision_fireboy(window, isAnimationStandingFireBoy, velocityFireBoy, FireBoy);
	collision_watergirl(window, isAnimationStandingWaterGirl, velocityWaterGirl, WaterGirl);
}
void Animation(RenderWindow& window) {




	//animation pond fireboy
	level[1].pondFireBoy[1].setTextureRect(IntRect(level[1].animationPond * 160, 0, 160, 21));

	if (level[1].clockPondFireBoy.getElapsedTime().asSeconds() >= 0.15)
	{
		if (level[1].isAnimationLava == 0)
		{
			level[1].animationPond++;
			if (level[1].animationPond == 4)level[1].isAnimationLava = 1;
		}
		else
			level[1].animationPond--;

		if (level[1].animationPond == 0) level[1].isAnimationLava = 0;

		level[1].clockPondFireBoy.restart();
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
			else if(f_w.fireboy_st.velocityFireBoy < 0 )
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
		
			cout << f_w.fireboy_st.velocityFireBoy << "\n";
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



	if (f_w.fireboy_st.firboy_down.getGlobalBounds().intersects(level[1].FireBoy_DoorOpening.getGlobalBounds())) {

		level[1].fireboy_dooropening = 1;
		level[1].FireBoy_DoorOpening.setTextureRect(IntRect(level[1].animationDoorFireBoy * 114, 0, 114, 123));
		if (level[1].animationDoorFireBoy != 21) { level[1].animationDoorFireBoy++; }
	}
	else {
		level[1].fireboy_dooropening = 0;
		level[1].FireBoy_DoorOpening.setTextureRect(IntRect(level[1].animationDoorFireBoy * 114, 0, 114, 123));
		if (level[1].animationDoorFireBoy != 0) { level[1].animationDoorFireBoy--; }

	}
	if (f_w.watergirl_st.watergirl_down.getGlobalBounds().intersects(level[1].WaterGirl_DoorOpening.getGlobalBounds())) {
		level[1].watergirl_dooropening = 1;
		level[1].WaterGirl_DoorOpening.setTextureRect(IntRect(level[1].animationDoorWaterGirl * 114, 0, 114, 122));
		if (level[1].animationDoorWaterGirl != 21) { level[1].animationDoorWaterGirl++; }
	}
	else {
		level[1].watergirl_dooropening = 1;
		level[1].WaterGirl_DoorOpening.setTextureRect(IntRect(level[1].animationDoorWaterGirl * 114, 0, 114, 122));
		if (level[1].animationDoorWaterGirl != 0) { level[1].animationDoorWaterGirl--; }
	}
	if (level[1].animationDoorFireBoy == 21 && level[1].animationDoorWaterGirl == 21) {
		level[1].both_dooropening = 1;
		level[1].FireBoy_DoorMoving.setTextureRect(IntRect(level[1].AnimationBothDoor * 149, 0, 149, 160));
		level[1].WaterGirl_DoorMoving.setTextureRect(IntRect(level[1].AnimationBothDoor * 149, 0, 149, 160));
		f_w.fireboy_st.FireBoy.setScale(0, 0);
		f_w.watergirl_st.WaterGirl.setScale(0, 0);

		if (level[1].AnimationBothDoor != 28) { level[1].AnimationBothDoor++; }
	}
}
void Game_Play(RenderWindow& window)
{
	//levels
	Levels(window);
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
		f_w.fireboy_st.FireBoy.move(0, -f_w.fireboy_st.velocityFireBoy);
		f_w.watergirl_st.WaterGirl.move(0, -f_w.watergirl_st.velocityWaterGirl);
		window.display();
	}
}
void draw(RenderWindow& window, Sprite& FireBoy, Sprite& WaterGirl)
{

	window.draw(level[1].background_levels[1]);
	window.draw(level[1].ground_levels[1]);
	for (int i = 0; i < 60; i++) {
		window.draw(level[1].ground[i]);
	}

	// window.draw(level[1].background_levels[1]);
//     window.draw(level[1].ground_levels[1]);
	window.draw(level[1].pondFireBoy[1]);
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
	window.draw(test2);

}