#ifndef ENDSTATE_HPP_INCLUDED
#define ENDSTATE_HPP_INCLUDED

class EndState: public GameState {
    public:
        EndState(GameEngine* theGameEngine);
        virtual void init();
        virtual void loop();
        virtual void stop();
        virtual void pause();
        virtual void resume();
        virtual void GetEvents(sf::Event eventNew);
        virtual void draw();
        virtual ~EndState();
    private:
        GameEngine *m_gameEngine;
        bool m_scaleUp;
        bool m_start;
        ImgAnim m_winner;
        sf::Sprite m_retry;
        PausableClock m_party;
        PausableClock m_continue;
};


#endif // ENDSTATE_HPP_INCLUDED
