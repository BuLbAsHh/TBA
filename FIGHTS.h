#pragma once
#include "settings.h"

void PlayerUpdateInFight(Player& obj, std::string LeftSpriteFileNAME, std::string RightSpriteMOVEFileNAME, std::string LeftSpriteMoveFileNAME, std::string RightSpriteFileNAME, Stand& stands, float time) {
    if (obj.health > obj.maxhealth) {
        obj.health = obj.maxhealth;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        if (obj.attacking == true) {
            obj.texture.loadFromFile("sprites\\player\\player1rightAttacking.png");
        }
        else {
            obj.texture.loadFromFile(RightSpriteMOVEFileNAME);
        }
        obj.sprite.move(obj.speed * time, 0);
        obj.left = false;
    }
    else {
        if (obj.attacking == true && obj.left == false) {
            obj.texture.loadFromFile("sprites\\player\\player1rightAttacking.png");
        }
        else  if (obj.left == false) {
            obj.texture.loadFromFile(RightSpriteFileNAME);
        }

    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        obj.left = true;
        if (obj.attacking == true) {
            obj.texture.loadFromFile("sprites\\player\\player1leftAttacking.png");
        }
        else {
            obj.texture.loadFromFile(LeftSpriteMoveFileNAME);
        }

        obj.sprite.move(-obj.speed * time, 0);
    }
    else {
        if (obj.attacking == true && obj.left == true) {
            obj.texture.loadFromFile("sprites\\player\\player1leftAttacking.png");
        }
        else if (obj.left == true) {
            obj.texture.loadFromFile(LeftSpriteFileNAME);
        }

    }


}

void FightMapUpdate(Player& pl, sf::Sprite& background1, sf::Sprite& background2, float backgroundSpeed)
{

    // ���������� ���� � ����������� �� ������� ������ � �������� �������� ����


    // ���������, ����� �� ����� �� ������� ������ ������
    if (pl.sprite.getPosition().x + 44.f >= background1.getPosition().x + background1.getGlobalBounds().width / 2  && pl.left == false)
    {
        background2.setPosition(background1.getPosition().x + background1.getGlobalBounds().width - 1.f, 0);
    }
    if (pl.sprite.getPosition().x + 44.f >= background2.getPosition().x + background2.getGlobalBounds().width / 2  && pl.left == false)
    {
        background1.setPosition(background2.getPosition().x + background2.getGlobalBounds().width - 1.f, 0);
    }
    //��������� ����� �����
    
    if (pl.sprite.getPosition().x <= background1.getPosition().x + background1.getGlobalBounds().width / 2 && pl.left == true)
    {
        background2.setPosition(background1.getPosition().x - background1.getGlobalBounds().width + 1.f, 0);
    }
    if (pl.sprite.getPosition().x <= background2.getPosition().x + background2.getGlobalBounds().width / 2 && pl.left == true)
    {
        background1.setPosition(background2.getPosition().x - background2.getGlobalBounds().width + 1.f, 0);
    }
    // ���������, ����� �� ����� �� ������� ������ �����


    if (D4CDimension == true) {
        background1.setColor(Purple);
        background2.setColor(Purple);
    }
    else {
        background1.setColor(sf::Color::White);
        background2.setColor(sf::Color::White);
    }
}


