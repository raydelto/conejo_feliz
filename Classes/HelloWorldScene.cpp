#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
	auto scene = Scene::createWithPhysics();
	scene -> getPhysicsWorld () -> setGravity(Vect(0,0));
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();
	scene -> getPhysicsWorld() ->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

void HelloWorld::moverJugador(Touch* toque, Event* evento)
{
	auto posicionToque = toque -> getLocation();
	if(_conejo->getBoundingBox().containsPoint(posicionToque)){
		_conejo -> setPositionX(posicionToque.x);
	}
	
}

void HelloWorld::inicializarFisica(cocos2d::Sprite* sprite)
{
	auto cuerpo = PhysicsBody::createCircle(sprite -> getContentSize().width / 2);
	cuerpo -> setContactTestBitmask(true);
	cuerpo -> setDynamic(true);
	sprite->setPhysicsBody(cuerpo);
}

void HelloWorld::agregarBombar(float dt)
{
	auto director = Director::getInstance();
	auto tamano = director->getWinSize();
	Sprite* bomba = nullptr;
	for(int i = 0 ; i < 3 ; i++)
	{
		bomba = Sprite::create("imagenes/bomba.png");
		bomba -> setAnchorPoint(Vec2::ZERO);
		bomba -> setPosition(CCRANDOM_0_1() * tamano.width , tamano.height);
		inicializarFisica(bomba);
		bomba ->getPhysicsBody()->setVelocity(Vect(0, ( (CCRANDOM_0_1() + 0.2f) * -250) ));
		_bombas.pushBack(bomba);
		this -> addChild(bomba, 1);
	}
}

void HelloWorld::inicializarToque()
{
	auto escuchador = EventListenerTouchOneByOne::create();
	escuchador -> onTouchBegan = [] (Touch* touch, Event* event) { return true;};
	escuchador -> onTouchMoved = CC_CALLBACK_2(HelloWorld::moverJugador, this);
	escuchador -> onTouchEnded = [=] (Touch* touch, Event* event) {}; 
	_eventDispatcher -> addEventListenerWithSceneGraphPriority(escuchador, this);
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
	auto director = Director::getInstance();
	auto tamano = director->getWinSize();
	auto spriteFondo = Sprite::create("imagenes/fondo.png");    
	spriteFondo -> setAnchorPoint(Vec2::ZERO);
	spriteFondo -> setPosition(0,0);
	addChild(spriteFondo,0);	
	_conejo = Sprite::create("imagenes/conejo.png");	
	_conejo -> setPosition(tamano.width / 2 , tamano.height * 0.23);
	inicializarFisica(_conejo);
	addChild(_conejo,1);
	inicializarToque();
	schedule(schedule_selector(HelloWorld::agregarBombar), 5.0f);
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
