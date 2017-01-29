#include "MyForm.h"
#include <msclr\marshal_cppstd.h>
#include<string>

using namespace msclr::interop;
using namespace CppWinForm1;


[STAThreadAttribute]
int main(array<System::String^>^ args)
{
	// Enabling Windows XP visual effects before any controls are created
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	// Create the main window and run it
	// convert argv[0] from System to array of char (file name)
	IntPtr ptrToNativeString0 = Marshal::StringToHGlobalAnsi(args[0]);
	char* quotesTxt = static_cast<char*>(ptrToNativeString0.ToPointer());

	IntPtr ptrToNativeString1 = Marshal::StringToHGlobalAnsi(args[1]);
	char* userQuotesTxt = static_cast<char*>(ptrToNativeString1.ToPointer());

	Application::Run(gcnew MyForm(quotesTxt, userQuotesTxt));
	return 0;
}
