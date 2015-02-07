#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
private:
	cocos2d::Sprite* _conejo;
	cocos2d::Vector<cocos2d::Sprite*> _bombas;
	void inicializarToque();	
	void agregarBombar(float dt);
	void inicializarFisica(cocos2d::Sprite* sprite);
	void moverJugador(cocos2d::Touch* toque, cocos2d::Event* event);
};

#endif // __HELLOWORLD_SCENE_H__
