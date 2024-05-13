vector<int> calcular_divisores(int numero) {
	vector<int> divisores;
	for( int i=1; i*i <= numero; i++ ) {
		if( numero%i == 0 ) {
			divisores.push_back(i);
			if( i*i != numero ) {
				divisores.push_back(numero/i);
			}
		}
	}
	return divisores;
}