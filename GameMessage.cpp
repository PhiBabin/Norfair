#include "GameMessage.hpp"

GameMessage::GameMessage():m_empty(true){
    m_font.LoadFromFile("font/pixel.ttf");
    m_principal.SetFont(m_font);
    m_principal.SetCharacterSize(18);
    m_nextMessage.Reset();
}
void GameMessage::AddMessage(sf::String newMessage){
    if(m_message.size()==0)m_nextMessage.Reset();
    m_message.push_back(newMessage);

}
void GameMessage::drawing(sf::RenderWindow* app){
    if(m_nextMessage.GetElapsedTime()>5000 && m_message.size()>0){
        m_message.erase(m_message.begin());
        m_nextMessage.Reset();
    }
    for(int i=0;i<m_message.size();i++){
       m_principal.SetString(m_message.at(i));
        m_principal.SetPosition(5,g_config["screenheight"]-20+i*-20);
        app->Draw(m_principal);
    }
}
GameMessage::~GameMessage(){
}
