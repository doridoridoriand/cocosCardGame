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

class CardSprite : public cocos2d::Sprite {
  protected:
    // 表画像ファイル名取得
    std::string getFileName(CardType, CardType);
    // カードとマークの数字を表示
    void showNumber();

  public:
    // 初期化処理
    virtual bool init();

    // 表示前処理
    void onEnter() override;

    // create関数作成マクロ
    CREATE_FUNC(CardSprite);

    /*
     * CC_SYNTHESIZEマクロ
     * 変数の定義、ゲッター、セッターの定義と実装を行ってくれるCocosのマクロ
     * CC_SYNTHESIZE(変数の型・クラス, 変数名, 関数名(プレフィックスとなるget, setを除いた名前))
     */
    CC_SYNTHESIZE(Card, _card, Card); // カード情報
    CC_SYNTHESIZE(PosIndex, _posIndex, PosIndex); // 表示位置

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
