//---------------------------------------------------------------------------
#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\Buttons.hpp>
#include <math>
//---------------------------------------------------------------------------
// Globals
double	z;
double	c;
//---------------------------------------------------------------------------
class MExpression							// abstract base class
{
	public:
		MExpression* Operand1;
		MExpression* Operand2;

		MExpression( MExpression* Op1 = 0, MExpression* Op2 = 0 )
		{
			Operand1 = Op1;
			Operand2 = Op2;
		}

		~MExpression()
		{
			if ( Operand1 ) delete Operand1;
			if ( Operand2 ) delete Operand2;
		}

		virtual double Do() = 0;	// pure virtual function
};

class MAddExpr : public MExpression
{
	public:
		MAddExpr( MExpression* Op1, MExpression* Op2 )
			: MExpression( Op1, Op2 ) {}
		double Do() { return ( Operand1->Do() + Operand2->Do() ); }
};

class MSubtractExpr : public MExpression
{
	public:
		MSubtractExpr( MExpression* Op1, MExpression* Op2 )
			: MExpression( Op1, Op2 ) {}
		double Do() { return ( Operand1->Do() - Operand2->Do() ); }
};

class MMultiplyExpr : public MExpression
{
	public:
		MMultiplyExpr( MExpression* Op1, MExpression* Op2 )
			: MExpression( Op1, Op2 ) {}
		double Do() { return ( Operand1->Do() * Operand2->Do() ); }
};

class MDivideExpr : public MExpression
{
	public:
		MDivideExpr( MExpression* Op1, MExpression* Op2 )
			: MExpression( Op1, Op2 ) {}
		double Do() { return ( Operand1->Do() / Operand2->Do() ); }
};

class MExponentExpr : public MExpression
{
	public:
		MExponentExpr( MExpression* Op1, MExpression* Op2 )
			: MExpression( Op1, Op2 ) {}
		double Do() { return ( pow( Operand1->Do(), Operand2->Do() ) ); }
};

class MUnaryMinusExpr : public MExpression
{
	public:
		MUnaryMinusExpr( MExpression* Op1 ) : MExpression( Op1 ) {}
		double Do() { return ( -( Operand1->Do() ) ); }
};

class MZExpr : public MExpression
{
	public:
		MZExpr() : MExpression() {};
		double Do() { return z; }				// z MUST be global
};

class MCExpr : public MExpression
{
	public:
		MCExpr() : MExpression() {};
		double Do() { return c; }				// c MUST be global
};

class MLeafExpr : public MExpression
{
	public:
		double LeafOperand;
		MLeafExpr( double leafOp ) : MExpression() { LeafOperand = leafOp; }
		double Do() { return LeafOperand; }
};

class MSinExpr : public MExpression
{
	public:
		MSinExpr( MExpression* Op1 ) : MExpression( Op1 ) {}
		double Do() { return sin( Operand1->Do() ); }
};

class MASinExpr : public MExpression
{
	public:
		MASinExpr( MExpression* Op1 ) : MExpression( Op1 ) {}
		double Do() { return asin( Operand1->Do() ); }
};

class MSinhExpr : public MExpression
{
	public:
		MSinhExpr( MExpression* Op1 ) : MExpression( Op1 ) {}
		double Do() { return sinh( Operand1->Do() ); }
};

class MCosExpr : public MExpression
{
	public:
		MCosExpr( MExpression* Op1 ) : MExpression( Op1 ) {}
		double Do() { return cos( Operand1->Do() ); }
};

class MACosExpr : public MExpression
{
	public:
		MACosExpr( MExpression* Op1 ) : MExpression( Op1 ) {}
		double Do() { return acos( Operand1->Do() ); }
};

class MTanExpr : public MExpression
{
	public:
		MTanExpr( MExpression* Op1 ) : MExpression( Op1 ) {}
		double Do() { return tan( Operand1->Do() ); }
};

class MATanExpr : public MExpression
{
	public:
		MATanExpr( MExpression* Op1 ) : MExpression( Op1 ) {}
		double Do() { return atan( Operand1->Do() ); }
};

class MLogExpr : public MExpression
{
	public:
		MLogExpr( MExpression* Op1 ) : MExpression( Op1 ) {}
		double Do() { return log( Operand1->Do() ); }
};
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TEdit *ExpressionEdit;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label5;
	TEdit *URealEdit;
	TEdit *UImagEdit;
	TEdit *VRealEdit;
	TEdit *VImagEdit;
	TEdit *WRealEdit;
	TEdit *WImagEdit;
	TBitBtn *OkBitBtn;
	TLabel *Label6;
	TLabel *Label7;
	TLabel *DebugLabel;
	TLabel *Label8;
	void __fastcall OkBitBtnClick(TObject *Sender);
	
private:	// User declarations
	double u, v, w;
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
	MExpression* __fastcall ParseExpression( const char* str, int& index );
	MExpression* __fastcall ParseOperand( const char* str, int& index );
};
//---------------------------------------------------------------------------
extern TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
