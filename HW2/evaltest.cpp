//
//  main.cpp
//  eval
//
//  Created by Esmail Mozaffari on 5/2/23.
//

#include <iostream>
#include <string>
#include <stack>
#include <cassert>
#include "eval.h"
using namespace std;

int main()
{
    string pf;
    bool answer;
    assert(evaluate("T^ F", pf, answer) == 0  &&  pf == "TF^"  &&  answer);
    assert(evaluate("T^", pf, answer) == 1);
    assert(evaluate("F F", pf, answer) == 1);
    assert(evaluate("TF", pf, answer) == 1);
    assert(evaluate("()", pf, answer) == 1);
    assert(evaluate("()T", pf, answer) == 1);
    assert(evaluate("T(F^T)", pf, answer) == 1);
    assert(evaluate("T(&T)", pf, answer) == 1);
    assert(evaluate("(T&(F^F)", pf, answer) == 1);
    assert(evaluate("T|F", pf, answer) == 1);
    assert(evaluate("", pf, answer) == 1);
    assert(evaluate("F  ^  !F & (T&F) ", pf, answer) == 0 &&  pf == "FF!TF&&^"  &&  !answer);
    assert(evaluate(" F  ", pf, answer) == 0 &&  pf == "F"  &&  !answer);
    assert(evaluate("((T))", pf, answer) == 0 &&  pf == "T"  &&  answer);

    assert(evaluate("T", pf, answer) == 0 && answer);
    assert(evaluate("(F)", pf, answer) == 0 && !answer);
    assert(evaluate("T^(F)", pf, answer) == 0 && answer);
    assert(evaluate("T ^ !F", pf, answer) == 0 && !answer);
    assert(evaluate("!(T&F)", pf, answer) == 0 && answer);
    assert(evaluate("!T&F", pf, answer) == 0 && !answer);
    assert(evaluate("T^F&F", pf, answer) == 0 && answer);
    assert(evaluate("T&!(F^T&T^F)^!!!(F&T&F)", pf, answer) == 0 && answer);
    
    
    //valid cases
        assert(evaluate("T", pf, answer) == 0  &&  pf == "T"  &&  answer);
        assert(evaluate("(F)", pf, answer) == 0  &&  pf == "F"  &&  !answer);
        assert(evaluate("T^ F", pf, answer) == 0  &&  pf == "TF^"  &&  answer);
        assert(evaluate("T&(F)", pf, answer) == 0  &&  pf == "TF&"  &&  !answer);
        assert(evaluate("T & !F", pf, answer) == 0  &&  pf == "TF!&"  &&  answer);
        assert(evaluate("!(F^T)", pf, answer) == 0  &&  pf == "FT^!"  &&  !answer);
        assert(evaluate("!F^T", pf, answer) == 0  &&  pf == "F!T^"  &&  !answer);
        assert(evaluate("T^F&F", pf, answer) == 0  &&  pf == "TFF&^"  &&  answer);
        assert(evaluate("T&!(F^T&T^F)^!!!(F&T&F)", pf, answer) == 0 &&  answer);
        assert(evaluate("F  ^  !F & (T&F) ", pf, answer) == 0 &&  pf == "FF!TF&&^"  &&  !answer);
        assert(evaluate(" F  ", pf, answer) == 0 &&  pf == "F"  &&  !answer);
        assert(evaluate("((T))", pf, answer) == 0 &&  pf == "T"  &&  answer);
        assert(evaluate("(T & !F)", pf, answer) == 0  &&  pf == "TF!&"  &&  answer);
        assert(evaluate("!F  ^  !F & (T&F) ", pf, answer) == 0  &&  pf == "F!F!TF&&^"  &&  answer);
        assert(evaluate("(T&(F^F))", pf, answer) == 0 && pf == "TFF^&" && !answer);
        assert(evaluate("F&T&F", pf, answer) == 0 && pf == "FT&F&"  && !answer);


        
        //check invalid cases
        assert(evaluate("(T&(F^F)", pf, answer) == 1);
        assert(evaluate("T^", pf, answer) == 1);
        assert(evaluate("F F", pf, answer) == 1);
        assert(evaluate("TF", pf, answer) == 1);
        assert(evaluate("()", pf, answer) == 1);
        assert(evaluate("(  )", pf, answer) == 1);
        assert(evaluate("(  T&F)T", pf, answer) == 1);
        assert(evaluate("T(F^T)", pf, answer) == 1);
        assert(evaluate("T(&T)", pf, answer) == 1);
        assert(evaluate("", pf, answer) == 1);
        assert(evaluate("  ", pf, answer) == 1);
        assert(evaluate("T!", pf, answer) == 1);
        assert(evaluate("T(", pf, answer) == 1);
        assert(evaluate("(TT", pf, answer) == 1);
        assert(evaluate("&TF", pf, answer) == 1);
        assert(evaluate(")(", pf, answer) == 1);
        assert(evaluate("#2", pf, answer) == 1);
        assert(evaluate("F&&", pf, answer) == 1);
        assert(evaluate("F!!", pf, answer) == 1);
        assert(evaluate("F!!T", pf, answer) == 1);
        
        //check valid cases
        assert(evaluate("T", pf, answer) == 0  &&  pf == "T"  &&  answer);
        assert(evaluate("T^T", pf, answer) == 0  &&  pf == "TT^"  &&  !answer);
        assert(evaluate("T&T", pf, answer) == 0  &&  pf == "TT&"  &&  answer);
        assert(evaluate("F^F", pf, answer) == 0  &&  pf == "FF^"  &&  !answer);
        assert(evaluate("T & !F", pf, answer) == 0  &&  pf == "TF!&"  &&  answer);
        assert(evaluate("!(F^T)", pf, answer) == 0  &&  pf == "FT^!"  &&  !answer);
        assert(evaluate("!F^T", pf, answer) == 0  &&  pf == "F!T^"  &&  !answer);
        assert(evaluate("T^F&F", pf, answer) == 0  &&  pf == "TFF&^"  &&  answer);
        assert(evaluate("T&!(F^T&T^F)^!!!(F&T&F)", pf, answer) == 0  &&  pf == "TFTT&^F^!&FT&F&!!!^"  &&  answer);
        assert(evaluate("(T&((F^T)&(T)))", pf, answer) == 0  &&  pf == "TFT^T&&"  &&  answer);
        
        assert(evaluate("(T^F)T", pf, answer) == 1);
        assert(evaluate("F&(&T)", pf, answer) == 1);
        assert(evaluate("F&^T", pf, answer) == 1);
        assert(evaluate("T!T", pf, answer) == 1);
        assert(evaluate("(F", pf, answer) == 1);
        assert(evaluate("F)", pf, answer) == 1);
        assert(evaluate("TF", pf, answer) == 1);
        assert(evaluate("F:T", pf, answer) == 1);
        assert(evaluate("F&:", pf, answer) == 1);
        assert(evaluate("F T&T", pf, answer) == 1);
        assert(evaluate("1& ^T", pf, answer) == 1);

        assert(evaluate("T^F^T", pf, answer) == 0 && pf == "TF^T^" && !answer);
    cout << "Passed all tests" << endl;
}
