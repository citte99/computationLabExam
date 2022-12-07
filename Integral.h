#ifndef __INTEGRAL_H__
#define __INTEGRAL_H__

#include "Funzioni.h"
#include "RandomGen.h"

class Integral{

public:
   Integral(double a, double b, const FunzioneBase* f);
   double MidPoint(unsigned nstep);
   double Simpson(unsigned nstep);
	 double Trapezoidi(double prec);
	 double Trapezoidi(int nstep);
	 double MonteCarloMedia(int npunti, RandomGen* myGen);
	 double MonteCarloMediaFixedPrec(double prec, RandomGen* myGen);
	 int MonteCarloMediaFixedPrecCustom(double prec, RandomGen* myGen);
	 double MonteCarloHom(int npunti, RandomGen* myGen, double max);
	 double MonteCarloHomFixedPrec(double prec, RandomGen* myGen, double max);
	 //int quantiIntervalliSarebberoNecessari(double prec);

private:
   double m_a, m_b;
   double m_sum;
   double m_h;
   int m_sign;
   double m_integral;
	 double m_integralPrec;
   const FunzioneBase* m_f;
};

#endif