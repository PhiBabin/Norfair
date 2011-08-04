#ifndef GAMEMESSAGE_HPP_INCLUDED
#define GAMEMESSAGE_HPP_INCLUDED
class GameMessage{
    public:
        GameMessage();
        void AddMessage(sf::String newMessage);
        void AddText(sf::String newText, sf::Vector2f pos);
        void drawing(sf::RenderWindow* app);
        ~GameMessage();
    private:
        bool m_empty;
        sf::Font m_font1;
        sf::Font m_font2;
        sf::Text m_principal;
        vector<sf::String> m_message;
        vector<sf::Text> m_text;
        PausableClock m_nextMessage;
};
#endif // GAMEMESSAGE_HPP_INCLUDED
