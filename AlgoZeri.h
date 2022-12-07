/*
The algorithms to find zeros of a function are coded here. The base class Solutore represents a generic algorithm. Concrete algorithms ( Bisezione, Secanti and Newton ) derive from the baseclass
*/

#ifndef __AlgoZeri_h__
#define __AlgoZeri_h__

#include "Funzioni.h"

class Solutore{

public:
	virtual ~Solutore(){;};
  virtual double CercaZeri(double xmin, double xmax, const FunzioneBase* f)=0;
  void SetPrecision(double epsilon) {m_prec = epsilon;};
  double GetPrecision() const {return m_prec;};
	void SetMaxIteraz(int a){maxIteraz=a;};

protected:
	double m_a, m_b;
  double m_prec=0.001;
	int maxIteraz=1E6;

};

class Bisezione: public Solutore {

public:
	Bisezione(){;};
	~Bisezione(){;};
  virtual double CercaZeri(double xmin, double xmax, const FunzioneBase* f);
 
};



#endif