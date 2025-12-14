/*
  P(x) / Q(x) = ( P(x) * Q(-x) ) / ( Q(x) * Q(-x) )
= ( U_0(x^2) + x * U_1(x^2) ) / V(x^2)
[x^k](P(x)/Q(x)) = [x^floor(k/2)](U_(k%2)(x)/V(x))
*/
LL BM(Poly P,Poly Q,LL k){ // Bostan Mori, [x^k](P(x)/Q(x))
	while(k>0){
		Poly Q_neg=Q;
		for(int i=1;i<(int)Q.size();i+=2){
			Q_neg[i]=NTT::mo-Q[i];
		}
		Poly U=poly_mul(P,Q_neg); P.clear();
		for(int i=k&1;i<(int)U.size();i+=2){
			P.emplace_back(U[i]);
		}
		Poly V=poly_mul(Q,Q_neg); Q.clear();
		for(int i=0;i<(int)V.size();i+=2){
			Q.emplace_back(V[i]);
		}
		k>>=1;
	}
	return P[0]*qpow(Q[0],NTT::mo-2,NTT::mo)%NTT::mo;
}