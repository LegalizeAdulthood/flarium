// cmplx.h
#include "math.h"

#define maxterm 100
#define abstol 1.e-10
#define reltol 1.e-5
#define zerotol 1.e-100    // 1.e-34
#define errorcode -1.e60
#define pi 3.141592653589793238462643383279
#define rad 57.2958
#define lim 15.
// #define max(a,b) ((a)>(b)?(a):(b))
#define infinite_loop for(;;)
#define rabs(x) ((x)<0.? -(x):(x))
#define ABS(X) rabs(X)
#define topexp 350.
#define expo 2.7183

class cmplx
{
  public: 
      double x,y;
			double bio;
	public:

       //cmplx( double xx , double yy) //create
       //  { x=xx;y=yy;}
       //cmplx() //create
       //  { x=0.;y=0.;}

      cmplx( double xx , double yy); //create
      cmplx(); //create

      inline void operator=(cmplx rvalue)
         {x=rvalue.x;y=rvalue.y;}
      inline void operator-=(cmplx rvalue)
         {x-=rvalue.x;y-=rvalue.y;}
      inline void operator+=(cmplx rvalue)
         {x+=rvalue.x;y+=rvalue.y;}
      inline void operator*=(cmplx rvalue)
         {
          *this=cmplx(rvalue.x*x-rvalue.y*y, 
            rvalue.x*y+rvalue.y*x);
         }
      inline void operator*=(double rvalue)
         {
					*this=cmplx(rvalue*x, rvalue*y);
         }
      inline cmplx operator+(cmplx rvalue)
         {return cmplx(x+rvalue.x,y+rvalue.y);}
      inline cmplx operator-(cmplx rvalue)
         {return cmplx(x-rvalue.x,y-rvalue.y);}
      inline cmplx operator-() //unary minus
         {return cmplx(-x,-y);}
      inline cmplx operator*(cmplx rvalue)
        {
					return cmplx(rvalue.x*x-rvalue.y*y,
							         rvalue.x*y+rvalue.y*x);
				}
      inline friend cmplx operator/(double dividend,cmplx divisor)
         { 
					//static double temp;

					//////////////////////////////////////////
					if (divisor.x < zerotol && divisor.x > -zerotol)
					{
						if (divisor.x >= 0)
							divisor.x = zerotol;
						else
							divisor.x = -zerotol;					
					}

					if (divisor.y < zerotol && divisor.y > -zerotol)
					{
						if (divisor.y >= 0)
							divisor.y = zerotol;
						else
							divisor.y = -zerotol;					
					}
					//////////////////////////////////////////	

					//temp=1./(divisor.x*divisor.x+divisor.y*divisor.y);
          // return cmplx((dividend*divisor.x)*temp,
          // (-dividend*divisor.y)*temp);

					//temp=1./(divisor.x*divisor.x+divisor.y*divisor.y);
          return cmplx((dividend*divisor.x)/(divisor.x*divisor.x+divisor.y*divisor.y),
           (-dividend*divisor.y)/(divisor.x*divisor.x+divisor.y*divisor.y));
         }
      inline cmplx operator/(cmplx divisor)
				{ 
					//static double temp;

					//////////////////////////////////////////
					if (divisor.x < zerotol && divisor.x > -zerotol)
					{
						if (divisor.x >= 0)
							divisor.x = zerotol;
						else
							divisor.x = -zerotol;					
					}

					if (divisor.y < zerotol && divisor.y > -zerotol)
					{
						if (divisor.y >= 0)
							divisor.y = zerotol;
						else
							divisor.y = -zerotol;					
					}
					//////////////////////////////////////////	

				 //temp=1./(divisor.x*divisor.x+divisor.y*divisor.y);
         //      return cmplx((divisor.x*x+divisor.y*y)*temp,
         //   (divisor.x*y-divisor.y*x)*temp);
				 
					//temp=1./(divisor.x*divisor.x+divisor.y*divisor.y);
         return cmplx((divisor.x*x+divisor.y*y)/(divisor.x*divisor.x+divisor.y*divisor.y),
            (divisor.x*y-divisor.y*x)/(divisor.x*divisor.x+divisor.y*divisor.y));
         }
      inline int operator==(cmplx rvalue)
         {return (x==rvalue.x && y==rvalue.y);}
      
			inline double real() {return x;}
      inline double imaginary() {return y;}
      inline double imag() {return y;}
			inline double abs() {return (x*x+y*y);}
//			inline double magnitude() {return sqrt(x*x+y*y);}

//			inline cmplx cexp() {
//				return cmplx(exp(x)*cos(y),exp(x)*sin(y));}

//			inline cmplx clog() {
//				return cmplx(log(fabs((*this).magnitude())),atan2(y,x));}

//			inline cmplx csin() { // !!!!!!!!!
//				return cmplx(.5*(exp(y)+1./exp(y))*sin(x),cos(x)*.5*(exp(y)-1./exp(y)));}

