/* Black Scholes Option Price Model 25/04/2014
 
 $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
 $   BlackScholes.h - header   $
 $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
 
 Copyright (C) 2014  W.B. Yates
 
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
 
    Black Scholes Merton European option price model (see Hull (6th edition), page 314)
    Suitable for pricing, for example, equity options (yield = divYield) or FX options (where yield = foreign risk free rate of interest) 
 
 
 Examples
 
    BlackScholes bs;
 
    // for these params option price is 51.83 (see Hull, Example 14.1, page 318)
    double yield = 0.03;
    double T  = 2.0 / 12.0;        
    double assetPrice = 930;        
    double rate = 0.08;		
    double vol = 0.2; 
    double strike = 900;
    double call = true;
    std::cout << "value is " <<  bs.value(strike, assetPrice, vol, rate, T, yield, call) << std::endl;
 
    // for these params Theta is -18.1528 (see Hull, Example 15.3, page 353)
    double yield = 0.03;
    double T  = 4.0 / 12.0;        
    double assetPrice = 305;        
    double rate = 0.08;		
    double vol = 0.25; 
    double strike = 300;
    double call = false; 
    std::cout << "theta is " <<  bs.theta(strike, assetPrice, vol, rate, T, yield, call) << std::endl;

    // for these params Vega is 66.4479 (see Hull, Example 15.7, page 361)
    double yield = 0.03;
    double T  = 4.0 / 12.0;        
    double assetPrice = 305;        
    double rate = 0.08;		
    double vol = 0.25; 
    double strike = 300;
    std::cout << "vega is " <<  bs.vega(strike, assetPrice, vol, rate, T, yield) << std::endl;
 
    // for these params Rho is -42.5792 (see Hull, Example 15.8, page 362)
    double yield = 0.03;
    double T  = 4.0 / 12.0;        
    double assetPrice = 305;        
    double rate = 0.08;		
    double vol = 0.25; 
    double strike = 300;
    double call = false; 
    std::cout << "rho is " <<  bs.rho(strike, assetPrice, vol, rate, T, yield, call) << std::endl; 

    // for these params Gamma is 0.00857161 (see Hull, Example 15.5, page 359)
    double yield = 0.03;
    double T  = 4.0 / 12.0;        
    double assetPrice = 305;        
    double rate = 0.08;		
    double vol = 0.25; 
    double strike = 300;
    std::cout << "gamma is " <<  bs.gamma(strike, assetPrice, vol, rate, T, yield) << std::endl;

 
    // an option on USD/GBP is both a call on sterling and a put on dollars,
    // for these params value is 0.0638857 GBP (see Hull, Example 14.2, page 322)
    double foreignRate = 0.11; // GPB interest rate
    double T  = 0.3333333333; // set this in value       
    double fxRate = 1.6; // USD/GBP      
    double rate = 0.08;	// USD interest rate	
    double vol = 0.20; 
    m_strike = 1.6;
    m_call = true 
    std::cout << "value is " <<  bs.value(strike, fxRate, vol, rate, T, foreignRate, call) << std::endl;
 */


#ifndef __BLACKSCHOLES_H__
#define __BLACKSCHOLES_H__



class BlackScholes
{
public:
	BlackScholes() {}
	~BlackScholes() {}
 
    double 
	value( double strike,       // option strike
                 double assetPrice,   // underlying asset's current value
                 double vol,          // volatility
                 double rate,         // risk free rate of interest
                 double T,            // time to maturity (year fraction)
                 double yield = 0.0,  // annualised yield of underlying asset over life of option (continuous compounded)
                 bool call = true ) const; 
    
    double 
	impliedVol( double strike,         // option strike
                double assetPrice,     // underlying asset's current value
                double marketPrice,    // market price of option
                double rate,           // risk free rate of interest
                double T,              // time to maturity (year fraction)
                double yield = 0.0 ) const;  // annualised yield of underlying asset over life of option (continuous compounded)
    
    double
    theta( double strike,      // option strike
           double assetPrice,  // underlying asset's current value
           double vol,         // volatility
           double rate,        // risk free rate of interest
           double T,           // time to maturity (year fraction)
           double yield = 0.0, // annualised yield of underlying asset over life of option (continuous compounded)
           bool call = true ) const;
    
    double
    delta( double strike,      // option strike
           double assetPrice,  // underlying asset's current value
           double vol,         // volatility
           double rate,        // risk free rate of interest
           double T,           // time to maturity (year fraction)
           double yield = 0.0, // annualised yield of underlying asset over life of option (continuous compounded)
           bool call = true ) const;
    
    double
    gamma( double strike,      // option strike
           double assetPrice,  // underlying asset's current value
           double vol,         // volatility
           double rate,        // risk free rate of interest
           double T,           // time to maturity (year fraction)
           double yield = 0.0 ) const; // annualised yield of underlying asset over life of option (continuous compounded)
    
    double
    rho( double strike,      // option strike
         double assetPrice,  // underlying asset's current value
         double vol,         // volatility
         double rate,        // risk free rate of interest
         double T,           // time to maturity (year fraction)
         double yield = 0.0, // annualised yield of underlying asset over life of option (continuous compounded)
         bool call = true ) const;
    
    double
    vega( double strike,        // option strike
          double assetPrice,    // underlying asset's current value
          double vol,           // volatility
          double rate,          // risk free rate of interest
          double T,             // time to maturity (year fraction)
          double yield = 0.0 ) const; // annualised yield of underlying asset over life of option (continuous compounded)
    
    double // the cumulative normal distribution function
	N( double x ) const;
    
    double // derivative of the cumulative normal distribution function 
	DN( double x ) const;
    
    
private:
    
};


#endif

///	

