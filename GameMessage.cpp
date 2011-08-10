#include "GameMessage.hpp"

GameMessage::GameMessage():m_empty(true){
    m_font1.LoadFromFile("font/pixel1.ttf");
    m_font2.LoadFromFile("font/pixel2.ttf");
    m_principal.SetFont(m_font1);
    m_principal.SetCharacterSize(18);
    m_nextMessage.Reset();
}
void GameMessage::AddMessage(sf::String newMessage){
    if(m_message.size()==0)m_nextMessage.Reset();
    m_message.push_back(newMessage);

}
void GameMessage::AddText(sf::String newText, sf::Vector2f pos){
    sf::Text text(newText,m_font2,16);
    text.SetPosition(pos);
    text.SetColor(sf::Color(255,255,255,255));
    m_text.push_back(text);

}
void GameMessage::drawing(sf::RenderWindow* app){
    if(m_nextMessage.GetElapsedTime()>5000 && m_message.size()>0){
        m_message.erase(m_message.begin());
        m_nextMessage.Reset();
    }
    for(unsigned int i=0;i<m_message.size();i++){
       m_principal.SetString(m_message.at(i));
        m_principal.SetPosition(5,GameConfig::g_config["screenheight"]-20+i*-20);
        app->Draw(m_principal);
    }
    for(unsigned int i=0;i<m_text.size();i++){
        m_text.at(i).Move(0,-30.f*app->GetFrameTime()/1000.f);
        float newColor=-60.f*app->GetFrameTime()/1000.f;
        if(m_text.at(i).GetColor().a+newColor<0)m_text.erase(m_text.begin()+i);
        else{
            m_text.at(i).SetColor(sf::Color(255,255,255,m_text.at(i).GetColor().a+newColor));
            app->Draw(m_text.at(i));
        }
    }
}
GameMessage::~GameMessage(){
}
