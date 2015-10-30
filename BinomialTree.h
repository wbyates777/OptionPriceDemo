/* Cox-Ross-Rubenstein  Option Price Model 12/10/2014
 
 $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
 $   BinomialTree.h - header   $
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
 
 Cox-Ross-Rubenstein binomial tree option price model (see Hull, 6th edition, page 393)
 Suitable for pricing, for example, American options 
 
 Examples
 
 BinomialTree bt;
 
 // for these params option price is 4.49 (see Hull, Example 17.1, page 394)
 double yield = 0.0;
 double T  = 0.4167;        
 double assetPrice = 50;        
 double rate = 0.1;		
 double vol = 0.4; 
 double strike = 50;
 double call = true;
 int MAXSTEP = 5
 std::cout << "value is " <<  bt.value(strike, assetPrice, vol, rate, T, yield, call) << std::endl;

 */
#ifndef __BINOMIALTREE_H__
#define __BINOMIALTREE_H__

#include <stdio.h>


#ifndef __MATRIX_H__
#include "AMatrix.h"
#endif

class BinomialTree
{
public:
    
    BinomialTree(): m_stepNumber(51), // 50 plus today
                    m_s(m_stepNumber, m_stepNumber, 0.0), 
                    m_v(m_stepNumber, m_stepNumber, 0.0) {}
   
    ~BinomialTree() 
    {
        m_stepNumber = 0;
        m_s.clear();
        m_v.clear();
    }
    
    
    //Cox-Ross-Rubenstein
    double 
    value( double strike,       // option strike
         double assetPrice,   // underlying asset's current value
         double vol,          // volatility
         double rate,         // risk free rate of interest
         double T,            // time to maturity (year fraction)
         double yield = 0.0,  // annualised yield of underlying asset over life of option (continuous compounded)
         bool call = true ) ; 
    
   /* double 
    impliedVol( double strike,         // option strike
                double assetPrice,     // underlying asset's current value
                double marketPrice,    // market price of option
                double rate,           // risk free rate of interest
                double T,              // time to maturity (year fraction)
                double yield = 0.0 ) const;  // annualised yield of underlying asset over life of option (continuous compounded) */
    
    double
    theta( double strike,      // option strike
           double assetPrice,  // underlying asset's current value
           double vol,         // volatility
           double rate,        // risk free rate of interest
           double T,           // time to maturity (year fraction)
           double yield = 0.0, // annualised yield of underlying asset over life of option (continuous compounded)
           bool call = true );
    
    double
    delta( double strike,      // option strike
           double assetPrice,  // underlying asset's current value
           double vol,         // volatility
           double rate,        // risk free rate of interest
           double T,           // time to maturity (year fraction)
           double yield = 0.0, // annualised yield of underlying asset over life of option (continuous compounded)
           bool call = true );
    
    double
    gamma( double strike,      // option strike
           double assetPrice,  // underlying asset's current value
           double vol,         // volatility
           double rate,        // risk free rate of interest
           double T,           // time to maturity (year fraction)
           double yield = 0.0 ) ; // annualised yield of underlying asset over life of option (continuous compounded)
    
    double
    rho( double strike,      // option strike
         double assetPrice,  // underlying asset's current value
         double vol,         // volatility
         double rate,        // risk free rate of interest
         double T,           // time to maturity (year fraction)
         double yield = 0.0, // annualised yield of underlying asset over life of option (continuous compounded)
         bool call = true );
    
    double
    vega( double strike,        // option strike
          double assetPrice,    // underlying asset's current value
          double vol,           // volatility
          double rate,          // risk free rate of interest
          double T,             // time to maturity (year fraction)
          double yield = 0.0 ); // annualised yield of underlying asset over life of option (continuous compounded)
    
    
    int 
    timeSteps( void ) const { return m_stepNumber - 1; }
    
    void 
    timeSteps( const unsigned int ts ) 
    { 
        m_stepNumber = ts + 1; // add a step for today
        m_s.resize(m_stepNumber, m_stepNumber, 0.0);
        m_v.resize(m_stepNumber, m_stepNumber, 0.0);
    } 

        
private:
    
    inline double 
    dmax(double x, double y) const { return (x > y) ?  x : y; }
    
    inline double
    payOff(double strike, double price, bool call) const
    {
        return (call) ? dmax( price - strike, 0.0 ) : dmax( strike - price, 0.0 ); 
    }
    
    int m_stepNumber;
    Matrix<double> m_s;  // asset price tree
    Matrix<double> m_v;  // option value tree   
};


#endif /* defined(__FinCalculator__BinomialTree__) */
