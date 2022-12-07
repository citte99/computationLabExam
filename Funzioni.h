/*
The representation of a function is coded here. Base class
and derived classes can be found 
*/

#ifndef __funzioni_h__
#define __funzioni_h__

#include <cmath>

class FunzioneBase{

public:

  virtual double Eval(double x) const = 0;

};

class Parabola: public FunzioneBase{

public:

  Parabola();
  Parabola(double a, double b, double c);
  ~Parabola(){;};
  
  void setA(double a) {m_a = a;};
  void setB(double b) {m_b = b;};
  void setC(double c) {m_c = c;};
  double getA() const {return m_a;};
  double getB() const {return m_b;};
  double getC() const {return m_c;};
	double getVertice() const{return -m_b/(2*m_a);};
	
	virtual double Eval(double x) const {return m_a*x*x + m_b*x + m_c;};

private:

  double m_a, m_b, m_c;

};


class funzioneEsercizio2: public FunzioneBase{

public:
	
	virtual double Eval(double x) const {return 3*pow(x,2)+5.*x-2.;};

};

class funzioneEsercizio3: public FunzioneBase{

public:
	
	virtual double Eval(double x) const {return sin(x)-x*cos(x);};

};

class Seno: public FunzioneBase{

public:
	
	virtual double Eval(double x) const {return sin(x);};

};

class FunzioneCompito: public FunzioneBase{
	
public:
	virtual double Eval(double x) const {return (6*pow(sin(x), 2)-2*cos(x))/(1.+0.1*x);}
};


#endif