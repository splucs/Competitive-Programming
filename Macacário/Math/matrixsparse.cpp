vector< vector<int> > adjA, adjB;

matrix sparsemult(matrix a, matrix b) {
	int n = (int)a.size();
	if (a[0].size() != b.size()) printf("fail\n");
	int m = (int)b.size();
	int p = (int)b[0].size();
	adjA.resize(n);
	for(int i=0; i<n; i++) {
		adjA[i].clear();
		for(int k=0; k<m; k++) {
			if (fabs(a[i][k]) > EPS) adjA[i].push_back(k);
		}
	}
	adjB.resize(p);
	for(int j=0; j<p; j++) {
		adjB[j].clear();
		for(int k=0; k<m; k++) {
			if (fabs(b[k][j]) > EPS) adjB[j].push_back(k);
		}
	}
	matrix c;
	c.resize(n);
	for(int i=0; i<n; i++) {
		c[i].assign(p, 0);
		for(int j=0; j<p; j++) {
			for(int u=0, v=0, k; u<(int)adjA[i].size() && v<(int)adjB[j].size();) {
				if (adjA[i][u] > adjB[j][v]) v++;
				else if (adjA[i][u] < adjB[j][v]) u++;
				else {
					k = adjA[i][u];
					c[i][j] += a[i][k]*b[k][j];
					u++; v++;
				}
			}
		}
	}
	return c;
}