/* Black Scholes Option Price Model 25/04/2014
 
 $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
 $   BlackScholes.cpp - code   $
 $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
 
 by W.B. Yates    
 Copyright (c) W.B. Yates. All rights reserved.
 History: 
 
 */

#include <iostream>
#include <math.h>

#ifndef __BLACKSCHOLES_H__
#include "BlackScholes.h"
#endif

#ifndef __NEARZERO_H__
#include "NearZero.h"
#endif

double 
BlackScholes::value( double strike,      // option strike
                           double assetPrice,  // asset's current value
                           double vol,         // volatility
                           double rate,        // risk free rate of interest; modify for inclusion of Div Yield
                           double T,           // time to maturity (year fraction)
                           double yield,       // annualised yield of underlying asset over life of option (continuous compounded)
                           bool call )  const
{
    double modPrice = assetPrice * exp(-yield * T);
	
	double term =  vol * sqrt(T);
	double d1 = ( log(assetPrice / strike) + (rate - yield + ((vol * vol) / 2.0)) * T ) / term;	
	double d2 = d1 - term;
    
	if (call)
		return modPrice * N(d1) - strike * exp(-rate * T) * N(d2);
	else return strike * exp(-rate * T) * N(-d2) - modPrice * N(-d1);
}

double 
BlackScholes::impliedVol( double strike,      // option strike
                          double assetPrice,  // underlying asset's current value
                          double marketPrice, // market price of option
                          double rate,        // risk free rate of interest
                          double T,           // time to maturity (year fraction)
                          double yield ) const     // annualised yield of underlying asset over life of option (continuous compounded)
// Newton-Raphson
// http://en.wikipedia.org/wiki/Newton's_method
// derivative of call option is        
// double d2 = (log(fxRate / m_strike) + (rate - foreignRate - vol * vol / 2.0) * T) / (vol * sqrtT);
// double dd1 = (T * (vol * vol/2.0 - rate - foreignRate) - log(fxRate / m_strike))/ (vol * vol * sqrtT);
// double dd2 = dd1 - sqrtT;
// double derivCall = exp(-foreignRate * T) * fxRate * DN(d1)*dd1 - exp(-rate * T)* m_strike * DN(d2) * dd2;
// we use vega
{     
    int iterations = 100;
    
    double vol = 0.5;
    double sqrtT = sqrt(T);
    double logTerm = log( assetPrice  / strike );
    double divTerm = exp( -yield * T );
    
    while (--iterations)
    {
        double p1 =  value(strike, assetPrice, vol, rate, T, yield, true) - marketPrice; 
        
        if (nearZero(p1))
            break;
        
        // vega(vol)
        double d1 = ( logTerm + (rate - yield + ((vol * vol) / 2.0)) * T ) / (vol * sqrtT);				
		double p2 = assetPrice * sqrtT * DN(d1) * divTerm;
        
        vol = vol - (p1 / p2);
    }
    
    return vol;   
}

double
BlackScholes::theta( double strike,      // option strike
                     double assetPrice,  // underlying asset's current value
                     double vol,         // volatility
                     double rate,        // risk free rate of interest
                     double T,           // time to maturity (year fraction)
                     double yield,       // annualised yield of underlying asset over life of option (continuous compounded)
                     bool call )  const  
{
    double tmp =  vol * sqrt(T);
    double d1 = ( log(assetPrice / strike) + (rate - yield + ((vol * vol) / 2.0)) * T ) / tmp;	
    double d2 = d1 - tmp;		
    
    double term = (assetPrice * DN(d1) * vol * exp(-yield * T)) / (2.0 * sqrt(T));
    
    if (call) 
        return  -term + (yield * assetPrice * N(d1) * exp( -yield * T )) - (rate * strike * exp(-rate * T) * N(d2)); 
    else return -term - (yield * assetPrice * N(-d1) * exp( -yield * T )) + (rate * strike * exp(-rate * T) * N(-d2));    
}

double
BlackScholes::delta( double strike,      // option strike
                     double assetPrice,  // underlying asset's current value
                     double vol,         // volatility
                     double rate,        // risk free rate of interest
                     double T,           // time to maturity (year fraction)
                     double yield,       // annualised yield of underlying asset over life of option (continuous compounded)
                     bool call )  const
{
    double d1 = ( log(assetPrice / strike) + (rate - yield + ((vol * vol) / 2.0)) * T ) / (vol * sqrt(T));		
    
    if (call) 
        return exp(-yield * T) * N(d1);
    else return exp(-yield * T) * (N(d1) - 1);    
}

double
BlackScholes::gamma( double strike,      // option strike
                     double assetPrice,  // underlying asset's current value
                     double vol,         // volatility
                     double rate,        // risk free rate of interest
                     double T,           // time to maturity (year fraction)
                     double yield ) const      // annualised yield of underlying asset over life of option (continuous compounded)
{    
    double term = vol * sqrt(T);
    double d1 = ( log(assetPrice / strike) + (rate - yield + ((vol * vol) / 2.0)) * T ) / term;		
    
    return (DN(d1) * exp( -yield * T )) / (assetPrice * term);	    
}

double
BlackScholes::rho( double strike,      // option strike
                   double assetPrice,  // underlying asset's current value
                   double vol,         // volatility
                   double rate,        // risk free rate of interest
                   double T,           // time to maturity (year fraction)
                   double yield,       // annualised yield of underlying asset over life of option (continuous compounded)
                   bool call ) const
{    
    double term =  vol * sqrt(T);
    double d1 = ( log(assetPrice / strike) + (rate - yield + ((vol * vol) / 2.0)) * T ) / term;	
    double d2 = d1 - term;		
    
    if (call)
        return strike * T * exp(-rate * T) * N(d2);
    else return -strike * T * exp(-rate * T) * N(-d2);    
}

double
BlackScholes::vega( double strike,      // option strike
                    double assetPrice,  // underlying asset's current value
                    double vol,         // volatility
                    double rate,        // risk free rate of interest
                    double T,           // time to maturity (year fraction)
                    double yield ) const      // annualised yield of underlying asset over life of option (continuous compounded)
{
    double d1 = ( log(assetPrice / strike) + (rate - yield + ((vol * vol) / 2.0)) * T ) / (vol * sqrt(T));		    
    return assetPrice * sqrt(T) * DN(d1) * exp( -yield * T );    
}

// the cumulative normal distribution function 
double 
BlackScholes::N( double x ) const  
{	
	double L, K, w ;
	
	double  a1 = 0.31938153, a2 = -0.356563782, a3 = 1.781477937;
	double  a4 = -1.821255978, a5 = 1.330274429;
    double  Pi = M_PI; //3.141592653589793238462643;
    
	L = fabs(x);
	K = 1.0 / (1.0 + 0.2316419 * L);
	w = 1.0 - 1.0 / sqrt(2 * Pi) * exp(-L * L / 2) * (a1 * K + a2 * K *K + a3 * pow(K,3) + a4 * pow(K,4) + a5 * pow(K,5));
	
	if ( x < 0 )
	{
		w = 1.0 - w;
	}
	return w;
}

// derivative of the cumulative normal distribution function 
double 
BlackScholes::DN( double x ) const  
// see Hull page 353
{
    double Pi2 = 2.0 * 3.141592653589793238462643;
    return (1.0 / (sqrt(Pi2))) * exp( -(x * x) / 2.0 );   
}


//



