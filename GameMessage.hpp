#ifndef GAMEMESSAGE_HPP_INCLUDED
#define GAMEMESSAGE_HPP_INCLUDED
class GameMessage{
    public:
        GameMessage();
        void AddMessage(sf::String newMessage);
        void drawing(sf::RenderWindow* app);
        ~GameMessage();
    private:
        bool m_empty;
        sf::Font m_font;
        sf::Text m_principal;
        sf::Text m_transition;
        vector<sf::String> m_message;
        PausableClock m_nextMessage;
};
#endif // GAMEMESSAGE_HPP_INCLUDED
