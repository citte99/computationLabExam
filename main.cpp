#include <iostream>
#include "Funzioni.h"
#include "AlgoZeri.h"
#include "Integral.h"
#include "VectorOperations.h"
#include "EquazioniDifferenziali.h"
#include "RandomGen.h"

#include "TApplication.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TGraph.h"
#include "TAxis.h"

using namespace std;

class punto6 {
public:
	punto6(double prec0);
	double getXMin(){return m_xMin;}
	double getXMax(){return m_xMax;}
	double getPrec0(){return m_prec0;}
	double getTrap10(){return m_trap10;}
	double getErr(){return m_err;}
	double trap10Random(RandomGen*);
private:
	double m_xMin, m_xMax, m_prec0, m_trap10, m_err;
};

int main(){
// punto 1 ===============
FunzioneCompito* myFun= new FunzioneCompito();
Bisezione* myBisez= new Bisezione();
myBisez->SetPrecision(0.1);
myBisez->SetMaxIteraz(10000000);
double intervallo1Left=0.;
double intervallo1Right=1.;
double intervallo2Left=5.;
double intervallo2Right=6.;
double xMin=myBisez->CercaZeri(intervallo1Left, intervallo1Right, myFun);
double xMax=myBisez->CercaZeri(intervallo2Left, intervallo2Right, myFun);

cout << "Point 1 : xMin = " << xMin << "  xMax = " << xMax << endl;
cout<<endl;

// punto 2 ===============
Integral* integrator = new Integral(xMin,xMax, myFun);
double integrale10Step=integrator->Trapezoidi(10);
cout << "Point 2 : Integral = " << integrale10Step << endl;
cout << endl;

// punto 3 ===============
double stimaErr=4./3.*fabs(integrator->Trapezoidi(20)-integrator->Trapezoidi(10));
 cout << "Point 3 : Error = " << stimaErr<< endl;
 cout<<endl;

// punto 4 ===============
double k=stimaErr/(pow((xMax-xMin)/10., 2));
double hNeeded=sqrt(0.002/k);
int ninttp=(int)((xMax-xMin)/hNeeded);
 cout << "Point 4 :" << ninttp << " intervals are needed to obtain a 0.002 accuracy with the trapeze method." <<  endl;
 cout<<endl;
// punto 5 ===============
RandomGen* myGen=new RandomGen(1);
int nintmd=integrator->MonteCarloMediaFixedPrecCustom(0.002, myGen);

cout << "Point 5 : " << nintmd << " points are needed to reach an accuracy of 0.002 with the mean value method." <<  endl;
cout<<endl;

// punto 6 ===============
punto6 evalPrec01(0.1);
punto6 evalPrec007(0.07);
punto6 evalPrec005(0.05);
punto6 evalPrec003(0.03);
punto6 evalPrec001(0.01);
cout << "Point 6 : precision = " << evalPrec01.getPrec0() << " integral = " << evalPrec01.getTrap10()  << "  error = " << evalPrec01.getErr() << endl;
cout << "Point 6 : precision = " << evalPrec007.getPrec0() << " integral = " << evalPrec007.getTrap10()  << "  error = " << evalPrec007.getErr() << endl;
cout << "Point 6 : precision = " << evalPrec005.getPrec0() << " integral = " << evalPrec005.getTrap10()  << "  error = " << evalPrec005.getErr() << endl;
cout << "Point 6 : precision = " << evalPrec003.getPrec0() << " integral = " << evalPrec003.getTrap10()  << "  error = " << evalPrec003.getErr() << endl;
cout << "Point 6 : precision = " << evalPrec001.getPrec0() << " integral = " << evalPrec001.getTrap10()  << "  error = " << evalPrec001.getErr() << endl;
cout<<endl;


// punto 7 ===============
double devSt01;
double devSt007;
double devSt005;
double devSt003;
double devSt001;
double av01;
double av007;
double av005;
double av003;
double av001;
{
	punto6 evalPrec=evalPrec01; 
	TH1F randomTrap("placeholder","placeholder", 1, 0, 1);
	for(int i=0; i<1000; i++){
		randomTrap.Fill(evalPrec.trap10Random(myGen));
	}
	devSt01=randomTrap.GetRMS();
	av01=randomTrap.GetMean();

}

{
	punto6 evalPrec=evalPrec007; 
	TH1F randomTrap("placeholder","placeholder", 1, 0, 1);
	for(int i=0; i<1000; i++){
		randomTrap.Fill(evalPrec.trap10Random(myGen));
	}
	devSt007=randomTrap.GetRMS();
	av007=randomTrap.GetMean();

}

{
	punto6 evalPrec=evalPrec005; 
	TH1F randomTrap("placeholder","placeholder", 1, 0, 1);
	for(int i=0; i<1000; i++){
		randomTrap.Fill(evalPrec.trap10Random(myGen));
	}
	devSt005=randomTrap.GetRMS();
	av005=randomTrap.GetMean();

}

{
	punto6 evalPrec=evalPrec003;
	TH1F randomTrap("placeholder","placeholder", 1, 0, 1);
	for(int i=0; i<1000; i++){
		randomTrap.Fill(evalPrec.trap10Random(myGen));
	}
	devSt003=randomTrap.GetRMS();
	av003=randomTrap.GetMean();
}

{
	punto6 evalPrec=evalPrec001; 
	TH1F randomTrap("placeholder","placeholder", 1, 0, 1);
	for(int i=0; i<1000; i++){
		randomTrap.Fill(evalPrec.trap10Random(myGen));
	}
	devSt001=randomTrap.GetRMS();
	av001=randomTrap.GetMean();

}
cout << "Point 7 : precision = " << evalPrec01.getPrec0() << " integral = "  <<av01<<" standard deviation = "<< devSt01<<endl;
cout << "Point 7 : precision = " << evalPrec007.getPrec0() << " integral = " <<av007<<" standad deviation = "<<devSt007<<endl;
cout << "Point 7 : precision = " << evalPrec005.getPrec0() << " integral = " <<av005<<" standard deviation = "<<devSt005<<endl;
cout << "Point 7 : precision = " << evalPrec003.getPrec0() << " integral = " <<av003<<" standard deviation = "<<devSt003<<endl;
cout << "Point 7 : precision = " << evalPrec001.getPrec0() << " integral = " <<av001<<" standard deviation = "<<devSt001<<endl;
//}
	return 0;
}


