#include "GLMMF.h"
// [[Rcpp::depends(RcppArmadillo)]]

double scaling(const int dist, const arma::mat& y, const arma::mat& u,const arma::mat& theta,
const arma::mat& ytilde, const arma::mat& H){
  
  double res=0.0;  
  switch (dist) {       
    case 2:    
    for(unsigned int i=0; i<y.n_elem; i++){
      if(arma::is_finite(y(i))){
        res += R::dpois( y(i), exp(theta(i))*u(i), 1) - R::dnorm( ytilde(i), theta(i), sqrt(H(i)), 1);
      }
    }
    break;    
    case 3:
    for(unsigned int i=0; i<y.n_elem; i++){
      if(arma::is_finite(y(i))){
        res += R::dbinom( y(i), u(i), exp(theta(i))/(1.0+exp(theta(i))), 1)- R::dnorm( ytilde(i), theta(i), sqrt(H(i)), 1);
      }
    }
    break;
    case 4:
    for(unsigned int i=0; i<y.n_elem; i++){
      if(arma::is_finite(y(i))){
        res += R::dgamma( y(i), u(i), exp(theta(i))/u(i), 1)- R::dnorm( ytilde(i), theta(i), sqrt(H(i)), 1);
      }
    }
    break;
    case 5:
    for(unsigned int i=0; i<y.n_elem; i++){
      if(arma::is_finite(y(i))){
        res += Rf_dnbinom_mu( y(i), u(i), exp(theta(i)), 1)- R::dnorm( ytilde(i), theta(i), sqrt(H(i)), 1);
      }
    }
    break;    
  }
  return res;
}