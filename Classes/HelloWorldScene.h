#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include <random>

enum CardType {
  Clubs = 0,
  Diamonds,
  Hearts,
  Spades
};

struct Card {
  int number;
  CardType type;
};

struct PosIndex {
  int x;
  int y;
};


class HelloWorld : public cocos2d::Layer
{

protected:
  // カードの配列
  std::vector<Card> _cards;
  // カードの初期化
  void initCards();
  // _cards変数からカードを一枚ランダムに取得する関数
  Card getCard();

  // カードを作成
  void createCard(PosIndex posIndex);

  // ゲーム開始時にカードを10枚表示する
  void showInitCards();

  // ゲームを初期化する
  void initGame();

public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
