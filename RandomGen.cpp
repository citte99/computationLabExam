#include "RandomGen.h"
//implementazione
class Gaussiana{
public:
	Gaussiana(double mean, double sigma){
		m_sigma=sigma;
		m_mean=mean;
	}
	double operator()(double x){
		return exp(-pow((x-m_mean)/m_sigma, 2)/2)/sqrt(2*M_PI*pow(m_sigma, 2));
	}
	double getMax(){
		return 1/sqrt(2*M_PI*pow(m_sigma, 2));
	}
private:
	double m_sigma;
	double m_mean;
};

RandomGen::RandomGen(unsigned int seed){
	m_seed=seed;
	m_a=1664525;
	m_c=1013904223;
	m_m=1<<31;
}
double RandomGen::Rand(){
	m_seed =  (m_a*m_seed+m_c)%(m_m); 
	return m_seed / double(m_m);
}

double RandomGen::Unif(double left, double right){
	if(left>right){
		double aux=left;
		left=right;
		right=aux;
	}
	return left+(right-left)*Rand();
}

double RandomGen::Exp(double mean){
	return (-1/(mean) * log(1-Rand()));
}

double RandomGen::Gauss(double mean, double sigma){
		
	double u1 = Rand();
	double u2= Rand();
			
	return mean+ sigma *((float) (sqrt(-2.* log(u1)) * cos(2 *M_PI* u2)));
}

double RandomGen::GaussAR(double mean, double sigma){
	double left=mean-5*sigma;
	double right=mean+5*sigma;
	double numExtracted;
	bool reject;
	do{
		numExtracted=left+(right-left)*Rand();
		Gaussiana myGauss(mean, sigma);
		reject=(myGauss.getMax()*Rand())>(myGauss(numExtracted));

	}while (reject);
	return numExtracted;

}
