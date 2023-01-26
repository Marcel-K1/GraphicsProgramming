#include "AppWindow.h"

int main()
{
	AppWindow app;

	if (app.Init(1024, 768))
	{
		while (app.IsRun())
		{
			app.Broadcast();
		}

	}

	return 0;
}