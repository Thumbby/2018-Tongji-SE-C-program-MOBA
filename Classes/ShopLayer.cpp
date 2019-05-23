#include "ShopLayer.h"
#include<cmath>
bool ShopLayer::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!Layer::init());
		Size winSize = Director::getInstance()->getWinSize();
		ScrollView * scrollView = ScrollView::create(Size(winSize.width, 35*winSize.height/100));
		scrollView->setBounceable(true);								   
        scrollView->ignoreAnchorPointForPosition(false);
	    scrollView->setPosition(Point(winSize.width/2, winSize.height/2));
	    scrollView->setDirection(ScrollView::Direction::VERTICAL);
		
		Layer * layer = Layer::create();
		auto layerSize = layer->getContentSize();
		layer->setPosition(0, 0);
		scrollView->setBounceable(true);

		Label* yidong = Label::createWithSystemFont("Move", "Arial", 30);
		yidong ->setPosition(25 * winSize.width / 100, 105 * winSize.height / 100);
		layer->addChild(yidong);

		MenuItem* shoes = MenuItemImage::create("shensuzhixve.jpg", "shensuzhixve.jpg",CC_CALLBACK_1(ShopLayer::shopMenuCallback,this));
		shoes->setScale(5); shoes->setTag(1); shoes->setPosition(35*winSize.width / 100, 105 * winSize.height / 100);

		Label* attack = Label::createWithSystemFont("Attack", "Arial", 30);
		attack->setPosition(25 * winSize.width / 100, 95 * winSize.height / 100);
		layer->addChild(attack);

		MenuItem* attack1 = MenuItemImage::create("tiejian.jpg", "tiejian.jpg", CC_CALLBACK_1(ShopLayer::shopMenuCallback, this));
		attack1->setScale(5); attack1->setTag(2); attack1->setPosition(35*winSize.width / 100, 95 * winSize.height / 100);

		MenuItem* attack2 = MenuItemImage::create("bishou.jpg", "bishou.jpg", CC_CALLBACK_1(ShopLayer::shopMenuCallback, this));
		attack2->setScale(5); attack2->setTag(3); attack2->setPosition(45*winSize.width / 100, 95 * winSize.height / 100);

		MenuItem* attack3 = MenuItemImage::create("bojiquantao.jpg", "bojiquantao.jpg", CC_CALLBACK_1(ShopLayer::shopMenuCallback, this));
		attack3->setScale(5); attack3->setTag(4); attack3->setPosition(55 * winSize.width / 100, 95 * winSize.height / 100);
		
		MenuItem* attack4 = MenuItemImage::create("fengbaojujian.jpg", "fengbaojujian.jpg", CC_CALLBACK_1(ShopLayer::shopMenuCallback, this));
		attack4->setScale(5); attack4->setTag(5); attack4->setPosition(35 * winSize.width / 100, 85 * winSize.height / 100);

		MenuItem* attack5 = MenuItemImage::create("kuangbaoshuangren.jpg", "kuangbaoshuangren.jpg", CC_CALLBACK_1(ShopLayer::shopMenuCallback, this));
		attack5->setScale(5); attack5->setTag(6); attack5->setPosition(45 * winSize.width / 100, 85 * winSize.height / 100);

		MenuItem* attack6 = MenuItemImage::create("sujizhiqiang.jpg", "sujizhiqiang.jpg", CC_CALLBACK_1(ShopLayer::shopMenuCallback, this));
		attack6->setScale(5); attack6->setTag(7); attack6->setPosition(55 * winSize.width / 100, 85 * winSize.height / 100);

		MenuItem* attack7 = MenuItemImage::create("anyingzhanfu.jpg", "anyingzhanfu.jpg", CC_CALLBACK_1(ShopLayer::shopMenuCallback, this));
		attack7->setScale(5); attack7->setTag(8); attack7->setPosition(35 * winSize.width / 100, 75 * winSize.height / 100);

		MenuItem* attack8 = MenuItemImage::create("poxiao.jpg", "poxiao.jpg", CC_CALLBACK_1(ShopLayer::shopMenuCallback, this));
		attack8->setScale(5); attack8->setTag(9); attack8->setPosition(45 * winSize.width / 100, 75 * winSize.height / 100);

		MenuItem* attack9 = MenuItemImage::create("wujinzhanren.jpg", "wujizhanren.jpg", CC_CALLBACK_1(ShopLayer::shopMenuCallback, this));
		attack9->setScale(5); attack9->setTag(10); attack9->setPosition(55 * winSize.width / 100, 75 * winSize.height / 100);

		Label* spell = Label::createWithSystemFont("Spell", "Arial", 30);
		spell->setPosition(25 * winSize.width / 100, 65 * winSize.height / 100);
		layer->addChild(spell);

		MenuItem* spell1 = MenuItemImage::create("zhoushudianji.jpg", "zhoushudianji.jpg", CC_CALLBACK_1(ShopLayer::shopMenuCallback, this));
		spell1->setScale(5); spell1->setTag(11); spell1->setPosition(35 * winSize.width / 100,65 * winSize.height / 100);

		MenuItem* spell2 = MenuItemImage::create("lanbaoshi.jpg", "lanbaoshi.jpg", CC_CALLBACK_1(ShopLayer::shopMenuCallback, this));
		spell2->setScale(5); spell2->setTag(12); spell2->setPosition(45 * winSize.width / 100, 65 * winSize.height / 100);

		MenuItem* spell3 = MenuItemImage::create("yuansuzhang.jpg", "yuansuzhang.jpg", CC_CALLBACK_1(ShopLayer::shopMenuCallback, this));
		spell3->setScale(5); spell3->setTag(13); spell3->setPosition(55 * winSize.width / 100, 65 * winSize.height / 100);

		MenuItem* spell4 = MenuItemImage::create("guanghuizhijian.jpg", "guanghuizhijian.jpg", CC_CALLBACK_1(ShopLayer::shopMenuCallback, this));
		spell4->setScale(5); spell4->setTag(14); spell4->setPosition(35 * winSize.width / 100, 55 * winSize.height / 100);

		MenuItem* spell5 = MenuItemImage::create("jinhuashuijing.jpg", "jinhuashuijing.jpg", CC_CALLBACK_1(ShopLayer::shopMenuCallback, this));
		spell5->setScale(5); spell5->setTag(15); spell5->setPosition(45 * winSize.width / 100, 55 * winSize.height / 100);

		MenuItem* spell6 = MenuItemImage::create("posuishengbei.jpg", "posuishengbei.jpg", CC_CALLBACK_1(ShopLayer::shopMenuCallback, this));
		spell6->setScale(5); spell6->setTag(16); spell6->setPosition(55 * winSize.width / 100, 55 * winSize.height / 100);

		MenuItem* spell7 = MenuItemImage::create("xianzhezhishu.jpg", "xianzhezhishu.jpg", CC_CALLBACK_1(ShopLayer::shopMenuCallback, this));
		spell7->setScale(5); spell7->setTag(17); spell7->setPosition(35 * winSize.width / 100, 45 * winSize.height / 100);

		MenuItem* spell8 = MenuItemImage::create("shengbei.jpg", "shengbei.jpg", CC_CALLBACK_1(ShopLayer::shopMenuCallback, this));
		spell8->setScale(5); spell8->setTag(18); spell8->setPosition(45 * winSize.width / 100, 45 * winSize.height / 100);

		MenuItem* spell9 = MenuItemImage::create("boxuezhezhinu.jpg", "boxuezhezhinu.jpg", CC_CALLBACK_1(ShopLayer::shopMenuCallback, this));
		spell9->setScale(5); spell9->setTag(19); spell9->setPosition(55 * winSize.width / 100, 45 * winSize.height / 100);

		Label* defence = Label::createWithSystemFont("Defence", "Arial", 30);
		defence->setPosition(25 * winSize.width / 100, 35 * winSize.height / 100);
		layer->addChild(defence);
		
		MenuItem* defence1 = MenuItemImage::create("hongmanao.jpg", "hongmanao.jpg", CC_CALLBACK_1(ShopLayer::shopMenuCallback, this));
		defence1->setScale(5); defence1->setTag(20); defence1->setPosition(35 * winSize.width / 100, 35 * winSize.height / 100);

		MenuItem* defence2 = MenuItemImage::create("bujia.jpg", "bujia.jpg", CC_CALLBACK_1(ShopLayer::shopMenuCallback, this));
		defence2->setScale(5); defence2->setTag(21); defence2->setPosition(45 * winSize.width / 100, 35 * winSize.height / 100);

		MenuItem* defence3 = MenuItemImage::create("kangmopifeng.jpg", "kangmopifeng.jpg", CC_CALLBACK_1(ShopLayer::shopMenuCallback, this));
		defence3->setScale(5); defence3->setTag(22); defence3->setPosition(55 * winSize.width / 100, 35 * winSize.height / 100);

		MenuItem* defence4 = MenuItemImage::create("liliangyaodai.jpg", "liliangyaodai.jpg", CC_CALLBACK_1(ShopLayer::shopMenuCallback, this));
		defence4->setScale(5); defence4->setTag(23); defence4->setPosition(35 * winSize.width / 100, 25 * winSize.height / 100);

		MenuItem* defence5 = MenuItemImage::create("shenyindoupeng.jpg", "shenyindoupeng.jpg", CC_CALLBACK_1(ShopLayer::shopMenuCallback, this));
		defence5->setScale(5); defence5->setTag(24); defence5->setPosition(45 * winSize.width / 100, 25 * winSize.height / 100);

		MenuItem* defence6 = MenuItemImage::create("xveshanyuandun.jpg", "xveshanyuandun.jpg", CC_CALLBACK_1(ShopLayer::shopMenuCallback, this));
		defence6->setScale(5); defence6->setTag(25); defence6->setPosition(55 * winSize.width / 100, 25 * winSize.height / 100);

		MenuItem* defence7 = MenuItemImage::create("bazhezhongzhuang.jpg", "bazhezhongzhuang.jpg", CC_CALLBACK_1(ShopLayer::shopMenuCallback, this));
		defence7->setScale(5); defence7->setTag(26); defence7->setPosition(35 * winSize.width / 100, 15 * winSize.height / 100);

		MenuItem* defence8 = MenuItemImage::create("buxiangzhengzhao.jpg", "buxiangzhengzhao.jpg", CC_CALLBACK_1(ShopLayer::shopMenuCallback, this));
		defence8->setScale(5); defence8->setTag(27); defence8->setPosition(45 * winSize.width / 100, 15 * winSize.height / 100);

		MenuItem* defence9 = MenuItemImage::create("monvdoupeng.jpg", "monvdoupeng.jpg", CC_CALLBACK_1(ShopLayer::shopMenuCallback, this));
		defence9->setScale(5); defence9->setTag(28); defence9->setPosition(55 * winSize.width / 100, 15 * winSize.height / 100);

		Label* support = Label::createWithSystemFont("Support", "Arial", 30);
		support->setPosition(25 * winSize.width / 100, 5 * winSize.height / 100);
		layer->addChild(support);

		MenuItem* support1 = MenuItemImage::create("xveshibaoshi.jpg", "xveshibaoshi.jpg", CC_CALLBACK_1(ShopLayer::shopMenuCallback, this));
		support1->setScale(5); support1->setTag(29); support1->setPosition(35 * winSize.width / 100, 5 * winSize.height / 100);

		MenuItem* support2 = MenuItemImage::create("fengmingzhihuan.jpg", "fengmingzhihuan.jpg", CC_CALLBACK_1(ShopLayer::shopMenuCallback, this));
		support2->setScale(5); support2->setTag(30); support2->setPosition(45 * winSize.width / 100, 5 * winSize.height / 100);

		MenuItem* support3 = MenuItemImage::create("jiying.jpg", "jiying.jpg", CC_CALLBACK_1(ShopLayer::shopMenuCallback, this));
		support3->setScale(5); support3->setTag(31); support3->setPosition(55 * winSize.width / 100, 5 * winSize.height / 100);

		Menu* shop = Menu::create(
			shoes, 
			attack1, attack2,attack3,attack4,attack5,attack6,attack7,attack8,attack9, 
			spell1,spell2,spell3,spell4,spell5,spell6,spell7,spell8,spell9,
			defence1,defence2,defence3,defence4,defence5,defence6,defence7,defence8,defence9,
			support1,support2,support3,
			NULL
		);
		shop->setPosition(Point::ZERO);
		layer->addChild(shop);

		scrollView->setContainer(layer);
		scrollView->setContentSize(Size(winSize.width/2, 110*winSize.height/100));
		scrollView->setContentOffset(Point(0, 0));
		this->addChild(scrollView);
		mscrollView = scrollView;
		bRet = true;
	} while (0);
	
	return bRet;
}
void ShopLayer::shopMenuCallback(Ref* psender)
{
	this->removeChildByTag(100);
	this->removeChildByName("menu");
	Size winSize = Director::getInstance()->getWinSize();
	auto itemSelect = (MenuItem*)psender;
	int num = itemSelect->getTag(); 
	Label* contents;
	switch (num)
	{
	case 1:
		contents= Label::createWithSystemFont("speed+30   $250", "Arial", 50);
		break;
	case 2:
	    contents = Label::createWithSystemFont("Attack+20  $250", "Arial", 50);
		break;
	case 3:
		contents = Label::createWithSystemFont("AttackSpeed+10  $290", "Arial", 50);
		break;
	case 4:
		contents = Label::createWithSystemFont("CriticRate+10  $320", "Arial", 50);
		break;
	case 5:
		contents = Label::createWithSystemFont("Attack+80  $910", "Arial", 50);
		break;
	case 6:
		contents = Label::createWithSystemFont("AttackSpeed+25  $890", "Arial", 50);
		break;
	case 7:
		contents = Label::createWithSystemFont("CriticRate+25  $890", "Arial", 50);
		break;
	case 8:
		contents = Label::createWithSystemFont("Attack+160  $2150", "Arial", 50);
		break;
	case 9:
		contents = Label::createWithSystemFont("AttackSpeed+40  $2000", "Arial", 50);
		break;
	case 10:
		contents = Label::createWithSystemFont("CriticRate+50  $2160", "Arial", 50);
		break;
	case 11:
		contents = Label::createWithSystemFont("SkillEnhance+5  $300", "Arial", 50);
		break;
	case 12:
		contents = Label::createWithSystemFont("Mp+300  $220", "Arial", 50);
		break;
	case 13:
		contents = Label::createWithSystemFont("MpRecover+5  $120", "Arial", 50);
		break;
	case 14:
		contents = Label::createWithSystemFont("SkillEnhance+15  $820", "Arial", 50);
		break;
	case 15:
		contents = Label::createWithSystemFont("MP+400  $890", "Arial", 50);
		break;
	case 16:
		contents = Label::createWithSystemFont("MPRecover+15  $700", "Arial", 50);
		break;
	case 17:
		contents = Label::createWithSystemFont("SkillEnhance+50  $2100", "Arial", 50);
		break;
	case 18:
		contents = Label::createWithSystemFont("MP+1000  $1980", "Arial", 50);
		break;
	case 19:
		contents = Label::createWithSystemFont("MPRecover+40  $1980", "Arial", 50);
		break;
	case 20:
		contents = Label::createWithSystemFont("HP+300  $300", "Arial", 50);
		break;
	case 21:
		contents = Label::createWithSystemFont("Defence+90  $220", "Arial", 50);
		break;
	case 22:
		contents = Label::createWithSystemFont("Resistance+90  $220", "Arial", 50);
		break;
	case 23:
		contents = Label::createWithSystemFont("HP+1000  $900", "Arial", 50);
		break;
	case 24:
		contents = Label::createWithSystemFont("Defence+210  $730", "Arial", 50);
		break;
	case 25:
		contents = Label::createWithSystemFont("Resistance+150  $890", "Arial", 50);
		break;
	case 26:
		contents = Label::createWithSystemFont("HP+2000  $2180", "Arial", 50);
		break;
	case 27:
		contents = Label::createWithSystemFont("Defence+400  $1980", "Arial", 50);
		break;
	case 28:
		contents = Label::createWithSystemFont("Resistance+320  $1980", "Arial", 50);
		break;
	case 29:
		contents = Label::createWithSystemFont("Get $5/3s  $300", "Arial", 50);
		break;
	case 30:
		contents = Label::createWithSystemFont("AllyAttackSpeed+20  $890", "Arial", 50);
		break;
	case 31:
		contents = Label::createWithSystemFont("AllyAttackSpeed+40  $1800", "Arial", 50);
		break;
	}

	contents->setTag(100);
	contents->setPosition(75 * winSize.width / 100, 55 * winSize.height / 100);
	this->addChild(contents);
	Label* buy = Label::createWithSystemFont("Buy", "Arial", 50);
	auto btn = MenuItemLabel::create(buy, CC_CALLBACK_1(ShopLayer::buyCallback, this));
	btn->setTag(num);
	btn->setPosition(75 * winSize.width / 100, 40 * winSize.height / 100);
	Menu* menu = Menu::create(btn, NULL);
	menu->setName("menu");
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

}
	void ShopLayer::buyCallback(Ref* psender)
	{
		
		auto itemSelect = (MenuItem*)psender;
		int num = itemSelect->getTag();itemSelect->removeFromParent();
		switch (num)
		{
		case 1:

			break;
		case 2:

			break;
		case 3:

			break;
		case 4:

			break;
		case 5:

			break;
		case 6:

			break;
		case 7:

			break;
		case 8:

			break;
		case 9:

			break;
		case 10:

			break;
		case 11:

			break;
		case 12:

			break;
		case 13:

			break;
		case 14:

			break;
		case 15:

			break;
		case 16:

			break;
		case 17:

			break;
		case 18:

			break;
		case 19:

			break;
		case 20:

			break;
		case 21:

			break;
		case 22:

			break;
		case 23:

			break;
		case 24:

			break;
		case 25:

			break;
		case 26:

			break;
		case 27:

			break;
		case 28:

			break;
		case 29:

			break;
		case 30:

			break;
		case 31:

			break;
		}
	}