			inline cmplx unknown() { // suppose to be sine
				return cmplx(.5*(exp(y)+1./exp(y))*sin(x),cos(x)*.5*(exp(y)-1./exp(y)));}

//			inline cmplx csin() 
//			{ // !!!!!!!!!
//				static double z,zi,sinh,cosh;
//				static BOOL bug = TRUE;

				//if( y> topexp)
	 			//	return cmplx( errorcode,0.);
				//if( y<-topexp) 
				//	return cmplx( 0.,0.);

				//z=exp(y);
				//zi=1./z;
				//cosh=.5*(z+zi);
				//sinh=.5*(z-zi);

//				zi=1./exp(y);
//				cosh=.5*(exp(y)+zi);
//				sinh=.5*(exp(y)-zi);
				
//				zi=1./exp(y);				
//				z=exp(y);

//				cosh=.5*(z+zi);
//				sinh=.5*(z-zi);
				
//				if (bug)
//				{
//					char cstr[256];
//					sprintf(cstr,"y=%f, zi=%f", y, zi);
//					AfxMessageBox(cstr);
//					bug = FALSE;
//				}

//				return cmplx(cosh*sin(x),cos(x)*sinh);
//			}

			//inline cmplx ccos() {
			//	return cmplx(.5*(exp(y)+1./exp(y))*cos(x),-sin(x)*.5*(exp(y)-1./exp(y)));}

//			inline cmplx csin_error() 
//			{
//				if( y> topexp)
//				 	return cmplx( errorcode,0.);
//				if( y<-topexp) 
//					return cmplx( 0.,0.);			
//				return cmplx(.5*(exp(y)+1./exp(y))*sin(x),cos(x)*.5*(exp(y)-1./exp(y)));
//			}
      
			inline cmplx conjugate()
         {return cmplx(x,-y);}
      inline friend cmplx operator*(cmplx num,double real)
         {return cmplx(num.x*real,num.y*real);}
      inline friend cmplx operator*(double real,cmplx num)
        {
					return cmplx(num.x*real,num.y*real);
				}
      inline friend cmplx operator+(cmplx num,double real)
         {return cmplx(num.x+real,num.y);}
      inline friend cmplx operator+(double real,cmplx num)
         {return cmplx(num.x+real,num.y);}
      inline cmplx operator+=(double real)
         {return cmplx(x+=real,y);}
      inline cmplx operator-=(double real)
         {
         return cmplx(x-=real,y);}
      inline cmplx operator++()
         {x+=1.;return *this;}
      inline friend cmplx operator/(cmplx num,double real)
         {return cmplx(num.x/real,num.y/real);}
      inline friend cmplx operator-(cmplx num,double real)
         {return cmplx(num.x-real,num.y);}
      inline friend cmplx operator-(double real,cmplx num)
         {return cmplx(real-num.x,-num.y);}
      //double abs();
			//double real();			
			//double imag();			
			//double imaginary();			
			
			//double sum_of_sqrs();			
			void set_biomorph(double dBiomorph);
			void set_real(double set_x);
			void set_imag(double set_y);

      double squares();
      double magnitude();
      double biotest();

      cmplx cexp();      			
			cmplx clog();
		  cmplx csin();
			cmplx csin_error(); // used for alden's ray method
		  cmplx ccos();
		  cmplx csqrt();

      cmplx operator^(double expon);
//      cmplx operator^(double expon)
//			{
//				return ((*this).clog( ) * expon).cexp();			
//			}
			
      cmplx operator^(cmplx expon);
//      cmplx operator^(cmplx expon)
//			{
//				return ((*this).clog( ) * expon).cexp();
//			}

      friend cmplx operator^(double base, cmplx expon);
      //void print( char *ahead="",char *behind="");
      cmplx hurwitz(cmplx );

};

#define _cmplx_DEFINED

//double cmplx::abs();
//double cmplx::sum_of_sqrs();
cmplx cmplx::cexp();
cmplx cmplx::clog();
//double cmplx::squares();

cmplx cmplx::operator^(double expon);
cmplx cmplx::operator^(cmplx expon);

cmplx cmplx::csin();
cmplx cmplx::ccos();
cmplx cmplx::csin_error();

cmplx tangent ( cmplx& x);
cmplx sinh(cmplx& x);
cmplx asin(cmplx&x);
cmplx acos(cmplx&x);
cmplx arctan( cmplx& x);
cmplx cpow( cmplx& x, int nPower);
cmplx cpow( cmplx& x, cmplx& nPower);
double loggam(double x);
double gamma(double x);
double bernoulli(int n);   /* n even 0<=n*/
double expon(double x);
