/* Black Forward Option Price Model 25/04/2014
 
 $$$$$$$$$$$$$$$$$$$$$$$$
 $   Black.h - header   $
 $$$$$$$$$$$$$$$$$$$$$$$$
 
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
 
 Black European option forward price model (see Hull (6th edition), page 332)
 Suitable for pricing options on bonds for example
 
 
 Examples
 
    Black b;
    // for these params option price is 1.11664 (see Hull, Example 14.8, page 333)
    double T  = 4.0 / 12.0;        
    double forwardPrice = 20;        
    double rate = 0.09;		
    double vol = 0.25; 
    double strike = 20;
    double call = false;

    std::cout << "value is " <<  b.value(strike, forwardPrice, vol, rate, T, call) << std::endl;
    std::cout << "value is " <<  b.impliedVol(strike, forwardPrice, 1.11664, rate, T) << std::endl;
 
 */


#ifndef __BLACK_H__
#define __BLACK_H__




class Black 
{
public:
    
    Black() {}
	virtual ~Black() {}
    
    double 
	value( double strike,       // option strike
           double forwardPrice, // underlying asset's forward value
           double vol,          // volatility
           double rate,         // risk free rate of interest
           double T,            // time to maturity (year fraction)
           bool call = true ) const; 
    
    double 
	impliedVol( double strike,        // option strike
                double forwardPrice,  // underlying asset's forward value
                double marketPrice,   // market price of option
                double rate,          // risk free rate of interest
                double T ) const;     // time to maturity (year fraction)
    
    double  // rate of change of option price with respect to time
    theta( double strike,       // option strike
           double forwardPrice, // underlying asset's forward value
           double vol,          // volatility
           double rate,         // risk free rate of interest
           double T,            // time to maturity (year fraction)
           bool call = true ) const;
    
    double // rate of change of option price with respect to price of underlying asset
    delta( double strike,       // option strike
           double forwardPrice, // underlying asset's forward value
           double vol,          // volatility
           double rate,         // risk free rate of interest
           double T,            // time to maturity (year fraction)
           bool call = true ) const;
     
    double // rate of change of delta (derivative of delta or curvature)
    gamma( double strike,       // option strike
           double forwardPrice, // underlying asset's forward value
           double vol,          // volatility
           double rate,         // risk free rate of interest
           double T ) const;    // time to maturity (year fraction)
    
    double // rate of change of option price with respect to risk free interest rate
    rho( double strike,       // option strike
         double forwardPrice, // underlying asset's forward value
         double vol,          // volatility
         double rate,         // risk free rate of interest
         double T,            // time to maturity (year fraction)
         bool call = true ) const;
    
    double // rate of change of option price with respect to volatility
    vega( double strike,       // option strike
          double forwardPrice, // underlying asset's forward value
          double vol,          // volatility
          double rate,         // risk free rate of interest
          double T ) const;    // time to maturity (year fraction)
    
    double // the cumulative normal distribution function
	N( double x ) const;
    
    double // derivative of the cumulative normal distribution function 
	DN( double x ) const;
    
    
private:
    
};


#endif

///	


