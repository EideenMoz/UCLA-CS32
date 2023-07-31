//
//  main.cpp
//  badlist
//
//  Created by Esmail Mozaffari on 5/12/23.
//


void removeBad(list<Restaurant*>& li)
{
    if (li.empty())
        return;
    
    for (list<Restaurant*>::iterator i = li.begin(); i != li.end();)
    {
        if ((*i)->stars() <= 2)
        {
            delete (*i);
            i = li.erase(i);
        }
        else
        {
            i++;
        }
    }
}





