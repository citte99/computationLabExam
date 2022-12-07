#ifndef __EQ_DIFF__
#define __EQ_DIFF__

#include "VectorOperations.h"
#include <cmath>

using namespace std;

// ===============================================================
// Classe astratta, restituisce la derivata nel punto x al tempo t
// ===============================================================

class FunzioneVettorialeBase {

public:
  virtual vector<double> Eval(double t, const vector<double> & x) const = 0;
};

// ===============================================================
// Caso fisico concreto
// ===============================================================

class OscillatoreArmonico : public FunzioneVettorialeBase {

public:

  OscillatoreArmonico(double omega0) { m_omega0 = omega0; };

  vector<double> Eval(double t, const vector<double> &x) const {
		vector<double> velocityVector(x.size());
		for(int i=0; i<x.size()/2; i++){
			int posCoord=i;
			int posVel=i+x.size()/2;
			velocityVector[i]=x[posVel];
			velocityVector[posVel]=-pow(m_omega0, 2)*x[posCoord];
		}
		return velocityVector;

  }

private:
  double m_omega0;
};

class Pendolo : public FunzioneVettorialeBase {

public:

  Pendolo(double lunghezza) { m_lunghezza = lunghezza; };

  vector<double> Eval(double t, const vector<double> &x) const {
		vector<double> velocityVector(x.size());
		for(int i=0; i<x.size()/2; i++){
			int posCoord=i;
			int posVel=i+x.size()/2;
			velocityVector[i]=x[posVel];
			velocityVector[posVel]=-(g/m_lunghezza)*sin(x[posCoord]);
		}
		return velocityVector;

  }

private:
  double m_lunghezza;
	const double g=9.80665;
};

class OscillatoreArmonicoSmFr : public FunzioneVettorialeBase{
	public:
		//costruttori
		OscillatoreArmonicoSmFr(){;}
		OscillatoreArmonicoSmFr(double omega0, double omegaForzante, double coeffAttr){
			m_omega0=omega0;
			m_omegaForzante=omegaForzante;
			m_coeffAttr=coeffAttr;
		}
		//metodi
		void SetOmega0(double omega0){ m_omega0=omega0;};
		void SetOmegaForzante(double a){ m_omegaForzante=a;};
		void SetCoeffAttr(double a) {m_coeffAttr=a;};

		vector<double> Eval(double t, const vector<double> &x) const {
			vector<double> velocityVector(x.size());
			for(int i=0; i<x.size()/2; i++){
				int posCoord=i;
				int posVel=i+x.size()/2;
				velocityVector[i]=x[posVel];
				velocityVector[posVel]=-pow(m_omega0, 2)*x[posCoord]-m_coeffAttr*x[posVel]+sin(m_omegaForzante*t);
			}
			return velocityVector;

		}

		
	private:
		double m_omega0;
		double m_omegaForzante;
		double m_coeffAttr;
};
// ===============================================================
// Classe astratta per un integratore di equazioni differenziali
// ===============================================================

class EquazioneDifferenzialeBase {
public:
  virtual vector<double> Passo(double t, const vector<double> &x, double h, FunzioneVettorialeBase *f) const = 0;
};

// ===============================================================
// Integratore concreto, metodo di Eulero
// ===============================================================

class Eulero : public EquazioneDifferenzialeBase {
public:

  vector<double> Passo(double t, const vector<double> &x, double h, FunzioneVettorialeBase *f) const {

		vector<double> vectorEvaluatedPasso= x+f->Eval(h, x)*h;
		return vectorEvaluatedPasso;

  }
};

class RC : public EquazioneDifferenzialeBase {
public:
  vector<double> Passo(double t, const vector<double> &x, double h, FunzioneVettorialeBase *f) const {
		vector<double> K1=f->Eval(t,x);
		vector<double> K2=f->Eval(t+h*0.5,x+K1*0.5*h);
		vector<double> K3=f->Eval(t+0.5*h,x+K2*0.5*h);
		vector<double> K4=f->Eval(t+h,x+K3*h);

		return x+(K1+2.*K2+2.*K3+K4)*(h/6.);


  }
};


#endif // __EQ_DIFF__