punto6::punto6(double prec0){
	m_prec0=prec0;
	FunzioneCompito* myFun= new FunzioneCompito();
	Bisezione* myBisez= new Bisezione();
	myBisez->SetPrecision(m_prec0);
	myBisez->SetMaxIteraz(10000000);
	double intervallo1Left=0.;
	double intervallo1Right=1.;
	double intervallo2Left=5.;
	double intervallo2Right=6.;
	m_xMin=myBisez->CercaZeri(intervallo1Left, intervallo1Right, myFun);
	m_xMax=myBisez->CercaZeri(intervallo2Left, intervallo2Right, myFun);
	Integral* integrator = new Integral(m_xMin,m_xMax, myFun);
	m_trap10=integrator->Trapezoidi(10);
	m_err=4./3.*fabs(integrator->Trapezoidi(20)-integrator->Trapezoidi(10));

}

double punto6::trap10Random(RandomGen* myGen){
	FunzioneCompito* myFun= new FunzioneCompito();
	double leftRandom=myGen->Unif(m_xMin-m_prec0/2., m_xMin+m_prec0/2.);
	double rightRandom=myGen->Unif(m_xMax-m_prec0/2., m_xMax+m_prec0/2.);
	Integral* integrator = new Integral(leftRandom ,rightRandom, myFun);
	return integrator->Trapezoidi(10);
}

