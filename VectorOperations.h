#ifndef __VectorOperations_h__
#define __VectorOperations_h__
#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>  // se se vogliono usare algoritmi STL
#include <numeric>    // std::inner_product

// ===============================================================================
// Nel namespace myVectAlgebra potremmo ridefinire gli operatori matematici che coinvolgono
// vettori e scalari
// ===============================================================================

// somma di due vettori : somma componente per componente

template <typename T> std::vector<T> operator+(const std::vector<T> &a, const std::vector<T> &b) {
  
  assert(a.size() == b.size()&&"i due vettori sommati non hanno la stessa dimensione");  
  std::vector<T> result(a.size());
  std::transform(a.begin(), a.end(), b.begin(), result.begin() , std::plus<T>()); 
  
  return result;
  
}

// differenza di due vettori componente per componente
// [ preferisco re-implementarlo perche' si fanno meno operazioni rispetto result = a + (-1.*b) ]

template <typename T> std::vector<T> operator-(const std::vector<T> &a, const std::vector<T> &b) {
  
  assert(a.size() == b.size()&&"i due vettori sommati non hanno la stessa dimensione");  
  std::vector<T> result(a.size());
  std::transform(a.begin(), a.end(), b.begin(), result.begin() , std::minus<T>()); 
  
  return result;
  
}

// ===============================================================================  
// prodotto scalare tra due vettori 
// ===============================================================================

template <typename T> T operator*(const std::vector<T> &a, const std::vector<T> &b) {
  
 // ==>> da completare ( anche se non serve esplictamente per questo progetto )
 assert(a.size() == b.size()&&"i due vettori moltiplicati scalarmente non hanno la stessa dimensione");
 T result=std::inner_product(std::begin(a), std::end(a), std::begin(b), 0.0);
 return result;
  
}

// ===============================================================================
// prodotto tra uno scalare e un vettore
// ===============================================================================

template <typename T> std::vector<T> operator*( T c , const std::vector<T> &a) {
  
 // ==>> da completare 
  std::vector<T> result(a.size());
  std::transform(a.begin(), a.end(), result.begin() , [c](const double& z){return c*z;});
	return result;
}

// ===============================================================================
// prodotto tra un vettore e uno scalare 
// ===============================================================================

template <typename T> std::vector<T> operator*( const std::vector<T> &a , T c) {
  
 // ==>> da completare
  std::vector<T> result(a.size());
  std::transform(a.begin(), a.end(), result.begin() , [c](const double& z){return c*z;});
	return result;
}


// ===============================================================================
// somma ad a un vettore b e il risultato viene messo in a
// ===============================================================================

template <typename T> std::vector<T>& operator+=(std::vector<T>& a, const std::vector<T>& b) {
  
  assert(a.size() == b.size()&&"i due vettori sommati non hanno la stessa dimensione");  
  std::transform(a.begin(), a.end(), b.begin(), a.begin() , std::plus<T>()); 
  
  return a;
}

// ===============================================================================
// sottrai ad a un vettore b e il risultato viene messo in a
// ===============================================================================

template <typename T> std::vector<T>& operator-=(std::vector<T>& a, const std::vector<T>& b) {
  
  assert(a.size() == b.size()&&"i due vettori sottratti non hanno la stessa dimensione");   
  std::transform(a.begin(), a.end(), b.begin(), a.begin() , std::minus<T>()); 
  
  return a;
}

template <typename T> void printVector(const std::vector<T>& v){
	for(int i=0; i<v.size(); i++){
		std::cout<<v[i]<<" ";
	}
	std::cout<<std::endl;
}
#endif//__VectorOperations_h__