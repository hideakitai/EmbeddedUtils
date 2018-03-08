#pragma once


namespace MatrixFunc
{

// C(m x l) = A(m × n) x B(n × l)
void MultiMatrix( const float * const A, const float * const B, int m, int n, int l, float * const C )
{
    int i, j, k;

    for( i=0; i<m; i++ ){
        for( j=0; j<l; j++ ){
            *( C+l*i+j ) = 0.0;
            for( k=0; k<n; k++ ){
                *( C+l*i+j ) += ( *( A+n*i+k ) )*( *( B+l*k+j ) );
            }
        }
    }
}

// C(m x l) = A(m × n) x B(n × l)
template <size_t m, size_t n, size_t l>
void MultiMatrix( const float (&A)[m][n], const float (&B)[n][l], float (&C)[m][l] )
{
    int i, j, k;

    for( i=0; i<m; i++ ){
        for( j=0; j<l; j++ ){
            C[i][j] = 0.0;
            for( k=0; k<n; k++ ){
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// cross product : X(3 x 1) = A(3×1) [cross] B(3×1)
void CrossMatrix( const float (&A)[3], const float (&B)[3], float (&X)[3] )
{
    X[0] = A[1]*B[2] - A[2]*B[1];
    X[1] = A[2]*B[0] - A[0]*B[2];
    X[2] = A[0]*B[1] - A[1]*B[0];
}


// transpose : A(m × n)
void TransMatrix( const float * const A, int m, int n, float * const A_trans )
{
    int i,j;
    for( i=0; i<m; i++ ){
        for( j=0; j<n; j++ ){
            *( A_trans+m*j+i ) = *( A+n*i+j );
        }
    }
}

// inverse : A (n x n)
void InvMatrix( const float * const A, int n, float * const A_inv )
{
    int i, j, k;
    float L[n][n], U[n][n], buf[n][n];

    // initialize
    for( i=0; i<n; i++ ){
        for( j=0; j<n; j++ ){
            U[i][j] = 0.0;
            if( i == j )	buf[i][j] = L[i][j] = 1.0;
            else			buf[i][j] = L[i][j] = 0.0;
        }
    }
    // LU decomposition
    for( i=0; i<n; i++ ){
        for( j=i; j<n; j++ ){
            U[i][j] = *( A+n*i+j );
            for( k=0; k<i; k++ ){
                U[i][j] -= L[i][k]*U[k][j]; // U = c[i][j]=a[i][j]-sigma(k=1,i-1)b[i][k]c[k][j] (i<=j)
            }
        }
        for( j=i+1; j<n; j++ ){
            L[j][i] = *( A+n*j+i );
            for( k=0; k<i; k++ ){
                L[j][i] -= L[j][k]*U[k][i]; // L = b[i][j]={a[i][j]-sigma(k=1,j-1)b[i][k]c[k][j]}/c[j][j] (i>j)
            }
            L[j][i] /= U[i][i];
        }
    }
    // calculate inverse : Ax = v
    for( k=0; k<n; k++ ){
        for( i=0; i<n; i++ ){
            for( j=0; j<i; j++ ){
                buf[i][k] -= L[i][j]*buf[j][k];
            }
        }
        for( i=n-1; i>=0; i-- ){
            *( A_inv+n*i+k ) = buf[i][k];
            for( j=n-1; j>i; j-- ){
                *( A_inv+n*i+k ) -= U[i][j]*( *( A_inv+n*j+k ) );
            }
            *( A_inv+n*i+k ) /= U[i][i];
        }
    }
}

template <size_t n>
void InvMatrix( const float (&A)[n][n], float (&A_inv)[n][n] )
{
    int i, j, k;
    float L[n][n], U[n][n], buf[n][n];

    // initialize
    for( i=0; i<n; i++ ){
        for( j=0; j<n; j++ ){
            U[i][j] = 0.0;
            if( i == j )    buf[i][j] = L[i][j] = 1.0;
            else            buf[i][j] = L[i][j] = 0.0;
        }
    }
    // LU decomposition
    for( i=0; i<n; i++ ){
        for( j=i; j<n; j++ ){
            U[i][j] = *( A+n*i+j );
            for( k=0; k<i; k++ ){
                U[i][j] -= L[i][k]*U[k][j]; // U = c[i][j]=a[i][j]-sigma(k=1,i-1)b[i][k]c[k][j] (i<=j)
            }
        }
        for( j=i+1; j<n; j++ ){
            L[j][i] = *( A+n*j+i );
            for( k=0; k<i; k++ ){
                L[j][i] -= L[j][k]*U[k][i]; // L = b[i][j]={a[i][j]-sigma(k=1,j-1)b[i][k]c[k][j]}/c[j][j] (i>j)
            }
            L[j][i] /= U[i][i];
        }
    }
    // calculate inverse : Ax = v
    for( k=0; k<n; k++ ){
        for( i=0; i<n; i++ ){
            for( j=0; j<i; j++ ){
                buf[i][k] -= L[i][j]*buf[j][k];
            }
        }
        for( i=n-1; i>=0; i-- ){
            A_inv[i][k] = buf[i][k];
            for( j=n-1; j>i; j-- ){
                *( A_inv+n*i+k ) -= U[i][j]*( *( A_inv+n*j+k ) );
            }
            A_inv[i][k] /= U[i][i];
        }
    }
}


// pseudo inverse : A (m x n)
void PInvMatrix( const float * const A, int m, int n, float * const A_pseudo )
{
    int k;
    if( m < n ) k = m;
    else        k = n;
    float A_trans[n][m], AA_trans[k][k], AA_inv[k][k];

    TransMatrix( A, m, n, *A_trans );
    if( m < n ){ // rank = m : A+ = A_trans*(A*A_trans)_inv
        MultiMatrix( A, *A_trans, m, n, m, *AA_trans );
        InvMatrix( *AA_trans, m, *AA_inv );
        MultiMatrix( *A_trans, *AA_inv, n, m, m, A_pseudo );
    }else{ // rank = n : A+ = (A_trans*A)_inv*A_trans
        MultiMatrix( *A_trans, A, n, m, n, *AA_trans );
        InvMatrix( *AA_trans, n, *AA_inv );
        MultiMatrix( *AA_inv, *A_trans, n, n, m, A_pseudo );
    }
}

// pseudo inverse : A (m x n)
template <size_t m, size_t n, size_t k = m < n ? m : n>
void PInvMatrix( const float (&A)[m][n], float (&A_pseudo)[n][m] )
{
    float A_trans[n][m], AA_trans[k][k], AA_inv[k][k];

    TransMatrix( A, m, n, *A_trans );
    if( m < n ){ // rank = m : A+ = A_trans*(A*A_trans)_inv
        MultiMatrix( A, A_trans, AA_trans );
        InvMatrix( AA_trans, AA_inv );
        MultiMatrix( A_trans, AA_inv, A_pseudo );
    }else{ // rank = n : A+ = (A_trans*A)_inv*A_trans
        MultiMatrix( A_trans, A, AA_trans );
        InvMatrix( AA_trans, AA_inv );
        MultiMatrix( AA_inv, A_trans, A_pseudo );
    }
}


// weighted pseudo inverse : A(m x n) & W(n x l)
void WPInvMatrix( const float * const A, const float * const W, int m, int n, int l, float * const A_wp )
{
    float A_trans[n][m], W_inv[l][l];
    float AW[m][l], AWA[m][m], AWA_inv[m][m], WA[l][m];

    TransMatrix( A, m, n, *A_trans );
    InvMatrix( W, l, *W_inv );

    MultiMatrix( A, *W_inv, m, n, l, *AW );
    MultiMatrix( *AW, *A_trans, m, l, m, *AWA );
    InvMatrix( *AWA, m, *AWA_inv );

    MultiMatrix( *W_inv, *A_trans, l, l, m ,*WA );

    MultiMatrix( *WA, *AWA_inv, l, m, m, A_wp );

}

// weighted pseudo inverse : A(m x n) & W(n x l)
template <size_t m, size_t n, size_t l>
void WPInvMatrix( const float (&A)[m][n], const float (&W)[n][l], float (&A_wp)[l][m] )
{
    float A_trans[n][m], W_inv[l][l];
    float AW[m][l], AWA[m][m], AWA_inv[m][m], WA[l][m];

    TransMatrix( A, A_trans );
    InvMatrix( W, W_inv );

    MultiMatrix( A, W_inv, AW );
    MultiMatrix( AW, A_trans, AWA );
    InvMatrix( AWA, AWA_inv );

    MultiMatrix( W_inv, A_trans, WA );

    MultiMatrix( WA, AWA_inv, A_wp );

}
}