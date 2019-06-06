#include "ShopLayer.h"
#include<cmath>
Hero* hero;
ShopLayer* ShopLayer::createLayer(Hero* hero1)
{
	hero = hero1;
	return ShopLayer::create();
}

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

		Label* yidong = Label::createWithSystemFont("Move", "Arial", 20);
		yidong ->setPosition(25 * winSize.width / 100, 105 * winSize.height / 100);
		layer->addChild(yidong);

		MenuItem* shoes = MenuItemImage::create("shensuzhixve.jpg", "shensuzhixve.jpg",CC_CALLBACK_1(ShopLayer::shopMenuCallback,this));
		shoes->setScale(0.2f); shoes->setTag(1); shoes->setPosition(35*winSize.width / 100, 105 * winSize.height / 100);

		Label* attack = Label::createWithSystemFont("Attack", "Arial", 20);
		attack->setPosition(25 * winSize.width / 100, 95 * winSize.height / 100);
		layer->addChild(attack);

		MenuItem* attack1 = MenuItemImage::create("tiejian.jpg", "tiejian.jpg", CC_CALLBACK_1(ShopLayer::shopMenuCallback, this));
		attack1->setScale(0.2f); attack1->setTag(2); attack1->setPosition(35*winSize.width / 100, 95 * winSize.height / 100);

		MenuItem* attack2 = MenuItemImage::create("bishou.jpg", "bishou.jpg", CC_CALLBACK_1(ShopLayer::shopMenuCallback, this));
		attack2->setScale(0.2f); attack2->setTag(3); attack2->setPosition(45*winSize.width / 100, 95 * winSize.height / 100);

		MenuItem* attack3 = MenuItemImage::create("bojiquantao.jpg", "bojiquantao.jpg", CC_CALLBACK_1(ShopLayer::shopMenuCallback, this));
		attack3->setScale(0.2f); attack3->setTag(4); attack3->setPosition(55 * winSize.width / 100, 95 * winSize.height / 100);
		
		MenuItem* attack4 = MenuItemImage::create("fengbaojujian.jpg", "fengbaojujian.jpg", CC_CALLBACK_1(ShopLayer::shopMenuCallback, this));
		attack4->setScale(0.2f); attack4->setTag(5); attack4->setPosition(35 * winSize.width / 100, 85 * winSize.height / 100);

		MenuItem* attack5 = MenuItemImage::create("kuangbaoshuangren.jpg", "kuangbaoshuangren.jpg", CC_CALLBACK_1(ShopLayer::shopMenuCallback, this));
		attack5->setScale(0.2f); attack5->setTag(6); attack5->setPosition(45 * winSize.width / 100, 85 * winSize.height / 100);

		MenuItem* attack6 = MenuItemImage::create("sujizhiqiang.jpg", "sujizhiqiang.jpg", CC_CALLBACK_1(ShopLayer::shopMenuCallback, this));
		attack6->setScale(0.2f); attack6->setTag(7); attack6->setPosition(55 * winSize.width / 100, 85 * winSize.height / 100);

		MenuItem* attack7 = MenuItemImage::create("anyingzhanfu.jpg", "anyingzhanfu.jpg", CC_CALLBACK_1(ShopLayer::shopMenuCallback, this));
		attack7->setScale(0.2f); attack7->setTag(8); attack7->setPosition(35 * winSize.width / 100, 75 * winSize.height / 100);

		MenuItem* attack8 = MenuItemImage::create("poxiao.jpg", "poxiao.jpg", CC_CALLBACK_1(ShopLayer::shopMenuCallback, this));
		attack8->setScale(0.2f); attack8->setTag(9); attack8->setPosition(45 * winSize.width / 100, 75 * winSize.height / 100);

		MenuItem* attack9 = MenuItemImage::create("wujinzhanren.jpg", "wujizhanren.jpg", CC_CALLBACK_1(ShopLayer::shopMenuCallback, this));
		attack9->setScale(0.2f); attack9->setTag(10); attack9->setPosition(55 * winSize.width / 100, 75 * winSize.height / 100);

		Label* spell = Label::createWithSystemFont("Spell", "Arial", 20);
		spell->setPosition(25 * winSize.width / 100, 65 * winSize.height / 100);
		layer->addChild(spell);

		MenuItem* spell1 = MenuItemImage::create("zhoushudianji.jpg", "zhoushudianji.jpg", CC_CALLBACK_1(ShopLayer::shopMenuCallback, this));
		spell1->setScale(0.2f); spell1->setTag(11); spell1->setPosition(35 * winSize.width / 100,65 * winSize.height / 100);

		MenuItem* spell2 = MenuItemImage::create("lanbaoshi.jpg", "lanbaoshi.jpg", CC_CALLBACK_1(ShopLayer::shopMenuCallback, this));
		spell2->setScale(0.2f); spell2->setTag(12); spell2->setPosition(45 * winSize.width / 100, 65 * winSize.height / 100);

		MenuItem* spell3 = MenuItemImage::create("yuansuzhang.jpg", "yuansuzhang.jpg", CC_CALLBACK_1(ShopLayer::shopMenuCallback, this));
		spell3->setScale(0.2f); spell3->setTag(13); spell3->setPosition(55 * winSize.width / 100, 65 * winSize.height / 100);

		MenuItem* spell4 = MenuItemImage::create("guanghuizhijian.jpg", "guanghuizhijian.jpg", CC_CALLBACK_1(ShopLayer::shopMenuCallback, this));
		spell4->setScale(0.2f); spell4->setTag(14); spell4->setPosition(35 * winSize.width / 100, 55 * winSize.height / 100);

		MenuItem* spell5 = MenuItemImage::create("jinhuashuijing.jpg", "jinhuashuijing.jpg", CC_CALLBACK_1(ShopLayer::shopMenuCallback, this));
		spell5->setScale(0.2f); spell5->setTag(15); spell5->setPosition(45 * winSize.width / 100, 55 * winSize.height / 100);

		MenuItem* spell6 = MenuItemImage::create("posuishengbei.jpg", "posuishengbei.jpg", CC_CALLBACK_1(ShopLayer::shopMenuCallback, this));
		spell6->setScale(0.2f); spell6->setTag(16); spell6->setPosition(55 * winSize.width / 100, 55 * winSize.height / 100);

		MenuItem* spell7 = MenuItemImage::create("xianzhezhishu.jpg", "xianzhezhishu.jpg", CC_CALLBACK_1(ShopLayer::shopMenuCallback, this));
		spell7->setScale(0.2f); spell7->setTag(17); spell7->setPosition(35 * winSize.width / 100, 45 * winSize.height / 100);

		MenuItem* spell8 = MenuItemImage::create("shengbei.jpg", "shengbei.jpg", CC_CALLBACK_1(ShopLayer::shopMenuCallback, this));
		spell8->setScale(0.2f); spell8->setTag(18); spell8->setPosition(45 * winSize.width / 100, 45 * winSize.height / 100);

		MenuItem* spell9 = MenuItemImage::create("boxuezhezhinu.jpg", "boxuezhezhinu.jpg", CC_CALLBACK_1(ShopLayer::shopMenuCallback, this));
		spell9->setScale(0.2f); spell9->setTag(19); spell9->setPosition(55 * winSize.width / 100, 45 * winSize.height / 100);

		Label* defence = Label::createWithSystemFont("Defence", "Arial", 20);
		defence->setPosition(25 * winSize.width / 100, 35 * winSize.height / 100);
		layer->addChild(defence);
		
		MenuItem* defence1 = MenuItemImage::create("hongmanao.jpg", "hongmanao.jpg", CC_CALLBACK_1(ShopLayer::shopMenuCallback, this));
		defence1->setScale(0.2f); defence1->setTag(20); defence1->setPosition(35 * winSize.width / 100, 35 * winSize.height / 100);

		MenuItem* defence2 = MenuItemImage::create("bujia.jpg", "bujia.jpg", CC_CALLBACK_1(ShopLayer::shopMenuCallback, this));
		defence2->setScale(0.2f); defence2->setTag(21); defence2->setPosition(45 * winSize.width / 100, 35 * winSize.height / 100);

		MenuItem* defence3 = MenuItemImage::create("kangmopifeng.jpg", "kangmopifeng.jpg", CC_CALLBACK_1(ShopLayer::shopMenuCallback, this));
		defence3->setScale(0.2f); defence3->setTag(22); defence3->setPosition(55 * winSize.width / 100, 35 * winSize.height / 100);

		MenuItem* defence4 = MenuItemImage::create("liliangyaodai.jpg", "liliangyaodai.jpg", CC_CALLBACK_1(ShopLayer::shopMenuCallback, this));
		defence4->setScale(0.2f); defence4->setTag(23); defence4->setPosition(35 * winSize.width / 100, 25 * winSize.height / 100);

		MenuItem* defence5 = MenuItemImage::create("shenyindoupeng.jpg", "shenyindoupeng.jpg", CC_CALLBACK_1(ShopLayer::shopMenuCallback, this));
		defence5->setScale(0.2f); defence5->setTag(24); defence5->setPosition(45 * winSize.width / 100, 25 * winSize.height / 100);

		MenuItem* defence6 = MenuItemImage::create("xveshanyuandun.jpg", "xveshanyuandun.jpg", CC_CALLBACK_1(ShopLayer::shopMenuCallback, this));
		defence6->setScale(0.2f); defence6->setTag(25); defence6->setPosition(55 * winSize.width / 100, 25 * winSize.height / 100);

		MenuItem* defence7 = MenuItemImage::create("bazhezhongzhuang.jpg", "bazhezhongzhuang.jpg", CC_CALLBACK_1(ShopLayer::shopMenuCallback, this));
		defence7->setScale(0.2f); defence7->setTag(26); defence7->setPosition(35 * winSize.width / 100, 15 * winSize.height / 100);

		MenuItem* defence8 = MenuItemImage::create("buxiangzhengzhao.jpg", "buxiangzhengzhao.jpg", CC_CALLBACK_1(ShopLayer::shopMenuCallback, this));
		defence8->setScale(0.2f); defence8->setTag(27); defence8->setPosition(45 * winSize.width / 100, 15 * winSize.height / 100);

		MenuItem* defence9 = MenuItemImage::create("monvdoupeng.jpg", "monvdoupeng.jpg", CC_CALLBACK_1(ShopLayer::shopMenuCallback, this));
		defence9->setScale(0.2f); defence9->setTag(28); defence9->setPosition(55 * winSize.width / 100, 15 * winSize.height / 100);

		Label* support = Label::createWithSystemFont("Support", "Arial", 20);
		support->setPosition(25 * winSize.width / 100, 5 * winSize.height / 100);
		layer->addChild(support);

		MenuItem* support1 = MenuItemImage::create("xveshibaoshi.jpg", "xveshibaoshi.jpg", CC_CALLBACK_1(ShopLayer::shopMenuCallback, this));
		support1->setScale(0.2f); support1->setTag(29); support1->setPosition(35 * winSize.width / 100, 5 * winSize.height / 100);

		MenuItem* support2 = MenuItemImage::create("fengmingzhihuan.jpg", "fengmingzhihuan.jpg", CC_CALLBACK_1(ShopLayer::shopMenuCallback, this));
		support2->setScale(0.2f); support2->setTag(30); support2->setPosition(45 * winSize.width / 100, 5 * winSize.height / 100);

		MenuItem* support3 = MenuItemImage::create("jiying.jpg", "jiying.jpg", CC_CALLBACK_1(ShopLayer::shopMenuCallback, this));
		support3->setScale(0.2f); support3->setTag(31); support3->setPosition(55 * winSize.width / 100, 5 * winSize.height / 100);

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
	int price;
	this->removeChildByTag(100);
	this->removeChildByTag(200);
	this->removeChildByName("menu");
	Size winSize = Director::getInstance()->getWinSize();
	auto itemSelect = (MenuItem*)psender;
	int num = itemSelect->getTag(); 
	Label* contents;
	switch (num)
	{
	case 1:
		contents= Label::createWithSystemFont("speed+30   $250", "Arial", 16);
		price = 250;
		break;
	case 2:
	    contents = Label::createWithSystemFont("Attack+20  $250", "Arial", 16);
		price = 250;
		break;
	case 3:
		contents = Label::createWithSystemFont("AttackSpeed+10  $290", "Arial", 16);
		price = 290;
		break;
	case 4:
		contents = Label::createWithSystemFont("CriticRate+10  $320", "Arial", 16);
		price = 320;
		break;
	case 5:
		contents = Label::createWithSystemFont("Attack+80  $910", "Arial", 16);
		price = 910;
		break;
	case 6:
		contents = Label::createWithSystemFont("AttackSpeed+25  $890", "Arial", 16);
		price = 890;
		break;
	case 7:
		contents = Label::createWithSystemFont("CriticRate+25  $890", "Arial", 16);
		price = 890;
		break;
	case 8:
		contents = Label::createWithSystemFont("Attack+160  $2150", "Arial", 16);
		price = 2150;
		break;
	case 9:
		contents = Label::createWithSystemFont("AttackSpeed+40  $2000", "Arial", 16);
		price = 2000;
		break;
	case 10:
		contents = Label::createWithSystemFont("CriticRate+50  $2160", "Arial", 16);
		price = 2160;
		break;
	case 11:
		contents = Label::createWithSystemFont("SkillEnhance+5  $300", "Arial", 16);
		price = 300;
		break;
	case 12:
		contents = Label::createWithSystemFont("Mp+300  $220", "Arial", 16);
		price = 220;
		break;
	case 13:
		contents = Label::createWithSystemFont("MpRecover+5  $120", "Arial", 16);
		price = 120;
		break;
	case 14:
		contents = Label::createWithSystemFont("SkillEnhance+15  $820", "Arial", 16);
		price = 820;
		break;
	case 15:
		contents = Label::createWithSystemFont("MP+400  $890", "Arial", 16);
		price = 890;
		break;
	case 16:
		contents = Label::createWithSystemFont("MPRecover+15  $700", "Arial", 16);
		price = 700;
		break;
	case 17:
		contents = Label::createWithSystemFont("SkillEnhance+50  $2100", "Arial", 16);
		price = 2100;
		break;
	case 18:
		contents = Label::createWithSystemFont("MP+1000  $1980", "Arial", 16);
		price = 1980;
		break;
	case 19:
		contents = Label::createWithSystemFont("MPRecover+40  $1980", "Arial", 16);
		price = 1980;
		break;
	case 20:
		contents = Label::createWithSystemFont("HP+300  $300", "Arial", 16);
		price = 300;
		break;
	case 21:
		contents = Label::createWithSystemFont("Defence+90  $220", "Arial", 16);
		price = 220;
		break;
	case 22:
		contents = Label::createWithSystemFont("Resistance+90  $220", "Arial", 16);
		price = 220;
		break;
	case 23:
		contents = Label::createWithSystemFont("HP+1000  $900", "Arial", 16);
		price = 900;
		break;
	case 24:
		contents = Label::createWithSystemFont("Defence+210  $730", "Arial", 16);
		price = 730;
		break;
	case 25:
		contents = Label::createWithSystemFont("Resistance+150  $890", "Arial", 16);
		price = 890;
		break;
	case 26:
		contents = Label::createWithSystemFont("HP+2000  $2180", "Arial", 16);
		price = 2180;
		break;
	case 27:
		contents = Label::createWithSystemFont("Defence+400  $1980", "Arial", 16);
		price = 1980;
		break;
	case 28:
		contents = Label::createWithSystemFont("Resistance+320  $1980", "Arial", 16);
		price = 1980;
		break;
	case 29:
		contents = Label::createWithSystemFont("Get $5/3s  $300", "Arial", 16);
		price = 300;
		break;
	case 30:
		contents = Label::createWithSystemFont("AllyAttackSpeed+20  $890", "Arial", 16);
		price = 890;
		break;
	case 31:
		contents = Label::createWithSystemFont("AllyAttackSpeed+40  $1800", "Arial", 16);
		price = 1800;
		break;
	}

	contents->setTag(100);
	contents->setPosition(70 * winSize.width / 100, 60 * winSize.height / 100);
	this->addChild(contents);
	Label* buy = Label::createWithSystemFont("Buy", "Arial", 20);
	auto btn = MenuItemLabel::create(buy, CC_CALLBACK_1(ShopLayer::buyCallback, this,price));
	btn->setTag(num);
	btn->setPosition(75 * winSize.width / 100, 40 * winSize.height / 100);
	Menu* menu = Menu::create(btn, NULL);
	menu->setName("menu");
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

}
	void ShopLayer::buyCallback(Ref* psender,int price)
	{
		this->removeChildByTag(200);
		Size winSize = Director::getInstance()->getWinSize();
		if (hero->Money < price)
		{
			Label* label1 = Label::createWithSystemFont("More Money...", "Arial", 20);
			label1->setPosition(75 * winSize.width / 100, 30 * winSize.height / 100+10);
			label1->setTag(200);
			this->addChild(label1);
			return;
		}
			
		else
			hero->Money -= price;
		auto itemSelect = (MenuItem*)psender;
		int num = itemSelect->getTag();
		switch (num)
		{
		case 1:
			hero->speed += 2;
			hero->Weapon[1] = 1;
			break;
		case 2:
			hero->Attack += 20;
			hero->Weapon[2] = 1;
			break;
		case 3:
			hero->Attack_Speed += 10;
			hero->Weapon[3] = 1;
			break;
		case 4:
			hero->Critical_Rate += 10;
			hero->Weapon[4] = 1;
			break;
		case 5:
			hero->Attack += 80;
			hero->Weapon[5] = 1;
			break;
		case 6:
			hero->Attack_Speed += 25;
			hero->Weapon[6] = 1;
			break;
		case 7:
			hero->Critical_Rate += 25;
			hero->Weapon[7] = 1;
			break;
		case 8:
			hero->Attack += 160;
			hero->Weapon[8] = 1;
			break;
		case 9:
			hero->Attack_Speed += 40;
			hero->Weapon[9] = 1;
			break;
		case 10:
			hero->Critical_Rate += 50;
			hero->Weapon[10] = 1;
			break;
		case 11:
			hero->Skill_Enhance += 5;
			hero->Weapon[11] = 1;
			break;
		case 12:
			hero->MaxMP += 300;
			hero->Weapon[12] = 1;
			break;
		case 13:
			hero->MP_Recover += 5;
			hero->Weapon[13] = 1;
			break;
		case 14:
			hero->Skill_Enhance += 15;
			hero->Weapon[14] = 1;
			break;
		case 15:
			hero->MaxMP += 400;
			hero->Weapon[15] = 1;
			break;
		case 16:
			hero->MP_Recover += 15;
			hero->Weapon[16] = 1;
			break;
		case 17:
			hero->Skill_Enhance += 50;
			hero->Weapon[17] = 1;
			break;
		case 18:
			hero->MaxMP + 1000;
			hero->Weapon[18] = 1;
			break;
		case 19:
			hero->MP_Recover += 40;
			hero->Weapon[19] = 1;
			break;
		case 20:
			hero->MaxHP += 300;
			hero->Weapon[20] = 1;
			break;
		case 21:
			hero->Defense += 90;
			hero->Weapon[21] = 1;
			break;
		case 22:
			hero->Resistance += 90;
			hero->Weapon[22] = 1;
			break;
		case 23:
			hero->MaxHP += 1000;
			hero->Weapon[23] = 1;
			break;
		case 24:
			hero->Defense += 210;
			hero->Weapon[24] = 1;
			break;
		case 25:
			hero->Resistance += 150;
			hero->Weapon[25] = 1;
			break;
		case 26:
			hero->MaxHP += 2000;
			hero->Weapon[26] = 1;
			break;
		case 27:
			hero->Defense += 400;
			hero->Weapon[27] = 1;
			break;
		case 28:
			hero->Resistance += 320; 
			hero->Weapon[28] = 1;
			break;
		case 29:

			break;
		case 30:

			break;
		case 31:

			break;
		}
	}

