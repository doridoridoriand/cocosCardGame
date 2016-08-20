#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

//変数宣言
// 1種類あたりのカードの枚数
#define CARD_NUM 13
// カードの種類の総数
#define CARD_TYPE_NUM 4

// 1番目のカードの位置
#define CARD_1_POS_X 200
#define CARD_1_POS_Y 320

// カード間の距離
#define CARD_DISTANCE_X 140
#define CARD_DISTANCE_Y 200

// 表示しているカードのZオーダー
#define ZORDER_SHOW_CARD 1

USING_NS_CC;

bool CardSprite::init() {
  if (!Sprite::init()) {
    return false;
  }
  return true;
}

void CardSprite::onEnter() {
  Sprite::onEnter();

  //画像の表示
  setTexture(getFileName(_card.type));

  //マークと数字の表示
  showNumber();

  //カード位置とタグを指定
  float posX = CARD_1_POS_X + CARD_DISTANCE_X * _posIndex.x;
  float posY = CARD_1_POS_Y + CARD_DISTANCE_Y * _posIndex.y;
  setPosition(posX, posY);
  setTag(_posIndex.x + _posIndex.y + 5 + 1);
}

void HelloWorld::initGame() {
  // カードを初期化
  initCards();

  // カードを表示
  showInitCards();
}

std::string CardSprite::getFileName(CardType cardType) {
  // ファイル名の取得
  std::string filename;
  switch(cardType) {
    case Clubs:    filename = "card_clubs.png";    break;
    case Diamonds: filename = "card_diamonds.png"; break;
    case Hearts:   filename = "card_hearts.png";   break;
    default:       filename = "card_spades.png";   break;
  }
  return filename;
}

void CardSprite::showNumber() {
  //表示する数字の取得
  std::string numberString;
  switch(_card.number) {
    case1:   numberString = "A";                                     break;
    case11:  numberString = "J";                                     break;
    case12:  numberString = "Q";                                     break;
    case13:  numberString = "K";                                     break;
    default: numberString = StringUtils::format("%d", _card.number); break;

  }

  //表示する文字色の取得
  Color4B textColor;
  switch(_card.type) {
    case Clubs:
    case Spades:
      textColor = Color4B::BLACK;
      break;

    default:
      textColor = Color4B::RED;
      break;
  }

  //ラベルの生成
  auto number = Label::createWithSystemFont(numberString, "Arial", 96);
  number->setPosition(Point(getContentSize() / 2));
  number->setTextColor(textColor);
  addChild(number);
}

void HelloWorld::showInitCards() {
  for (int tag = 1; tag <= 10; tag++) {
    auto card = getChildByTag(tag);
    if (card) {
      card->removeFromParent();
    }
  }

  // 5列*2行分のループ
  for (int x = 0; x < 5; x++) {
    for (int y = 0; y < 2; y++) {
      PosIndex posIndex;
      posIndex.x = x;
      posIndex.y = y;

      // カードの生成
      createCard(posIndex);
    }
  }
}

void HelloWorld::createCard(PosIndex posIndex) {
  // 新しいカードを作成
  auto card = CardSprite::create();
  card->setCard(getCard());
  card->setPosIndex(posIndex);
  addChild(card, ZORDER_SHOW_CARD);
}

void HelloWorld::initCards() {
  // ゲームカードのクリア
  _cards.clear();

  // 4種類*13枚分のループ
  for (int type = 0; type < CARD_TYPE_NUM; type++) {
    for (int number = 1; number <= CARD_NUM; number++) {
      // カード情報の作成
      Card card;
      card.number = number;
      card.type = (CardType)type;

      // カード情報をカード配列に追加
      _cards.push_back(card);
    }
  }
}

Card HelloWorld::getCard() {
  std::random_device rd;
  std::mt19937 rand = std::mt19937(rd());

  // インデックスをランダムに取得する
  int index = std::uniform_int_distribution<int>(0, (int)_cards.size() - 1)(rand);

  // カードの数値を取得する
  auto card = _cards[index];

  // 一時的に格納しているだけなので、要素を削除
  _cards.erase(_cards.begin() + index);

  return card;
}

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
  if (!Layer::init()) {
    return false;
  }
  initGame();

  return true;
}
