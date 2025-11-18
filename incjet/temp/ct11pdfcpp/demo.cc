//----demo file for the using of CTEQPDF c++ inteface-----
#include <cstdlib>
#include <vector>
#include <string>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <math.h>
#include <time.h>
#include <ct11pdf.h>
//-------------------------------------------------

using namespace std;
//-------------------------------------------------

int main() {

//---name of the CTEQ pds file------ 
  string it1="ct10nn.00.pds"; // new format
  string it2="ctq66.00.pds"; //old format

//---define a PDF table-------
  cteqpdf ct10nn, ctq66;

//---initializing the PDF table-----
  cout <<endl;
  cout <<endl;
  ct10nn.setct11(it1);
  ctq66.setct11(it2);

//---get the parton distribution functions----
  double x=0.01, Q=91.187;
  double pg1, pg2;

  cout <<endl;
  cout <<endl;

  pg1=ct10nn.parton(0, x, Q);
  pg2=ctq66.parton(0, x, Q);
  cout << "Gluon PDFs at Q="<<Q<<" and x="<<x <<endl;
  cout << "For "<<ct10nn.filepds<< " g="<<pg1<<endl;
  cout << "For "<<ctq66.filepds<< " g="<<pg2<<endl;
  cout <<endl;

  pg1=ct10nn.parton(1, x, Q);
  pg2=ctq66.parton(1, x, Q);
  cout << "u quark PDFs at Q="<<Q<<" and x="<<x <<endl;
  cout << "For "<<ct10nn.filepds<< " u="<<pg1<<endl;
  cout << "For "<<ctq66.filepds<< " u="<<pg2<<endl;
  cout <<endl;

  pg1=ct10nn.parton(2, x, Q);
  pg2=ctq66.parton(2, x, Q);
  cout << "d quark PDFs at Q="<<Q<<" and x="<<x <<endl;
  cout << "For "<<ct10nn.filepds<< " d="<<pg1<<endl;
  cout << "For "<<ctq66.filepds<< " d="<<pg2<<endl;
  cout <<endl;

  pg1=ct10nn.parton(3, x, Q);
  pg2=ctq66.parton(3, x, Q);
  cout << "s quark PDFs at Q="<<Q<<" and x="<<x <<endl;
  cout << "For "<<ct10nn.filepds<< " s="<<pg1<<endl;
  cout << "For "<<ctq66.filepds<< " s="<<pg2<<endl;
  cout <<endl;

  pg1=ct10nn.parton(4, x, Q);
  pg2=ctq66.parton(4, x, Q);
  cout << "c quark PDFs at Q="<<Q<<" and x="<<x <<endl;
  cout << "For "<<ct10nn.filepds<< " c="<<pg1<<endl;
  cout << "For "<<ctq66.filepds<< " c="<<pg2<<endl;
  cout <<endl;

  pg1=ct10nn.parton(5, x, Q);
  pg2=ctq66.parton(5, x, Q);
  cout << "b quark PDFs at Q="<<Q<<" and x="<<x <<endl;
  cout << "For "<<ct10nn.filepds<< " b="<<pg1<<endl;
  cout << "For "<<ctq66.filepds<< " b="<<pg2<<endl;
  cout <<endl;

//---get the alphas value (only for new formats, otherwise
//--------will cause an exit of the program)----
  double al;
  al=ct10nn.alphas(Q);
  cout << "\n"<<"\n"<<"Alphas at Q="<<Q<<endl;
  cout << "For "<<ct10nn.filepds<< " as="<<al<<endl;

//---get the quark masses
  double mu, md, ms, mc ,mb, mt;
  mu=ct10nn.amass[0];
  md=ct10nn.amass[1];
  ms=ct10nn.amass[2];
  mc=ct10nn.amass[3];
  mb=ct10nn.amass[4];
  mt=ct10nn.amass[5];
  cout << "\n"<<"\n"<<"quark masses" << " u" << " d"<< " s"<< " c"<< " b"<<" t"<<endl;
  cout << mu<<" "<< md<<" "<< ms <<" "<< mc<< " "<< mb<<" "<<mt<<endl;

//---other QCD parameters
  int IO;
  double Qc, Ac;
  IO=ct10nn.Iorder;
  Qc=ct10nn.Qalfa;
  Ac=ct10nn.AlfaQ;
  cout << "\n"<<"\n"<<"Order of PDFs " << IO<<endl;
  cout << "standard alphas at Q= "<<Qc<<": as=="<<Ac<<endl; 
  

//  string fname="ctq66c.out";
//  ofstream infile;
//  infile.open(fname.c_str());

//---test of speed----
  time_t t1=time(0);
  for (int i=1; i<=201; i++) {
	  for (int j=1; j<=201; j++) {
		  x=exp(log(10.)*(-5.*(i-1)/200.));  
		  Q=exp(log(10.)*(4.*(i-1)/200.));
		  for (int k=-5; k<=5; k++) {
			  pg1=ct10nn.parton(k, x, Q);
//			  infile <<scientific<<setprecision(8)<<pg1 <<endl;
		  }
	  }
  }
  time_t t2=time(0);
  double d=difftime(t2, t1);
  cout << "It took "<< d << " seconds"<<endl;

//  infile.clear();
//  infile.close();


//---release the PDF tables
  cout <<endl;
  cout <<endl;
  ct10nn.pdfexit();
  ctq66.pdfexit();

  return 0;
}

