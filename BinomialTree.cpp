/* Cox-Ross-Rubenstein Option Price Model 12/10/2014
 
 $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
 $   BinomialTree.cpp - code   $
 $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
 
 by W.B. Yates    
 Copyright (c) W.B. Yates. All rights reserved.
 History:
 
 Cox-Ross-Rubenstein binomial tree option price model (see Hull (6th edition), page 393)
 Suitable for pricing, for example, American options 
*/

#ifndef __BINOMIALTREE_H__
#include "BinomialTree.h"
#endif

#ifndef __NEARZERO_H__
#include "NearZero.h"
#endif

#include <math.h>


double
BinomialTree::value( double strike, // option strike
                  double assetPrice, // asset's current value
                  double vol, // volatility
                  double rate, // risk free rate of interest; modify for inclusion of Div Yield
                  double maturity, // year fraction; options time to maturity
                  double yield,
                  bool call ) 

{
        
    // How many time steps to maturity
    double dt = maturity / double(m_stepNumber-1);
    
    // see Hull (6th edition), Chapter 17,  page 393
    // Cox, Ross, Rubinstein
    double sqrtDt = sqrt(dt);
    double u = exp( vol * sqrtDt );
    double d = exp( -vol * sqrtDt );
    double a = exp( (rate - yield) * dt );  
    double p = (a - d) / (u - d);
    
    
    m_s[0][0] = assetPrice;
    
    for (int m = 1; m < m_stepNumber; m++)
    {
        for (int n = m + 1; n > 0 ;n--)
        {
            m_s[m][n] = u * m_s[m - 1][n - 1];
        }
        m_s[m][0] = d * m_s[m - 1][0];
    }
    
    for (int n = 0; n < m_stepNumber; n++)
    {
        m_v[m_stepNumber-1][n] = payOff( strike, m_s[m_stepNumber-1][n], call );
    }
    
    double discount = exp(-rate * dt);
    for (int m = m_stepNumber - 2; m >= 0; m--)
    {
        for (int n = 0; n <= m; n++)
        {
            double hold = ((1 - p) * m_v[m+1][n]) + (p * m_v[m+1][n+1]);
            hold *= discount;
            m_v[m][n] = dmax( hold, payOff( strike, m_s[m][n], call ) );
        }
    }

    return m_v[0][0];
}

double
BinomialTree::delta( double strike,      // option strike
                      double assetPrice,  // underlying asset's current value
                      double vol,         // volatility
                      double rate,        // risk free rate of interest
                      double maturity,           // time to maturity (year fraction)
                      double yield, // annualised yield of underlying asset over life of option (continuous compounded)
                      bool call )
{

    value( strike, assetPrice, vol, rate, maturity, yield, call );
    
    double dt = maturity / double(m_stepNumber-1);
    double sqrtDt = sqrt(dt);
    double u = exp( vol * sqrtDt );
    double d = exp( -vol * sqrtDt );    

    double delta = (m_v[1][1] - m_v[1][0]) / ((assetPrice * u) - (assetPrice * d));
    return delta;
}

double
BinomialTree::gamma( double strike,      // option strike
                    double assetPrice,  // underlying asset's current value
                    double vol,         // volatility
                    double rate,        // risk free rate of interest
                    double maturity,           // time to maturity (year fraction)
                    double yield ) // annualised yield of underlying asset over life of option (continuous compounded)
{
    
    value( strike, assetPrice, vol, rate, maturity, yield, true );
    
    double dt = maturity / double(m_stepNumber-1);
    double sqrtDt = sqrt(dt);
    double u = exp( vol * sqrtDt );
    double d = exp( -vol * sqrtDt );    
    
    double h = 0.5 * ((assetPrice * u * u) - (assetPrice * d * d));
    double delta1 = (m_v[2][2] - m_v[2][1]) / ((assetPrice * u * u) - assetPrice);
    double delta2 = (m_v[2][1] - m_v[2][0]) / (assetPrice - (assetPrice * d * d));
    return (delta1 - delta2) / h;
}

double
BinomialTree::theta( double strike,      // option strike
      double assetPrice,  // underlying asset's current value
      double vol,         // volatility
      double rate,        // risk free rate of interest
      double maturity,           // time to maturity (year fraction)
      double yield, // annualised yield of underlying asset over life of option (continuous compounded)
      bool call )
{
    value( strike, assetPrice, vol, rate, maturity, yield, call );
    
    double dt = maturity / double(m_stepNumber-1);
    double theta = (m_v[2][1] - m_v[0][0]) / (2.0 * dt);
    return theta;
}

double
BinomialTree::rho( double strike,      // option strike
                    double assetPrice,  // underlying asset's current value
                    double vol,         // volatility
                    double rate,        // risk free rate of interest
                    double maturity,           // time to maturity (year fraction)
                    double yield, // annualised yield of underlying asset over life of option (continuous compounded)
                    bool call )
{
    double deltaR = 0.00001;
    double f0 = value( strike, assetPrice, vol, rate, maturity, yield, call );
    double f1 = value( strike, assetPrice, vol, rate + deltaR, maturity, yield, call );
    return ((f0 - f1) / deltaR) / 100.0; // express as decimal not percentage
}

double
BinomialTree::vega( double strike,      // option strike
                  double assetPrice,  // underlying asset's current value
                  double vol,         // volatility
                  double rate,        // risk free rate of interest
                  double maturity,           // time to maturity (year fraction)
                  double yield ) // annualised yield of underlying asset over life of option (continuous compounded)
{
    double deltaV = 0.00001;
    double f0 = value( strike, assetPrice, vol, rate, maturity, yield, true );
    double f1 = value( strike, assetPrice, vol + deltaV, rate, maturity, yield, true );
    return ((f0 - f1) / deltaV) / 100.0; // express as decimal not percentage
}
///




