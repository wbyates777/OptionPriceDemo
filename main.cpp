/* Option Pricing Demo 30/10/2015
 
 $$$$$$$$$$$$$$$$$$$$$$$
 $   main.h - header   $
 $$$$$$$$$$$$$$$$$$$$$$$


Copyright (C) 2015  W.B. Yates

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see http://www.gnu.org/licenses/
 
 History:
 
 Functional implementations of 3 option pricing models (see "Options, Futures, and Other Derivatives" by J.C. Hull) 
 
 1) Black Scholes' model
 2) Binomial Tree model
 3) Black's model
 
 Each model comes with some test examples.
 
 The idea is to embed these classes in your option class
 
*/


#include <iostream>

#ifndef __BLACKSCHOLES_H__
#include "BlackScholes.h"
#endif

#ifndef __BLACK_H__
#include "Black.h"
#endif

#ifndef __BINOMIALTREE_H__
#include "BinomialTree.h"
#endif

int 
main(int argc, const char * argv[]) 
{
    std::cout << "Option Pricing Demo Copyright (C) 2015,  W. B. Yates" << std::endl;
    std::cout << "This program comes with ABSOLUTELY NO WARRANTY; for details see http://www.gnu.org/licenses/." << std::endl;
    std::cout << "This is free software, and you are welcome to redistribute it" << std::endl;
    std::cout << "under certain conditions; see http://www.gnu.org/licenses/" << std::endl;
    std::cout << std::endl;
    
    BlackScholes bs;
   
    double yield = 0;
    double T;        
    double assetPrice;        
    double rate;		
    double vol; 
    double strike;
    double call;
    
    // for these params option price is 51.83 (see Hull, Example 14.1, page 318)
    yield = 0.03;
    T  = 2.0 / 12.0;        
    assetPrice = 930;        
    rate = 0.08;		
    vol = 0.2; 
    strike = 900;
    call = true;
    std::cout << "value is " <<  bs.value(strike, assetPrice, vol, rate, T, yield, call) << std::endl;
    
    // for these params Theta is -18.1528 (see Hull, Example 15.3, page 353)
    yield = 0.03;
    T  = 4.0 / 12.0;        
    assetPrice = 305;        
    rate = 0.08;		
    vol = 0.25; 
    strike = 300;
    call = false; 
    std::cout << "theta is " <<  bs.theta(strike, assetPrice, vol, rate, T, yield, call) << std::endl;
    
    // for these params Vega is 66.4479 (see Hull, Example 15.7, page 361)
    yield = 0.03;
    T  = 4.0 / 12.0;        
    assetPrice = 305;        
    rate = 0.08;		
    vol = 0.25; 
    strike = 300;
    std::cout << "vega is " <<  bs.vega(strike, assetPrice, vol, rate, T, yield) << std::endl;
    
    // for these params Rho is -42.5792 (see Hull, Example 15.8, page 362)
    yield = 0.03;
    T  = 4.0 / 12.0;        
    assetPrice = 305;        
    rate = 0.08;		
    vol = 0.25; 
    strike = 300;
    call = false; 
    std::cout << "rho is " <<  bs.rho(strike, assetPrice, vol, rate, T, yield, call) << std::endl; 
    
    // for these params Gamma is 0.00857161 (see Hull, Example 15.5, page 359)
    yield = 0.03;
    T  = 4.0 / 12.0;        
    assetPrice = 305;        
    rate = 0.08;		
    vol = 0.25; 
    strike = 300;
    std::cout << "gamma is " <<  bs.gamma(strike, assetPrice, vol, rate, T, yield) << std::endl;
    
    
    // an option on USD/GBP is both a call on Sterling and a put on Dollars,
    // for these params value is 0.0638857 GBP (see Hull, Example 14.2, page 322)
    double foreignRate = 0.11; // GPB interest rate
    T  = 0.3333333333;       
    double fxRate = 1.6;       // USD/GBP      
    rate = 0.08;	           // USD interest rate	
    vol = 0.20; 
    strike = 1.6;
    call = true; 
    std::cout << "value is " <<  bs.value(strike, fxRate, vol, rate, T, foreignRate, call) << std::endl;
    
    return 0;
}