class Fights {
private:
    sf::Texture menutexture;
    sf::Sprite menu;
    sf::Texture Accepttexture;
    sf::Sprite Acceptbutton;
    sf::Texture Icontexture;
    sf::Sprite Icon;
    sf::Texture Rejecttexture;
    sf::Sprite Rejectbutton;
    bool IsOpen;
    Vragi* VragBitv;
    sf::Text textvizova;
    sf::Text Accepttext;
    sf::Text RewardText;
    sf::Text Rejecttext;
    sf::Font font;
    bool InFight;
    sf::Vector2f Pos;
public:
    Fights() {
       
        menutexture.loadFromFile("sprites\\hud\\FightMenu.png");
        Accepttexture.loadFromFile("sprites\\hud\\AcceptButton.png");
        Acceptbutton.setTexture(Accepttexture);
        Rejecttexture.loadFromFile("sprites\\hud\\RejectButton.png");
        Rejectbutton.setTexture(Rejecttexture);
        Icontexture.loadFromFile("sprites\\NPC\\PlohoiParen.png");
        Icon.setTexture(Icontexture);
        menu.setTexture(menutexture);
        font.loadFromFile("NjalBold.ttf");
        textvizova.setFont(font);
        textvizova.setCharacterSize(16);

        RewardText.setFont(font);
       RewardText.setCharacterSize(24);


        Accepttext.setFont(font);
        Accepttext.setCharacterSize(24);
        Rejecttext.setFont(font);
        Rejecttext.setCharacterSize(24);
        InFight = false;
       
        IsOpen = false; //false
        Accepttext.setString("Accept");
        Rejecttext.setString("Reject");
    }

    void OpenMenu(Vragi& vrag) {
        if (IsOpen == false) {
            VragBitv = &vrag;
            IsOpen = true;
        }
    }
    sf::Vector2f getPos() { return Pos; }
    bool getOpen() { return IsOpen; }
    bool getFight() { return InFight; } 
    void setFight(bool a) { InFight = a; }
    auto getVrag() { return VragBitv; }
    auto setVrag(Vragi& vrag) { VragBitv = &vrag; }
    void update(sf::Vector2f pos, sf::Vector2f mouspos, Player& pl, Stand& stpl, Stand& vragpl, sf::Vector2f plpos) {

        if (IsOpen == true) {
            if (VragBitv->Name == "Bad Guy") {
                Icontexture.loadFromFile("sprites\\NPC\\icons\\PlohoiParenIcon.png");
            }

            RewardText.setString("Reward: " + std::to_string(VragBitv->Reward) + "$");
            menu.setPosition(pos);
            Icon.setPosition({ menu.getPosition().x + 156.f, menu.getPosition().y + 155.f });
            textvizova.setPosition({ menu.getPosition().x + 90.f, menu.getPosition().y + 300.f });
            textvizova.setString(VragBitv->Name + " wants to fight you,\naccept?");
            RewardText.setPosition({ Icon.getPosition().x - 30.f, Icon.getPosition().y - 30.f });
            Acceptbutton.setPosition({ menu.getPosition().x + 10.f, menu.getPosition().y + menu.getGlobalBounds().height - 100.f });
            Rejectbutton.setPosition({ menu.getPosition().x + menu.getGlobalBounds().width - Rejectbutton.getGlobalBounds().width - 10.f, menu.getPosition().y + menu.getGlobalBounds().height - 100.f });
            Accepttext.setPosition({ Acceptbutton.getPosition().x + 30.f, Acceptbutton.getPosition().y + 5.f });
           Rejecttext.setPosition({ Rejectbutton.getPosition().x + 30.f,Rejectbutton.getPosition().y + 5.f });
            if (Rejectbutton.getGlobalBounds().contains(mouspos.x, mouspos.y)) {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    IsOpen = false;
                }
            }
            if (Acceptbutton.getGlobalBounds().contains(mouspos.x, mouspos.y)) {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    IsOpen = false;
                    InFight = true;
                    pl.stoi = false;
                    VragBitv->health = 100.f;
                    pl.sprite.setPosition({ 1000.f,840.f - pl.sprite.getGlobalBounds().height });
                    stpl.visible = false;
                    VragBitv->sprite.setPosition({ 1500.f,840.f - VragBitv->sprite.getGlobalBounds().height });
                    vragpl.sprite.setPosition({ 1500.f,840.f - VragBitv->sprite.getGlobalBounds().height });
                    Pos = plpos;
                    
                }
            }
        }
    }
   

    void draw(sf::RenderWindow& window) {
        if (IsOpen == true) {
            window.draw(menu);
            window.draw(Icon);
            window.draw(Acceptbutton);
            window.draw(Rejectbutton);
            window.draw(Accepttext);
            window.draw(Rejecttext);
            window.draw(RewardText);
            window.draw(textvizova);
        }
    }
};