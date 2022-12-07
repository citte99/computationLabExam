#include "Integral.h"
#include <algorithm>
#include <iostream> //da togliere
#include "TH1F.h"
#include <cmath>

using namespace std;

Integral::Integral(double a, double b, const FunzioneBase* f){

   m_f = f;
   m_a = min(a,b);
   m_b = max(a,b);
   if ( a > b) m_sign = -1;
   else m_sign = 1;   
}

double Integral::MidPoint(unsigned int nstep){

   m_h = (m_b - m_a)/double(nstep);
   m_sum = 0.;

   for (unsigned int i=0; i<nstep; i++){
     m_sum += m_f->Eval( m_a + (i+0.5)*m_h );
   }	

   m_integral = m_sign*m_sum*m_h;

   return m_integral;
}
double Integral::Simpson(unsigned nstep){
	m_h = (m_b - m_a)/double(nstep);
  m_sum = m_f->Eval(m_a)+m_f->Eval(m_b);
	for(int i=1; i<nstep; i+=2){
		m_sum+=2*m_f->Eval(m_a+i*m_h/2);
	}
	for (int i=2; i<nstep; i+=2){
		m_sum+=4*m_f->Eval(m_a+i*m_h/2);
	}
	m_integral=m_sign*m_sum*m_h/3;
	return m_integral;
}
double Integral::Trapezoidi(double prec){
	//raddoppio sempre il numero di intervalli
	m_h = (m_b - m_a);
	m_sum=(m_f->Eval(m_a)+m_f->Eval(m_b))/2.;
	m_integralPrec=m_sum*m_h;//precedente
	m_h=m_h/2.;
	m_sum+=m_f->Eval(m_a+m_h);
	m_integral=m_sum*m_h;
	while(4./3.*fabs(m_integral-m_integralPrec)>prec){
		m_integralPrec=m_integral;
		m_h=m_h/2;
		double posizEvaluation=m_a+m_h;
		while(posizEvaluation<m_b){
			m_sum+=m_f->Eval(posizEvaluation);
			posizEvaluation+=2*m_h;
		}
		m_integral=m_sum*m_h;
	}
	return m_integral;
}

double Integral::Trapezoidi(int nstep){
	m_sum=m_f->Eval(m_a)/2.+m_f->Eval(m_b)/2.;
	m_h=(m_b-m_a)/((double)nstep);
	for (int i=1; i<nstep; i++){
		m_sum+=m_f->Eval(m_a+i*m_h);
	}
	m_integral=m_sum*m_h;
	return m_integral;
}

double Integral::MonteCarloMedia(int npunti, RandomGen* myGen){
	double sum=0;
	for(int i=0; i<npunti; i++){
		sum+=m_f->Eval(myGen->Unif(m_a, m_b));
	}
	return sum*(m_b-m_a)*(m_sign)/npunti;
}
/*
double Integral::MonteCarloMediaFixedPrec(double prec, RandomGen* myGen){
	if (prec< 0.0001){
		std::cout<<"To low precision, try with = or bigger than 0.0001"<<std::endl;
		exit(-1);
	}
	TH1F histo1("histo1","histo1", 1, 0, 1);
	histo1.StatOverflows(kTRUE);

	for(int i=0; i<10000; i++){
		histo1.Fill(MonteCarloMedia(100, myGen));
	}
	double err1=histo1.GetRMS();
	double k=err1*sqrt(100);
	int nNeeded=(int)(pow(k/prec, 2)+1); 
	return MonteCarloMedia(nNeeded, myGen);
}
*/

double Integral::MonteCarloMediaFixedPrec(double prec, RandomGen* myGen){
	if (prec< 0.0001){
		std::cout<<"To low precision, try with = or bigger than 0.0001"<<std::endl;
		exit(-1);
	}
	TH1F histo1("histo1","histo1", 1, 0, 1);
	histo1.StatOverflows(kTRUE);

	for(int i=0; i<10000; i++){
		histo1.Fill(m_f->Eval(myGen->Unif(m_a, m_b)));
	}
	double devStFun=histo1.GetRMS();
	int nNeeded=(int)pow(devStFun*(m_b-m_a)/prec, 2); 
	return MonteCarloMedia(nNeeded, myGen);
}

double Integral::MonteCarloHom(int npunti, RandomGen* myGen, double max){
	int hitCounter=0;
	for(int i=0; i<npunti; i++){
		if (m_f->Eval(myGen->Unif(m_a, m_b))>myGen->Rand()*max){
			hitCounter++;
		}
	}
	return (m_b-m_a)*max*hitCounter/(double)npunti;
}

double Integral::MonteCarloHomFixedPrec(double prec, RandomGen* myGen, double max){
	if (prec< 0.0001){
		std::cout<<"To low precision, try with = or bigger than 0.0001"<<std::endl;
		exit(-1);
	}
	TH1F histo1("histo1","histo1", 1, 0, 1);
	histo1.StatOverflows(kTRUE);

	for(int i=0; i<10000; i++){
		histo1.Fill(MonteCarloHom(100, myGen, max));
	}
	double err1=histo1.GetRMS();
	double k=err1*sqrt(100);
	int nNeeded=(int)(pow(k/prec, 2)+1); 
	return MonteCarloHom(nNeeded, myGen, max);
}
/*
int Integral::quantiIntervalliSarebberoNecessari(double prec){
	//raddoppio sempre il numero di intervalli
	m_h = (m_b - m_a);
	m_sum=(m_f->Eval(m_a)+m_f->Eval(m_b))/2.;
	m_integralPrec=m_sum*m_h;//precedente
	m_h=m_h/2.;
	m_sum+=m_f->Eval(m_a+m_h);
	m_integral=m_sum*m_h;
	while(4./3.*fabs(m_integral-m_integralPrec)>prec){
		m_integralPrec=m_integral;
		m_h=m_h/2;
		double posizEvaluation=m_a+m_h;
		while(posizEvaluation<m_b){
			m_sum+=m_f->Eval(posizEvaluation);
			posizEvaluation+=2*m_h;
		}
		m_integral=m_sum*m_h;
	}
	return (int)((m_b-m_a)/m_h);
}
*/

int Integral::MonteCarloMediaFixedPrecCustom(double prec, RandomGen* myGen){
	if (prec< 0.0001){
		std::cout<<"To low precision, try with = or bigger than 0.0001"<<std::endl;
		exit(-1);
	}
	TH1F histo1("histo1","histo1", 1, 0, 1);
	histo1.StatOverflows(kTRUE);

	for(int i=0; i<10000; i++){
		histo1.Fill(m_f->Eval(myGen->Unif(m_a, m_b)));
	}
	double devStFun=histo1.GetRMS();
	int nNeeded=(int)pow(devStFun*(m_b-m_a)/prec, 2); 
	return nNeeded;
}