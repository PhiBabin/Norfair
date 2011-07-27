#include "GameMessage.hpp"

GameMessage::GameMessage():m_empty(true){
    m_font.LoadFromFile("font/pixel.ttf");
    m_principal.SetFont(m_font);
    m_transition.SetFont(m_font);
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
    if(m_message.size()>0)m_principal.SetString(m_message.at(0));
    else m_principal.SetString("");
    if(m_message.size()>1)m_transition.SetString(m_message.at(1));
    else m_transition.SetString("");

    if(m_nextMessage.GetElapsedTime()>4000){
        m_principal.Move(app->GetFrameTime()*0.7,0);
        if(m_transition.GetPosition().x+app->GetFrameTime()*0.7<g_config["screenwidth"]/2)m_transition.Move(app->GetFrameTime()*0.7,0);
        else m_transition.SetPosition(g_config["screenwidth"]/2,g_config["screenheight"]-100);

    }
    else{
        m_principal.SetPosition(g_config["screenwidth"]/2,g_config["screenheight"]-100);
        m_transition.SetPosition(-300,g_config["screenheight"]-100);
    }

    m_principal.SetOrigin(m_principal.GetRect().Width/2,0);
    m_transition.SetOrigin(m_principal.GetRect().Width/2,0);

    app->Draw(m_principal);
    app->Draw(m_transition);
}
GameMessage::~GameMessage(){
}
