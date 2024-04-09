//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include <math>
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TForm1 *Form1;

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
    String Message()
    {
      return Msg;
    }
    int Message(char* buff, int buffsize)
		{
      if (Msg.Length() < buffsize) {
        strcpy(buff, Msg.c_str());
        return Msg.Length();
      }
      else {
        strcpy(buff, "");
        return 0;
      }
    }
private:
  int ErrorCode;
  String Msg;
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
// The next two functions use recursion to call each other through multiple
// levels.
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
				//case '^': Operand1 = Operand1^Operand2; break;				// new
				case '^': Operand1 = pow( Operand1, Operand2 ); break;	// new
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
			case '.':																									// new
			{
				//cmplx cx = cmplx( atof( &( str[ index ] ) ), 0 );
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

			// new start

			// If none of the above options used, maybe the operand is a function
			// call (sin, sinh, asin, cos, acos, tan, atan, log).
			// No cosh() supported in cmplx class.
			default:
				// Is it the sin() function?
				// All values used inside the sin(), cos(), and tan() are in radians
				// where 2 pi radians = 360 degrees.
				if ( strncmp( &( str[ index ] ), "sin(", 4 ) == 0 )
				{
					index += 3;
					return sin( ParseOperand( str, index ) );
				}

				// Is it the sinh() function?
				if ( strncmp( &( str[ index ] ), "sinh(", 5 ) == 0 )
				{
					index += 4;
					return sinh( ParseOperand( str, index ) );
				}

				// Is it the asin() function?
				if ( strncmp( &( str[ index ] ), "asin(", 5 ) == 0 )
				{
					index += 4;
					return asin( ParseOperand( str, index ) );
				}

				// Is it the cos() function?
				else if ( strncmp( &( str[ index ] ), "cos(", 4 ) == 0 )
				{
					index += 3;
					return cos( ParseOperand( str, index ) );
				}

				// Is it the acos() function?
				else if ( strncmp( &( str[ index ] ), "acos(", 5 ) == 0 )
				{
					index += 4;
					return acos( ParseOperand( str, index ) );
				}

				// Is it the tan() function?
				else if ( strncmp( &( str[ index ] ), "tan(", 4 ) == 0 )
				{
					index += 3;
					return tan( ParseOperand( str, index ) );
				}

				// Is it the atan() function?
				else if ( strncmp( &( str[ index ] ), "atan(", 5 ) == 0 )
				{
					index += 4;
					return atan( ParseOperand( str, index ) );
				}

				// Is it the log() function?
				else if ( strncmp( &( str[ index ] ), "log(", 4 ) == 0 )
				{
					index += 3;
					return log( ParseOperand( str, index ) );
				}

				// If execution gets to here, something is wrong with the expression.
				else throw MyEHClass( 0, "Bad Expression" );

				// new end
		}
	}
	catch ( MyEHClass& )
	{
		throw;	// re-throw it for the next level up.
	}
}


