template<int MOD>
struct ModInt{
    int v;
    ModInt(long long _v=0){
        _v%=MOD;
        if(_v<0) _v+=MOD;
        v=_v;
    }

    ModInt& operator+=(const ModInt &o){
        v+=o.v;
        if(v>=MOD) v-=MOD;
        return *this;
    }

    ModInt& operator-=(const ModInt &o){
        v-=o.v;
        if(v<0) v+=MOD;
        return *this;
    }

    ModInt& operator*=(const ModInt &o){
        v=1LL*v*o.v%MOD;
        return *this;
    }

    static ModInt qpow(ModInt a,long long e){
        ModInt r=1;
        while(e){
            if(e&1) r*=a;
            a*=a;
            e>>=1;
        }
        return r;
    }

    ModInt inv()const{
        return qpow(*this,MOD-2);
    }

    ModInt& operator/=(const ModInt &o){
        return (*this)*=o.inv();
    }

    friend ModInt operator+(ModInt a,const ModInt &b){ return a+=b; }
    friend ModInt operator-(ModInt a,const ModInt &b){ return a-=b; }
    friend ModInt operator*(ModInt a,const ModInt &b){ return a*=b; }
    friend ModInt operator/(ModInt a,const ModInt &b){ return a/=b; }

    friend bool operator==(const ModInt &a,const ModInt &b){
        return a.v==b.v;
    }

    friend bool operator!=(const ModInt &a,const ModInt &b){
        return a.v!=b.v;
    }

    friend ostream& operator<<(ostream &os,const ModInt &a){
        return os<<a.v;
    }

    friend istream& operator>>(istream &is,ModInt &a){
        long long x;
        is>>x;
        a=ModInt(x);
        return is;
    }
};
const int mod=998244353;
using mint=ModInt<mod>;
