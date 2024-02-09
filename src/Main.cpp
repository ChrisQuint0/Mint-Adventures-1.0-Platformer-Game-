#include <iostream>
#include <thread>
#include <chrono>
#include <sstream>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>



int maxHealth = 3;
int currentHealth = maxHealth;

void drawHealthBar(sf::RenderWindow& window, sf::Texture& filledHeartTexture, sf::Texture& emptyHeartTexture)
{
	for (int i = 0; i < maxHealth; ++i) {
		sf::Sprite heartSprite;
		heartSprite.setTexture((i < currentHealth) ? filledHeartTexture : emptyHeartTexture);
		heartSprite.setPosition(i * filledHeartTexture.getSize().x * 3.f, 0);
		heartSprite.setScale(3.f, 3.f);
		window.draw(heartSprite);
	}
}

void updateHealth(int newHealth)
{
	currentHealth = std::max(0, std::min(maxHealth, newHealth));
}

int main()
{
	sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();

	sf::RenderWindow window(desktopMode, "Mint Adventures", sf::Style::Close);
	window.setFramerateLimit(60);
	
	//Player Physics
	float gravity = 0.5f;
	float playerVelocityX = 0.f;
	float playerVelocityY = 0.f;
	float jumpVelocity = -10.f;
	float jumpCount = 0;
	int maxJump = 2;


	//Player Booleans
	bool isJumping = false;
	bool isMoving = false;
	bool movingLeft = false;
	bool movingRight = false;

	//Player's Switch Frame and Frame Count
	int frameCount = 0;
	int switchFrame(8);

	//Enemy Frame Count
	int enemyFrameCount = 0;
	int enemyFrameCount2 = 0;
	int enemyFrameCount3 = 0;
	int enemyFrameCount4 = 0;
	int enemyFrameCount5 = 0;

	//Flying Enemy Frame Count
	int fenemyFrameCount = 0;
	int fenemyFrameCount2 = 0;
	int fenemyFrameCount3 = 0;
	int fenemyFrameCount4 = 0;
	int fenemyFrameCount5 = 0;

	//Red Enemy Frame Count
	int rEnemyFrameCount = 0;
	int rEnemyFrameCount2 = 0;
	int rEnemyFrameCount3 = 0;
	int rEnemyFrameCount4 = 0;
	int rEnemyFrameCount5 = 0;
	int rEnemyFrameCount6 = 0;

	//Blue Enemy Switch Frame
	int enemySwitchFrame(8);
	int enemySwitchFrame2(8);
	int enemySwitchFrame3(8);
	int enemySwitchFrame4(8);
	int enemySwitchFrame5(8);

	//Flying Enemy Switch Frame
	int fenemySwitchFrame(10);
	int fenemySwitchFrame2(8);
	int fenemySwitchFrame3(8);
	int fenemySwitchFrame4(8);
	int fenemySwitchFrame5(8);

	//Red Enemy Switch Frame
	int rEnemySwitchFrame(8);
	int rEnemySwitchFrame2(8);
	int rEnemySwitchFrame3(8);
	int rEnemySwitchFrame4(8);
	int rEnemySwitchFrame5(8);
	int rEnemySwitchFrame6(8);

	//COIN FRAME COUNT
	int coin1FrameCount = 0;
	int coin2FrameCount = 0;
	int coin3FrameCount = 0;

	//COIN SWITCH FRAMES
	int coin1SwitchFrame(15);
	int coin2SwitchFrame(15);
	int coin3SwitchFrame(15);

	//Jump Sound
	sf::SoundBuffer jumpBuffer;
	jumpBuffer.loadFromFile("Audio/jump.wav");
	sf::Sound jumpSound;
	jumpSound.setBuffer(jumpBuffer);

	//COIN SOUND
	sf::SoundBuffer coinBuffer;
	coinBuffer.loadFromFile("Audio/coin.mp3");
	sf::Sound coinSound;
	coinSound.setBuffer(coinBuffer);

	//DOOR UNLOCK
	sf::SoundBuffer doorBuffer;
	doorBuffer.loadFromFile("Audio/doorUnlock.wav");
	sf::Sound doorSound;
	doorSound.setBuffer(doorBuffer);

	//KEY COLLECT
	sf::SoundBuffer keyBuffer;
	keyBuffer.loadFromFile("Audio/keyCollect.mp3");
	sf::Sound keySound;
	keySound.setBuffer(keyBuffer);

	//VICTORY SOUND
	sf::SoundBuffer vicBuffer;
	vicBuffer.loadFromFile("Audio/victory.mp3");
	sf::Sound victorySound;
	victorySound.setBuffer(vicBuffer);

	//BACKGROUND MUSIC
	

	//Player Texture
	sf::Texture playerTexture;
	playerTexture.loadFromFile("Textures/playerMovementSheet.png");
	sf::Sprite player;
	player.setTexture(playerTexture);
	player.setTextureRect(sf::IntRect(0, 0, 24, 24));
	player.setOrigin(12.f, 12.f);
	player.setScale(2.f, 2.f);
	
	//----------------------------------------------------------------------------------------------------------------
	//MENU
	int currentLevel = 0;
	bool menuActive = true;

	//Heart Textures
	sf::Texture filledHeartTexture;
	filledHeartTexture.loadFromFile("Textures/heart.png");

	sf::Texture emptyHeartTexture;
	emptyHeartTexture.loadFromFile("Textures/heartEmpty.png");

	//Spike
	sf::Texture spikeTex1, spikeTex2, spikeTex3, spikeTex4;
	sf::Sprite spike1, spike2, spike3, spike4, spike5, spike6, spike7, spike8, spike9, spike10;
	spikeTex1.loadFromFile("Textures/Level 1/spike.png");
	spikeTex2.loadFromFile("Textures/Level 1/1 - DoubleSpike.png");
	spikeTex3.loadFromFile("Textures/Level 1/1 - SpikeSidewards.png");
	spikeTex4.loadFromFile("Textures/Level 1/1 - SpikeUpsideDown.png");

	spike1.setTexture(spikeTex1);
	spike2.setTexture(spikeTex2);
	spike3.setTexture(spikeTex3);
	spike4.setTexture(spikeTex1);
	spike5.setTexture(spikeTex1);
	spike6.setTexture(spikeTex4);
	spike7.setTexture(spikeTex4);
	spike8.setTexture(spikeTex4);
	spike9.setTexture(spikeTex4);
	spike10.setTexture(spikeTex4);

	spike1.setPosition(282, 989);
	spike1.setScale(3.f, 3.f);
	spike2.setPosition(622, 1015);
	spike3.setPosition(1200, 830);
	spike4.setPosition(1230, 770);
	spike4.setScale(3.f, 3.f);
	spike5.setPosition(193, 232);
	spike5.setScale(3.f, 3.f);
	spike6.setPosition(575, 31);
	spike7.setPosition(788, 32);
	spike8.setPosition(1012, 33);
	spike9.setPosition(1191, 33);
	spike10.setPosition(1367, 31);

	//Stab Audio
	sf::SoundBuffer spikeStab;
	spikeStab.loadFromFile("Audio/spike.wav");
	sf::Sound spikeStabSound;
	spikeStabSound.setBuffer(spikeStab);

	//SPRING
	sf::Texture spring1Tex, spring2Tex;
	sf::Sprite spring1, spring2;

	spring1Tex.loadFromFile("Textures/springTileSheet.png");
	spring2Tex.loadFromFile("Textures/springTileSheet.png");

	spring1.setTexture(spring1Tex);
	spring2.setTexture(spring2Tex);

	spring1.setTextureRect(sf::IntRect(0, 0, 18, 14));
	spring2.setTextureRect(sf::IntRect(0, 0, 18, 14));

	spring1.setScale(2.f, 2.f);
	spring2.setScale(2.f, 2.f);

	spring1.setPosition(1877, 798);
	spring2.setPosition(7, 419);

	//COINS
	sf::Texture coin1Tex, coin2Tex, coin3Tex;
	sf::Sprite coin1, coin2, coin3;

	coin1Tex.loadFromFile("Textures/coin.png");
	coin2Tex.loadFromFile("Textures/coin.png");
	coin3Tex.loadFromFile("Textures/coin.png");

	coin1.setTexture(coin1Tex);
	coin2.setTexture(coin2Tex);
	coin3.setTexture(coin3Tex);

	coin1.setScale(2.f, 2.f);
	coin2.setScale(2.f, 2.f);
	coin3.setScale(2.f, 2.f);

	coin1.setTextureRect(sf::IntRect(0, 0, 12, 12));
	coin2.setTextureRect(sf::IntRect(0, 0, 12, 12));
	coin3.setTextureRect(sf::IntRect(0, 0, 12, 12));

	coin1.setPosition(1195, 1015);
	coin2.setPosition(1890, 438);
	coin3.setPosition(696, 39);

	//KEY
	sf::Texture keyTex;
	sf::Sprite key;
	
	keyTex.loadFromFile("Textures/key.png");

	key.setTexture(keyTex);

	key.setPosition(243, 92);


	//Clock
	sf::Clock damageCooldown;
	const sf::Time coolDownDuration = sf::seconds(3.0f);

	sf::Clock blinkingTimer;
	const sf::Time blinkingTimerDuration = sf::seconds(3.0f);

	//------------------------------------------------------------------------------------------------------
	//Level 1
	//Snow Platforms
	sf::Texture snowBgTex, snowPTex1, snowPTex2, snowPTex3, snowPTex4;
	sf::Sprite snowBg, snowP1, snowP2, snowP3, snowP4;

	snowBgTex.loadFromFile("Textures/Level 1/whiteBg.png");
	snowPTex1.loadFromFile("Textures/Level 1/1 - SnowChunk Left.png");
	snowPTex2.loadFromFile("Textures/Level 1/1 - SnowWide.png");
	snowPTex3.loadFromFile("Textures/Level 1/1 - SnowWide.png");
	snowPTex4.loadFromFile("Textures/Level 1/1 - SnowChunk Right.png");

	snowBg.setTexture(snowBgTex);
	snowP1.setTexture(snowPTex1);
	snowP2.setTexture(snowPTex2);
	snowP3.setTexture(snowPTex3);
	snowP4.setTexture(snowPTex4);

	snowP1.setPosition(0.f, 865.f);
	snowP2.setPosition(276.f, 1041.f);
	snowP3.setPosition(589.f, 1041.f);
	snowP4.setPosition(1222, 825);

	//Metal Platforms
	sf::Texture dMetalPTex, sMetalPTex;
	sf::Sprite dMetalP1, dMetalP2, sMetalP;

	dMetalPTex.loadFromFile("Textures/Level 1/1 - MetalPlat2.png");
	sMetalPTex.loadFromFile("Textures/Level 1/1 - MetalPlat1.png");

	dMetalP1.setTexture(dMetalPTex);
	dMetalP2.setTexture(dMetalPTex);
	sMetalP.setTexture(sMetalPTex);

	dMetalP1.setPosition(996.f, 930.f);
	dMetalP2.setPosition(830, 850);
	sMetalP.setPosition(1050, 750);

	//Chiseled Platforms
	sf::Texture chisTex1, chisTex2, chisTex3, chisTex4, chisTex5, chisTex6;
	sf::Sprite chis1, chis2, chis3, chis4, chis5, chis6, chis7, chis8, chis9;

	chisTex1.loadFromFile("Textures/Level 1/1 - ChiseledPlatTrio.png");
	chisTex2.loadFromFile("Textures/Level 1/1 - ChiseledPlatTrioCut.png");
	chisTex3.loadFromFile("Textures/Level 1/1 - ChiseledPlatTR.png");
	chisTex4.loadFromFile("Textures/Level 1/1 - ChiseledPlatCeil.png");
	chisTex5.loadFromFile("Textures/Level 1/1 - ChiseledPlatCeil2.png");
	chisTex6.loadFromFile("Textures/Level 1/1 - ChiseledPlatCeilEnd.png");

	chis1.setTexture(chisTex1);
	chis2.setTexture(chisTex2);
	chis3.setTexture(chisTex1);
	chis4.setTexture(chisTex3);
	chis5.setTexture(chisTex4);
	chis6.setTexture(chisTex5);
	chis7.setTexture(chisTex5);
	chis8.setTexture(chisTex5);
	chis9.setTexture(chisTex6);

	chis1.setPosition(1566, 575);
	chis2.setPosition(1668, 463);
	chis3.setPosition(100, 280);
	chis4.setPosition(0, 137);
	chis5.setPosition(398, 0);
	chis6.setPosition(427, 0);
	chis7.setPosition(705, 0);
	chis8.setPosition(983, 0);
	chis9.setPosition(1256, 0);

	//Clouds
	sf::Texture cloudTex, smallCloudTex;
	sf::Sprite cloud1, cloud2, cloud3, cloud4, cloud5, cloud6, cloud7, cloud8, cloud9, cloud10, cloud11, cloud12, coinCloud, keyCloud, sCloud1, sCloud2;

	cloudTex.loadFromFile("Textures/Level 1/1 - CloudWide.png");
	smallCloudTex.loadFromFile("Textures/Level 1/1 - CloudSmall.png");

	cloud1.setTexture(cloudTex);
	cloud2.setTexture(cloudTex);
	cloud3.setTexture(cloudTex);
	cloud4.setTexture(cloudTex);
	cloud5.setTexture(cloudTex);
	cloud6.setTexture(cloudTex);
	cloud7.setTexture(cloudTex);
	cloud8.setTexture(cloudTex);
	cloud9.setTexture(cloudTex);
	cloud10.setTexture(cloudTex);
	cloud11.setTexture(cloudTex);
	cloud12.setTexture(cloudTex);
	coinCloud.setTexture(cloudTex);
	keyCloud.setTexture(cloudTex);
	sCloud1.setTexture(smallCloudTex);
	sCloud2.setTexture(smallCloudTex);

	cloud1.setPosition(1277, 464);
	cloud2.setPosition(952, 487);
	cloud3.setPosition(775, 470);
	cloud4.setPosition(622, 509);
	cloud5.setPosition(384, 483);
	cloud6.setPosition(204, 492);
	cloud7.setPosition(2, 446);
	cloud8.setPosition(521, 224);
	cloud9.setPosition(739, 204);
	cloud10.setPosition(958, 213);
	cloud11.setPosition(1143, 186);
	cloud12.setPosition(1315, 247);

	coinCloud.setPosition(1781, 269);
	keyCloud.setPosition(1773, 123);

	sCloud1.setPosition(470, 713);
	sCloud2.setPosition(1651, 216);

	//Door
	sf::Texture normalD, coinD, keyD;
	sf::Sprite norDoor, coinDoor, keyDoor;

	normalD.loadFromFile("Textures/Level 1/1 - Door.png");
	coinD.loadFromFile("Textures/Level 1/1 - coinDoor.png");
	keyD.loadFromFile("Textures/Level 1/1 - KeyDoor.png");

	norDoor.setTexture(normalD);
	coinDoor.setTexture(coinD);
	keyDoor.setTexture(keyD);

	norDoor.setPosition(324, 45);
	coinDoor.setPosition(1813, 177);
	keyDoor.setPosition(1811, 31);

	//Snowman
	sf::Texture snowManTex;
	sf::Sprite snowMan;

	snowManTex.loadFromFile("Textures/Level 1/1- Snowman.png");
	snowMan.setTexture(snowManTex);
	snowMan.setPosition(465, 661);
	
	//COIN CHECK
	int coins = 0;

	//-------------------------------------------------------------------------------------------------------------
	//Enemy
	sf::SoundBuffer stompBuffer;
	stompBuffer.loadFromFile("Audio/splat.mp3");
	sf::Sound stompSound;
	stompSound.setBuffer(stompBuffer);

	//BLUE ENEMY SPEED
	float enemySpeed = 1.0f;
	float enemySpeed2 = 1.0f;
	float enemySpeed3 = 1.0f;
	float enemySpeed4 = 1.0f;
	float enemySpeed5 = 1.0f;

	//FLYING ENEMY SPEED
	float fenemySpeed = 1.0f;
	float fenemySpeed2 = 1.0f;
	float fenemySpeed3 = 1.0f;
	float fenemySpeed4 = 1.0f;
	float fenemySpeed5 = 1.0f;

	//RED ENEMY SPEED
	float rEnemySpeed = 1.0f;
	float rEnemySpeed2 = 1.0f;
	float rEnemySpeed3 = 1.0f;
	float rEnemySpeed4 = 1.0f;
	float rEnemySpeed5 = 1.0f;
	float rEnemySpeed6 = 1.0f;

	//FLYING ENEMY DIRECTION
	float fenemyDirection = 1.0f;
	float fenemyDirection2 = -1.0f;
	float fenemyDirection3 = -1.0f;
	float fenemyDirection4 = -1.0f;
	float fenemyDirection5 = -1.0f;

	//BLUE ENEMY DIRECTION
	float enemyDirection = 1.0f;
	float enemyDirection2 = -1.0f;
	float enemyDirection3 = -1.0f;
	float enemyDirection4 = -1.0f;
	float enemyDirection5 = -1.0f;

	//RED ENEMY DIRECTION
	float rEnemyDirection = -1.0f;
	float rEnemyDirection2 = -1.0f;
	float rEnemyDirection3 = -1.0f;
	float rEnemyDirection4 = -1.0f;
	float rEnemyDirection5 = -1.0f;
	float rEnemyDirection6 = -1.0f;
	
	//BLUE ENEMY BOUNDS
	float leftBound = dMetalP1.getGlobalBounds().left;
	float rightBound = dMetalP1.getPosition().x + dMetalP1.getGlobalBounds().width;

	float e2LeftBound = dMetalP2.getGlobalBounds().left;
	float e2RightBound = dMetalP2.getPosition().x + dMetalP2.getGlobalBounds().width;

	float e3LeftBound = cloud9.getGlobalBounds().left;
	float e3RightBound = cloud9.getPosition().x + cloud9.getGlobalBounds().width;

	float e4LeftBound = cloud10.getGlobalBounds().left;
	float e4RightBound = cloud10.getPosition().x + cloud10.getGlobalBounds().width;

	float e5LeftBound = sCloud2.getGlobalBounds().left;
	float e5RightBound = sCloud2.getPosition().x + sCloud2.getGlobalBounds().width;

	//FLYING ENEMY BOUNDS
	float fleftBound = chis1.getGlobalBounds().left;
	float frightBound = chis2.getPosition().x + chis2.getGlobalBounds().width;

	float f2LeftBound = cloud4.getGlobalBounds().left;
	float f2RightBound = cloud1.getPosition().x + cloud1.getGlobalBounds().width;

	float f3LeftBound = cloud7.getGlobalBounds().left;
	float f3RightBound = cloud5.getPosition().x + cloud5.getGlobalBounds().width;

	float f4LeftBound = cloud8.getGlobalBounds().left;
	float f4RightBound = cloud9.getPosition().x + cloud9.getGlobalBounds().width;

	float f5LeftBound = cloud10.getGlobalBounds().left;
	float f5RightBound = cloud12.getPosition().x + cloud12.getGlobalBounds().width;

	//RED ENEMY BOUNDS
	float rLeftBound = cloud1.getGlobalBounds().left;
	float rRightBound = cloud1.getPosition().x + cloud1.getGlobalBounds().width;

	float r2LeftBound = cloud2.getGlobalBounds().left;
	float r2RightBound = cloud2.getPosition().x + cloud2.getGlobalBounds().width;

	float r3LeftBound = cloud3.getGlobalBounds().left;
	float r3RightBound = cloud3.getPosition().x + cloud3.getGlobalBounds().width;

	float r4LeftBound = cloud4.getGlobalBounds().left;
	float r4RightBound = cloud4.getPosition().x + cloud4.getGlobalBounds().width;

	float r5LeftBound = cloud6.getGlobalBounds().left;
	float r5RightBound = cloud6.getPosition().x + cloud6.getGlobalBounds().width;

	float r6LeftBound = cloud12.getGlobalBounds().left;
	float r6RightBound = cloud12.getPosition().x + cloud12.getGlobalBounds().width;

	//----------------------------------------------------------------------------------
	//SQUISH BOOLEANS

	//BLUE ENEMY
	bool isSquished = false;
	sf::Clock squishTimer;
	sf::Time squishDuration = sf::seconds(0.5f);

	bool isSquished2 = false;
	sf::Clock squishTimer2;
	sf::Time squishDuration2 = sf::seconds(0.5f);

	bool isSquished3 = false;
	sf::Clock squishTimer3;
	sf::Time squishDuration3 = sf::seconds(0.5f);

	bool isSquished4 = false;
	sf::Clock squishTimer4;
	sf::Time squishDuration4 = sf::seconds(0.5f);

	bool isSquished5 = false;
	sf::Clock squishTimer5;
	sf::Time squishDuration5 = sf::seconds(0.5f);

	//FLYING ENEMY
	bool fisSquished = false;
	sf::Clock fsquishTimer;
	sf::Time fsquishDuration = sf::seconds(0.5f);

	bool f2isSquished = false;
	sf::Clock f2squishTimer;
	sf::Time f2squishDuration = sf::seconds(0.5f);

	bool f3isSquished = false;
	sf::Clock f3squishTimer;
	sf::Time f3squishDuration = sf::seconds(0.5f);

	bool f4isSquished = false;
	sf::Clock f4squishTimer;
	sf::Time f4squishDuration = sf::seconds(0.5f);

	bool f5isSquished = false;
	sf::Clock f5squishTimer;
	sf::Time f5squishDuration = sf::seconds(0.5f);

	//COLLISION BOOLEANS
	bool hasCollidedWithLeftSide = false;
	bool hasCollidedWithRightSide = false;
	bool hasCollidedWithBottom = false;
	bool hasCollidedWithTop = false;

	//SPRING BOOLEANS
	bool isSpringActivated = false;

	//KEY BOOLEANS
	bool completedCoins = false;
	bool hasKey = false;


	//---------------------------------------------------------------------------------------------------------------------------------------
	//ENEMY BLUE TEXTURES

	sf::Texture enemyBlueTexture, enemyBlueTexture2, enemyBlueTexture3, enemyBlueTexture4, enemyBlueTexture5;

	enemyBlueTexture.loadFromFile("Textures/enemyBlue.png");
	enemyBlueTexture2.loadFromFile("Textures/enemyBlue.png");
	enemyBlueTexture3.loadFromFile("Textures/enemyBlue.png");
	enemyBlueTexture4.loadFromFile("Textures/enemyBlue.png");
	enemyBlueTexture5.loadFromFile("Textures/enemyBlue.png");

	sf::Sprite enemyBlue, enemyBlue2, enemyBlue3, enemyBlue4, enemyBlue5;
	enemyBlue.setTexture(enemyBlueTexture);
	enemyBlue2.setTexture(enemyBlueTexture2);
	enemyBlue3.setTexture(enemyBlueTexture3);
	enemyBlue4.setTexture(enemyBlueTexture4);
	enemyBlue5.setTexture(enemyBlueTexture5);

	enemyBlue.setTextureRect(sf::IntRect(0.f, 0.f, 15.f, 14.f));
	enemyBlue2.setTextureRect(sf::IntRect(0.f, 0.f, 15.f, 14.f));
	enemyBlue3.setTextureRect(sf::IntRect(0.f, 0.f, 15.f, 14.f));
	enemyBlue4.setTextureRect(sf::IntRect(0.f, 0.f, 15.f, 14.f));
	enemyBlue5.setTextureRect(sf::IntRect(0.f, 0.f, 15.f, 14.f));

	enemyBlue.setOrigin(12.f, 12.f);
	enemyBlue2.setOrigin(12.f, 12.f);
	enemyBlue3.setOrigin(12.f, 12.f);
	enemyBlue4.setOrigin(12.f, 12.f);
	enemyBlue5.setOrigin(12.f, 12.f);

	enemyBlue.setPosition(dMetalP1.getPosition().y + 50.f, dMetalP1.getPosition().y - 5.f);
	enemyBlue2.setPosition(dMetalP2.getPosition().y, dMetalP2.getPosition().y - 5.f);
	enemyBlue3.setPosition(cloud9.getPosition().x, cloud9.getPosition().y - 5.f);
	enemyBlue4.setPosition(cloud10.getPosition().x, cloud10.getPosition().y - 5.f);
	enemyBlue5.setPosition(sCloud2.getPosition().x, sCloud2.getPosition().y - 5.f);

	enemyBlue.setScale(2.f, 2.f);
	enemyBlue2.setScale(2.f, 2.f);
	enemyBlue3.setScale(2.f, 2.f);
	enemyBlue4.setScale(2.f, 2.f);
	enemyBlue5.setScale(2.f, 2.f);

	//---------------------------------------------------------------------------------------------------------------------------------------------
	//FLYING ENEMY TEXTURES
	sf::Texture fEnemyTex, fEnemyTex2, fEnemyTex3, fEnemyTex4, fEnemyTex5;
	sf::Sprite fEnemy, fEnemy2, fEnemy3, fEnemy4, fEnemy5;

	fEnemyTex.loadFromFile("Textures/flyingEnemy.png");
	fEnemyTex2.loadFromFile("Textures/flyingEnemy.png");
	fEnemyTex3.loadFromFile("Textures/flyingEnemy.png");
	fEnemyTex4.loadFromFile("Textures/flyingEnemy.png");
	fEnemyTex5.loadFromFile("Textures/flyingEnemy.png");
	
	fEnemy.setTexture(fEnemyTex);
	fEnemy2.setTexture(fEnemyTex2);
	fEnemy3.setTexture(fEnemyTex3);
	fEnemy4.setTexture(fEnemyTex4);
	fEnemy5.setTexture(fEnemyTex5);

	fEnemy.setTextureRect(sf::IntRect(0, 0, 18, 17));
	fEnemy2.setTextureRect(sf::IntRect(0, 0, 18, 17));
	fEnemy3.setTextureRect(sf::IntRect(0, 0, 18, 17));
	fEnemy4.setTextureRect(sf::IntRect(0, 0, 18, 17));
	fEnemy5.setTextureRect(sf::IntRect(0, 0, 18, 17));

	fEnemy.setOrigin(12.f, 12.f);
	fEnemy2.setOrigin(12.f, 12.f);
	fEnemy3.setOrigin(12.f, 12.f);
	fEnemy4.setOrigin(12.f, 12.f);
	fEnemy5.setOrigin(12.f, 12.f);

	fEnemy.setPosition(1904,352);
	fEnemy2.setPosition(1396, 366);
	fEnemy3.setPosition(511, 372);
	fEnemy4.setPosition(516, 115);
	fEnemy5.setPosition(966, 97);

	fEnemy.setScale(2.f, 2.f);
	fEnemy2.setScale(2.f, 2.f);
	fEnemy3.setScale(2.f, 2.f);
	fEnemy4.setScale(2.f, 2.f);
	fEnemy5.setScale(2.f, 2.f);

	//--------------------------------------------------------------------------------------------------------------------------
	//RED SPIKE ENEMY TEXTURES
	sf::Texture rEnemyTex, rEnemyTex2, rEnemyTex3, rEnemyTex4, rEnemyTex5, rEnemyTex6;
	sf::Sprite rEnemy, rEnemy2, rEnemy3, rEnemy4, rEnemy5, rEnemy6;

	rEnemyTex.loadFromFile("Textures/enemyRed.png");
	rEnemyTex2.loadFromFile("Textures/enemyRed.png");
	rEnemyTex3.loadFromFile("Textures/enemyRed.png");
	rEnemyTex4.loadFromFile("Textures/enemyRed.png");
	rEnemyTex5.loadFromFile("Textures/enemyRed.png");
	rEnemyTex6.loadFromFile("Textures/enemyRed.png");

	rEnemy.setTexture(rEnemyTex);
	rEnemy2.setTexture(rEnemyTex2);
	rEnemy3.setTexture(rEnemyTex3);
	rEnemy4.setTexture(rEnemyTex4);
	rEnemy5.setTexture(rEnemyTex5);
	rEnemy6.setTexture(rEnemyTex6);

	rEnemy.setTextureRect(sf::IntRect(0.f, 0.f, 15.f, 19.f));
	rEnemy2.setTextureRect(sf::IntRect(0.f, 0.f, 15.f, 19.f));
	rEnemy3.setTextureRect(sf::IntRect(0.f, 0.f, 15.f, 19.f));
	rEnemy4.setTextureRect(sf::IntRect(0.f, 0.f, 15.f, 19.f));
	rEnemy5.setTextureRect(sf::IntRect(0.f, 0.f, 15.f, 19.f));
	rEnemy6.setTextureRect(sf::IntRect(0.f, 0.f, 15.f, 19.f));

	rEnemy.setOrigin(12.f, 12.f);
	rEnemy2.setOrigin(12.f, 12.f);
	rEnemy3.setOrigin(12.f, 12.f);
	rEnemy4.setOrigin(12.f, 12.f);
	rEnemy5.setOrigin(12.f, 12.f);
	rEnemy6.setOrigin(12.f, 12.f);

	rEnemy.setPosition(1413, 450);
	rEnemy2.setPosition(963, 472);
	rEnemy3.setPosition(908, 456);
	rEnemy4.setPosition(754, 498);
	rEnemy5.setPosition(331, 476);
	rEnemy6.setPosition(1450, 234);

	rEnemy.setScale(2.f, 2.f);
	rEnemy2.setScale(2.f, 2.f);
	rEnemy3.setScale(2.f, 2.f);
	rEnemy4.setScale(2.f, 2.f);
	rEnemy5.setScale(2.f, 2.f);
	rEnemy6.setScale(2.f, 2.f);
	
	

	//-------------------------------------------------------HOME LEVEL----------------------------------------------------------------//
	//---------------------------------------------------BACKGROUND------------------------------------------------------------//
	sf::Texture homeLevelBgTex;
	sf::Sprite homeLevelBg;
	homeLevelBgTex.loadFromFile("Textures/homeLevel/homeLevelBg.png");
	homeLevelBg.setTexture(homeLevelBgTex);

	//---------------------------------------------------TEXT-----------------------------------------------------------------//
	sf::Font leagueSpartan;
	leagueSpartan.loadFromFile("Fonts/LeagueSpartan-Bold.ttf");

	sf::Text text1("LEFT", leagueSpartan, 30);
	text1.setPosition(110, 742);
	text1.setFillColor(sf::Color::Black);

	sf::Text text2("RIGHT", leagueSpartan, 30);
	text2.setPosition(129, 799);
	text2.setFillColor(sf::Color::Black);

	sf::Text text3("DOUBLE JUMP", leagueSpartan, 30);
	text3.setPosition(471, 747);
	text3.setFillColor(sf::Color::Black);

	sf::Text text4("COLLECT ALL THE COINS", leagueSpartan, 30);
	text4.setPosition(715, 735);
	text4.setFillColor(sf::Color::Black);

	sf::Text text5("TO UNLOCK THE COIN DOOR", leagueSpartan, 30);
	text5.setPosition(693, 710);
	text5.setFillColor(sf::Color::Black);

	sf::Text text6("COLLECT THE KEY", leagueSpartan, 30);
	text6.setPosition(1068, 808);
	text6.setFillColor(sf::Color::Black);

	sf::Text text7("TO UNLOCK THE KEY DOOR", leagueSpartan, 30);
	text7.setPosition(1013, 783);
	text7.setFillColor(sf::Color::Black);

	sf::Text text8("Where are your friends?", leagueSpartan, 14);
	text8.setPosition(734, 878);
	text8.setFillColor(sf::Color::Black);

	sf::Text text9("It's starting", leagueSpartan, 15);
	text9.setPosition(932, 877);
	text9.setFillColor(sf::Color::Black);

	sf::Text text10("You better find them", leagueSpartan, 15);
	text10.setPosition(933, 877);
	text10.setFillColor(sf::Color::Black);


	sf::Text text11("JUMP", leagueSpartan, 30);
	text11.setPosition(290, 806);
	text11.setFillColor(sf::Color::Black);

	sf::Text text12("+", leagueSpartan, 30);
	text12.setPosition(367, 758);
	text12.setFillColor(sf::Color::Black);


	//------------------------------------------------------------------SPRITES AND TEXTURES--------------------------------------------//
	sf::Texture aKeyTexh, dkeyTexh, wKeyTexh, wKeyTex2h, coinTexh, keyTexh, dialogueTex1h, dialogueTex2h, snowmanTex1h, snowmanTex2h, spring1Texh, spring2Texh, spring3Texh, spring4Texh, num1Texh, num2Texh, num3Texh, num4Texh, cloud1Texh, cloud2Texh, cloud3Texh, cloud4Texh, door1Texh, door2Texh, door3Texh, door4Texh, doorNum1Texh, doorNum2Texh, doorNum3Texh, doorNum4Texh;

	sf::Sprite aKeyh, dKeyh, wKeyh1, wKeyh2, coinh, keyh, dialogue1h, dialogue2h, snowman1h, snowman2h, spring1h, spring2h, spring3h, spring4h, num1h, num2h, num3h, num4h, cloud1h, cloud2h, cloud3h, cloud4h, door1h, door2h, door3h, door4h, doorNum1h, doorNum2h, doorNum3h, doorNum4h;

	aKeyTexh.loadFromFile("Textures/homeLevel/a.png");
	dkeyTexh.loadFromFile("Textures/homeLevel/d.png");
	wKeyTexh.loadFromFile("Textures/homeLevel/w.png");
	wKeyTex2h.loadFromFile("Textures/homeLevel/w.png");
	coinTexh.loadFromFile("Textures/homeLevel/coin.png");
	keyTexh.loadFromFile("Textures/homeLevel/key.png");
	dialogueTex1h.loadFromFile("Textures/homeLevel/dialogue.png");
	dialogueTex2h.loadFromFile("Textures/homeLevel/dialogue.png");
	snowmanTex1h.loadFromFile("Textures/homeLevel/snowman.png");
	snowmanTex2h.loadFromFile("Textures/homeLevel/snowman.png");
	spring1Texh.loadFromFile("Textures/homeLevel/springTileSheet.png");
	spring2Texh.loadFromFile("Textures/homeLevel/springTileSheet.png");
	spring3Texh.loadFromFile("Textures/homeLevel/springTileSheet.png");
	spring4Texh.loadFromFile("Textures/homeLevel/springTileSheet.png");
	num1Texh.loadFromFile("Textures/homeLevel/1.png");
	num2Texh.loadFromFile("Textures/homeLevel/2.png");
	num3Texh.loadFromFile("Textures/homeLevel/3.png");
	num4Texh.loadFromFile("Textures/homeLevel/4.png");
	cloud1Texh.loadFromFile("Textures/homeLevel/cloud.png");
	cloud2Texh.loadFromFile("Textures/homeLevel/cloud.png");
	cloud3Texh.loadFromFile("Textures/homeLevel/cloud.png");
	cloud4Texh.loadFromFile("Textures/homeLevel/cloud.png");
	door1Texh.loadFromFile("Textures/homeLevel/door.png");
	door2Texh.loadFromFile("Textures/homeLevel/door.png");
	door3Texh.loadFromFile("Textures/homeLevel/door.png");
	door4Texh.loadFromFile("Textures/homeLevel/door.png");
	doorNum1Texh.loadFromFile("Textures/homeLevel/1.png");
	doorNum2Texh.loadFromFile("Textures/homeLevel/2.png");
	doorNum3Texh.loadFromFile("Textures/homeLevel/3.png");
	doorNum4Texh.loadFromFile("Textures/homeLevel/4.png");

	//SPRITES

	aKeyh.setTexture(aKeyTexh);
	dKeyh.setTexture(dkeyTexh);
	wKeyh1.setTexture(wKeyTexh);
	wKeyh2.setTexture(wKeyTex2h);
	coinh.setTexture(coinTexh);
	keyh.setTexture(keyTexh);
	dialogue1h.setTexture(dialogueTex1h);
	dialogue2h.setTexture(dialogueTex2h);
	snowman1h.setTexture(snowmanTex1h);
	snowman2h.setTexture(snowmanTex2h);
	spring1h.setTexture(spring1Texh);
	spring2h.setTexture(spring2Texh);
	spring3h.setTexture(spring3Texh);
	spring4h.setTexture(spring4Texh);
	num1h.setTexture(num1Texh);
	num2h.setTexture(num2Texh);
	num3h.setTexture(num3Texh);
	num4h.setTexture(num4Texh);
	cloud1h.setTexture(cloud1Texh);
	cloud2h.setTexture(cloud2Texh);
	cloud3h.setTexture(cloud3Texh);
	cloud4h.setTexture(cloud4Texh);
	door1h.setTexture(door1Texh);
	door2h.setTexture(door2Texh);
	door3h.setTexture(door3Texh);
	door4h.setTexture(door4Texh);
	doorNum1h.setTexture(doorNum1Texh);
	doorNum2h.setTexture(doorNum2Texh);
	doorNum3h.setTexture(doorNum3Texh);
	doorNum4h.setTexture(doorNum4Texh);

	spring1h.setTextureRect(sf::IntRect(0, 0, 18, 14));
	spring2h.setTextureRect(sf::IntRect(0, 0, 18, 14));
	spring3h.setTextureRect(sf::IntRect(0, 0, 18, 14));
	spring4h.setTextureRect(sf::IntRect(0, 0, 18, 14));


	//Sprite Positions
	aKeyh.setPosition(170, 726);
	dKeyh.setPosition(61, 786);
	wKeyh1.setPosition(293, 735);
	wKeyh2.setPosition(400, 732);
	coinh.setPosition(875, 778);
	keyh.setPosition(1174, 760);
	dialogue1h.setPosition(724, 868);
	dialogue2h.setPosition(918, 868);
	snowman1h.setPosition(809, 942);
	snowman2h.setPosition(1029, 942);
	spring1h.setPosition(1311, 964);
	spring2h.setPosition(1489, 964);
	spring3h.setPosition(1642, 965);
	spring4h.setPosition(1867, 961);
	num1h.setPosition(1323, 943);
	num2h.setPosition(1499, 943);
	num3h.setPosition(1655, 943);
	num4h.setPosition(1876, 939);
	cloud1h.setPosition(1304, 705);
	cloud2h.setPosition(1471, 482);
	cloud3h.setPosition(1634, 312);
	cloud4h.setPosition(1776, 123);
	door1h.setPosition(1393, 637);
	door2h.setPosition(1559, 413);
	door3h.setPosition(1727, 244);
	door4h.setPosition(1803, 55);
	doorNum1h.setPosition(1390, 580);
	doorNum2h.setPosition(1557, 372);
	doorNum3h.setPosition(1723, 199);
	doorNum4h.setPosition(1869, 17);

	//Set Scale
	dialogue1h.setScale(0.5, 0.5);
	dialogue2h.setScale(0.5, 0.5);
	snowman1h.setScale(3, 3);
	snowman2h.setScale(3, 3);
	coinh.setScale(2, 2);
	keyh.setScale(2, 2);
	spring1h.setScale(2, 2);
	spring2h.setScale(2, 2);
	spring3h.setScale(2, 2);
	spring4h.setScale(2, 2);
	num1h.setScale(2, 2);
	num2h.setScale(2, 2);
	num3h.setScale(2, 2);
	num4h.setScale(2, 2);
	cloud1h.setScale(3, 3);
	cloud2h.setScale(3, 3);
	cloud3h.setScale(3, 3);
	cloud4h.setScale(3, 3);
	door1h.setScale(3, 3);
	door2h.setScale(3, 3);
	door3h.setScale(3, 3);
	door4h.setScale(3, 3);
	doorNum1h.setScale(2, 2);
	doorNum2h.setScale(2, 2);
	doorNum3h.setScale(2, 2);
	doorNum4h.setScale(2, 2);

	//Snow Platform
	sf::Texture snowPTexh, snowPTexh2, snowPTexh3, snowPTexh4;
	sf::Sprite snowP1h, snowP2h, snowP3h, snowP4h;

	snowPTexh.loadFromFile("Textures/homeLevel/snowPlatform.png");
	snowPTexh2.loadFromFile("Textures/homeLevel/snowPlatform.png");
	snowPTexh3.loadFromFile("Textures/homeLevel/snowPlatform.png");
	snowPTexh4.loadFromFile("Textures/homeLevel/snowPlatform.png");

	snowP1h.setTexture(snowPTexh);
	snowP2h.setTexture(snowPTexh2);
	snowP3h.setTexture(snowPTexh3);
	snowP4h.setTexture(snowPTexh4);

	snowP1h.setPosition(0, 990);
	snowP2h.setPosition(671, 990);
	snowP3h.setPosition(1285, 990);
	snowP4h.setPosition(1897, 990);

	//------------------------------------------------------------------------------------------------------------------------------------------//

	//PLAYER CAMERA/ VIEW INITIALIZATION
	sf::View view(sf::FloatRect(0, 0, 800, 600));
	sf::View defview(sf::FloatRect(0, 0, 1920, 1080));

	sf::View guiView(sf::FloatRect(0, 0, 800, 600));
	sf::View endView(sf::FloatRect(0, 0, 500, 300));

	sf::Music bgMusic;
	bgMusic.openFromFile("Audio/bgMusic.wav");

	bgMusic.setVolume(0);
	bgMusic.setLoop(true);
	bgMusic.play();
		
	sf::Music home, snow, desert, jungle;
	snow.openFromFile("Audio/snow.mp3");
	snow.setVolume(80);
	snow.setLoop(true);

	desert.openFromFile("Audio/desert.mp3");
	desert.setVolume(80);
	desert.setLoop(true);

	jungle.openFromFile("Audio/jungle.mp3");
	jungle.setVolume(80);
	jungle.setLoop(true);

	home.openFromFile("Audio/home.wav");
	home.setVolume(80);
	home.setLoop(true);
	
	
	


	//UNIVERSAL BOOLEANS
	bool haskeyLevel1 = true;
	bool hasKeyLevel2 = false;
	bool hasKeyLevel3 = false;
	bool hasKeyLevel4 = false;

	player.setPosition(snowP1.getPosition().x, snowP1.getPosition().y + 50);

	//-------------------------------------------------------------------------------------------------------------------------------------------//
	// LEVEL 2
	
	//---------------------------------------------------BACKGROUND------------------------------------------------------------//
	sf::Texture dBgTex; //Dbg == Desert Background
	sf::Sprite dBg;
	dBgTex.loadFromFile("Textures/Level 2/bg.png");
	dBg.setTexture(dBgTex);
	//----------------------------------------------SPRITES AND TEXTURES--------------------------------------------------------//
	//AUTUMN CHUCNK
	sf::Texture chunkTexd;
	sf::Sprite chunkd, chunkd2;

	chunkTexd.loadFromFile("Textures/Level 2/chunk.png");

	chunkd.setTexture(chunkTexd);
	chunkd2.setTexture(chunkTexd);

	chunkd.setPosition(0, 974);
	chunkd2.setPosition(1735, 974);

	//Spring
	sf::Texture springdTex;
	sf::Sprite springd1, springd2, springd3, springd4, springd5, springd6, springd7, springd8, springd9, springd10, springd11, springd12, springd13;

	springdTex.loadFromFile("Textures/Level 2/springTileSheet.png");

	springd1.setTexture(springdTex);
	springd2.setTexture(springdTex);
	springd3.setTexture(springdTex);
	springd4.setTexture(springdTex);
	springd5.setTexture(springdTex);
	springd6.setTexture(springdTex);
	springd7.setTexture(springdTex);
	springd8.setTexture(springdTex);
	springd9.setTexture(springdTex);
	springd10.setTexture(springdTex);
	springd11.setTexture(springdTex);
	springd12.setTexture(springdTex);
	springd13.setTexture(springdTex);

	springd1.setTextureRect(sf::IntRect(0, 0, 18, 14));
	springd2.setTextureRect(sf::IntRect(0, 0, 18, 14));
	springd3.setTextureRect(sf::IntRect(0, 0, 18, 14));
	springd4.setTextureRect(sf::IntRect(0, 0, 18, 14));
	springd5.setTextureRect(sf::IntRect(0, 0, 18, 14));
	springd6.setTextureRect(sf::IntRect(0, 0, 18, 14));
	springd7.setTextureRect(sf::IntRect(0, 0, 18, 14));
	springd8.setTextureRect(sf::IntRect(0, 0, 18, 14));
	springd9.setTextureRect(sf::IntRect(0, 0, 18, 14));
	springd10.setTextureRect(sf::IntRect(0, 0, 18, 14));
	springd11.setTextureRect(sf::IntRect(0, 0, 18, 14));
	springd12.setTextureRect(sf::IntRect(0, 0, 18, 14));
	springd13.setTextureRect(sf::IntRect(0, 0, 18, 14));

	springd1.setScale(2, 2);
	springd2.setScale(2, 2);
	springd3.setScale(2, 2);
	springd4.setScale(2, 2);
	springd5.setScale(2, 2);
	springd6.setScale(2, 2);
	springd7.setScale(2, 2);
	springd8.setScale(2, 2);
	springd9.setScale(2, 2);
	springd10.setScale(2, 2);
	springd11.setScale(2, 2);
	springd12.setScale(2, 2);
	springd13.setScale(2, 2);

	springd1.setPosition(152, 946);
	springd2.setPosition(300, 946);
	springd3.setPosition(454, 946);
	springd4.setPosition(613, 946);
	springd5.setPosition(754, 946);
	springd6.setPosition(913, 946);
	springd7.setPosition(1076, 946);
	springd8.setPosition(1249, 946);
	springd9.setPosition(1407, 946);
	springd10.setPosition(1574, 946);
	springd11.setPosition(1770, 946);
	springd12.setPosition(1879, 946);
	springd13.setPosition(50, 433);

	//PILLARS

	sf::Texture p3Texd, pTexd;
	sf::Sprite p3d, pd1, pd2, pd3, pd4, pd5, pd6, pd7, pd8, pd9, pd10;

	p3Texd.loadFromFile("Textures/Level 2/pillar1.png");
	pTexd.loadFromFile("Textures/Level 2/pillar2.png");

	p3d.setTexture(p3Texd);
	pd1.setTexture(pTexd);
	pd2.setTexture(pTexd);
	pd3.setTexture(pTexd);
	pd4.setTexture(pTexd);
	pd5.setTexture(pTexd);
	pd6.setTexture(pTexd);
	pd7.setTexture(pTexd);
	pd8.setTexture(pTexd);
	pd9.setTexture(pTexd);
	pd10.setTexture(pTexd);

	p3d.setPosition(199, 836);
	pd1.setPosition(346, 792);
	pd2.setPosition(502, 794);
	pd3.setPosition(657, 792);
	pd4.setPosition(803, 793);
	pd5.setPosition(963, 794);
	pd6.setPosition(1122, 792);
	pd7.setPosition(1298, 793);
	pd8.setPosition(1451, 794);
	pd9.setPosition(1617, 791);
	pd10.setPosition(1813, 794);

	//SPIKES

	sf::Texture spikeTexd;
	sf::Sprite spiked1, spiked2, spiked3, spiked4, spiked5, spiked6, spiked7, spiked8, spiked9, spiked10, spiked11;

	spikeTexd.loadFromFile("Textures/Level 2/spike.png");

	spiked1.setTexture(spikeTexd);
	spiked2.setTexture(spikeTexd);
	spiked3.setTexture(spikeTexd);
	spiked4.setTexture(spikeTexd);
	spiked5.setTexture(spikeTexd);
	spiked6.setTexture(spikeTexd);
	spiked7.setTexture(spikeTexd);
	spiked8.setTexture(spikeTexd);
	spiked9.setTexture(spikeTexd);
	spiked10.setTexture(spikeTexd);
	spiked11.setTexture(spikeTexd);

	spiked1.setScale(2, 2);
	spiked2.setScale(2, 2);
	spiked3.setScale(2, 2);
	spiked4.setScale(2, 2);
	spiked5.setScale(2, 2);
	spiked6.setScale(2, 2);
	spiked7.setScale(2, 2);
	spiked8.setScale(2, 2);
	spiked9.setScale(2, 2);
	spiked10.setScale(2, 2);
	spiked11.setScale(2, 2);

	spiked1.setPosition(205, 817);
	spiked2.setPosition(354, 773);
	spiked3.setPosition(508, 775);
	spiked4.setPosition(663, 775);
	spiked5.setPosition(808, 775);
	spiked6.setPosition(967, 775);
	spiked7.setPosition(1127, 775);
	spiked8.setPosition(1305, 775);
	spiked9.setPosition(1458, 775);
	spiked10.setPosition(1622, 773);
	spiked11.setPosition(1818, 775);

	//COINS
	sf::Texture coinTexd;
	sf::Sprite coin1d, coin2d, coin3d, coinInDoor;

	coinTexd.loadFromFile("Textures/coin.png");

	coin1d.setTexture(coinTexd);
	coin2d.setTexture(coinTexd);
	coin3d.setTexture(coinTexd);
	coinInDoor.setTexture(coinTexd);


	coin1d.setTextureRect(sf::IntRect(0, 0, 12, 12));
	coin2d.setTextureRect(sf::IntRect(0, 0, 12, 12));
	coin3d.setTextureRect(sf::IntRect(0, 0, 12, 12));
	coinInDoor.setTextureRect(sf::IntRect(0, 0, 12, 12));

	coin1d.setScale(2, 2);
	coin2d.setScale(2, 2);
	coin3d.setScale(2, 2);
	coinInDoor.setScale(2, 2);

	coin1d.setPosition(669, 713);
	coin2d.setPosition(1133, 711);
	coin3d.setPosition(1638, 247);
	coinInDoor.setPosition(1875, 240);



	//CLOUDS
	sf::Texture cloudTexd, sCloudTexd;
	sf::Sprite cloud1d, cloud2d, cloud3d, cloud4d, cloud5d, cloud6d, cloud7d, cloud8d, cloud9d, cloud10d, cloud11d, cloud12d, cloud13d, cloud14d, cloud15d, cloud16d, sCloud1d, sCloud2d, sCloud3d, sCloud4d, sCloud5d, sCloud6d, sCloud7d, sCloud8d, sCloud9d, sCloud10d;

	cloudTexd.loadFromFile("Textures/Level 2/cloud.png");
	sCloudTexd.loadFromFile("Textures/Level 2/sCloud.png");

	cloud1d.setTexture(cloudTexd);
	cloud2d.setTexture(cloudTexd);
	cloud3d.setTexture(cloudTexd);
	cloud4d.setTexture(cloudTexd);
	cloud5d.setTexture(cloudTexd);
	cloud6d.setTexture(cloudTexd);
	cloud7d.setTexture(cloudTexd);
	cloud8d.setTexture(cloudTexd);
	cloud9d.setTexture(cloudTexd);
	cloud10d.setTexture(cloudTexd);
	cloud11d.setTexture(cloudTexd);
	cloud12d.setTexture(cloudTexd);
	cloud13d.setTexture(cloudTexd);
	cloud14d.setTexture(cloudTexd);
	cloud15d.setTexture(cloudTexd);
	cloud16d.setTexture(cloudTexd);

	sCloud1d.setTexture(sCloudTexd);
	sCloud2d.setTexture(sCloudTexd);
	sCloud3d.setTexture(sCloudTexd);
	sCloud4d.setTexture(sCloudTexd);
	sCloud5d.setTexture(sCloudTexd);
	sCloud6d.setTexture(sCloudTexd);
	sCloud7d.setTexture(sCloudTexd);
	sCloud8d.setTexture(sCloudTexd);
	sCloud9d.setTexture(sCloudTexd);
	sCloud10d.setTexture(sCloudTexd);

	cloud1d.setScale(3, 3);
	cloud2d.setScale(3, 3);
	cloud3d.setScale(3, 3);
	cloud4d.setScale(3, 3);
	cloud5d.setScale(3, 3);
	cloud6d.setScale(3, 3);
	cloud7d.setScale(3, 3);
	cloud8d.setScale(3, 3);
	cloud9d.setScale(3, 3);
	cloud10d.setScale(3, 3);
	cloud11d.setScale(3, 3);
	cloud12d.setScale(3, 3);
	cloud13d.setScale(3, 3);
	cloud14d.setScale(3, 3);
	cloud15d.setScale(3, 3);
	cloud16d.setScale(3, 3);

	sCloud1d.setScale(3, 3);
	sCloud2d.setScale(3, 3);
	sCloud3d.setScale(3, 3);
	sCloud4d.setScale(3, 3);
	sCloud5d.setScale(3, 3);
	sCloud6d.setScale(3, 3);
	sCloud7d.setScale(3, 3);
	sCloud8d.setScale(3, 3);
	sCloud9d.setScale(3, 3);
	sCloud10d.setScale(3, 3);

	cloud1d.setPosition(1364, 518);
	cloud2d.setPosition(1151, 533);
	cloud3d.setPosition(974, 498);
	cloud4d.setPosition(782, 533);
	cloud5d.setPosition(594, 513);
	cloud6d.setPosition(162, 513);
	cloud7d.setPosition(163, 305);
	cloud8d.setPosition(374, 280);
	cloud9d.setPosition(562, 284);
	cloud10d.setPosition(765, 286);
	cloud11d.setPosition(995, 298);
	cloud12d.setPosition(1194, 272);
	cloud13d.setPosition(1368, 300);
	cloud14d.setPosition(1582, 282);
	cloud15d.setPosition(1781, 289);
	cloud16d.setPosition(26, 108);

	sCloud1d.setPosition(436, 532);
	sCloud2d.setPosition(42, 459);
	sCloud3d.setPosition(1255, 84);
	sCloud4d.setPosition(1100, 73);
	sCloud5d.setPosition(962, 81);
	sCloud6d.setPosition(807, 67);
	sCloud7d.setPosition(668, 81);
	sCloud8d.setPosition(540, 57);
	sCloud9d.setPosition(378, 69);
	sCloud10d.setPosition(275, 73);

	//CHISELED PLATFORM
	sf::Texture chisCutTexd, chisTrioTexd;
	sf::Sprite chisCut, chisTrio1, chisTrio2, chisTrio3;

	chisCutTexd.loadFromFile("Textures/Level 2/chisCut.png");
	chisTrioTexd.loadFromFile("Textures/Level 2/chis1.png");

	chisCut.setTexture(chisCutTexd);
	chisTrio1.setTexture(chisTrioTexd);
	chisTrio2.setTexture(chisTrioTexd);
	chisTrio3.setTexture(chisTrioTexd);

	chisCut.setPosition(1892, 0);
	chisTrio1.setPosition(1589, 566);
	chisTrio2.setPosition(1605, 101);
	chisTrio3.setPosition(1321, 101);

	//KEY
	sf::Texture keyTexD;
	sf::Sprite keydi, keyd;

	keyTexD.loadFromFile("Textures/Level 2/key.png");
	keydi.setTexture(keyTexD);
	keyd.setTexture(keyTexD);

	keydi.setPosition(1613, 52);
	keyd.setPosition(74, 52);

	keydi.setScale(2, 2);
	keyd.setScale(2, 2);

	//DOOR
	sf::Texture doorTexd;
	sf::Sprite coinDoord, keyDoord;

	doorTexd.loadFromFile("Textures/Level 2/door.png");

	coinDoord.setTexture(doorTexd);
	keyDoord.setTexture(doorTexd);

	coinDoord.setScale(3, 3);
	keyDoord.setScale(3, 3);

	coinDoord.setPosition(1860, 224);
	keyDoord.setPosition(65, 40);

	//-----------------------------------------------------ENEMIES---------------------------------------//


	sf::Texture bEnemyd1t, bEnemyd2t, bEnemyd3t, bEnemyd4t, bEnemyd5t, bEnemyd6t, bEnemyd7t;
	sf::Sprite bEnemyd1, bEnemyd2, bEnemyd3, bEnemyd4, bEnemyd5, bEnemyd6, bEnemyd7;

	bEnemyd1t.loadFromFile("Textures/enemyBlue.png");
	bEnemyd2t.loadFromFile("Textures/enemyBlue.png");
	bEnemyd3t.loadFromFile("Textures/enemyBlue.png");
	bEnemyd4t.loadFromFile("Textures/enemyBlue.png");
	bEnemyd5t.loadFromFile("Textures/enemyBlue.png");
	bEnemyd6t.loadFromFile("Textures/enemyBlue.png");
	bEnemyd7t.loadFromFile("Textures/enemyBlue.png");

	bEnemyd1.setTexture(bEnemyd1t);
	bEnemyd2.setTexture(bEnemyd2t);
	bEnemyd3.setTexture(bEnemyd3t);
	bEnemyd4.setTexture(bEnemyd4t);
	bEnemyd5.setTexture(bEnemyd5t);
	bEnemyd6.setTexture(bEnemyd6t);
	bEnemyd7.setTexture(bEnemyd7t);

	bEnemyd1.setTextureRect(sf::IntRect(0, 0, 15, 14));
	bEnemyd2.setTextureRect(sf::IntRect(0, 0, 15, 14));
	bEnemyd3.setTextureRect(sf::IntRect(0, 0, 15, 14));
	bEnemyd4.setTextureRect(sf::IntRect(0, 0, 15, 14));
	bEnemyd5.setTextureRect(sf::IntRect(0, 0, 15, 14));
	bEnemyd6.setTextureRect(sf::IntRect(0, 0, 15, 14));
	bEnemyd7.setTextureRect(sf::IntRect(0, 0, 15, 14));

	bEnemyd1.setPosition(cloud7d.getPosition().x, cloud7d.getPosition().y - 3);
	bEnemyd2.setPosition(cloud8d.getPosition().x, cloud8d.getPosition().y - 3);
	bEnemyd3.setPosition(cloud9d.getPosition().x, cloud9d.getPosition().y - 3);
	bEnemyd4.setPosition(cloud10d.getPosition().x, cloud10d.getPosition().y - 3);
	bEnemyd5.setPosition(cloud11d.getPosition().x, cloud11d.getPosition().y - 3);
	bEnemyd6.setPosition(cloud12d.getPosition().x, cloud12d.getPosition().y - 3);
	bEnemyd7.setPosition(cloud13d.getPosition().x, cloud13d.getPosition().y - 3);

	bEnemyd1.setScale(2, 2);
	bEnemyd2.setScale(2, 2);
	bEnemyd3.setScale(2, 2);
	bEnemyd4.setScale(2, 2);
	bEnemyd5.setScale(2, 2);
	bEnemyd6.setScale(2, 2);
	bEnemyd7.setScale(2, 2);

	bEnemyd1.setOrigin(12.f, 12.f);
	bEnemyd2.setOrigin(12.f, 12.f);
	bEnemyd3.setOrigin(12.f, 12.f);
	bEnemyd4.setOrigin(12.f, 12.f);
	bEnemyd5.setOrigin(12.f, 12.f);
	bEnemyd6.setOrigin(12.f, 12.f);
	bEnemyd7.setOrigin(12.f, 12.f);

	float bed1LeftBound = cloud7d.getGlobalBounds().left;
	float bed1rightBound = cloud7d.getPosition().x + cloud7d.getGlobalBounds().width;

	float bed2LeftBound = cloud8d.getGlobalBounds().left;
	float bed2rightBound = cloud8d.getPosition().x + cloud8d.getGlobalBounds().width;

	float bed3LeftBound = cloud9d.getGlobalBounds().left;
	float bed3rightBound = cloud9d.getPosition().x + cloud9d.getGlobalBounds().width;

	float bed4LeftBound = cloud10d.getGlobalBounds().left;
	float bed4rightBound = cloud10d.getPosition().x + cloud10d.getGlobalBounds().width;

	float bed5LeftBound = cloud11d.getGlobalBounds().left;
	float bed5rightBound = cloud11d.getPosition().x + cloud11d.getGlobalBounds().width;

	float bed6LeftBound = cloud12d.getGlobalBounds().left;
	float bed6rightBound = cloud12d.getPosition().x + cloud12d.getGlobalBounds().width;

	float bed7LeftBound = cloud13d.getGlobalBounds().left;
	float bed7rightBound = cloud13d.getPosition().x + cloud13d.getGlobalBounds().width;

	int bed1frameCount = 0;
	int bed1switchFrame(8);

	int bed2frameCount = 0;
	int bed2switchFrame(8);

	int bed3frameCount = 0;
	int bed3switchFrame(8);

	int bed4frameCount = 0;
	int bed4switchFrame(8);

	int bed5frameCount = 0;
	int bed5switchFrame(8);

	int bed6frameCount = 0;
	int bed6switchFrame(8);

	int bed7frameCount = 0;
	int bed7switchFrame(8);

	float bed1enemySpeed = 1.0f;
	float bed1enemyDirection = -1.0f;

	float bed7enemySpeed = 1.0f;
	float bed7enemyDirection = -1.0f;

	float bed2enemySpeed = 1.0f;
	float bed2enemyDirection = -1.0f;

	float bed3enemySpeed = 1.0f;
	float bed3enemyDirection = -1.0f;

	float bed4enemySpeed = 1.0f;
	float bed4enemyDirection = -1.0f;

	float bed5enemySpeed = 1.0f;
	float bed5enemyDirection = -1.0f;

	float bed6enemySpeed = 1.0f;
	float bed6enemyDirection = -1.0f;



	//RED ENEMY
	sf::Texture rEnemyTexd1, rEnemyTexd2, rEnemyTexd3, rEnemyTexd4, rEnemyTexd5, rEnemyTexd6;
	sf::Sprite rEnemyd1, rEnemyd2, rEnemyd3, rEnemyd4, rEnemyd5, rEnemyd6;

	rEnemyTexd1.loadFromFile("Textures/enemyRed.png");
	rEnemyTexd2.loadFromFile("Textures/enemyRed.png");
	rEnemyTexd3.loadFromFile("Textures/enemyRed.png");
	rEnemyTexd4.loadFromFile("Textures/enemyRed.png");
	rEnemyTexd5.loadFromFile("Textures/enemyRed.png");
	rEnemyTexd6.loadFromFile("Textures/enemyRed.png");

	rEnemyd1.setTexture(rEnemyTexd1);
	rEnemyd2.setTexture(rEnemyTexd1);
	rEnemyd3.setTexture(rEnemyTexd3);
	rEnemyd4.setTexture(rEnemyTexd4);
	rEnemyd5.setTexture(rEnemyTexd5);
	rEnemyd6.setTexture(rEnemyTexd6);

	rEnemyd1.setTextureRect(sf::IntRect(0, 0, 15, 19));
	rEnemyd2.setTextureRect(sf::IntRect(0, 0, 15, 19));
	rEnemyd3.setTextureRect(sf::IntRect(0, 0, 15, 19));
	rEnemyd4.setTextureRect(sf::IntRect(0, 0, 15, 19));
	rEnemyd5.setTextureRect(sf::IntRect(0, 0, 15, 19));
	rEnemyd6.setTextureRect(sf::IntRect(0, 0, 15, 19));

	rEnemyd1.setScale(2, 2);
	rEnemyd2.setScale(2, 2);
	rEnemyd3.setScale(2, 2);
	rEnemyd4.setScale(2, 2);
	rEnemyd5.setScale(2, 2);
	rEnemyd6.setScale(2, 2);

	rEnemyd1.setPosition(cloud1d.getPosition().x, cloud1d.getPosition().y - 13);
	rEnemyd2.setPosition(cloud3d.getPosition().x, cloud3d.getPosition().y - 10);
	rEnemyd3.setPosition(cloud5d.getPosition().x, cloud5d.getPosition().y - 10);
	rEnemyd4.setPosition(cloud6d.getPosition().x, cloud6d.getPosition().y - 10);

	rEnemyd1.setOrigin(12.f, 12.f);
	rEnemyd2.setOrigin(12.f, 12.f);
	rEnemyd3.setOrigin(12.f, 12.f);
	rEnemyd4.setOrigin(12.f, 12.f);
	rEnemyd5.setOrigin(12.f, 12.f);
	rEnemyd6.setOrigin(12.f, 12.f);

	float red1LeftBound = cloud1d.getGlobalBounds().left;
	float red1rightBound = cloud1d.getPosition().x + cloud1d.getGlobalBounds().width;

	float red2LeftBound = cloud3d.getGlobalBounds().left;
	float red2rightBound = cloud3d.getPosition().x + cloud3d.getGlobalBounds().width;

	float red3LeftBound = cloud5d.getGlobalBounds().left;
	float red3rightBound = cloud5d.getPosition().x + cloud5d.getGlobalBounds().width;

	float red4LeftBound = cloud6d.getGlobalBounds().left;
	float red4rightBound = cloud6d.getPosition().x + cloud6d.getGlobalBounds().width;



	int red1frameCount = 0;
	int red1switchFrame(8);

	int red2frameCount = 0;
	int red2switchFrame(8);

	int red3frameCount = 0;
	int red3switchFrame(8);

	int red4frameCount = 0;
	int red4switchFrame(8);


	float red1enemySpeed = 1.0f;
	float red1enemyDirection = -1.0f;

	float red2enemySpeed = 1.0f;
	float red2enemyDirection = -1.0f;

	float red3enemySpeed = 1.0f;
	float red3enemyDirection = -1.0f;

	float red4enemySpeed = 1.0f;
	float red4enemyDirection = -1.0f;

	//FLYING ENEMY

	sf::Texture fEnemyTex1d, fEnemyTex2d;
	sf::Sprite fEnemyd1, fEnemyd2;

	fEnemyTex1d.loadFromFile("Textures/flyingEnemy.png");
	fEnemyTex2d.loadFromFile("Textures/flyingEnemy.png");

	fEnemyd1.setTexture(fEnemyTex1d);
	fEnemyd2.setTexture(fEnemyTex2d);

	fEnemyd1.setScale(2, 2);
	fEnemyd2.setScale(2, 2);

	fEnemyd1.setPosition(1503, 390);
	fEnemyd2.setPosition(1731, 168);

	fEnemyd1.setScale(2, 2);
	fEnemyd2.setScale(2, 2);

	fEnemyd1.setOrigin(12.f, 12.f);
	fEnemyd2.setOrigin(12.f, 12.f);



	float fed1LeftBound = cloud6d.getGlobalBounds().left;
	float fed1rightBound = cloud1d.getPosition().x + cloud1d.getGlobalBounds().width;

	float fed2LeftBound = cloud7d.getGlobalBounds().left;
	float fed2rightBound = cloud14d.getPosition().x + cloud14d.getGlobalBounds().width;

	int fed1frameCount = 0;
	int fed1switchFrame(8);

	int fed2frameCount = 0;
	int fed2switchFrame(8);

	float fed1enemySpeed = 2.5f;
	float fed1enemyDirection = -1.0f;

	float fed2enemySpeed = 2.5f;
	float fed2enemyDirection = -1.0f;

	sf::Font font;
	font.loadFromFile("Fonts/LeagueSpartan-SemiBold.ttf"); // Corrected font file path
	sf::Text text("In level 2", font, 30);

	bool isSquishedb1d = false;
	bool isSquishedb2d = false;
	bool isSquishedb3d = false;
	bool isSquishedb4d = false;
	bool isSquishedb5d = false;
	bool isSquishedb6d = false;
	bool isSquishedb7d = false;
	bool isSquishedf1d = false;
	bool isSquishedf2d = false;

	sf::Clock squishTimerb1d;
	sf::Clock squishTimerb2d;
	sf::Clock squishTimerb3d;
	sf::Clock squishTimerb4d;
	sf::Clock squishTimerb5d;
	sf::Clock squishTimerb6d;
	sf::Clock squishTimerb7d;
	sf::Clock squishTimerf1d;
	sf::Clock squishTimerf2d;

	sf::Time squishDurationb1d = sf::seconds(0.5f);
	sf::Time squishDurationb2d = sf::seconds(0.5f);
	sf::Time squishDurationb3d = sf::seconds(0.5f);
	sf::Time squishDurationb4d = sf::seconds(0.5f);
	sf::Time squishDurationb5d = sf::seconds(0.5f);
	sf::Time squishDurationb6d = sf::seconds(0.5f);
	sf::Time squishDurationb7d = sf::seconds(0.5f);
	sf::Time squishDurationf1d = sf::seconds(0.5f);
	sf::Time squishDurationf2d = sf::seconds(0.5f);
	
	int coin1DFrameCount = 0;
	float coin1DSwitchFrame(10);

	int coin2DFrameCount = 0;
	float coin2DSwitchFrame(10);

	int coin3DFrameCount = 0;
	float coin3DSwitchFrame(10);

	sf::FloatRect chisTrio1Bounds = chisTrio1.getGlobalBounds();
	sf::FloatRect playerBounds = player.getGlobalBounds();

	sf::Texture cratesTex;
	sf::Sprite crates;

	cratesTex.loadFromFile("Textures/Level 2/crates.png");

	crates.setTexture(cratesTex);

	crates.setPosition(chisTrio3.getPosition().x, chisTrio3.getPosition().y - 200);

	crates.setScale(2, 2);

	sf::FloatRect chisCutBounds = chisCut.getGlobalBounds();

	sf::SoundBuffer woodBuffer;
	woodBuffer.loadFromFile("Audio/wood.mp3");
	sf::Sound wood;
	wood.setBuffer(woodBuffer);

	//LEVEL 3
	//---------------------------------------------------BACKGROUND------------------------------------------------------------//
	sf::Texture fBgTex; //Dbg == Desert Background
	sf::Sprite fBg;
	fBgTex.loadFromFile("Textures/Level 3/bg.png");
	fBg.setTexture(fBgTex);

	//------------------------------------------------------------------------------------------------------------------------//
	sf::Texture grassChunkTex, grassPlatTex, grassPlatCutTex;
	sf::Sprite grassChunk, grassPlat1, grassPlat2, grassPlat3, grassPlat4, grassPlatCut;

	grassChunkTex.loadFromFile("Textures/Level 3/grassChunk.png");
	grassPlatTex.loadFromFile("Textures/Level 3/grassPlatform.png");
	grassPlatCutTex.loadFromFile("Textures/Level 3/grassPlatformCut.png");

	grassChunk.setTexture(grassChunkTex);
	grassPlat1.setTexture(grassPlatTex);
	grassPlat2.setTexture(grassPlatTex);
	grassPlat3.setTexture(grassPlatTex);
	grassPlat4.setTexture(grassPlatTex);
	grassPlatCut.setTexture(grassPlatCutTex);

	grassChunk.setPosition(0, 1023);
	grassPlat1.setPosition(468, 1039);
	grassPlat2.setPosition(802, 1039);
	grassPlat3.setPosition(1122, 1039);
	grassPlat4.setPosition(1481, 1039);
	grassPlatCut.setPosition(1825, 1035);

	//-------------------------------------------------------SPIKES---------------------------------------------------------//

	sf::Texture jSpikeT;
	sf::Sprite jSpike1, jSpike2, jSpike3, jSpike4;

	jSpikeT.loadFromFile("Textures/Level 3/spike.png");

	jSpike1.setTexture(jSpikeT);
	jSpike2.setTexture(jSpikeT);
	jSpike3.setTexture(jSpikeT);
	jSpike4.setTexture(jSpikeT);

	jSpike1.setScale(2, 2);
	jSpike2.setScale(2, 2);
	jSpike3.setScale(2, 2);
	jSpike4.setScale(2, 2);

	jSpike1.setPosition(570, 1021);
	jSpike2.setPosition(862, 1021);
	jSpike3.setPosition(1219, 1021);
	jSpike4.setPosition(1578, 1021);

	//-------------------------------------------------------BRANCHES---------------------------------------------------------//

	sf::Texture branchTex;
	sf::Sprite branch1, branch2, branch3, branch4;

	branchTex.loadFromFile("Textures/Level 3/branch.png");

	branch1.setTexture(branchTex);
	branch2.setTexture(branchTex);
	branch3.setTexture(branchTex);
	branch4.setTexture(branchTex);

	branch1.setPosition(462, 919);
	branch2.setPosition(797, 902);
	branch3.setPosition(1154, 920);
	branch4.setPosition(1509, 900);

	//-------------------------------------------------------TREES-----------------------------------------------------------//

	sf::Texture treeTex1, treeTex2;
	sf::Sprite tree1, tree2, tree3, tree4;

	treeTex1.loadFromFile("Textures/Level 3/tree1.png");
	treeTex2.loadFromFile("Textures/Level 3/tree2.png");

	tree1.setTexture(treeTex1);
	tree2.setTexture(treeTex2);
	tree3.setTexture(treeTex1);
	tree4.setTexture(treeTex2);

	tree1.setPosition(359, 620);
	tree2.setPosition(713, 632);
	tree3.setPosition(1051, 622);
	tree4.setPosition(1426, 630);

	//-------------------------------------------------------CLOUDS---------------------------------------------------------//

	sf::Texture jCloudTex;
	sf::Sprite jCloud1, jCloud2, jCloud3, jCloud4, jCloud5, jCloud6, jCloud7, jCloud8, jCloud9, jCloud10, jCloud11, jCloud12, jCloud13;

	jCloudTex.loadFromFile("Textures/Level 3/cloud.png");

	jCloud1.setTexture(jCloudTex);
	jCloud2.setTexture(jCloudTex);
	jCloud3.setTexture(jCloudTex);
	jCloud4.setTexture(jCloudTex);
	jCloud5.setTexture(jCloudTex);
	jCloud6.setTexture(jCloudTex);
	jCloud7.setTexture(jCloudTex);
	jCloud8.setTexture(jCloudTex);
	jCloud9.setTexture(jCloudTex);
	jCloud10.setTexture(jCloudTex);
	jCloud11.setTexture(jCloudTex);
	jCloud12.setTexture(jCloudTex);
	jCloud13.setTexture(jCloudTex);

	jCloud1.setScale(3, 3);
	jCloud2.setScale(3, 3);
	jCloud3.setScale(3, 3);
	jCloud4.setScale(3, 3);
	jCloud5.setScale(3, 3);
	jCloud6.setScale(3, 3);
	jCloud7.setScale(3, 3);
	jCloud8.setScale(3, 3);
	jCloud9.setScale(3, 3);
	jCloud10.setScale(3, 3);
	jCloud11.setScale(3, 3);
	jCloud12.setScale(3, 3);
	jCloud13.setScale(3, 3);

	jCloud1.setPosition(1684, 642);
	jCloud2.setPosition(1407, 600);
	jCloud3.setPosition(1178, 579);
	jCloud4.setPosition(797, 593);
	jCloud5.setPosition(562, 575);
	jCloud6.setPosition(281, 604);
	jCloud7.setPosition(32, 496);
	jCloud8.setPosition(298, 420);
	jCloud9.setPosition(543, 300);
	jCloud10.setPosition(784, 419);
	jCloud11.setPosition(991, 357);
	jCloud12.setPosition(1268, 402);
	jCloud13.setPosition(13, 109);


	//-------------------------------------------------------LARGE TREE---------------------------------------------------------//

	sf::Texture largeTreeTex, largeTreeBranchT1, largeTreeBranchT2;
	sf::Sprite largeTree, largeTreeBranch1, largeTreeBranch2;

	largeTreeTex.loadFromFile("Textures/Level 3/tree3.png");
	largeTree.setTexture(largeTreeTex);

	largeTree.setPosition(1275, 2);

	largeTreeBranchT1.loadFromFile("Textures/Level 3/branchWideCon.png");
	largeTreeBranchT2.loadFromFile("Textures/Level 3/branchWideEnd.png");


	largeTreeBranch2.setTexture(largeTreeBranchT2);
	largeTreeBranch2.setPosition(1504, 172);
	largeTreeBranch1.setTexture(largeTreeBranchT1);
	largeTreeBranch1.setPosition(1720, 172);

	//-------------------------------------------------------SMALL CLOUDS---------------------------------------------------------//
	sf::Texture jSCloudTex;
	sf::Sprite jSCloud1, jSCloud2;

	jSCloudTex.loadFromFile("Textures/Level 3/sCloud.png");

	jSCloud1.setTexture(jSCloudTex);
	jSCloud2.setTexture(jSCloudTex);

	jSCloud1.setPosition(1058, 555);
	jSCloud2.setPosition(397, 172);

	jSCloud1.setScale(2, 2);
	jSCloud2.setScale(2, 2);

	//-------------------------------------------------------SPRINGS--------------------------------------------------------------//
	sf::Texture jSpringTex;
	sf::Sprite jSpring1, jSpring2, jSpring3, jSpring4;

	jSpringTex.loadFromFile("Textures/Level 3/springTileSheet.png");

	jSpring1.setTexture(jSpringTex);
	jSpring2.setTexture(jSpringTex);
	jSpring3.setTexture(jSpringTex);
	jSpring4.setTexture(jSpringTex);

	jSpring1.setTextureRect(sf::IntRect(0, 0, 18, 14));
	jSpring2.setTextureRect(sf::IntRect(0, 0, 18, 14));
	jSpring3.setTextureRect(sf::IntRect(0, 0, 18, 14));
	jSpring4.setTextureRect(sf::IntRect(0, 0, 18, 14));

	jSpring1.setScale(2, 2);
	jSpring2.setScale(2, 2);
	jSpring3.setScale(2, 2);
	jSpring4.setScale(2, 2);

	jSpring1.setPosition(1831, 1010);
	jSpring2.setPosition(36, 469);
	jSpring3.setPosition(397, 144);
	jSpring4.setPosition(jCloud12.getPosition().x + jCloud12.getGlobalBounds().width - jSpring4.getGlobalBounds().width, jCloud12.getPosition().y - 25);

	//------------------------------------------------------------DOOR----------------------------------------------------------//
	sf::Texture jDoorTex, coinInDoorT, keyInDoorT;
	sf::Sprite jDoor, coinInDoorJ, keyInDoor;

	jDoorTex.loadFromFile("Textures/Level 3/door.png");
	coinInDoorT.loadFromFile("Textures/Level 3/coinInDoor.png");
	keyInDoorT.loadFromFile("Textures/Level 3/keyInDoor.png");

	jDoor.setTexture(jDoorTex);
	jDoor.setScale(3, 3);
	jDoor.setPosition(65, 40);

	coinInDoorJ.setTexture(coinInDoorT);
	keyInDoor.setTexture(keyInDoorT);

	coinInDoorJ.setPosition(79, 25);
	keyInDoor.setPosition(95, 25);

	//------------------------------------------------------------ENEMIES---------------------------------------------------------//
	sf::Texture jERT1, jERT2, jEBT1, jEBT2, jEBT3, jFET1, jFET2;
	sf::Sprite jEnemyRed1, jEnemyRed2, jEnemyBlue1, jEnemyBlue2, jEnemyBlue3, jFEnemy1, jFEnemy2;

	jERT1.loadFromFile("Textures/enemyRed.png");
	jERT2.loadFromFile("Textures/enemyRed.png");

	jEBT1.loadFromFile("Textures/enemyBlue.png");
	jEBT2.loadFromFile("Textures/enemyBlue.png");
	jEBT3.loadFromFile("Textures/enemyBlue.png");

	jFET1.loadFromFile("Textures/flyingEnemy.png");
	jFET2.loadFromFile("Textures/flyingEnemy.png");

	//---------------------------------

	jEnemyRed1.setTexture(jERT1);
	jEnemyRed2.setTexture(jERT2);

	jEnemyBlue1.setTexture(jEBT1);
	jEnemyBlue2.setTexture(jEBT2);
	jEnemyBlue3.setTexture(jEBT3);

	jFEnemy1.setTexture(jFET1);
	jFEnemy2.setTexture(jFET2);

	//-----------------------------------------------------
	jEnemyRed1.setTextureRect(sf::IntRect(0, 0, 15, 19));
	jEnemyRed2.setTextureRect(sf::IntRect(0, 0, 15, 19));

	jEnemyBlue1.setTextureRect(sf::IntRect(0, 0, 15, 14));
	jEnemyBlue2.setTextureRect(sf::IntRect(0, 0, 15, 14));
	jEnemyBlue3.setTextureRect(sf::IntRect(0, 0, 15, 14));

	jFEnemy1.setTextureRect(sf::IntRect(0, 0, 18, 17));
	jFEnemy2.setTextureRect(sf::IntRect(0, 0, 18, 17));

	//--------------------------------------
	jEnemyRed1.setScale(2, 2);
	jEnemyRed2.setScale(2, 2);

	jEnemyBlue1.setScale(2, 2);
	jEnemyBlue2.setScale(2, 2);
	jEnemyBlue3.setScale(2, 2);

	jFEnemy1.setScale(2, 2);
	jFEnemy2.setScale(2, 2);

	//-------------------------------------
	jEnemyBlue1.setPosition(jCloud5.getGlobalBounds().left, jCloud5.getPosition().y - 4);
	jEnemyBlue2.setPosition(jCloud8.getGlobalBounds().left, jCloud8.getPosition().y - 4);
	jEnemyBlue3.setPosition(jCloud10.getGlobalBounds().left, jCloud8.getPosition().y - 4);

	jFEnemy1.setPosition(1371, 275);
	jFEnemy2.setPosition(1507, 475);

	jEnemyRed1.setPosition(jCloud1.getGlobalBounds().left, jCloud1.getPosition().y - 14);
	jEnemyRed2.setPosition(jCloud3.getGlobalBounds().left, jCloud3.getPosition().y - 14);

	//--------------------------------------------------ENEMY ORIGINS-----------------------------------------------------//

	jEnemyBlue1.setOrigin(12, 12);
	jEnemyBlue2.setOrigin(12, 12);
	jEnemyBlue3.setOrigin(12, 12);

	jEnemyRed1.setOrigin(12, 12);
	jEnemyRed2.setOrigin(12, 12);

	jFEnemy1.setOrigin(12, 12);
	jFEnemy2.setOrigin(12, 12);

	//-------------------------------------------------MOVEMENT VARIABLES-------------------------------------------------//
	float jB1enemySpeed = 1;
	float jB2enemySpeed = 1;
	float jB3enemySpeed = 1;

	float jR1enemySpeed = 1;
	float jR2enemySpeed = 1;

	float jF1enemySpeed = 1;
	float jF2enemySpeed = 1;

	float jB1enemyDirection = -1;
	float jB2enemyDirection = -1;
	float jB3enemyDirection = -1;

	float jR1enemyDirection = -1;
	float jR2enemyDirection = -1;

	float jF1enemyDirection = -1;
	float jF2enemyDirection = -1;

	float jB1enemyLeftBound = jCloud5.getGlobalBounds().left;
	float jB1enemyRightBound = jCloud5.getPosition().x + jCloud5.getGlobalBounds().width;

	float jB2enemyLeftBound = jCloud8.getGlobalBounds().left;
	float jB2enemyRightBound = jCloud8.getPosition().x + jCloud5.getGlobalBounds().width;

	float jB3enemyLeftBound = jCloud10.getGlobalBounds().left;
	float jB3enemyRightBound = jCloud10.getPosition().x + jCloud5.getGlobalBounds().width;

	float jR1enemyLeftBound = jCloud1.getGlobalBounds().left;
	float jR1enemyRightBound = jCloud1.getPosition().x + jCloud5.getGlobalBounds().width;

	float jR2enemyLeftBound = jCloud3.getGlobalBounds().left;
	float jR2enemyRightBound = jCloud3.getPosition().x + jCloud5.getGlobalBounds().width;

	float jF1enemyLeftBound = jCloud6.getGlobalBounds().left;
	float jF1enemyRightBound = jCloud2.getPosition().x + jCloud5.getGlobalBounds().width;

	float jF2enemyLeftBound = jCloud8.getGlobalBounds().left;
	float jF2enemyRightBound = jCloud12.getPosition().x + jCloud5.getGlobalBounds().width;

	int jB1FrameCount = 0;
	int jB1switchFrame(8);

	int jB2FrameCount = 0;
	int jB2switchFrame(8);

	int jB3FrameCount = 0;
	int jB3switchFrame(8);

	int jR1FrameCount = 0;
	int jR1switchFrame(8);

	int jR2FrameCount = 0;
	int jR2switchFrame(8);

	int jF1FrameCount = 0;
	int jF1SwitchFrame(8);

	int jF2FrameCount = 0;
	int jF2SwitchFrame(8);

	sf::FloatRect grassChunkBounds = grassChunk.getGlobalBounds();
	sf::FloatRect grassPlat1Bounds = grassPlat1.getGlobalBounds();
	sf::FloatRect grassPlat2Bounds = grassPlat2.getGlobalBounds();
	sf::FloatRect grassPlat3Bounds = grassPlat3.getGlobalBounds();
	sf::FloatRect grassPlat4Bounds = grassPlat4.getGlobalBounds();

	sf::FloatRect jCloud1Bounds = jCloud1.getGlobalBounds();
	sf::FloatRect jCloud2Bounds = jCloud2.getGlobalBounds();
	sf::FloatRect jCloud3Bounds = jCloud3.getGlobalBounds();
	sf::FloatRect jCloud4Bounds = jCloud4.getGlobalBounds();
	sf::FloatRect jCloud5Bounds = jCloud5.getGlobalBounds();
	sf::FloatRect jCloud6Bounds = jCloud6.getGlobalBounds();
	sf::FloatRect jCloud7Bounds = jCloud7.getGlobalBounds();
	sf::FloatRect jCloud8Bounds = jCloud8.getGlobalBounds();
	sf::FloatRect jCloud9Bounds = jCloud9.getGlobalBounds();
	sf::FloatRect jCloud10Bounds = jCloud10.getGlobalBounds();
	sf::FloatRect jCloud11Bounds = jCloud11.getGlobalBounds();
	sf::FloatRect jCloud12Bounds = jCloud12.getGlobalBounds();
	sf::FloatRect jCloud13Bounds = jCloud13.getGlobalBounds();

	sf::FloatRect branch1Bounds = branch1.getGlobalBounds();
	sf::FloatRect branch2Bounds = branch2.getGlobalBounds();
	sf::FloatRect branch3Bounds = branch3.getGlobalBounds();
	sf::FloatRect branch4Bounds = branch4.getGlobalBounds();

	sf::FloatRect wideBranchBounds1 = largeTreeBranch1.getGlobalBounds();
	sf::FloatRect wideBranchBounds2 = largeTreeBranch2.getGlobalBounds();

	sf::FloatRect jSpike1Bounds = jSpike1.getGlobalBounds();
	sf::FloatRect jSpike2Bounds = jSpike2.getGlobalBounds();
	sf::FloatRect jSpike3Bounds = jSpike3.getGlobalBounds();
	sf::FloatRect jSpike4Bounds = jSpike4.getGlobalBounds();

	bool isSquishedjeb1 = false;
	bool isSquishedjeb2 = false;
	bool isSquishedjeb3 = false;

	bool isSquishedjer1 = false;
	bool isSquishedjer2 = false;

	bool isSquishedjef1 = false;
	bool isSquishedjef2 = false;

	sf::Clock squishTimerjeb1;
	sf::Clock squishTimerjeb2;
	sf::Clock squishTimerjeb3;

	sf::Clock squishTimerjer1;
	sf::Clock squishTimerjer2;

	sf::Clock squishTimerjef1;
	sf::Clock squishTimerjef2;

	sf::Time squishDurationjeb1 = sf::seconds(0.5f);
	sf::Time squishDurationjeb2 = sf::seconds(0.5f);
	sf::Time squishDurationjeb3 = sf::seconds(0.5f);

	sf::Time squishDurationjer1 = sf::seconds(0.5f);
	sf::Time squishDurationjer2 = sf::seconds(0.5f);

	sf::Time squishDurationjef1 = sf::seconds(0.5f);
	sf::Time squishDurationjef2 = sf::seconds(0.5f);

	//-------------------------------------------COINS------------------------------------------------------//
	sf::Texture jCoinsIT;
	sf::Sprite jCoins1, jCoins2, jCoins3;

	jCoinsIT.loadFromFile("Textures/coin.png");

	jCoins1.setTexture(jCoinsIT);
	jCoins2.setTexture(jCoinsIT);
	jCoins3.setTexture(jCoinsIT);

	jCoins1.setScale(2, 2);
	jCoins2.setScale(2, 2);
	jCoins3.setScale(2, 2);
	
	jCoins1.setTextureRect(sf::IntRect(0, 0, 12, 12));
	jCoins2.setTextureRect(sf::IntRect(0, 0, 12, 12));
	jCoins3.setTextureRect(sf::IntRect(0, 0, 12, 12));

	jCoins1.setPosition(921, 1010);
	jCoins2.setPosition(49, 257);
	jCoins3.setPosition(1446, 257);

	int jCoins1FrameCount = 0;
	int jCoins1SwitchFrame(10);

	int jCoins2FrameCount = 0;
	int jCoins2SwitchFrame(10);

	int jCoins3FrameCount = 0;
	int jCoins3SwitchFrame(10);

	//-----------------------------------------------------------KEYS
	sf::Texture jKeyT;
	sf::Sprite jKey;

	jKeyT.loadFromFile("Textures/Level 3/keyI.png");
	
	jKey.setTexture(jKeyT);
	jKey.setScale(2, 2);
	jKey.setPosition(1751, 131);

	//COIN MONITOR
	std::stringstream coinMon;
	coinMon << "Find and Collect the Coins (" << coins << "/3)" << "\n";

	sf::Text coinMonitor;

	coinMonitor.setFont(leagueSpartan);

	coinMonitor.setString(coinMon.str());

	//----------------------------------------------------MENU------------------------------------------------//
	//MENU
	sf::Texture menuBackgroundTex;
	sf::Sprite menuBackground;

	menuBackgroundTex.loadFromFile("Textures/Menu/menu.png");
	menuBackground.setTexture(menuBackgroundTex);

	//SNOWMAN

	sf::Texture mSnowmanTex;
	sf::Sprite mSnowman;

	mSnowmanTex.loadFromFile("Textures/Menu/snowman.png");
	mSnowman.setTexture(mSnowmanTex);
	mSnowman.setScale(4, 4);

	mSnowman.setPosition(939, 926);

	//DIALOGUE
	sf::Texture mDialogueTex1, mDialogueTex2, mDialogueTex3, mDialogueTex4, mDialogueTex5, mDialogueTex6, mDialogueTex7;
	sf::Sprite mDialogue;

	mDialogueTex1.loadFromFile("Textures/Menu/1.png");
	mDialogueTex2.loadFromFile("Textures/Menu/2.png");
	mDialogueTex3.loadFromFile("Textures/Menu/3.png");
	mDialogueTex4.loadFromFile("Textures/Menu/4.png");
	mDialogueTex5.loadFromFile("Textures/Menu/5.png");
	mDialogueTex6.loadFromFile("Textures/Menu/6.png");
	mDialogueTex7.loadFromFile("Textures/Menu/7.png");

	mDialogue.setTexture(mDialogueTex1);

	mDialogue.setScale(1, 1);

	mDialogue.setPosition(mSnowman.getPosition().x - 190, mSnowman.getPosition().y - 120);

	int mDialogueNum = 1;

	sf::Clock dialogueClock;
	const sf::Time dialogueClockDur = sf::seconds(1.5f);

	//DIALOGUE NEXT SOUND
	sf::SoundBuffer dialogueBuffer;
	sf::Sound dialogueSound;

	dialogueBuffer.loadFromFile("Audio/snowball.wav");
	dialogueSound.setBuffer(dialogueBuffer);

	//GAME OVER SCREEN
	sf::Texture goTex;
	sf::Sprite gameOver;

	goTex.loadFromFile("Textures/Menu/gameOver1.png");

	gameOver.setTexture(goTex);

	sf::Vector2u goTextureSize = goTex.getSize();
	float goWidth = static_cast<float>(goTextureSize.x);
	float goHeight = static_cast<float>(goTextureSize.y);

	// Set the sprite's position to the center of the window
	
	bool gameOverDisplayed = false;
	sf::Clock gameOverClock;

	sf::SoundBuffer goBuffer;
	sf::Sound goSound;

	goBuffer.loadFromFile("Audio/gameover.mp3");
	goSound.setBuffer(goBuffer);

	//FRIEND ACCOMPLISHMENT
	bool level1Friendbool = false;
	bool level2Friendbool = false;
	bool level3Friendbool = false;
	bool level4Friendbool = false;

	//FRIEND TEXTURES
	sf::Texture l1FTex, l2FTex, l3FTex, l4FTex;
	sf::Sprite level1Friend, level2Friend, level3Friend, level4Friend;

	l1FTex.loadFromFile("Textures/homeLevel/friend1.png");
	l2FTex.loadFromFile("Textures/homeLevel/friend2.png");
	l3FTex.loadFromFile("Textures/homeLevel/friend3.png");
	l4FTex.loadFromFile("Textures/homeLevel/friend4.png");

	level1Friend.setTexture(l1FTex);
	level2Friend.setTexture(l2FTex);
	level3Friend.setTexture(l3FTex);
	level4Friend.setTexture(l4FTex);

	level1Friend.setScale(2, 2);
	level2Friend.setScale(2, 2);
	level3Friend.setScale(2, 2);
	level4Friend.setScale(2, 2);

	level1Friend.setPosition(spring1h.getPosition().x + 50, snowP1.getPosition().y + 80);
	level2Friend.setPosition(spring2h.getPosition().x + 50, snowP1.getPosition().y + 80);
	level3Friend.setPosition(spring3h.getPosition().x + 50, snowP1.getPosition().y + 80);
	level4Friend.setPosition(spring4h.getPosition().x + 50, snowP1.getPosition().y + 80);

	//FRIEND DIALOGUE
	sf::Texture frDialogueT1, frDialogueT2, frDialogueT3, frDialogueT4;
	sf::Sprite frDialogue1, frDialogue2, frDialogue3, frDialogue4;

	frDialogueT1.loadFromFile("Textures/homeLevel/8.png");
	frDialogueT2.loadFromFile("Textures/homeLevel/9.png");
	frDialogueT3.loadFromFile("Textures/homeLevel/10.png");
	/*frDialogueT4.loadFromFile("Textures/homeLevel/11.png");*/

	frDialogue1.setTexture(frDialogueT1);
	frDialogue2.setTexture(frDialogueT2);
	frDialogue3.setTexture(frDialogueT3);
	frDialogue4.setTexture(frDialogueT4);

	frDialogue1.setScale(0.5, 0.5);
	frDialogue2.setScale(0.5, 0.5);
	frDialogue3.setScale(0.5, 0.5);
	frDialogue4.setScale(0.5, 0.5);

	frDialogue1.setPosition(level1Friend.getPosition().x - 100, level1Friend.getPosition().y - 60);
	frDialogue2.setPosition(level2Friend.getPosition().x - 100, level2Friend.getPosition().y - 60);
	frDialogue3.setPosition(level3Friend.getPosition().x - 100, level3Friend.getPosition().y - 60);
	frDialogue4.setPosition(level4Friend.getPosition().x - 100, level4Friend.getPosition().y - 60);

	//-------------------------------------------ENDING VAR-------------------------------------------------//
	
	sf::Texture endTex;
	sf::Sprite end;

	endTex.loadFromFile("Textures/ending/end.png");
	end.setTexture(endTex);

	sf::Texture manT;
	sf::Sprite man;

	//ENDING MAN
	manT.loadFromFile("Textures/ending/man.png");
	man.setTexture(manT);
	
	man.setScale(0.03, 0.03);
	man.setPosition(1835, 1053);

	//BLOODY FRIENDS
	sf::Texture bfriend1T, bfriend2T, bfriend3T, bfriend4T;
	
	bfriend1T.loadFromFile("Textures/ending/friend1b.png");
	bfriend2T.loadFromFile("Textures/ending/friend2b.png");
	bfriend3T.loadFromFile("Textures/ending/friend3b.png");
	bfriend4T.loadFromFile("Textures/ending/friend4b.png");

	//Ending Dialogue
	sf::Texture eDT1, eDT2, eDT3;
	sf::Sprite endingDialogue1, endingDialogue2, endingDialogue3;

	eDT1.loadFromFile("Textures/ending/dialogue1.png");
	eDT2.loadFromFile("Textures/ending/dialogue2.png");
	eDT3.loadFromFile("Textures/ending/dialogue3.png");

	endingDialogue1.setTexture(eDT1);
	endingDialogue2.setTexture(eDT2);
	endingDialogue3.setTexture(eDT3);

	endingDialogue1.setScale(0.25, 0.25);
	endingDialogue2.setScale(0.25, 0.25);
	endingDialogue3.setScale(0.25, 0.25);

	//ALIEN SOUNDS
	sf::SoundBuffer alienBuffer1, alienBuffer2, alienBuffer3, suspenseBuffer;
	sf::Sound alien1, alien2, alien3, suspense;

	alienBuffer1.loadFromFile("Audio/alien1.wav");
	alienBuffer2.loadFromFile("Audio/alien2.wav");
	alienBuffer3.loadFromFile("Audio/alien3.wav");
	suspenseBuffer.loadFromFile("Audio/suspense.wav");

	alien1.setBuffer(alienBuffer1);
	alien2.setBuffer(alienBuffer2);
	alien3.setBuffer(alienBuffer3);
	suspense.setBuffer(suspenseBuffer);

	//CREDITS
	sf::Texture blackTex, jumpscareTex;
	sf::Sprite black, jumpscare;

	blackTex.loadFromFile("Textures/ending/black.png");
	jumpscareTex.loadFromFile("Textures/ending/jumpscare.png");

	black.setTexture(blackTex);
	jumpscare.setTexture(jumpscareTex);

	//Ending MUsic

	sf::Music endingMusic, creditsMusic;
	creditsMusic.openFromFile("Audio/creditsMusic.mp3");
	endingMusic.openFromFile("Audio/endingMusic.mp3");
	endingMusic.setVolume(80);
	endingMusic.setLoop(true);


	sf::SoundBuffer jumpscareBuffer;
	sf::Sound jumpscareSound;

	jumpscareBuffer.loadFromFile("Audio/jumpscare.mp3");
	jumpscareSound.setBuffer(jumpscareBuffer);

	//CREDITS PNG
	sf::Texture c1T, c2T, c3T;
	sf::Sprite credits1, credits2, credits3;

	c1T.loadFromFile("Textures/ending/credits1.png");
	c2T.loadFromFile("Textures/ending/credits2.png");
	c3T.loadFromFile("Textures/ending/credits3.png");

	credits1.setTexture(c1T);
	credits2.setTexture(c2T);
	credits3.setTexture(c3T);

	bool credits = false;

	//TRANSITION LEVELS
	//TRANSITIONS
	sf::Texture transTex, tDoorTex;
	sf::Sprite trans, tDoor;

	transTex.loadFromFile("Textures/transitions/transition.png");
	tDoorTex.loadFromFile("Textures/transitions/door.png");
	tDoor.setTexture(tDoorTex);
	trans.setTexture(transTex);

	tDoor.setScale(3, 3);
	tDoor.setPosition(1822, 920);

	//Logo
	sf::Texture logoBgTex, logoTex;
	sf::Sprite logoBg, logo;

	logoBgTex.loadFromFile("Textures/menu/logoBg.png");
	logoTex.loadFromFile("Textures/menu/logo.png");

	logoBg.setTexture(logoBgTex);
	logo.setTexture(logoTex);

	float alpha = 0.f;
	sf::Clock fadeInClock;

	//Menu Screen Status

	int menuScreen = 1;
	sf::Clock logoClock;
	int logoDuration = 10;

	//Logo Startup Sound
	sf::SoundBuffer logoSoundBuffer;

	logoSoundBuffer.loadFromFile("Audio/violin.wav");
	
	sf::Sound logoSound;
	logoSound.setBuffer(logoSoundBuffer);
	logoSound.play();

	sf::Clock logoSoundClock;
	int logoSoundDuration = 8;

	bool logoDone = false;

	sf::Clock clock;

	

	//GAME LOOP
	while (window.isOpen())
	{
		//PLAYER
		sf::FloatRect playerBounds = player.getGlobalBounds();

		//SNOW PLATFORMS
		sf::FloatRect snowP1Bounds = snowP1.getGlobalBounds();
		sf::FloatRect snowP4Bounds = snowP4.getGlobalBounds();

		//METAL PLATFORMS
		sf::FloatRect dMetalP1Bounds = dMetalP1.getGlobalBounds();
		sf::FloatRect dMetalP2Bounds = dMetalP2.getGlobalBounds();
		sf::FloatRect sMetalBounds = sMetalP.getGlobalBounds();

		//CHISELED PLATFORMS
		sf::FloatRect chis1Bounds = chis1.getGlobalBounds();
		sf::FloatRect chis2Bounds = chis2.getGlobalBounds();
		sf::FloatRect chis3Bounds = chis3.getGlobalBounds();
		sf::FloatRect chis4Bounds = chis4.getGlobalBounds();
		sf::FloatRect chis5Bounds = chis5.getGlobalBounds();
		sf::FloatRect chis6Bounds = chis6.getGlobalBounds();
		sf::FloatRect chis7Bounds = chis7.getGlobalBounds();
		sf::FloatRect chis8Bounds = chis8.getGlobalBounds();
		sf::FloatRect chis9Bounds = chis9.getGlobalBounds();

		//CLOUDS
		sf::FloatRect cloud1Bounds = cloud1.getGlobalBounds();
		sf::FloatRect cloud2Bounds = cloud2.getGlobalBounds();
		sf::FloatRect cloud3Bounds = cloud3.getGlobalBounds();
		sf::FloatRect cloud4Bounds = cloud4.getGlobalBounds();
		sf::FloatRect cloud5Bounds = cloud5.getGlobalBounds();
		sf::FloatRect cloud6Bounds = cloud6.getGlobalBounds();
		sf::FloatRect cloud7Bounds = cloud7.getGlobalBounds();
		sf::FloatRect cloud8Bounds = cloud8.getGlobalBounds();
		sf::FloatRect cloud9Bounds = cloud9.getGlobalBounds();
		sf::FloatRect cloud10Bounds = cloud10.getGlobalBounds();
		sf::FloatRect cloud11Bounds = cloud11.getGlobalBounds();
		sf::FloatRect cloud12Bounds = cloud12.getGlobalBounds();
		sf::FloatRect coinCloudBounds = coinCloud.getGlobalBounds();
		sf::FloatRect keyCloudBounds = keyCloud.getGlobalBounds();
		sf::FloatRect sCloud1Bounds = sCloud1.getGlobalBounds();
		sf::FloatRect sCloud2Bounds = sCloud2.getGlobalBounds();

		//SPIKES
		sf::FloatRect spike1Bounds = spike1.getGlobalBounds();
		sf::FloatRect spike2Bounds = spike2.getGlobalBounds();
		sf::FloatRect spike3Bounds = spike3.getGlobalBounds();
		sf::FloatRect spike4Bounds = spike4.getGlobalBounds();
		sf::FloatRect spike5Bounds = spike5.getGlobalBounds();
		sf::FloatRect spike6Bounds = spike6.getGlobalBounds();
		sf::FloatRect spike7Bounds = spike7.getGlobalBounds();
		sf::FloatRect spike8Bounds = spike8.getGlobalBounds();
		sf::FloatRect spike9Bounds = spike9.getGlobalBounds();
		sf::FloatRect spike10Bounds = spike10.getGlobalBounds();

		//RED ENEMY
		sf::FloatRect rEnemyBounds = rEnemy.getGlobalBounds();
		sf::FloatRect rEnemyBounds2 = rEnemy2.getGlobalBounds();
		sf::FloatRect rEnemyBounds3 = rEnemy3.getGlobalBounds();
		sf::FloatRect rEnemyBounds4 = rEnemy4.getGlobalBounds();
		sf::FloatRect rEnemyBounds5 = rEnemy5.getGlobalBounds();
		sf::FloatRect rEnemyBounds6 = rEnemy6.getGlobalBounds();
	
		sf::FloatRect chisTrio2Bounds = chisTrio2.getGlobalBounds();
		sf::FloatRect chisTrio3Bounds = chisTrio3.getGlobalBounds();

		//KEY CHECKS
		int keyforLevel3 = 0;

		//PLAYER CAMERA/ VIEW
		sf::Vector2f playerPosition = player.getPosition();

		// ADJUST THE VIEW POSITION TO FOLLOW THE PLAYER WITHIN THE WORLD BOUNDS
		sf::Vector2f viewCenter = playerPosition;

		//CLAMPS THE VIEW WITHIN WORLD BOUNDS
		sf::Vector2f viewHalfSize = view.getSize() / 2.0f;
		viewCenter.x = std::max(viewCenter.x, viewHalfSize.x);
		viewCenter.y = std::max(viewCenter.y, viewHalfSize.y);
		viewCenter.x = std::min(viewCenter.x, 1920 - viewHalfSize.x);
		viewCenter.y = std::min(viewCenter.y, 1080 - viewHalfSize.y);
		view.setCenter(viewCenter);

		sf::Vector2f endViewCenter = playerPosition;

		sf::Vector2f endViewHalfSize = endView.getSize() / 2.0f;
		endViewCenter.x = std::max(endViewCenter.x, endViewHalfSize.x);
		endViewCenter.y = std::max(endViewCenter.y, endViewHalfSize.y);
		endViewCenter.x = std::min(endViewCenter.x, 1920 - endViewHalfSize.x);
		endViewCenter.y = std::min(endViewCenter.y, 1080 - endViewHalfSize.y);
		endView.setCenter(endViewCenter);

		//Event Variable
		sf::Event ev;

		//Poll Events
		while (window.pollEvent(ev))
		{
			if (ev.type == sf::Event::Closed)
			{
				window.close();
			}
			else if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Escape)
			{
				window.close();
			}
			else if (menuActive && ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Y) {
				menuActive = false;
				currentLevel = 1;
				player.setPosition(snowP1.getPosition().x + 100, snowP1.getPosition().y + 50);
				bgMusic.stop();
				home.play();
			}
		}

		if (ev.type == sf::Event::MouseButtonPressed)
		{
			sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
			std::cout << "Mouse Clicked at Position: (" << mousePosition.x << ", " << mousePosition.y << ")" << std::endl;
		}
		sf::Font font;
		font.loadFromFile("Fonts/LeagueSpartan-SemiBold.ttf"); // Corrected font file path
		sf::Text l1text("In level 1", font, 30);
		

		if (!menuActive)
		{
			switch (currentLevel)
			{
			case 1:
				jumpVelocity = -10;
				player.setScale(2, 2);
				coins = 0;
				currentHealth = maxHealth;
				hasKey = false;

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
				{
					playerVelocityX = -5.f;
					isMoving = true;
					movingLeft = true;
					movingRight = false;
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
				{
					playerVelocityX = 5.f;
					isMoving = true;
					movingLeft = false;
					movingRight = true;
				}
				else
				{
					playerVelocityX = 0.f;
					isMoving = false;
					movingLeft = false;
					movingRight = false;
				}

				//PLAYER JUMP
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
				{
					if (!isJumping && jumpCount < maxJump)
					{
						isJumping = true;
						playerVelocityY = jumpVelocity;
						jumpCount++;
						frameCount = 0;

						jumpSound.play();
					}
				}
				else
				{
					isJumping = false;
				}

				playerVelocityY += gravity;
				player.move(playerVelocityX, playerVelocityY);

				if (player.getPosition().x < 0) {
					// Correct position to be exactly at the left boundary
					player.setPosition(0, player.getPosition().y);

					// If the player is moving left, stop horizontal movement
					if (playerVelocityX < 0) {
						playerVelocityX = 0.f;
					}
				}

				if (player.getPosition().x > 1920) {
					// Correct position to be exactly at the left boundary
					player.setPosition(1920, player.getPosition().y);

					// If the player is moving left, stop horizontal movement
					if (playerVelocityX > 1920) {
						playerVelocityX = 0.f;
					}
				}

				if (player.getPosition().y < 0) {
					// Correct position to be exactly at the left boundary
					player.setPosition(player.getPosition().x, 0);

					// If the player is moving left, stop horizontal movement
					if (playerVelocityY < 0) {
						playerVelocityY = 0.f;
					}
				}

				//FLOOR COLLISION
				if (player.getPosition().y >= 966.f)
				{
					player.setPosition(player.getPosition().x, 966.f);
					playerVelocityY = 0.f;
					jumpCount = 0;
				}
				if (player.getPosition().y == 966.f)
				{
					jumpCount = 0;
				}

				//-------------------------------------------------------------------------------------
				//ANIMATIONS

				//JUMPING ANIMATION
				if (isJumping)
				{
					player.setTextureRect(sf::IntRect(0, 0, 20, 24));
				}
				//LEFT MOVEMENT ANIMATION
				else if (movingLeft)
				{
					if (frameCount == switchFrame)
					{
						frameCount = 0;
						if (player.getTextureRect().left == 0)
							player.setTextureRect(sf::IntRect(24, 0, 20, 24));
						else
							player.setTextureRect(sf::IntRect(0, 0, 20, 24));
					}
					else
					{
						frameCount++;
					}
				}
				//RIGHT MOVEMENT ANIMATION
				else if (movingRight)
				{
					if (frameCount == switchFrame)
					{
						frameCount = 0;
						if (player.getTextureRect().left == 0)
						{
							player.setTextureRect(sf::IntRect(24, 0, 20, 24));
						}
						else
						{
							player.setTextureRect(sf::IntRect(0, 0, 20, 24));
						}
					}
					else
					{
						frameCount++;
					}
				}
				else
				{
					player.setTextureRect(sf::IntRect(24, 0, 20, 24));
				}

				//FLIPS THE SPRITE BASED ON DIRECTION
				if (movingLeft)
				{
					player.setScale(-2.f, 2.f);
				}
				else if (movingRight)
				{
					player.setScale(2.f, 2.f);
				}






				/*else if (playerBounds.left + playerBounds.width > window.getSize().x) {
					player.setPosition(window.getSize().x - playerBounds.width, player.getPosition().y);
				}*/

				//// Check top boundary
				//if (playerBounds.top < 0) {
				//	player.setPosition(player.getPosition().x, 0);
				//}
				//// Check bottom boundary
				//else if (playerBounds.top + playerBounds.height > window.getSize().y) {
				//	player.setPosition(player.getPosition().x, window.getSize().y - playerBounds.height);
				//}












				//-------------------------------------SPRING---------------------------------------------------------------//
				if (player.getGlobalBounds().intersects(spring1h.getGlobalBounds())) {
					if (!isSpringActivated && playerVelocityY > 0) {
						// Player jumps on the spring while moving downward, activate it
						isSpringActivated = true;
						playerVelocityY = -20.0f; // Adjust the vertical force as needed
						spring1h.setTextureRect(sf::IntRect(19, 0, 18, 14)); // Assuming second frame starts at x=32
						jumpSound.play();
					}
				}
				else {
					isSpringActivated = false;
					spring1h.setTextureRect(sf::IntRect(0, 0, 18, 14));
				}
				
				if (player.getGlobalBounds().intersects(spring2h.getGlobalBounds())) {
					if (!isSpringActivated && playerVelocityY > 0) {
						// Player jumps on the spring while moving downward, activate it
						isSpringActivated = true;
						playerVelocityY = -25.0f; // Adjust the vertical force as needed
						spring2h.setTextureRect(sf::IntRect(19, 0, 18, 14)); // Assuming second frame starts at x=32
						jumpSound.play();
					}
				}
				else {
					isSpringActivated = false;
					spring2h.setTextureRect(sf::IntRect(0, 0, 18, 14));
				}

				if (player.getGlobalBounds().intersects(spring3h.getGlobalBounds())) {
					if (!isSpringActivated && playerVelocityY > 0) {
						// Player jumps on the spring while moving downward, activate it
						isSpringActivated = true;
						playerVelocityY = -27.0f; // Adjust the vertical force as needed
						spring3h.setTextureRect(sf::IntRect(19, 0, 18, 14)); // Assuming second frame starts at x=32
						jumpSound.play();
					}
				}
				else {
					isSpringActivated = false;
					spring3h.setTextureRect(sf::IntRect(0, 0, 18, 14));
				}

				if (player.getGlobalBounds().intersects(spring4h.getGlobalBounds())) {
					if (!isSpringActivated && playerVelocityY > 0) {
						// Player jumps on the spring while moving downward, activate it
						isSpringActivated = true;
						playerVelocityY = -30.0f; // Adjust the vertical force as needed
						spring4h.setTextureRect(sf::IntRect(19, 0, 18, 14)); // Assuming second frame starts at x=32
						jumpSound.play();
					}
				}
				else {
					isSpringActivated = false;
					spring4h.setTextureRect(sf::IntRect(0, 0, 18, 14));
				}

				if (playerBounds.intersects(cloud1h.getGlobalBounds()))
				{
					// Check for downward collision (player is moving downwards)
					if (playerVelocityY > 0)
					{
						if (player.getPosition().y - playerBounds.height / 2 < cloud1h.getPosition().y)
						{
							// Calculate the new player position
							float newYc1h = cloud1h.getPosition().y - playerBounds.height / 2;

							// Adjust player position and velocity
							player.setPosition(player.getPosition().x, newYc1h);
							playerVelocityY = 0.f;
							jumpCount = 0;
						}
					}
				}

				if (playerBounds.intersects(cloud2h.getGlobalBounds()))
				{
					// Check for downward collision (player is moving downwards)
					if (playerVelocityY > 0)
					{
						if (player.getPosition().y - playerBounds.height / 2 < cloud2h.getPosition().y)
						{
							// Calculate the new player position
							float newYc2h = cloud2h.getPosition().y - playerBounds.height / 2;

							// Adjust player position and velocity
							player.setPosition(player.getPosition().x, newYc2h);
							playerVelocityY = 0.f;
							jumpCount = 0;
						}
					}
				}

				if (playerBounds.intersects(cloud3h.getGlobalBounds()))
				{
					// Check for downward collision (player is moving downwards)
					if (playerVelocityY > 0)
					{
						if (player.getPosition().y - playerBounds.height / 2 < cloud3h.getPosition().y)
						{
							// Calculate the new player position
							float newYc3h = cloud3h.getPosition().y - playerBounds.height / 2;

							// Adjust player position and velocity
							player.setPosition(player.getPosition().x, newYc3h);
							playerVelocityY = 0.f;
							jumpCount = 0;
						}
					}
				}

				if (playerBounds.intersects(cloud4h.getGlobalBounds()))
				{
					// Check for downward collision (player is moving downwards)
					if (playerVelocityY > 0)
					{
						if (player.getPosition().y - playerBounds.height / 2 < cloud4h.getPosition().y)
						{
							// Calculate the new player position
							float newYc4h = cloud4h.getPosition().y - playerBounds.height / 2;

							// Adjust player position and velocity
							player.setPosition(player.getPosition().x, newYc4h);
							playerVelocityY = 0.f;
							jumpCount = 0;
						}
					}
				}

				if (playerBounds.intersects(door1h.getGlobalBounds()) && haskeyLevel1)
				{
					currentLevel = 2;
					player.setPosition(snowP1.getPosition().x + 50, snowP1.getPosition().y - 150);
					snow.play();
					home.stop();
				}
				
				if (playerBounds.intersects(door2h.getGlobalBounds()) && hasKeyLevel2 == true)
				{
						currentLevel = 3;
						player.setPosition(99, 888);
						desert.play();
						home.stop();
				}

				if (playerBounds.intersects(door3h.getGlobalBounds()) && hasKeyLevel3 == true)
				{
					currentLevel = 4;
					player.setPosition(99, 888);
					home.stop();
					jungle.play();
				}

				if (playerBounds.intersects(door4h.getGlobalBounds()) && hasKeyLevel4 == true)
				{
					currentLevel = 5;
					player.setPosition(0, 1000);
					home.stop();
					endingMusic.play();
				}

				window.clear();
				
				window.setView(view);
				window.draw(homeLevelBg);
				window.draw(aKeyh);
				window.draw(dKeyh);
				window.draw(wKeyh1);
				window.draw(wKeyh2);
				window.draw(coinh);
				window.draw(keyh);

				//DRAW FRIEND
				if (level1Friendbool == true)
				{
					window.draw(level1Friend);
				}
				if (level2Friendbool == true)
				{
					window.draw(level2Friend);
				}
				if (level3Friendbool == true)
				{
					window.draw(level3Friend);
				}
				if (level4Friendbool == true)
				{
					window.draw(level4Friend);
				}
				

				//DRAW DIALOGUE
				if (playerBounds.intersects(level1Friend.getGlobalBounds()) && level1Friendbool == true)
				{
					window.draw(frDialogue1);
				}
				if (playerBounds.intersects(level2Friend.getGlobalBounds()) && level2Friendbool == true)
				{
					window.draw(frDialogue2);
				}
				if (playerBounds.intersects(level3Friend.getGlobalBounds()) && level3Friendbool == true)
				{
					window.draw(frDialogue3);
				}
				if (playerBounds.intersects(level4Friend.getGlobalBounds()) && level4Friendbool == true)
				{
					window.draw(frDialogue4);
				}
				
				
				window.draw(snowman1h);
				window.draw(snowman2h);
				window.draw(spring1h);
				window.draw(spring2h);
				window.draw(spring3h);
				window.draw(spring4h);
				window.draw(num1h);
				window.draw(num2h);
				window.draw(num3h);
				window.draw(num4h);
				window.draw(cloud1h);
				window.draw(cloud2h);
				window.draw(cloud3h);
				window.draw(cloud4h);
				window.draw(door1h);
				window.draw(door2h);
				window.draw(door3h);
				window.draw(door4h);
				window.draw(doorNum1h);
				window.draw(doorNum2h);
				window.draw(doorNum3h);
				window.draw(doorNum4h);
				window.draw(snowP4h);
				window.draw(snowP3h);
				window.draw(snowP2h);
				window.draw(snowP1h);
				window.draw(text1);
				window.draw(text2);
				window.draw(text3);
				window.draw(text4);
				window.draw(text5);
				window.draw(text6);
				window.draw(text7);
				window.draw(text11);
				window.draw(text12);

				if (playerBounds.intersects(snowman1h.getGlobalBounds()))
				{
					window.draw(dialogue1h);
					window.draw(text8);
					
					
				}
				if (playerBounds.intersects(snowman2h.getGlobalBounds()))
				{
					window.draw(dialogue2h);
					window.draw(text10);
				}
				
				window.draw(player);
				window.display();
				
				break;
			case 2:
				//ENTITY GLOBAL BOUNDS

				// SETS THE VIEW FOR THE WINDOW
				window.setView(view);

				//PLAYER LEFT AND RIGHT MOVEMENT

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
				{
					playerVelocityX = -5.f;
					isMoving = true;
					movingLeft = true;
					movingRight = false;
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
				{
					playerVelocityX = 5.f;
					isMoving = true;
					movingLeft = false;
					movingRight = true;
				}
				else
				{
					playerVelocityX = 0.f;
					isMoving = false;
					movingLeft = false;
					movingRight = false;
				}

				//PLAYER JUMP
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
				{
					if (!isJumping && jumpCount < maxJump)
					{
						isJumping = true;
						playerVelocityY = jumpVelocity;
						jumpCount++;
						frameCount = 0;

						jumpSound.play();
					}
				}
				else
				{
					isJumping = false;
				}

				playerVelocityY += gravity;
				player.move(playerVelocityX, playerVelocityY);

				if (player.getPosition().x < 0) {
					// Correct position to be exactly at the left boundary
					player.setPosition(0, player.getPosition().y);

					// If the player is moving left, stop horizontal movement
					if (playerVelocityX < 0) {
						playerVelocityX = 0.f;
					}
				}

				if (player.getPosition().x > 1920) {
					// Correct position to be exactly at the left boundary
					player.setPosition(1920, player.getPosition().y);

					// If the player is moving left, stop horizontal movement
					if (playerVelocityX > 1920) {
						playerVelocityX = 0.f;
					}
				}

				if (player.getPosition().y < 0) {
					// Correct position to be exactly at the left boundary
					player.setPosition(player.getPosition().x, 0);

					// If the player is moving left, stop horizontal movement
					if (playerVelocityY < 0) {
						playerVelocityY = 0.f;
					}
				}

				//FLOOR COLLISION
				if (player.getPosition().y >= 1018.f)
				{
					player.setPosition(player.getPosition().x, 1018.f);
					playerVelocityY = 0.f;
					jumpCount = 0;
				}
				if (player.getPosition().y == 1018.f)
				{
					jumpCount = 0;
				}

				//-------------------------------------------------------------------------------------
				//ANIMATIONS

				//JUMPING ANIMATION
				if (isJumping)
				{
					player.setTextureRect(sf::IntRect(0, 0, 20, 24));
				}
				//LEFT MOVEMENT ANIMATION
				else if (movingLeft)
				{
					if (frameCount == switchFrame)
					{
						frameCount = 0;
						if (player.getTextureRect().left == 0)
							player.setTextureRect(sf::IntRect(24, 0, 20, 24));
						else
							player.setTextureRect(sf::IntRect(0, 0, 20, 24));
					}
					else
					{
						frameCount++;
					}
				}
				//RIGHT MOVEMENT ANIMATION
				else if (movingRight)
				{
					if (frameCount == switchFrame)
					{
						frameCount = 0;
						if (player.getTextureRect().left == 0)
						{
							player.setTextureRect(sf::IntRect(24, 0, 20, 24));
						}
						else
						{
							player.setTextureRect(sf::IntRect(0, 0, 20, 24));
						}
					}
					else
					{
						frameCount++;
					}
				}
				else
				{
					player.setTextureRect(sf::IntRect(24, 0, 20, 24));
				}

				//FLIPS THE SPRITE BASED ON DIRECTION
				if (movingLeft)
				{
					player.setScale(-2.f, 2.f);
				}
				else if (movingRight)
				{
					player.setScale(2.f, 2.f);
				}

				if (playerBounds.intersects(snowP1Bounds))
				{
					// Check for downward collision (player is moving downwards)
					if (playerVelocityY > 0)
					{
						if (player.getPosition().y - playerBounds.height / 2 < snowP1.getPosition().y)
						{
							// Calculate the new player position
							float newYP1 = snowP1.getPosition().y - playerBounds.height / 2;

							// Adjust player position and velocity
							player.setPosition(player.getPosition().x, newYP1);
							playerVelocityY = 0.f;
							jumpCount = 0;
						}
					}
				}

				//SNOW P1 SIDE COLLISION CHECKS

				if (playerBounds.intersects(sf::FloatRect(snowP1Bounds.left, snowP1Bounds.top, 0.5f, snowP1Bounds.height)))
				{
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && player.getPosition().x < snowP1Bounds.left && !hasCollidedWithLeftSide) //LEFT SIDE
					{
						player.setPosition(snowP1Bounds.left - playerBounds.width / 2.f, player.getPosition().y);
						hasCollidedWithLeftSide = true;
					}
					hasCollidedWithRightSide = false;
				}
				else if (playerBounds.intersects(sf::FloatRect(snowP1Bounds.left + snowP1Bounds.width, snowP1Bounds.top, 1.f, snowP1Bounds.height)))
				{
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && player.getPosition().x > snowP1Bounds.left + snowP1Bounds.width && !hasCollidedWithRightSide)
					{
						player.setPosition(snowP1Bounds.left + snowP1Bounds.width + playerBounds.width / 2.f, player.getPosition().y);
						hasCollidedWithRightSide = true;
					}
					hasCollidedWithLeftSide = false;
				}
				else {
					hasCollidedWithLeftSide = false;
					hasCollidedWithRightSide = false;
				}

				if (playerBounds.intersects(snowP4Bounds))
				{
					// Check for downward collision (player is moving downwards)
					if (playerVelocityY > 0)
					{
						if (player.getPosition().y - playerBounds.height / 2 < snowP4.getPosition().y)
						{
							// Calculate the new player position
							float newY = snowP4.getPosition().y - playerBounds.height / 2;

							// Adjust player position and velocity
							player.setPosition(player.getPosition().x, newY);
							playerVelocityY = 0.f;
							jumpCount = 0;
						}
					}
				}

				//SNOW P4 SIDE COLLISION CHECKS

				if (playerBounds.intersects(sf::FloatRect(snowP4Bounds.left, snowP4Bounds.top, 0.5f, snowP4Bounds.height)))
				{
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && player.getPosition().x < snowP4Bounds.left && !hasCollidedWithLeftSide)
					{
						player.setPosition(snowP4Bounds.left - playerBounds.width / 2.f, player.getPosition().y);
						hasCollidedWithLeftSide = true;
					}
					hasCollidedWithRightSide = false;
				}
				else if (playerBounds.intersects(sf::FloatRect(snowP4Bounds.left + snowP4Bounds.width, snowP4Bounds.top, 1.f, snowP4Bounds.height)))
				{
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && player.getPosition().x > snowP4Bounds.left + snowP4Bounds.width && !hasCollidedWithRightSide)
					{
						player.setPosition(snowP1Bounds.left + snowP1Bounds.width + playerBounds.width / 2.f, player.getPosition().y);
						hasCollidedWithRightSide = true;
					}
					hasCollidedWithLeftSide = false;
				}
				else {
					hasCollidedWithLeftSide = false;
					hasCollidedWithRightSide = false;
				}

				//METAL PLATFORM 1 PLATFORM COLLISION CHECK
				if (playerBounds.intersects(dMetalP1Bounds))
				{
					if (playerVelocityY > 0)
					{
						if (player.getPosition().y < dMetalP1.getPosition().y)
						{
							player.setPosition(player.getPosition().x, dMetalP1.getPosition().y - playerBounds.height / 2);
							playerVelocityY = 0.f;
							jumpCount = 0;
						}
					}
				}

				//METAL PLATFORM 2 PLATFORM COLLISION CHECK
				if (playerBounds.intersects(dMetalP2Bounds))
				{
					if (playerVelocityY > 0)
					{
						if (player.getPosition().y < dMetalP2.getPosition().y)
						{
							player.setPosition(player.getPosition().x, dMetalP2.getPosition().y - playerBounds.height / 2);
							playerVelocityY = 0.f;
							jumpCount = 0;
						}
					}
				}

				//SINGLE METAL PLATFORM COLLISION CHECK
				if (playerBounds.intersects(sMetalBounds))
				{
					if (playerVelocityY > 0)
					{
						if (player.getPosition().y < sMetalP.getPosition().y)
						{
							player.setPosition(player.getPosition().x, sMetalP.getPosition().y - playerBounds.height / 2);
							playerVelocityY = 0.f;
							jumpCount = 0;
						}
					}
				}

				//CHISELED PLATFORM 1 COLLISION CHECK
				if (playerBounds.intersects(chis1Bounds))
				{
					if (playerVelocityY > 0)
					{
						if (player.getPosition().y < chis1.getPosition().y)
						{
							player.setPosition(player.getPosition().x, chis1.getPosition().y - playerBounds.height / 2);
							playerVelocityY = 0.f;
							jumpCount = 0;
						}
					}
				}

				//CHISELED PLATFORM 1 HEAD COLLISION CHECK
				if (playerBounds.intersects(sf::FloatRect(chis1Bounds.left, chis1Bounds.top + chis1Bounds.height - 1, chis1Bounds.width, 1.f)))
				{
					if (playerVelocityY < 0) {
						player.setPosition(player.getPosition().x, chis1Bounds.top + chis1Bounds.height);
						playerVelocityY = 10.f;
						isJumping = false;
						jumpCount = 0;
					}
				}

				if (playerBounds.intersects(sf::FloatRect(chis2Bounds.left, chis2Bounds.top + chis2Bounds.height - 1, chis2Bounds.width, 1.f))) {
					// Player intersects with the bottom side of the platform

					// Check if the player is moving upwards (jumping)
					if (playerVelocityY < 0) {
						// Adjust player's position only if moving upwards
						player.setPosition(player.getPosition().x, chis2Bounds.top + chis2Bounds.height);
						playerVelocityY = 0.f; // Set vertical velocity to zero to stop upward movement
						isJumping = false; // Reset jump state
						jumpCount = 0; // Reset jump count
					}
				}

				if (playerBounds.intersects(chis2Bounds))
				{
					if (playerVelocityY > 0)
					{
						if (player.getPosition().y < chis2.getPosition().y)
						{
							player.setPosition(player.getPosition().x, chis2.getPosition().y - playerBounds.height / 2);
							playerVelocityY = 0.f;
							jumpCount = 0;
						}
					}
				}

				//----------------------------------------------------------------------------------------------------------------------------------
				//Clouds

				if (playerBounds.intersects(cloud1Bounds))
				{
					if (playerVelocityY > 0)
					{
						if (player.getPosition().y - playerBounds.height / 2 < cloud1.getPosition().y)
						{
							// Calculate the new player position
							float newYcloud1 = cloud1.getPosition().y - playerBounds.height / 2;

							// Adjust player position and velocity
							player.setPosition(player.getPosition().x, newYcloud1);
							playerVelocityY = 0.f;
							jumpCount = 0;
						}
					}
				}

				if (playerBounds.intersects(cloud2Bounds))
				{
					if (playerVelocityY > 0)
					{
						if (player.getPosition().y - playerBounds.height / 2 < cloud2.getPosition().y)
						{
							// Calculate the new player position
							float newYcloud2 = cloud2.getPosition().y - playerBounds.height / 2;

							// Adjust player position and velocity
							player.setPosition(player.getPosition().x, newYcloud2);
							playerVelocityY = 0.f;
							jumpCount = 0;
						}
					}
				}

				if (playerBounds.intersects(cloud3Bounds))
				{
					if (playerVelocityY > 0)
					{
						if (player.getPosition().y - playerBounds.height / 2 < cloud3.getPosition().y)
						{
							// Calculate the new player position
							float newYcloud3 = cloud3.getPosition().y - playerBounds.height / 2;

							// Adjust player position and velocity
							player.setPosition(player.getPosition().x, newYcloud3);
							playerVelocityY = 0.f;
							jumpCount = 0;
						}
					}
				}

				if (playerBounds.intersects(cloud4Bounds))
				{
					if (playerVelocityY > 0)
					{
						if (player.getPosition().y - playerBounds.height / 2 < cloud4.getPosition().y)
						{
							// Calculate the new player position
							float newYcloud4 = cloud4.getPosition().y - playerBounds.height / 2;

							// Adjust player position and velocity
							player.setPosition(player.getPosition().x, newYcloud4);
							playerVelocityY = 0.f;
							jumpCount = 0;
						}
					}
				}

				if (playerBounds.intersects(cloud5Bounds))
				{
					if (playerVelocityY > 0)
					{
						if (player.getPosition().y - playerBounds.height / 2 < cloud5.getPosition().y)
						{
							// Calculate the new player position
							float newYcloud5 = cloud5.getPosition().y - playerBounds.height / 2;

							// Adjust player position and velocity
							player.setPosition(player.getPosition().x, newYcloud5);
							playerVelocityY = 0.f;
							jumpCount = 0;
						}
					}
				}

				if (playerBounds.intersects(cloud6Bounds))
				{
					if (playerVelocityY > 0)
					{
						if (player.getPosition().y - playerBounds.height / 2 < cloud6.getPosition().y)
						{
							// Calculate the new player position
							float newYcloud6 = cloud6.getPosition().y - playerBounds.height / 2;

							// Adjust player position and velocity
							player.setPosition(player.getPosition().x, newYcloud6);
							playerVelocityY = 0.f;
							jumpCount = 0;
						}
					}
				}

				if (playerBounds.intersects(cloud7Bounds))
				{
					if (playerVelocityY > 0)
					{
						if (player.getPosition().y - playerBounds.height / 2 < cloud7.getPosition().y)
						{
							// Calculate the new player position
							float newYcloud7 = cloud7.getPosition().y - playerBounds.height / 2;

							// Adjust player position and velocity
							player.setPosition(player.getPosition().x, newYcloud7);
							playerVelocityY = 0.f;
							jumpCount = 0;
						}
					}
				}

				if (playerBounds.intersects(cloud8Bounds))
				{
					if (playerVelocityY > 0)
					{
						if (player.getPosition().y - playerBounds.height / 2 < cloud8.getPosition().y)
						{
							// Calculate the new player position
							float newYcloud8 = cloud8.getPosition().y - playerBounds.height / 2;

							// Adjust player position and velocity
							player.setPosition(player.getPosition().x, newYcloud8);
							playerVelocityY = 0.f;
							jumpCount = 0;
						}
					}
				}

				if (playerBounds.intersects(cloud9Bounds))
				{
					if (playerVelocityY > 0)
					{
						if (player.getPosition().y - playerBounds.height / 2 < cloud9.getPosition().y)
						{
							// Calculate the new player position
							float newYcloud9 = cloud9.getPosition().y - playerBounds.height / 2;

							// Adjust player position and velocity
							player.setPosition(player.getPosition().x, newYcloud9);
							playerVelocityY = 0.f;
							jumpCount = 0;
						}
					}
				}

				if (playerBounds.intersects(cloud10Bounds))
				{
					if (playerVelocityY > 0)
					{
						if (player.getPosition().y - playerBounds.height / 2 < cloud10.getPosition().y)
						{
							// Calculate the new player position
							float newYcloud10 = cloud10.getPosition().y - playerBounds.height / 2;

							// Adjust player position and velocity
							player.setPosition(player.getPosition().x, newYcloud10);
							playerVelocityY = 0.f;
							jumpCount = 0;
						}
					}
				}

				if (playerBounds.intersects(cloud11Bounds))
				{
					if (playerVelocityY > 0)
					{
						if (player.getPosition().y - playerBounds.height / 2 < cloud11.getPosition().y)
						{
							// Calculate the new player position
							float newYcloud11 = cloud11.getPosition().y - playerBounds.height / 2;

							// Adjust player position and velocity
							player.setPosition(player.getPosition().x, newYcloud11);
							playerVelocityY = 0.f;
							jumpCount = 0;
						}
					}
				}

				if (playerBounds.intersects(cloud12Bounds))
				{
					if (playerVelocityY > 0)
					{
						if (player.getPosition().y - playerBounds.height / 2 < cloud12.getPosition().y)
						{
							// Calculate the new player position
							float newYcloud12 = cloud12.getPosition().y - playerBounds.height / 2;

							// Adjust player position and velocity
							player.setPosition(player.getPosition().x, newYcloud12);
							playerVelocityY = 0.f;
							jumpCount = 0;
						}
					}
				}

				if (playerBounds.intersects(coinCloudBounds))
				{
					if (playerVelocityY > 0)
					{
						if (player.getPosition().y - playerBounds.height / 2 < coinCloud.getPosition().y)
						{
							// Calculate the new player position
							float newYcoinCloud = coinCloud.getPosition().y - playerBounds.height / 2;

							// Adjust player position and velocity
							player.setPosition(player.getPosition().x, newYcoinCloud);
							playerVelocityY = 0.f;
							jumpCount = 0;
						}
					}
				}

				if (playerBounds.intersects(keyCloudBounds))
				{
					if (playerVelocityY > 0)
					{
						if (player.getPosition().y - playerBounds.height / 2 < keyCloud.getPosition().y)
						{
							// Calculate the new player position
							float newYkeyCloud = keyCloud.getPosition().y - playerBounds.height / 2;

							// Adjust player position and velocity
							player.setPosition(player.getPosition().x, newYkeyCloud);
							playerVelocityY = 0.f;
							jumpCount = 0;
						}
					}
				}

				if (playerBounds.intersects(sCloud1Bounds))
				{
					if (playerVelocityY > 0)
					{
						if (player.getPosition().y - playerBounds.height / 2 < sCloud1.getPosition().y)
						{
							// Calculate the new player position
							float newYsCloud1 = sCloud1.getPosition().y - playerBounds.height / 2;

							// Adjust player position and velocity
							player.setPosition(player.getPosition().x, newYsCloud1);
							playerVelocityY = 0.f;
							jumpCount = 0;
						}
					}
				}

				if (playerBounds.intersects(sCloud2Bounds))
				{
					if (playerVelocityY > 0)
					{
						if (player.getPosition().y - playerBounds.height / 2 < sCloud2.getPosition().y)
						{
							// Calculate the new player position
							float newYsCloud2 = sCloud2.getPosition().y - playerBounds.height / 2;

							// Adjust player position and velocity
							player.setPosition(player.getPosition().x, newYsCloud2);
							playerVelocityY = 0.f;
							jumpCount = 0;
						}
					}
				}

				//------------------------------------------------------------------------------------------------------------------------------
				//Chiseled Blocks

				if (playerBounds.intersects(chis3Bounds))
				{
					if (playerVelocityY > 0)
					{
						if (player.getPosition().y < chis3.getPosition().y)
						{
							player.setPosition(player.getPosition().x, chis3.getPosition().y - playerBounds.height / 2);
							playerVelocityY = 0.f;
							jumpCount = 0;
						}
					}
				}

				// Assume playerBounds and chis1Bounds are the bounding boxes of the player and platform respectively

				if (playerBounds.intersects(sf::FloatRect(chis3Bounds.left, chis3Bounds.top + chis3Bounds.height - 1, chis3Bounds.width, 1.f))) {
					// Player intersects with the bottom side of the platform

					// Check if the player is moving upwards (jumping)
					if (playerVelocityY < 0) {
						// Adjust player's position only if moving upwards
						player.setPosition(player.getPosition().x, chis3Bounds.top + chis3Bounds.height);
						playerVelocityY = 0.f; // Set vertical velocity to zero to stop upward movement
						isJumping = false; // Reset jump state
						jumpCount = 0; // Reset jump count
					}
				}

				if (playerBounds.intersects(chis4Bounds))
				{
					if (playerVelocityY > 0)
					{
						if (player.getPosition().y < chis4.getPosition().y)
						{
							player.setPosition(player.getPosition().x, chis4.getPosition().y - playerBounds.height / 2);
							playerVelocityY = 0.f;
							jumpCount = 0;
						}
					}
				}

				// Assume playerBounds and chis1Bounds are the bounding boxes of the player and platform respectively

				if (playerBounds.intersects(sf::FloatRect(chis4Bounds.left, chis4Bounds.top + chis4Bounds.height - 1, chis4Bounds.width, 1.f))) {
					// Player intersects with the bottom side of the platform

					// Check if the player is moving upwards (jumping)
					if (playerVelocityY < 0) {
						// Adjust player's position only if moving upwards
						player.setPosition(player.getPosition().x, chis4Bounds.top + chis4Bounds.height);
						playerVelocityY = 0.f; // Set vertical velocity to zero to stop upward movement
						isJumping = false; // Reset jump state
						jumpCount = 0; // Reset jump count
					}
				}

				if (playerBounds.intersects(chis5Bounds))
				{
					if (playerVelocityY > 0)
					{
						if (player.getPosition().y < chis5.getPosition().y)
						{
							player.setPosition(player.getPosition().x, chis5.getPosition().y - playerBounds.height / 2);
							playerVelocityY = 0.f;
							jumpCount = 0;
						}
					}
				}

				if (playerBounds.intersects(sf::FloatRect(chis5Bounds.left, chis5Bounds.top, 0.5f, chis5Bounds.height))) {
					// Player intersects with the left side of the snow1 platform
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && player.getPosition().x < chis5Bounds.left && !hasCollidedWithLeftSide) {
						// Adjust player's position only if trying to move right and hasn't collided before
						player.setPosition(chis5Bounds.left - chis5Bounds.width / 2.f, player.getPosition().y);
						hasCollidedWithLeftSide = true;
					}
					// Reset the flag for right side collision
					hasCollidedWithRightSide = false;
				}
				else if (playerBounds.intersects(sf::FloatRect(chis5Bounds.left + chis5Bounds.width, chis5Bounds.top, 1.f, chis5Bounds.height))) {
					// Player intersects with the right side of the snow1 platform
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && player.getPosition().x > chis5Bounds.left + chis5Bounds.width && !hasCollidedWithRightSide) {
						// Adjust player's position only if trying to move left and hasn't collided before
						player.setPosition(chis5Bounds.left + chis5Bounds.width + playerBounds.width / 2.f, player.getPosition().y);
						hasCollidedWithRightSide = true;
					}
					// Reset the flag for left side collision
					hasCollidedWithLeftSide = false;
				}
				else {
					hasCollidedWithLeftSide = false; // Reset the flag for left side collision
					hasCollidedWithRightSide = false; // Reset the flag for right side collision
				}

				// Assume playerBounds and chis1Bounds are the bounding boxes of the player and platform respectively

				if (playerBounds.intersects(sf::FloatRect(chis5Bounds.left, chis5Bounds.top + chis5Bounds.height - 1, chis5Bounds.width, 1.f))) {
					// Player intersects with the bottom side of the platform

					// Check if the player is moving upwards (jumping)
					if (playerVelocityY < 0) {
						// Adjust player's position only if moving upwards
						player.setPosition(player.getPosition().x, chis5Bounds.top + chis5Bounds.height);
						playerVelocityY = 0.f; // Set vertical velocity to zero to stop upward movement
						isJumping = false; // Reset jump state
						jumpCount = 0; // Reset jump count
					}
				}

				if (playerBounds.intersects(chis6Bounds))
				{
					if (playerVelocityY > 0)
					{
						if (player.getPosition().y < chis6.getPosition().y)
						{
							player.setPosition(player.getPosition().x, chis6.getPosition().y - playerBounds.height / 2);
							playerVelocityY = 0.f;
							jumpCount = 0;
						}
					}
				}

				// Assume playerBounds and chis1Bounds are the bounding boxes of the player and platform respectively

				if (playerBounds.intersects(sf::FloatRect(chis6Bounds.left, chis6Bounds.top + chis6Bounds.height - 1, chis6Bounds.width, 1.f))) {
					// Player intersects with the bottom side of the platform

					// Check if the player is moving upwards (jumping)
					if (playerVelocityY < 0) {
						// Adjust player's position only if moving upwards
						player.setPosition(player.getPosition().x, chis6Bounds.top + chis6Bounds.height);
						playerVelocityY = 0.f; // Set vertical velocity to zero to stop upward movement
						isJumping = false; // Reset jump state
						jumpCount = 0; // Reset jump count
					}
				}

				if (playerBounds.intersects(chis7Bounds))
				{
					if (playerVelocityY > 0)
					{
						if (player.getPosition().y < chis7.getPosition().y)
						{
							player.setPosition(player.getPosition().x, chis7.getPosition().y - playerBounds.height / 2);
							playerVelocityY = 0.f;
							jumpCount = 0;
						}
					}
				}

				// Assume playerBounds and chis1Bounds are the bounding boxes of the player and platform respectively

				if (playerBounds.intersects(sf::FloatRect(chis7Bounds.left, chis7Bounds.top + chis7Bounds.height - 1, chis7Bounds.width, 1.f))) {
					// Player intersects with the bottom side of the platform

					// Check if the player is moving upwards (jumping)
					if (playerVelocityY < 0) {
						// Adjust player's position only if moving upwards
						player.setPosition(player.getPosition().x, chis7Bounds.top + chis7Bounds.height);
						playerVelocityY = 0.f; // Set vertical velocity to zero to stop upward movement
						isJumping = false; // Reset jump state
						jumpCount = 0; // Reset jump count
					}
				}

				if (playerBounds.intersects(chis8Bounds))
				{
					if (playerVelocityY > 0)
					{
						if (player.getPosition().y < chis8.getPosition().y)
						{
							player.setPosition(player.getPosition().x, chis8.getPosition().y - playerBounds.height / 2);
							playerVelocityY = 0.f;
							jumpCount = 0;
						}
					}
				}

				// Assume playerBounds and chis1Bounds are the bounding boxes of the player and platform respectively

				if (playerBounds.intersects(sf::FloatRect(chis8Bounds.left, chis8Bounds.top + chis8Bounds.height - 1, chis8Bounds.width, 1.f))) {
					// Player intersects with the bottom side of the platform

					// Check if the player is moving upwards (jumping)
					if (playerVelocityY < 0) {
						// Adjust player's position only if moving upwards
						player.setPosition(player.getPosition().x, chis8Bounds.top + chis8Bounds.height);
						playerVelocityY = 0.f; // Set vertical velocity to zero to stop upward movement
						isJumping = false; // Reset jump state
						jumpCount = 0; // Reset jump count
					}
				}

				if (playerBounds.intersects(chis9Bounds))
				{
					if (playerVelocityY > 0)
					{
						if (player.getPosition().y < chis9.getPosition().y)
						{
							player.setPosition(player.getPosition().x, chis9.getPosition().y - playerBounds.height / 2);
							playerVelocityY = 0.f;
							jumpCount = 0;
						}
					}
				}

				// Assume playerBounds and chis1Bounds are the bounding boxes of the player and platform respectively

				if (playerBounds.intersects(sf::FloatRect(chis9Bounds.left, chis9Bounds.top + chis9Bounds.height - 1, chis9Bounds.width, 1.f))) {
					// Player intersects with the bottom side of the platform

					// Check if the player is moving upwards (jumping)
					if (playerVelocityY < 0) {
						// Adjust player's position only if moving upwards
						player.setPosition(player.getPosition().x, chis9Bounds.top + chis9Bounds.height);
						playerVelocityY = 0.f; // Set vertical velocity to zero to stop upward movement
						isJumping = false; // Reset jump state
						jumpCount = 0; // Reset jump count
					}
				}
				//-------------------------------------------------------------------------------------------------------------------------------
				//Spike
				if (playerBounds.intersects(spike1Bounds) && damageCooldown.getElapsedTime() > coolDownDuration)
				{
					playerVelocityY = -12.f;
					currentHealth--;

					spikeStabSound.play();

					blinkingTimer.restart();
					damageCooldown.restart();
				}

				if (playerBounds.intersects(spike2Bounds) && damageCooldown.getElapsedTime() > coolDownDuration)
				{
					playerVelocityY = -12.f;
					currentHealth--;

					spikeStabSound.play();

					blinkingTimer.restart();
					damageCooldown.restart();
				}

				if (playerBounds.intersects(spike3Bounds) && damageCooldown.getElapsedTime() > coolDownDuration)
				{
					playerVelocityY = -12.f;
					currentHealth--;

					spikeStabSound.play();

					blinkingTimer.restart();
					damageCooldown.restart();
				}

				if (playerBounds.intersects(spike4Bounds) && damageCooldown.getElapsedTime() > coolDownDuration)
				{
					playerVelocityY = -12.f;
					currentHealth--;

					spikeStabSound.play();

					blinkingTimer.restart();
					damageCooldown.restart();
				}

				/*if (playerBounds.intersects(spike5Bounds) && damageCooldown.getElapsedTime() > coolDownDuration)
				{
					playerVelocityY = -12.f;
					currentHealth--;

					spikeStabSound.play();

					blinkingTimer.restart();
					damageCooldown.restart();
				}*/

				if (playerBounds.intersects(spike6Bounds) && damageCooldown.getElapsedTime() > coolDownDuration)
				{
					playerVelocityY = -12.f;
					currentHealth--;

					spikeStabSound.play();

					blinkingTimer.restart();
					damageCooldown.restart();
				}

				if (playerBounds.intersects(spike7Bounds) && damageCooldown.getElapsedTime() > coolDownDuration)
				{
					playerVelocityY = -12.f;
					currentHealth--;

					spikeStabSound.play();

					blinkingTimer.restart();
					damageCooldown.restart();
				}

				if (playerBounds.intersects(spike8Bounds) && damageCooldown.getElapsedTime() > coolDownDuration)
				{
					playerVelocityY = -12.f;
					currentHealth--;

					spikeStabSound.play();

					blinkingTimer.restart();
					damageCooldown.restart();
				}

				if (playerBounds.intersects(spike9Bounds) && damageCooldown.getElapsedTime() > coolDownDuration)
				{
					playerVelocityY = -12.f;
					currentHealth--;

					spikeStabSound.play();

					blinkingTimer.restart();
					damageCooldown.restart();
				}

				if (playerBounds.intersects(spike10Bounds) && damageCooldown.getElapsedTime() > coolDownDuration)
				{
					playerVelocityY = -12.f;
					currentHealth--;

					spikeStabSound.play();

					blinkingTimer.restart();
					damageCooldown.restart();
				}


				//-------------------------------------------------------------------------------------------------------------------------------------
				//Enemy Blue

				enemyBlue.move(enemySpeed * enemyDirection, 0.f);

				if (enemyBlue.getPosition().x < leftBound || enemyBlue.getPosition().x > rightBound) {
					if (enemyBlue.getPosition().x < leftBound) {
						enemyDirection = 1.0f;  // Move to the right
						enemyBlue.setScale(-std::abs(enemyBlue.getScale().x), 2.0f);
					}
					else {
						enemyDirection = -1.0f;  // Move to the left

						enemyBlue.setScale(std::abs(enemyBlue.getScale().x), 2.0f);
					}
				}

				if (enemyFrameCount == enemySwitchFrame) {
					enemyFrameCount = 0;
					if (enemyBlue.getTextureRect().left == 0)
					{
						enemyBlue.setTextureRect(sf::IntRect(24, 0, 15, 14));
					}
					else
					{
						enemyBlue.setTextureRect(sf::IntRect(0, 0, 15, 14));
					}
				}
				else {
					enemyFrameCount++;
				}



				//-------------------------------------------------------------------------------------------------------------------
				enemyBlue2.move(enemySpeed2 * enemyDirection2, 0.f);


				if (enemyBlue2.getPosition().x < e2LeftBound || enemyBlue2.getPosition().x > e2RightBound) {
					if (enemyBlue2.getPosition().x < e2LeftBound) {
						enemyDirection2 = 1.0f;  // Move to the right
						enemyBlue2.setScale(-std::abs(enemyBlue2.getScale().x), 2.0f);
					}
					else {
						enemyDirection2 = -1.0f;  // Move to the left

						enemyBlue2.setScale(std::abs(enemyBlue2.getScale().x), 2.0f);
					}
				}

				if (enemyFrameCount2 == enemySwitchFrame2) {
					enemyFrameCount2 = 0;
					if (enemyBlue2.getTextureRect().left == 0)
						enemyBlue2.setTextureRect(sf::IntRect(24, 0, 15, 14));
					else
						enemyBlue2.setTextureRect(sf::IntRect(0, 0, 15, 14));
				}
				else {
					enemyFrameCount2++;
				}

				//
				////----------------------------------------------------------------------------------------------------------------------

				enemyBlue3.move(enemySpeed3 * enemyDirection3, 0.f);



				if (enemyBlue3.getPosition().x < e3LeftBound || enemyBlue3.getPosition().x > e3RightBound) {
					if (enemyBlue3.getPosition().x < e3LeftBound) {
						enemyDirection3 = 1.0f;  // Move to the right
						enemyBlue3.setScale(-std::abs(enemyBlue3.getScale().x), 2.0f);
					}
					else {
						enemyDirection3 = -1.0f;  // Move to the left

						enemyBlue3.setScale(std::abs(enemyBlue3.getScale().x), 2.0f);
					}
				}

				if (enemyFrameCount3 == enemySwitchFrame3) {
					enemyFrameCount3 = 0;
					if (enemyBlue3.getTextureRect().left == 0)
					{
						enemyBlue3.setTextureRect(sf::IntRect(24, 0, 15, 14));
					}
					else
					{
						enemyBlue3.setTextureRect(sf::IntRect(0, 0, 15, 14));
					}
				}
				else {
					enemyFrameCount3++;
				}


				////---------------------------------------------------------------------------------------------------------------------

				enemyBlue4.move(enemySpeed4 * enemyDirection4, 0.f);


				if (enemyBlue4.getPosition().x < e4LeftBound || enemyBlue4.getPosition().x > e4RightBound) {
					if (enemyBlue4.getPosition().x < e4LeftBound) {
						enemyDirection4 = 1.0f;  // Move to the right
						enemyBlue4.setScale(-std::abs(enemyBlue4.getScale().x), 2.0f);
					}
					else {
						enemyDirection4 = -1.0f;  // Move to the left

						enemyBlue4.setScale(std::abs(enemyBlue4.getScale().x), 2.0f);
					}
				}

				if (enemyFrameCount4 == enemySwitchFrame4)
				{
					enemyFrameCount4 = 0;
					if (enemyBlue4.getTextureRect().left == 0)
					{
						enemyBlue4.setTextureRect(sf::IntRect(24, 0, 15, 14));
					}
					else
					{
						enemyBlue4.setTextureRect(sf::IntRect(0, 0, 15, 14));
					}
				}
				else {
					enemyFrameCount4++;
				}

				////-------------------------------------------------------------------------------------------------------------------------
				enemyBlue5.move(enemySpeed5 * enemyDirection5, 0.f);

				if (enemyBlue5.getPosition().x < e5LeftBound || enemyBlue5.getPosition().x > e5RightBound) {
					if (enemyBlue5.getPosition().x < e5LeftBound) {
						enemyDirection5 = 1.0f;  // Move to the right
						enemyBlue5.setScale(-std::abs(enemyBlue5.getScale().x), 2.0f);
					}
					else {
						enemyDirection5 = -1.0f;  // Move to the left

						enemyBlue5.setScale(std::abs(enemyBlue5.getScale().x), 2.0f);
					}
				}

				if (frameCount == switchFrame) {
					frameCount = 0;
					if (enemyBlue5.getTextureRect().left == 0)
						enemyBlue5.setTextureRect(sf::IntRect(24, 0, 15, 14));
					else
						enemyBlue5.setTextureRect(sf::IntRect(0, 0, 15, 14));
				}
				else {
					frameCount++;
				}

				//------------------------------------------------------------------------------------------------------------------------
				//Squish Check

				if (player.getGlobalBounds().intersects(enemyBlue.getGlobalBounds()) && damageCooldown.getElapsedTime() > coolDownDuration)
				{
					float playerFeet = player.getPosition().y + player.getGlobalBounds().height / 2.0f;
					float enemyTop = enemyBlue.getPosition().y - enemyBlue.getGlobalBounds().height / 2.0f;

					if (playerFeet < enemyTop)
					{
						// Player jumps on the enemy, so enemy is squished
						playerVelocityY = -12.f;
						stompSound.play();
						isSquished = true;
						squishTimer.restart();

					}
					else
					{
						// Player touches the enemy without jumping, so player gets damaged
						spikeStabSound.play();
						currentHealth--;
						float knockbackDistance = 100.0f; // Adjust as needed
						if (player.getPosition().x < enemyBlue.getPosition().x)
						{
							player.setPosition(player.getPosition().x - knockbackDistance, player.getPosition().y);
						}
						else
						{
							player.setPosition(player.getPosition().x + knockbackDistance, player.getPosition().y);
						}
						blinkingTimer.restart();
						damageCooldown.restart();
					}
				}

				if (isSquished)
				{
					sf::Time elapsed = squishTimer.getElapsedTime();
					if (elapsed < squishDuration)
					{
						// Show squished appearance on the ground
						enemyBlue.setScale(3.f, 0.5f); // Adjust the y-scale for the squish effect
						enemyBlue.setPosition(enemyBlue.getPosition().x, dMetalP1.getPosition().y);
						enemySpeed = 0.f;
					}
					else
					{
						// Remove the enemy after the squish duration
						isSquished = false;
						enemyBlue.setPosition(-1000.0f, -1000.0f);
					}
				}

				//----------------------------------------------------------------------------------------------------------------------------

				if (player.getGlobalBounds().intersects(enemyBlue2.getGlobalBounds()) && damageCooldown.getElapsedTime() > coolDownDuration)
				{
					float playerFeet = player.getPosition().y + player.getGlobalBounds().height / 2.0f;
					float enemyTop2 = enemyBlue2.getPosition().y - enemyBlue2.getGlobalBounds().height / 2.0f;

					if (playerFeet < enemyTop2)
					{
						// Player jumps on the enemy, so enemy is squished
						playerVelocityY = -12.f;
						stompSound.play();
						isSquished2 = true;
						squishTimer2.restart();

					}
					else
					{
						// Player touches the enemy without jumping, so player gets damaged
						spikeStabSound.play();
						currentHealth--;
						float knockbackDistance = 100.0f; // Adjust as needed
						if (player.getPosition().x < enemyBlue2.getPosition().x)
						{
							player.setPosition(player.getPosition().x - knockbackDistance, player.getPosition().y);
						}
						else
						{
							player.setPosition(player.getPosition().x + knockbackDistance, player.getPosition().y);
						}
						blinkingTimer.restart();
						damageCooldown.restart();
					}
				}


				if (isSquished2)
				{
					sf::Time elapsed = squishTimer2.getElapsedTime();
					if (elapsed < squishDuration2)
					{
						// Show squished appearance on the ground
						enemyBlue2.setScale(3.f, 0.5f); // Adjust the y-scale for the squish effect
						enemyBlue2.setPosition(enemyBlue2.getPosition().x, dMetalP2.getPosition().y);
						enemySpeed2 = 0.f;
					}
					else
					{
						// Remove the enemy after the squish duration
						isSquished2 = false;
						enemyBlue2.setPosition(-1000.0f, -1000.0f);
					}
				}

				//--------------------------------------------------------------------------------------------------------------------

				if (player.getGlobalBounds().intersects(enemyBlue3.getGlobalBounds()) && damageCooldown.getElapsedTime() > coolDownDuration)
				{
					float playerFeet = player.getPosition().y + player.getGlobalBounds().height / 2.0f;
					float enemyTop3 = enemyBlue3.getPosition().y - enemyBlue3.getGlobalBounds().height / 2.0f;

					if (playerFeet < enemyTop3)
					{
						// Player jumps on the enemy, so enemy is squished
						playerVelocityY = -12.f;
						stompSound.play();
						isSquished3 = true;
						squishTimer3.restart();

					}
					else
					{
						// Player touches the enemy without jumping, so player gets damaged
						spikeStabSound.play();
						currentHealth--;
						float knockbackDistance = 100.0f; // Adjust as needed
						if (player.getPosition().x < enemyBlue3.getPosition().x)
						{
							player.setPosition(player.getPosition().x - knockbackDistance, player.getPosition().y);
						}
						else
						{
							player.setPosition(player.getPosition().x + knockbackDistance, player.getPosition().y);
						}
						blinkingTimer.restart();
						damageCooldown.restart();
					}
				}


				if (isSquished3)
				{
					sf::Time elapsed = squishTimer3.getElapsedTime();
					if (elapsed < squishDuration3)
					{
						// Show squished appearance on the ground
						enemyBlue3.setScale(3.f, 0.5f); // Adjust the y-scale for the squish effect
						enemyBlue3.setPosition(enemyBlue3.getPosition().x, cloud9.getPosition().y);
						enemySpeed3 = 0.f;
					}
					else
					{
						// Remove the enemy after the squish duration
						isSquished3 = false;
						enemyBlue3.setPosition(-1000.0f, -1000.0f);
					}
				}

				//----------------------------------------------------------------------------------------------------

				if (player.getGlobalBounds().intersects(enemyBlue4.getGlobalBounds()) && damageCooldown.getElapsedTime() > coolDownDuration)
				{
					float playerFeet = player.getPosition().y + player.getGlobalBounds().height / 2.0f;
					float enemyTop4 = enemyBlue4.getPosition().y - enemyBlue4.getGlobalBounds().height / 2.0f;

					if (playerFeet < enemyTop4)
					{
						// Player jumps on the enemy, so enemy is squished
						playerVelocityY = -12.f;
						stompSound.play();
						isSquished4 = true;
						squishTimer4.restart();

					}
					else
					{
						// Player touches the enemy without jumping, so player gets damaged
						spikeStabSound.play();
						currentHealth--;
						float knockbackDistance = 100.0f; // Adjust as needed
						if (player.getPosition().x < enemyBlue4.getPosition().x)
						{
							player.setPosition(player.getPosition().x - knockbackDistance, player.getPosition().y);
						}
						else
						{
							player.setPosition(player.getPosition().x + knockbackDistance, player.getPosition().y);
						}
						blinkingTimer.restart();
						damageCooldown.restart();
					}
				}


				if (isSquished4)
				{
					sf::Time elapsed = squishTimer4.getElapsedTime();
					if (elapsed < squishDuration4)
					{
						// Show squished appearance on the ground
						enemyBlue4.setScale(3.f, 0.5f); // Adjust the y-scale for the squish effect
						enemyBlue4.setPosition(enemyBlue4.getPosition().x, cloud10.getPosition().y);
						enemySpeed4 = 0.f;
					}
					else
					{
						// Remove the enemy after the squish duration
						isSquished4 = false;
						enemyBlue4.setPosition(-1000.0f, -1000.0f);
					}
				}

				//----------------------------------------------------------------------------------------------------------
				if (player.getGlobalBounds().intersects(enemyBlue5.getGlobalBounds()) && damageCooldown.getElapsedTime() > coolDownDuration)
				{
					float playerFeet = player.getPosition().y + player.getGlobalBounds().height / 2.0f;
					float enemyTop5 = enemyBlue5.getPosition().y - enemyBlue5.getGlobalBounds().height / 2.0f;

					if (playerFeet < enemyTop5)
					{
						// Player jumps on the enemy, so enemy is squished
						playerVelocityY = -12.f;
						stompSound.play();
						isSquished5 = true;
						squishTimer5.restart();

					}
					else
					{
						// Player touches the enemy without jumping, so player gets damaged
						spikeStabSound.play();
						currentHealth--;
						float knockbackDistance = 100.0f; // Adjust as needed
						if (player.getPosition().x < enemyBlue5.getPosition().x)
						{
							player.setPosition(player.getPosition().x - knockbackDistance, player.getPosition().y);
						}
						else
						{
							player.setPosition(player.getPosition().x + knockbackDistance, player.getPosition().y);
						}
						blinkingTimer.restart();
						damageCooldown.restart();
					}
				}


				if (isSquished5)
				{
					sf::Time elapsed = squishTimer5.getElapsedTime();
					if (elapsed < squishDuration5)
					{
						// Show squished appearance on the ground
						enemyBlue5.setScale(3.f, 0.5f); // Adjust the y-scale for the squish effect
						enemyBlue5.setPosition(enemyBlue5.getPosition().x, sCloud2.getPosition().y);
						enemySpeed5 = 0.f;
					}
					else
					{
						// Remove the enemy after the squish duration
						isSquished5 = false;
						enemyBlue5.setPosition(-1000.0f, -1000.0f);
					}
				}
				//--------------------------------------------------------------------------------------------------------------------
				//Flying Enemy

				fEnemy.move(fenemySpeed * fenemyDirection, 0.f);

				if (fEnemy.getPosition().x < fleftBound || fEnemy.getPosition().x > frightBound) {
					if (fEnemy.getPosition().x < fleftBound) {
						fenemyDirection = 1.0f;  // Move to the right
						fEnemy.setScale(-std::abs(fEnemy.getScale().x), 2.0f);
					}
					else {
						fenemyDirection = -1.0f;  // Move to the left

						fEnemy.setScale(std::abs(fEnemy.getScale().x), 2.0f);
					}
				}

				if (fenemyFrameCount == fenemySwitchFrame) {
					fenemyFrameCount = 0;
					if (fEnemy.getTextureRect().left == 0)
					{
						fEnemy.setTextureRect(sf::IntRect(21, 0, 24, 16));
					}
					else if (fEnemy.getTextureRect().left == 21)
					{
						fEnemy.setTextureRect(sf::IntRect(45, 0, 24, 16));
					}
					else
					{
						fEnemy.setTextureRect(sf::IntRect(0, 0, 18, 17));
					}
				}
				else {
					fenemyFrameCount++;
				}
				//-------------------------------------------------------------------------------------------------------------------------

				fEnemy2.move(fenemySpeed2 * fenemyDirection2, 0.f);

				if (fEnemy2.getPosition().x < f2LeftBound || fEnemy2.getPosition().x > f2RightBound) {
					if (fEnemy2.getPosition().x < f2LeftBound) {
						fenemyDirection2 = 1.0f;  // Move to the right
						fEnemy2.setScale(-std::abs(fEnemy2.getScale().x), 2.0f);
					}
					else {
						fenemyDirection2 = -1.0f;  // Move to the left

						fEnemy2.setScale(std::abs(fEnemy2.getScale().x), 2.0f);
					}
				}

				if (fenemyFrameCount2 == fenemySwitchFrame2) {
					fenemyFrameCount2 = 0;
					if (fEnemy2.getTextureRect().left == 0)
					{
						fEnemy2.setTextureRect(sf::IntRect(21, 0, 24, 16));
					}
					else if (fEnemy2.getTextureRect().left == 21)
					{
						fEnemy2.setTextureRect(sf::IntRect(45, 0, 24, 16));
					}
					else
					{
						fEnemy2.setTextureRect(sf::IntRect(0, 0, 18, 17));
					}
				}
				else {
					fenemyFrameCount2++;
				}

				//-----------------------------------------------------------------------------------------------------------------------------

				fEnemy3.move(fenemySpeed3 * fenemyDirection3, 0.f);

				if (fEnemy3.getPosition().x < f3LeftBound || fEnemy3.getPosition().x > f3RightBound) {
					if (fEnemy3.getPosition().x < f3LeftBound) {
						fenemyDirection3 = 1.0f;  // Move to the right
						fEnemy3.setScale(-std::abs(fEnemy3.getScale().x), 2.0f);
					}
					else {
						fenemyDirection3 = -1.0f;  // Move to the left

						fEnemy3.setScale(std::abs(fEnemy3.getScale().x), 2.0f);
					}
				}

				if (fenemyFrameCount3 == fenemySwitchFrame3) {
					fenemyFrameCount3 = 0;
					if (fEnemy3.getTextureRect().left == 0)
					{
						fEnemy3.setTextureRect(sf::IntRect(21, 0, 24, 16));
					}
					else if (fEnemy3.getTextureRect().left == 21)
					{
						fEnemy3.setTextureRect(sf::IntRect(45, 0, 24, 16));
					}
					else
					{
						fEnemy3.setTextureRect(sf::IntRect(0, 0, 18, 17));
					}
				}
				else {
					fenemyFrameCount3++;
				}
				//--------------------------------------------------------------------------------------------------------------
				fEnemy4.move(fenemySpeed4 * fenemyDirection4, 0.f);

				if (fEnemy4.getPosition().x < f4LeftBound || fEnemy4.getPosition().x > f4RightBound) {
					if (fEnemy4.getPosition().x < f4LeftBound) {
						fenemyDirection4 = 1.0f;  // Move to the right
						fEnemy4.setScale(-std::abs(fEnemy4.getScale().x), 2.0f);
					}
					else {
						fenemyDirection4 = -1.0f;  // Move to the left

						fEnemy4.setScale(std::abs(fEnemy4.getScale().x), 2.0f);
					}
				}

				if (fenemyFrameCount4 == fenemySwitchFrame4) {
					fenemyFrameCount4 = 0;
					if (fEnemy4.getTextureRect().left == 0)
					{
						fEnemy4.setTextureRect(sf::IntRect(21, 0, 24, 16));
					}
					else if (fEnemy4.getTextureRect().left == 21)
					{
						fEnemy4.setTextureRect(sf::IntRect(45, 0, 24, 16));
					}
					else
					{
						fEnemy4.setTextureRect(sf::IntRect(0, 0, 18, 17));
					}
				}
				else {
					fenemyFrameCount4++;
				}
				//-------------------------------------------------------------------------------------------------------------------
				fEnemy5.move(fenemySpeed5 * fenemyDirection5, 0.f);

				if (fEnemy5.getPosition().x < f5LeftBound || fEnemy5.getPosition().x > f5RightBound) {
					if (fEnemy5.getPosition().x < f5LeftBound) {
						fenemyDirection5 = 1.0f;  // Move to the right
						fEnemy5.setScale(-std::abs(fEnemy5.getScale().x), 2.0f);
					}
					else {
						fenemyDirection5 = -1.0f;  // Move to the left

						fEnemy5.setScale(std::abs(fEnemy5.getScale().x), 2.0f);
					}
				}

				if (fenemyFrameCount5 == fenemySwitchFrame5) {
					fenemyFrameCount5 = 0;
					if (fEnemy5.getTextureRect().left == 0)
					{
						fEnemy5.setTextureRect(sf::IntRect(21, 0, 24, 16));
					}
					else if (fEnemy5.getTextureRect().left == 21)
					{
						fEnemy5.setTextureRect(sf::IntRect(45, 0, 24, 16));
					}
					else
					{
						fEnemy5.setTextureRect(sf::IntRect(0, 0, 18, 17));
					}
				}
				else {
					fenemyFrameCount5++;
				}
				//--------------------------------------------------------------------------------------------------------
				//Flying Squished
				if (player.getGlobalBounds().intersects(fEnemy.getGlobalBounds()) && damageCooldown.getElapsedTime() > coolDownDuration)
				{
					float playerFeet = player.getPosition().y + player.getGlobalBounds().height / 2.0f;
					float enemyTopf = fEnemy.getPosition().y - fEnemy.getGlobalBounds().height / 2.0f;

					if (playerFeet < enemyTopf)
					{
						// Player jumps on the enemy, so enemy is squished
						playerVelocityY = -12.f;
						stompSound.play();
						fisSquished = true;
						fsquishTimer.restart();

					}
					else
					{
						// Player touches the enemy without jumping, so player gets damaged
						spikeStabSound.play();
						currentHealth--;
						float knockbackDistance = 100.0f; // Adjust as needed
						if (player.getPosition().x < fEnemy.getPosition().x)
						{
							player.setPosition(player.getPosition().x - knockbackDistance, player.getPosition().y);
						}
						else
						{
							player.setPosition(player.getPosition().x + knockbackDistance, player.getPosition().y);
						}
						blinkingTimer.restart();
						damageCooldown.restart();
					}
				}


				if (fisSquished)
				{
					sf::Time elapsed = fsquishTimer.getElapsedTime();
					if (elapsed < fsquishDuration)
					{
						// Show squished appearance on the ground
						//fEnemy.setScale(3.f, 0.5f); // Adjust the y-scale for the squish effect
						fEnemy.move(0.f, 20.f);
						fenemySpeed = 0.f;
					}
					else
					{
						// Remove the enemy after the squish duration
						fisSquished = false;
						fEnemy.setPosition(-1000.0f, -1000.0f);
					}
				}

				//---------------------------------------------------------------------------------------------------------------

				if (player.getGlobalBounds().intersects(fEnemy2.getGlobalBounds()) && damageCooldown.getElapsedTime() > coolDownDuration)
				{
					float playerFeet = player.getPosition().y + player.getGlobalBounds().height / 2.0f;
					float enemyTopf2 = fEnemy2.getPosition().y - fEnemy2.getGlobalBounds().height / 2.0f;

					if (playerFeet < enemyTopf2)
					{
						// Player jumps on the enemy, so enemy is squished
						playerVelocityY = -12.f;
						stompSound.play();
						f2isSquished = true;
						f2squishTimer.restart();

					}
					else
					{
						// Player touches the enemy without jumping, so player gets damaged
						spikeStabSound.play();
						currentHealth--;
						float knockbackDistance = 100.0f; // Adjust as needed
						if (player.getPosition().x < fEnemy2.getPosition().x)
						{
							player.setPosition(player.getPosition().x - knockbackDistance, player.getPosition().y);
						}
						else
						{
							player.setPosition(player.getPosition().x + knockbackDistance, player.getPosition().y);
						}
						blinkingTimer.restart();
						damageCooldown.restart();
					}
				}


				if (f2isSquished)
				{
					sf::Time elapsed = f2squishTimer.getElapsedTime();
					if (elapsed < f2squishDuration)
					{
						// Show squished appearance on the ground
						//fEnemy.setScale(3.f, 0.5f); // Adjust the y-scale for the squish effect
						fEnemy2.move(0.f, 20.f);
						fenemySpeed2 = 0.f;
					}
					else
					{
						// Remove the enemy after the squish duration
						f2isSquished = false;
						fEnemy2.setPosition(-1000.0f, -1000.0f);
					}
				}
				//------------------------------------------------------------------------------------------------------------------
				if (player.getGlobalBounds().intersects(fEnemy3.getGlobalBounds()) && damageCooldown.getElapsedTime() > coolDownDuration)
				{
					float playerFeet = player.getPosition().y + player.getGlobalBounds().height / 2.0f;
					float enemyTopf3 = fEnemy3.getPosition().y - fEnemy3.getGlobalBounds().height / 2.0f;

					if (playerFeet < enemyTopf3)
					{
						// Player jumps on the enemy, so enemy is squished
						playerVelocityY = -12.f;
						stompSound.play();
						f3isSquished = true;
						f3squishTimer.restart();

					}
					else
					{
						// Player touches the enemy without jumping, so player gets damaged
						spikeStabSound.play();
						currentHealth--;
						float knockbackDistance = 100.0f; // Adjust as needed
						if (player.getPosition().x < fEnemy3.getPosition().x)
						{
							player.setPosition(player.getPosition().x - knockbackDistance, player.getPosition().y);
						}
						else
						{
							player.setPosition(player.getPosition().x + knockbackDistance, player.getPosition().y);
						}
						blinkingTimer.restart();
						damageCooldown.restart();
					}
				}


				if (f3isSquished)
				{
					sf::Time elapsed = f3squishTimer.getElapsedTime();
					if (elapsed < f3squishDuration)
					{
						// Show squished appearance on the ground
						//fEnemy.setScale(3.f, 0.5f); // Adjust the y-scale for the squish effect
						fEnemy3.move(0.f, 20.f);
						fenemySpeed3 = 0.f;
					}
					else
					{
						// Remove the enemy after the squish duration
						f3isSquished = false;
						fEnemy3.setPosition(-1000.0f, -1000.0f);
					}
				}
				//----------------------------------------------------------------------------------------------------------------
				if (player.getGlobalBounds().intersects(fEnemy4.getGlobalBounds()) && damageCooldown.getElapsedTime() > coolDownDuration)
				{
					float playerFeet = player.getPosition().y + player.getGlobalBounds().height / 2.0f;
					float enemyTopf4 = fEnemy4.getPosition().y - fEnemy4.getGlobalBounds().height / 2.0f;

					if (playerFeet < enemyTopf4)
					{
						// Player jumps on the enemy, so enemy is squished
						playerVelocityY = -12.f;
						stompSound.play();
						f4isSquished = true;
						f4squishTimer.restart();

					}
					else
					{
						// Player touches the enemy without jumping, so player gets damaged
						spikeStabSound.play();
						currentHealth--;
						float knockbackDistance = 100.0f; // Adjust as needed
						if (player.getPosition().x < fEnemy4.getPosition().x)
						{
							player.setPosition(player.getPosition().x - knockbackDistance, player.getPosition().y);
						}
						else
						{
							player.setPosition(player.getPosition().x + knockbackDistance, player.getPosition().y);
						}
						blinkingTimer.restart();
						damageCooldown.restart();
					}
				}


				if (f4isSquished)
				{
					sf::Time elapsed = f4squishTimer.getElapsedTime();
					if (elapsed < f4squishDuration)
					{
						// Show squished appearance on the ground
						//fEnemy.setScale(3.f, 0.5f); // Adjust the y-scale for the squish effect
						fEnemy4.move(0.f, 20.f);
						fenemySpeed4 = 0.f;
					}
					else
					{
						// Remove the enemy after the squish duration
						f4isSquished = false;
						fEnemy4.setPosition(-1000.0f, -1000.0f);
					}
				}
				//--------------------------------------------------------------------------------------------------------------------------
				if (player.getGlobalBounds().intersects(fEnemy5.getGlobalBounds()) && damageCooldown.getElapsedTime() > coolDownDuration)
				{
					float playerFeet = player.getPosition().y + player.getGlobalBounds().height / 2.0f;
					float enemyTopf5 = fEnemy5.getPosition().y - fEnemy5.getGlobalBounds().height / 2.0f;

					if (playerFeet < enemyTopf5)
					{
						// Player jumps on the enemy, so enemy is squished
						playerVelocityY = -12.f;
						stompSound.play();
						f5isSquished = true;
						f5squishTimer.restart();

					}
					else
					{
						// Player touches the enemy without jumping, so player gets damaged
						spikeStabSound.play();
						currentHealth--;
						float knockbackDistance = 100.0f; // Adjust as needed
						if (player.getPosition().x < fEnemy5.getPosition().x)
						{
							player.setPosition(player.getPosition().x - knockbackDistance, player.getPosition().y);
						}
						else
						{
							player.setPosition(player.getPosition().x + knockbackDistance, player.getPosition().y);
						}
						blinkingTimer.restart();
						damageCooldown.restart();
					}
				}


				if (f5isSquished)
				{
					sf::Time elapsed = f5squishTimer.getElapsedTime();
					if (elapsed < f5squishDuration)
					{
						// Show squished appearance on the ground
						//fEnemy.setScale(3.f, 0.5f); // Adjust the y-scale for the squish effect
						fEnemy5.move(0.f, 20.f);
						fenemySpeed5 = 0.f;
					}
					else
					{
						// Remove the enemy after the squish duration
						f5isSquished = false;
						fEnemy5.setPosition(-1000.0f, -1000.0f);
					}
				}

				//RED ENEMY MOVEMENT ANIMATIONS

				rEnemy.move(rEnemySpeed * rEnemyDirection, 0.f);


				if (rEnemy.getPosition().x < rLeftBound || rEnemy.getPosition().x > rRightBound) {
					if (rEnemy.getPosition().x < rLeftBound) {
						rEnemyDirection = 1.0f;  // Move to the right
						rEnemy.setScale(-std::abs(rEnemy.getScale().x), 2.0f);
					}
					else {
						rEnemyDirection = -1.0f;  // Move to the left

						rEnemy.setScale(std::abs(rEnemy.getScale().x), 2.0f);
					}
				}

				if (rEnemyFrameCount == rEnemySwitchFrame) {
					rEnemyFrameCount = 0;
					if (rEnemy.getTextureRect().left == 0)
						rEnemy.setTextureRect(sf::IntRect(25, 0, 15, 19));
					else
						rEnemy.setTextureRect(sf::IntRect(0, 0, 15, 19));
				}
				else {
					rEnemyFrameCount++;
				}



				//-------------------------------------------------------------------------------
				rEnemy2.move(rEnemySpeed2 * rEnemyDirection2, 0.f);

				if (rEnemy2.getPosition().x < r2LeftBound || rEnemy2.getPosition().x > r2RightBound) {
					if (rEnemy2.getPosition().x < r2LeftBound) {
						rEnemyDirection2 = 1.0f;  // Move to the right
						rEnemy2.setScale(-std::abs(rEnemy2.getScale().x), 2.0f);
					}
					else {
						rEnemyDirection2 = -1.0f;  // Move to the left

						rEnemy2.setScale(std::abs(rEnemy2.getScale().x), 2.0f);
					}
				}

				if (rEnemyFrameCount2 == rEnemySwitchFrame2) {
					rEnemyFrameCount2 = 0;
					if (rEnemy2.getTextureRect().left == 0)
						rEnemy2.setTextureRect(sf::IntRect(25, 0, 15, 19));
					else
						rEnemy2.setTextureRect(sf::IntRect(0, 0, 15, 19));
				}
				else {
					rEnemyFrameCount2++;
				}
				//---------------------------------------------------------------------------------
				rEnemy3.move(rEnemySpeed3 * rEnemyDirection3, 0.f);

				if (rEnemy3.getPosition().x < r3LeftBound || rEnemy3.getPosition().x > r3RightBound) {
					if (rEnemy3.getPosition().x < r3LeftBound) {
						rEnemyDirection3 = 1.0f;  // Move to the right
						rEnemy3.setScale(-std::abs(rEnemy3.getScale().x), 2.0f);
					}
					else {
						rEnemyDirection3 = -1.0f;  // Move to the left

						rEnemy3.setScale(std::abs(rEnemy3.getScale().x), 2.0f);
					}
				}

				if (rEnemyFrameCount3 == rEnemySwitchFrame3) {
					rEnemyFrameCount3 = 0;
					if (rEnemy3.getTextureRect().left == 0)
						rEnemy3.setTextureRect(sf::IntRect(25, 0, 15, 19));
					else
						rEnemy3.setTextureRect(sf::IntRect(0, 0, 15, 19));
				}
				else {
					rEnemyFrameCount3++;
				}
				//----------------------------------------------------------------------------------
				rEnemy4.move(rEnemySpeed4 * rEnemyDirection4, 0.f);

				if (rEnemy4.getPosition().x < r4LeftBound || rEnemy4.getPosition().x > r4RightBound) {
					if (rEnemy4.getPosition().x < r4LeftBound) {
						rEnemyDirection4 = 1.0f;  // Move to the right
						rEnemy4.setScale(-std::abs(rEnemy3.getScale().x), 2.0f);
					}
					else {
						rEnemyDirection4 = -1.0f;  // Move to the left

						rEnemy4.setScale(std::abs(rEnemy4.getScale().x), 2.0f);
					}
				}

				if (rEnemyFrameCount4 == rEnemySwitchFrame4) {
					rEnemyFrameCount4 = 0;
					if (rEnemy4.getTextureRect().left == 0)
						rEnemy4.setTextureRect(sf::IntRect(25, 0, 15, 19));
					else
						rEnemy4.setTextureRect(sf::IntRect(0, 0, 15, 19));
				}
				else {
					rEnemyFrameCount4++;
				}
				//---------------------------------------------------------------------------------------
				rEnemy5.move(rEnemySpeed5 * rEnemyDirection5, 0.f);

				if (rEnemy5.getPosition().x < r5LeftBound || rEnemy5.getPosition().x > r5RightBound) {
					if (rEnemy5.getPosition().x < r5LeftBound) {
						rEnemyDirection5 = 1.0f;  // Move to the right
						rEnemy5.setScale(-std::abs(rEnemy3.getScale().x), 2.0f);
					}
					else {
						rEnemyDirection5 = -1.0f;  // Move to the left

						rEnemy5.setScale(std::abs(rEnemy4.getScale().x), 2.0f);
					}
				}

				if (rEnemyFrameCount5 == rEnemySwitchFrame4) {
					rEnemyFrameCount5 = 0;
					if (rEnemy5.getTextureRect().left == 0)
						rEnemy5.setTextureRect(sf::IntRect(25, 0, 15, 19));
					else
						rEnemy5.setTextureRect(sf::IntRect(0, 0, 15, 19));
				}
				else {
					rEnemyFrameCount5++;
				}
				//-------------------------------------------------------------------------------------------
				rEnemy6.move(rEnemySpeed6 * rEnemyDirection6, 0.f);

				if (rEnemy6.getPosition().x < r6LeftBound || rEnemy6.getPosition().x > r6RightBound) {
					if (rEnemy6.getPosition().x < r6LeftBound) {
						rEnemyDirection6 = 1.0f;  // Move to the right
						rEnemy6.setScale(-std::abs(rEnemy6.getScale().x), 2.0f);
					}
					else {
						rEnemyDirection6 = -1.0f;  // Move to the left

						rEnemy6.setScale(std::abs(rEnemy6.getScale().x), 2.0f);
					}
				}

				if (rEnemyFrameCount6 == rEnemySwitchFrame6) {
					rEnemyFrameCount6 = 0;
					if (rEnemy6.getTextureRect().left == 0)
						rEnemy6.setTextureRect(sf::IntRect(25, 0, 15, 19));
					else
						rEnemy6.setTextureRect(sf::IntRect(0, 0, 15, 19));
				}
				else {
					rEnemyFrameCount6++;
				}
				//-----------------------------------------------------------------------------------------------
				//RED ENEMY COLLISION
				if (playerBounds.intersects(rEnemyBounds) && damageCooldown.getElapsedTime() > coolDownDuration)
				{
					playerVelocityY = -12.f;
					currentHealth--;

					spikeStabSound.play();

					blinkingTimer.restart();
					damageCooldown.restart();
				}

				if (playerBounds.intersects(rEnemyBounds2) && damageCooldown.getElapsedTime() > coolDownDuration)
				{
					playerVelocityY = -12.f;
					currentHealth--;

					spikeStabSound.play();

					blinkingTimer.restart();
					damageCooldown.restart();
				}

				if (playerBounds.intersects(rEnemyBounds3) && damageCooldown.getElapsedTime() > coolDownDuration)
				{
					playerVelocityY = -12.f;
					currentHealth--;

					spikeStabSound.play();

					blinkingTimer.restart();
					damageCooldown.restart();
				}

				if (playerBounds.intersects(rEnemyBounds4) && damageCooldown.getElapsedTime() > coolDownDuration)
				{
					playerVelocityY = -12.f;
					currentHealth--;

					spikeStabSound.play();

					blinkingTimer.restart();
					damageCooldown.restart();
				}

				if (playerBounds.intersects(rEnemyBounds5) && damageCooldown.getElapsedTime() > coolDownDuration)
				{
					playerVelocityY = -12.f;
					currentHealth--;

					spikeStabSound.play();

					blinkingTimer.restart();
					damageCooldown.restart();
				}

				if (player.getGlobalBounds().intersects(spring1.getGlobalBounds())) {
					if (!isSpringActivated && playerVelocityY > 0) {
						// Player jumps on the spring while moving downward, activate it
						isSpringActivated = true;
						playerVelocityY = -20.0f; // Adjust the vertical force as needed
						spring1.setTextureRect(sf::IntRect(19, 0, 18, 14)); // Assuming second frame starts at x=32
						jumpSound.play();
					}
				}
				else {
					isSpringActivated = false;
					spring1.setTextureRect(sf::IntRect(0, 0, 18, 14));
				}

				if (player.getGlobalBounds().intersects(spring2.getGlobalBounds())) {
					if (!isSpringActivated && playerVelocityY > 0) {
						// Player jumps on the spring while moving downward, activate it
						isSpringActivated = true;
						playerVelocityY = -20.0f; // Adjust the vertical force as needed
						spring2.setTextureRect(sf::IntRect(19, 0, 18, 14)); // Assuming second frame starts at x=32
						jumpSound.play();
					}
				}
				else {
					isSpringActivated = false;
					spring2.setTextureRect(sf::IntRect(0, 0, 18, 14));
				}

				if (coin1FrameCount == coin1SwitchFrame) {
					coin1FrameCount = 0;
					if (coin1.getTextureRect().left == 0)
						coin1.setTextureRect(sf::IntRect(20, 0, 8, 12));
					else
						coin1.setTextureRect(sf::IntRect(0, 0, 12, 12));
				}
				else {
					coin1FrameCount++;
				}


				if (coin2FrameCount == coin2SwitchFrame) {
					coin2FrameCount = 0;
					if (coin2.getTextureRect().left == 0)
						coin2.setTextureRect(sf::IntRect(20, 0, 8, 12));
					else
						coin2.setTextureRect(sf::IntRect(0, 0, 12, 12));
				}
				else {
					coin2FrameCount++;
				}

				if (coin3FrameCount == coin3SwitchFrame) {
					coin3FrameCount = 0;
					if (coin3.getTextureRect().left == 0)
						coin3.setTextureRect(sf::IntRect(20, 0, 8, 12));
					else
						coin3.setTextureRect(sf::IntRect(0, 0, 12, 12));
				}
				else {
					coin3FrameCount++;
				}
				//-----------------------------------------------------------------------------


				if (player.getGlobalBounds().intersects(coin1.getGlobalBounds())) {
					coins += 1;
					coin1.setPosition(-1000, -1000);
					coinSound.play();
				}

				if (player.getGlobalBounds().intersects(coin2.getGlobalBounds())) {
					coins += 1;
					coin2.setPosition(-1000, -1000);
					coinSound.play();
				}

				if (player.getGlobalBounds().intersects(coin3.getGlobalBounds())) {
					coins += 1;
					coin3.setPosition(-1000, -1000);
					coinSound.play();
				}

				//----------------------------------------------------------------------------
				
				if (player.getGlobalBounds().intersects(norDoor.getGlobalBounds())) {
					doorSound.play();
					player.setPosition(1680, 184);
				}



				if (player.getGlobalBounds().intersects(key.getGlobalBounds())) {
					keySound.play();
					key.setPosition(-1000, -1000);
					hasKey = true;
				}

				if (player.getGlobalBounds().intersects(keyDoor.getGlobalBounds())) {

					if (hasKey)
					{
						snow.stop();
						victorySound.play();
						hasKeyLevel2 = true;
						level1Friendbool = true;
						currentLevel = 7;
						/*player.setPosition(spring3h.getPosition().x - 200, snowP1.getPosition().y);*/
						player.setPosition(20, 1000);

						coin1.setPosition(1195, 1015);
						coin2.setPosition(1890, 438);
						coin3.setPosition(696, 39);

						key.setPosition(243, 92);
						std::this_thread::sleep_for(std::chrono::seconds(5));
					}
				}

				

		
				updateHealth(currentHealth);
				
				
				
				window.clear();
				
				window.draw(snowBg);
				window.setView(view);
				
				window.draw(enemyBlue);
				window.draw(enemyBlue2);
				window.draw(enemyBlue3);
				window.draw(enemyBlue4);
				window.draw(enemyBlue5);
				window.draw(fEnemy);
				window.draw(fEnemy2);
				window.draw(fEnemy3);
				window.draw(fEnemy4);
				window.draw(fEnemy5);
				window.draw(rEnemy);
				window.draw(rEnemy2);
				window.draw(rEnemy3);
				window.draw(rEnemy4);
				window.draw(rEnemy5);
				window.draw(rEnemy6);
				window.draw(spike1);
				window.draw(spike2);
				window.draw(spike3);
				window.draw(spike4);
				/*window.draw(spike5);*/
				window.draw(spike6);
				window.draw(spike7);
				window.draw(spike8);
				window.draw(spike9);
				window.draw(spike10);
				window.draw(spring1);
				window.draw(spring2);
				window.draw(coin1);
				window.draw(coin2);
				window.draw(coin3);
				window.draw(key);
				window.draw(snowP1);
				window.draw(snowP4);
				window.draw(snowP2);
				window.draw(snowP3);
				window.draw(dMetalP1);
				window.draw(dMetalP2);
				window.draw(sMetalP);
				window.draw(chis1);
				window.draw(chis2);
				window.draw(chis3);
				window.draw(chis4);
				window.draw(chis5);
				window.draw(chis6);
				window.draw(chis7);
				window.draw(chis8);
				window.draw(chis9);
				window.draw(cloud1);
				window.draw(cloud2);
				window.draw(cloud3);
				window.draw(cloud4);
				window.draw(cloud5);
				window.draw(cloud6);
				window.draw(cloud7);
				window.draw(cloud8);
				window.draw(cloud9);
				window.draw(cloud10);
				window.draw(cloud11);
				window.draw(cloud12);

				window.draw(coinCloud);
				window.draw(keyCloud);
				window.draw(sCloud1);
				window.draw(sCloud2);
				window.draw(snowMan);
				window.draw(norDoor);
				window.draw(coinDoor);
				window.draw(keyDoor);

				if (player.getGlobalBounds().intersects(coinDoor.getGlobalBounds())) {
					if (coins == 3)
					{
						doorSound.play();
						player.setPosition(73, 109);
					}
				}

				if (blinkingTimer.getElapsedTime() < blinkingTimerDuration)
				{
					if (static_cast<int>(blinkingTimer.getElapsedTime().asSeconds() * 5) % 2 == 0)
					{
						window.draw(player);
					}
				}
				else
				{
					window.draw(player);
				}

				if (currentHealth == 0)
				{

					gameOver.setPosition(view.getCenter().x - goWidth / 2, view.getCenter().y - goHeight / 2);

					goSound.play();

					window.draw(gameOver);

					window.display();

					currentLevel = 1;

					player.setPosition(spring2h.getPosition().x - 220, snowP1.getPosition().y + 50);

					coin1.setPosition(1195, 1015);
					coin2.setPosition(1890, 438);
					coin3.setPosition(696, 39);

					key.setPosition(243, 92);

					snow.stop();
		
					std::this_thread::sleep_for(std::chrono::seconds(5));
				
				}

			

				window.setView(guiView);
				drawHealthBar(window, filledHeartTexture, emptyHeartTexture);
				window.display();

				break;
			case 3:
					window.setView(view);
					sf::Event pollEvent;

					while (window.pollEvent(pollEvent))
					{
						if (pollEvent.type == sf::Event::Closed)
						{
							window.close();
						}
						else if (pollEvent.type == sf::Event::KeyPressed && pollEvent.key.code == sf::Keyboard::Escape)
						{
							window.close();
						}
					}

					//Player Movement
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
					{
						playerVelocityX = -5.f;
						isMoving = true;
						movingLeft = true;
						movingRight = false;
					}
					else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
					{
						playerVelocityX = 5.f;
						isMoving = true;
						movingLeft = false;
						movingRight = true;
					}
					else
					{
						playerVelocityX = 0.f;
						isMoving = false;
						movingLeft = false;
						movingRight = false;
					}

					//PLAYER JUMP
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
					{
						if (!isJumping && jumpCount < maxJump)
						{
							isJumping = true;
							playerVelocityY = jumpVelocity;
							jumpCount++;
							frameCount = 0;

							jumpSound.play();
						}
					}
					else
					{
						isJumping = false;
					}

					playerVelocityY += gravity;
					player.move(playerVelocityX, playerVelocityY);

					if (player.getPosition().x < 0) {
						// Correct position to be exactly at the left boundary
						player.setPosition(0, player.getPosition().y);

						// If the player is moving left, stop horizontal movement
						if (playerVelocityX < 0) {
							playerVelocityX = 0.f;
						}
					}

					if (player.getPosition().x > 1920) {
						// Correct position to be exactly at the left boundary
						player.setPosition(1920, player.getPosition().y);

						// If the player is moving left, stop horizontal movement
						if (playerVelocityX > 1920) {
							playerVelocityX = 0.f;
						}
					}

					if (player.getPosition().y < 0) {
						// Correct position to be exactly at the left boundary
						player.setPosition(player.getPosition().x, 0);

						// If the player is moving left, stop horizontal movement
						if (playerVelocityY < 0) {
							playerVelocityY = 0.f;
						}
					}

					//FLOOR COLLISION
					if (player.getPosition().y >= 950.f)
					{
						player.setPosition(player.getPosition().x, 950.f);
						playerVelocityY = 0.f;
						jumpCount = 0;
					}
					if (player.getPosition().y == 950.f)
					{
						jumpCount = 0;
					}

					//-------------------------------------------------------------------------------------
					//ANIMATIONS

					//JUMPING ANIMATION
					if (isJumping)
					{
						player.setTextureRect(sf::IntRect(0, 0, 20, 24));
					}
					//LEFT MOVEMENT ANIMATION
					else if (movingLeft)
					{
						if (frameCount == switchFrame)
						{
							frameCount = 0;
							if (player.getTextureRect().left == 0)
								player.setTextureRect(sf::IntRect(24, 0, 20, 24));
							else
								player.setTextureRect(sf::IntRect(0, 0, 20, 24));
						}
						else
						{
							frameCount++;
						}
					}
					//RIGHT MOVEMENT ANIMATION
					else if (movingRight)
					{
						if (frameCount == switchFrame)
						{
							frameCount = 0;
							if (player.getTextureRect().left == 0)
							{
								player.setTextureRect(sf::IntRect(24, 0, 20, 24));
							}
							else
							{
								player.setTextureRect(sf::IntRect(0, 0, 20, 24));
							}
						}
						else
						{
							frameCount++;
						}
					}
					else
					{
						player.setTextureRect(sf::IntRect(24, 0, 20, 24));
					}

					//FLIPS THE SPRITE BASED ON DIRECTION
					if (movingLeft)
					{
						player.setScale(-2.f, 2.f);
					}
					else if (movingRight)
					{
						player.setScale(2.f, 2.f);
					}

					//-----------------------------------------------------------------------------------------ENEMY MOVEMENT------------------------------------------------------//

					bEnemyd1.move(bed1enemySpeed * bed1enemyDirection, 0.f);

					//ENEMY BLUE ANIMATION
					if (bEnemyd1.getPosition().x < bed1LeftBound || bEnemyd1.getPosition().x > bed1rightBound) {
						if (bEnemyd1.getPosition().x < bed1LeftBound) {
							bed1enemyDirection = 1.0f;  // Move to the right
							bEnemyd1.setScale(-std::abs(bEnemyd1.getScale().x), 2.0f);
						}
						else {
							bed1enemyDirection = -1.0f;  // Move to the left

							bEnemyd1.setScale(std::abs(bEnemyd1.getScale().x), 2.0f);
						}
					}

					if (bed1frameCount == bed1switchFrame) {
						bed1frameCount = 0;
						if (bEnemyd1.getTextureRect().left == 0)
							bEnemyd1.setTextureRect(sf::IntRect(24, 0, 15, 14));
						else
							bEnemyd1.setTextureRect(sf::IntRect(0, 0, 15, 14));
					}
					else {
						bed1frameCount++;
					}

					//-------------------------------------------------------------------------------------------------------------------------------------------------------------//

					bEnemyd2.move(bed2enemySpeed * bed2enemyDirection, 0.f);

					if (bEnemyd2.getPosition().x < bed2LeftBound || bEnemyd2.getPosition().x > bed2rightBound) {
						if (bEnemyd2.getPosition().x < bed2LeftBound) {
							bed2enemyDirection = 1.0f;  // Move to the right
							bEnemyd2.setScale(-std::abs(bEnemyd2.getScale().x), 2.0f);
						}
						else {
							bed2enemyDirection = -1.0f;  // Move to the left

							bEnemyd2.setScale(std::abs(bEnemyd2.getScale().x), 2.0f);
						}
					}

					if (bed2frameCount == bed2switchFrame) {
						bed2frameCount = 0;
						if (bEnemyd2.getTextureRect().left == 0)
							bEnemyd2.setTextureRect(sf::IntRect(24, 0, 15, 14));
						else
							bEnemyd2.setTextureRect(sf::IntRect(0, 0, 15, 14));
					}
					else {
						bed2frameCount++;
					}

					//-------------------------------------------------------------------------------------------------------------------------------------------------------------//

					bEnemyd3.move(bed3enemySpeed * bed3enemyDirection, 0.f);

					if (bEnemyd3.getPosition().x < bed3LeftBound || bEnemyd3.getPosition().x > bed3rightBound) {
						if (bEnemyd3.getPosition().x < bed3LeftBound) {
							bed3enemyDirection = 1.0f;  // Move to the right
							bEnemyd3.setScale(-std::abs(bEnemyd3.getScale().x), 2.0f);
						}
						else {
							bed3enemyDirection = -1.0f;  // Move to the left

							bEnemyd3.setScale(std::abs(bEnemyd3.getScale().x), 2.0f);
						}
					}

					if (bed3frameCount == bed3switchFrame) {
						bed3frameCount = 0;
						if (bEnemyd3.getTextureRect().left == 0)
							bEnemyd3.setTextureRect(sf::IntRect(24, 0, 15, 14));
						else
							bEnemyd3.setTextureRect(sf::IntRect(0, 0, 15, 14));
					}
					else {
						bed3frameCount++;
					}

					//-------------------------------------------------------------------------------------------------------------------------------------------------------------//

					bEnemyd4.move(bed4enemySpeed * bed4enemyDirection, 0.f);

					if (bEnemyd4.getPosition().x < bed4LeftBound || bEnemyd4.getPosition().x > bed4rightBound) {
						if (bEnemyd4.getPosition().x < bed4LeftBound) {
							bed4enemyDirection = 1.0f;  // Move to the right
							bEnemyd4.setScale(-std::abs(bEnemyd4.getScale().x), 2.0f);
						}
						else {
							bed4enemyDirection = -1.0f;  // Move to the left

							bEnemyd4.setScale(std::abs(bEnemyd4.getScale().x), 2.0f);
						}
					}

					if (bed4frameCount == bed4switchFrame) {
						bed4frameCount = 0;
						if (bEnemyd4.getTextureRect().left == 0)
							bEnemyd4.setTextureRect(sf::IntRect(24, 0, 15, 14));
						else
							bEnemyd4.setTextureRect(sf::IntRect(0, 0, 15, 14));
					}
					else {
						bed4frameCount++;
					}
					//-------------------------------------------------------------------------------------------------------------------------------------------------------------//
					bEnemyd5.move(bed5enemySpeed * bed5enemyDirection, 0.f);

					if (bEnemyd5.getPosition().x < bed5LeftBound || bEnemyd5.getPosition().x > bed5rightBound) {
						if (bEnemyd5.getPosition().x < bed5LeftBound) {
							bed5enemyDirection = 1.0f;  // Move to the right
							bEnemyd5.setScale(-std::abs(bEnemyd5.getScale().x), 2.0f);
						}
						else {
							bed5enemyDirection = -1.0f;  // Move to the left

							bEnemyd5.setScale(std::abs(bEnemyd5.getScale().x), 2.0f);
						}
					}

					if (bed5frameCount == bed5switchFrame) {
						bed5frameCount = 0;
						if (bEnemyd5.getTextureRect().left == 0)
							bEnemyd5.setTextureRect(sf::IntRect(24, 0, 15, 14));
						else
							bEnemyd5.setTextureRect(sf::IntRect(0, 0, 15, 14));
					}
					else {
						bed5frameCount++;
					}
					//-------------------------------------------------------------------------------------------------------------------------------------------------------------//
					bEnemyd6.move(bed6enemySpeed * bed6enemyDirection, 0.f);

					if (bEnemyd6.getPosition().x < bed6LeftBound || bEnemyd6.getPosition().x > bed6rightBound) {
						if (bEnemyd6.getPosition().x < bed6LeftBound) {
							bed6enemyDirection = 1.0f;  // Move to the right
							bEnemyd6.setScale(-std::abs(bEnemyd6.getScale().x), 2.0f);
						}
						else {
							bed6enemyDirection = -1.0f;  // Move to the left

							bEnemyd6.setScale(std::abs(bEnemyd6.getScale().x), 2.0f);
						}
					}

					if (bed6frameCount == bed6switchFrame) {
						bed6frameCount = 0;
						if (bEnemyd6.getTextureRect().left == 0)
							bEnemyd6.setTextureRect(sf::IntRect(24, 0, 15, 14));
						else
							bEnemyd6.setTextureRect(sf::IntRect(0, 0, 15, 14));
					}
					else {
						bed6frameCount++;
					}
					//-------------------------------------------------------------------------------------------------------------------------------------------------------------//
					bEnemyd7.move(bed7enemySpeed * bed7enemyDirection, 0.f);

					if (bEnemyd7.getPosition().x < bed7LeftBound || bEnemyd7.getPosition().x > bed7rightBound) {
						if (bEnemyd7.getPosition().x < bed7LeftBound) {
							bed7enemyDirection = 1.0f;  // Move to the right
							bEnemyd7.setScale(-std::abs(bEnemyd7.getScale().x), 2.0f);
						}
						else {
							bed7enemyDirection = -1.0f;  // Move to the left

							bEnemyd7.setScale(std::abs(bEnemyd7.getScale().x), 2.0f);
						}
					}

					if (bed7frameCount == bed7switchFrame) {
						bed7frameCount = 0;
						if (bEnemyd7.getTextureRect().left == 0)
							bEnemyd7.setTextureRect(sf::IntRect(24, 0, 15, 14));
						else
							bEnemyd7.setTextureRect(sf::IntRect(0, 0, 15, 14));
					}
					else {
						bed7frameCount++;
					}
					//-------------------------------------------------------------------------------------------------------------------------------------------------------------//

							//RED ENEMY ANIMATION

					rEnemyd1.move(red1enemySpeed * red1enemyDirection, 0.f);

					if (rEnemyd1.getPosition().x < red1LeftBound || rEnemyd1.getPosition().x > red1rightBound) {
						if (rEnemyd1.getPosition().x < red1LeftBound) {
							red1enemyDirection = 1.0f;  // Move to the right
							rEnemyd1.setScale(-std::abs(rEnemyd1.getScale().x), 2.0f);
						}
						else {
							red1enemyDirection = -1.0f;  // Move to the left

							rEnemyd1.setScale(std::abs(rEnemyd1.getScale().x), 2.0f);
						}
					}

					if (red1frameCount == red1switchFrame) {
						red1frameCount = 0;
						if (rEnemyd1.getTextureRect().left == 0)
							rEnemyd1.setTextureRect(sf::IntRect(25, 0, 15, 19));
						else
							rEnemyd1.setTextureRect(sf::IntRect(0, 0, 15, 19));
					}
					else {
						red1frameCount++;
					}

					//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
					rEnemyd2.move(red2enemySpeed * red2enemyDirection, 0.f);

					if (rEnemyd2.getPosition().x < red2LeftBound || rEnemyd2.getPosition().x > red2rightBound) {
						if (rEnemyd2.getPosition().x < red2LeftBound) {
							red2enemyDirection = 1.0f;  // Move to the right
							rEnemyd2.setScale(-std::abs(rEnemyd2.getScale().x), 2.0f);
						}
						else {
							red2enemyDirection = -1.0f;  // Move to the left

							rEnemyd2.setScale(std::abs(rEnemyd2.getScale().x), 2.0f);
						}
					}

					if (red2frameCount == red2switchFrame) {
						red2frameCount = 0;
						if (rEnemyd2.getTextureRect().left == 0)
							rEnemyd2.setTextureRect(sf::IntRect(25, 0, 15, 19));
						else
							rEnemyd2.setTextureRect(sf::IntRect(0, 0, 15, 19));
					}
					else {
						red2frameCount++;
					}
					//-------------------------------------------------------------------------------------------------------------------------------------------------------------//
					rEnemyd3.move(red3enemySpeed * red3enemyDirection, 0.f);

					if (rEnemyd3.getPosition().x < red3LeftBound || rEnemyd3.getPosition().x > red3rightBound) {
						if (rEnemyd3.getPosition().x < red3LeftBound) {
							red3enemyDirection = 1.0f;  // Move to the right
							rEnemyd3.setScale(-std::abs(rEnemyd3.getScale().x), 2.0f);
						}
						else {
							red3enemyDirection = -1.0f;  // Move to the left

							rEnemyd3.setScale(std::abs(rEnemyd3.getScale().x), 2.0f);
						}
					}

					if (red3frameCount == red3switchFrame) {
						red3frameCount = 0;
						if (rEnemyd3.getTextureRect().left == 0)
							rEnemyd3.setTextureRect(sf::IntRect(25, 0, 15, 19));
						else
							rEnemyd3.setTextureRect(sf::IntRect(0, 0, 15, 19));
					}
					else {
						red3frameCount++;
					}
					//----------------------------------------------------------------------------------------------------------------------------------------------------------//
					rEnemyd4.move(red4enemySpeed * red4enemyDirection, 0.f);

					if (rEnemyd4.getPosition().x < red4LeftBound || rEnemyd4.getPosition().x > red4rightBound) {
						if (rEnemyd4.getPosition().x < red4LeftBound) {
							red4enemyDirection = 1.0f;  // Move to the right
							rEnemyd4.setScale(-std::abs(rEnemyd4.getScale().x), 2.0f);
						}
						else {
							red4enemyDirection = -1.0f;  // Move to the left

							rEnemyd4.setScale(std::abs(rEnemyd4.getScale().x), 2.0f);
						}
					}

					if (red4frameCount == red4switchFrame) {
						red4frameCount = 0;
						if (rEnemyd4.getTextureRect().left == 0)
							rEnemyd4.setTextureRect(sf::IntRect(25, 0, 15, 19));
						else
							rEnemyd4.setTextureRect(sf::IntRect(0, 0, 15, 19));
					}
					else {
						red4frameCount++;
					}
					//----------------------------------------------------------------------------------------------------------------------------------------------------------//
							//FLYING ENEMY
					fEnemyd1.move(fed1enemySpeed * fed1enemyDirection, 0.f);

					if (fEnemyd1.getPosition().x < fed1LeftBound || fEnemyd1.getPosition().x > fed1rightBound) {
						if (fEnemyd1.getPosition().x < fed1LeftBound) {
							fed1enemyDirection = 1.0f;  // Move to the right
							fEnemyd1.setScale(-std::abs(fEnemyd1.getScale().x), 2.0f);
						}
						else {
							fed1enemyDirection = -1.0f;  // Move to the left

							fEnemyd1.setScale(std::abs(fEnemyd1.getScale().x), 2.0f);
						}
					}

					if (fed1frameCount == fed1switchFrame) {
						fed1frameCount = 0;
						if (fEnemyd1.getTextureRect().left == 0)
						{
							fEnemyd1.setTextureRect(sf::IntRect(21, 0, 24, 16));
						}
						else if (fEnemyd1.getTextureRect().left == 21)
						{
							fEnemyd1.setTextureRect(sf::IntRect(45, 0, 24, 16));
						}
						else
						{
							fEnemyd1.setTextureRect(sf::IntRect(0, 0, 18, 17));
						}
					}
					else {
						fed1frameCount++;
					}
					//----------------------------------------------------------------------------------------------------------------------------------------------------------------//

					fEnemyd2.move(fed2enemySpeed * fed2enemyDirection, 0.f);

					if (fEnemyd2.getPosition().x < fed2LeftBound || fEnemyd2.getPosition().x > fed2rightBound) {
						if (fEnemyd2.getPosition().x < fed2LeftBound) {
							fed2enemyDirection = 1.0f;  // Move to the right
							fEnemyd2.setScale(-std::abs(fEnemyd2.getScale().x), 2.0f);
						}
						else {
							fed2enemyDirection = -1.0f;  // Move to the left

							fEnemyd2.setScale(std::abs(fEnemyd2.getScale().x), 2.0f);
						}
					}

					if (fed2frameCount == fed2switchFrame) {
						fed2frameCount = 0;
						if (fEnemyd2.getTextureRect().left == 0)
						{
							fEnemyd2.setTextureRect(sf::IntRect(21, 0, 24, 16));
						}
						else if (fEnemyd2.getTextureRect().left == 21)
						{
							fEnemyd2.setTextureRect(sf::IntRect(45, 0, 24, 16));
						}
						else
						{
							fEnemyd2.setTextureRect(sf::IntRect(0, 0, 18, 17));
						}
					}
					else {
						fed2frameCount++;
					}

					//-------------------------------------------------COLLISION CHECKS---------------------------------------------------------------------//

					if (player.getGlobalBounds().intersects(p3d.getGlobalBounds()))
					{
						// Check for downward collision (player is moving downwards)
						if (playerVelocityY > 0)
						{
							if (player.getPosition().y - playerBounds.height / 2 < p3d.getPosition().y)
							{
								// Calculate the new player position
								float newYp3d = p3d.getPosition().y - playerBounds.height / 2;

								// Adjust player position and velocity
								player.setPosition(player.getPosition().x, newYp3d);
								playerVelocityY = 0.f;
								jumpCount = 0;
							}
						}
					}

					//--------------------------------------------------------------------------------------------------------------------------------------------

					if (player.getGlobalBounds().intersects(sf::FloatRect(p3d.getGlobalBounds().left, p3d.getGlobalBounds().top, 0.5f, p3d.getGlobalBounds().height)))
					{
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && player.getPosition().x < p3d.getGlobalBounds().left && !hasCollidedWithLeftSide)
						{
							player.setPosition(p3d.getGlobalBounds().left - player.getGlobalBounds().width / 2.f, player.getPosition().y);
							hasCollidedWithLeftSide = true;
						}
						hasCollidedWithRightSide = false;
					}
					else if (player.getGlobalBounds().intersects(sf::FloatRect(p3d.getGlobalBounds().left + p3d.getGlobalBounds().width, p3d.getGlobalBounds().top, 1.f, p3d.getGlobalBounds().height)))
					{
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && player.getPosition().x > p3d.getGlobalBounds().left + p3d.getGlobalBounds().width && !hasCollidedWithRightSide)
						{
							player.setPosition(p3d.getGlobalBounds().left + p3d.getGlobalBounds().width + player.getGlobalBounds().width / 2.f, player.getPosition().y);
							hasCollidedWithRightSide = true;
						}
						hasCollidedWithLeftSide = false;
					}
					else {
						hasCollidedWithLeftSide = false;
						hasCollidedWithRightSide = false;
					}





					//----------------------------------------------------------------------------------------------------------------------------------------------


					if (player.getGlobalBounds().intersects(pd1.getGlobalBounds()))
					{
						// Check for downward collision (player is moving downwards)
						if (playerVelocityY > 0)
						{
							if (player.getPosition().y - playerBounds.height / 2 < pd1.getPosition().y)
							{
								// Calculate the new player position
								float newYpd1 = pd1.getPosition().y - playerBounds.height / 2;

								// Adjust player position and velocity
								player.setPosition(player.getPosition().x, newYpd1);
								playerVelocityY = 0.f;
								jumpCount = 0;
							}
						}
					}

					//-----------------------------------------------------------------------------------------------------------------------------------------
					if (player.getGlobalBounds().intersects(sf::FloatRect(pd1.getGlobalBounds().left, pd1.getGlobalBounds().top, 0.5f, pd1.getGlobalBounds().height)))
					{
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && player.getPosition().x < pd1.getGlobalBounds().left && !hasCollidedWithLeftSide)
						{
							player.setPosition(pd1.getGlobalBounds().left - player.getGlobalBounds().width / 2.f, player.getPosition().y);
							hasCollidedWithLeftSide = true;
						}
						hasCollidedWithRightSide = false;
					}
					else if (player.getGlobalBounds().intersects(sf::FloatRect(pd1.getGlobalBounds().left + pd1.getGlobalBounds().width, pd1.getGlobalBounds().top, 1.f, pd1.getGlobalBounds().height)))
					{
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && player.getPosition().x > pd1.getGlobalBounds().left + pd1.getGlobalBounds().width && !hasCollidedWithRightSide)
						{
							player.setPosition(pd1.getGlobalBounds().left + pd1.getGlobalBounds().width + player.getGlobalBounds().width / 2.f, player.getPosition().y);
							hasCollidedWithRightSide = true;
						}
						hasCollidedWithLeftSide = false;
					}
					else {
						hasCollidedWithLeftSide = false;
						hasCollidedWithRightSide = false;
					}

					//------------------------------------------------------------------------------------------------------------------------------------------

					if (player.getGlobalBounds().intersects(pd2.getGlobalBounds()))
					{
						// Check for downward collision (player is moving downwards)
						if (playerVelocityY > 0)
						{
							if (player.getPosition().y - playerBounds.height / 2 < pd2.getPosition().y)
							{
								// Calculate the new player position
								float newYpd2 = pd2.getPosition().y - playerBounds.height / 2;

								// Adjust player position and velocity
								player.setPosition(player.getPosition().x, newYpd2);
								playerVelocityY = 0.f;
								jumpCount = 0;
							}
						}
					}

					//---------------------------------------------------------------------------------------------------------------------------------------------
					if (player.getGlobalBounds().intersects(sf::FloatRect(pd2.getGlobalBounds().left, pd2.getGlobalBounds().top, 0.5f, pd2.getGlobalBounds().height)))
					{
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && player.getPosition().x < pd2.getGlobalBounds().left && !hasCollidedWithLeftSide)
						{
							player.setPosition(pd2.getGlobalBounds().left - player.getGlobalBounds().width / 2.f, player.getPosition().y);
							hasCollidedWithLeftSide = true;
						}
						hasCollidedWithRightSide = false;
					}
					else if (player.getGlobalBounds().intersects(sf::FloatRect(pd2.getGlobalBounds().left + pd2.getGlobalBounds().width, pd2.getGlobalBounds().top, 1.f, pd2.getGlobalBounds().height)))
					{
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && player.getPosition().x > pd2.getGlobalBounds().left + pd2.getGlobalBounds().width && !hasCollidedWithRightSide)
						{
							player.setPosition(pd2.getGlobalBounds().left + pd2.getGlobalBounds().width + player.getGlobalBounds().width / 2.f, player.getPosition().y);
							hasCollidedWithRightSide = true;
						}
						hasCollidedWithLeftSide = false;
					}
					else {
						hasCollidedWithLeftSide = false;
						hasCollidedWithRightSide = false;
					}
					//--------------------------------------------------------------------------------------------------------------------------------------------------

					if (player.getGlobalBounds().intersects(pd3.getGlobalBounds()))
					{
						// Check for downward collision (player is moving downwards)
						if (playerVelocityY > 0)
						{
							if (player.getPosition().y - playerBounds.height / 2 < pd3.getPosition().y)
							{
								// Calculate the new player position
								float newYpd3 = pd3.getPosition().y - playerBounds.height / 2;

								// Adjust player position and velocity
								player.setPosition(player.getPosition().x, newYpd3);
								playerVelocityY = 0.f;
								jumpCount = 0;
							}
						}
					}

					//-----------------------------------------------------------------------------------------------------------------------------------------------------
					if (player.getGlobalBounds().intersects(sf::FloatRect(pd3.getGlobalBounds().left, pd3.getGlobalBounds().top, 0.5f, pd3.getGlobalBounds().height)))
					{
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && player.getPosition().x < pd3.getGlobalBounds().left && !hasCollidedWithLeftSide)
						{
							player.setPosition(pd3.getGlobalBounds().left - player.getGlobalBounds().width / 2.f, player.getPosition().y);
							hasCollidedWithLeftSide = true;
						}
						hasCollidedWithRightSide = false;
					}
					else if (player.getGlobalBounds().intersects(sf::FloatRect(pd3.getGlobalBounds().left + pd3.getGlobalBounds().width, pd3.getGlobalBounds().top, 1.f, pd3.getGlobalBounds().height)))
					{
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && player.getPosition().x > pd3.getGlobalBounds().left + pd3.getGlobalBounds().width && !hasCollidedWithRightSide)
						{
							player.setPosition(pd3.getGlobalBounds().left + pd3.getGlobalBounds().width + player.getGlobalBounds().width / 2.f, player.getPosition().y);
							hasCollidedWithRightSide = true;
						}
						hasCollidedWithLeftSide = false;
					}
					else {
						hasCollidedWithLeftSide = false;
						hasCollidedWithRightSide = false;
					}

					//--------------------------------------------------------------------------------------------------------------------------------------------

					if (player.getGlobalBounds().intersects(pd4.getGlobalBounds()))
					{
						// Check for downward collision (player is moving downwards)
						if (playerVelocityY > 0)
						{
							if (player.getPosition().y - playerBounds.height / 2 < pd4.getPosition().y)
							{
								// Calculate the new player position
								float newYpd4 = pd4.getPosition().y - playerBounds.height / 2;

								// Adjust player position and velocity
								player.setPosition(player.getPosition().x, newYpd4);
								playerVelocityY = 0.f;
								jumpCount = 0;
							}
						}
					}

					//----------------------------------------------------------------------------------------------------------------------------------------------
					if (player.getGlobalBounds().intersects(sf::FloatRect(pd4.getGlobalBounds().left, pd4.getGlobalBounds().top, 0.5f, pd4.getGlobalBounds().height)))
					{
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && player.getPosition().x < pd4.getGlobalBounds().left && !hasCollidedWithLeftSide)
						{
							player.setPosition(pd4.getGlobalBounds().left - player.getGlobalBounds().width / 2.f, player.getPosition().y);
							hasCollidedWithLeftSide = true;
						}
						hasCollidedWithRightSide = false;
					}
					else if (player.getGlobalBounds().intersects(sf::FloatRect(pd4.getGlobalBounds().left + pd4.getGlobalBounds().width, pd4.getGlobalBounds().top, 1.f, pd4.getGlobalBounds().height)))
					{
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && player.getPosition().x > pd4.getGlobalBounds().left + pd4.getGlobalBounds().width && !hasCollidedWithRightSide)
						{
							player.setPosition(pd4.getGlobalBounds().left + pd4.getGlobalBounds().width + player.getGlobalBounds().width / 2.f, player.getPosition().y);
							hasCollidedWithRightSide = true;
						}
						hasCollidedWithLeftSide = false;
					}
					else {
						hasCollidedWithLeftSide = false;
						hasCollidedWithRightSide = false;
					}
					//----------------------------------------------------------------------------------------------

					if (player.getGlobalBounds().intersects(pd5.getGlobalBounds()))
					{
						// Check for downward collision (player is moving downwards)
						if (playerVelocityY > 0)
						{
							if (player.getPosition().y - playerBounds.height / 2 < pd5.getPosition().y)
							{
								// Calculate the new player position
								float newYpd5 = pd5.getPosition().y - playerBounds.height / 2;

								// Adjust player position and velocity
								player.setPosition(player.getPosition().x, newYpd5);
								playerVelocityY = 0.f;
								jumpCount = 0;
							}
						}
					}

					//-----------------------------------------------------------------------------------------------

					if (player.getGlobalBounds().intersects(sf::FloatRect(pd5.getGlobalBounds().left, pd5.getGlobalBounds().top, 0.5f, pd5.getGlobalBounds().height)))
					{
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && player.getPosition().x < pd5.getGlobalBounds().left && !hasCollidedWithLeftSide)
						{
							player.setPosition(pd5.getGlobalBounds().left - player.getGlobalBounds().width / 2.f, player.getPosition().y);
							hasCollidedWithLeftSide = true;
						}
						hasCollidedWithRightSide = false;
					}
					else if (player.getGlobalBounds().intersects(sf::FloatRect(pd5.getGlobalBounds().left + pd5.getGlobalBounds().width, pd5.getGlobalBounds().top, 1.f, pd5.getGlobalBounds().height)))
					{
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && player.getPosition().x > pd5.getGlobalBounds().left + pd5.getGlobalBounds().width && !hasCollidedWithRightSide)
						{
							player.setPosition(pd5.getGlobalBounds().left + pd5.getGlobalBounds().width + player.getGlobalBounds().width / 2.f, player.getPosition().y);
							hasCollidedWithRightSide = true;
						}
						hasCollidedWithLeftSide = false;
					}
					else {
						hasCollidedWithLeftSide = false;
						hasCollidedWithRightSide = false;
					}
					//---------------------------------------------------------------------------------------
					if (player.getGlobalBounds().intersects(pd6.getGlobalBounds()))
					{
						// Check for downward collision (player is moving downwards)
						if (playerVelocityY > 0)
						{
							if (player.getPosition().y - playerBounds.height / 2 < pd6.getPosition().y)
							{
								// Calculate the new player position
								float newYpd6 = pd6.getPosition().y - playerBounds.height / 2;

								// Adjust player position and velocity
								player.setPosition(player.getPosition().x, newYpd6);
								playerVelocityY = 0.f;
								jumpCount = 0;
							}
						}
					}

					//----------------------------------------------------------------------------------------------
					if (player.getGlobalBounds().intersects(sf::FloatRect(pd6.getGlobalBounds().left, pd6.getGlobalBounds().top, 0.5f, pd6.getGlobalBounds().height)))
					{
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && player.getPosition().x < pd6.getGlobalBounds().left && !hasCollidedWithLeftSide)
						{
							player.setPosition(pd6.getGlobalBounds().left - player.getGlobalBounds().width / 2.f, player.getPosition().y);
							hasCollidedWithLeftSide = true;
						}
						hasCollidedWithRightSide = false;
					}
					else if (player.getGlobalBounds().intersects(sf::FloatRect(pd6.getGlobalBounds().left + pd6.getGlobalBounds().width, pd6.getGlobalBounds().top, 1.f, pd6.getGlobalBounds().height)))
					{
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && player.getPosition().x > pd6.getGlobalBounds().left + pd6.getGlobalBounds().width && !hasCollidedWithRightSide)
						{
							player.setPosition(pd6.getGlobalBounds().left + pd6.getGlobalBounds().width + player.getGlobalBounds().width / 2.f, player.getPosition().y);
							hasCollidedWithRightSide = true;
						}
						hasCollidedWithLeftSide = false;
					}
					else {
						hasCollidedWithLeftSide = false;
						hasCollidedWithRightSide = false;
					}
					//--------------------------------------------------------------------------------------------------------------------------------------------

					if (player.getGlobalBounds().intersects(pd7.getGlobalBounds()))
					{
						// Check for downward collision (player is moving downwards)
						if (playerVelocityY > 0)
						{
							if (player.getPosition().y - playerBounds.height / 2 < pd7.getPosition().y)
							{
								// Calculate the new player position
								float newYpd7 = pd7.getPosition().y - playerBounds.height / 2;

								// Adjust player position and velocity
								player.setPosition(player.getPosition().x, newYpd7);
								playerVelocityY = 0.f;
								jumpCount = 0;
							}
						}
					}

					//------------------------------------------------------------------------------------------------------------------------------------------------------
					if (player.getGlobalBounds().intersects(sf::FloatRect(pd7.getGlobalBounds().left, pd7.getGlobalBounds().top, 0.5f, pd7.getGlobalBounds().height)))
					{
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && player.getPosition().x < pd7.getGlobalBounds().left && !hasCollidedWithLeftSide)
						{
							player.setPosition(pd7.getGlobalBounds().left - player.getGlobalBounds().width / 2.f, player.getPosition().y);
							hasCollidedWithLeftSide = true;
						}
						hasCollidedWithRightSide = false;
					}
					else if (player.getGlobalBounds().intersects(sf::FloatRect(pd7.getGlobalBounds().left + pd7.getGlobalBounds().width, pd7.getGlobalBounds().top, 1.f, pd7.getGlobalBounds().height)))
					{
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && player.getPosition().x > pd7.getGlobalBounds().left + pd7.getGlobalBounds().width && !hasCollidedWithRightSide)
						{
							player.setPosition(pd7.getGlobalBounds().left + pd7.getGlobalBounds().width + player.getGlobalBounds().width / 2.f, player.getPosition().y);
							hasCollidedWithRightSide = true;
						}
						hasCollidedWithLeftSide = false;
					}
					else {
						hasCollidedWithLeftSide = false;
						hasCollidedWithRightSide = false;
					}
					//---------------------------------------------------------------------------------------
					if (player.getGlobalBounds().intersects(pd8.getGlobalBounds()))
					{
						// Check for downward collision (player is moving downwards)
						if (playerVelocityY > 0)
						{
							if (player.getPosition().y - playerBounds.height / 2 < pd8.getPosition().y)
							{
								// Calculate the new player position
								float newYpd8 = pd8.getPosition().y - playerBounds.height / 2;

								// Adjust player position and velocity
								player.setPosition(player.getPosition().x, newYpd8);
								playerVelocityY = 0.f;
								jumpCount = 0;
							}
						}
					}
					//--------------------------------------------------------------------------------------------------------
					if (player.getGlobalBounds().intersects(sf::FloatRect(pd8.getGlobalBounds().left, pd8.getGlobalBounds().top, 0.5f, pd8.getGlobalBounds().height)))
					{
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && player.getPosition().x < pd8.getGlobalBounds().left && !hasCollidedWithLeftSide)
						{
							player.setPosition(pd8.getGlobalBounds().left - player.getGlobalBounds().width / 2.f, player.getPosition().y);
							hasCollidedWithLeftSide = true;
						}
						hasCollidedWithRightSide = false;
					}
					else if (player.getGlobalBounds().intersects(sf::FloatRect(pd8.getGlobalBounds().left + pd8.getGlobalBounds().width, pd8.getGlobalBounds().top, 1.f, pd8.getGlobalBounds().height)))
					{
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && player.getPosition().x > pd8.getGlobalBounds().left + pd8.getGlobalBounds().width && !hasCollidedWithRightSide)
						{
							player.setPosition(pd8.getGlobalBounds().left + pd8.getGlobalBounds().width + player.getGlobalBounds().width / 2.f, player.getPosition().y);
							hasCollidedWithRightSide = true;
						}
						hasCollidedWithLeftSide = false;
					}
					else {
						hasCollidedWithLeftSide = false;
						hasCollidedWithRightSide = false;
					}
					//---------------------------------------------------------------------------------------------------------------------------------------
					if (player.getGlobalBounds().intersects(pd9.getGlobalBounds()))
					{
						// Check for downward collision (player is moving downwards)
						if (playerVelocityY > 0)
						{
							if (player.getPosition().y - playerBounds.height / 2 < pd9.getPosition().y)
							{
								// Calculate the new player position
								float newYpd9 = pd9.getPosition().y - playerBounds.height / 2;

								// Adjust player position and velocity
								player.setPosition(player.getPosition().x, newYpd9);
								playerVelocityY = 0.f;
								jumpCount = 0;
							}
						}
					}

					if (player.getGlobalBounds().intersects(sf::FloatRect(pd9.getGlobalBounds().left, pd9.getGlobalBounds().top, 0.5f, pd9.getGlobalBounds().height)))
					{
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && player.getPosition().x < pd9.getGlobalBounds().left && !hasCollidedWithLeftSide)
						{
							player.setPosition(pd9.getGlobalBounds().left - player.getGlobalBounds().width / 2.f, player.getPosition().y);
							hasCollidedWithLeftSide = true;
						}
						hasCollidedWithRightSide = false;
					}
					else if (player.getGlobalBounds().intersects(sf::FloatRect(pd9.getGlobalBounds().left + pd9.getGlobalBounds().width, pd9.getGlobalBounds().top, 1.f, pd9.getGlobalBounds().height)))
					{
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && player.getPosition().x > pd9.getGlobalBounds().left + pd9.getGlobalBounds().width && !hasCollidedWithRightSide)
						{
							player.setPosition(pd9.getGlobalBounds().left + pd9.getGlobalBounds().width + player.getGlobalBounds().width / 2.f, player.getPosition().y);
							hasCollidedWithRightSide = true;
						}
						hasCollidedWithLeftSide = false;
					}
					else {
						hasCollidedWithLeftSide = false;
						hasCollidedWithRightSide = false;
					}
					//---------------------------------------------------------------------------------------------------------
					if (player.getGlobalBounds().intersects(pd10.getGlobalBounds()))
					{
						// Check for downward collision (player is moving downwards)
						if (playerVelocityY > 0)
						{
							if (player.getPosition().y - playerBounds.height / 2 < pd10.getPosition().y)
							{
								// Calculate the new player position
								float newYpd10 = pd10.getPosition().y - playerBounds.height / 2;

								// Adjust player position and velocity
								player.setPosition(player.getPosition().x, newYpd10);
								playerVelocityY = 0.f;
								jumpCount = 0;
							}
						}
					}

					if (player.getGlobalBounds().intersects(sf::FloatRect(pd10.getGlobalBounds().left, pd10.getGlobalBounds().top, 0.5f, pd10.getGlobalBounds().height)))
					{
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && player.getPosition().x < pd10.getGlobalBounds().left && !hasCollidedWithLeftSide)
						{
							player.setPosition(pd10.getGlobalBounds().left - player.getGlobalBounds().width / 2.f, player.getPosition().y);
							hasCollidedWithLeftSide = true;
						}
						hasCollidedWithRightSide = false;
					}
					else if (player.getGlobalBounds().intersects(sf::FloatRect(pd10.getGlobalBounds().left + pd10.getGlobalBounds().width, pd10.getGlobalBounds().top, 1.f, pd10.getGlobalBounds().height)))
					{
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && player.getPosition().x > pd10.getGlobalBounds().left + pd10.getGlobalBounds().width && !hasCollidedWithRightSide)
						{
							player.setPosition(pd10.getGlobalBounds().left + pd10.getGlobalBounds().width + player.getGlobalBounds().width / 2.f, player.getPosition().y);
							hasCollidedWithRightSide = true;
						}
						hasCollidedWithLeftSide = false;
					}
					else {
						hasCollidedWithLeftSide = false;
						hasCollidedWithRightSide = false;
					}

					if (player.getGlobalBounds().intersects(springd1.getGlobalBounds())) {
						if (!isSpringActivated && playerVelocityY > 0) {
							// Player jumps on the spring while moving downward, activate it
							isSpringActivated = true;
							playerVelocityY = -15.0f; // Adjust the vertical force as needed
							springd1.setTextureRect(sf::IntRect(19, 0, 18, 14)); // Assuming second frame starts at x=32
							jumpSound.play();
						}
					}
					else {
						isSpringActivated = false;
						springd1.setTextureRect(sf::IntRect(0, 0, 18, 14));
					}

					if (player.getGlobalBounds().intersects(springd2.getGlobalBounds())) {
						if (!isSpringActivated && playerVelocityY > 0) {
							// Player jumps on the spring while moving downward, activate it
							isSpringActivated = true;
							playerVelocityY = -15.0f; // Adjust the vertical force as needed
							springd2.setTextureRect(sf::IntRect(19, 0, 18, 14)); // Assuming second frame starts at x=32
							jumpSound.play();
						}
					}
					else {
						isSpringActivated = false;
						springd2.setTextureRect(sf::IntRect(0, 0, 18, 14));
					}

					if (player.getGlobalBounds().intersects(springd3.getGlobalBounds())) {
						if (!isSpringActivated && playerVelocityY > 0) {
							// Player jumps on the spring while moving downward, activate it
							isSpringActivated = true;
							playerVelocityY = -15.0f; // Adjust the vertical force as needed
							springd3.setTextureRect(sf::IntRect(19, 0, 18, 14)); // Assuming second frame starts at x=32
							jumpSound.play();
						}
					}
					else {
						isSpringActivated = false;
						springd3.setTextureRect(sf::IntRect(0, 0, 18, 14));
					}

					if (player.getGlobalBounds().intersects(springd4.getGlobalBounds())) {
						if (!isSpringActivated && playerVelocityY > 0) {
							// Player jumps on the spring while moving downward, activate it
							isSpringActivated = true;
							playerVelocityY = -15.0f; // Adjust the vertical force as needed
							springd4.setTextureRect(sf::IntRect(19, 0, 18, 14)); // Assuming second frame starts at x=32
							jumpSound.play();
						}
					}
					else {
						isSpringActivated = false;
						springd4.setTextureRect(sf::IntRect(0, 0, 18, 14));
					}

					if (player.getGlobalBounds().intersects(springd5.getGlobalBounds())) {
						if (!isSpringActivated && playerVelocityY > 0) {
							// Player jumps on the spring while moving downward, activate it
							isSpringActivated = true;
							playerVelocityY = -15.0f; // Adjust the vertical force as needed
							springd5.setTextureRect(sf::IntRect(19, 0, 18, 14)); // Assuming second frame starts at x=32
							jumpSound.play();
						}
					}
					else {
						isSpringActivated = false;
						springd5.setTextureRect(sf::IntRect(0, 0, 18, 14));
					}

					if (player.getGlobalBounds().intersects(springd6.getGlobalBounds())) {
						if (!isSpringActivated && playerVelocityY > 0) {
							// Player jumps on the spring while moving downward, activate it
							isSpringActivated = true;
							playerVelocityY = -15.0f; // Adjust the vertical force as needed
							springd6.setTextureRect(sf::IntRect(19, 0, 18, 14)); // Assuming second frame starts at x=32
							jumpSound.play();
						}
					}
					else {
						isSpringActivated = false;
						springd6.setTextureRect(sf::IntRect(0, 0, 18, 14));
					}

					if (player.getGlobalBounds().intersects(springd7.getGlobalBounds())) {
						if (!isSpringActivated && playerVelocityY > 0) {
							// Player jumps on the spring while moving downward, activate it
							isSpringActivated = true;
							playerVelocityY = -15.0f; // Adjust the vertical force as needed
							springd7.setTextureRect(sf::IntRect(19, 0, 18, 14)); // Assuming second frame starts at x=32
							jumpSound.play();
						}
					}
					else {
						isSpringActivated = false;
						springd7.setTextureRect(sf::IntRect(0, 0, 18, 14));
					}

					if (player.getGlobalBounds().intersects(springd8.getGlobalBounds())) {
						if (!isSpringActivated && playerVelocityY > 0) {
							// Player jumps on the spring while moving downward, activate it
							isSpringActivated = true;
							playerVelocityY = -15.0f; // Adjust the vertical force as needed
							springd8.setTextureRect(sf::IntRect(19, 0, 18, 14)); // Assuming second frame starts at x=32
							jumpSound.play();
						}
					}
					else {
						isSpringActivated = false;
						springd8.setTextureRect(sf::IntRect(0, 0, 18, 14));
					}

					if (player.getGlobalBounds().intersects(springd9.getGlobalBounds())) {
						if (!isSpringActivated && playerVelocityY > 0) {
							// Player jumps on the spring while moving downward, activate it
							isSpringActivated = true;
							playerVelocityY = -15.0f; // Adjust the vertical force as needed
							springd9.setTextureRect(sf::IntRect(19, 0, 18, 14)); // Assuming second frame starts at x=32
							jumpSound.play();
						}
					}
					else {
						isSpringActivated = false;
						springd9.setTextureRect(sf::IntRect(0, 0, 18, 14));
					}

					if (player.getGlobalBounds().intersects(springd10.getGlobalBounds())) {
						if (!isSpringActivated && playerVelocityY > 0) {
							// Player jumps on the spring while moving downward, activate it
							isSpringActivated = true;
							playerVelocityY = -15.0f; // Adjust the vertical force as needed
							springd10.setTextureRect(sf::IntRect(19, 0, 18, 14)); // Assuming second frame starts at x=32
							jumpSound.play();
						}
					}
					else {
						isSpringActivated = false;
						springd10.setTextureRect(sf::IntRect(0, 0, 18, 14));
					}

					if (player.getGlobalBounds().intersects(springd11.getGlobalBounds())) {
						if (!isSpringActivated && playerVelocityY > 0) {
							// Player jumps on the spring while moving downward, activate it
							isSpringActivated = true;
							playerVelocityY = -15.0f; // Adjust the vertical force as needed
							springd11.setTextureRect(sf::IntRect(19, 0, 18, 14)); // Assuming second frame starts at x=32
							jumpSound.play();
						}
					}
					else {
						isSpringActivated = false;
						springd11.setTextureRect(sf::IntRect(0, 0, 18, 14));
					}

					if (player.getGlobalBounds().intersects(springd12.getGlobalBounds())) {
						if (!isSpringActivated && playerVelocityY > 0) {
							// Player jumps on the spring while moving downward, activate it
							isSpringActivated = true;
							playerVelocityY = -20.0f; // Adjust the vertical force as needed
							springd12.setTextureRect(sf::IntRect(19, 0, 18, 14)); // Assuming second frame starts at x=32
							jumpSound.play();
						}
					}
					else {
						isSpringActivated = false;
						springd12.setTextureRect(sf::IntRect(0, 0, 18, 14));
					}

					if (player.getGlobalBounds().intersects(springd13.getGlobalBounds())) {
						if (!isSpringActivated && playerVelocityY > 0) {
							// Player jumps on the spring while moving downward, activate it
							isSpringActivated = true;
							playerVelocityY = -15.0f; // Adjust the vertical force as needed
							springd13.setTextureRect(sf::IntRect(19, 0, 18, 14)); // Assuming second frame starts at x=32
							jumpSound.play();
						}
					}
					else {
						isSpringActivated = false;
						springd13.setTextureRect(sf::IntRect(0, 0, 18, 14));
					}

					if (player.getGlobalBounds().intersects(spiked1.getGlobalBounds()) && damageCooldown.getElapsedTime() > coolDownDuration)
					{
						playerVelocityY = -12.f;
						currentHealth--;

						spikeStabSound.play();

						blinkingTimer.restart();
						damageCooldown.restart();
					}

					if (player.getGlobalBounds().intersects(spiked2.getGlobalBounds()) && damageCooldown.getElapsedTime() > coolDownDuration)
					{
						playerVelocityY = -12.f;
						currentHealth--;

						spikeStabSound.play();

						blinkingTimer.restart();
						damageCooldown.restart();
					}

					if (player.getGlobalBounds().intersects(spiked3.getGlobalBounds()) && damageCooldown.getElapsedTime() > coolDownDuration)
					{
						playerVelocityY = -12.f;
						currentHealth--;

						spikeStabSound.play();

						blinkingTimer.restart();
						damageCooldown.restart();
					}

					if (player.getGlobalBounds().intersects(spiked4.getGlobalBounds()) && damageCooldown.getElapsedTime() > coolDownDuration)
					{
						playerVelocityY = -12.f;
						currentHealth--;

						spikeStabSound.play();

						blinkingTimer.restart();
						damageCooldown.restart();
					}

					if (player.getGlobalBounds().intersects(spiked5.getGlobalBounds()) && damageCooldown.getElapsedTime() > coolDownDuration)
					{
						playerVelocityY = -12.f;
						currentHealth--;

						spikeStabSound.play();

						blinkingTimer.restart();
						damageCooldown.restart();
					}

					if (player.getGlobalBounds().intersects(spiked6.getGlobalBounds()) && damageCooldown.getElapsedTime() > coolDownDuration)
					{
						playerVelocityY = -12.f;
						currentHealth--;

						spikeStabSound.play();

						blinkingTimer.restart();
						damageCooldown.restart();
					}

					if (player.getGlobalBounds().intersects(spiked7.getGlobalBounds()) && damageCooldown.getElapsedTime() > coolDownDuration)
					{
						playerVelocityY = -12.f;
						currentHealth--;

						spikeStabSound.play();

						blinkingTimer.restart();
						damageCooldown.restart();
					}

					if (player.getGlobalBounds().intersects(spiked8.getGlobalBounds()) && damageCooldown.getElapsedTime() > coolDownDuration)
					{
						playerVelocityY = -12.f;
						currentHealth--;

						spikeStabSound.play();

						blinkingTimer.restart();
						damageCooldown.restart();
					}

					if (player.getGlobalBounds().intersects(spiked9.getGlobalBounds()) && damageCooldown.getElapsedTime() > coolDownDuration)
					{
						playerVelocityY = -12.f;
						currentHealth--;

						spikeStabSound.play();

						blinkingTimer.restart();
						damageCooldown.restart();
					}

					if (player.getGlobalBounds().intersects(spiked10.getGlobalBounds()) && damageCooldown.getElapsedTime() > coolDownDuration)
					{
						playerVelocityY = -12.f;
						currentHealth--;

						spikeStabSound.play();

						blinkingTimer.restart();
						damageCooldown.restart();
					}

					if (player.getGlobalBounds().intersects(spiked11.getGlobalBounds()) && damageCooldown.getElapsedTime() > coolDownDuration)
					{
						playerVelocityY = -12.f;
						currentHealth--;

						spikeStabSound.play();

						blinkingTimer.restart();
						damageCooldown.restart();
					}

					

					if (player.getGlobalBounds().intersects(chisTrio1.getGlobalBounds()))
					{
						// Check for downward collision (player is moving downwards)
						if (playerVelocityY > 0 )
						{
							if (player.getPosition().y - playerBounds.height / 2 < chisTrio1.getPosition().y )
							{
								// Calculate the new player position
								float newYct1 = chisTrio1.getPosition().y - playerBounds.height / 2;

								// Adjust player position and velocity
								player.setPosition(player.getPosition().x, newYct1);
								playerVelocityY = 0.f;
								jumpCount = 0;
							}
						}
					}


					if (player.getGlobalBounds().intersects(chisTrio1.getGlobalBounds()))
					{
						if (playerVelocityY > 0 && sf::Keyboard::isKeyPressed(sf::Keyboard::W))
						{
							if (player.getPosition().y < chisTrio1.getPosition().y)
							{
								player.setPosition(player.getPosition().x, chisTrio1.getPosition().y - player.getGlobalBounds().height / 2);
								playerVelocityY = 10.f;
								jumpCount = 0;
							}
						}
					}


					if (player.getGlobalBounds().intersects(sf::FloatRect(chisTrio1Bounds.left, chisTrio1Bounds.top + chisTrio1Bounds.height - 1, chisTrio1Bounds.width, 1.f))) {
						// Player intersects with the bottom side of the platform

						// Check if the player is moving upwards (jumping)
						if (playerVelocityY < 0) {
							// Adjust player's position only if moving upwards
							player.setPosition(player.getPosition().x, chisTrio1Bounds.top + chisTrio1Bounds.height);
							playerVelocityY = 0.f; // Set vertical velocity to zero to stop upward movement
							isJumping = false; // Reset jump state
							jumpCount = 0; // Reset jump count
						}
					}
					//----------------------------------------------------------------------------------------------------------------------
					if (player.getGlobalBounds().intersects(chisCut.getGlobalBounds()))
					{
						// Check for downward collision (player is moving downwards)
						if (playerVelocityY > 0)
						{
							if (player.getPosition().y - playerBounds.height / 2 < chisCut.getPosition().y)
							{
								// Calculate the new player position
								float newYcut1 = chisCut.getPosition().y - playerBounds.height / 2;

								// Adjust player position and velocity
								player.setPosition(player.getPosition().x, newYcut1);
								playerVelocityY = 0.f;
								jumpCount = 0;
							}
						}
					}


					if (playerBounds.intersects(sf::FloatRect(chisCutBounds.left, chisCutBounds.top, 0.5f, chisCutBounds.height)))
					{
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && player.getPosition().x < chisCutBounds.left && !hasCollidedWithLeftSide) //LEFT SIDE
						{
							player.setPosition(chisCutBounds.left - playerBounds.width / 2.f, player.getPosition().y);
							hasCollidedWithLeftSide = true;
						}
						hasCollidedWithRightSide = false;
					}
					else if (playerBounds.intersects(sf::FloatRect(chisCutBounds.left + chisCutBounds.width, chisCutBounds.top, 1.f, chisCutBounds.height)))
					{
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && player.getPosition().x > chisCutBounds.left + chisCutBounds.width && !hasCollidedWithRightSide)
						{
							player.setPosition(chisCutBounds.left + chisCutBounds.width + playerBounds.width / 2.f, player.getPosition().y);
							hasCollidedWithRightSide = true;
						}
						hasCollidedWithLeftSide = false;
					}
					else {
						hasCollidedWithLeftSide = false;
						hasCollidedWithRightSide = false;
					}
					//------------------------------------------------------------------------------------------------------------------------

					//CLOUDS
					if (player.getGlobalBounds().intersects(cloud1d.getGlobalBounds()))
					{
						// Check for downward collision (player is moving downwards)
						if (playerVelocityY > 0)
						{
							if (player.getPosition().y - playerBounds.height / 2 < cloud1d.getPosition().y)
							{
								// Calculate the new player position
								float newYcl1d = cloud1d.getPosition().y - playerBounds.height / 2;

								// Adjust player position and velocity
								player.setPosition(player.getPosition().x, newYcl1d);
								playerVelocityY = 0.f;
								jumpCount = 0;
							}
						}
					}

					if (player.getGlobalBounds().intersects(cloud2d.getGlobalBounds()))
					{
						// Check for downward collision (player is moving downwards)
						if (playerVelocityY > 0)
						{
							if (player.getPosition().y - playerBounds.height / 2 < cloud2d.getPosition().y)
							{
								// Calculate the new player position
								float newYcl2d = cloud2d.getPosition().y - playerBounds.height / 2;

								// Adjust player position and velocity
								player.setPosition(player.getPosition().x, newYcl2d);
								playerVelocityY = 0.f;
								jumpCount = 0;
							}
						}
					}

					if (player.getGlobalBounds().intersects(cloud3d.getGlobalBounds()))
					{
						// Check for downward collision (player is moving downwards)
						if (playerVelocityY > 0)
						{
							if (player.getPosition().y - playerBounds.height / 2 < cloud3d.getPosition().y)
							{
								// Calculate the new player position
								float newYcl3d = cloud3d.getPosition().y - playerBounds.height / 2;

								// Adjust player position and velocity
								player.setPosition(player.getPosition().x, newYcl3d);
								playerVelocityY = 0.f;
								jumpCount = 0;
							}
						}
					}

					if (player.getGlobalBounds().intersects(cloud4d.getGlobalBounds()))
					{
						// Check for downward collision (player is moving downwards)
						if (playerVelocityY > 0)
						{
							if (player.getPosition().y - playerBounds.height / 2 < cloud4d.getPosition().y)
							{
								// Calculate the new player position
								float newYcl4d = cloud4d.getPosition().y - playerBounds.height / 2;

								// Adjust player position and velocity
								player.setPosition(player.getPosition().x, newYcl4d);
								playerVelocityY = 0.f;
								jumpCount = 0;
							}
						}
					}

					if (player.getGlobalBounds().intersects(cloud5d.getGlobalBounds()))
					{
						// Check for downward collision (player is moving downwards)
						if (playerVelocityY > 0)
						{
							if (player.getPosition().y - playerBounds.height / 2 < cloud5d.getPosition().y)
							{
								// Calculate the new player position
								float newYcl5d = cloud5d.getPosition().y - playerBounds.height / 2;

								// Adjust player position and velocity
								player.setPosition(player.getPosition().x, newYcl5d);
								playerVelocityY = 0.f;
								jumpCount = 0;
							}
						}
					}

					if (player.getGlobalBounds().intersects(cloud6d.getGlobalBounds()))
					{
						// Check for downward collision (player is moving downwards)
						if (playerVelocityY > 0)
						{
							if (player.getPosition().y - playerBounds.height / 2 < cloud6d.getPosition().y)
							{
								// Calculate the new player position
								float newYcl6d = cloud6d.getPosition().y - playerBounds.height / 2;

								// Adjust player position and velocity
								player.setPosition(player.getPosition().x, newYcl6d);
								playerVelocityY = 0.f;
								jumpCount = 0;
							}
						}
					}

					if (player.getGlobalBounds().intersects(cloud7d.getGlobalBounds()))
					{
						// Check for downward collision (player is moving downwards)
						if (playerVelocityY > 0)
						{
							if (player.getPosition().y - playerBounds.height / 2 < cloud7d.getPosition().y)
							{
								// Calculate the new player position
								float newYcl7d = cloud7d.getPosition().y - playerBounds.height / 2;

								// Adjust player position and velocity
								player.setPosition(player.getPosition().x, newYcl7d);
								playerVelocityY = 0.f;
								jumpCount = 0;
							}
						}
					}

					if (player.getGlobalBounds().intersects(cloud8d.getGlobalBounds()))
					{
						// Check for downward collision (player is moving downwards)
						if (playerVelocityY > 0)
						{
							if (player.getPosition().y - playerBounds.height / 2 < cloud8d.getPosition().y)
							{
								// Calculate the new player position
								float newYcl8d = cloud8d.getPosition().y - playerBounds.height / 2;

								// Adjust player position and velocity
								player.setPosition(player.getPosition().x, newYcl8d);
								playerVelocityY = 0.f;
								jumpCount = 0;
							}
						}
					}

					if (player.getGlobalBounds().intersects(cloud9d.getGlobalBounds()))
					{
						// Check for downward collision (player is moving downwards)
						if (playerVelocityY > 0)
						{
							if (player.getPosition().y - playerBounds.height / 2 < cloud9d.getPosition().y)
							{
								// Calculate the new player position
								float newYcl9d = cloud9d.getPosition().y - playerBounds.height / 2;

								// Adjust player position and velocity
								player.setPosition(player.getPosition().x, newYcl9d);
								playerVelocityY = 0.f;
								jumpCount = 0;
							}
						}
					}

					if (player.getGlobalBounds().intersects(cloud10d.getGlobalBounds()))
					{
						// Check for downward collision (player is moving downwards)
						if (playerVelocityY > 0)
						{
							if (player.getPosition().y - playerBounds.height / 2 < cloud10d.getPosition().y)
							{
								// Calculate the new player position
								float newYcl10d = cloud10d.getPosition().y - playerBounds.height / 2;

								// Adjust player position and velocity
								player.setPosition(player.getPosition().x, newYcl10d);
								playerVelocityY = 0.f;
								jumpCount = 0;
							}
						}
					}

					if (player.getGlobalBounds().intersects(cloud11d.getGlobalBounds()))
					{
						// Check for downward collision (player is moving downwards)
						if (playerVelocityY > 0)
						{
							if (player.getPosition().y - playerBounds.height / 2 < cloud11d.getPosition().y)
							{
								// Calculate the new player position
								float newYcl11d = cloud11d.getPosition().y - playerBounds.height / 2;

								// Adjust player position and velocity
								player.setPosition(player.getPosition().x, newYcl11d);
								playerVelocityY = 0.f;
								jumpCount = 0;
							}
						}
					}

					if (player.getGlobalBounds().intersects(cloud12d.getGlobalBounds()))
					{
						// Check for downward collision (player is moving downwards)
						if (playerVelocityY > 0)
						{
							if (player.getPosition().y - playerBounds.height / 2 < cloud12d.getPosition().y)
							{
								// Calculate the new player position
								float newYcl12d = cloud12d.getPosition().y - playerBounds.height / 2;

								// Adjust player position and velocity
								player.setPosition(player.getPosition().x, newYcl12d);
								playerVelocityY = 0.f;
								jumpCount = 0;
							}
						}
					}

					if (player.getGlobalBounds().intersects(cloud13d.getGlobalBounds()))
					{
						// Check for downward collision (player is moving downwards)
						if (playerVelocityY > 0)
						{
							if (player.getPosition().y - playerBounds.height / 2 < cloud13d.getPosition().y)
							{
								// Calculate the new player position
								float newYcl13d = cloud13d.getPosition().y - playerBounds.height / 2;

								// Adjust player position and velocity
								player.setPosition(player.getPosition().x, newYcl13d);
								playerVelocityY = 0.f;
								jumpCount = 0;
							}
						}
					}

					if (player.getGlobalBounds().intersects(cloud14d.getGlobalBounds()))
					{
						// Check for downward collision (player is moving downwards)
						if (playerVelocityY > 0)
						{
							if (player.getPosition().y - playerBounds.height / 2 < cloud14d.getPosition().y)
							{
								// Calculate the new player position
								float newYcl14d = cloud14d.getPosition().y - playerBounds.height / 2;

								// Adjust player position and velocity
								player.setPosition(player.getPosition().x, newYcl14d);
								playerVelocityY = 0.f;
								jumpCount = 0;
							}
						}
					}

					if (player.getGlobalBounds().intersects(cloud15d.getGlobalBounds()))
					{
						// Check for downward collision (player is moving downwards)
						if (playerVelocityY > 0)
						{
							if (player.getPosition().y - playerBounds.height / 2 < cloud15d.getPosition().y)
							{
								// Calculate the new player position
								float newYcl15d = cloud15d.getPosition().y - playerBounds.height / 2;

								// Adjust player position and velocity
								player.setPosition(player.getPosition().x, newYcl15d);
								playerVelocityY = 0.f;
								jumpCount = 0;
							}
						}
					}

					//SMALL CLOUDS
					if (player.getGlobalBounds().intersects(sCloud1d.getGlobalBounds()))
					{
						// Check for downward collision (player is moving downwards)
						if (playerVelocityY > 0)
						{
							if (player.getPosition().y - playerBounds.height / 2 < sCloud1d.getPosition().y)
							{
								// Calculate the new player position
								float newYscl1d = sCloud1d.getPosition().y - playerBounds.height / 2;

								// Adjust player position and velocity
								player.setPosition(player.getPosition().x, newYscl1d);
								playerVelocityY = 0.f;
								jumpCount = 0;
							}
						}
					}

					if (player.getGlobalBounds().intersects(sCloud2d.getGlobalBounds()))
					{
						// Check for downward collision (player is moving downwards)
						if (playerVelocityY > 0)
						{
							if (player.getPosition().y - playerBounds.height / 2 < sCloud2d.getPosition().y)
							{
								// Calculate the new player position
								float newYscl2d = sCloud2d.getPosition().y - playerBounds.height / 2;

								// Adjust player position and velocity
								player.setPosition(player.getPosition().x, newYscl2d);
								playerVelocityY = 0.f;
								jumpCount = 0;
							}
						}
					}

					if (player.getGlobalBounds().intersects(sCloud3d.getGlobalBounds()))
					{
						// Check for downward collision (player is moving downwards)
						if (playerVelocityY > 0)
						{
							if (player.getPosition().y - playerBounds.height / 2 < sCloud3d.getPosition().y)
							{
								// Calculate the new player position
								float newYscl3d = sCloud3d.getPosition().y - playerBounds.height / 2;

								// Adjust player position and velocity
								player.setPosition(player.getPosition().x, newYscl3d);
								playerVelocityY = 0.f;
								jumpCount = 0;
							}
						}
					}

					if (player.getGlobalBounds().intersects(sCloud4d.getGlobalBounds()))
					{
						// Check for downward collision (player is moving downwards)
						if (playerVelocityY > 0)
						{
							if (player.getPosition().y - playerBounds.height / 2 < sCloud4d.getPosition().y)
							{
								// Calculate the new player position
								float newYscl4d = sCloud4d.getPosition().y - playerBounds.height / 2;

								// Adjust player position and velocity
								player.setPosition(player.getPosition().x, newYscl4d);
								playerVelocityY = 0.f;
								jumpCount = 0;
							}
						}
					}

					if (player.getGlobalBounds().intersects(sCloud5d.getGlobalBounds()))
					{
						// Check for downward collision (player is moving downwards)
						if (playerVelocityY > 0)
						{
							if (player.getPosition().y - playerBounds.height / 2 < sCloud5d.getPosition().y)
							{
								// Calculate the new player position
								float newYscl5d = sCloud5d.getPosition().y - playerBounds.height / 2;

								// Adjust player position and velocity
								player.setPosition(player.getPosition().x, newYscl5d);
								playerVelocityY = 0.f;
								jumpCount = 0;
							}
						}
					}

					if (player.getGlobalBounds().intersects(sCloud6d.getGlobalBounds()))
					{
						// Check for downward collision (player is moving downwards)
						if (playerVelocityY > 0)
						{
							if (player.getPosition().y - playerBounds.height / 2 < sCloud6d.getPosition().y)
							{
								// Calculate the new player position
								float newYscl6d = sCloud6d.getPosition().y - playerBounds.height / 2;

								// Adjust player position and velocity
								player.setPosition(player.getPosition().x, newYscl6d);
								playerVelocityY = 0.f;
								jumpCount = 0;
							}
						}
					}

					if (player.getGlobalBounds().intersects(sCloud7d.getGlobalBounds()))
					{
						// Check for downward collision (player is moving downwards)
						if (playerVelocityY > 0)
						{
							if (player.getPosition().y - playerBounds.height / 2 < sCloud7d.getPosition().y)
							{
								// Calculate the new player position
								float newYscl7d = sCloud7d.getPosition().y - playerBounds.height / 2;

								// Adjust player position and velocity
								player.setPosition(player.getPosition().x, newYscl7d);
								playerVelocityY = 0.f;
								jumpCount = 0;
							}
						}
					}
					
					if (player.getGlobalBounds().intersects(sCloud8d.getGlobalBounds()))
					{
						// Check for downward collision (player is moving downwards)
						if (playerVelocityY > 0)
						{
							if (player.getPosition().y - playerBounds.height / 2 < sCloud8d.getPosition().y)
							{
								// Calculate the new player position
								float newYscl8d = sCloud8d.getPosition().y - playerBounds.height / 2;

								// Adjust player position and velocity
								player.setPosition(player.getPosition().x, newYscl8d);
								playerVelocityY = 0.f;
								jumpCount = 0;
							}
						}
					}

					if (player.getGlobalBounds().intersects(sCloud9d.getGlobalBounds()))
					{
						// Check for downward collision (player is moving downwards)
						if (playerVelocityY > 0)
						{
							if (player.getPosition().y - playerBounds.height / 2 < sCloud9d.getPosition().y)
							{
								// Calculate the new player position
								float newYscl9d = sCloud9d.getPosition().y - playerBounds.height / 2;

								// Adjust player position and velocity
								player.setPosition(player.getPosition().x, newYscl9d);
								playerVelocityY = 0.f;
								jumpCount = 0;
							}
						}
					}


					if (player.getGlobalBounds().intersects(sCloud10d.getGlobalBounds()))
					{
						// Check for downward collision (player is moving downwards)
						if (playerVelocityY > 0)
						{
							if (player.getPosition().y - playerBounds.height / 2 < sCloud10d.getPosition().y)
							{
								// Calculate the new player position
								float newYscl10d = sCloud10d.getPosition().y - playerBounds.height / 2;

								// Adjust player position and velocity
								player.setPosition(player.getPosition().x, newYscl10d);
								playerVelocityY = 0.f;
								jumpCount = 0;
							}
						}
					}

					if (player.getGlobalBounds().intersects(cloud16d.getGlobalBounds()))
					{
						// Check for downward collision (player is moving downwards)
						if (playerVelocityY > 0)
						{
							if (player.getPosition().y - playerBounds.height / 2 < cloud16d.getPosition().y)
							{
								// Calculate the new player position
								float newYscl16d = cloud16d.getPosition().y - playerBounds.height / 2;

								// Adjust player position and velocity
								player.setPosition(player.getPosition().x, newYscl16d);
								playerVelocityY = 0.f;
								jumpCount = 0;
							}
						}
					}



					if (player.getGlobalBounds().intersects(chisTrio2.getGlobalBounds()))
					{
						// Check for downward collision (player is moving downwards)
						if (playerVelocityY > 0)
						{
							if (player.getPosition().y - playerBounds.height / 2 < chisTrio2.getPosition().y)
							{
								// Calculate the new player position
								float newYct2 = chisTrio2.getPosition().y - playerBounds.height / 2;

								// Adjust player position and velocity
								player.setPosition(player.getPosition().x, newYct2);
								playerVelocityY = 0.f;
								jumpCount = 0;
							}
						}
					}
					
					if (player.getGlobalBounds().intersects(chisTrio3.getGlobalBounds()))
					{
						// Check for downward collision (player is moving downwards)
						if (playerVelocityY > 0)
						{
							if (player.getPosition().y - playerBounds.height / 2 < chisTrio3.getPosition().y)
							{
								// Calculate the new player position
								float newYct3 = chisTrio3.getPosition().y - playerBounds.height / 2;

								// Adjust player position and velocity
								player.setPosition(player.getPosition().x, newYct3);
								playerVelocityY = 0.f;
								jumpCount = 0;
							}
						}
					}

					

					if (player.getGlobalBounds().intersects(chisTrio2.getGlobalBounds()))
					{
						if (playerVelocityY > 0 )
						{
							if (player.getPosition().y < chisTrio2.getPosition().y)
							{
								player.setPosition(player.getPosition().x, chisTrio2.getPosition().y - player.getGlobalBounds().height / 2);
								playerVelocityY = 10.f;
								jumpCount = 0;
							}
						}
					}


					if (player.getGlobalBounds().intersects(sf::FloatRect(chisTrio2Bounds.left, chisTrio2Bounds.top + chisTrio2Bounds.height - 1, chisTrio2Bounds.width, 1.f))) {
						// Player intersects with the bottom side of the platform

						// Check if the player is moving upwards (jumping)
						if (playerVelocityY < 0) {
							// Adjust player's position only if moving upwards
							player.setPosition(player.getPosition().x, chisTrio2Bounds.top + chisTrio2Bounds.height);
							playerVelocityY = 0.f; // Set vertical velocity to zero to stop upward movement
							isJumping = false; // Reset jump state
							jumpCount = 0; // Reset jump count
						}
					}

					if (player.getGlobalBounds().intersects(chisTrio3.getGlobalBounds()))
					{
						if (playerVelocityY > 0)
						{
							if (player.getPosition().y < chisTrio3.getPosition().y)
							{
								player.setPosition(player.getPosition().x, chisTrio3.getPosition().y - player.getGlobalBounds().height / 2);
								playerVelocityY = 10.f;
								jumpCount = 0;
							}
						}
					}


					if (player.getGlobalBounds().intersects(sf::FloatRect(chisTrio3Bounds.left, chisTrio3Bounds.top + chisTrio3Bounds.height - 1, chisTrio3Bounds.width, 1.f))) {
						// Player intersects with the bottom side of the platform

						// Check if the player is moving upwards (jumping)
						if (playerVelocityY < 0) {
							// Adjust player's position only if moving upwards
							player.setPosition(player.getPosition().x, chisTrio3Bounds.top + chisTrio3Bounds.height);
							playerVelocityY = 0.f; // Set vertical velocity to zero to stop upward movement
							isJumping = false; // Reset jump state
							jumpCount = 0; // Reset jump count
						}
					}

					//-------------------------------------------------------------------------------------------
					//ENEMY COLLISIONS
					if (player.getGlobalBounds().intersects(bEnemyd1.getGlobalBounds()) && damageCooldown.getElapsedTime() > coolDownDuration)
					{
						float playerFeet = player.getPosition().y + player.getGlobalBounds().height / 2.0f;
						float bEnemyd1Top = bEnemyd1.getPosition().y - bEnemyd1.getGlobalBounds().height / 2.0f;

						if (playerFeet < bEnemyd1Top)
						{
							// Player jumps on the enemy, so enemy is squished
							playerVelocityY = -12.f;
							stompSound.play();
							isSquishedb1d = true;
							squishTimerb1d.restart();

						}
						else
						{
							// Player touches the enemy without jumping, so player gets damaged
							spikeStabSound.play();
							currentHealth--;
							float knockbackDistance = 100.0f; // Adjust as needed
							if (player.getPosition().x < bEnemyd1.getPosition().x)
							{
								player.setPosition(player.getPosition().x - knockbackDistance, player.getPosition().y);
							}
							else
							{
								player.setPosition(player.getPosition().x + knockbackDistance, player.getPosition().y);
							}
							blinkingTimer.restart();
							damageCooldown.restart();
						}
					}


					if (isSquishedb1d)
					{
						sf::Time elapsed = squishTimerb1d.getElapsedTime();
						if (elapsed < squishDurationb1d)
						{
							// Show squished appearance on the ground
							bEnemyd1.setScale(3.f, 0.5f); // Adjust the y-scale for the squish effect
							bEnemyd1.setPosition(bEnemyd1.getPosition().x, cloud7d.getPosition().y);
							bed1enemySpeed = 0.f;
						}
						else
						{
							// Remove the enemy after the squish duration
							isSquishedb1d = false;
							bEnemyd1.setPosition(-1000.0f, -1000.0f);
						}
					}

					//-----------------------------------------------------------------------

					if (player.getGlobalBounds().intersects(bEnemyd2.getGlobalBounds()) && damageCooldown.getElapsedTime() > coolDownDuration)
					{
						float playerFeet = player.getPosition().y + player.getGlobalBounds().height / 2.0f;
						float bEnemyd2Top = bEnemyd2.getPosition().y - bEnemyd2.getGlobalBounds().height / 2.0f;

						if (playerFeet < bEnemyd2Top)
						{
							// Player jumps on the enemy, so enemy is squished
							playerVelocityY = -12.f;
							stompSound.play();
							isSquishedb2d = true;
							squishTimerb2d.restart();

						}
						else
						{
							// Player touches the enemy without jumping, so player gets damaged
							spikeStabSound.play();
							currentHealth--;
							float knockbackDistance = 100.0f; // Adjust as needed
							if (player.getPosition().x < bEnemyd2.getPosition().x)
							{
								player.setPosition(player.getPosition().x - knockbackDistance, player.getPosition().y);
							}
							else
							{
								player.setPosition(player.getPosition().x + knockbackDistance, player.getPosition().y);
							}
							blinkingTimer.restart();
							damageCooldown.restart();
						}
					}


					if (isSquishedb2d)
					{
						sf::Time elapsed = squishTimerb2d.getElapsedTime();
						if (elapsed < squishDurationb2d)
						{
							// Show squished appearance on the ground
							bEnemyd2.setScale(3.f, 0.5f); // Adjust the y-scale for the squish effect
							bEnemyd2.setPosition(bEnemyd2.getPosition().x, cloud8d.getPosition().y);
							bed2enemySpeed = 0.f;
						}
						else
						{
							// Remove the enemy after the squish duration
							isSquishedb2d = false;
							bEnemyd2.setPosition(-1000.0f, -1000.0f);
						}
					}

					//--------------------------------------------------------------------------
					if (player.getGlobalBounds().intersects(bEnemyd3.getGlobalBounds()) && damageCooldown.getElapsedTime() > coolDownDuration)
					{
						float playerFeet = player.getPosition().y + player.getGlobalBounds().height / 2.0f;
						float bEnemyd3Top = bEnemyd3.getPosition().y - bEnemyd3.getGlobalBounds().height / 2.0f;

						if (playerFeet < bEnemyd3Top)
						{
							// Player jumps on the enemy, so enemy is squished
							playerVelocityY = -12.f;
							stompSound.play();
							isSquishedb3d = true;
							squishTimerb3d.restart();

						}
						else
						{
							// Player touches the enemy without jumping, so player gets damaged
							spikeStabSound.play();
							currentHealth--;
							float knockbackDistance = 100.0f; // Adjust as needed
							if (player.getPosition().x < bEnemyd3.getPosition().x)
							{
								player.setPosition(player.getPosition().x - knockbackDistance, player.getPosition().y);
							}
							else
							{
								player.setPosition(player.getPosition().x + knockbackDistance, player.getPosition().y);
							}
							blinkingTimer.restart();
							damageCooldown.restart();
						}
					}


					if (isSquishedb3d)
					{
						sf::Time elapsed = squishTimerb3d.getElapsedTime();
						if (elapsed < squishDurationb3d)
						{
							// Show squished appearance on the ground
							bEnemyd3.setScale(3.f, 0.5f); // Adjust the y-scale for the squish effect
							bEnemyd3.setPosition(bEnemyd3.getPosition().x, cloud9d.getPosition().y);
							bed3enemySpeed = 0.f;
						}
						else
						{
							// Remove the enemy after the squish duration
							isSquishedb3d = false;
							bEnemyd3.setPosition(-1000.0f, -1000.0f);
						}
					}
					//---------------------------------------------------------------------------------------------------------------

					if (player.getGlobalBounds().intersects(bEnemyd4.getGlobalBounds()) && damageCooldown.getElapsedTime() > coolDownDuration)
					{
						float playerFeet = player.getPosition().y + player.getGlobalBounds().height / 2.0f;
						float bEnemyd4Top = bEnemyd4.getPosition().y - bEnemyd4.getGlobalBounds().height / 2.0f;

						if (playerFeet < bEnemyd4Top)
						{
							// Player jumps on the enemy, so enemy is squished
							playerVelocityY = -12.f;
							stompSound.play();
							isSquishedb4d = true;
							squishTimerb4d.restart();

						}
						else
						{
							// Player touches the enemy without jumping, so player gets damaged
							spikeStabSound.play();
							currentHealth--;
							float knockbackDistance = 100.0f; // Adjust as needed
							if (player.getPosition().x < bEnemyd4.getPosition().x)
							{
								player.setPosition(player.getPosition().x - knockbackDistance, player.getPosition().y);
							}
							else
							{
								player.setPosition(player.getPosition().x + knockbackDistance, player.getPosition().y);
							}
							blinkingTimer.restart();
							damageCooldown.restart();
						}
					}


					if (isSquishedb4d)
					{
						sf::Time elapsed = squishTimerb4d.getElapsedTime();
						if (elapsed < squishDurationb4d)
						{
							// Show squished appearance on the ground
							bEnemyd4.setScale(3.f, 0.5f); // Adjust the y-scale for the squish effect
							bEnemyd4.setPosition(bEnemyd4.getPosition().x, cloud10d.getPosition().y);
							bed4enemySpeed = 0.f;
						}
						else
						{
							// Remove the enemy after the squish duration
							isSquishedb4d = false;
							bEnemyd4.setPosition(-1000.0f, -1000.0f);
						}
					}

					//------------------------------------------------------------------------------------------------
					if (player.getGlobalBounds().intersects(bEnemyd5.getGlobalBounds()) && damageCooldown.getElapsedTime() > coolDownDuration)
					{
						float playerFeet = player.getPosition().y + player.getGlobalBounds().height / 2.0f;
						float bEnemyd5Top = bEnemyd5.getPosition().y - bEnemyd5.getGlobalBounds().height / 2.0f;

						if (playerFeet < bEnemyd5Top)
						{
							// Player jumps on the enemy, so enemy is squished
							playerVelocityY = -12.f;
							stompSound.play();
							isSquishedb5d = true;
							squishTimerb5d.restart();

						}
						else
						{
							// Player touches the enemy without jumping, so player gets damaged
							spikeStabSound.play();
							currentHealth--;
							float knockbackDistance = 100.0f; // Adjust as needed
							if (player.getPosition().x < bEnemyd5.getPosition().x)
							{
								player.setPosition(player.getPosition().x - knockbackDistance, player.getPosition().y);
							}
							else
							{
								player.setPosition(player.getPosition().x + knockbackDistance, player.getPosition().y);
							}
							blinkingTimer.restart();
							damageCooldown.restart();
						}
					}


					if (isSquishedb5d)
					{
						sf::Time elapsed = squishTimerb5d.getElapsedTime();
						if (elapsed < squishDurationb5d)
						{
							// Show squished appearance on the ground
							bEnemyd5.setScale(3.f, 0.5f); // Adjust the y-scale for the squish effect
							bEnemyd5.setPosition(bEnemyd5.getPosition().x, cloud11d.getPosition().y);
							bed5enemySpeed = 0.f;
						}
						else
						{
							// Remove the enemy after the squish duration
							isSquishedb5d = false;
							bEnemyd5.setPosition(-1000.0f, -1000.0f);
						}
					}
					//----------------------------------------------------------------------------
					if (player.getGlobalBounds().intersects(bEnemyd6.getGlobalBounds()) && damageCooldown.getElapsedTime() > coolDownDuration)
					{
						float playerFeet = player.getPosition().y + player.getGlobalBounds().height / 2.0f;
						float bEnemyd6Top = bEnemyd6.getPosition().y - bEnemyd6.getGlobalBounds().height / 2.0f;

						if (playerFeet < bEnemyd6Top)
						{
							// Player jumps on the enemy, so enemy is squished
							playerVelocityY = -12.f;
							stompSound.play();
							isSquishedb6d = true;
							squishTimerb6d.restart();

						}
						else
						{
							// Player touches the enemy without jumping, so player gets damaged
							spikeStabSound.play();
							currentHealth--;
							float knockbackDistance = 100.0f; // Adjust as needed
							if (player.getPosition().x < bEnemyd6.getPosition().x)
							{
								player.setPosition(player.getPosition().x - knockbackDistance, player.getPosition().y);
							}
							else
							{
								player.setPosition(player.getPosition().x + knockbackDistance, player.getPosition().y);
							}
							blinkingTimer.restart();
							damageCooldown.restart();
						}
					}


					if (isSquishedb6d)
					{
						sf::Time elapsed = squishTimerb6d.getElapsedTime();
						if (elapsed < squishDurationb6d)
						{
							// Show squished appearance on the ground
							bEnemyd6.setScale(3.f, 0.5f); // Adjust the y-scale for the squish effect
							bEnemyd6.setPosition(bEnemyd6.getPosition().x, cloud12d.getPosition().y);
							bed6enemySpeed = 0.f;
						}
						else
						{
							// Remove the enemy after the squish duration
							isSquishedb6d = false;
							bEnemyd6.setPosition(-1000.0f, -1000.0f);
						}
					}
					//-------------------------------------------------------------------------------------
					if (player.getGlobalBounds().intersects(bEnemyd7.getGlobalBounds()) && damageCooldown.getElapsedTime() > coolDownDuration)
					{
						float playerFeet = player.getPosition().y + player.getGlobalBounds().height / 2.0f;
						float bEnemyd7Top = bEnemyd7.getPosition().y - bEnemyd7.getGlobalBounds().height / 2.0f;

						if (playerFeet < bEnemyd7Top)
						{
							// Player jumps on the enemy, so enemy is squished
							playerVelocityY = -12.f;
							stompSound.play();
							isSquishedb7d = true;
							squishTimerb7d.restart();

						}
						else
						{
							// Player touches the enemy without jumping, so player gets damaged
							spikeStabSound.play();
							currentHealth--;
							float knockbackDistance = 100.0f; // Adjust as needed
							if (player.getPosition().x < bEnemyd7.getPosition().x)
							{
								player.setPosition(player.getPosition().x - knockbackDistance, player.getPosition().y);
							}
							else
							{
								player.setPosition(player.getPosition().x + knockbackDistance, player.getPosition().y);
							}
							blinkingTimer.restart();
							damageCooldown.restart();
						}
					}


					if (isSquishedb7d)
					{
						sf::Time elapsed = squishTimerb7d.getElapsedTime();
						if (elapsed < squishDurationb7d)
						{
							// Show squished appearance on the ground
							bEnemyd7.setScale(3.f, 0.5f); // Adjust the y-scale for the squish effect
							bEnemyd7.setPosition(bEnemyd7.getPosition().x, cloud13d.getPosition().y);
							bed7enemySpeed = 0.f;
						}
						else
						{
							// Remove the enemy after the squish duration
							isSquishedb7d = false;
							bEnemyd7.setPosition(-1000.0f, -1000.0f);
						}
					}

					if (player.getGlobalBounds().intersects(fEnemyd1.getGlobalBounds()) && damageCooldown.getElapsedTime() > coolDownDuration)
					{
						float playerFeet = player.getPosition().y + player.getGlobalBounds().height / 2.0f;
						float fEnemyd1Top = fEnemyd1.getPosition().y - fEnemyd1.getGlobalBounds().height / 2.0f;

						if (playerFeet < fEnemyd1Top)
						{
							// Player jumps on the enemy, so enemy is squished
							playerVelocityY = -12.f;
							fEnemyd1.move(0, -10);
							stompSound.play();
							isSquishedf1d = true;
							squishTimerf1d.restart();

						}
						else
						{
							// Player touches the enemy without jumping, so player gets damaged
							spikeStabSound.play();
							currentHealth--;
							float knockbackDistance = 100.0f; // Adjust as needed
							if (player.getPosition().x < fEnemyd1.getPosition().x)
							{
								player.setPosition(player.getPosition().x - knockbackDistance, player.getPosition().y);
							}
							else
							{
								player.setPosition(player.getPosition().x + knockbackDistance, player.getPosition().y);
							}
							blinkingTimer.restart();
							damageCooldown.restart();
						}
					}


					if (isSquishedf1d)
					{
						sf::Time elapsed = squishTimerf1d.getElapsedTime();
						if (elapsed < squishDurationf1d)
						{
							// Show squished appearance on the ground
							/*fEnemyd1.setScale(3.f, 0.5f);*/ // Adjust the y-scale for the squish effect
							fEnemyd1.move(0, 20);
							fed1enemySpeed = 0.f;
						}
						else
						{
							// Remove the enemy after the squish duration
							isSquishedf1d = false;
							fEnemyd1.setPosition(-1000.0f, -1000.0f);
						}
					}

					//-----------------------------------------------------------------------------------------------------
					if (player.getGlobalBounds().intersects(fEnemyd2.getGlobalBounds()) && damageCooldown.getElapsedTime() > coolDownDuration)
					{
						float playerFeet = player.getPosition().y + player.getGlobalBounds().height / 2.0f;
						float fEnemyd2Top = fEnemyd2.getPosition().y - fEnemyd2.getGlobalBounds().height / 2.0f;

						if (playerFeet < fEnemyd2Top)
						{
							// Player jumps on the enemy, so enemy is squished
							playerVelocityY = -12.f;
							stompSound.play();
							isSquishedf2d = true;
							squishTimerf2d.restart();

						}
						else
						{
							// Player touches the enemy without jumping, so player gets damaged
							spikeStabSound.play();
							currentHealth--;
							float knockbackDistance = 100.0f; // Adjust as needed
							if (player.getPosition().x < fEnemyd2.getPosition().x)
							{
								player.setPosition(player.getPosition().x - knockbackDistance, player.getPosition().y);
							}
							else
							{
								player.setPosition(player.getPosition().x + knockbackDistance, player.getPosition().y);
							}
							blinkingTimer.restart();
							damageCooldown.restart();
						}
					}


					if (isSquishedf2d)
					{
						sf::Time elapsed = squishTimerf2d.getElapsedTime();
						if (elapsed < squishDurationf2d)
						{
							// Show squished appearance on the ground
							//fEnemyd2.setScale(3.f, 0.5f); // Adjust the y-scale for the squish effect
							fEnemyd2.move(0, 20);
							fed2enemySpeed = 0.f;
						}
						else
						{
							// Remove the enemy after the squish duration
							isSquishedf2d = false;
							fEnemyd2.setPosition(-1000.0f, -1000.0f);
						}
					}

					if (player.getGlobalBounds().intersects(rEnemyd1.getGlobalBounds()) && damageCooldown.getElapsedTime() > coolDownDuration)
					{
						playerVelocityY = -12.f;
						currentHealth--;

						spikeStabSound.play();

						blinkingTimer.restart();
						damageCooldown.restart();
					}

					if (player.getGlobalBounds().intersects(rEnemyd2.getGlobalBounds()) && damageCooldown.getElapsedTime() > coolDownDuration)
					{
						playerVelocityY = -12.f;
						currentHealth--;

						spikeStabSound.play();

						blinkingTimer.restart();
						damageCooldown.restart();
					}

					if (player.getGlobalBounds().intersects(rEnemyd3.getGlobalBounds()) && damageCooldown.getElapsedTime() > coolDownDuration)
					{
						playerVelocityY = -12.f;
						currentHealth--;

						spikeStabSound.play();

						blinkingTimer.restart();
						damageCooldown.restart();
					}

					if (player.getGlobalBounds().intersects(rEnemyd4.getGlobalBounds()) && damageCooldown.getElapsedTime() > coolDownDuration)
					{
						playerVelocityY = -12.f;
						currentHealth--;

						spikeStabSound.play();

						blinkingTimer.restart();
						damageCooldown.restart();
					}
					//COIN ANIMATION
					//COIN 1
					if (coin1DFrameCount == coin1DSwitchFrame) {
						coin1DFrameCount = 0;
						if (coin1d.getTextureRect().left == 0)
							coin1d.setTextureRect(sf::IntRect(20, 0, 8, 12));
						else
							coin1d.setTextureRect(sf::IntRect(0, 0, 12, 12));
					}
					else {
						coin1DFrameCount++;
					}

					//COIN 2
					if (coin2DFrameCount == coin2DSwitchFrame) {
						coin2DFrameCount = 0;
						if (coin2d.getTextureRect().left == 0)
							coin2d.setTextureRect(sf::IntRect(20, 0, 8, 12));
						else
							coin2d.setTextureRect(sf::IntRect(0, 0, 12, 12));
					}
					else {
						coin2DFrameCount++;
					}

					//COIN 3
					if (coin3DFrameCount == coin3DSwitchFrame) {
						coin3DFrameCount = 0;
						if (coin3d.getTextureRect().left == 0)
							coin3d.setTextureRect(sf::IntRect(20, 0, 8, 12));
						else
							coin3d.setTextureRect(sf::IntRect(0, 0, 12, 12));
					}
					else {
						coin3DFrameCount++;
					}

					if (player.getGlobalBounds().intersects(coin1d.getGlobalBounds()))
					{
						coins += 1;

						coinSound.play();

						coin1d.setPosition(-1000, -1000);
					}

					if (player.getGlobalBounds().intersects(coin2d.getGlobalBounds()))
					{
						coins += 1;

						coinSound.play();

						coin2d.setPosition(-1000, -1000);
					}

					if (player.getGlobalBounds().intersects(coin3d.getGlobalBounds()))
					{
						coins += 1;

						coinSound.play();

						coin3d.setPosition(-1000, -1000);
					}

					if (player.getGlobalBounds().intersects(coinDoord.getGlobalBounds()))
					{
						if (coins == 3)
						{
							crates.setPosition(-1000, -1000);
							wood.play();
							player.setPosition(chisTrio2.getPosition().x + 100, chisTrio2.getPosition().y - 50);
						}
					}

					if (player.getGlobalBounds().intersects(keydi.getGlobalBounds()))
					{
						keySound.play();
						hasKey = true;
						keydi.setPosition(-1000, -1000);
					}

					if (player.getGlobalBounds().intersects(keyDoord.getGlobalBounds()))
					{
						if (hasKey == true)
						{
							desert.stop();
							doorSound.play();
							victorySound.play();
							hasKeyLevel3 = true;
							level2Friendbool = true;
							
							std::this_thread::sleep_for(std::chrono::seconds(2));
							currentLevel = 7;
							/*player.setPosition(spring3h.getPosition().x - 100, snowP1.getPosition().y );*/
							player.setPosition(20, 1000);
							crates.setPosition(chisTrio3.getPosition().x, chisTrio3.getPosition().y - 200);
							coin1d.setPosition(669, 713);
							coin2d.setPosition(1133, 711);
							coin3d.setPosition(1638, 247);

							keydi.setPosition(1613, 52);
							endingMusic.play();
						}
					}

					if (currentHealth == 0)
					{
						currentLevel = 1;

						player.setPosition(spring2h.getPosition().x - 100, snowP1.getPosition().y + 50);

						coin1d.setPosition(669, 713);
						coin2d.setPosition(1133, 711);
						coin3d.setPosition(1638, 247);

						keydi.setPosition(1613, 52);

						desert.stop();

						crates.setPosition(chisTrio3.getPosition().x, chisTrio3.getPosition().y - 200);
					}











					//-------------------------------------------------------------------------------------------------------
					if (playerBounds.intersects(sf::FloatRect(crates.getGlobalBounds().left, crates.getGlobalBounds().top, 0.5f, crates.getGlobalBounds().height)))
					{
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && player.getPosition().x < crates.getGlobalBounds().left && !hasCollidedWithLeftSide)
						{
							player.setPosition(crates.getGlobalBounds().left - playerBounds.width / 2.f, player.getPosition().y);
							hasCollidedWithLeftSide = true;
						}
						hasCollidedWithRightSide = false;
					}
					else if (playerBounds.intersects(sf::FloatRect(crates.getGlobalBounds().left + crates.getGlobalBounds().width, crates.getGlobalBounds().top, 1.f, crates.getGlobalBounds().height)))
					{
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && player.getPosition().x > crates.getGlobalBounds().left + crates.getGlobalBounds().width && !hasCollidedWithRightSide)
						{
							player.setPosition(crates.getGlobalBounds().left + crates.getGlobalBounds().width + playerBounds.width / 2.f, player.getPosition().y);
							hasCollidedWithRightSide = true;
						}
						hasCollidedWithLeftSide = false;
					}
					else {
						hasCollidedWithLeftSide = false;
						hasCollidedWithRightSide = false;
					}
				

					updateHealth(currentHealth);



					window.clear();

					window.draw(dBg);
		
					window.setView(view);

					
					window.draw(chunkd);
					window.draw(chunkd2);
					window.draw(springd1);
					window.draw(springd2);
					window.draw(springd3);
					window.draw(springd4);
					window.draw(springd5);
					window.draw(springd6);
					window.draw(springd7);
					window.draw(springd8);
					window.draw(springd9);
					window.draw(springd10);
					window.draw(springd11);
					window.draw(springd12);
					window.draw(springd13);
					window.draw(spiked1);
					window.draw(spiked2);
					window.draw(spiked3);
					window.draw(spiked4);
					window.draw(spiked5);
					window.draw(spiked6);
					window.draw(spiked7);
					window.draw(spiked8);
					window.draw(spiked9);
					window.draw(spiked10);
					window.draw(spiked11);
					window.draw(p3d);
					window.draw(pd1);
					window.draw(pd2);
					window.draw(pd3);
					window.draw(pd4);
					window.draw(pd5);
					window.draw(pd6);
					window.draw(pd7);
					window.draw(pd8);
					window.draw(pd9);
					window.draw(pd10);
					
					
					window.draw(coinDoord);
					window.draw(keyDoord);

					window.draw(coin1d);
					window.draw(coin2d);
					window.draw(coin3d);
					window.draw(coinInDoor);


					window.draw(cloud1d);
					window.draw(cloud2d);
					window.draw(cloud3d);
					window.draw(cloud4d);
					window.draw(cloud5d);
					window.draw(cloud6d);
					window.draw(cloud7d);
					window.draw(cloud8d);
					window.draw(cloud9d);
					window.draw(cloud10d);
					window.draw(cloud11d);
					window.draw(cloud12d);
					window.draw(cloud13d);
					window.draw(cloud14d);
					window.draw(cloud15d);
					window.draw(cloud16d);

					window.draw(sCloud1d);
					window.draw(sCloud2d);
					window.draw(sCloud3d);
					window.draw(sCloud4d);
					window.draw(sCloud5d);
					window.draw(sCloud6d);
					window.draw(sCloud7d);
					window.draw(sCloud8d);
					window.draw(sCloud9d);
					window.draw(sCloud10d);

					window.draw(chisCut);
					window.draw(chisTrio1);
					window.draw(chisTrio2);
					window.draw(chisTrio3);
						window.draw(crates);

					window.draw(keydi);
					window.draw(keyd);

					window.draw(bEnemyd1);
					window.draw(bEnemyd2);
					window.draw(bEnemyd3);
					window.draw(bEnemyd4);
					window.draw(bEnemyd5);
					window.draw(bEnemyd6);
					window.draw(bEnemyd7);

					window.draw(rEnemyd1);
					window.draw(rEnemyd2);
					window.draw(rEnemyd3);
					window.draw(rEnemyd4);

					window.draw(fEnemyd1);
					window.draw(fEnemyd2);


					if (blinkingTimer.getElapsedTime() < blinkingTimerDuration)
					{
						if (static_cast<int>(blinkingTimer.getElapsedTime().asSeconds() * 5) % 2 == 0)
						{
							window.draw(player);
						}
					}
					else
					{
						window.draw(player);
					}

					window.setView(guiView);
					drawHealthBar(window, filledHeartTexture, emptyHeartTexture);
					window.display();
					break;
			case 4:

					while (window.pollEvent(pollEvent))
					{
						if (pollEvent.type == sf::Event::Closed)
						{
							window.close();
						}
						else if (pollEvent.type == sf::Event::KeyPressed && pollEvent.key.code == sf::Keyboard::Escape)
						{
							window.close();
						}
					}

					//Player Movement
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
					{
						playerVelocityX = -5.f;
						isMoving = true;
						movingLeft = true;
						movingRight = false;
					}
					else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
					{
						playerVelocityX = 5.f;
						isMoving = true;
						movingLeft = false;
						movingRight = true;
					}
					else
					{
						playerVelocityX = 0.f;
						isMoving = false;
						movingLeft = false;
						movingRight = false;
					}

					//PLAYER JUMP
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
					{
						if (!isJumping && jumpCount < maxJump)
						{
							isJumping = true;
							playerVelocityY = jumpVelocity;
							jumpCount++;
							frameCount = 0;

							jumpSound.play();
						}
					}
					else
					{
						isJumping = false;
					}

					playerVelocityY += gravity;
					player.move(playerVelocityX, playerVelocityY);

					if (player.getPosition().x < 0) {
						// Correct position to be exactly at the left boundary
						player.setPosition(0, player.getPosition().y);

						// If the player is moving left, stop horizontal movement
						if (playerVelocityX < 0) {
							playerVelocityX = 0.f;
						}
					}

					if (player.getPosition().x > 1920) {
						// Correct position to be exactly at the left boundary
						player.setPosition(1920, player.getPosition().y);

						// If the player is moving left, stop horizontal movement
						if (playerVelocityX > 1920) {
							playerVelocityX = 0.f;
						}
					}

					if (player.getPosition().y < 0) {
						// Correct position to be exactly at the left boundary
						player.setPosition(player.getPosition().x, 0);

						// If the player is moving left, stop horizontal movement
						if (playerVelocityY < 0) {
							playerVelocityY = 0.f;
						}
					}

					//FLOOR COLLISION
					if (player.getPosition().y >= 1100)
					{
						player.setPosition(player.getPosition().x, 1100);
						playerVelocityY = 0.f;
						jumpCount = 0;
					}
					if (player.getPosition().y == 1100)
					{
						jumpCount = 0;
					}

					//-------------------------------------------------------------------------------------
					//ANIMATIONS

					//JUMPING ANIMATION
					if (isJumping)
					{
						player.setTextureRect(sf::IntRect(0, 0, 20, 24));
					}
					//LEFT MOVEMENT ANIMATION
					else if (movingLeft)
					{
						if (frameCount == switchFrame)
						{
							frameCount = 0;
							if (player.getTextureRect().left == 0)
								player.setTextureRect(sf::IntRect(24, 0, 20, 24));
							else
								player.setTextureRect(sf::IntRect(0, 0, 20, 24));
						}
						else
						{
							frameCount++;
						}
					}
					//RIGHT MOVEMENT ANIMATION
					else if (movingRight)
					{
						if (frameCount == switchFrame)
						{
							frameCount = 0;
							if (player.getTextureRect().left == 0)
							{
								player.setTextureRect(sf::IntRect(24, 0, 20, 24));
							}
							else
							{
								player.setTextureRect(sf::IntRect(0, 0, 20, 24));
							}
						}
						else
						{
							frameCount++;
						}
					}
					else
					{
						player.setTextureRect(sf::IntRect(24, 0, 20, 24));
					}

					//FLIPS THE SPRITE BASED ON DIRECTION
					if (movingLeft)
					{
						player.setScale(-2.f, 2.f);
					}
					else if (movingRight)
					{
						player.setScale(2.f, 2.f);
					}
					

					//-------------------------------------------------------------ENEMY MOVEMENT--------------------------------------------//
					jEnemyBlue1.move(jB1enemySpeed * jB1enemyDirection, 0.f);

					//ENEMY BLUE ANIMATION
					if (jEnemyBlue1.getPosition().x < jB1enemyLeftBound || jEnemyBlue1.getPosition().x > jB1enemyRightBound) {
						if (jEnemyBlue1.getPosition().x < jB1enemyLeftBound) {
							jB1enemyDirection = 1.0f;  // Move to the right
							jEnemyBlue1.setScale(-std::abs(jEnemyBlue1.getScale().x), 2.0f);
						}
						else {
							jB1enemyDirection = -1.0f;  // Move to the left

							jEnemyBlue1.setScale(std::abs(jEnemyBlue1.getScale().x), 2.0f);
						}
					}

					if (jB1FrameCount == jB1switchFrame) {
						jB1FrameCount = 0;
						if (jEnemyBlue1.getTextureRect().left == 0)
							jEnemyBlue1.setTextureRect(sf::IntRect(24, 0, 15, 14));
						else
							jEnemyBlue1.setTextureRect(sf::IntRect(0, 0, 15, 14));
					}
					else {
						jB1FrameCount++;
					}
					//----------------------
					jEnemyBlue2.move(jB2enemySpeed * jB2enemyDirection, 0.f);

					if (jEnemyBlue2.getPosition().x < jB2enemyLeftBound || jEnemyBlue2.getPosition().x > jB2enemyRightBound) {
						if (jEnemyBlue2.getPosition().x < jB2enemyLeftBound) {
							jB2enemyDirection = 1.0f;  // Move to the right
							jEnemyBlue2.setScale(-std::abs(jEnemyBlue2.getScale().x), 2.0f);
						}
						else {
							jB2enemyDirection = -1.0f;  // Move to the left

							jEnemyBlue2.setScale(std::abs(jEnemyBlue2.getScale().x), 2.0f);
						}
					}

					if (jB2FrameCount == jB2switchFrame) {
						jB2FrameCount = 0;
						if (jEnemyBlue2.getTextureRect().left == 0)
							jEnemyBlue2.setTextureRect(sf::IntRect(24, 0, 15, 14));
						else
							jEnemyBlue2.setTextureRect(sf::IntRect(0, 0, 15, 14));
					}
					else {
						jB2FrameCount++;
					}
					//----------------------
					jEnemyBlue3.move(jB3enemySpeed * jB3enemyDirection, 0.f);

					if (jEnemyBlue3.getPosition().x < jB3enemyLeftBound || jEnemyBlue3.getPosition().x > jB3enemyRightBound) {
						if (jEnemyBlue3.getPosition().x < jB3enemyLeftBound) {
							jB3enemyDirection = 1.0f;  // Move to the right
							jEnemyBlue3.setScale(-std::abs(jEnemyBlue3.getScale().x), 2.0f);
						}
						else {
							jB3enemyDirection = -1.0f;  // Move to the left

							jEnemyBlue3.setScale(std::abs(jEnemyBlue3.getScale().x), 2.0f);
						}
					}

					if (jB3FrameCount == jB3switchFrame) {
						jB3FrameCount = 0;
						if (jEnemyBlue3.getTextureRect().left == 0)
							jEnemyBlue3.setTextureRect(sf::IntRect(24, 0, 15, 14));
						else
							jEnemyBlue3.setTextureRect(sf::IntRect(0, 0, 15, 14));
					}
					else {
						jB3FrameCount++;
					}
					//----------------------
					jEnemyRed1.move(jR1enemySpeed * jR1enemyDirection, 0.f);

					if (jEnemyRed1.getPosition().x < jR1enemyLeftBound || jEnemyRed1.getPosition().x > jR1enemyRightBound) {
						if (jEnemyRed1.getPosition().x < jR1enemyLeftBound) {
							jR1enemyDirection = 1.0f;  // Move to the right
							jEnemyRed1.setScale(-std::abs(jEnemyRed1.getScale().x), 2.0f);
						}
						else {
							jR1enemyDirection = -1.0f;  // Move to the left

							jEnemyRed1.setScale(std::abs(jEnemyRed1.getScale().x), 2.0f);
						}
					}

					if (jR1FrameCount == jR1switchFrame) {
						jR1FrameCount = 0;
						if (jEnemyRed1.getTextureRect().left == 0)
							jEnemyRed1.setTextureRect(sf::IntRect(25, 0, 15, 19));
						else
							jEnemyRed1.setTextureRect(sf::IntRect(0, 0, 15, 19));
					}
					else {
						jR1FrameCount++;
					}
					//----------------------
					jEnemyRed2.move(jR2enemySpeed * jR2enemyDirection, 0.f);

					if (jEnemyRed2.getPosition().x < jR2enemyLeftBound || jEnemyRed2.getPosition().x > jR2enemyRightBound) {
						if (jEnemyRed2.getPosition().x < jR2enemyLeftBound) {
							jR2enemyDirection = 1.0f;  // Move to the right
							jEnemyRed2.setScale(-std::abs(jEnemyRed2.getScale().x), 2.0f);
						}
						else {
							jR2enemyDirection = -1.0f;  // Move to the left

							jEnemyRed2.setScale(std::abs(jEnemyRed2.getScale().x), 2.0f);
						}
					}

					if (jR2FrameCount == jR2switchFrame) {
						jR2FrameCount = 0;
						if (jEnemyRed2.getTextureRect().left == 0)
							jEnemyRed2.setTextureRect(sf::IntRect(25, 0, 15, 19));
						else
							jEnemyRed2.setTextureRect(sf::IntRect(0, 0, 15, 19));
					}
					else {
						jR2FrameCount++;
					}
					//----------------------
					jFEnemy1.move(jF1enemySpeed * jF1enemyDirection, 0.f);

					if (jFEnemy1.getPosition().x < jF1enemyLeftBound || jFEnemy1.getPosition().x > jF1enemyRightBound) {
						if (jFEnemy1.getPosition().x < jF1enemyLeftBound) {
							jF1enemyDirection = 1.0f;  // Move to the right
							jFEnemy1.setScale(-std::abs(jFEnemy1.getScale().x), 2.0f);
						}
						else {
							jF1enemyDirection = -1.0f;  // Move to the left

							jFEnemy1.setScale(std::abs(jFEnemy1.getScale().x), 2.0f);
						}
					}

					if (jF1FrameCount == jF1SwitchFrame) {
						jF1FrameCount = 0;
						if (jFEnemy1.getTextureRect().left == 0)
						{
							jFEnemy1.setTextureRect(sf::IntRect(21, 0, 24, 17));
						}
						else if (jFEnemy1.getTextureRect().left == 21)
						{
							jFEnemy1.setTextureRect(sf::IntRect(48, 0, 18, 17));
						}
						else
						{
							jFEnemy1.setTextureRect(sf::IntRect(0, 0, 18, 17));
						}
					}
					else {
						jF1FrameCount++;
					}
					//----------------------
					jFEnemy2.move(jF2enemySpeed * jF2enemyDirection, 0.f);

					if (jFEnemy2.getPosition().x < jF2enemyLeftBound || jFEnemy2.getPosition().x > jF2enemyRightBound) {
						if (jFEnemy2.getPosition().x < jF2enemyLeftBound) {
							jF2enemyDirection = 1.0f;  // Move to the right
							jFEnemy2.setScale(-std::abs(jFEnemy2.getScale().x), 2.0f);
						}
						else {
							jF2enemyDirection = -1.0f;  // Move to the left

							jFEnemy2.setScale(std::abs(jFEnemy2.getScale().x), 2.0f);
						}
					}

					if (jF2FrameCount == jF2SwitchFrame) {
						jF2FrameCount = 0;
						if (jFEnemy2.getTextureRect().left == 0)
						{
							jFEnemy2.setTextureRect(sf::IntRect(21, 0, 24, 17));
						}
						else if (jFEnemy2.getTextureRect().left == 21)
						{
							jFEnemy2.setTextureRect(sf::IntRect(48, 0, 18, 17));
						}
						else
						{
							jFEnemy2.setTextureRect(sf::IntRect(0, 0, 18, 17));
						}
					}
					else {
						jF2FrameCount++;
					}

					//------------------------------------------------COLLISION CHECKS---------------------------------------------//
					if (playerBounds.intersects(grassChunkBounds))
					{
						// Check for downward collision (player is moving downwards)
						if (playerVelocityY > 0)
						{
							if (player.getPosition().y - playerBounds.height / 2 < grassChunk.getPosition().y)
							{
								// Calculate the new player position
								float newY = grassChunk.getPosition().y - playerBounds.height / 2;

								// Adjust player position and velocity
								player.setPosition(player.getPosition().x, newY);
								playerVelocityY = 0.f;
								jumpCount = 0;
							}
						}
					}

					if (playerBounds.intersects(grassPlat1Bounds))
					{
						// Check for downward collision (player is moving downwards)
						if (playerVelocityY > 0)
						{
							if (player.getPosition().y - playerBounds.height / 2 < grassPlat1.getPosition().y)
							{
								// Calculate the new player position
								float newY = grassPlat1.getPosition().y - playerBounds.height / 2;

								// Adjust player position and velocity
								player.setPosition(player.getPosition().x, newY);
								playerVelocityY = 0.f;
								jumpCount = 0;
							}
						}
					}

					if (playerBounds.intersects(grassPlat2Bounds))
					{
						// Check for downward collision (player is moving downwards)
						if (playerVelocityY > 0)
						{
							if (player.getPosition().y - playerBounds.height / 2 < grassPlat2.getPosition().y)
							{
								// Calculate the new player position
								float newY = grassPlat2.getPosition().y - playerBounds.height / 2;

								// Adjust player position and velocity
								player.setPosition(player.getPosition().x, newY);
								playerVelocityY = 0.f;
								jumpCount = 0;
							}
						}
					}

					if (playerBounds.intersects(grassPlat3Bounds))
					{
						// Check for downward collision (player is moving downwards)
						if (playerVelocityY > 0)
						{
							if (player.getPosition().y - playerBounds.height / 2 < grassPlat3.getPosition().y)
							{
								// Calculate the new player position
								float newY = grassPlat3.getPosition().y - playerBounds.height / 2;

								// Adjust player position and velocity
								player.setPosition(player.getPosition().x, newY);
								playerVelocityY = 0.f;
								jumpCount = 0;
							}
						}
					}

					if (playerBounds.intersects(grassPlat4Bounds))
					{
						// Check for downward collision (player is moving downwards)
						if (playerVelocityY > 0)
						{
							if (player.getPosition().y - playerBounds.height / 2 < grassPlat4.getPosition().y)
							{
								// Calculate the new player position
								float newY = grassPlat4.getPosition().y - playerBounds.height / 2;

								// Adjust player position and velocity
								player.setPosition(player.getPosition().x, newY);
								playerVelocityY = 0.f;
								jumpCount = 0;
							}
						}
					}

					if (playerBounds.intersects(grassPlatCut.getGlobalBounds()))
					{
						// Check for downward collision (player is moving downwards)
						if (playerVelocityY > 0)
						{
							if (player.getPosition().y - playerBounds.height / 2 < grassPlatCut.getPosition().y)
							{
								// Calculate the new player position
								float newY = grassPlatCut.getPosition().y - playerBounds.height / 2;

								// Adjust player position and velocity
								player.setPosition(player.getPosition().x, newY);
								playerVelocityY = 0.f;
								jumpCount = 0;
							}
						}
					}

					if (playerBounds.intersects(branch1Bounds))
					{
						// Check for downward collision (player is moving downwards)
						if (playerVelocityY > 0)
						{
							if (player.getPosition().y - playerBounds.height / 2 < branch1.getPosition().y)
							{
								// Calculate the new player position
								float newY = branch1.getPosition().y - playerBounds.height / 2;

								// Adjust player position and velocity
								player.setPosition(player.getPosition().x, newY);
								playerVelocityY = 0.f;
								jumpCount = 0;
							}
						}
					}

					if (playerBounds.intersects(branch2Bounds))
					{
						// Check for downward collision (player is moving downwards)
						if (playerVelocityY > 0)
						{
							if (player.getPosition().y - playerBounds.height / 2 < branch2.getPosition().y)
							{
								// Calculate the new player position
								float newY = branch2.getPosition().y - playerBounds.height / 2;

								// Adjust player position and velocity
								player.setPosition(player.getPosition().x, newY);
								playerVelocityY = 0.f;
								jumpCount = 0;
							}
						}
					}

					if (playerBounds.intersects(branch3Bounds))
					{
						// Check for downward collision (player is moving downwards)
						if (playerVelocityY > 0)
						{
							if (player.getPosition().y - playerBounds.height / 2 < branch3.getPosition().y)
							{
								// Calculate the new player position
								float newY = branch3.getPosition().y - playerBounds.height / 2;

								// Adjust player position and velocity
								player.setPosition(player.getPosition().x, newY);
								playerVelocityY = 0.f;
								jumpCount = 0;
							}
						}
					}
					
					if (playerBounds.intersects(branch4Bounds))
					{
						// Check for downward collision (player is moving downwards)
						if (playerVelocityY > 0)
						{
							if (player.getPosition().y - playerBounds.height / 2 < branch4.getPosition().y)
							{
								// Calculate the new player position
								float newY = branch4.getPosition().y - playerBounds.height / 2;

								// Adjust player position and velocity
								player.setPosition(player.getPosition().x, newY);
								playerVelocityY = 0.f;
								jumpCount = 0;
							}
						}
					}

					if (playerBounds.intersects(jCloud1Bounds))
					{
						// Check for downward collision (player is moving downwards)
						if (playerVelocityY > 0)
						{
							if (player.getPosition().y - playerBounds.height / 2 < jCloud1.getPosition().y)
							{
								// Calculate the new player position
								float newY = jCloud1.getPosition().y - playerBounds.height / 2;

								// Adjust player position and velocity
								player.setPosition(player.getPosition().x, newY);
								playerVelocityY = 0.f;
								jumpCount = 0;
							}
						}
					}

					if (playerBounds.intersects(jCloud2Bounds))
					{
						// Check for downward collision (player is moving downwards)
						if (playerVelocityY > 0)
						{
							if (player.getPosition().y - playerBounds.height / 2 < jCloud2.getPosition().y)
							{
								// Calculate the new player position
								float newY = jCloud2.getPosition().y - playerBounds.height / 2;

								// Adjust player position and velocity
								player.setPosition(player.getPosition().x, newY);
								playerVelocityY = 0.f;
								jumpCount = 0;
							}
						}
					}

					if (playerBounds.intersects(jCloud3Bounds))
					{
						// Check for downward collision (player is moving downwards)
						if (playerVelocityY > 0)
						{
							if (player.getPosition().y - playerBounds.height / 2 < jCloud3.getPosition().y)
							{
								// Calculate the new player position
								float newY = jCloud3.getPosition().y - playerBounds.height / 2;

								// Adjust player position and velocity
								player.setPosition(player.getPosition().x, newY);
								playerVelocityY = 0.f;
								jumpCount = 0;
							}
						}
					}

					if (playerBounds.intersects(jCloud4Bounds))
					{
						// Check for downward collision (player is moving downwards)
						if (playerVelocityY > 0)
						{
							if (player.getPosition().y - playerBounds.height / 2 < jCloud4.getPosition().y)
							{
								// Calculate the new player position
								float newY = jCloud4.getPosition().y - playerBounds.height / 2;

								// Adjust player position and velocity
								player.setPosition(player.getPosition().x, newY);
								playerVelocityY = 0.f;
								jumpCount = 0;
							}
						}
					}

					if (playerBounds.intersects(jCloud5Bounds))
					{
						// Check for downward collision (player is moving downwards)
						if (playerVelocityY > 0)
						{
							if (player.getPosition().y - playerBounds.height / 2 < jCloud5.getPosition().y)
							{
								// Calculate the new player position
								float newY = jCloud5.getPosition().y - playerBounds.height / 2;

								// Adjust player position and velocity
								player.setPosition(player.getPosition().x, newY);
								playerVelocityY = 0.f;
								jumpCount = 0;
							}
						}
					}

					if (playerBounds.intersects(jCloud6Bounds))
					{
						// Check for downward collision (player is moving downwards)
						if (playerVelocityY > 0)
						{
							if (player.getPosition().y - playerBounds.height / 2 < jCloud6.getPosition().y)
							{
								// Calculate the new player position
								float newY = jCloud6.getPosition().y - playerBounds.height / 2;

								// Adjust player position and velocity
								player.setPosition(player.getPosition().x, newY);
								playerVelocityY = 0.f;
								jumpCount = 0;
							}
						}
					}
					
					if (playerBounds.intersects(jCloud7Bounds))
					{
						// Check for downward collision (player is moving downwards)
						if (playerVelocityY > 0)
						{
							if (player.getPosition().y - playerBounds.height / 2 < jCloud7.getPosition().y)
							{
								// Calculate the new player position
								float newY = jCloud7.getPosition().y - playerBounds.height / 2;

								// Adjust player position and velocity
								player.setPosition(player.getPosition().x, newY);
								playerVelocityY = 0.f;
								jumpCount = 0;
							}
						}
					}

					if (playerBounds.intersects(jCloud8Bounds))
					{
						// Check for downward collision (player is moving downwards)
						if (playerVelocityY > 0)
						{
							if (player.getPosition().y - playerBounds.height / 2 < jCloud8.getPosition().y)
							{
								// Calculate the new player position
								float newY = jCloud8.getPosition().y - playerBounds.height / 2;

								// Adjust player position and velocity
								player.setPosition(player.getPosition().x, newY);
								playerVelocityY = 0.f;
								jumpCount = 0;
							}
						}
					}

					if (playerBounds.intersects(jCloud9Bounds))
					{
						// Check for downward collision (player is moving downwards)
						if (playerVelocityY > 0)
						{
							if (player.getPosition().y - playerBounds.height / 2 < jCloud9.getPosition().y)
							{
								// Calculate the new player position
								float newY = jCloud9.getPosition().y - playerBounds.height / 2;

								// Adjust player position and velocity
								player.setPosition(player.getPosition().x, newY);
								playerVelocityY = 0.f;
								jumpCount = 0;
							}
						}
					}

					if (playerBounds.intersects(jCloud10Bounds))
					{
						// Check for downward collision (player is moving downwards)
						if (playerVelocityY > 0)
						{
							if (player.getPosition().y - playerBounds.height / 2 < jCloud10.getPosition().y)
							{
								// Calculate the new player position
								float newY = jCloud10.getPosition().y - playerBounds.height / 2;

								// Adjust player position and velocity
								player.setPosition(player.getPosition().x, newY);
								playerVelocityY = 0.f;
								jumpCount = 0;
							}
						}
					}

					if (playerBounds.intersects(jCloud11Bounds))
					{
						// Check for downward collision (player is moving downwards)
						if (playerVelocityY > 0)
						{
							if (player.getPosition().y - playerBounds.height / 2 < jCloud11.getPosition().y)
							{
								// Calculate the new player position
								float newY = jCloud11.getPosition().y - playerBounds.height / 2;

								// Adjust player position and velocity
								player.setPosition(player.getPosition().x, newY);
								playerVelocityY = 0.f;
								jumpCount = 0;
							}
						}
					}

					if (playerBounds.intersects(jCloud12Bounds))
					{
						// Check for downward collision (player is moving downwards)
						if (playerVelocityY > 0)
						{
							if (player.getPosition().y - playerBounds.height / 2 < jCloud12.getPosition().y)
							{
								// Calculate the new player position
								float newY = jCloud12.getPosition().y - playerBounds.height / 2;

								// Adjust player position and velocity
								player.setPosition(player.getPosition().x, newY);
								playerVelocityY = 0.f;
								jumpCount = 0;
							}
						}
					}

					if (playerBounds.intersects(jCloud13Bounds))
					{
						// Check for downward collision (player is moving downwards)
						if (playerVelocityY > 0)
						{
							if (player.getPosition().y - playerBounds.height / 2 < jCloud13.getPosition().y)
							{
								// Calculate the new player position
								float newY = jCloud13.getPosition().y - playerBounds.height / 2;

								// Adjust player position and velocity
								player.setPosition(player.getPosition().x, newY);
								playerVelocityY = 0.f;
								jumpCount = 0;
							}
						}
					}

					if (player.getGlobalBounds().intersects(jSpring1.getGlobalBounds())) {
						if (!isSpringActivated && playerVelocityY > 0) {
							// Player jumps on the spring while moving downward, activate it
							isSpringActivated = true;
							playerVelocityY = -20.0f; // Adjust the vertical force as needed
							jSpring1.setTextureRect(sf::IntRect(19, 0, 18, 14)); // Assuming second frame starts at x=32
							jumpSound.play();
						}
					}
					else {
						isSpringActivated = false;
						jSpring1.setTextureRect(sf::IntRect(0, 0, 18, 14));
					}

					if (player.getGlobalBounds().intersects(jSpring2.getGlobalBounds())) {
						if (!isSpringActivated && playerVelocityY > 0) {
							// Player jumps on the spring while moving downward, activate it
							isSpringActivated = true;
							playerVelocityY = -10.0f; // Adjust the vertical force as needed
							jSpring2.setTextureRect(sf::IntRect(19, 0, 18, 14)); // Assuming second frame starts at x=32
							jumpSound.play();
						}
					}
					else {
						isSpringActivated = false;
						jSpring2.setTextureRect(sf::IntRect(0, 0, 18, 14));
					}

					if (playerBounds.intersects(jSCloud1.getGlobalBounds()))
					{
						// Check for downward collision (player is moving downwards)
						if (playerVelocityY > 0)
						{
							if (player.getPosition().y - playerBounds.height / 2 < jSCloud1.getPosition().y)
							{
								// Calculate the new player position
								float newY = jSCloud1.getPosition().y - playerBounds.height / 2;

								// Adjust player position and velocity
								player.setPosition(player.getPosition().x, newY);
								playerVelocityY = 0.f;
								jumpCount = 0;
							}
						}
					}

					if (playerBounds.intersects(jSCloud2.getGlobalBounds()))
					{
						// Check for downward collision (player is moving downwards)
						if (playerVelocityY > 0)
						{
							if (player.getPosition().y - playerBounds.height / 2 < jSCloud2.getPosition().y)
							{
								// Calculate the new player position
								float newY = jSCloud2.getPosition().y - playerBounds.height / 2;

								// Adjust player position and velocity
								player.setPosition(player.getPosition().x, newY);
								playerVelocityY = 0.f;
								jumpCount = 0;
							}
						}
					}

					if (playerBounds.intersects(wideBranchBounds1))
					{
						// Check for downward collision (player is moving downwards)
						if (playerVelocityY > 0)
						{
							if (player.getPosition().y - playerBounds.height / 2 < largeTreeBranch1.getPosition().y)
							{
								// Calculate the new player position
								float newY = largeTreeBranch1.getPosition().y - playerBounds.height / 2;

								// Adjust player position and velocity
								player.setPosition(player.getPosition().x, newY);
								playerVelocityY = 0.f;
								jumpCount = 0;
							}
						}
					}

					if (playerBounds.intersects(wideBranchBounds2))
					{
						// Check for downward collision (player is moving downwards)
						if (playerVelocityY > 0)
						{
							if (player.getPosition().y - playerBounds.height / 2 < largeTreeBranch1.getPosition().y)
							{
								// Calculate the new player position
								float newY = largeTreeBranch1.getPosition().y - playerBounds.height / 2;

								// Adjust player position and velocity
								player.setPosition(player.getPosition().x, newY);
								playerVelocityY = 0.f;
								jumpCount = 0;
							}
						}
					}

					if (player.getGlobalBounds().intersects(jSpring4.getGlobalBounds())) {
						if (!isSpringActivated && playerVelocityY > 0) {
							// Player jumps on the spring while moving downward, activate it
							isSpringActivated = true;
							playerVelocityY = -10.0f; // Adjust the vertical force as needed
							jSpring4.setTextureRect(sf::IntRect(19, 0, 18, 14)); // Assuming second frame starts at x=32
							jumpSound.play();
						}
					}
					else {
						isSpringActivated = false;
						jSpring4.setTextureRect(sf::IntRect(0, 0, 18, 14));
					}

					if (player.getGlobalBounds().intersects(jSpring3.getGlobalBounds())) {
						if (!isSpringActivated && playerVelocityY > 0) {
							// Player jumps on the spring while moving downward, activate it
							isSpringActivated = true;
							playerVelocityY = -10.0f; // Adjust the vertical force as needed
							jSpring3.setTextureRect(sf::IntRect(19, 0, 18, 14)); // Assuming second frame starts at x=32
							jumpSound.play();
						}
					}
					else {
						isSpringActivated = false;
						jSpring3.setTextureRect(sf::IntRect(0, 0, 18, 14));
					}


					//-----------------------JUNGLE SQUISH CHECK-------------------------------------------------------------------------------//

					if (player.getGlobalBounds().intersects(jEnemyBlue1.getGlobalBounds()) && damageCooldown.getElapsedTime() > coolDownDuration)
					{
						float playerFeet = player.getPosition().y + player.getGlobalBounds().height / 2.0f;
						float enemyTopjeb1 = jEnemyBlue1.getPosition().y - jEnemyBlue1.getGlobalBounds().height / 2.0f;

						if (playerFeet < enemyTopjeb1)
						{
							
							playerVelocityY = -12.f;
							stompSound.play();
							isSquishedjeb1 = true;
							squishTimerjeb1.restart();

						}
						else
						{
							// Player touches the enemy without jumping, so player gets damaged
							spikeStabSound.play();
							currentHealth--;
							float knockbackDistance = 100.0f; // Adjust as needed

							if (player.getPosition().x < jEnemyBlue1.getPosition().x)
							{
								player.setPosition(player.getPosition().x - knockbackDistance, player.getPosition().y);
							}
							else
							{
								player.setPosition(player.getPosition().x + knockbackDistance, player.getPosition().y);
							}
							blinkingTimer.restart();
							damageCooldown.restart();
						}
					}

					if (isSquishedjeb1)
					{
						sf::Time elapsed = squishTimerjeb1.getElapsedTime();
						if (elapsed < squishDurationjeb1)
						{
							// Show squished appearance on the ground
							jEnemyBlue1.setScale(3.f, 0.5f); // Adjust the y-scale for the squish effect
							jEnemyBlue1.setPosition(jEnemyBlue1.getPosition().x, jCloud5.getPosition().y);
							jB1enemySpeed = 0.f;
						}
						else
						{
							// Remove the enemy after the squish duration
							isSquishedjeb1 = false;
							jEnemyBlue1.setPosition(-1000.0f, -1000.0f);
						}
					}
					//-----------------------------------------------------
					if (player.getGlobalBounds().intersects(jEnemyBlue2.getGlobalBounds()) && damageCooldown.getElapsedTime() > coolDownDuration)
					{
						float playerFeet = player.getPosition().y + player.getGlobalBounds().height / 2.0f;
						float enemyTopjeb2 = jEnemyBlue2.getPosition().y - jEnemyBlue2.getGlobalBounds().height / 2.0f;

						if (playerFeet < enemyTopjeb2)
						{

							playerVelocityY = -12.f;
							stompSound.play();
							isSquishedjeb2 = true;
							squishTimerjeb2.restart();

						}
						else
						{
							// Player touches the enemy without jumping, so player gets damaged
							spikeStabSound.play();
							currentHealth--;
							float knockbackDistance = 100.0f; // Adjust as needed

							if (player.getPosition().x < jEnemyBlue2.getPosition().x)
							{
								player.setPosition(player.getPosition().x - knockbackDistance, player.getPosition().y);
							}
							else
							{
								player.setPosition(player.getPosition().x + knockbackDistance, player.getPosition().y);
							}
							blinkingTimer.restart();
							damageCooldown.restart();
						}
					}

					if (isSquishedjeb2)
					{
						sf::Time elapsed = squishTimerjeb2.getElapsedTime();
						if (elapsed < squishDurationjeb2)
						{
							// Show squished appearance on the ground
							jEnemyBlue2.setScale(3.f, 0.5f); // Adjust the y-scale for the squish effect
							jEnemyBlue2.setPosition(jEnemyBlue2.getPosition().x, jCloud8.getPosition().y);
							jB2enemySpeed = 0.f;
						}
						else
						{
							// Remove the enemy after the squish duration
							isSquishedjeb2 = false;
							jEnemyBlue2.setPosition(-1000.0f, -1000.0f);
						}
					}

				//-----------------------------------------------------------
					if (player.getGlobalBounds().intersects(jEnemyBlue3.getGlobalBounds()) && damageCooldown.getElapsedTime() > coolDownDuration)
					{
						float playerFeet = player.getPosition().y + player.getGlobalBounds().height / 2.0f;
						float enemyTopjeb3 = jEnemyBlue3.getPosition().y - jEnemyBlue3.getGlobalBounds().height / 2.0f;

						if (playerFeet < enemyTopjeb3)
						{

							playerVelocityY = -12.f;
							stompSound.play();
							isSquishedjeb3 = true;
							squishTimerjeb3.restart();

						}
						else
						{
							// Player touches the enemy without jumping, so player gets damaged
							spikeStabSound.play();
							currentHealth--;
							float knockbackDistance = 100.0f; // Adjust as needed

							if (player.getPosition().x < jEnemyBlue3.getPosition().x)
							{
								player.setPosition(player.getPosition().x - knockbackDistance, player.getPosition().y);
							}
							else
							{
								player.setPosition(player.getPosition().x + knockbackDistance, player.getPosition().y);
							}
							blinkingTimer.restart();
							damageCooldown.restart();
						}
					}

					if (isSquishedjeb3)
					{
						sf::Time elapsed = squishTimerjeb3.getElapsedTime();
						if (elapsed < squishDurationjeb3)
						{
							// Show squished appearance on the ground
							jEnemyBlue3.setScale(3.f, 0.5f); // Adjust the y-scale for the squish effect
							jEnemyBlue3.setPosition(jEnemyBlue3.getPosition().x, jCloud10.getPosition().y);
							jB3enemySpeed = 0.f;
						}
						else
						{
							// Remove the enemy after the squish duration
							isSquishedjeb3 = false;
							jEnemyBlue3.setPosition(-1000.0f, -1000.0f);
						}
					}

					//--------------------------------------------------------------------
					if (player.getGlobalBounds().intersects(jEnemyRed1.getGlobalBounds()) && damageCooldown.getElapsedTime() > coolDownDuration)
					{
						float playerFeet = player.getPosition().y + player.getGlobalBounds().height / 2.0f;
						float enemyTopjer1 = jEnemyRed1.getPosition().y - jEnemyRed1.getGlobalBounds().height / 2.0f;

						if (playerFeet < enemyTopjer1)
						{

							playerVelocityY = -12.f;
							stompSound.play();
							isSquishedjer1 = true;
							squishTimerjer1.restart();

						}
						else
						{
							// Player touches the enemy without jumping, so player gets damaged
							spikeStabSound.play();
							currentHealth--;
							float knockbackDistance = 100.0f; // Adjust as needed

							if (player.getPosition().x < jEnemyRed1.getPosition().x)
							{
								player.setPosition(player.getPosition().x - knockbackDistance, player.getPosition().y);
							}
							else
							{
								player.setPosition(player.getPosition().x + knockbackDistance, player.getPosition().y);
							}
							blinkingTimer.restart();
							damageCooldown.restart();
						}
					}

					if (isSquishedjer1)
					{
						sf::Time elapsed = squishTimerjer1.getElapsedTime();
						if (elapsed < squishDurationjer1)
						{
							// Show squished appearance on the ground
							jEnemyRed1.setScale(3.f, 0.5f); // Adjust the y-scale for the squish effect
							jEnemyRed1.setPosition(jEnemyRed1.getPosition().x, jEnemyRed1.getPosition().y);
							jR1enemySpeed = 0.f;
						}
						else
						{
							// Remove the enemy after the squish duration
							isSquishedjer1 = false;
							jEnemyRed1.setPosition(-1000.0f, -1000.0f);
						}
					}
					//-------------------------------------------------
					if (player.getGlobalBounds().intersects(jEnemyRed2.getGlobalBounds()) && damageCooldown.getElapsedTime() > coolDownDuration)
					{
						float playerFeet = player.getPosition().y + player.getGlobalBounds().height / 2.0f;
						float enemyTopjer2 = jEnemyRed2.getPosition().y - jEnemyRed2.getGlobalBounds().height / 2.0f;

						if (playerFeet < enemyTopjer2)
						{

							playerVelocityY = -12.f;
							stompSound.play();
							isSquishedjer2 = true;
							squishTimerjer2.restart();

						}
						else
						{
							// Player touches the enemy without jumping, so player gets damaged
							spikeStabSound.play();
							currentHealth--;
							float knockbackDistance = 100.0f; // Adjust as needed

							if (player.getPosition().x < jEnemyRed2.getPosition().x)
							{
								player.setPosition(player.getPosition().x - knockbackDistance, player.getPosition().y);
							}
							else
							{
								player.setPosition(player.getPosition().x + knockbackDistance, player.getPosition().y);
							}
							blinkingTimer.restart();
							damageCooldown.restart();
						}
					}

					if (isSquishedjer2)
					{
						sf::Time elapsed = squishTimerjer2.getElapsedTime();
						if (elapsed < squishDurationjer2)
						{
							// Show squished appearance on the ground
							jEnemyRed2.setScale(3.f, 0.5f); // Adjust the y-scale for the squish effect
							jEnemyRed2.setPosition(jEnemyRed2.getPosition().x, jEnemyRed2.getPosition().y);
							jR1enemySpeed = 0.f;
						}
						else
						{
							// Remove the enemy after the squish duration
							isSquishedjer2 = false;
							jEnemyRed2.setPosition(-1000.0f, -1000.0f);
						}
					}

					//------------------------------------------------------
					if (player.getGlobalBounds().intersects(jFEnemy1.getGlobalBounds()) && damageCooldown.getElapsedTime() > coolDownDuration)
					{
						float playerFeet = player.getPosition().y + player.getGlobalBounds().height / 2.0f;
						float enemyTopjef1 = jFEnemy1.getPosition().y - jFEnemy1.getGlobalBounds().height / 2.0f;

						if (playerFeet < enemyTopjef1)
						{
							// Player jumps on the enemy, so enemy is squished
							playerVelocityY = -12.f;
							stompSound.play();
							isSquishedjef1 = true;
							squishTimerjef1.restart();

						}
						else
						{
							// Player touches the enemy without jumping, so player gets damaged
							spikeStabSound.play();
							currentHealth--;
							float knockbackDistance = 100.0f; // Adjust as needed
							if (player.getPosition().x < jFEnemy1.getPosition().x)
							{
								player.setPosition(player.getPosition().x - knockbackDistance, player.getPosition().y);
							}
							else
							{
								player.setPosition(player.getPosition().x + knockbackDistance, player.getPosition().y);
							}
							blinkingTimer.restart();
							damageCooldown.restart();
						}
					}

					if (isSquishedjef1)
					{
						sf::Time elapsed = squishTimerjef1.getElapsedTime();
						if (elapsed < squishDurationjef1)
						{
							// Show squished appearance on the ground
							//fEnemy.setScale(3.f, 0.5f); // Adjust the y-scale for the squish effect
							jFEnemy1.move(0.f, 20.f);
							jF1enemySpeed = 0.f;
						}
						else
						{
							// Remove the enemy after the squish duration
							isSquishedjef1 = false;
							jFEnemy1.setPosition(-1000.0f, -1000.0f);
						}
					}

					//----------------------------------------------------------------
					if (player.getGlobalBounds().intersects(jFEnemy2.getGlobalBounds()) && damageCooldown.getElapsedTime() > coolDownDuration)
					{
						float playerFeet = player.getPosition().y + player.getGlobalBounds().height / 2.0f;
						float enemyTopjef2 = jFEnemy2.getPosition().y - jFEnemy2.getGlobalBounds().height / 2.0f;

						if (playerFeet < enemyTopjef2)
						{
							// Player jumps on the enemy, so enemy is squished
							playerVelocityY = -12.f;
							stompSound.play();
							isSquishedjef2 = true;
							squishTimerjef2.restart();

						}
						else
						{
							// Player touches the enemy without jumping, so player gets damaged
							spikeStabSound.play();
							currentHealth--;
							float knockbackDistance = 100.0f; // Adjust as needed
							if (player.getPosition().x < jFEnemy2.getPosition().x)
							{
								player.setPosition(player.getPosition().x - knockbackDistance, player.getPosition().y);
							}
							else
							{
								player.setPosition(player.getPosition().x + knockbackDistance, player.getPosition().y);
							}
							blinkingTimer.restart();
							damageCooldown.restart();
						}
					}

					if (isSquishedjef2)
					{
						sf::Time elapsed = squishTimerjef2.getElapsedTime();
						if (elapsed < squishDurationjef1)
						{
							// Show squished appearance on the ground
							//fEnemy.setScale(3.f, 0.5f); // Adjust the y-scale for the squish effect
							jFEnemy2.move(0.f, 20.f);
							jF2enemySpeed = 0.f;
						}
						else
						{
							// Remove the enemy after the squish duration
							isSquishedjef2 = false;
							jFEnemy2.setPosition(-1000.0f, -1000.0f);
						}
					}
					//---------------------------------------------------
					//Spike Collisions

					if (playerBounds.intersects(jSpike1Bounds) && damageCooldown.getElapsedTime() > coolDownDuration)
					{
						playerVelocityY = -12.f;
						currentHealth--;

						spikeStabSound.play();

						blinkingTimer.restart();
						damageCooldown.restart();
					}

					if (playerBounds.intersects(jSpike2Bounds) && damageCooldown.getElapsedTime() > coolDownDuration)
					{
						playerVelocityY = -12.f;
						currentHealth--;

						spikeStabSound.play();

						blinkingTimer.restart();
						damageCooldown.restart();
					}

					if (playerBounds.intersects(jSpike3Bounds) && damageCooldown.getElapsedTime() > coolDownDuration)
					{
						playerVelocityY = -12.f;
						currentHealth--;

						spikeStabSound.play();

						blinkingTimer.restart();
						damageCooldown.restart();
					}

					if (playerBounds.intersects(jSpike4Bounds) && damageCooldown.getElapsedTime() > coolDownDuration)
					{
						playerVelocityY = -12.f;
						currentHealth--;

						spikeStabSound.play();

						blinkingTimer.restart();
						damageCooldown.restart();
					}

					//-------------------------COINS

					if (jCoins1FrameCount == jCoins1SwitchFrame) {
						jCoins1FrameCount = 0;
						if (jCoins1.getTextureRect().left == 0)
							jCoins1.setTextureRect(sf::IntRect(20, 0, 8, 12));
						else
							jCoins1.setTextureRect(sf::IntRect(0, 0, 12, 12));
					}
					else {
						jCoins1FrameCount++;
					}

					if (jCoins2FrameCount == jCoins2SwitchFrame) {
						jCoins2FrameCount = 0;
						if (jCoins2.getTextureRect().left == 0)
							jCoins2.setTextureRect(sf::IntRect(20, 0, 8, 12));
						else
							jCoins2.setTextureRect(sf::IntRect(0, 0, 12, 12));
					}
					else {
						jCoins2FrameCount++;
					}

					if (jCoins3FrameCount == jCoins3SwitchFrame) {
						jCoins3FrameCount = 0;
						if (jCoins3.getTextureRect().left == 0)
							jCoins3.setTextureRect(sf::IntRect(20, 0, 8, 12));
						else
							jCoins3.setTextureRect(sf::IntRect(0, 0, 12, 12));
					}
					else {
						jCoins3FrameCount++;
					}

					if (playerBounds.intersects(jCoins1.getGlobalBounds()) && damageCooldown.getElapsedTime() > coolDownDuration)
					{
						coins += 1;
						coinSound.play();
						jCoins1.setPosition(-1000, -1000);
					}

					if (playerBounds.intersects(jCoins2.getGlobalBounds()) && damageCooldown.getElapsedTime() > coolDownDuration)
					{
						coins += 1;
						coinSound.play();
						jCoins2.setPosition(-1000, -1000);
					}

					if (playerBounds.intersects(jCoins3.getGlobalBounds()) && damageCooldown.getElapsedTime() > coolDownDuration)
					{
						coins += 1;
						coinSound.play();
						jCoins3.setPosition(-1000, -1000);
					}

					if (playerBounds.intersects(jKey.getGlobalBounds()) && damageCooldown.getElapsedTime() > coolDownDuration)
					{
						hasKey = true;
						keySound.play();
						jKey.setPosition(-1000, -1000);
					}

					if (playerBounds.intersects(jDoor.getGlobalBounds()) && damageCooldown.getElapsedTime() > coolDownDuration)
					{
						if (hasKey == true && coins == 3)
						{
							player.setPosition(spring4h.getPosition().x - 100, snowP1.getPosition().y + 50);
							victorySound.play();
							jungle.stop();
							hasKeyLevel4 = true;
							level3Friendbool = true;
							std::this_thread::sleep_for(std::chrono::seconds(5));
							currentLevel = 7;
							player.setPosition(20, 1000);
							endingMusic.play();
							
						}
					}

					if (player.getPosition().y >= 1100)
					{
						spikeStabSound.play();
						currentHealth -= 3;
						playerVelocityY = 0.f;
						jumpCount = 1;
					}

					if (currentHealth == 0)
					{
						currentLevel = 1;
						player.setPosition(spring1h.getPosition().x - 200, snowP1.getPosition().y + 50);
						jungle.stop();

						jCoins1.setPosition(921, 1010);
						jCoins2.setPosition(49, 257);
						jCoins3.setPosition(1446, 257);

						jKey.setPosition(1825, 132);
					}

					
					updateHealth(currentHealth);

					//DRAW OBJECT JUNGLE

					window.clear();
					window.setView(view);
					window.draw(fBg);

					//DRAW ENEMIES
					window.draw(jEnemyBlue1);
					window.draw(jEnemyBlue2);
					window.draw(jEnemyBlue3);

					window.draw(jEnemyRed1);
					window.draw(jEnemyRed2);

					window.draw(jFEnemy1);
					window.draw(jFEnemy2);

					//DRAW GRASS
					window.draw(grassChunk);
					window.draw(grassPlat1);
					window.draw(grassPlat2);
					window.draw(grassPlat3);
					window.draw(grassPlat4);
					window.draw(grassPlatCut);

					//DRAW SPIKES
					window.draw(jSpike1);
					window.draw(jSpike2);
					window.draw(jSpike3);
					window.draw(jSpike4);


					//DRAW BRANCHES
					window.draw(branch1);
					window.draw(branch2);
					window.draw(branch3);
					window.draw(branch4);
					window.draw(largeTreeBranch1);
					window.draw(largeTreeBranch2);

					//DRAW PLAYER
					if (blinkingTimer.getElapsedTime() < blinkingTimerDuration)
					{
						if (static_cast<int>(blinkingTimer.getElapsedTime().asSeconds() * 5) % 2 == 0)
						{
							window.draw(player);
						}
					}
					else
					{
						window.draw(player);
					}

					//DRAW TREES
					window.draw(tree1);
					window.draw(tree2);
					window.draw(tree3);
					window.draw(tree4);

					//DRAW CLOUDS
					window.draw(jCloud1);
					window.draw(jCloud2);
					window.draw(jCloud3);
					window.draw(jCloud4);
					window.draw(jCloud5);
					window.draw(jCloud6);
					window.draw(jCloud7);
					window.draw(jCloud8);
					window.draw(jCloud9);
					window.draw(jCloud10);
					window.draw(jCloud11);
					window.draw(jCloud12);
					window.draw(jCloud13);

					//DRAW LARGE TREE
					window.draw(largeTree);

					//DRAW SMALL CLOUDS
					window.draw(jSCloud1);
					window.draw(jSCloud2);

					//DRAW SPRINGS
					window.draw(jSpring1);
					window.draw(jSpring2);
					window.draw(jSpring3);
					window.draw(jSpring4);

					//DRAW DOOR
					window.draw(jDoor);
					window.draw(coinInDoorJ);
					window.draw(keyInDoor);

					//DRAW COINS
					window.draw(jCoins1);
					window.draw(jCoins2);
					window.draw(jCoins3);

					//DRAW KEY
					window.draw(jKey);

					//DRAW HEALTHBAR
					window.setView(guiView);
					drawHealthBar(window, filledHeartTexture, emptyHeartTexture);

					

					window.display();
				break;
			case 5: //ENDING C5

				jumpVelocity = -2;

				player.setScale(0.8, 0.8);

				level1Friend.setTexture(bfriend1T);
				level2Friend.setTexture(bfriend2T);
				level3Friend.setTexture(bfriend3T);
				level4Friend.setTexture(bfriend4T);

				level1Friend.setScale(0.8, 0.8);
				level2Friend.setScale(0.8, 0.8);
				level3Friend.setScale(-0.8, 0.8);
				level4Friend.setScale(-0.8,0.8);

				level1Friend.setPosition(1869, 1049.5);
				level2Friend.setPosition(1894, 1049.5);
				level3Friend.setPosition(1803, 1049.5);
				level4Friend.setPosition(1771, 1049.5);

				endingDialogue1.setPosition(1702, level1Friend.getPosition().y - 35);
				endingDialogue2.setPosition(1741, level2Friend.getPosition().y - 35);
				endingDialogue3.setPosition(level3Friend.getPosition().x + 10, level3Friend.getPosition().y - 35);
			    /*level1Friend.setPosition():*/
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
				{
					playerVelocityX = -1.f;
					isMoving = true;
					movingLeft = true;
					movingRight = false;
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
				{
					playerVelocityX = 1.f;
					isMoving = true;
					movingLeft = false;
					movingRight = true;
				}
				else
				{
					playerVelocityX = 0.f;
					isMoving = false;
					movingLeft = false;
					movingRight = false;
				}

				//PLAYER JUMP
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) 
				{
					if (!isJumping && jumpCount < maxJump)
					{
						isJumping = true;
						playerVelocityY = jumpVelocity;
						jumpCount++;
						frameCount = 0;

						jumpSound.play();
					}
				}
				else
				{
					isJumping = false;
				}

				playerVelocityY += gravity;
				player.move(playerVelocityX, playerVelocityY);

				if (player.getPosition().x < 0) {
					// Correct position to be exactly at the left boundary
					player.setPosition(0, player.getPosition().y);

					// If the player is moving left, stop horizontal movement
					if (playerVelocityX < 0) {
						playerVelocityX = 0.f;
					}
				}

				if (player.getPosition().x > 1920) {
					// Correct position to be exactly at the left boundary
					player.setPosition(1920, player.getPosition().y);

					// If the player is moving left, stop horizontal movement
					if (playerVelocityX > 1920) {
						playerVelocityX = 0.f;
					}
				}

				if (player.getPosition().y < 0) {
					// Correct position to be exactly at the left boundary
					player.setPosition(player.getPosition().x, 0);

					// If the player is moving left, stop horizontal movement
					if (playerVelocityY < 0) {
						playerVelocityY = 0.f;
					}
				}

				//FLOOR COLLISION
				if (player.getPosition().y >= 1059.f)
				{
					player.setPosition(player.getPosition().x, 1059.f);
					playerVelocityY = 0.f;
					jumpCount = 0;
				}
				if (player.getPosition().y == 1059.f)
				{
					jumpCount = 0;
				}

				//-------------------------------------------------------------------------------------
				//ANIMATIONS

				//JUMPING ANIMATION
				if (isJumping)
				{
					player.setTextureRect(sf::IntRect(0, 0, 20, 24));
				}
				//LEFT MOVEMENT ANIMATION
				else if (movingLeft)
				{
					if (frameCount == switchFrame)
					{
						frameCount = 0;
						if (player.getTextureRect().left == 0)
							player.setTextureRect(sf::IntRect(24, 0, 20, 24));
						else
							player.setTextureRect(sf::IntRect(0, 0, 20, 24));
					}
					else
					{
						frameCount++;
					}
				}
				//RIGHT MOVEMENT ANIMATION
				else if (movingRight)
				{
					if (frameCount == switchFrame)
					{
						frameCount = 0;
						if (player.getTextureRect().left == 0)
						{
							player.setTextureRect(sf::IntRect(24, 0, 20, 24));
						}
						else
						{
							player.setTextureRect(sf::IntRect(0, 0, 20, 24));
						}
					}
					else
					{
						frameCount++;
					}
				}
				else
				{
					player.setTextureRect(sf::IntRect(24, 0, 20, 24));
				}

				//FLIPS THE SPRITE BASED ON DIRECTION
				if (movingLeft)
				{
					player.setScale(-0.8f, 0.8f);
				}
				else if (movingRight)
				{
					player.setScale(0.8f, 0.8f);
				}

				window.clear();
				window.clear();
				window.setView(endView);
				window.draw(end);
				window.draw(man);
				
				
				
				window.draw(level1Friend);
				window.draw(level2Friend);
				window.draw(level3Friend);
				window.draw(level4Friend);
				window.draw(player);

				if (playerBounds.intersects(level4Friend.getGlobalBounds()))
				{
					endingMusic.stop();
					suspense.play();
					window.draw(endingDialogue1);
					alien1.play();
					window.display();
					std::this_thread::sleep_for(std::chrono::seconds(5));
					window.draw(endingDialogue2);
					alien2.play();
					window.display();
					std::this_thread::sleep_for(std::chrono::seconds(7));
					window.draw(endingDialogue3);
					alien3.play();
					window.display();
					std::this_thread::sleep_for(std::chrono::seconds(7));
					credits = true;
					currentLevel = 6;
				}

				window.display();
				break;
			case 6:
				window.setView(defview);

				window.draw(black);
				window.display();
				stompSound.play();
				std::this_thread::sleep_for(std::chrono::seconds(3));

				stompSound.play();
				std::this_thread::sleep_for(std::chrono::seconds(2));
				stompSound.play();
				std::this_thread::sleep_for(std::chrono::seconds(1));
				stompSound.play();
				std::this_thread::sleep_for(std::chrono::seconds(1));
				stompSound.play();
				std::this_thread::sleep_for(std::chrono::seconds(1));
				stompSound.play();
				std::this_thread::sleep_for(std::chrono::seconds(7));


				alien1.play();
				std::this_thread::sleep_for(std::chrono::seconds(3));
				alien2.play();
				std::this_thread::sleep_for(std::chrono::seconds(3));
				alien1.play();
				std::this_thread::sleep_for(std::chrono::seconds(5));


				jumpscareSound.play();
				jumpscareSound.setVolume(100);
				window.draw(jumpscare);
				window.display();
				std::this_thread::sleep_for(std::chrono::seconds(4));


				window.draw(black);
				window.display();
				std::this_thread::sleep_for(std::chrono::seconds(5));
				if (credits == true)
				{
					creditsMusic.play();
				}
				window.draw(credits1);
				window.display();
				std::this_thread::sleep_for(std::chrono::seconds(20));
				window.draw(credits2);
				window.display();
				std::this_thread::sleep_for(std::chrono::seconds(20));
				window.draw(credits3);
				window.display();
				std::this_thread::sleep_for(std::chrono::seconds(20));
				creditsMusic.stop();
				menuActive = true;
				

				break;
			case 7:
				jumpVelocity = -5;
				
				//Player Movement
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
				{
					playerVelocityX = -2.f;
					isMoving = true;
					movingLeft = true;
					movingRight = false;
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
				{
					playerVelocityX = 2.f;
					isMoving = true;
					movingLeft = false;
					movingRight = true;
				}
				else
				{
					playerVelocityX = 0.f;
					isMoving = false;
					movingLeft = false;
					movingRight = false;
				}

				//Player Jump
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
				{
					if (!isJumping && jumpCount < maxJump)
					{
						isJumping = true;
						playerVelocityY = jumpVelocity;
						jumpCount++;
						frameCount = 0;

						jumpSound.play();
					}
				}
				else
				{
					isJumping = false;
				}

				playerVelocityY += gravity;
				player.move(playerVelocityX, playerVelocityY);

				if (player.getPosition().x < 0) {
					// Correct position to be exactly at the left boundary
					player.setPosition(0, player.getPosition().y);

					// If the player is moving left, stop horizontal movement
					if (playerVelocityX < 0) {
						playerVelocityX = 0.f;
					}
				}

				if (player.getPosition().x > 1920) {
					// Correct position to be exactly at the left boundary
					player.setPosition(1920, player.getPosition().y);

					// If the player is moving left, stop horizontal movement
					if (playerVelocityX > 1920) {
						playerVelocityX = 0.f;
					}
				}

				if (player.getPosition().y < 0) {
					// Correct position to be exactly at the left boundary
					player.setPosition(player.getPosition().x, 0);

					// If the player is moving left, stop horizontal movement
					if (playerVelocityY < 0) {
						playerVelocityY = 0.f;
					}
				}

				//Floor
				if (player.getPosition().y >= 965.f)
				{
					player.setPosition(player.getPosition().x, 965.f);
					playerVelocityY = 0.f;
					jumpCount = 0;
				}
				if (player.getPosition().y == 965.f)
				{
					jumpCount = 0;
				}

				//-----------------------------------ANIMATIONS---------------------------------------//
				// Jumping Animation
				if (isJumping)
				{
					player.setTextureRect(sf::IntRect(0, 0, 20, 24));
				}

				//Left Movement Animation
				else if (movingLeft)
				{
					if (frameCount == switchFrame)
					{
						frameCount = 0;
						if (player.getTextureRect().left == 0)
							player.setTextureRect(sf::IntRect(24, 0, 20, 24));
						else
							player.setTextureRect(sf::IntRect(0, 0, 20, 24));
					}
					else
					{
						frameCount++;
					}
				}

				//Right Movement Animation
				else if (movingRight)
				{
					if (frameCount == switchFrame)
					{
						frameCount = 0;
						if (player.getTextureRect().left == 0)
						{
							player.setTextureRect(sf::IntRect(24, 0, 20, 24));
						}
						else
						{
							player.setTextureRect(sf::IntRect(0, 0, 20, 24));
						}
					}
					else
					{
						frameCount++;
					}
				}
				else
				{
					player.setTextureRect(sf::IntRect(24, 0, 20, 24));
				}

				//Flips the Sprite Based on Direction
				if (movingLeft)
				{
					player.setScale(-2.f, 2.f);
				}
				else if (movingRight)
				{
					player.setScale(2.f, 2.f);
				}
				if (playerBounds.intersects(tDoor.getGlobalBounds()))
				{
					doorSound.play();
					currentLevel = 1;
					player.setPosition(spring1h.getPosition().x - 200, snowP1.getPosition().y);
					home.play();
					endingMusic.stop();
				}

				window.clear();
				window.setView(view);
				window.draw(trans);
				window.draw(tDoor);
				window.draw(player);
				window.display();

				break;
			}
		}
		else
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				playerVelocityX = -5.f;
				isMoving = true;
				movingLeft = true;
				movingRight = false;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				playerVelocityX = 5.f;
				isMoving = true;
				movingLeft = false;
				movingRight = true;
			}
			else
			{
				playerVelocityX = 0.f;
				isMoving = false;
				movingLeft = false;
				movingRight = false;
			}

			//PLAYER JUMP
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				if (!isJumping && jumpCount < maxJump)
				{
					isJumping = true;
					playerVelocityY = jumpVelocity;
					jumpCount++;
					frameCount = 0;

					jumpSound.play();
				}
			}
			else
			{
				isJumping = false;
			}

			playerVelocityY += gravity;
			player.move(playerVelocityX, playerVelocityY);

			//FLOOR COLLISION
			if (player.getPosition().y >= 967.f)
			{
				player.setPosition(player.getPosition().x, 967.f);
				playerVelocityY = 0.f;
				jumpCount = 0;
			}
			if (player.getPosition().y == 967.f)
			{
				jumpCount = 0;
			}

			//-------------------------------------------------------------------------------------
			//ANIMATIONS

			//JUMPING ANIMATION
			if (isJumping)
			{
				player.setTextureRect(sf::IntRect(0, 0, 20, 24));
			}
			//LEFT MOVEMENT ANIMATION
			else if (movingLeft)
			{
				if (frameCount == switchFrame)
				{
					frameCount = 0;
					if (player.getTextureRect().left == 0)
						player.setTextureRect(sf::IntRect(24, 0, 20, 24));
					else
						player.setTextureRect(sf::IntRect(0, 0, 20, 24));
				}
				else
				{
					frameCount++;
				}
			}
			//RIGHT MOVEMENT ANIMATION
			else if (movingRight)
			{
				if (frameCount == switchFrame)
				{
					frameCount = 0;
					if (player.getTextureRect().left == 0)
					{
						player.setTextureRect(sf::IntRect(24, 0, 20, 24));
					}
					else
					{
						player.setTextureRect(sf::IntRect(0, 0, 20, 24));
					}
				}
				else
				{
					frameCount++;
				}
			}
			else
			{
				player.setTextureRect(sf::IntRect(24, 0, 20, 24));
			}

			//FLIPS THE SPRITE BASED ON DIRECTION
			if (movingLeft)
			{
				player.setScale(-2.f, 2.f);
			}
			else if (movingRight)
			{
				player.setScale(2.f, 2.f);
			}

			if (dialogueClock.getElapsedTime() > dialogueClockDur)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::N))
				{
					mDialogueNum += 1;
					dialogueSound.play();
					dialogueClock.restart();
				}
			}


			switch (mDialogueNum)
			{
			case 2:
				mDialogue.setTexture(mDialogueTex2);
				break;
			case 3:
				mDialogue.setTexture(mDialogueTex3);
				break;
			case 4:
				mDialogue.setTexture(mDialogueTex4);
				break;
			case 5:
				mDialogue.setTexture(mDialogueTex5);
				break;
			case 6:
				mDialogue.setTexture(mDialogueTex6);
				break;
			case 7:
				mDialogue.setTexture(mDialogueTex7);
				break;
			}

			window.clear();
			
			sf::Time elapsed = fadeInClock.getElapsedTime();
			alpha = 255 * std::min(elapsed.asSeconds() / 5.0f, 1.0f);

			logo.setColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(alpha)));

			window.clear();
			window.draw(logoBg);
			window.draw(logo);

			if (clock.getElapsedTime().asSeconds() >= 10)
			{
				bgMusic.setVolume(50);
				window.draw(menuBackground);
				window.draw(mSnowman);

				if (playerBounds.intersects(mSnowman.getGlobalBounds()))
				{
					window.draw(mDialogue);
				}

				window.draw(player);

			}
			window.display();

		}
	}
	return 0;
}






