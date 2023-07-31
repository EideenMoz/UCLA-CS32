//
//  main.cpp
//  event
//
//  Created by Esmail Mozaffari on 5/3/23.
//


// Event -------------------------------------------------------------------------------
class Event
{
    public:
        Event(string name);
        virtual ~Event() {};
    
        virtual string name() const;
        virtual bool isSport() const;
        virtual string need() const = 0;        // pure virtual, abstract class
        
    private:
        string m_name;
};

Event::Event(string name)
{
    m_name = name;
}

string Event::name() const
{
    return m_name;
}

bool Event::isSport() const
{
    return true;
}


// BasketballGame --------------------------------------------------------------------------------------------
class BasketballGame : public Event
{
    public:
        BasketballGame(string name);
        virtual ~BasketballGame();
    
        virtual string need() const;
};

BasketballGame::BasketballGame(string name)
 : Event(name) {}

string BasketballGame::need() const
{
    return "hoops";
}

BasketballGame::~BasketballGame()
{
    cout << "Destroying the " << Event::name() << " basketball game" << endl;
}


// Concert -----------------------------------------------------------------------------------------------------
class Concert : public Event
{
    public:
        Concert(string name, string genre);
        virtual ~Concert();

        virtual bool isSport() const;
        virtual string need() const;
    
    private:
        string m_genre;
};

Concert::Concert(string name, string genre)
 : Event(name)
{
    m_genre = genre;
}


bool Concert::isSport() const
{
    return false;
}

string Concert::need() const
{
    return "a stage";
}

Concert::~Concert()
{
    cout << "Destroying the " << Event::name() << " " <<  m_genre << " concert" << endl;
}


// HockeyGame ----------------------------------------------------------------------------------------------
class HockeyGame : public Event
{
    public:\

        HockeyGame(string name);
        virtual ~HockeyGame();
    
        virtual string need() const;
};

HockeyGame::HockeyGame(string name)
 : Event(name) {}

string HockeyGame::need() const
{
    return "ice";
}

HockeyGame::~HockeyGame()
{
    cout << "Destroying the " << Event::name() << " hockey game" << endl;
}

