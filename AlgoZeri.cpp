#include "AlgoZeri.h"
#include <iostream>

//funzione sign
double Sign(double x){ return(x==0.?0.:(x>0?1.:-1));};

double Bisezione::CercaZeri(double xmin, double xmax, const FunzioneBase* f){

	m_a= xmin;
	m_b= xmax;
	double center;

	double signLeft=Sign(f->Eval(m_a));
	double signCenter;
	double signRight=Sign(f->Eval(m_b));
	
	if(m_a>m_b||!(signLeft*signRight<0)){
		std::cout<<"Gli estremi dell'intervallo non sono accettabili o non sono discordi"<<std::endl;
		return 0;
	}

	
	double myErr=(m_b-m_a)/2.;
	int iterCounter=0;
	while(myErr>m_prec&&iterCounter<maxIteraz){
		center=m_a+(m_b-m_a)/2.;
		signLeft=Sign(f->Eval(m_a));
		signCenter=Sign(f->Eval(center));
		if(signLeft*signCenter<0.){
			m_b=center;
		}else{
			m_a=center;
		}
		myErr=(m_b-m_a)/2.;
		iterCounter++;
	}
	if(!(iterCounter<maxIteraz)){
		std::cout<<"limite di iterazioni raggiunto"<<std::endl;
	}
	return center;
};

//imposto i boundary
//se non sono di segno opposto mi fermo 
//divido in due e scelgo il nuovo intervallo
