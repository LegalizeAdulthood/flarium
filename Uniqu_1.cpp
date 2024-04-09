//////////////////////////////
// Unique Parser by Gerry Myers
//

#include "stdafx.h"
#include "Flarium24.h"

#include "Flarium24Doc.h"
#include "Flarium24View.h"
#include "mainfrm.h"
#include <math.h>

void CFlarium24View::OnDrawUnique()
{
  // Editor Dialog


}

//---------------------------------------------------------------------------
//#include <vcl\vcl.h>
//#pragma hdrstop

//#include "Unit1.h"
//---------------------------------------------------------------------------
//#pragma resource "*.dfm"
//TForm1 *Form1;

//
// A simple class that could be used for exception
// handling chores.
//

class MyEHClass {
  public:
    MyEHClass(int error, char* msg)
    {
      ErrorCode = error;
      Msg = msg;
    }
    int Error()
    {
      return ErrorCode;
    }
    CString Message()
    {
      return Msg;
    }
    int Message(char* buff, int buffsize)
		{
      if (Msg.GetLength() < buffsize) {
        strcpy(buff, Msg);
        //strcpy(buff, Msg.c_str());
        return Msg.GetLength();
      }
      else {
        strcpy(buff, "");
        return 0;
      }
    }
private:
  int ErrorCode;
  CString Msg;
};


//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	u = v = w = z = 0;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::OkBitBtnClick(TObject *Sender)
{
	try
	{
		// If there is nothing in the string, do nothing.
		if ( ExpressionEdit->Text.Length() <= 0 ) return;

		u = atof( URealEdit->Text.c_str() );
		v = atof( VRealEdit->Text.c_str() );
		w = atof( WRealEdit->Text.c_str() );
		int i = 0;
		z = ParseExpression( ExpressionEdit->Text.c_str(), i );
		DebugLabel->Caption = AnsiString( z );
	}
	catch ( MyEHClass& )
	{
		Application->MessageBox( "Something wrong in the expression!",
			"Invalid Expression", MB_OK | MB_ICONEXCLAMATION );

		DebugLabel->Caption = "Invalid Expression.";
	}
}
//---------------------------------------------------------------------------
double __fastcall TForm1::ParseExpression( const char* str, int& index )
{
	try
	{
		//
		// Parse out the first operand of this expression.
		//
		double Operand1 = ParseOperand( str, index );

		//
		// Determine the operation.  The next character should be an operator.
		// Prime the pump.
		//
		while ( str[ index ] == ' ' ) index++;		// eat whitespace
		char Operation = str[ index ];

		// Repeat this block as long as there is more expression left.  If this
		// is a "two operand" expression, this loop will only execute once.
		// However, if this is a three, four, or more operand expression, this
		// loop will execute once for each operand (except for the first operand).
		// The current progress is always held as operand 1.
		while ( ( Operation != '\0' ) && ( Operation != ')' ) )
		{
			//
			// Parse out the second operand in this expression.
			//
			double Operand2 = ParseOperand( str, ++index );

			//
			// Perform the operation with the two operands.
			//
			switch ( Operation )
			{
				case '+': Operand1 = Operand1 + Operand2; break;
				case '-': Operand1 = Operand1 - Operand2; break;
				case '*': Operand1 = Operand1 * Operand2; break;
				case '/': Operand1 = Operand1 / Operand2; break;
				default: throw MyEHClass( 0, "Bad Expression" );
			}

			while ( str[ index ] == ' ' ) index++;		// eat whitespace
			Operation = str[ index ];
		}

		// Return the accumulated result.
		return Operand1;
	}
	catch ( MyEHClass& )
	{
		throw;	// re-throw it for the next level up.
	}
}
//---------------------------------------------------------------------------
double __fastcall TForm1::ParseOperand( const char* str, int& index )
{
	try
	{
		// Get rid of any leading blanks.
		while ( str[ index ] == ' ' ) index++;

		switch ( str[ index ] )
		{
			// Is this a sub-expression?
			case '(':
			{
				index++;
				double d = ParseExpression( str, index );

				// Get rid of any leading blanks.
				while ( str[ index ] == ' ' ) index++;

				// The current character (left over from the above sub-expression)
				// should be ')'.  If not, the entire expression is bad.
				if ( str[ index++ ] != ')' ) throw MyEHClass( 0, "Bad Expression" );

				// Store the first operand.
				return d;
			}

			// Is this the Z data member?
			case 'z':
			case 'Z':
				index++;						// advance to the next character
				return z;

			// Is this the U data member?
			case 'u':
			case 'U':
				index++;						// advance to the next character
				return u;

			// Is this the V data member?
			case 'v':
			case 'V':
				index++;						// advance to the next character
				return v;

			// Is this the W data member?
			case 'w':
			case 'W':
				index++;						// advance to the next character
				return w;

			// Is this a number?
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
			{
				//Cmplx cx = Cmplx( atof( str ), 0 );
				double d = atof( &( str[ index ] ) );

				// Move to the end of this number.
				while ( ( ( str[ index ] >= '0' ) && ( str[ index ] <= '9' ) ) ||
									( str[ index ] == '.' ) )
					index++;
				return d;
			}

			// Is this the unary minus?  If so, break down any sub-expression that
			// may be sitting behind it.
			case '-':
				return -( ParseExpression( str, ++index ) );

			// If none of the above options used, something is wrong with the
			// expression.
			default:
				throw MyEHClass( 0, "Bad Expression" );
		}
	}
	catch ( MyEHClass& )
	{
		throw;	// re-throw it for the next level up.
	}
}


/////////////////////////////////////////////////////////////////////////////
// CUnique dialog


CUnique::CUnique(CWnd* pParent /*=NULL*/)
	: CDialog(CUnique::IDD, pParent)
{
	//{{AFX_DATA_INIT(CUnique)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CUnique::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUnique)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CUnique, CDialog)
	//{{AFX_MSG_MAP(CUnique)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUnique message handlers
