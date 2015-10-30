/* Black Forward Option Price Model 25/04/2014
 
 $$$$$$$$$$$$$$$$$$$$$$$$
 $   Black.cpp - code   $
 $$$$$$$$$$$$$$$$$$$$$$$$
 
 by W.B. Yates    
 Copyright (c) W.B. Yates. All rights reserved.
 History: 
 
 */

#include <iostream>
#include <math.h>

#ifndef __BLACK_H__
#include "Black.h"
#endif

#ifndef __NEARZERO_H__
#include "NearZero.h"
#endif

double 
Black::value( double strike,       // option strike
                    double forwardPrice, // underlying asset's forward value
                    double vol,          // volatility
                    double rate,         // risk free rate of interest; modify for inclusion of Div Yield
                    double T,            // time to maturity (year fraction)
                    bool call ) const  
{

	double term =  vol * sqrt(T);
	double d1 = ( log(forwardPrice / strike) + (((vol * vol) / 2.0)) * T ) / term;	
	double d2 = d1 - term;

    if (call)
		return exp(-rate * T) * ((forwardPrice * N(d1)) - (strike * N(d2)));
	else return exp(-rate * T) * ((strike * N(-d2)) - (forwardPrice * N(-d1)));
}

double 
Black::impliedVol( double strike,       // option strike
                   double forwardPrice, // underlying asset's forward value
                   double marketPrice,  // market price of option
                   double rate,         // risk free rate of interest
                   double T ) const     // time to maturity (year fraction)
{
    
    int iterations = 100;
    
    double vol = 0.5;
    double sqrtT = sqrt(T);
    double logTerm = log(forwardPrice / strike);
    
    while (--iterations)
    {
        double p1 =  value(strike, forwardPrice, vol, rate, T, true) - marketPrice; 
        
        if (nearZero(p1))
            break;
        
        // vega(vol)
        double d1 = ( logTerm + (((vol * vol) / 2.0)) * T ) / (vol * sqrtT);				
		double p2 = forwardPrice * exp( -rate * T ) * sqrtT * DN(d1); 
        
        vol = vol - (p1 / p2);
    }
    
    return vol;   
}

double
Black::theta( double strike,       // option strike
              double forwardPrice, // underlying asset's forward value
              double vol,          // volatility
              double rate,         // risk free rate of interest
              double T,            // time to maturity (year fraction)
              bool call ) const         // annualised dividend yield of asset (continuous compounded)
{
	double tmp =  vol * sqrt(T);
	double d1 = ( log(forwardPrice / strike) + (((vol * vol) / 2.0)) * T ) / tmp;	
	double d2 = d1 - tmp;	
    
    double term = (forwardPrice * exp(-rate * T) * DN(d1) * vol) / (2.0 * sqrt(T));
    
    if (call) 
        return  -term + (rate * forwardPrice * exp( -rate * T ) * N(d1)) - (rate * strike * exp(-rate * T) * N(d2)); 
    else return -term - (rate * forwardPrice * exp( -rate * T ) * N(-d1)) + (rate * strike * exp(-rate * T) * N(-d2));    
}

double
Black::delta( double strike,       // option strike
              double forwardPrice, // underlying asset's forward value
              double vol,          // volatility
              double rate,         // risk free rate of interest
              double T,            // time to maturity (year fraction)
              bool call ) const
{
    double d1 =  ( log(forwardPrice / strike) + (((vol * vol) / 2.0)) * T ) / (vol * sqrt(T));		
    
    if (call) 
        return exp(-rate * T) * N(d1);
    else return exp(-rate * T) * (N(d1) - 1);    
}

double
Black::gamma( double strike,       // option strike
              double forwardPrice, // underlying asset's forward value
              double vol,          // volatility
              double rate,         // risk free rate of interest
              double T ) const     // time to maturity (year fraction)
{    
    double term = vol * sqrt(T);
    double d1 =  ( log(forwardPrice / strike) + (((vol * vol) / 2.0)) * T ) / term;		
    
    return exp( -rate * T ) * (DN(d1)  / (forwardPrice * term));	    
}

double
Black::rho( double strike,       // option strike
            double forwardPrice, // underlying asset's forward value
            double vol,          // volatility
            double rate,         // risk free rate of interest
            double T,            // time to maturity (year fraction)
            bool call ) const
{    
	double tmp =  vol * sqrt(T);
	double d1 = ( log(forwardPrice / strike) + (((vol * vol) / 2.0)) * T ) / tmp;	
	double d2 = d1 - tmp;		
    
    if (call)
        return strike * T * exp(-rate * T) * N(d2);
    else return -strike * T * exp(-rate * T) * N(-d2);    
}

double
Black::vega( double strike,       // option strike
             double forwardPrice, // underlying asset's forward value
             double vol,          // volatility
             double rate,         // risk free rate of interest
             double T ) const     // time to maturity (year fraction)

{
	double d1 = ( log(forwardPrice / strike) + (((vol * vol) / 2.0)) * T ) / (vol * sqrt(T));		        
    return forwardPrice * exp( -rate * T ) * sqrt(T) * DN(d1);    
}

// the cumulative normal distribution function 
double 
Black::N( double x ) const  
{	
	double L, K, w ;
	
	const double  a1 = 0.31938153, a2 = -0.356563782, a3 = 1.781477937;
	const double  a4 = -1.821255978, a5 = 1.330274429;
	const double  Pi = 3.141592653589793238462643;
    
	L = fabs(x);
	K = 1.0 / (1.0 + 0.2316419 * L);
	w = 1.0 - 1.0 / sqrt(2 * Pi) * exp(-L * L / 2) * (a1 * K + a2 * K * K + a3 * pow(K,3) + a4 * pow(K,4) + a5 * pow(K,5));
	
	if ( x < 0 )
	{
		w = 1.0 - w;
	}
	return w;
}

// derivative of the cumulative normal distribution function 
double 
Black::DN( double x ) const  
// see Hull page 353
{
    const double Pi2 = 2.0 * 3.141592653589793238462643;
    return (1.0 / (sqrt(Pi2))) * exp( -(x * x) / 2.0 );   
}


//



