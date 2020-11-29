/************************************************************************************************/
/*** Topic: Sync calculation                                                                  ***/
/***                                                                         Ali-Seif         ***/
/*** Version Release 17.12 rev 11256                                                          ***/
/*** Date: 11/29/2020                                                                         ***/
/*** Code implemented in CodeBlocks C++ compiler (v. 17.12),                                  ***/
/*** MSI: PX60 6QD/ DDR4                                                                      ***/
/*** Run under a Intel� Core� i7-6700HQ CPU @ 2.60GHz � 64 based processor with 16 GB RAM     ***/
/************************************************************************************************/
#include <iostream>
#include <fstream>//for ifstream
#include <math.h> //for pow()
#include <sstream>   //for stringstream
using namespace std;
//##############################################################
//####                                                      ####
//####           Calculate the interspike distance          ####
//####                                                      ####
//##############################################################
float dif(float t[],int i)
{
    float x;
    x=t[i+1]-t[i];
    return   x;
}
//##############################################################
//####                                                      ####
//####                Sync calculation                      ####
//####                                                      ####
//##############################################################
float isi(float mean_tau,float mean_tau2,int N)
{
    float B ;
    float mean2_tau=pow(mean_tau,2);
    B=((((pow((mean_tau2-mean2_tau),0.5))/(mean_tau)))-1)/(1/pow(N,0.5));
    return   B;
}
//##############################################################
//####                                                      ####
//####          Calculation of mean and variance            ####
//####                                                      ####
//##############################################################
float synchrony(float Array[],int N,int size_spike)
{
    float x;
    float tau[size_spike]=    {0.0};
    float tau2[size_spike]=    {0.0};
    float mean_tau=0.0;
    float mean_tau2=0.0;
    for (int i=1 ; i<=size_spike-1;i++){
        tau[i]=dif(Array,i);
        tau2[i]=tau[i]*tau[i];
        mean_tau=mean_tau+tau[i];
        mean_tau2=mean_tau2+tau2[i];
    }
    mean_tau=mean_tau/(size_spike-1);
    mean_tau2=mean_tau2/(size_spike-1);
    //cout<<mean_tau2<<'\t'<<2*pow(mean_tau,2);
    x=isi(mean_tau,mean_tau2,N);
    return   x;
}
//##############################################################
//####                                                      ####
//####                     fill array                       ####
//####                                                      ####
//##############################################################
float *fillarr( float arr[] ) {
    return arr;
}
//##############################################################
//####                                                      ####
//####              Convert file to array                   ####
//####                                                      ####
//##############################################################
float *readfile(int neurun) {
//_______________________________________________
//___________________Read file___________________
//_______________________________________________
	std::string s;
	std::stringstream ss;
	ss << neurun;
	ss >> s;
    std::string scheme ("spike");
    std::string hostname;
    std::string url;
    hostname = s+".txt" ;
    url = scheme + hostname;
    char* char_arr;
    string str_obj(url);
    char_arr = &str_obj[0];
    char * filename = char_arr;
//_______________________________________________
//__________Calculation of Size Spike____________
//_______________________________________________
    ifstream myfile1 (filename);
    string line1;
    string size1;
    getline (myfile1,line1);
    size1=line1;
    stringstream geek1(size1);
    int size_spike = 0;
    geek1 >> size_spike;
//_______________________________________________
//___________Convert File to Array_______________
//_______________________________________________
    string myArray[size_spike+1];
    float Array[size_spike+1];
    Array[0]=size_spike;
    for(int i = 1; i < size_spike+1; ++i){
        myfile1 >> myArray[i];
        stringstream geek(myArray[i]);
        geek >> Array[i];
        //cout<<i<<'\t'<<Array[i]<<endl;
    }
    myfile1.close();
//_______________________________________________
//___________Convert Array to Array______________
//_______________________________________________
    float *nn = fillarr(Array);
    return   nn;
}

//_______________________________________________________________________________________\\
//_____________                                                             _____________\\
//_____________                                      @                      _____________\\
//_____________           @@       @@       @            @@     @           _____________\\
//_____________           @ @     @ @      @ @       @   @ @    @           _____________\\
//_____________           @  @   @  @     @   @      @   @  @   @           _____________\\
//_____________           @   @@@   @    @@@@@@@     @   @   @  @           _____________\\
//_____________           @    @    @   @       @    @   @    @ @           _____________\\
//_____________           @         @  @         @   @   @     @@           _____________\\
//_______________________________________________________________________________________\\

int main ()
{

    int N=3;
    int a=1;
    cout<<synchrony(readfile(a),N,readfile(a)[0]);

    return 0;
}
